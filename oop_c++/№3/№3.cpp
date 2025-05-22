#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Базовый класс
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

    virtual void display() const {
        cout << "Имя: " << name << endl;
        cout << "Род деятельности: " << occupation << endl;
        cout << "Описание: " << description << endl;
    }
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

    ~Scientist() {
        cout << "Вызван деструктор Scientist для " << name << endl;
    }

    void display() const override {
        Personality::display();
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

    ~Politician() {
        cout << "Вызван деструктор Politician для " << name << endl;
    }

    void display() const override {
        Personality::display();
        cout << "Страна: " << country << endl;
        cout << "Годы у власти: " << yearsInPower << endl;
        cout << "---------------------" << endl;
    }
};

int main() {
    cout << "=== Создание отдельных объектов ===" << endl;
    {
        Personality p1("Леонардо да Винчи", "Художник", "Итальянский гений");
        p1.display();

        Scientist s1("Альберт Эйнштейн", "Физик", "Теория относительности", 
                    "E=mc^2", 40);
        s1.display();

        Politician pol1("Уинстон Черчилль", "Премьер-министр", "Лидер Великобритании",
                      "Великобритания", 10);
        pol1.display();
    }
    cout << "=== Объекты уничтожены ===" << endl << endl;

    cout << "=== Массив базового типа ===" << endl;
    vector<Personality*> people;
    people.push_back(new Personality("Исаак Ньютон", "Физик", "Закон всемирного тяготения"));
    people.push_back(new Scientist("Мария Кюри", "Физик", "Исследование радиоактивности", 
                                 "Радий и полоний", 35));
    people.push_back(new Politician("Теодор Рузвельт", "Президент", "26-й президент США",
                                  "США", 8));

    for (auto p : people) {
        p->display();
        delete p;
    }
    people.clear();
    cout << endl;

    cout << "=== Массив типа Scientist ===" << endl;
    vector<Scientist> scientists;
    scientists.push_back(Scientist("Никола Тесла", "Изобретатель", "Работы с электричеством",
                                 "Переменный ток", 45));
    scientists.push_back(Scientist("Галилео Галилей", "Астроном", "Гелиоцентрическая система",
                                 "Телескоп", 30));

    for (auto& s : scientists) {
        s.display();
    }

    return 0;
}