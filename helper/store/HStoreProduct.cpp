
#include "HStoreProduct.h"

NS_CC_H_BEGIN

HStoreProduct* HStoreProduct::create(const std::string &identifier,
                                     const std::string &title,
                                     const std::string &description,
                                     float price,
                                     const std::string &priceLocale) {
    auto ret = new HStoreProduct();
    if (ret && ret->init(identifier, title, description, price, priceLocale)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool HStoreProduct::init(const std::string &identifier,
                               const std::string &title,
                               const std::string &description,
                               float price,
                               const std::string &priceLocale) {
    _identifier = identifier;
    _title = title;
    _description = description;
    _price = price;
    _priceLocale = priceLocale;
    return true;
}

NS_CC_H_END
