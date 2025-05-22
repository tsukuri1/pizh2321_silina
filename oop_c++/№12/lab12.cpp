#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <memory>

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
    
    string getName() const { return name; }
    string getOccupation() const { return occupation; }
    string getDescription() const { return description; }
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
    // 1. Создание контейнера с использованием умных указателей
    vector<unique_ptr<Personality>> people;
    people.emplace_back(make_unique<Scientist>("Альберт Эйнштейн", "Физик", 
                        "Теория относительности", "E=mc²", 40));
    people.emplace_back(make_unique<Politician>("Владимир Путин", "Президент", 
                        "Президент России", "Россия", 20));
    people.emplace_back(make_unique<Scientist>("Мария Кюри", "Физик", 
                        "Исследование радиоактивности", "Радий и полоний", 35));
    people.emplace_back(make_unique<Politician>("Джо Байден", "Президент", 
                        "Президент США", "США", 3));

    // 2. Лямбда-функция для сортировки по убыванию имени
    auto sortDesc = [](const auto& a, const auto& b) {
        return a->getName() > b->getName();
    };

    // 3. Сортировка основного контейнера
    sort(people.begin(), people.end(), sortDesc);

    // 4. Вывод отсортированного контейнера
    cout << "=== Контейнер после сортировки по убыванию ===" << endl;
    for_each(people.begin(), people.end(), [](const auto& p) { p->display(); });

    // 5. Лямбда для определения политиков
    auto isPolitician = [](const auto& p) {
        const string& occ = p->getOccupation();
        return occ.find("Президент") != string::npos || 
               occ.find("Премьер") != string::npos;
    };

    // 6. Разделение на ученых и политиков
    list<unique_ptr<Personality>> politicians;
    auto it = partition(people.begin(), people.end(), 
        [&](const auto& p) { return !isPolitician(p); });
    
    // 7. Перенос политиков в отдельный контейнер
    move(it, people.end(), back_inserter(politicians));
    people.erase(it, people.end());

    // 8. Вывод контейнера с политиками
    cout << "\n=== Контейнер с политиками ===" << endl;
    for_each(politicians.begin(), politicians.end(), [](const auto& p) { p->display(); });

    // 9. Лямбда для сортировки по возрастанию
    auto sortAsc = [](const auto& a, const auto& b) {
        return a->getName() < b->getName();
    };

    // 10. Сортировка обоих контейнеров
    sort(people.begin(), people.end(), sortAsc);
    politicians.sort(sortAsc);

    // 11. Вывод отсортированных контейнеров
    cout << "\n=== Основной контейнер (ученые) по возрастанию ===" << endl;
    for_each(people.begin(), people.end(), [](const auto& p) { p->display(); });

    cout << "\n=== Контейнер политиков по возрастанию ===" << endl;
    for_each(politicians.begin(), politicians.end(), [](const auto& p) { p->display(); });

    // Очистка памяти не требуется благодаря unique_ptr

    return 0;
}