#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string name, int age) : name(name), age(age) {}
    virtual void display() const = 0;
};

class Coach : public Person {
private:
    string role;
public:
    Coach(string name, int age, string role) : Person(name, age), role(role) {}
    void display() const override {
        cout << role << " - " << name << ", umur: " << age << endl;
    }
};

class Player : public Person {
private:
    int number;
    string position;
public:
    Player(string name, int age, int number, string position)
        : Person(name, age), number(number), position(position) {}
    void display() const override {
        cout << "Player #" << number << " - " << name << ", Posisi: " << position
             << ", umur: " << age << endl;
    }
};

// Factory Method Pattern
class PersonFactory {
public:
    static shared_ptr<Person> createCoach(string name, int age, string role) {
        return make_shared<Coach>(name, age, role);
    }

    static shared_ptr<Person> createPlayer(string name, int age, int number, string position) {
        return make_shared<Player>(name, age, number, position);
    }
};

class Team {
private:
    string teamName;
    vector<shared_ptr<Coach>> coaches;
    vector<shared_ptr<Player>> players;
public:
    Team(string teamName) : teamName(teamName) {}

    void addCoach(shared_ptr<Coach> coach) {
        coaches.push_back(coach);
    }

    void addPlayer(shared_ptr<Player> player) {
        if (players.size() < 15)
            players.push_back(player);
        else
            cout << "Sudah ada 15 pemain!" << endl;
    }

    void showTeam() const {
        cout << "== " << teamName << " ==" << endl;
        cout << "--- Coaches ---" << endl;
        for (auto& c : coaches) c->display();
        cout << "--- Players ---" << endl;
        for (auto& p : players) p->display();
    }
};

int main() {
    Team fc("FC Cakrawala Muda");

    fc.addCoach(dynamic_pointer_cast<Coach>(PersonFactory::createCoach("Pak Budi", 45, "Head Coach")));
    fc.addCoach(dynamic_pointer_cast<Coach>(PersonFactory::createCoach("Pak Dedi", 39, "Assistant Coach")));

    fc.addPlayer(dynamic_pointer_cast<Player>(PersonFactory::createPlayer("Andi", 20, 10, "Striker")));
    fc.addPlayer(dynamic_pointer_cast<Player>(PersonFactory::createPlayer("Budi", 21, 7, "Midfielder")));
    fc.addPlayer(dynamic_pointer_cast<Player>(PersonFactory::createPlayer("Cahya", 22, 1, "Goalkeeper")));

    fc.showTeam();
    return 0;
}
