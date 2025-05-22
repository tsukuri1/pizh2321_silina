#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <windows.h> // Для SetConsoleOutputCP

using namespace std;

// Функция для установки русской кодировки в консоли
void setRussianEncoding() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
}

class Personality {
protected:
    string name;
    string occupation;
public:
    Personality(const string& n = "Неизвестно", const string& o = "Неизвестно")
        : name(n), occupation(o) {}

    friend ostream& operator<<(ostream& os, const Personality& p);
    friend istream& operator>>(istream& is, Personality& p);

    virtual void showInfo() const = 0;
    virtual void saveToFile(ofstream& file) const = 0;
    virtual void loadFromFile(ifstream& file) = 0;
    virtual ~Personality() = default;
};

ostream& operator<<(ostream& os, const Personality& p) {
    os << "Имя: " << p.name << "\nРод деятельности: " << p.occupation;
    return os;
}

istream& operator>>(istream& is, Personality& p) {
    cout << "Введите имя: ";
    getline(is, p.name);
    cout << "Введите род деятельности: ";
    getline(is, p.occupation);
    return is;
}

class Scientist : public Personality {
    string discovery;
public:
    Scientist(const string& n = "Неизвестно", const string& o = "Неизвестно", 
              const string& d = "Неизвестно")
        : Personality(n, o), discovery(d) {}

    void showInfo() const override {
        cout << *this << "\nОткрытие: " << discovery << endl;
    }

    void saveToFile(ofstream& file) const override {
        file << "Scientist\n" << name << "\n" << occupation << "\n" << discovery << "\n";
    }

    void loadFromFile(ifstream& file) override {
        getline(file, name);
        getline(file, occupation);
        getline(file, discovery);
    }
};

class Encyclopedia {
    vector<unique_ptr<Personality>> people;
public:
    void addPerson(unique_ptr<Personality> p) {
        people.push_back(move(p));
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) throw runtime_error("Не удалось открыть файл для записи");
        
        for (const auto& p : people) {
            p->saveToFile(file);
        }
        cout << "Данные успешно сохранены в файл: " << filename << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) throw runtime_error("Не удалось открыть файл для чтения");
        
        people.clear();
        string type;
        while (getline(file, type)) {
            unique_ptr<Personality> p;
            if (type == "Scientist") {
                p = make_unique<Scientist>();
                p->loadFromFile(file);
                people.push_back(move(p));
            }
            // Добавьте обработку других типов при необходимости
        }
        cout << "Данные успешно загружены из файла: " << filename << endl;
    }

    void showAll() const {
        if (people.empty()) {
            cout << "Энциклопедия пуста.\n";
            return;
        }
        
        cout << "\nСодержимое энциклопедии:\n";
        for (size_t i = 0; i < people.size(); ++i) {
            cout << "[" << i + 1 << "] ";
            people[i]->showInfo();
            cout << "--------------------\n";
        }
    }
};

void displayMenu() {
    cout << "\nМеню:\n"
         << "1. Добавить ученого\n"
         << "2. Показать все записи\n"
         << "3. Сохранить в файл\n"
         << "4. Загрузить из файла\n"
         << "5. Выход\n"
         << "Выберите действие: ";
}

int main() {
    setRussianEncoding();
    Encyclopedia book;
    int choice = 0;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Очищаем буфер после ввода числа
        
        try {
            switch (choice) {
                case 1: {
                    unique_ptr<Personality> p = make_unique<Scientist>();
                    cin >> *p;
                    book.addPerson(move(p));
                    cout << "Запись добавлена.\n";
                    break;
                }
                case 2:
                    book.showAll();
                    break;
                case 3:
                    book.saveToFile("encyclopedia.txt");
                    break;
                case 4:
                    book.loadFromFile("encyclopedia.txt");
                    break;
                case 5:
                    cout << "Выход из программы.\n";
                    return 0;
                default:
                    cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }
}