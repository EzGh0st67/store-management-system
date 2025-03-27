#include "Customer.h"
#include "Store.h"
#include <stdexcept>

Customer::Customer(const std::string& name, double initialBalance) 
    : name(name), balance(initialBalance) {
    if (initialBalance < 0) 
        throw std::invalid_argument("Negative balance");
}

void Customer::addToShoppingList(const std::string& productName, int quantity) {
    if (quantity <= 0) 
        throw std::invalid_argument("Invalid quantity");
    
    // Проверяем наличие товара в списке
    for (auto& item : shoppingList) {
        if (item.first == productName) {
            item.second += quantity; // Увеличиваем количество
            return;
        }
    }
    // Если не найден - добавляем новый элемент
    shoppingList.emplace_back(productName, quantity);
}

void Customer::clearShoppingList() { shoppingList.clear(); }

void Customer::addBalance(double amount) {
    if (amount < 0) 
        throw std::invalid_argument("Negative amount");
    balance += amount;
}

double Customer::getBalance() const { return balance; }

void Customer::purchaseItems(Store& store) {
    double totalCost = 0.0;
    for (const auto& item : shoppingList) {
        const std::string& product = item.first;
        const int quantity = item.second;
        int available = store.getProductQuantity(product);
        if (available < quantity)
            throw std::runtime_error("Not enough " + product + " in store");
        totalCost += store.getProductPrice(product) * quantity;
    }
    
    if (totalCost > balance) {
        throw std::runtime_error("Insufficient funds");
    }

    // Если все проверки пройдены, совершаем покупку
    for (const auto& item : shoppingList) {
        const std::string& product = item.first;
        const int quantity = item.second;
        store.sellProduct(product, quantity);
    }
    
    balance -= totalCost;
}