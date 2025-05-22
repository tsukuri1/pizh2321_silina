#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Собственные классы исключений (изменена иерархия наследования)
class MyCustomError : public runtime_error {
public:
    MyCustomError(const string& msg) : runtime_error(msg) {}
};

class MyAnotherError : public logic_error {  // Изменили базовый класс
public:
    MyAnotherError(const string& msg) : logic_error(msg) {}
};

class Personality {
protected:
    string name;
    string occupation;
public:
    Personality(string n = "Неизвестно", string o = "Неизвестно") 
        : name(n), occupation(o) {
        if (n.empty()) throw invalid_argument("Имя не может быть пустым");
    }
    
    virtual void showInfo() const = 0;
};

class Scientist : public Personality {
    string discovery;
public:
    Scientist(string n, string o, string d) : Personality(n, o), discovery(d) {
        if (d.empty()) throw MyCustomError("Открытие не может быть пустым");
        if (o.empty()) throw MyAnotherError("Род деятельности не может быть пустым");
    }
    
    void showInfo() const override {
        cout << name << " - " << occupation << ": " << discovery << endl;
    }
};

void processPersonality() {
    try {
        Scientist s("Эйнштейн", "", "E=mc²"); // Генерирует MyAnotherError
    } 
    catch (const invalid_argument& e) {
        cerr << "Локальная обработка: " << e.what() << endl;
        throw;
    }
}

template <typename T>
class ArrayContainer {
    vector<T> elements;
public:
    ArrayContainer(size_t n) {
        if (n > 100) throw length_error("Слишком большой размер массива");
        elements.reserve(n);
    }
    
    void add(const T& element) {
        if (elements.size() >= elements.capacity())
            throw out_of_range("Массив переполнен");
        elements.push_back(element);
    }
};

int main() {
    // 1. Обработка стандартных исключений
    try {
        ArrayContainer<int>(150);
    } 
    catch (const length_error& e) {
        cerr << "[1] Ошибка размера: " << e.what() << endl;
    }

    // 2. Обработка пользовательских исключений
    try {
        Scientist("Эйнштейн", "Физик", "");
    } 
    catch (const MyCustomError& e) {
        cerr << "[2] Пользовательская ошибка: " << e.what() << endl;
    }

    // 3. Иерархия обработки исключений
    try {
        processPersonality();
    }
    catch (const MyAnotherError& e) {
        cerr << "[3] Ошибка логики: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "[3] Стандартная ошибка: " << e.what() << endl;
    }
    catch (...) {
        cerr << "[3] Неизвестная ошибка" << endl;
    }

    // 4. Локальная обработка
    try {
        ArrayContainer<string> container(2);
        try {
            container.add("first");
            container.add("second");
            container.add("third"); // Вызовет out_of_range
        } 
        catch (...) {
            cerr << "[4] Локальная обработка переполнения" << endl;
        }
    } 
    catch (...) {
        cerr << "[4] Эта обработка не должна срабатывать" << endl;
    }

    // 5. Примитивные типы исключений
    try {
        throw 42;
    } 
    catch (int e) {
        cout << "[5] Числовая ошибка: " << e << endl;
    }

    try {
        throw "текст ошибки";
    } 
    catch (const char* e) {
        cout << "[5] Строковая ошибка: " << e << endl;
    }

    return 0;
}