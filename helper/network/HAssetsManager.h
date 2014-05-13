#ifndef __HELPER_NETWORK_HASSETSMANAGER_H__
#define __HELPER_NETWORK_HASSETSMANAGER_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

#include <string>
#include <mutex>

NS_CC_H_BEGIN

class HHttpRequest;
class HAssetsManagerDelegateProtocol;

class HAssetsManager : public Node {
public:
    enum class ErrorCode {
        CREATE_FILE,
        NETWORK,
        NO_NEW_VERSION,
        UNCOMPRESS,
    };

    typedef std::function<void(bool)> CheckSuccessCallback;
    typedef std::function<void(void)> CheckFailedCallback;
    typedef std::function<void(int)> ErrorCallback;
    typedef std::function<void(int)> ProgressCallback;
    typedef std::function<void(void)> SuccessCallback;
public:
    HAssetsManager(const std::string &versionFileUrl = "",
        const std::string &storagePath = "");
    virtual ~HAssetsManager();
    
    const std::string& getVersionFileUrl() const;
    void setVersionFileUrl(const std::string &versionFileUrl);
    const std::string& getStoragePath() const;
    void setStoragePath(const std::string &storagePath);

    HAssetsManagerDelegateProtocol* getDelegate() const { return _delegate; }
    void setDelegate(HAssetsManagerDelegateProtocol *delegate);

    std::string getVersion();
    void setVersion(const std::string &version);
    const std::string& getVersionRemote() const {
        return _downloadedVersion;
    }

    long getConnectionTimeout() const;
    void setConnectionTimeout(long timeout);

    virtual bool checkUpdate();

    using Node::update;
    virtual void update();
public:
    friend int assetsManagerProgressFunc(void*, double, double, double, double);
    friend class HCheckRequestDelegate;
public:
    static HAssetsManager* create(const std::string &versionFileUrl,
        const std::string &storagePath,
        CheckSuccessCallback checkSuccessCallback,
        CheckFailedCallback checkFailedCallback,
        ErrorCallback errorCallback,
        ProgressCallback progressCallback,
        SuccessCallback successCallback);

    static bool mkdir(const std::string &path);
    static bool rmdir(const std::string &path);
    static std::string dirname(const std::string &filename);
    static std::string basename(const std::string &filename, const std::string &ext = "");
    static std::string extname(const std::string &filename);
    static std::string changeExt(const std::string &filename, const std::string &ext);
    static std::string changeExt(const std::string &filename);
    static bool checkToDecrypt(const std::string &path);
    static bool isDirectory(const std::string &path);
    static std::vector<std::string> readdir(const std::string &path, bool recursive = false);
protected:
    bool downLoad();
    void checkStoragePath();
    bool uncompress();
    void setSearchPath();
    void sendErrorMessage(ErrorCode code);
    void downloadAndUncompress();
private:
    typedef struct _Message {
    public:
        enum class Type {
            UPDATE_SUCCEED,
            RECORD_DOWNLOADED_VERSION,
            PROGRESS,
            ERROR
        };
    public:
        _Message() : what(Type::UPDATE_SUCCEED), obj(nullptr) {}
        Type what;
        void *obj;
    } Message;

    class Helper : public Ref {
    public:
        Helper();
        ~Helper();

        virtual void update(float dt);
        void sendMessage(Message *msg);
    private:
        void handleUpdateSucceed(Message *msg);
    private:
        std::list<Message*> *_messageQueue;
        std::mutex _messageQueueMutex;
    };
private:
    void createStoragePath();
    void destroyStoragePath();

    std::string keyOfVersion() const;
private:
    std::string _storagePath;

    std::string _packageUrl;
    std::string _versionFileUrl;

    std::string _downloadedVersion;

    void *_curl;

    Helper *_schedule;
    long _connectionTimeout;

    HAssetsManagerDelegateProtocol *_delegate;

    bool _isDownloading;
    bool _shouldDeleteDelegateWhenExit;
    
    HHttpRequest *_request;
    bool _updateRemote;
    std::vector<std::string> _vecDeleteRemote;
};

class HAssetsManagerDelegateProtocol {
public:
    virtual ~HAssetsManagerDelegateProtocol() {}
public:
    virtual void onCheckSuccess(bool update) {}
    virtual void onCheckFailed() {}
    virtual void onError(HAssetsManager::ErrorCode errorCode) {}
    virtual void onProgress(int percent) {}
    virtual void onSuccess() {}
};

NS_CC_H_END

#endif //__HELPER_NETWORK_HASSETSMANAGER_H__
