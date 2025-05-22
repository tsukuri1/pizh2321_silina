#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Personality {
private:
    string name;
    string occupation;
    string description;

public:
    // Конструктор без параметров
    Personality() : name("Неизвестно"), occupation("Неизвестно"), description("Нет данных") {
        cout << "Вызван конструктор Personality без параметров" << endl;
    }

    // Конструктор с параметрами
    Personality(string n, string o, string d) : name(n), occupation(o), description(d) {
        cout << "Вызван конструктор Personality с параметрами" << endl;
    }

    // Конструктор копирования
    Personality(const Personality& other) : name(other.name), occupation(other.occupation), description(other.description) {
        cout << "Вызван конструктор копирования Personality" << endl;
    }

    // Деструктор
    ~Personality() {
        cout << "Вызван деструктор Personality для " << name << endl;
    }

    void display() const {
        cout << "Имя: " << name << endl;
        cout << "Род деятельности: " << occupation << endl;
        cout << "Описание: " << description << endl;
        cout << "---------------------" << endl;
    }
};

class Encyclopedia {
private:
    string title;
    int year;
    vector<Personality> personalities;

public:
    // Конструктор без параметров
    Encyclopedia() : title("Без названия"), year(0) {
        cout << "Вызван конструктор Encyclopedia без параметров" << endl;
    }

    // Конструктор с параметрами
    Encyclopedia(string t, int y) : title(t), year(y) {
        cout << "Вызван конструктор Encyclopedia с параметрами" << endl;
    }

    // Конструктор копирования
    Encyclopedia(const Encyclopedia& other) : title(other.title), year(other.year), personalities(other.personalities) {
        cout << "Вызван конструктор копирования Encyclopedia" << endl;
    }

    // Деструктор
    ~Encyclopedia() {
        cout << "Вызван деструктор Encyclopedia для " << title << endl;
    }

    // Метод для создания и добавления Personality
    void addPersonalityParams(string n, string o, string d) {
        Personality p(n, o, d);
        personalities.push_back(p);
    }

    // Метод для создания копий Personality
    void addCopies(const Personality& p, int count) {
        for (int i = 0; i < count; i++) {
            personalities.push_back(p);
        }
    }

    void display() const {
        cout << "Энциклопедия: " << title << endl;
        cout << "Год издания: " << year << endl;
        cout << "Содержит следующие личности:" << endl;
        cout << "=====================" << endl;
        
        for (const auto& p : personalities) {
            p.display();
        }
    }
};

int main() {
    // Демонстрация конструкторов Personality
    cout << "=== Создание объектов Personality ===" << endl;
    Personality p1; // без параметров
    Personality p2("Альберт Эйнштейн", "Физик", "Создатель теории относительности"); // с параметрами
    Personality p3(p2); // копирования

    // Демонстрация конструкторов Encyclopedia
    cout << "\n=== Создание объектов Encyclopedia ===" << endl;
    Encyclopedia e1; // без параметров
    Encyclopedia e2("Великие ученые", 2024); // с параметрами
    Encyclopedia e3(e2); // копирования

    // Использование новых методов
    cout << "\n=== Использование методов добавления ===" << endl;
    e2.addPersonalityParams("Никола Тесла", "Изобретатель", "Работы по электричеству");
    e2.addCopies(p2, 2); // Добавим 2 копии Эйнштейна

    // Вывод информации
    cout << "\n=== Вывод информации ===" << endl;
    e2.display();

    cout << "\n=== Завершение программы ===" << endl;
    return 0;
}