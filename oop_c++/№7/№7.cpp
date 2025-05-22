#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class Personality {
protected:
    string name;
    string occupation;
public:
    Personality(string n = "Неизвестно", string o = "Неизвестно") 
        : name(n), occupation(o) {}
    virtual ~Personality() = default;
    
    bool operator<(const Personality& other) const {
        return name < other.name;
    }
    bool operator>(const Personality& other) const {
        return name > other.name;
    }
    
    virtual void showInfo() const = 0;
    friend ostream& operator<<(ostream& os, const Personality& p);
};

class Scientist : public Personality {
    string discovery;
public:
    Scientist(string n = "Неизвестно", string o = "Неизвестно", string d = "Неизвестно")
        : Personality(n, o), discovery(d) {}
    void showInfo() const override {
        cout << "Ученый: " << name << ", " << occupation << ", открытие: " << discovery;
    }
};

class Politician : public Personality {
    string country;
public:
    Politician(string n = "Неизвестно", string o = "Неизвестно", string c = "Неизвестно")
        : Personality(n, o), country(c) {}
    void showInfo() const override {
        cout << "Политик: " << name << ", " << occupation << ", страна: " << country;
    }
};

ostream& operator<<(ostream& os, const Personality& p) {
    p.showInfo();
    return os;
}

template <typename T>
class ArrayContainer {
    vector<T> elements;
public:
    ArrayContainer(size_t n) {
        elements.reserve(n);
    }
    
    // Изменено: принимаем элемент по rvalue-ссылке
    void add(T&& element) {
        elements.push_back(move(element));
    }
    
    T& get(size_t index) {
        return elements.at(index);
    }
    
    // Для указателей нужна специализация
    const T& min() const {
        if (elements.empty()) throw runtime_error("Массив пуст");
        return *min_element(elements.begin(), elements.end());
    }
    
    const T& max() const {
        if (elements.empty()) throw runtime_error("Массив пуст");
        return *max_element(elements.begin(), elements.end());
    }
};

// Специализация для unique_ptr<Personality>
template <>
class ArrayContainer<unique_ptr<Personality>> {
    vector<unique_ptr<Personality>> elements;
public:
    ArrayContainer(size_t n) {
        elements.reserve(n);
    }
    
    void add(unique_ptr<Personality>&& element) {
        elements.push_back(move(element));
    }
    
    unique_ptr<Personality>& get(size_t index) {
        return elements.at(index);
    }
    
    // Возвращаем ссылку на объект
    const Personality& min() const {
        if (elements.empty()) throw runtime_error("Массив пуст");
        auto it = min_element(elements.begin(), elements.end(),
            [](const auto& a, const auto& b) { return *a < *b; });
        return **it;
    }
    
    const Personality& max() const {
        if (elements.empty()) throw runtime_error("Массив пуст");
        auto it = max_element(elements.begin(), elements.end(),
            [](const auto& a, const auto& b) { return *a < *b; });
        return **it;
    }
};

int main() {
    // Пример с целыми числами
    ArrayContainer<int> intContainer(3);
    intContainer.add(10);
    intContainer.add(5);
    intContainer.add(20);
    
    cout << "Целые числа:\n";
    cout << "Минимум: " << intContainer.min() << endl;
    cout << "Максимум: " << intContainer.max() << endl << endl;
    
    // Пример с указателями на базовый класс
    ArrayContainer<unique_ptr<Personality>> personContainer(4);
    personContainer.add(make_unique<Scientist>("Альберт Эйнштейн", "Физик", "E=mc²"));
    personContainer.add(make_unique<Politician>("Владимир Путин", "Президент", "Россия"));
    personContainer.add(make_unique<Scientist>("Никола Тесла", "Изобретатель", "Переменный ток"));
    personContainer.add(make_unique<Politician>("Авраам Линкольн", "Президент", "США"));
    
    cout << "Персоны:\n";
    cout << "Минимум (по имени):\n" << personContainer.min() << endl;
    cout << "Максимум (по имени):\n" << personContainer.max() << endl << endl;
    
    // Пример с конкретным классом-наследником
    ArrayContainer<Scientist> scientistContainer(2);
    scientistContainer.add(Scientist("Мария Кюри", "Физик", "Радий"));
    scientistContainer.add(Scientist("Исаак Ньютон", "Физик", "Гравитация"));
    
    cout << "Ученые:\n";
    cout << "Минимум (по имени):\n" << scientistContainer.min() << endl;
    cout << "Максимум (по имени):\n" << scientistContainer.max() << endl;
    
    return 0;
}