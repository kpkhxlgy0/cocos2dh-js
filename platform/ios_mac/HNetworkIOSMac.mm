
#include "HNetwork.h"
#import "ReachabilityIOSMac.h"

NS_CC_H_BEGIN

bool HNetwork::isLocalWiFiAvailable(void)
{
    return [[ReachabilityIOSMac reachabilityForLocalWiFi] currentReachabilityStatus] != NotReachable;
}

bool HNetwork::isInternetConnectionAvailable(void)
{
    return [[ReachabilityIOSMac reachabilityForInternetConnection] currentReachabilityStatus] != NotReachable;
}

bool HNetwork::isHostNameReachable(const char* hostName)
{
    NSString *hostName_ = [NSString stringWithUTF8String:hostName];
    return [[ReachabilityIOSMac reachabilityWithHostname:hostName_] currentReachabilityStatus] != NotReachable;
}

int HNetwork::getInternetConnectionStatus(void)
{
    NetworkStatus status = [[ReachabilityIOSMac reachabilityForInternetConnection] currentReachabilityStatus];
    if (status == ReachableViaWiFi) return kCCNetworkStatusReachableViaWiFi;
    if (status == ReachableViaWWAN) return kCCNetworkStatusReachableViaWWAN;
    return kCCNetworkStatusNotReachable;
}

NS_CC_H_END
