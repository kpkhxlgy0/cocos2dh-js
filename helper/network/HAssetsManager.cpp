#include "HAssetsManager.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <zlib.h>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#endif

#include "unzip/unzip.h"
#include "HHttpRequest.h"
#include "HHttpResponse.h"
#include "HHttpPacker.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

using namespace std;

#define H_KEY_OF_VERSION "h-current-version-code"
#define H_TEMP_PACKAGE_FILE_NAME "h-cocos2dx-update-temp-package.zip"
#define H_BUFFER_SIZE 8192
#define H_MAX_FILENAME 512

NS_CC_H_BEGIN

struct HErrorMessage {
    HAssetsManager::ErrorCode code;
    HAssetsManager *manager;
};

struct HProgressMessage {
    int percent;
    HAssetsManager *manager;
};

static string keyWithHash(const char *prefix, const string &url) {
    char buf[256];
    sprintf(buf, "%s%zd", prefix, std::hash<std::string>()(url));
    return buf;
}

static size_t getVersionCode(void *ptr, size_t size, size_t nmemb,
    void *userdata) {
    auto version = static_cast<string*>(userdata);
    version->append((char*)ptr, size * nmemb);
    return (size * nmemb);
}

static size_t downLoadPackage(void *ptr, size_t size, size_t nmemb,
    void *userdata) {
    FILE *fp = (FILE*)userdata;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

class HCheckRequestDelegate : public HHttpRequestDelegate, public Ref {
public:
    void setAssetsManager(HAssetsManager *assetsManager) {
        _assetsManager = assetsManager;
    }
private:
    void onReceiveHttpPacket(HHttpResponse *response) override {
        if (!response->isSucceed()) {
            if (_assetsManager->_delegate) {
                _assetsManager->_delegate->onCheckFailed();
            }
            return;
        }
        auto str = response->getResponseDataUnpacked();
        rapidjson::Document rootValue;
        rootValue.Parse<0>(str.c_str());
        const auto &resValue = rootValue["i0"];
        _assetsManager->_updateRemote = resValue["update"].GetBool();
        if (_assetsManager->_updateRemote) {
            _assetsManager->_downloadedVersion =
                resValue["version"].GetString();
            _assetsManager->_packageUrl = resValue["url"].GetString();
            const auto &dList = resValue["dList"];
            for (auto i = 0; i < dList.Size(); ++i) {
                _assetsManager->_vecDeleteRemote.push_back(dList[i].GetString());
            }
        } else {
            _assetsManager->setSearchPath();
        }
        if (_assetsManager->_delegate) {
            _assetsManager->_delegate->onCheckSuccess(
                _assetsManager->_updateRemote);
        }
    }
private:
    HAssetsManager *_assetsManager;
};

HAssetsManager::HAssetsManager(const string &versionFileUrl,
    const string &storagePath)
: _storagePath(storagePath)
, _packageUrl("")
, _versionFileUrl(versionFileUrl)
, _downloadedVersion("")
, _curl(nullptr)
, _connectionTimeout(0)
, _delegate(nullptr)
, _isDownloading(false)
, _shouldDeleteDelegateWhenExit(false)
, _updateRemote(false) {
    checkStoragePath();
    _schedule = new Helper();
    _request = new HHttpRequest();
}

HAssetsManager::~HAssetsManager() {
    if (_schedule) {
        _schedule->release();
    }
    if (_shouldDeleteDelegateWhenExit) {
        delete _delegate;
    }
}

const string& HAssetsManager::getVersionFileUrl() const {
    return _versionFileUrl;
}

void HAssetsManager::setVersionFileUrl(const string &versionFileUrl) {
    _versionFileUrl = versionFileUrl;
}

const string& HAssetsManager::getStoragePath() const {
    return _storagePath;
}

void HAssetsManager::setStoragePath(const string &storagePath) {
    _storagePath = storagePath;
    checkStoragePath();
}

void HAssetsManager::setDelegate(HAssetsManagerDelegateProtocol *delegate) {
    _delegate = delegate;
}

string HAssetsManager::getVersion() {
    return UserDefault::getInstance()->getStringForKey(keyOfVersion().c_str());
}

void HAssetsManager::setVersion(const std::string &version) {
    UserDefault::getInstance()->setStringForKey(keyOfVersion().c_str(),
        version);
}

void HAssetsManager::setConnectionTimeout(long timeout) {
    _connectionTimeout = timeout;
}

long HAssetsManager::getConnectionTimeout() const {
    return _connectionTimeout;
}

bool HAssetsManager::checkUpdate() {
    if (_versionFileUrl.size() == 0) {
        return false;
    }
    
    string recordedVersion =
        UserDefault::getInstance()->getStringForKey(keyOfVersion().c_str());
    
    _request->setUrl(_versionFileUrl.c_str());
    _request->setRequestType(network::HttpRequest::Type::POST);
    auto delegate = new HCheckRequestDelegate();
    delegate->autorelease();
    delegate->setAssetsManager(this);
    _request->setDelegate(delegate);
    auto packer = HHttpPacker::create();
    packer->packMap(1);
    packer->packString("version");
    packer->packString(recordedVersion);
    _request->addPacker("data", packer);
    if (_connectionTimeout) {
        network::HttpClient::getInstance()->setTimeoutForConnect(
            _connectionTimeout);
    }
    _request->send();
    return true;
}

void HAssetsManager::update() {
    if (_isDownloading) {
        return;
    }

    if (_versionFileUrl.size() == 0) {
        CCLOG("no version file url, "
            "or the package is not a zip file");
        _isDownloading = false;
        return;
    }
    
    if (!_updateRemote) {
        sendErrorMessage(ErrorCode::NO_NEW_VERSION);
        return;
    }
    
    for (const auto &v : _vecDeleteRemote) {
        auto path = _storagePath + v;
        rmdir(path);
    }
    _vecDeleteRemote.clear();
    
    _isDownloading = true;
    
    auto t = std::thread(&HAssetsManager::downloadAndUncompress, this);
    t.detach();
}

int assetsManagerProgressFunc(void *ptr, double totalToDownload,
    double nowDownloaded, double totalToUpLoad, double nowUpLoaded) {
    auto manager = static_cast<HAssetsManager*>(ptr);
    auto msg = new HAssetsManager::Message();
    msg->what = HAssetsManager::Message::Type::PROGRESS;

    auto progressData = new HProgressMessage();
    auto per = static_cast<int>(nowDownloaded / totalToDownload * 100);
    progressData->percent = per;
    progressData->manager = manager;
    msg->obj = progressData;

    manager->_schedule->sendMessage(msg);
    return 0;
}

HAssetsManager* HAssetsManager::create(const string &versionFileUrl,
    const string &storagePath, CheckSuccessCallback checkSuccessCallback,
    CheckFailedCallback checkFailedCallback, ErrorCallback errorCallback,
    ProgressCallback progressCallback, SuccessCallback successCallback) {
    class HDelegateProtocolImpl : public HAssetsManagerDelegateProtocol {
    public :
        HDelegateProtocolImpl(CheckSuccessCallback checkSuccessCallback,
            CheckFailedCallback checkFailedCallback,
            ErrorCallback errorCallback,
            ProgressCallback progressCallback,
            SuccessCallback successCallback)
        : _checkSuccessCallback(checkSuccessCallback)
        , _checkFailedCallback(checkFailedCallback)
        , _errorCallback(errorCallback)
        , _progressCallback(progressCallback)
        , _successCallback(successCallback) {}
        void onCheckSuccess(bool update) override {
            _checkSuccessCallback(update);
        }
        void onCheckFailed() override {
            _checkFailedCallback();
        }
        void onError(HAssetsManager::ErrorCode errorCode) override {
            _errorCallback(int(errorCode));
        }
        void onProgress(int percent) override { _progressCallback(percent); }
        void onSuccess() override { _successCallback(); }
    private :
        CheckSuccessCallback _checkSuccessCallback;
        CheckFailedCallback _checkFailedCallback;
        ErrorCallback _errorCallback;
        ProgressCallback _progressCallback;
        SuccessCallback _successCallback;
    };

    auto manager = new HAssetsManager(versionFileUrl, storagePath);
    auto delegate = new HDelegateProtocolImpl(checkSuccessCallback,
        checkFailedCallback,
        errorCallback,
        progressCallback,
        successCallback);
    manager->setDelegate(delegate);
    manager->_shouldDeleteDelegateWhenExit = true;
    manager->autorelease();
    return manager;
}

bool HAssetsManager::mkdir(const string &path) {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    mode_t processMask = umask(0);
    int ret = ::mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    umask(processMask);
    if (ret != 0 && (errno != EEXIST)) {
        return false;
    }
    return true;
#else
    BOOL ret = CreateDirectoryA(path.c_str(), nullptr);
    if (!ret && ERROR_ALREADY_EXISTS != GetLastError()) {
        return false;
    }
    return true;
#endif
}

bool HAssetsManager::rmdir(const string &path) {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS && !TARGET_IPHONE_SIMULATOR
    std::remove(path.c_str());
#else
    std::string command = "rm -r ";
    // Path may include space.
    command += "\"" + path + "\"";
    system(command.c_str());
#endif
#else
    std::string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + path + "\"";
    system(command.c_str());
#endif
    return errno == 0;
}

std::string HAssetsManager::dirname(const std::string &filename) {
    size_t pos = filename.rfind('/');
    if (pos != std::string::npos) {
        return filename.substr(0, pos);
    }
    return "";
}
std::string HAssetsManager::basename(const std::string &filename, const std::string &ext) {
    auto name = filename;
    size_t pos = name.rfind('/');
    if (pos != std::string::npos) {
        name = name.substr(pos + 1);
    }
    if (!ext.empty()) {
        pos = name.rfind('.');
        if (pos != std::string::npos) {
            auto ext1 = name.substr(pos);
            if (ext == ext1) {
                return name.substr(0, pos);
            }
        }
    }
    return name;
}
std::string HAssetsManager::extname(const std::string &filename) {
    auto name = filename;
    size_t pos = name.rfind('/');
    if (pos != std::string::npos) {
        name = name.substr(pos + 1);
    }
    pos = name.rfind('.');
    if (pos != std::string::npos) {
        return name.substr(pos);
    }
    return "";
}
std::string HAssetsManager::changeExt(const std::string &filename, const std::string &ext) {
    auto dir = dirname(filename);
    auto ext1 = extname(filename);
    auto base = basename(filename, ext1);
    if (!dir.empty() && *dir.rbegin() != '/') {
        dir += "/";
    }
    return dir + base + ext;
}
std::string HAssetsManager::changeExt(const std::string &filename) {
    auto path = filename;
    auto ext = extname(path);
    if (ext == ".jpg" || ext == ".png") {
        path = changeExt(path, ".di");
    } else if (ext == ".fnt") {
        path = changeExt(path, ".df");
    } else if (ext == ".json") {
        path = changeExt(path, ".dc");
    } else if (ext == ".caf" || ext == ".mp3" || ext == ".wav") {
        path = changeExt(path, ".ds");
    } else if (ext == ".ccbi") {
        path = changeExt(path, ".du");
    } else if (ext == ".plist") {
        path = changeExt(path, ".dp");
    } else if (ext == ".js") {
        path = changeExt(path, ".dj");
    }
    return path;
}
bool HAssetsManager::checkToDecrypt(const std::string &path) {
    auto ext = extname(path);
    if (ext == ".di") {
        return true;
    } else if (ext == ".df") {
        return true;
    } else if (ext == ".dc") {
        return true;
    } else if (ext == ".ds") {
        return true;
    } else if (ext == ".du") {
        return true;
    } else if (ext == ".dp") {
        return true;
    } else if (ext == ".dj") {
        return true;
    }
    return false;
}

bool HAssetsManager::isDirectory(const std::string &path) {
    struct stat buf;
    stat(path.c_str(), &buf);
    if(S_IFDIR & buf.st_mode){
        return true;
    }
    return false;
}
std::vector<std::string> HAssetsManager::readdir(const std::string &path, bool recursive) {
    std::vector<std::string> ret;
    DIR *dir;
    struct dirent *ent;
    
    dir = opendir(path.c_str());
    
    ent = ::readdir(dir);
    while(ent) {
        if(ent->d_type & DT_DIR) {
            if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                ent = ::readdir(dir);
                continue;
            }
            std::string childPath = path + "/" + ent->d_name;
            if (isDirectory(childPath)) {
                std::vector<std::string> sub = readdir(childPath, recursive);
                for (const auto &v : sub) {
                    ret.push_back(v);
                }
            } else {
                ret.push_back(childPath);
            }
        }
        ent = ::readdir(dir);
    }
    return ret;
}

bool HAssetsManager::downLoad() {
    if (_packageUrl.length() == 0) {
        return true;
    }
    string outFileName = _storagePath + H_TEMP_PACKAGE_FILE_NAME;
    FILE *fp = fopen(outFileName.c_str(), "wb");
    if (!fp) {
        sendErrorMessage(ErrorCode::CREATE_FILE);
        return false;
    }
    _curl = curl_easy_init();
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, _packageUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, downLoadPackage);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION,
        assetsManagerProgressFunc);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
    res = curl_easy_perform(_curl);
    curl_easy_cleanup(_curl);
    if (res) {
        sendErrorMessage(ErrorCode::NETWORK);
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}

void HAssetsManager::checkStoragePath() {
    if (_storagePath.size() > 0 &&
        _storagePath[_storagePath.size() - 1] != '/') {
        _storagePath.append("/");
    }
}

bool HAssetsManager::uncompress() {
    string outFileName = _storagePath + H_TEMP_PACKAGE_FILE_NAME;
    if (!FileUtils::getInstance()->isFileExist(outFileName)) {
        return true;
    }
    unzFile zipfile = unzOpen(outFileName.c_str());
    if (!zipfile) {
        CCLOG("can not open downloaded zip file %s", outFileName.c_str());
        return false;
    }

    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK) {
        CCLOG("can not read file global info of %s", outFileName.c_str());
        unzClose(zipfile);
        return false;
    }

    char readBuffer[H_BUFFER_SIZE];

    CCLOG("start uncompressing");

    uLong i;
    for (i = 0; i < global_info.number_entry; ++i) {
        unz_file_info fileInfo;
        char fileName[H_MAX_FILENAME];
        if (unzGetCurrentFileInfo(zipfile,
                &fileInfo,
                fileName,
                H_MAX_FILENAME,
                nullptr,
                0,
                nullptr,
                0) != UNZ_OK) {
            CCLOG("can not read file info");
            unzClose(zipfile);
            return false;
        }

        string fullPath = _storagePath + fileName;
        const size_t filenameLength = strlen(fileName);

        if (fileName[filenameLength - 1] == '/') {
            if (!HAssetsManager::mkdir(fullPath)) {
                CCLOG("can not create directory %s", fullPath.c_str());
                unzClose(zipfile);
                return false;
            }
        } else {
            string fileNameStr(fileName);
            size_t startIndex = 0;
            size_t index = fileNameStr.find("/", startIndex);

            while(index != -1) {
                string dir = _storagePath + fileNameStr.substr(0, index);
                FILE *out = fopen(dir.c_str(), "r");

                if(!out) {
                    if (!HAssetsManager::mkdir(dir)) {
                        CCLOG("can not create directory %s", dir.c_str());
                        unzClose(zipfile);
                        return false;
                    } else {
                        CCLOG("create directory %s",dir.c_str());
                    }
                } else {
                    fclose(out);
                }

                startIndex = index + 1;
                index = fileNameStr.find("/", startIndex);
            }

            if (unzOpenCurrentFile(zipfile) != UNZ_OK) {
                CCLOG("can not open file %s", fileName);
                unzClose(zipfile);
                return false;
            }

            FILE *out = fopen(fullPath.c_str(), "wb");
            if (!out) {
                CCLOG("can not open destination file %s", fullPath.c_str());
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                return false;
            }

            int error = UNZ_OK;
            do {
                error = unzReadCurrentFile(zipfile, readBuffer, H_BUFFER_SIZE);
                if (error < 0) {
                    CCLOG("can not read zip file %s, error code is %d",
                        fileName, error);
                    unzCloseCurrentFile(zipfile);
                    unzClose(zipfile);
                    return false;
                }

                if (error > 0) {
                    fwrite(readBuffer, error, 1, out);
                }
            } while(error > 0);

            fclose(out);
        }

        unzCloseCurrentFile(zipfile);

        if ((i + 1) < global_info.number_entry) {
            if (unzGoToNextFile(zipfile) != UNZ_OK) {
                CCLOG("can not read next file");
                unzClose(zipfile);
                return false;
            }
        }
    }

    CCLOG("end uncompressing");
    return true;
}

void HAssetsManager::setSearchPath() {
//    auto searchPaths = FileUtils::getInstance()->getSearchPaths();
//    auto iter = searchPaths.begin();
//    searchPaths.insert(iter, _storagePath);
//    FileUtils::getInstance()->setSearchPaths(searchPaths);
}

void HAssetsManager::sendErrorMessage(HAssetsManager::ErrorCode code) {
    auto msg = new Message();
    msg->what = HAssetsManager::Message::Type::ERROR;

    auto errorMessage = new HErrorMessage();
    errorMessage->code = code;
    errorMessage->manager = this;
    msg->obj = errorMessage;

    _schedule->sendMessage(msg);
}

void HAssetsManager::downloadAndUncompress() {
    do {
        createStoragePath();
        if (_updateRemote) {
            if (!downLoad()) {
                break;
            }

            auto msg1 = new HAssetsManager::Message();
            msg1->what = Message::Type::RECORD_DOWNLOADED_VERSION;
            msg1->obj = this;
            _schedule->sendMessage(msg1);
        }

        if (!uncompress()) {
            sendErrorMessage(ErrorCode::UNCOMPRESS);
            break;
        }

        // Record updated version and remove downloaded zip file
        auto msg2 = new HAssetsManager::Message();
        msg2->what = Message::Type::UPDATE_SUCCEED;
        msg2->obj = this;
        _schedule->sendMessage(msg2);
    } while (0);

    _isDownloading = false;
}

void HAssetsManager::createStoragePath() {
    HAssetsManager::mkdir(_storagePath);
}

void HAssetsManager::destroyStoragePath() {
    setVersion("");
    HAssetsManager::rmdir(_storagePath);
}

string HAssetsManager::keyOfVersion() const {
    return keyWithHash(H_KEY_OF_VERSION, _versionFileUrl);
}

#pragma mark - Helper

HAssetsManager::Helper::Helper() {
    _messageQueue = new list<Message*>();
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0,
        false);
}

HAssetsManager::Helper::~Helper() {
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    delete _messageQueue;
}

void HAssetsManager::Helper::update(float dt) {
    Message *msg = nullptr;

    _messageQueueMutex.lock();
    if (_messageQueue->size() == 0) {
        _messageQueueMutex.unlock();
        return;
    }
    Message *proMsg = nullptr;
    for (auto it = _messageQueue->begin(); it != _messageQueue->end(); ++it) {
        if((*it)->what == HAssetsManager::Message::Type::PROGRESS) {
            if (proMsg) {
                _messageQueue->remove(proMsg);
                delete (HProgressMessage*)proMsg->obj;
                delete proMsg;
            }
            proMsg = *it;
        }
    }
    msg = *(_messageQueue->begin());
    _messageQueue->pop_front();
    _messageQueueMutex.unlock();

    switch (msg->what) {
        case HAssetsManager::Message::Type::UPDATE_SUCCEED:
            handleUpdateSucceed(msg);
            break;
        case HAssetsManager::Message::Type::RECORD_DOWNLOADED_VERSION:
            break;
        case HAssetsManager::Message::Type::PROGRESS:
            if (((HProgressMessage*)msg->obj)->manager->_delegate) {
                ((HProgressMessage*)msg->obj)->manager->_delegate->onProgress(
                    ((HProgressMessage*)msg->obj)->percent);
            }
            delete (HProgressMessage*)msg->obj;
            break;
        case HAssetsManager::Message::Type::ERROR:
            if (((HErrorMessage*)msg->obj)->manager->_delegate) {
                ((HErrorMessage*)msg->obj)->manager->_delegate->onError(
                    ((HErrorMessage*)msg->obj)->code);
            }
            delete ((HErrorMessage*)msg->obj);
            break;
        default:
            break;
    }
    delete msg;
}

void HAssetsManager::Helper::sendMessage(Message *msg) {
    _messageQueueMutex.lock();
    _messageQueue->push_back(msg);
    _messageQueueMutex.unlock();
}

void HAssetsManager::Helper::handleUpdateSucceed(Message *msg) {
    auto manager = (HAssetsManager*)msg->obj;
    auto userDefault = UserDefault::getInstance();

    userDefault->setStringForKey(manager->keyOfVersion().c_str(),
        manager->_downloadedVersion);
    userDefault->flush();

    manager->setSearchPath();

    string zipfileName = manager->_storagePath + H_TEMP_PACKAGE_FILE_NAME;
    if (remove(zipfileName.c_str()) != 0) {
        CCLOG("can not remove downloaded zip file %s", zipfileName.c_str());
    }

    if (manager->_delegate) manager->_delegate->onSuccess();
}

NS_CC_H_END
