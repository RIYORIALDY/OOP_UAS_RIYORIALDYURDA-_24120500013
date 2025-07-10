#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Kelas dasar
class Person {
protected:
    string name;
    int age;
public:
    Person(string name, int age) : name(name), age(age) {}
    virtual void display() const = 0;
};

// Kelas turunan
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

// Tim FC Cakrawala Muda
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

    fc.addCoach(make_shared<Coach>("Pak Budi", 45, "Head Coach"));
    fc.addCoach(make_shared<Coach>("Pak Dedi", 39, "Assistant Coach"));

    fc.addPlayer(make_shared<Player>("Andi", 20, 10, "Striker"));
    fc.addPlayer(make_shared<Player>("Budi", 21, 7, "Midfielder"));
    fc.addPlayer(make_shared<Player>("Cahya", 22, 1, "Goalkeeper"));
    // Tambahkan hingga 15 pemain jika diperlukan

    fc.showTeam();
    return 0;
}
