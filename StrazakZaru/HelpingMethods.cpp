#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include "HelpingMethods.h"


// wyswietlenie menu w glownym menu
void displayMenu(int score, std::string place) {
    std::cout << "Wynik: " + std::to_string(score) + "\n\n\n";
    std::cout << "1. Podroz do " + place + "\n";
    std::cout << "2. Mapa\n";
    std::cout << "3. Plecak\n";
    std::cout << "4. Umiejetnosci\n";
    std::cout << "5. Zapisz\n";
    std::cout << "6. Cel\n";
    std::cout << "7. Wyjdz\n\n";
}
// Wyswietleniu menu w walce
std::string fightMenu()
{
    return "1. Ekwipunek\n2. Umiejetnosc\n3. Poddaj sie\nWybor: ";
}
// Zamienianie slowa na male litery
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
// czyszczenie konsoli
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// Czekanie na enter
void waitForEnter() {
    std::cout << "\n\nNacisnij Enter, aby kontynuowac...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// Czekanie na podwojny enter
void waitForEnterSec()
{
    std::cout << "\n\nNacisnij Enter, aby kontynuowac...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// wyswietlanie tekstu po malu
void displayTextSlowly(const std::string& text, int delay_ms)
{
    for (char c : text)
    {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}
// Wybieranie miedzy dwiema opcjami
int choice2Options(std::string text)
{
    std::string userInput;
    int choice;

    // wybranie 1 lub 2
    while (true) {
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choice && (choice == 1 || choice == 2) && ss.eof()) {
            clearScreen();   // Wyczyœæ ekran
            break;
        }
        else {
            clearScreen(); // Wyczyœæ ekran
            std::cout << text;
        }
    }
    return choice;
}
// Wybieranie miedzy trzema opcjami
int choice3Options(std::string text)
{
    std::string userInput;
    int choice;

    // wybranie 1,lub 2, lub 3,
    while (true) {
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choice && (choice == 1 || choice == 2 || choice == 3) && ss.eof()) {
            clearScreen(); // Wyczyœæ ekran
            break;
        }
        else {
            clearScreen(); // Wyczyœæ ekran
            std::cout << text;
        }
    }
    return choice;
}
// Opis celu gry
void target()
{
    // opis celu gry
    std::string gameGoal = "Celem gry jest zbieranie przedmiotow i umiejetnosci przydatnych w walce ze "
        "smokami oraz pomocy\nroznym ludziom. Gra sklada sie z pieciu roznych lokacji, z ktorych kazda ma swoje wlasny\n"
        "lore oraz zadania do wykonania. Podczas rozgrywki gracz moze napotkac rozne misje poboczne oraz rozmawiac z NPC,\n"
        "co moze wplynac na fabule oraz rozwoj postaci. Po przejsciu wszystkich pieciu lokalizacji gracz zmierzy\n"
        "sie z finalnym bossem, Wladca Zaru, aby przywrocic pokoj w Pyroklas.";
    std::cout << gameGoal;
    waitForEnterSec();  // Czekaj na naciœniêcie Enter
    clearScreen();   // Wyczyœæ ekran
}
// Opis miejsc w ktorych sie znajdzie uzytkownik
void showMap()
{
    // opis mapy
    std::string map =
        "----------------------------------------\n"
        "1. Centralny Park\n"
        "----------------------------------------\n"
        "Zielone serce miasta, gdzie mieszkancy odpoczywaja od zgielku codziennosci.\n"
        "Znajdziesz tu liczne sciezki spacerowe, plac zabaw oraz malownicze stawy.\n"
        "----------------------------------------\n"
        "2. Muzeum Techniki\n"
        "----------------------------------------\n"
        "Fascynujace miejsce, w ktorym mozna zobaczyc eksponaty zwiazane z historia technologii,\n"
        "od starozytnych wynalazkow po wspolczesne osiagniecia nauki.\n"
        "----------------------------------------\n"
        "3. Biblioteka Miejska\n"
        "----------------------------------------\n"
        "Oaza wiedzy i spokoju. W jej zbiorach znajdziesz zarowno starodruki, jak i najnowsze bestsellery.\n"
        "Idealne miejsce na nauke i refleksje.\n"
        "----------------------------------------\n"
        "4. Stare Miasto\n"
        "----------------------------------------\n"
        "Historyczna czesc miasta pelna urokliwych uliczek, zabytkowych kamienic i klimatycznych kafejek.\n"
        "To tutaj mozna poczuc ducha przeszlosci.\n"
        "----------------------------------------\n"
        "5. Cytadela\n"
        "----------------------------------------\n"
        "Potezna twierdza, ktora od wiekow strzeze miasta przed niebezpieczenstwami zewnetrznymi. "
        "Tutejsze mury kryja w sobie historie bohaterskich obron i odwagi.\n"
        "----------------------------------------\n"
        "6. Final (Katedra)\n"
        "----------------------------------------\n"
        "Monumentalna katedra, symbol miasta. Jej wnetrza kryja wspaniale witraze i piekne rzezby,\n"
        "a atmosfera tego miejsca jest przepelniona spokojem i majestatem.\n"
        "----------------------------------------\n";
    std::cout << map;
    waitForEnterSec(); // czekanie na enter
}
