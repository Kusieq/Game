#pragma once

// Struktura dla przedmiotowo
struct BackpackItem {
    std::string name;
    std::string description;
    int id;
};

// Struktura dla umiejetnosci
struct Abilities {
    std::string name;
    std::string description;
    int id;
    bool active;
};

// klasa strazaka
class Firefighter
{
public:
    int score;
    std::vector<BackpackItem> backpack;
    std::vector<Abilities> abilities;

    Firefighter(int initialScore);
};


// obrazenia od przedmiotow
int dmgByItem(int id);
// tworzenie struktury umiejetnosci
void addAbilityToBackpack(Firefighter& firefighter, const std::string& name, const std::string& description, int id);
// tworzenie struktury przedmiotu
void addItemToBackpack(Firefighter& firefighter, const std::string& name, const std::string& description, int id);
// dodawanie umiejetnosci do postaci
void addAbilities(int item, Firefighter& firefighter);
// dodawanie umiejetnosci do plecaka
void addItems(int item, Firefighter& firefighter);
// uzywanie danego przedmiotu
double usingItem(Firefighter& firefighter, double fire, bool crit, bool lastStage, bool& blow);
// uzywanie danej umiejetnosci
int usingAbility(Firefighter& firefighter);
// silnik walki
void fightEngine(double hpFire, int stage, Firefighter& firefighter);