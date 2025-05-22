#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

// Базовый класс
class Personality {
protected:
    string name;
    string occupation;
    string description;

public:
    Personality() : name("Неизвестно"), occupation("Неизвестно"), description("Нет данных") {}
    Personality(string n, string o, string d) : name(n), occupation(o), description(d) {}
    virtual ~Personality() {}

    virtual void display() const {
        cout << "Имя: " << name << "\nРод деятельности: " << occupation 
             << "\nОписание: " << description << endl;
    }
    
    // Для сортировки по имени (по убыванию)
    bool operator<(const Personality& other) const {
        return name > other.name;
    }
    
    // Для поиска по условию (политики)
    bool isPolitician() const {
        return occupation.find("Президент") != string::npos || 
               occupation.find("Премьер") != string::npos;
    }
};

// Класс-наследник 1 - Ученый
class Scientist : public Personality {
    string discovery;
    int yearsActive;

public:
    Scientist(string n = "Неизвестно", string o = "Неизвестно", string d = "Нет данных",
              string disc = "Неизвестно", int years = 0)
        : Personality(n, o, d), discovery(disc), yearsActive(years) {}

    void display() const override {
        Personality::display();
        cout << "Открытие: " << discovery << "\nГоды активности: " << yearsActive 
             << "\n---------------------\n";
    }
};

// Класс-наследник 2 - Политик
class Politician : public Personality {
    string country;
    int yearsInPower;

public:
    Politician(string n = "Неизвестно", string o = "Неизвестно", string d = "Нет данных",
               string c = "Неизвестно", int years = 0)
        : Personality(n, o, d), country(c), yearsInPower(years) {}

    void display() const override {
        Personality::display();
        cout << "Страна: " << country << "\nГоды у власти: " << yearsInPower 
             << "\n---------------------\n";
    }
};

int main() {
    // 2. Создание контейнера (вектора) пользовательского типа
    vector<Personality*> people;
    people.push_back(new Scientist("Альберт Эйнштейн", "Физик", "Теория относительности", 
                                 "E=mc²", 40));
    people.push_back(new Politician("Владимир Путин", "Президент", "Президент России",
                                  "Россия", 20));
    people.push_back(new Scientist("Мария Кюри", "Физик", "Исследование радиоактивности",
                                 "Радий и полоний", 35));
    people.push_back(new Politician("Джо Байден", "Президент", "Президент США",
                                  "США", 3));

    // 3. Сортировка по убыванию (по имени)
    sort(people.begin(), people.end(), 
        [](Personality* a, Personality* b) { return *a < *b; });

    // 4. Просмотр отсортированного контейнера
    cout << "=== Контейнер после сортировки по убыванию ===" << endl;
    for (const auto& p : people) {
        p->display();
    }

    // 5. Поиск политиков
    // 6. Перемещение политиков в другой контейнер (list)
    list<Personality*> politicians;
    auto it = partition(people.begin(), people.end(),
        [](Personality* p) { return !p->isPolitician(); });
    
    politicians.assign(it, people.end());
    people.erase(it, people.end());

    // 7. Просмотр второго контейнера
    cout << "\n=== Контейнер с политиками ===" << endl;
    for (const auto& p : politicians) {
        p->display();
    }

    // 8. Сортировка обоих контейнеров по возрастанию
    sort(people.begin(), people.end(),
        [](Personality* a, Personality* b) { return *b < *a; });
    
    politicians.sort([](Personality* a, Personality* b) { return *b < *a; });

    // 9. Просмотр отсортированных контейнеров
    cout << "\n=== Основной контейнер (ученые) по возрастанию ===" << endl;
    for (const auto& p : people) {
        p->display();
    }

    cout << "\n=== Контейнер политиков по возрастанию ===" << endl;
    for (const auto& p : politicians) {
        p->display();
    }

    // Очистка памяти
    for (auto& p : people) delete p;
    for (auto& p : politicians) delete p;

    return 0;
}