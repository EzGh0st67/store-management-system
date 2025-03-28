#include "StoreManager.h"
#include <limits>

void StoreManager::addStore(Store* store) {
    stores.push_back(store);
}

Store* StoreManager::findStoreWithLowestPrice(const std::string& productName) {
    if (stores.empty()) return nullptr;

    Store* bestStore = nullptr;
    double bestPrice = std::numeric_limits<double>::max();

    for (Store* store : stores) {
        try {
            double price = store->getProductPrice(productName);
            if (price < bestPrice) {
                bestPrice = price;
                bestStore = store;
            }
        } catch (const std::exception&) {
            // Пропускаем магазины, где нет этого товара
            continue;
        }
    }

    return bestStore;
}