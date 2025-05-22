#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Базовый класс (абстрактный)
class Personality {
protected:
    string name;
    string occupation;
    string description;

public:
    Personality() : name("Неизвестно"), occupation("Неизвестно"), description("Нет данных") {
        cout << "Вызван конструктор Personality без параметров" << endl;
    }

    Personality(string n, string o, string d) : name(n), occupation(o), description(d) {
        cout << "Вызван конструктор Personality с параметрами" << endl;
    }

    virtual ~Personality() {
        cout << "Вызван деструктор Personality для " << name << endl;
    }

    // Чисто виртуальная функция
    virtual void displayFullInfo() const = 0;
};

// Класс-наследник 1 - Ученый
class Scientist : public Personality {
private:
    string discovery;
    int yearsActive;

public:
    Scientist() : Personality(), discovery("Неизвестно"), yearsActive(0) {
        cout << "Вызван конструктор Scientist без параметров" << endl;
    }

    Scientist(string n, string o, string d, string disc, int years) 
        : Personality(n, o, d), discovery(disc), yearsActive(years) {
        cout << "Вызван конструктор Scientist с параметрами" << endl;
    }

    ~Scientist() override {
        cout << "Вызван деструктор Scientist для " << name << endl;
    }

    void displayFullInfo() const override {
        cout << "=== Ученый ===" << endl;
        cout << "Имя: " << name << endl;
        cout << "Род деятельности: " << occupation << endl;
        cout << "Описание: " << description << endl;
        cout << "Важное открытие: " << discovery << endl;
        cout << "Годы активности: " << yearsActive << endl;
        cout << "---------------------" << endl;
    }
};

// Класс-наследник 2 - Политик
class Politician : public Personality {
private:
    string country;
    int yearsInPower;

public:
    Politician() : Personality(), country("Неизвестно"), yearsInPower(0) {
        cout << "Вызван конструктор Politician без параметров" << endl;
    }

    Politician(string n, string o, string d, string c, int years) 
        : Personality(n, o, d), country(c), yearsInPower(years) {
        cout << "Вызван конструктор Politician с параметрами" << endl;
    }

    ~Politician() override {
        cout << "Вызван деструктор Politician для " << name << endl;
    }

    void displayFullInfo() const override {
        cout << "=== Политик ===" << endl;
        cout << "Имя: " << name << endl;
        cout << "Род деятельности: " << occupation << endl;
        cout << "Описание: " << description << endl;
        cout << "Страна: " << country << endl;
        cout << "Годы у власти: " << yearsInPower << endl;
        cout << "---------------------" << endl;
    }
};

// Основной класс (Энциклопедия)
class Encyclopedia {
private:
    string title;
    int year;
    vector<unique_ptr<Personality>> personalities;

public:
    Encyclopedia(string t, int y) : title(t), year(y) {
        cout << "Вызван конструктор Encyclopedia" << endl;
    }

    ~Encyclopedia() {
        cout << "Вызван деструктор Encyclopedia" << endl;
    }

    // Добавление любой личности
    void addPersonality(unique_ptr<Personality> p) {
        personalities.push_back(move(p));
    }

    // Вывод всех данных
    void displayAll() const {
        cout << "\n=== Энциклопедия ===" << endl;
        cout << "Название: " << title << endl;
        cout << "Год издания: " << year << endl;
        cout << "\nСодержит следующие личности:\n";
        cout << "=====================" << endl;
        
        for (const auto& p : personalities) {
            p->displayFullInfo();
        }
    }
};

int main() {
    cout << "=== Часть 1: Массив базового типа ===" << endl;
    {
        vector<unique_ptr<Personality>> people;
        people.push_back(make_unique<Scientist>("Альберт Эйнштейн", "Физик", 
                                              "Теория относительности", "E=mc^2", 40));
        people.push_back(make_unique<Politician>("Уинстон Черчилль", "Премьер-министр",
                                               "Лидер Великобритании", "Великобритания", 10));
        people.push_back(make_unique<Scientist>("Мария Кюри", "Физик", 
                                              "Исследование радиоактивности", "Радий и полоний", 35));

        for (const auto& p : people) {
            p->displayFullInfo();
        }
    }
    cout << "=== Массив уничтожен ===" << endl << endl;

    cout << "=== Часть 2: Работа с основным классом ===" << endl;
    Encyclopedia encyclopedia("История в лицах", 2024);
    
    encyclopedia.addPersonality(make_unique<Scientist>("Никола Тесла", "Изобретатель", 
                                                    "Работы с электричеством", "Переменный ток", 45));
    encyclopedia.addPersonality(make_unique<Politician>("Теодор Рузвельт", "Президент", 
                                                     "26-й президент США", "США", 8));
    encyclopedia.addPersonality(make_unique<Scientist>("Галилео Галилей", "Астроном", 
                                                    "Гелиоцентрическая система", "Телескоп", 30));

    encyclopedia.displayAll();

    return 0;
}