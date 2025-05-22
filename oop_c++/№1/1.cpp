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
    Personality() : name(""), occupation(""), description("") {}
    Personality(string n, string o) : name(n), occupation(o), description("Нет описания") {}
    Personality(string n, string o, string d) : name(n), occupation(o), description(d) {}

    string getName() const { return name; }
    string getOccupation() const { return occupation; }
    string getDescription() const { return description; }

    void setName(string n) { name = n; }
    void setOccupation(string o) { occupation = o; }
    void setDescription(string d) { description = d; }

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
    Encyclopedia(string t, int y) : title(t), year(y) {}

    string getTitle() const { return title; }
    int getYear() const { return year; }

    void setTitle(string t) { title = t; }
    void setYear(int y) { year = y; }

    void addPersonality(const Personality& p) {
        personalities.push_back(p);
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
    Encyclopedia historyEncyclopedia("История в лицах", 2023);

    Personality p1("Александр Македонский", "Полководец", 
                   "Царь Македонии, создатель одной из крупнейших империй древности.");
    
    Personality p2("Леонардо да Винчи", "Художник и изобретатель");
    p2.setDescription("Итальянский художник, учёный, изобретатель");

    Personality p3;
    p3.setName("Исаак Ньютон");
    p3.setOccupation("Физик, математик");
    p3.setDescription("Создатель классической физики");

    historyEncyclopedia.addPersonality(p1);
    historyEncyclopedia.addPersonality(p2);
    historyEncyclopedia.addPersonality(p3);

    historyEncyclopedia.display();

    return 0;
}