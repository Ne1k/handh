#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Creature {
protected:
    int attack;
    int defense;
    int health;

public:
    Creature(int attack, int defense, int health) : attack(attack), defense(defense), health(health) {
        srand(static_cast<unsigned>(time(0))); // Для генерации случайных чисел
    }

    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int damage) {
        if (damage > 0) {
            health -= damage;
            if (health < 0) {
                health = 0;
            }
        }
    }

    int getAttack() const {
        return attack;
    }

    int getDefense() const {
        return defense;
    }

    int getHealth() const {
        return health;
    }
};

class Monster; 

class Player : public Creature {
private:
    int minDamage;
    int maxDamage;
    int healCount;

public:
    Player(int attack, int defense, int health, int minDamage, int maxDamage)
        : Creature(attack, defense, health), minDamage(minDamage), maxDamage(maxDamage), healCount(0) {}

    int attackCreature(Creature& target) {
        int attackModifier = attack - target.getDefense() + 1;
        if (attackModifier < 1) {
            attackModifier = 1;
        }

        int damage = 0;
        for (int i = 0; i < attackModifier; ++i) {
            int roll = rand() % 6 + 1;
            if (roll >= 5) {
                int damageAmount = rand() % (maxDamage - minDamage + 1) + minDamage;
                target.takeDamage(damageAmount);
                damage += damageAmount;
            }
        }

        if (damage > 0) {
            cout << "Игрок нанес " << damage << " урона." << endl;
        }
        else {
            cout << "Игрок промахнулся в атаке." << endl;
        }

        return damage;
    }

    void heal() {
        if (health > 0 && healCount < 4) {
            int maxHeal = 50 - health;
            int healAmount = rand() % (maxHeal + 1); 
            if (health + healAmount > 50) { 
                healAmount = 50 - health; 
            }
            health += healAmount;
            cout << "Игрок исцелил себя на " << healAmount << " единиц здоровья." << endl;
            healCount++;
        }
        else {
            cout << "Игрок не может исцелиться." << endl;
        }
    }
};

class Monster : public Creature {
private:
    int minDamage;
    int maxDamage;

public:
    Monster(int attack, int defense, int health, int minDamage, int maxDamage)
        : Creature(attack, defense, health), minDamage(minDamage), maxDamage(maxDamage) {}

    int attackPlayer(Player& player) {
        int attackModifier = attack - player.getDefense() + 1;
        if (attackModifier < 1) {
            attackModifier = 1;
        }

        int damage = 0;
        for (int i = 0; i < attackModifier; ++i) {
            int roll = rand() % 6 + 1;
            if (roll >= 5) {
                int damageAmount = rand() % (maxDamage - minDamage + 1) + minDamage;
                player.takeDamage(damageAmount);
                damage += damageAmount;
            }
        }

        if (damage > 0) {
            cout << "Монстр нанес " << damage << " урона игроку." << endl;
        }
        else {
            cout << "Монстр промахнулся в атаке." << endl;
        }

        return damage;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Player player(8, 3, 50, 1, 6);
    Monster monster(8, 3, 50, 1, 6);

    cout << "Здоровье игрока: " << player.getHealth() << endl;
    cout << "Здоровье монстра: " << monster.getHealth() << endl;

    while (player.isAlive() && monster.isAlive()) {
        player.attackCreature(monster);
        monster.attackPlayer(player);
        if (player.isAlive()) {
            player.heal();
        }

        cout << "Здоровье игрока: " << player.getHealth() << endl;
        cout << "Здоровье монстра: " << monster.getHealth() << endl;
    }

    if (player.isAlive()) {
        cout << "Игрок победил!" << endl;
    }
    else {
        cout << "Монстр победил!" << endl;
    }

    return 0;
}
