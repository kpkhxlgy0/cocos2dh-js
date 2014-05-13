#include "HWebView.h"
#include "HWebViewImpl.h"

NS_CC_H_BEGIN

HWebView* HWebView::create(const Size &INsize) {
	HWebView* pTemp = new HWebView();
	if (pTemp && pTemp->initWithSize(INsize)) {
		pTemp->autorelease();
		return pTemp;
	}
	return NULL;
}

HWebView::HWebView() : m_pWebViewImpl(NULL) {
	
}

HWebView::~HWebView() {
	delete m_pWebViewImpl;
}

bool HWebView::initWithSize(const Size &INsize) {
	m_pWebViewImpl = createSystemWebView(this);
	m_pWebViewImpl->initWithSize(INsize);
    setPosition(Point(0, 0));
    setAnchorPoint(Point(0.5, 0.5));
	setContentSize(INsize);
	return true;
}
void HWebView::setPosition(const Point &INpoint) {
    CCNode::setPosition(INpoint);
    if (m_pWebViewImpl != NULL) {
        m_pWebViewImpl->setPosition(INpoint);
    }
}
void HWebView::setVisible(bool visible) {
    CCNode::setVisible(visible);
    if (m_pWebViewImpl != NULL) {
        m_pWebViewImpl->setVisible(visible);
    }
}
void HWebView::setContentSize(const Size &INsize) {
	CCNode::setContentSize(INsize);
	if (m_pWebViewImpl) {
		m_pWebViewImpl->setContentSize(INsize);
	}
}
void HWebView::setAnchorPoint(const Point& anchorPoint) {
    CCNode::setAnchorPoint(anchorPoint);
    if (m_pWebViewImpl != NULL) {
        m_pWebViewImpl->setAnchorPoint(anchorPoint);
    }
}
void HWebView::visit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated) {
    CCNode::visit(renderer, parentTransform, parentTransformUpdated);
    if (m_pWebViewImpl != NULL) {
        m_pWebViewImpl->visit();
    }
}
void HWebView::onEnter() {
    CCNode::onEnter();
    if (m_pWebViewImpl) {
		m_pWebViewImpl->onEnter();
	}
}
void HWebView::onExit() {
    CCNode::onExit();
    if (m_pWebViewImpl) {
		m_pWebViewImpl->onExit();
	}
}

void HWebView::setDelegate(cocos2d::h::HWebViewDelegate *INpDelegate) {
	if (m_pWebViewImpl) {
		m_pWebViewImpl->setDelegate(INpDelegate);
	}
}

void HWebView::loadURL(const char *INurl) {
	if (m_pWebViewImpl) {
		m_pWebViewImpl->loadURL(INurl);
	}
}

void HWebView::stopLoading() {
    if (m_pWebViewImpl) {
		m_pWebViewImpl->stopLoading();
	}
}
void HWebView::reload() {
    if (m_pWebViewImpl) {
		m_pWebViewImpl->reload();
	}
}

void HWebView::goBack() {
    if (m_pWebViewImpl) {
		m_pWebViewImpl->goBack();
	}
}
void HWebView::goForward() {
    if (m_pWebViewImpl) {
		m_pWebViewImpl->goForward();
	}
}

bool HWebView::canGoBack() {
    if (m_pWebViewImpl) {
		return m_pWebViewImpl->canGoBack();
	}
    return false;
}

bool HWebView::canGoForward() {
    if (m_pWebViewImpl) {
		return m_pWebViewImpl->canGoForward();
	}
    return false;
}
bool HWebView::isLoading() {
    if (m_pWebViewImpl) {
		return m_pWebViewImpl->isLoading();
	}
    return false;
}

NS_CC_H_END
