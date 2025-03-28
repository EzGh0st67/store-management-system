#include <iostream>
#include "Store.h"
#include "Customer.h"
#include "StoreManager.h"

/**
 * @brief Демонстрация работы системы управления магазинами
 * 
 * В этом примере показаны основные возможности системы:
 * - Создание и управление магазинами
 * - Добавление товаров
 * - Работа с покупателями
 * - Поиск лучших цен
 */
int main() {
    try {
        std::cout << "=== Система управления магазинами ===\n\n";

        // Инициализация первого магазина
        std::cout << "Создание первого магазина...\n";
        Store store1("SuperMarket");
        store1.addProduct("Milk", 2.5, 10);
        store1.addProduct("Bread", 1.0, 15);
        std::cout << "Магазин " << store1.getName() << " создан успешно\n\n";

        // Инициализация второго магазина
        std::cout << "Создание второго магазина...\n";
        Store store2("MegaMarket");
        store2.addProduct("Milk", 2.2, 8);
        store2.addProduct("Eggs", 1.5, 20);
        std::cout << "Магазин " << store2.getName() << " создан успешно\n\n";

        // Создание менеджера магазинов
        std::cout << "Инициализация менеджера магазинов...\n";
        StoreManager manager;
        manager.addStore(&store1);
        manager.addStore(&store2);
        std::cout << "Менеджер магазинов инициализирован\n\n";

        // Создание покупателя
        std::cout << "Создание покупателя...\n";
        Customer customer("Alice", 50.0);
        customer.addToShoppingList("Milk", 2);
        customer.addToShoppingList("Bread", 1);
        std::cout << "Покупатель " << customer.getName() << " создан\n";
        std::cout << "Начальный баланс: $" << customer.getBalance() << "\n\n";

        // Покупка товаров
        std::cout << "=== Процесс покупки ===\n";
        customer.purchaseItems(store1);
        std::cout << "Покупка успешно завершена!\n";
        std::cout << "Остаток баланса: $" << customer.getBalance() << "\n\n";

        // Поиск лучшей цены
        std::cout << "=== Поиск лучшей цены ===\n";
        if (auto bestStore = manager.findStoreWithLowestPrice("Milk")) {
            std::cout << "Лучшая цена на молоко:\n";
            std::cout << "Магазин: " << bestStore->getName() << "\n";
            std::cout << "Цена: $" << bestStore->getProductPrice("Milk") << "\n";
        } else {
            std::cout << "Молоко не найдено ни в одном магазине\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\nНеизвестная ошибка\n";
        return 1;
    }

    std::cout << "\n=== Программа успешно завершена ===\n";
    return 0;
}