#include <iostream>

// Функция обмена по значению - создает копии параметров
void swap_value(int a, int b) {
    std::cout << "  [swap_value] Получены копии: a = " << a << ", b = " << b << '\n';
    
    int temp = a;
    a = b;
    b = temp;
    
    std::cout << "  [swap_value] После обмена копий: a = " << a << ", b = " << b << '\n';
    std::cout << "  [swap_value] Изменения затронули только локальные копии!\n";
}

// Функция обмена по ссылке - работает с оригинальными переменными
void swap_reference(int &a, int &b) {
    std::cout << "  [swap_reference] Получены ссылки на оригиналы: a = " << a << ", b = " << b << '\n';
    
    int temp = a;
    a = b;
    b = temp;
    
    std::cout << "  [swap_reference] После обмена: a = " << a << ", b = " << b << '\n';
    std::cout << "  [swap_reference] Изменения затронули оригинальные переменные!\n";
}

// Функция обмена по указателю - работает через адреса
void swap_pointer(int *a, int *b) {
    // Проверка на nullptr для безопасности
    if (a == nullptr || b == nullptr) {
        std::cout << "  [swap_pointer] Ошибка: получен nullptr!\n";
        return;
    }
    
    std::cout << "  [swap_pointer] Получены указатели: *a = " << *a << ", *b = " << *b << '\n';
    std::cout << "  [swap_pointer] Адреса: a = " << a << ", b = " << b << '\n';
    
    int temp = *a;
    *a = *b;
    *b = temp;
    
    std::cout << "  [swap_pointer] После обмена: *a = " << *a << ", *b = " << *b << '\n';
    std::cout << "  [swap_pointer] Изменения затронули оригинальные переменные!\n";
}

int main() {
    int original_a = 5, original_b = 10;
    
    std::cout << "=== ДЕМОНСТРАЦИЯ СПОСОБОВ ПЕРЕДАЧИ ПАРАМЕТРОВ ===\n\n";
    std::cout << "Исходные значения: a = " << original_a << ", b = " << original_b << "\n\n";
    
    // Тест 1: Передача по значению
    {
        int a = original_a, b = original_b;  // Восстанавливаем значения
        
        std::cout << "1. ПЕРЕДАЧА ПО ЗНАЧЕНИЮ (Pass by Value):\n";
        std::cout << "  До вызова: a = " << a << ", b = " << b << '\n';
        swap_value(a, b);
        std::cout << "  После вызова: a = " << a << ", b = " << b << '\n';
        std::cout << "  ✓ Оригинальные переменные остались неизменными\n\n";
    }
    
    // Тест 2: Передача по ссылке
    {
        int a = original_a, b = original_b;  // Восстанавливаем значения
        
        std::cout << "2. ПЕРЕДАЧА ПО ССЫЛКЕ (Pass by Reference):\n";
        std::cout << "  До вызова: a = " << a << ", b = " << b << '\n';
        swap_reference(a, b);
        std::cout << "  После вызова: a = " << a << ", b = " << b << '\n';
        std::cout << "  ✓ Оригинальные переменные были изменены\n\n";
    }
    
    // Тест 3: Передача по указателю
    {
        int a = original_a, b = original_b;  // Восстанавливаем значения
        
        std::cout << "3. ПЕРЕДАЧА ПО УКАЗАТЕЛЮ (Pass by Pointer):\n";
        std::cout << "  До вызова: a = " << a << ", b = " << b << '\n';
        swap_pointer(&a, &b);
        std::cout << "  После вызова: a = " << a << ", b = " << b << '\n';
        std::cout << "  ✓ Оригинальные переменные были изменены\n\n";
    }
    
    std::cout << "=== ВЫВОДЫ ===\n";
    std::cout << "• По значению: безопасно, но не может изменить оригинал\n";
    std::cout << "• По ссылке: эффективно и безопасно для изменения оригинала\n";
    std::cout << "• По указателю: мощно, но требует осторожности (nullptr, арифметика)\n";
    
    return 0;
}