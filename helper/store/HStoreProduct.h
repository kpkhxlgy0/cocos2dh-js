
#ifndef __HELPER_STORE_HSTOREPRODUCT_H__
#define __HELPER_STORE_HSTOREPRODUCT_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

#pragma mark - HStoreProduct

class HStoreProduct : public Ref {
public:
    const std::string& getIdentifier() {
        return _identifier;
    }
    const std::string& getTitle() {
        return _title;
    }
    const std::string& getDescription() {
        return _description;
    }
    float getPrice() {
        return _price;
    }
    const std::string& getPriceLocale() {
        return _priceLocale;
    }
public:
    static HStoreProduct* create(const std::string &identifier,
                                 const std::string &title,
                                 const std::string &description,
                                 float price,
                                 const std::string &priceLocale);
private:
    HStoreProduct() {}
    bool init(const std::string &identifier,
                    const std::string &title,
                    const std::string &description,
                    float price,
                    const std::string &priceLocale);
    
    std::string _identifier;
    std::string _title;
    std::string _description;
    float _price;
    std::string _priceLocale;
};

NS_CC_H_END

#endif // __HELPER_STORE_HSTOREPRODUCT_H__
