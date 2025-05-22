#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Базовый класс
class Personality {
private:
    static int totalCount; 
protected: 
    string name;
    string occupation;

public:
    Personality() : name("Неизвестно"), occupation("Неизвестно") {
        totalCount++;
    }

    Personality(string n, string o) : name(n), occupation(o) {
        totalCount++;
    }

    virtual ~Personality() {
        totalCount--;
    }

    virtual void showInfo() const = 0;

    static int getTotalCount() {
        return totalCount;
    }
};

int Personality::totalCount = 0;

// Класс-наследник 1 - Ученый
class Scientist : public Personality {
    string discovery;
public:
    Scientist(string n, string o, string d)
        : Personality(n, o), discovery(d) {}

    void showInfo() const override {
        cout << "Ученый: " << name << ", " << occupation
             << ", открытие: " << discovery << endl;
    }
};

// Класс-наследник 2 - Политик
class Politician : public Personality {
    string country;
public:
    Politician(string n, string o, string c)
        : Personality(n, o), country(c) {}

    void showInfo() const override {
        cout << "Политик: " << name << ", " << occupation
             << ", страна: " << country << endl;
    }
};

// Основной класс - Энциклопедия
class Encyclopedia {
private:
    static int storedCount; // Счетчик объектов в массиве
    vector<unique_ptr<Personality>> people;

public:
    void addPerson(unique_ptr<Personality> p) {
        people.push_back(move(p));
        storedCount++;
    }

    void showAll() const {
        for (const auto& p : people) {
            p->showInfo();
        }
    }

    static int getStoredCount() {
        return storedCount;
    }
};

int Encyclopedia::storedCount = 0;

int main() {
    cout << "Начальное количество объектов: " << Personality::getTotalCount() << endl;

    Encyclopedia book;
    book.addPerson(make_unique<Scientist>("Альберт Эйнштейн", "Физик", "Теория относительности"));
    book.addPerson(make_unique<Politician>("Владимир Путин", "Президент", "Россия"));

    cout << "\nПосле создания объектов:\n";
    cout << "Всего объектов: " << Personality::getTotalCount() << endl;
    cout << "В энциклопедии: " << Encyclopedia::getStoredCount() << endl;

    cout << "\nСодержимое энциклопедии:\n";
    book.showAll();

    return 0;
}