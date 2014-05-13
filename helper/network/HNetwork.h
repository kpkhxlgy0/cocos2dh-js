
#ifndef __HELPER_NETWORK_HNETWORK_H__
#define __HELPER_NETWORK_HNETWORK_H__

#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

enum {
    kCCNetworkStatusNotReachable,
    kCCNetworkStatusReachableViaWiFi,
    kCCNetworkStatusReachableViaWWAN
};

class HNetwork {
public:
#pragma mark -
#pragma mark reachability
    
    /** @brief Checks whether a local wifi connection is available */
    static bool isLocalWiFiAvailable(void);
    
    /** @brief Checks whether the default route is available */
    static bool isInternetConnectionAvailable(void);
    
    /** @brief Checks the reachability of a particular host name */
    static bool isHostNameReachable(const char* hostName);
    
    /** @brief Checks Internet connection reachability status */
    static int getInternetConnectionStatus(void);
    
private:
    HNetwork(void) {}
};

NS_CC_H_END

#endif // __HELPER_NETWORK_HNETWORK_H__
