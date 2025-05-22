#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    
    // Для изменения описания
    void setDescription(const string& desc) {
        description = desc;
    }
    
    // Для поиска по имени
    bool hasName(const string& searchName) const {
        return name == searchName;
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
    // 1. Создание и заполнение контейнера (вектора) базового типа
    vector<Personality*> people;
    people.push_back(new Personality("Исаак Ньютон", "Физик", "Закон всемирного тяготения"));
    people.push_back(new Scientist("Альберт Эйнштейн", "Физик", "Теория относительности", 
                                 "E=mc²", 40));
    people.push_back(new Politician("Владимир Путин", "Президент", "Президент России",
                                  "Россия", 20));

    // 2. Просмотр контейнера
    cout << "=== Исходное содержимое контейнера ===" << endl;
    for (const auto& p : people) {
        p->display();
    }

    // 3. Изменение контейнера
    // Удаление элемента по условию (имя содержит "Ньютон")
    people.erase(
        remove_if(people.begin(), people.end(), 
            [](Personality* p) {
                if (p->hasName("Исаак Ньютон")) {
                    delete p;
                    return true;
                }
                return false;
            }),
        people.end()
    );
    
    // Изменение элемента
    for (auto& p : people) {
        if (p->hasName("Альберт Эйнштейн")) {
            p->setDescription("Создатель теории относительности, Нобелевский лауреат");
        }
    }

    // 4. Просмотр с использованием итераторов
    cout << "\n=== Измененное содержимое контейнера ===" << endl;
    for (auto it = people.begin(); it != people.end(); ++it) {
        (*it)->display();
    }

    // 5. Очистка памяти
    for (auto& p : people) {
        delete p;
    }
    people.clear();

    // 6. То же самое для пользовательского типа (Scientist)
    vector<Scientist> scientists;
    scientists.emplace_back("Никола Тесла", "Изобретатель", "Работы с электричеством",
                          "Переменный ток", 45);
    scientists.emplace_back("Мария Кюри", "Физик", "Исследование радиоактивности",
                          "Радий и полоний", 35);

    cout << "\n=== Контейнер ученых до изменений ===" << endl;
    for (const auto& s : scientists) {
        s.display();
    }

    // Удаление элемента
    scientists.erase(
        remove_if(scientists.begin(), scientists.end(),
            [](const Scientist& s) {
                return s.hasName("Никола Тесла");
            }),
        scientists.end()
    );

    // Изменение элемента
    for (auto& s : scientists) {
        if (s.hasName("Мария Кюри")) {
            s.setDescription("Первая женщина-лауреат Нобелевской премии");
        }
    }

    cout << "\n=== Контейнер ученых после изменений ===" << endl;
    for (auto it = scientists.begin(); it != scientists.end(); ++it) {
        it->display();
    }

    return 0;
}