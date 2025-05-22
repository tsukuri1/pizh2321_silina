#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Personality {
protected:
    string name;
    string occupation;
public:
    Personality(string n = "Неизвестно", string o = "Неизвестно") 
        : name(n), occupation(o) {}
    virtual void showInfo() const = 0;
    virtual ~Personality() = default;
};

class Scientist : public Personality {
    string discovery;
public:
    Scientist(string n = "Неизвестно", string o = "Неизвестно", string d = "Неизвестно")
        : Personality(n, o), discovery(d) {}
    void showInfo() const override {
        cout << "Ученый: " << name << ", " << occupation << ", открытие: " << discovery << endl;
    }
};

class Politician : public Personality {
    string country;
public:
    Politician(string n = "Неизвестно", string o = "Неизвестно", string c = "Неизвестно")
        : Personality(n, o), country(c) {}
    void showInfo() const override {
        cout << "Политик: " << name << ", " << occupation << ", страна: " << country << endl;
    }
};

class Encyclopedia {
    vector<unique_ptr<Personality>> people;
public:
    // Оператор + для добавления (теперь принимает rvalue ссылку)
    Encyclopedia& operator+(unique_ptr<Personality>&& p) {
        people.push_back(move(p));
        return *this;
    }
    
    // Префиксный ++
    Encyclopedia& operator++() {
        people.push_back(make_unique<Scientist>());
        return *this;
    }
    
    // Постфиксный ++ (теперь возвращает void)
    void operator++(int) {
        people.push_back(make_unique<Politician>());
    }
    
    // Оператор []
    Personality& operator[](size_t index) {
        return *people.at(index);
    }
    
    // Оператор вывода
    friend ostream& operator<<(ostream& os, const Encyclopedia& e) {
        for (const auto& p : e.people) {
            p->showInfo();
        }
        return os;
    }
};

int main() {
    Encyclopedia book;
    
    // Добавление через + (теперь с move)
    book + make_unique<Scientist>("Альберт Эйнштейн", "Физик", "E=mc²");
    book + make_unique<Politician>("Владимир Путин", "Президент", "Россия");
    
    // Добавление через ++
    ++book;  // Ученый по умолчанию
    book++;  // Политик по умолчанию
    
    // Вывод через <<
    cout << "Содержимое энциклопедии:\n" << book;
    
    // Доступ по индексу
    cout << "\nЭлемент 0:\n";
    book[0].showInfo();
    
    return 0;
}