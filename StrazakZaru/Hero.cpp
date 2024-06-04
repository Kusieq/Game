#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <limits>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include "Hero.h"
#include "HelpingMethods.h"

Firefighter::Firefighter(int initialScore) : score(initialScore) {}

// obrazenia od przedmiotow
int dmgByItem(int id)
{
    int dmg = 0;
    switch (id)
    {
    case 1: // gasnica
        dmg = 30;
        break;
    case 2: // bomba wodna
        dmg = 45;
        break;
    case 3: // wiadro
        dmg = 0;
        break;
    case 4: // dmuchawa
        dmg = 10;
        break;
    case 5: // waz gasniczy
        dmg = 75;
        break;
    }
    return dmg;
}
// tworzenie struktury umiejetnosci
void addAbilityToBackpack(Firefighter& firefighter, const std::string& name, const std::string& description, int id)
{
    Abilities abili = { name, description, id, true };
    firefighter.abilities.push_back(abili); // przypisywanie do listy
}
// tworzenie struktury przedmiotu
void addItemToBackpack(Firefighter& firefighter, const std::string& name, const std::string& description, int id)
{
    BackpackItem newItem = { name, description, id };
    firefighter.backpack.push_back(newItem);// przypisywanie do listy
}
// dodawanie umiejetnosci do postaci
void addAbilities(int item, Firefighter& firefighter)
{
    switch (item) {
    case 1:
        addAbilityToBackpack(firefighter, "Odstraszanie smokow", "Odstraszenie smoka podczas gaszenia pozaru", 0);
        break;
    case 2:
        addAbilityToBackpack(firefighter, "Przyzywanie deszczu", "Przez cala walke z pozarem deszcz bedzie gasil 10 pkn pozaru", 1);
        break;
    case 3:
        addAbilityToBackpack(firefighter, "Wzmocnienie gaszenia", "Wzmacnia kazdy atak o 10 pkn.", 2);
        break;
    }
}
// dodawanie umiejetnosci do plecaka
void addItems(int item, Firefighter& firefighter)
{
    switch (item) {
    case 1:
        addItemToBackpack(firefighter, "Gasnica", "Uzyteczna do wszytskich pozarow", 1);
        break;
    case 2:
        addItemToBackpack(firefighter, "Bomba wodna", "Specjalna bomba do specjalnego ognia", 2);
        break;
    case 3:
        addItemToBackpack(firefighter, "Wiadro", "Gasi pozar w 50%", 3);
        break;
    case 4:
        addItemToBackpack(firefighter, "Dmuchawa do wody", "Zadaje male obrazenia ale nastepny atak jest mocniejszy", 4);
        break;
    case 5:
        addItemToBackpack(firefighter, "Waz gasniczy", "Uzyteczny do wszytskich pozarow", 5);
        break;
    }

}
// uzywanie danego przedmiotu
double usingItem(Firefighter& firefighter, double fire, bool crit, bool lastStage, bool& blow)
{
    std::string items;
    int num = 0;

    // wyswietlenie itemow
    for (const auto& item : firefighter.backpack) {
        num += 1;
        items += std::to_string(num) + ". " + item.name + ": " + item.description + "\n";
    }

    items += "\nWybor: ";
    std::cout << items;  // wyswietlenie tekstu

    std::string userInput;
    int choice;
    // wybranie itemu oraz przypisanie danego dmg przez przedmiot
    while (true) {
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choice && (choice >= 1 && choice <= num) && ss.eof()) {

            BackpackItem selectedItem = firefighter.backpack[choice - 1]; // wybranie danego przedmiotu
            displayTextSlowly(std::to_string(selectedItem.id), 5);
            firefighter.backpack.erase(firefighter.backpack.begin() + (choice - 1)); // usuniecie przedmiotu z plecaka
            double dmg = dmgByItem(selectedItem.id); // ustawienie dmg przez dany przedmiot

            // dla bomby wodnej
            if (lastStage && selectedItem.id == 2)
            {
                dmg *= 2;
            }

            // krytyczne uderzenie
            if (crit)
            {
                dmg *= 1.5;
            }

            // uzycie dmuchawy jako drugi atak krytyczny
            if (blow == true)
            {
                blow = false;
                dmg *= 1.5;
            }

            // uzycie wiadra
            if (selectedItem.id == 3)
            {
                fire /= 2;
            }

            //  uzycie dmuchawy
            if (selectedItem.id == 4)
            {
                blow = true;
                dmg = 10;
            }
            return fire - dmg; // wyrzuca nam ogien po redukcji obrazen
        }
        else {
            clearScreen(); // Czysczenie ekranu
            std::cout << items;
        }

    }
}
// uzywanie danej umiejetnosci
int usingAbility(Firefighter& firefighter)
{
    std::string items;
    int num = 0;
    std::vector<Abilities> abilitiesCopy; // utworzenie kopi listy z aktywnymi umiejetnosciami

    // pokazanie aktywnych umiejetnosci
    for (const auto& item : firefighter.abilities) {
        if (item.active == true)
        {
            abilitiesCopy.push_back(item);
            num += 1;
            items += std::to_string(num) + ". " + item.name + ": " + item.description + "\n";
        }
    }

    // gdy nie ma aktywnych to wyrzuca nam -1
    if (num == 0)
    {
        return -1;
    }

    items += "\nWybor: ";
    std::cout << items; // wyswietlenie tekstu

    while (true)
    {
        // wybor z listy
        int choice;
        std::string userInput;
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choice && (choice >= 1 && choice <= num) && ss.eof()) {
            int out = choice - 1;
            return abilitiesCopy[out].id;
        }
        else {
            clearScreen(); // Czyszczenie ekrani
            std::cout << items;
        }
    }
}
// silnik walki
void fightEngine(double hpFire, int stage, Firefighter& firefighter)
{
    // sprawdzenie czy nie jest to final
    bool lastStage = false;
    if (stage == 4)
    {
        lastStage = true;
    }

    // podstawowe statystyki i zmienne
    double fire = hpFire;
    std::string yt = "Twoja tura\n\n";
    std::string at = "Tura przeciwnika";
    bool lose = false;
    bool blow = false;
    bool drakeActive = true;
    bool rainActive = false;
    int specialFinal = 1;

    // silnik walki
    while (true)
    {
        // podstawowe statystyki i zmienne
        fire = round(fire * 100) / 100;
        bool critActive = false;
        int ability = -2;
        bool returnToMenu = false;
        std::string message = "";
        double dm;
        std::ostringstream oss;

        oss << std::fixed << std::setprecision(2) << fire; // uciecie zer od pozaru
        std::string menu = yt + "\nPozar: " + oss.str() + " Pkn\n\n" + fightMenu(); // opis tury uzytkownika, pkn pozazru oraz menu
        displayTextSlowly(menu, 5); // wyswietlenie tekstu
        int choice = choice3Options(menu); // metoda do wybrania opcji jednej z 3


        // tura uzytkownika
        switch (choice)
        {
        case 1:
            // uzycie przemdiotu
            if (firefighter.backpack.empty()) {
                message = "PUSTY EKWIPUNEK";
                returnToMenu = true;
                break;
            }
            else if (drakeActive && stage == 2)
            {
                dm = usingItem(firefighter, fire, critActive, lastStage, blow);  // ustawienie danego dmg dla drugiej walki z pozarem
                fire -= ((fire - dm) / 2);
            }
            else
            {
                fire = usingItem(firefighter, fire, critActive, lastStage, blow); // ustawienie punktow zycia dla pozaru
            }
            critActive = false;

            break;
        case 2:
            // uzycie umiejetnosci

            if (firefighter.abilities.empty()) {
                message = "BRAK UMIEJETNOSCI";
                returnToMenu = true;
                break;
            }

            ability = usingAbility(firefighter); // uzyciue danej umiejetnosci
            break;
        case 3:
            lose = true;
            break;
        }

        if (ability == -1)
        {
            continue;
        }


        // uzywanie umiejetnosci
        if (ability >= 0)
        {
            firefighter.abilities[ability].active = false; // ustawienie umiejetnosci na nieaktywna 

            switch (ability)
            {
            case 0:
                drakeActive = false;
                break;
            case 1:
                rainActive = true;
                break;
            case 2:
                critActive = true;
                break;
            default:
                break;
            }
        }

        // powrot do poczatku tury
        if (returnToMenu)
        {
            displayTextSlowly(message, 5); // Wyswietlenie tekstu
            waitForEnter();// Czekaj na naciœniêcie Enter
            clearScreen();// Wyczyszczenie ekrany
            continue;
        }

        // uzywanie umiejetnosci jesli jest aktywna
        if (rainActive)
        {
            fire -= 10;
        }

        // sprawdzanie parametrow
        if (lose)
        {
            firefighter.score += hpFire - fire;
            break;
        }
        else if (fire <= 0)
        {
            firefighter.score += hpFire;
            break;
        }

        fire = round(fire * 100) / 100;

        // tura przeciwnika
        clearScreen(); // Wyczyszczenie ekrany
        std::cout << at;
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // zatrzymanie ekranu



        // statystyki dla danej walki oraz specjalne utrudnienia (stage - > dany pozar [NIE LVL])
        if (stage == 1)
        {
            // regenracja ognia
            if (fire + 5 >= 100)
            {
                fire = 100;
            }
            else
            {
                fire += 5;
            }

            // regenracja ognia
            std::this_thread::sleep_for(std::chrono::milliseconds(200));// zatrzymanie ekranu 
            if (fire + 15 >= 100 && drakeActive)
            {
                fire = 100;
                std::cout << "\n\nSmok zregenrowal pozar!";
            }
            else if (fire + 15 <= 100 && drakeActive)
            {
                fire += 15;
                std::cout << "\n\nSmok zregenrowal pozar!";
            }
        }
        else if (stage == 2)
        {
            if (fire + 8 >= 250)
            {
                fire = 250;

            }
            else
            {
                fire += 8;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));// zatrzymanie ekranu 
            if (drakeActive)
            {
                std::cout << "\n\nSmok zmniejszyl twoje obrazenia!";
            }
        }
        else if (stage == 3)
        {
            if (fire + 8 >= 450)
            {
                fire = 450;
            }
            else
            {
                fire += 8;
            }
        }
        else if (stage == 4)
        {
            if (fire + 10 >= 700)
            {
                fire = 700;
            }
            else
            {
                fire += 10;
            }

            // regenracja ognia
            std::this_thread::sleep_for(std::chrono::milliseconds(50));// zatrzymanie ekranu 
            if (fire + 30 >= 700 && drakeActive)
            {
                fire == 700;
                std::cout << "\n\nSmok szafirowy zregenrowal ogien!";
            }
            else if (fire + 30 <= 700 && drakeActive)
            {
                fire += 30;
                std::cout << "\n\nSmok szafirowy zregenrowal ogien!";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));// zatrzymanie ekranu 
            srand(time(0));
            int randomNumber = rand() % 10;
            if ((randomNumber >= 0 || randomNumber <= 1) && specialFinal != 0)
            {
                specialFinal -= 1;
                fire = hpFire;
                std::cout << "\n\nSmok szmaragdowy rozpalil pozar na nowo";
            }

        }


        std::cout << "\n\nPozar zregenrowal sie!";
        std::ostringstream osss;
        osss << std::fixed << std::setprecision(2) << fire;
        std::cout << "\n\nPozar: " + osss.str() + "pkn";
        waitForEnter();// Czekaj na naciœniêcie Enter
        clearScreen();// Wyczyszczenie ekrany
    }
    clearScreen();// Wyczyszczenie ekrany


    // sprawdzenie danego rezultatu
    if (lose && stage != 4)
    {
        // opis rezultatu bitwy
        std::string info = "Niestety, nie udalo ci sie pokonac pozaru.\n"
            "Ale nie martw sie, twoja przygoda sie konczy sie na przegranej walce.\n"
            "Przed toba jeszcze kilka pojedynkow.";
        displayTextSlowly(info, 5);// Wyswietlenie tekstu
    }
    else if (lose && stage == 4)
    {
        std::string info = "Niestety, nie udalo ci sie pokonac pozaru.\n";
    }
    else
    {
        // opis rezultatu bitwy
        std::string info = "BRAWO!, udalo ci sie pokonac pozar.";
        displayTextSlowly(info, 5); // Wyswietlenie tekstu
    }
    waitForEnter();// Czekaj na naciœniêcie Enter
    clearScreen();// Wyczyszczenie ekrany

}