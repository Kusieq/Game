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

//Struktura dla przedmiotu
struct BackpackItem {
    std::string name;
    std::string description;
    int id;
};
//Struktura dla umiejetnosci
struct Abilities {
    std::string name;
    std::string description;
    int id;
    bool active;
};
// klasa strazak
class Firefighter
{
public:
    int score;
    std::vector<BackpackItem> backpack;
    std::vector<Abilities> abilities;

    Firefighter(int initialScore) : score(initialScore) {}

};


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
void displayTextSlowly(const std::string& text, int delay_ms = 7)
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
            clearScreen();   // Wyczyść ekran
            break;
        }
        else {
            clearScreen(); // Wyczyść ekran
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
            clearScreen(); // Wyczyść ekran
            break;
        }
        else {
            clearScreen(); // Wyczyść ekran
            std::cout << text;
        }
    }
    return choice;
}


// tworzenie struktury umiejetnosci
void addAbilityToBackpack(Firefighter& firefighter, const std::string& name, const std::string& description, int id)
{
    Abilities abili = { name, description, id, true};
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
        addItemToBackpack(firefighter, "Gasnica", "Uzyteczna do wszytskich pozarow",1);
        break;
    case 2:
        addItemToBackpack(firefighter, "Bomba wodna", "Specjalna bomba do specjalnego ognia",2);
        break;
    case 3:
        addItemToBackpack(firefighter, "Wiadro", "Gasi pozar w 50%",3);
        break;
    case 4:
        addItemToBackpack(firefighter, "Dmuchawa do wody", "Zadaje male obrazenia ale nastepny atak jest mocniejszy",4);
        break;
    case 5:
        addItemToBackpack(firefighter, "Waz gasniczy", "Uzyteczny do wszytskich pozarow",5);
        break;
    }
    
}


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
            displayTextSlowly(std::to_string(selectedItem.id));
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
                dmg*=1.5; 
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
        displayTextSlowly(menu); // wyswietlenie tekstu
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
            displayTextSlowly(message); // Wyswietlenie tekstu
            waitForEnter();// Czekaj na naciśnięcie Enter
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
        waitForEnter();// Czekaj na naciśnięcie Enter
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
        displayTextSlowly(info);// Wyswietlenie tekstu
    }
    else if (lose && stage == 4)
    {
        std::string info = "Niestety, nie udalo ci sie pokonac pozaru.\n";
    }
    else
    {
        // opis rezultatu bitwy
        std::string info = "BRAWO!, udalo ci sie pokonac pozar.";
        displayTextSlowly(info); // Wyswietlenie tekstu
    }
    waitForEnter();// Czekaj na naciśnięcie Enter
    clearScreen();// Wyczyszczenie ekrany

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
    waitForEnterSec();  // Czekaj na naciśnięcie Enter
    clearScreen();   // Wyczyść ekran
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



// Intro do gry
void intro()
{
    //opis
    std::string intro = "Witaj w Pyroklas, miescie, gdzie codziennosc miesza sie z groza. Smoki sa tu rzeczywistoscia,\n"
        "niosac ogien i zniszczenie. Jako nowy czlonek Brygady Skrzydla Ognia, stajesz do walki z\nplomieniami i chronisz mieszkancow.";

    displayTextSlowly(intro);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();   // Wyczyść ekran

    //opis
    intro = "Ostatnio ataki smokow staly sie zorganizowane i czestsze, jakby kierowane przez tajemniczego Wladce Zaru,\n"
        "legendarnym smoku ukrytym w wulkanicznych gorach. Twoim zadaniem jest nie tylko walczyc z ogniem, ale tez odkryc\n"
        "prawde stojaca za tym zagrozeniem.";

    displayTextSlowly(intro);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();   // Wyczyść ekran
}
// Pierwsze zadanie uzytkownika
int firstQuest(Firefighter& firefighter)
{
    // opis 
    std::string quest = "Po wytezonym dniu walki z pozarami w miescie Pyroklas, strazak z Brygady Skrzydla Ognia,\n"
        "wreszcie zyskuje chwile wytchnienia. Gdy wznosi wzrok ku niebu, wsrod zarzacych sie ruin,\n"
        "zauwaza trzy kleby dymu unoszace sie w oddali. W sercu tej desperackiej sytuacji musi\n"
        "podjac jedna z trzech decyzji, z ktorych kazda prowadzi do innego niebezpieczenstwa i wyzwania\n"
        "\n1.Opuszczony magazyn\n2.Sklad chemiczny\n3.Sklep z butami\nWybor: ";

    displayTextSlowly(quest);   // Wyswietlenie tekstu

    std::string item;
    std::string place;
    int choice = choice3Options(quest); // wybieranie miedzy 3 opcjami


    // przypisywanie ktora opcja zostala wybrana przez uzytkownika
    if (choice == 1) {
        place = "opuszczony magazyn";
        item = "+2 Gasnica";
    } 
    else if (choice == 2) {
        place = "sklad chemiczny";
        item = "+1 Bomba wodna\n+2 Gasnica ";
    }
    else if (choice == 3) {
        place = "sklep z butami";
        item = "+3 Gasnica";
    }

    //opis zadania
    quest = "Wyruszasz w kierunku " + place + ". Kiedy docierasz na miejsce, widzisz,ze " + place + " \n"
        "jest ogarniety mrokiem i spustoszeniem. Twoje strazackie instynkty podpowiadaja, ze moze byc \n"
        "ktos lub cos, co potrzebuje twojej pomocy. Podczas przeszukiwania odkrywasz ukryte drzwi prowadzace do podziemi.\n"
        "Wchodzac do podziemi, slyszysz zdlawiony glos wolajacy o pomoc. Kiedy docierasz do konca korytarza,\n"
        "dostrzegasz uwieziona osobe za drzwiami. Potrzebujesz specjalnego kodu na otworzenie drzwi.\n"
        "Na scianie widzisz napis: ";
    displayTextSlowly(quest);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();   // Wyczyść ekran

    // opis zadania
    quest = "Mam cztery cyfry. Moja pierwsza cyfra jest parzysta a druga jest taka sama jak pierwsza.\n"
        "Trzecia cyfra jest o 3 mniejsza niz druga cyfra a czwarta cyfra jest o 7 wieksza niz trzecia cyfra\n"
        "Jaka jestem liczba ?\n\nKod: ";
    displayTextSlowly(quest);

    // zgadywanie liczby jako kod
    int code = 4429; // kod
    std::string userInput;
    int choiceCode;
    while (true) {
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choiceCode && (code == choiceCode) && ss.eof()) {
            clearScreen(); // Wyczyść ekran
            break;
        }
        else {
            clearScreen();// Wyczyść ekran
            std::cout << quest;
        }
    }

    // opis wynku
    quest = "BRAWO! Odgadles kod i uwolniles uwieziona osobe.";
    displayTextSlowly(quest);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();   // Wyczyść ekran

    // opis dialogu
    std::string specItem = "\n\n" + item; // opis dodania nowego przedmiotu do ekwipunku
    std::string dial = "Osoba: Dziekuje ci za uratowanie mnie! Ale to, co odkrylem podczas mojej uwiezienia, jest przerazajace.\nWiem, kto stoi za tymi atakami smokow.\n\n"
    "Bohater: Kto to jest? Musimy go powstrzymac, zanim spowoduje wiecej zniszczen!\n\n"
    "Osoba: Ten, ktorego nazywaja 'Wladca Zaru'. Jest to legendarny smok, ktory kieruje atakami smokow na miasto."
    "\nAby go powstrzymac, musisz ugasic 5 najblizszych pozarow i wykonac pewne poboczne misje,\nktore pomoga ci w dotarciu do niego.\n\n"
    "Bohater: Zrobie wszystko, co w mojej mocy, aby przywrocic spokoj w Pyroklas. Dziekuje za te informacje.\n\n"
    "Osoba: W nagrode za uratowania mnie daje ci specjalne przedmioty. Napewno ci sie przyda w przyszlosci!\n" + specItem;
    displayTextSlowly(dial); // wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();   // Wyczyść ekran
    firefighter.score += 10;
    return choice;
}

// Level - Centralny park oraz losowe eventy
void centralParkEventItems(int randomEvent, Firefighter& firefighter)
{
    if (randomEvent == 2)
    {
        // opis eventu
        std::string event = "Podczas drogi do centralnego parku, nagle uslyszales dziwne glosy dochodzace zza drzew. "
            "\nBy sie tam dostac, bedziesz musial uzyc jednej z gasnic, ktore masz przy sobie. "
            "Czy chcesz to zrobic?\nTo moze byc kluczowy moment, wiec decyzja nalezy do Ciebie."
            "\n\n1. Tak\n2. Nie\nWybor: ";
        displayTextSlowly(event); // Wsywietlenie tekstu

        int choice = choice2Options(event); // wybranie czy chcesz isc dalej czy pomoc

        // wyjscie z zdarzenia losowego
        if (choice == 2)
        {
            return;
        }

        // iterowanie po liscie
        for (auto it = firefighter.backpack.begin(); it != firefighter.backpack.end(); ++it) {
            if (it->name == "Gasnica") {
                firefighter.backpack.erase(it);
                break; // Przerwij pętlę po znalezieniu i usunięciu przedmiotu
            }
        }

        clearScreen(); // wyczyszczenie ekranu

        // opis dialogu
        std::string dia = "Nieznajomy: Dziekuje ci za zgaszenie naszej drogi, nie moglismy sie stad wydostac.\n\n"
            "Bohater: Czy moge wiedziec, co was tu sprowadzilo?\n\n"
            "Nieznajomy: Nie, ale w zamian za pomoc ofiarujemy ci gasnice oraz bombe wodna, ktore moga okazac sie\nprzydatne w twojej podrozy.\n\n"
            "Bohater: Dziekuje za oferte. Przyjmuje ja z wdziecznoscia.\n\n\n-1 Gasnica\n+1 Gasnica\n+1 Bomba wodna";

        displayTextSlowly(dia); // Wyswietlenie tekstu
        addItems(1, firefighter); // dodanie gasnicy do listy
        addItems(2, firefighter); // dodanie bomby wodnej do listy
        waitForEnter(); // Czekanie na wcisniecie enteru
        firefighter.score += 20;
        
    }
    else
    {
        // opis eventu
        std::string event = "Podczas drogi do centralnego parku, nagle zauwazasz postac stojaca za drzewem, wpatrujaca sie w ciebie z daleka.\n"
            "Czy chcesz podejsc i porozmawiac z ta nieznajoma osoba?"
            "\n\n1. Tak\n2. Nie\nWybor: ";
        displayTextSlowly(event); // wyswietlenie tekstu

        int choice = choice2Options(event); // wybranie czy chcesz isc dalej czy porozmawiac z postacia

        if (choice == 2)
        {
            return;
        }

        //opis opcji do wybrania
        event = "1. Witaj, czy potrzebujesz pomocy?\n2. Witaj, kim jestes?\n3. Przestan sie na mnie gapic!\nWybor: ";
        displayTextSlowly(event); // wyswietlenie tekstu

        choice = choice3Options(event); // wybor miedzy 3 opcjami podanymi wyzej
        clearScreen(); // wyczyszczenie ekranu



        if (choice == 1) {
            
            // opis dialogu
            std::string dial = "Bohater: Witaj, czy potrzebujesz pomocy?\n\n"
                "Nieznajomy: Nie, nie potrzebuje pomocy. Przepraszam za problem.";
            displayTextSlowly(dial); // wyswietlenie tekstu
        }
        else if (choice == 2) {

            // opis dialogu
            std::string dial = "Bohater: Witaj, kim jestes?\n\n"
                "Nieznajomy: Jestem podrozynkiem poszukujacym zaginionych skarbow. A kim jestes ty ? \n\n"
                "Bohater: Jestem strazakiem zaru, probuje sie dostac do central parku. Czy masz moze jakies infomracje co sie tam stalo?\n\n"
                "Nieznajomy: Tak, niedawno przylecial tam jakis smok i uwiezil kilka osob na drzewie.\n\n"
                "Bohater: Bardzo dziekuje za informacje. Czy moglbys mi pomoc w dotarciu do centralnego parku?\n\n"
                "Nieznajomy: Niestety, mam inne sprawy do zalatwienia. Ale zycze Ci powodzenia.";
            displayTextSlowly(dial); // wyswietlenie tekstu
        }
        else if (choice == 3) {
            //opis dialogu
            std::string dial = "Bohater: Przestan sie na mnie gapic!\n\n"
                "Nieznajomy: Przepraszam, jesli Cie urazilem. Nie chcialem Cie zawracac glowy. Pozwol, ze sie oddale.";
            displayTextSlowly(dial); // wyswietlenie tekstu
        }
        waitForEnter(); // czekanie na wcisniecie enteru
        firefighter.score += 10;
    }

    clearScreen(); // wyczyszczenie ekranu
}
void centralPark(Firefighter& firefighter)
{
    // zapisanie 2 randomowych zdarzen
    int itRand = 2;

    //opis historii
    std::string hist = "Po uratowaniu ostatniej osoby, ktora ledwo zdolales wydostac zauwazasz ze po spalonym obszarze,\n"
        "dostrzegasz cos nietypowego. Wsrod resztek spalonego miejsca zauwazasz slady - slady,\n"
        "ktore wydaja sie nie byc spowodowane przez ogien. Sa to slady nietypowe, jakby pozostawione\n"
        "przez cos duzego i ciezkiego, cos, co nie przypomina zadnego znanego ci zwierzecia czy istoty.\n"
        "Te tajemnicze slady prowadza prosto do centralnego obszaru parku.\n"
        "Bez wahania i niezlomnie wyruszasz.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnterSec();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran


    // graficzne pokazanie drogi
    std::string text = "##################################";
    std::string road = "Droga - ";
    srand(time(0));

    // pokazanie graficznego przebiegu drogi oraz losowanie rawndomowych eventow
    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // zatrzymywanie drogi na 50 millisekund
        int randomNumber = rand() % 51; // losowanie liczby od 0 do 50

        if ((itRand == 1 || itRand == 2) && randomNumber >= 0 && randomNumber <= 4) // 
        {
            clearScreen();// Wyczyść ekran
            centralParkEventItems(itRand,firefighter); // metoda do randomowych zdarzen
            itRand -= 1;
        }
        clearScreen();// Wyczyść ekran
    }

    // opis historii
    hist = "Po dotarciu na miejsce, zauwazasz w oddali majestatycznego smoka, ktorego imie brzmi Aethraxis,\n"
        "wznoszacego sie nad starozytnymi ruinami. Jego potezne skrzydla rozwiniete ss w szerokim luku,\n"
        "a szpony odblaskujs w blasku slonca, przypominajac blyszczacy stal. Jego skora pokryta jest luskami\n"
        "o zlocisto-brazowym odcieniu, ktore blyszcza w promieniach slonca.\n";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // opis historii
    hist = "Po chwili majestatyczny smok unoszacy sie nad zrujnowanymi ruinami, nagle odlecial w kierunku Muzeum Techniki.\n"
        "W tym samym czasie ty bez chwili wahania pobiegles w kierunku drzewa,na ktorym byly uwiezione dwie osoby.\n"
        "Twoim zadaniem bedzie odgadniecie dobrego kata po ktorym wespniesz sie na drzewo.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // opis historii
    hist = "Znajdz kat, ktory jest rowny jednej trzeciej kata prostego,\npomnozonego przez 2, "
        "a nastepnie odjete od sumy 120 stopni.\n\nKat: ";
    displayTextSlowly(hist);   // Wyswietlenie tekstu


    // zgadywanie liczby jako kat
    int kat = 60; // podany kat
    std::string userInput1;
    int choiceCode;
    while (true) {
        std::getline(std::cin, userInput1);
        std::stringstream ss(userInput1);
        if (ss >> choiceCode && (kat == choiceCode) && ss.eof()) {
            clearScreen(); // Wyczysc ekran
            break;
        }
        else {
            clearScreen(); // Wyczysc ekran
            std::cout << hist;
        }
    }

    // opis zgadniecia kata
    hist = "BRAWO! odgadles wlasciwy kat. Uratowales dwie osoby przez smiercia.\n\n"
        "Gdy wchodziles na drzewo, natknales sie na bombe wodna, ktora nie zostala zdetonowana.\n"
        "Zdecydowales sie umiescic ja w swoim plecaku.\n";
    displayTextSlowly(hist); // wyswietleniu tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran
    addItems(2, firefighter); // dodanie bomby wodnej do plecaka
    firefighter.score += 60;

    // opis dialogu
    std::string dial = "Osoba: Dziekuje Ci za ratunek! Jestesmy bardzo wdzieczni.\n\n";
    std::string que = "1.Co sie stalo? \n2.Czy moge wam jakos pomoc?\nWybor: ";
    displayTextSlowly(dial + que);
    int choice = choice2Options(dial+que); // wybranie opcji pierwszej lub drugiej
    std::cout << dial;

    if (choice == 1)
    {
        // opis dialogu
        dial = "Bohater: Co sie stalo? \n\n"
            "Osoba: Nasza grupa byla scigana przez tego smoka. Jestesmy Ci "
            "niezmiernie wdzieczni za pomoc. W zamian za ratunek\nchcielibysmy Ci podarowac specjalna"
            "umiejetnosc do walki z smokami. Dajemy Ci umiejetnosc \"odstraszenie smoka\".\nJest "
            "ona tylko aktywna gdysmok Ci przeszkadza w ugaszeniu pozaru\n\n"
            "Bohater: Dziekuje za umiejetnosc. To dla mnie zaszczyt, ze moge posiadac taka umiejetnosc.\nBardzo ciesze sie, ze wszyscy sa bezpieczni.";
        displayTextSlowly(dial); // wyswietlenie tekstu
    }
    else
    {
        //opis dialogu
        dial = "Bohater: Czy moge Wam jakos pomoc?\n\n"
            "Osoba: Nie, dziekujemy. Jestesmy Wam "
            "niezmiernie wdzieczni za pomoc. W zamian za ratunek\nchcielibysmy Wam podarowac specjalna"
            "umiejetnosc do walki z smokami. Dajemy Wam umiejetnosc \"odstraszenie smoka\".\nJest "
            "ona aktywna tylko wtedy, gdy smok przeszkadza Wam w ugaszeniu pozaru\n\n"
            "Bohater: Dziekuje za umiejetnosc. To dla mnie zaszczyt, ze moge posiadac taka umiejetnosc.";
        displayTextSlowly(dial);    // wyswietlenie tekstu
    }

    std::string abi = "\n\n\n+1 Odstraszenie smoka"; 
    addAbilities(1, firefighter); // dodanie umiejetnosci do listy
    displayTextSlowly(abi); // wyswietlenie dodania umijejetnosci
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran
}

// Level - Muzeum  oraz losowe eventy
void museumOfTechnicEventItems(int randomEvent, Firefighter& firefighter)
{
    // opis randomowego zadania
    std::string quest = "Podczas podrozy w strone muzeum, przykulo Twoja uwage zgliszcza dawnego szpitala.\n"
        "Zatrzymujesz sie na chwile, by lepiej przyjrzec sie temu, co pozostalo z budynku. \nCzy "
        "chcesz przeszukac ten budynek?\n\n1. Tak\n2. Nie\nWybor: ";

    displayTextSlowly(quest); // Wsywietlenie tekstu
    int choice = choice2Options(quest); // wybranie jednej z dwoch opcji

    // wyjscie
    if (choice == 2)
    {
        return;
    }

    // graficzne pokazanie szukania
    std::string seak = "##############################";
    std::cout << "Szukanie - ";
    displayTextSlowly(seak); // Wsywietlenie tekstu
    clearScreen(); // Wyczysc ekran

    srand(time(0));
    int randomNumber = rand() % 51; // losowanie liczby od 0 do 50
    if (randomNumber <= 50 && randomNumber >= 25)
    {
        std::string info = "Niestety nic nie znalazles.";
        displayTextSlowly(info); // wyswietlenie tekstu
    }
    else
    {
        std::string info = "Znalazles dwie gasnice!\n\n\n+2 Gasnica";
        displayTextSlowly(info); // wyswieltnie tekstu
        addItems(1, firefighter); // dodanie gasnicy do listy
        addItems(1, firefighter);// dodanie gasnicy do listy
        firefighter.score += 10;
    }
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

}
void museumOfTechnic(Firefighter& firefighter)
{
    // zapisanie 1 randomowych zdarzen
    int itRand = 1;

    // opis historii
    std::string hist = "Po uratowaniu osob z drzewa i uzyskaniu specjalnej umiejetnosci, czujesz, ze Twoja misja\n"
        "wcale sie nie konczy. Wiesz, ze musisz podazac za smokiem, ktory udalo Ci sie tylko na chwile przestraszyc.\n"
        "Kierujesz sie teraz w strone Museum Techniki, miejsca, ktore kiedys bylo symbolem postepu i ludzkich osiagniec,\n"
        "a teraz lezy w ruinach, owiane plomieniami i dymem. Wierzysz, ze wlasnie tam znajdziesz smoka i bedziesz\n"
        "mogl sie z nim skonfrontowac.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnterSec();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // opis historii
    hist = "Z kazdym krokiem czujesz, jak adrenalina wzmaga sie w Twoich zylach, a kazdy dzwiek\n"
        "budzi czujnosc. Gdy zblizasz sie do muzeum, widzisz jego sylwetke na horyzoncie - zniszczone budynki,\n"
        "roztrzaskane eksponaty i wszechobecny zapach spalenizny. Wiesz, ze to bedzie trudna walka,\n"
        "ale jestes zdeterminowany, by odpedzic Aethraxisa i przywrocic spokoj miastu.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran


    // graficzne pokazanie drogi
    std::string text = "#####################";
    std::string road = "Droga - ";
    srand(time(0));

    // pokazanie graficznego przebiegu drogi oraz losowanie rawndomowych eventow
    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // zatrzymanie iterowania na 50 milisekund
        int randomNumber = rand() % 51; // losowanie liczby od 0 do 50
        if ((itRand == 1) && randomNumber >= 0 && randomNumber <= 6)
        {
            clearScreen(); // Wyczysc ekran
            museumOfTechnicEventItems(itRand, firefighter);// metoda do randomowych zdarzen
            itRand -= 1;
        }
        clearScreen();// Wyczysc ekran
    }

    // opis historii
    hist = "Po dotarciu na miejsce, widzisz, ze muzeum jest w oplakanym stanie. W powietrzu unosi sie gesty dym,\n"
        "ktory utrudnia oddychanie. Nagle, wsrod ruin, dostrzegasz potezna sylwetke Aethraxisa. Smok zionie ogniem,\n"
        "niszczac resztki muzeum. Musisz dzialac szybko i skutecznie, aby ugasic pozar i jednoczesnie stawic czola smokowi.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // Opis zadania 
    hist = "Twoim zadaniem bedzie ugaszenie pozaru w jak najszybszym czasie po przez uzywania rzeczy z ekwpinuku.\n"
        "Jesli ci sie nie uda ugasic, wplynie to na koncowy rezultat gry.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    fightEngine(100, 1, firefighter);

    hist = "Po wyczerpujacej walce, kiedy Aethraxis, choc niepokonany, zostal wygnany z miasta, zobaczyles coc niezwyklego.\n"
        "Na wzgorzu, gorujacym nad biblioteka miejska, krazyly smoki, ich obecnosc zwiastujaca cos niepokojacego.\n"
        "Ostrzegawcze warkniecia i blyski ognia na niebie sprawialy, ze atmosfera byla napieta i niepewna.\n"
        "Zdajac sobie sprawe, ze sytuacja w miescie nadal jest krytyczna, postanowiles zbadac, co sie dzieje w bibliotece,\n"
        "w nadziei na znalezienie odpowiedzi na to zagadkowe zjawisko.";
    displayTextSlowly(hist); // wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

}

// Level - Biblioteka miasto oraz losowe eventy
void libraryEventItems(int randomEvent, Firefighter& firefighter)
{
    if (randomEvent == 1)
    {
        // opis eventu
        std::string event = "Podczas podrozy w strone biblioteki, przykulo Twoja uwage zgliszcza szkoly.\n"
            "Zatrzymujesz sie na chwile, by lepiej przyjrzec sie temu, co pozostalo z budynku.\nCzy "
            "chcesz przeszukac ten budynek? \n\n1. Tak\n2. Nie\nWybor: ";
        displayTextSlowly(event); // Wyswietlenie tekstu

        int choice = choice2Options(event); // wybranie jednej z dwoch opcji

        //wizualizacja szukania
        std::string seak = "##############################";
        std::cout << "Szukanie - ";
        displayTextSlowly(seak); // wyswietlanie tekstu
        clearScreen(); // czysczenie ekranu

        srand(time(0));
        int randomNumber = rand() % 51;
        if (randomNumber <= 50 && randomNumber >= 25)
        {
            std::string info = "Niestety nic nie znalazles.";
            displayTextSlowly(info); // wyswietlenie tekstu
        }
        else
        {
            std::string info = "Znalazles wiadro i gasnice!\n\n\n+1 Gasnica\n+1 Wiadro";
            displayTextSlowly(info); // wyswietlenie teksu
            addItems(1, firefighter); // dodanie gasnicy do plecaka
            addItems(3, firefighter); // dodanie wiadra do plecaka
            firefighter.score += 20;
        }
        waitForEnter();  // Czekaj na naciśnięcie Enter
        clearScreen();  // Wyczyść ekran
    }
    else if (randomEvent == 2)
    {
        // opis eventu
        std::string event = "Podczas podrozy w strone biblioteki, przykulo Twoja uwage dziwne miejsce.\n"
            "Zatrzymujesz sie na chwile, by lepiej przyjrzec sie temu, co pozostalo z budynku.\nCzy "
            "chcesz przeszukac ten budynek? "
            "\n\n1. Tak\n2. Nie\nWybor: ";
        displayTextSlowly(event); // Wyswietlenie tekstu

        int choice = choice2Options(event); // wybranie jednej  z dwoch opcji

        // wyjscie z eventu
        if (choice == 2)
        {
            return;
        }

        // opis eventu
        std::string fail = "Niestety ale zostales schwytany w ognista klatke. Musiales zuzyc pierwszy przedmiot z listy!";

        // usuniecie przedmiotu z plecaka
        if (!firefighter.backpack.empty()) {
            firefighter.backpack.erase(firefighter.backpack.begin());
        }

        displayTextSlowly(fail); // wyswietlenie tekstu
        waitForEnter();  // Czekaj na naciśnięcie Enter
        clearScreen();  // Wyczyść ekran
    }
    else if (randomEvent == 3)
    {
        // opis eventu
        std::string event = "Podczas drogi do Biblioteki, nagle zauwazasz strazaka.\n"
            "Czy chcesz podejsc i porozmawiac z strazakiem?\n\n1. Tak\n2. Nie\nWybor: ";
        displayTextSlowly(event); // Wsywietlenie tekstu

        int choice = choice2Options(event); // wybranie jednej z dwoch opcji

        // wyjscie z eventu
        if (choice == 2)
        {
            return;
        }

        // wybranie opcji
        std::string quest = "1. Witaj, czy wiesz co sie dzieje w bibliotece?\n2. Witaj, czy mozesz mi pomoc?\nWybor: ";
        displayTextSlowly(quest); // Wsywietlenie tekstu

        choice = choice2Options(quest); // wybranie jednej z dwoch opcji

        clearScreen(); // wyczyszczenie ekranu
        if (choice == 1) {
            std::string dial = "Bohater: Witaj, czy wiesz co sie dzieje w rejonie biblioteki?\n\n"
                "Strazak: Wybacz ale nie mam czasu na pogawedki.";
            displayTextSlowly(dial); // Wsywietlenie tekstu
        }
        else if (choice == 2) {
            std::string dial = "Bohater: Witaj, czy mozesz mi pomoc?\n\n"
                "Strazak: Slucham.\n\n"
                "Bohater: Potrzebuje ekwipunku do pokonania pozarow oraz smokow, czy masz cos co by mi pomoglo?\n\n"
                "Strazak: Moge ci pozyczyc wiadro z woda.\n\n"
                "Bohater: Bardzo dziekuje za propozycje. Czy moglbys mi pomoc dotrzec do biblioteki?\n\n"
                "Strazak: Niestety, mam inne sprawy do zalatwienia. Ale zycze ci powodzenia.\n\n+1 Wiadro";
            displayTextSlowly(dial); // Wsywietlenie tekstu
            addItems(3,firefighter); // dodanie wiadra do plecaka
            firefighter.score += 10;
        }
        waitForEnter(); // Wyczyść ekran
    }

    
}
void library(Firefighter& firefighter)
{
    // zapisanie 3 randomowych zdarzen
    int itRand = 3;

    // opis historii
    std::string hist = "Natychmiast udales sie do biblioteki, aby zbadac sytuacje. W bibliotece zastapila cie atmosfera skupienia,\n"
        "a ludzie goraczkowo poszukiwali informacji. Wsrod nich rowniez ty, majac nadzieje znalezc wskazowki na \n"
        "temat obecnosci smokow i sposobu ich powstrzymania.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnterSec();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // graficzne pokazanie drogi
    std::string text = "#########################################";
    std::string road = "Droga - ";
    srand(time(0));

    // pokazanie graficznego przebiegu drogi oraz losowanie rawndomowych eventow
    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // zatrzymanie iterowania na 50 milisekund
        int randomNumber = rand() % 51; // losowanie liczby od 0 do 50
        if ((itRand == 1 || itRand == 2|| itRand == 3) && randomNumber >= 0 && randomNumber <= 5)
        {
            clearScreen(); // wyczyszczenie ekranu
            libraryEventItems(itRand, firefighter);// metoda do randomowych zdarzen
            itRand -= 1;
        }
        clearScreen(); // wyczyszczenie ekranu
    }

    // opis hitorii
    hist = "Gdy dotarles do biblioteki, zauwazasz, ze ludzie sa uwiezieni w dziwnej konstrukcji przypominajacej klatke.\n"
        "Krzyki i wolanie o pomoc napelniaja powietrze, a panika zaczyna sie rozprzestrzeniac. Musisz znalezc sposob,\n"
        "jak uwolnic uwiezionych, zanim bedzie za pozno. Szukajac wzrokiem przykula cie magiczna kartka z szyfrem do klodki.\n"
        "Twoim zadaniem bedzie odgadniecie hasla do klodki.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // opis zagadki
    hist = "uasfhajskfhajksh2akslfkaaslf\n"
        "sadkj1fjasfhajksfhjaksfhasfa\n"
        "kiwoeqiweqruy8jqrhjhjsdhasds\n"
        "asdhajskh1ajshdjakdhajksdask\n\n"
        "Ten szyfr zawiera kod do klodki. Znajdz i wpisz zeby uwolnic ludzi\n\nKod do klodki: ";
    displayTextSlowly(hist);// Wyswietlenie tekstu

    int code = 2181; // kod do odgadniecia
    std::string userInput1;
    int choiceCode;
    while (true) {
        std::getline(std::cin, userInput1);
        std::stringstream ss(userInput1);
        if (ss >> choiceCode && (code == choiceCode) && ss.eof()) {
            clearScreen(); // Wyczyść ekran
            break;
        }
        else {
            clearScreen(); // Wyczyść ekran
            std::cout << hist;
        }
    }

    // opis zagadki
    hist = "BRAWO! odgadles wlasciwy kod. Uratowales wiele istnien przez smiercia.\n"
        "\nW podziekowaniu mieszkancy biblioteki podarowali ci nowa umiejetnosc - przyzywanie deszczu oraz dwie bomby wodne\n\n\n+1 Przyzywanie deszczu\n+2 Bomby wodne";

    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran
    addAbilities(2, firefighter); // dodanie umiejetnosci do listy
    addItems(2, firefighter); // dodanie bomby wodnej
    addItems(2, firefighter); // dodanie bomby wodnej

    // opis historii
    hist = "Gdy opuszczales biblioteke, uslyszales przerazajace ryki dochodzace ze Starego Miasta.\n"
        "Wiedziales, ze to oznacza tylko jedno - kolejny smok pojawil sie w okolicy, siejac zniszczenie.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran
    firefighter.score += 50;

}

// Level - Stare miasto oraz losowe eventy
void oldTownEventItems(Firefighter& firefighter)
{
    std::string event = "W drodze na stare miasto znalazles specjalna dmuchawe do wody "
        "ktora przyda ci sie w walce z pozarami\n\n+1 Dmuchawa wodna";
    displayTextSlowly(event); // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran
    addItems(4,firefighter); // dodanie dmuchawy do plecaka
}
void oldTown(Firefighter& firefighter)
{
    // zapisanie 1 randomowych zdarzen
    int itRand = 1;

    // opis historii
    std::string hist = "Odrazu udales sie do Starego Miasta, aby zbadac sytuacje.";

    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnterSec();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // graficzne pokazanie drogi
    std::string text = "#############################################";
    std::string road = "Droga - ";
    srand(time(0));

    // pokazanie graficznego przebiegu drogi oraz losowanie rawndomowych eventow
    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // zatrzymanie iterowania na 50 milisekund
        int randomNumber = rand() % 51; // losowanie liczby od 0 do 50
        if ((itRand == 1) && randomNumber >= 0 && randomNumber <= 5)
        {
            clearScreen();// Wyczyść ekran
            oldTownEventItems(firefighter); // wylosowanie randomowego eventu
            itRand -= 1;
        }
        clearScreen();// Wyczyść ekran
    }

    // opis historii
    hist = "Kiedy dotarles, zastala cie atmosfera paniki. Ludzie goraczkowo probowali uciekac przed ogniem i zniszczeniem,\n"
        "wywolanymi przez kolejnego smoka. Na niebie unosil sie olbrzymi, srebrno-niebieski smok o imieniu Syltherion.\n"
        "Jego obecnosc emanowala chlodem, a kazde uderzenie jego skrzydel powodowalo, ze plomienie na ulicach gasly,\n"
        "tylko po to by pojawic sie z nowa sila. Syltherion mial umiejetnosc zmniejszania sily twoich atakow,\n"
        "oslabiajac cie z kazdym kolejnym starciem. Musisz znalezc sposob, aby pokonac tego poteznego\n"
        "przeciwnika i uratowac Stare Miasto.";
        
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // opis historii
    hist = "Twoim zadaniem bedzie ugaszenie pozaru w jak najszybszym czasie po przez uzywania rzeczy z ekwpinuku.\n"
        "Jesli ci sie nie uda ugasic, wplynie to na koncowy rezultat gry.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    fightEngine(250, 2, firefighter);


    // opis historii
    hist = "Po zacietej walce z Syltherionem, stare Miasto bylo zniszczone, ale przynajmniej jego mieszkancy \n"
        "byli bezpieczni. Wsrod ocalalych zauwazyles grupe ludzi, ktorzy przygladali sie z wdziecznoscia i ulzeniem.\n"
        "Masz teraz mozliwosc porozmawiania z jedna z tych osob, moze dowiesz sie czegos wiecej o sytuacji\n"
        "lub uzyskasz cenne wskazowki na dalsza podroz.\n\n"
        "Czy chcesz porozmawiac z losowa osoba?\n\n1. Tak\n2. Nie\nWybor: ";
    displayTextSlowly(hist); // Wyswietlenie tekstu

    int choice = choice2Options(hist); // wybranie jednej z dwoch opcji

    if (choice == 1)
    {
        std::string dial = "Bohater: Czy moge w czyms pomoc?\n\n"
            "Starszy mezczyzna: Juz nam pomogles, ratujac nasze miasto przed tym straszliwym smokiem.\n"
            "W podziekowaniu chcemy podarowac ci przedmioty.\n\n"
            "Bohater: Dziekuje, to na pewno bedzie bardzo przydatne.\n\n\n+1 Gasnica\n+2 Bomby wodne\n+1 Wiadro";
        displayTextSlowly(dial);// Wyswietlenie tekstu
        waitForEnter();// Czekaj na naciśnięcie Enter
        clearScreen();// Wyczyszczenie ekrany
        addItems(1, firefighter);// dodanie gasnicy do ekwipunku
        addItems(2, firefighter);// dodanie bomby do ekwipunku
        addItems(2, firefighter);// dodanie bomby do ekwipunku
        addItems(3, firefighter);// dodanie wiadra do ekwipunku
        firefighter.score += 10;
    }

    // opis historii
    hist = "Kolejne miejsce, do ktorego prowadza wskazowki, to starozytna Cytadela, znajdujaca sie na wzgorzu.\n"
        "To dawna twierdza, ktora kiedys sluzyla jako glowna linia obrony miasta. Teraz, jej mury sa pokryte mchem,\n"
        "a wieze niegdys majestatyczne, teraz wygladaja na opuszczone i zaniedbane.";
    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnter();// Czekaj na naciśnięcie Enter
    clearScreen();// Wyczyszczenie ekrany

    // opis historii
    hist = "Podczas zbierania sie do wyprawy do cydateli znalazles waz gasniczy oraz dmuchawe ktore przyda ci sie w walce z ogniem!\n\n+1 Waz gasniczy\n+1 Wiadro";
    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnter();// Czekaj na naciśnięcie Enter
    clearScreen();// Wyczyszczenie ekrany
    addItems(5, firefighter); // dodanie weza gasniczego do ekwipunku
    addItems(4, firefighter); // dodanie dmuchawy do ekwipunku
}

// Level - Cytadela oraz losowe eventy
void cytadelEventItems(int randomEvent, Firefighter& firefighter)
{
    if (randomEvent == 4)
    {
        // opis eventu
        std::string event = "Podczas drogi do cytadeli, nagle zauwazasz strazaka.\n"
            "Czy chcesz podejsc i porozmawiac z ta nieznajoma osoba?"
            "\n\n1. Tak\n2. Nie\nWybor: ";
        displayTextSlowly(event); // wyswietlenie tekstu

        int choice = choice2Options(event); // wybranie jednej z dowch opcji

        // wyjscie z eventu
        if (choice == 2)
        {
            return;
        }

        clearScreen(); // wyczyszczenie ekranu
        std::string dial = "Bohater: Czesc, wracasz moze z cytadeli?\n\n"
            "Strazak: A nie widac? Cytadela jest w oplakanym stanie, a na dodatek kraży tam smok!\n\n"
            "Bohater: Czy masz jakies wskazowki, jak sie tam dostac i przejsc bezpiecznie?\n\n"
            "Strazak: Trzymaj te mapę, pomoże Ci znaleźć bezpieczną drogę. Uważaj na siebie! I pamietaj, na ogień w cytadeli najlepiej działaja bomby wodne.\n\n";
        displayTextSlowly(dial); // wyswietlenie dialogu
        waitForEnter(); // Czekaj na naciśnięcie Enter
        clearScreen();  // Wyczyść ekran
        firefighter.score += 10;
    }
    else if (randomEvent == 3)
    {
        // opis eventu
        std::string event = "Podczas podrozy w strone cytadeli, przykulo Twoja uwage opuszczona remiza. "
            "Zatrzymujesz sie na chwile, by lepiej przyjrzec sie temu, co pozostalo z budynku. Czy "
            "chcesz przeszukac ten budynek?"
            "\n\n1. Tak\n2. Nie\nWybor: ";

        displayTextSlowly(event);// Wyswietlenie tekstu

        int choice = choice2Options(event); // wybranie jednej z dwoch opcji

        //wizualizacja szukania
        std::string seak = "##############################";
        std::cout << "Szukanie - ";
        displayTextSlowly(seak);// Wyswietlenie tekstu
        clearScreen(); // wyczyszczenie erkanu

        srand(time(0));
        int randomNumber = rand() % 51; // losowanie liczby od 0 do 50
        if (randomNumber <= 50 && randomNumber >= 25)
        {
            // opis eventu
            event = "Znalazles wiadro, 3 gasnice oraz dwie bomby wodna\n\n\n+1 Wiadro\n+2 Bomba wodna\n+3 Gasnica";
            displayTextSlowly(event);// Wyswietlenie tekstu
            addItems(3, firefighter); // dodanie gasnicy
            addItems(2, firefighter); // dodanie bomby wodnej
            addItems(2, firefighter); // dodanie bomby wodnej
            addItems(1, firefighter); // dodanie gasnicy
            addItems(1, firefighter); // dodanie gasnicy
            addItems(1, firefighter); // dodanie gasnicy
        }
        else
        {
            // opis eventu
            event = "Znalazles dwie gasnice i trzy weze gasnicze!\n\n\n+2 Gasnice\n+3 Waz gasniczy";
            displayTextSlowly(event);// Wyswietlenie tekstu
            addItems(1, firefighter); // dodanie gasnicy
            addItems(1, firefighter); // dodanie gasnicy
            addItems(5, firefighter); // dodanie weza gasniczego
            addItems(5, firefighter); // dodanie weza gasniczego
            addItems(5, firefighter); // dodanie weza gasniczego
        }
        waitForEnterSec();  // Czekaj na naciśnięcie Enter
        clearScreen();  // Wyczyść ekran
        firefighter.score += 10;
    }
    else if (randomEvent == 2)
    {
        // opis eventu
        std::string event = "Podczas drogi do cytadeli, przypadkowi ludzie poprosili cie o ugaszenie ich domu\n"
            "bedziesz musial uzyc jednej weza gasniczego, ktory masz przy sobie by ugasic ogromny pozar.\n"
            "Czy chcesz to zrobic? To moze byc kluczowy moment, wiec decyzja nalezy do Ciebie."
            "\n\n1. Tak\n2. Nie\nWybor: ";

        displayTextSlowly(event); // wyswietlenie tekstu

        int choice = choice2Options(event); // wybranie jednej z dwoj opcji

        // wysjcie
        if (choice == 2)
        {
            return;
        }

        clearScreen(); // wyczyszczenie ekranu

        // opis dialogu
        std::string dia = "Nieznajomy: Dziekuje ci za zgaszenie naszego domu.\n\n"
            "Bohater: Nie ma za co dziekowac.\n\n"
            "Nieznajomy: Jest, ale w zamian za pomoc ofiarujemy ci gasnice, ktora moze okazac sie przydatna w twojej podrozy.\n\n"
            "Bohater: Dziekuje za oferte. Przyjmuje ja z wdziecznoscia.\n\n\n-1 Waz gasniczy\n+1 Gasnica\n+1 Bomba wodna";

        // usuniecie weza gasniczego
        for (auto it = firefighter.backpack.begin(); it != firefighter.backpack.end(); ++it) {
            if (it->name == "Waz gasniczy") {
                firefighter.backpack.erase(it);
                break; // Przerwij pętlę po znalezieniu i usunięciu przedmiotu
            }
        }
        addItems(1, firefighter); // dodanie gasciny do ekwipunku
        addItems(2, firefighter);// dodanie bomby wodnej do ekwipunku
        displayTextSlowly(dia); // Wyswietlenie tekstu
        waitForEnter();// Czekaj na naciśnięcie Enter
        clearScreen(); // wyczyszczenie ekranu
        firefighter.score += 30;
    }
    else if (randomEvent == 1)
    {
        // opis eventu
        std::string event = "Podczas drogi do cytadeli, nagle zauwazasz postac stojaca na srdoku drogi. "
            "Czy chcesz podejsc i porozmawiac z ta nieznajoma osoba?"
            "\n\n1. Tak\n2. Nie\nWybor: ";
        displayTextSlowly(event); // Wyswietlenie tekstu

        int choice = choice2Options(event); // wybieranie jedne z dwoch opcji

        if (choice == 2)
        {
            return;
        }

        //opis wyboru
        event = "Wybierz jedna z opcji\n\n1. Witaj, kim jestes?\n2. Odejdz!\nWybor: ";
        displayTextSlowly(event); // Wyswietlenie tekstu

        choice = choice2Options(event); // wybieranie jedne z dwoch opcji

        clearScreen(); // Wyczyszczenie ekrany

        if (choice == 1) {

            // opis dialogu
            std::string dial = "Bohater: Witaj, kim jestes?\n\n"
                "Wiedzma: Jestem strazniczka tej krainy. Twoja obecnosc tutaj nie jest przypadkowa.\n\n"
                "Bohater: Czy mozesz mi pomoc? Szukam wskazowek, jak pokonac smoki i ugasic pozary.\n\n"
                "Wiedzma: Moge Ci pomoc. Ale musisz mi odpowiedziec na zagadke ktora przygotowalam dla ciebie, masz 3 proby.\n\n";
            displayTextSlowly(dial);// Wyswietlenie tekstu
            waitForEnter(); // Czekaj na naciśnięcie Enter 
            clearScreen(); // Wyczyszczenie ekrany

            // opis zagadki
            dial ="Plynie, a nie rzeka.\n"
                "Stoi, a nie cz;owiek.\n"
                "Czasem się z nim liczysz.\n"
                "Zawsze jest przy Tobie.\n\nOdpowiedz: ";
            displayTextSlowly(dial);// Wyswietlenie tekstu
            waitForEnter(); // Czekaj na naciśnięcie Enter 
            clearScreen(); // Wyczyszczenie ekrany

            // sprawdzanie czy uzytkownik poprawnie odgadl
            bool accept = false;
            int attempt = 3;
            while (true)
            {
                clearScreen();// wyczyszczenie ekranu
                std::string ans;
                std::cin >> ans;
                if (toLowerCase(ans) == "czas") {
                    accept = true;
                    break;
                }
                else if(attempt == 0) 
                {
                    break;
                }
                attempt -= 1;
                std::cout << dial;
            }
            clearScreen(); // wyczyszczenie ekranu

            // sprawdzenie czy odgadl uzytkownik zagadke
            if (accept)
            {
                // opis zgadniecia
                dial = "BRAWO! Odpowiedz jest poprawna, dostajesz umiejetnosc!\n\n+1 Wzmocnienie gaszenia.";
                addAbilities(3, firefighter); // dodanie umiejetnosci do listy
                firefighter.score += 30;
            }
            else
            {
                // opis zgadniecia
                dial = "Niestety, odpowiedz jest niepoprawna. Nie dostajesz dodatkowej umiejetnosci.";
                firefighter.score += 10;
            }
            displayTextSlowly(dial);// Wyswietlenie tekstu
        }
        else if (choice == 2) {
            std::string dial = "Bohater: Odejdz!\n\n"
                "Nieznajomy: Przegrasz ta walke...";
            displayTextSlowly(dial);// Wyswietlenie tekstu
        }
        waitForEnter();// Czekaj na naciśnięcie Enter 
        clearScreen();// wyczyszczenie ekranu
    }
}
void cytadel(Firefighter& firefighter)
{
    // zapisanie 4 randomowych zdarzen
    int itRand = 4;

    // opis historii
    std::string hist = "Po zakonczeniu akcji ratunkowej na Starym Miescie, skierowales swoje kroki w strone Cytadeli.\n"
       "Wskazowki, ktore zebrales od mieszkancow, prowadzily Cie wlasnie tam. Cytadela, gorujaca nad miastem,\n"
       "byla niegdys symbolem potegi i ochrony. Dzis jej mury ss pokryte bluszczem, a wieze wydaja sie niemal dotykac nieba.\n"
       "Wiesz, ze wewnatrz czeka na Ciebie nowe wyzwanie, a byc moze i kolejny smok.\n"
       "Twoja misja jest jasna - musisz odkryc tajemnice Cytadeli i zrobic wszystko, by uratowac miasto.";
    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnterSec();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // graficzne pokazanie drogi
    std::string text = "######################################################################";
    std::string road = "Droga - ";
    srand(time(0));

    // pokazanie graficznego przebiegu drogi oraz losowanie rawndomowych eventow
    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));// zatrzymanie iterowania na 50 milisekund
        int randomNumber = rand() % 51;  // losowanie liczby od 0 do 50
        if ((itRand <=4 && itRand >= 1) && randomNumber >= 0 && randomNumber <= 5)
        {
            clearScreen(); // Wyczyść ekran
            cytadelEventItems(itRand,firefighter); // wylosowanie randomowego eventu
            itRand -= 1;
        }
        clearScreen(); // Wyczyść ekran
    }

    // opis hitorii
    hist = "Po dotarciu do cytadeli, zastałes ogromny specjalny ogien, ktory będzie kosztowal duzo wysilku,\n"
        "by ugasic. Dodatkowo zauwazasz, ze smok, który wczesniej sial spustoszenie, lezy z potezna rana.\n"
        "Jest to Pyroskryt, smok potrafiacy mowic ludzkim glosem. Teraz czeka cie nielatwa walka z ogniem\n"
        "i proba porozumienia sie z rannym smokiem, by zrozumiec, co spowodowalo jego agresje.";

    // opis historii
    hist = "Twoim zadaniem bedzie ugaszenie pozaru w jak najszybszym czasie po przez uzywania rzeczy z ekwpinuku.\n"
        "Jesli ci sie nie uda ugasic, wplynie to na koncowy rezultat gry.";
    displayTextSlowly(hist);   // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    fightEngine(450, 3, firefighter);

    hist = "Po zakonczeniu walki z pozarem, bohaterowi udalo sie dotrzec do rannego smoka. Smok, nazwany Pyroskrytem.";
    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // opis dialogu
    std::string dial = "Czesc, Pyroskrycie. Jak sie czujesz?\n\n"
        "Marnie, ale przezyje. Dzieki za interwencje.\n\n"
        "To dobrze, ze udalo mi sie dotrzec na czas. Co spowodowalo twoje rany?\n\n"
        "To Wladca Zaru. To on atakuje smoki, prowokujac je do agresji, a ich agresywne zachowanie prowadzi do pozarow.\n\n"
        "Wladca Zaru? Gdzie go znajdziemy?\n\n"
        "Musisz udac sie na wzgorze. To tam mieszka. Badz ostrozny, bo to potezny przeciwnik.\n\n"
        "Dzieki za ostrzezenie. Ruszam w droge. Dzieki, Pyroskrycie.";
    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran
}

// Final gry oraz losowy event
void finalEvent(Firefighter& firefighter)
{
    // opis historii
    std::string hist = "Przemierzales waska, kreta sciezke prowadzaca przez ciemny las. Kazdy krok byl wyzwaniem,\n"
        "a geste zarosla sprawialy, ze droga wydawala sie jeszcze bardziej niebezpieczna. Nagle, na srodku drogi,\n"
        "dostrzegłles sylwetke starszego mezczyzny, opierajacego sie na kosturze. Jego biala broda i gleboko osadzone\n"
        "oczy swiadczyly o wielkiej madrosci i doswiadczeniu.\n\n";
    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // dialog
    std::string dial = "Straznik: Witaj, mlody wojowniku, wygladasz na kogos, kto ma przed soba wazne zadanie.'\n\n";
    std::string que = "1. Kim jestes?\n2. Skad wiesz o moim zadaniu?\n3. Czy mozesz mi pomoc?\nWybor: ";

    int choice = choice3Options(dial + que); // wybranie jednej z 3 opcji
    clearScreen(); // Wyczyść ekran
    displayTextSlowly(dial); // Wyswietlenie tekstu
    if (choice == 1)
    {
        // opis dialogu
        dial += "Bohater: Kim jestes?\n\n"
            "Straznik: Jestem Althar, starozytny straznik tych lasow, odpowiedzial. Chronie to miejsce i jego mieszkancow od wielu lat.\n\n"
            "Bohater: Dlaczego tu jestes?\n\n"
            "Straznik: Wiedzialem, ze nadejdzie ktos taki jak ty. Twoje serce jest czyste, a twoja misja szlachetna. Potrzebujesz pomocy, a ja moge ci jej udzielic.\n\n"
            "Bohater: Jak mozesz mi pomoc?\n\n"
            "Straznik: Odzyskales czesc swoich umiejetnosci, ale nadal jestes slabszy niz powinienes byc, pozwol, ze przywroce ci pelna sile.\n\n"
            "Bohater: Dziekuje, Altharze. Teraz jestem gotow stawic czola Wladcy Zaru.\n\n"
            "Straznik: Idz i spelnij swoje przeznaczenie.";

    }
    else if (choice == 2)
    {
        // opis dialogu
        dial += "Bohater: Skad wiesz o moim zadaniu?\n\n"
            "Straznik: Jestem Althar, starozytny straznik tych lasow. Wiedzialem, ze nadejdzie ktos, kto sprobuje powstrzymac Wladce Zaru.\n\n"
            "Bohater: Jak mozesz mi pomoc?\n\n"
            "Straznik: Twoja determinacja jest godna podziwu, ale widze, ze jestes oslabiony. Pozwol, ze przywroce ci pelna sile.\n\n"
            "Bohater: Dziekuje, Altharze. Teraz jestem gotow stawic czola Wladcy Zaru.\n\n"
            "Straznik: Idz i spelnij swoje przeznaczenie.";
    }
    else
    {
        // opis dialogu
        dial += "Bohater: Czy mozesz mi pomoc?\n\n"
            "Straznik: Jestem Althar, starozytny straznik tych lasow. Widze, ze twoje serce jest pelne odwagi, ale twoje cialo jest oslabione. "
            "Twoje zadanie jest niezwykle wazne. Musisz byc w pelni sil, aby stawic czola Wladcy Zaru.\n\n"
            "Bohater: Jak mozesz mi pomoc?\n\n"
            "Straznik: Moge przywrocic ci pelna sile. Pozwol, ze uzyje mojej magii, abys mogl odzyskac wszystkie swoje umiejetnosci.\n\n"
            "Bohater: Dziekuje, Altharze. Teraz jestem gotow stawic czola Wladcy Zaru.\n\n"
            "Straznik: Idz i spelnij swoje przeznaczenie.";
    }
    displayTextSlowly(dial); // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // zmienienie na aktywne wszystkie umiejetnosci
    for (auto& item : firefighter.abilities) {
        item.active = true;
    }

}
void final(Firefighter& firefighter)
{
    // zapisanie 1 randomowych zdarzen
    int itRand = 1;

    //opis historii
    std::string hist = "Wziales gleboki oddech i spojrzales w strone wzgorza.\n"
        "Przed toba rozciagal sie dlugi szlak, wijacy sie przez las i pnący sie ku ciemnym, \n"
        "burzowym chmurom zbierajacym sie nad wzgorzem. Kazdy krok w kierunku wzgorza wydawal sie ciezszy,\n"
        "jakby powietrze samo w sobie bylo przesycone niebezpieczenstwem i tajemnica.\n"
        "Kazdy krok w kierunku wzgorza wydawal sie ciezszy, jakby powietrze samo w sobie bylo przesycone niebezpieczenstwem i tajemnica.\n\n"
        "Droga byla ciezka i wyboista. Czasami musiales przeciskac sie przez geste zarosla, \n"
        "innym razem omijac powalone drzewa i przeprawiac sie przez rwace potoki. Las wokol ciebie byl cichy, \n"
        "zbyt cichy jak na zwykle warunki. Nawet ptaki zdawaly sie unikac tego miejsca.\n\n";

    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnterSec();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    // graficzne pokazanie drogi
    std::string text = "##############################";
    std::string road = "Droga - ";
    srand(time(0));

    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        int randomNumber = rand() % 51;
        if ((itRand == 1) && randomNumber >= 0 && randomNumber <= 2)
        {
            clearScreen(); // Wyczyszczenie ekranu
            finalEvent(firefighter); // event 
            itRand -= 1;
        }
        clearScreen(); // wyczyszczenie ekranu
    }

    //opis historii
    hist = "W koncu dotarles do podnoza wzgorza. Przed toba rozposcieraly sie strome schody wykute w skale,\n"
        "prowadzace na sam szczyt. Wiedziales, ze na gorze czeka Wladca Zaru, gotowy do walki. Z pelnym zdecydowaniem\n"
        "zacząles wspinaczke, kazdy krok przyblizal cie do konfrontacji z poteznym przeciwnikiem.\n\n";
    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    //opis historii
    hist = "Po dlugiej i wyczerpujacej wspinaczce, wreszcie dotarles na szczyt wzgorza. Twoim oczom ukazal sie Wladca\n"
        "Zaru w calej swojej okazalosci. Byl to potezny smok o luskach jak lawa, a jego oddech rozpalal\n"
        "powietrze do czerwonosci. Jego oczy plonely zlowieszcza inteligencja, a wokol niego krazyly dwa\n"
        "inne smoki - jeden o szafirowych luskach, a drugi o szmaragdowych oczach, obaj gotowi bronic swego pana.\n\n ";

    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnter();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    //opis historii
    hist = "Wladca zaru: Smialku, myslisz, ze mozesz mnie pokonac?"
        "Nie wiesz, z kim masz do czynienia. Jestem wladca ognia i zniszczenia!'\n\n"
        "Bohater: Nie boje sie ciebie, Wladco Zaru, Twoje rany na moim przyjacielu Pyroskrycie"
        "zostana pomszczone, a ja poloze kres twoim niszczycielskim planom.'\n\n"
        "Wladca zaru: Pyroskryt byl slaby, a ty podzielisz jego los. Moi sludzy i ja roztrzaskamy cie na proch, a twoje miasto splynie krwia!'\n\n";

    displayTextSlowly(hist); // Wyswietlenie tekstu
    waitForEnterSec();  // Czekaj na naciśnięcie Enter
    clearScreen();  // Wyczyść ekran

    fightEngine(1000, 4, firefighter);


}

// wybranie danego lvl
int level(int stage, Firefighter& firefighter)
{
    switch (stage)
    {
    case 0:
        centralPark(firefighter);
        break;
    case 1:
        museumOfTechnic(firefighter);
        break;
    case 2:
        library(firefighter);
        break;
    case 3:
        oldTown(firefighter);
        break;
    case 4:
        cytadel(firefighter);
        break;
    case 5:
        final(firefighter);
        break;
    }

    return 0;
}
// menu 
int main() {

    // utworzenie obiektu strazaka
    Firefighter firefighter(0);

    intro(); // wprowadzenie do gry
    int firstItem = firstQuest(firefighter); // pierwszy quest

    // dodanie poczatkowych przemidotow
    switch (firstItem)
    {
    case 1:
        addItems(1, firefighter); // dodanie gasnicy do ekwpiunku
        addItems(1, firefighter); // dodanie gasnicy do ekwpiunku
        break;
    case 2:
        addItems(1, firefighter);// dodanie gasnicy do ekwpiunku
        addItems(1, firefighter); // dodanie gasnicy do ekwpiunku
        addItems(2, firefighter);// dodanie bomby wodnej do ekwpiunku
        break;
    case 3:
        addItems(1, firefighter);// dodanie gasnicy do ekwpiunku
        addItems(1, firefighter); // dodanie gasnicy do ekwpiunku
        addItems(1, firefighter); // dodanie gasnicy do ekwpiunku
        break;
    default:
        break;
    } 

    // tablica z wszytskimi lokalizacjami
    std::string tablica[6] = {
    "Centralny Park",
    "Muzeum Techniki",
    "Biblioteka Miejska",
    "Stare Miasto",
    "Cytadela",
    "Wladcy zaru",};


    int stage = 0; // dany level
    int choice;
    while (true) {
        clearScreen(); // wyczyszczenie ekranu
        displayMenu(firefighter.score,tablica[stage]); // wyswietlenie menu
        std::cout << "Wybierz opcje: ";
        std::cin >> choice;
        std::string items;
        int num = 0;
        clearScreen(); // wyczyszczenie ekranu

        switch (choice) {
        case 1:
            level(stage,firefighter); // start danego lvl
            stage += 1;
            break;
        case 2:
            showMap(); // pokazanie wszytskich miejsc
            break;
        case 3:
            // sprawdzenie wszytskich umiejetnosci
            if (firefighter.backpack.empty()) {
                items = "BRAK PRZEDMIOTOW\n";
            }
            else {
                for (const auto& item : firefighter.backpack) {
                    num += 1;
                    items += std::to_string(num) + ". " + item.name + ": " + item.description + "\n";
                }
            }
            displayTextSlowly(items); // wyswietlenie przedmiotow
            waitForEnterSec(); // Czekaj na naciśnięcie Enter
            break;
        case 4:
            // sprawdzenie wszytskim umiejetnosci
            if (firefighter.abilities.empty()) {
                items = "BRAK UMIEJETNOSCI\n";
            }
            else {
                for (const auto& item : firefighter.abilities) {
                    num += 1;
                    items += std::to_string(num) + ". " + item.name + ": " + item.description;
                    if (item.active == true)
                    {
                        items += " - Aktywna\n";
                    }
                    else
                    {
                        items += " - Nieaktywna\n";
                    }
                }
            }
            displayTextSlowly(items);// wyswietlenie wszytskich umiejetnosci
            waitForEnterSec();// Czekaj na naciśnięcie Enter
            break;
        case 5:
            // Zapisz (nie dziala)
            break;
        case 6:
            target(); // Cel gry
            break;
        case 7:
            return 0; // Wyjscie
        default:
            continue;
        }

        // wyjscie po finale
        if (stage == 6)
        {
            break;
        }
    }

    std::string finalStage;
    if (firefighter.score >= 0 && firefighter.score <= 1300)
    {
        finalStage = "Niestety, nie udalo ci sie pokonac Wladcy Zaru. Jego potega okazala sie zbyt wielka, a twoje wysilki byly niewystarczajace.\n"
            "Miasto zostanie spalone, a ludzie pozostana bezbronni wobec atakow smokow. Twoja porazka zostanie zapamietana na wieki.\n"
            "Czy zdołasz zbierzec siły i sprobować ponownie? To juz zalezy od ciebie...\n\nWynik - " + std::to_string(firefighter.score);

        displayTextSlowly(finalStage); // Wyswietlenie tekstu
        waitForEnterSec();  // Czekaj na naciśnięcie Enter
        clearScreen();  // Wyczyść ekran
    }
    else if (firefighter.score >= 1300 && firefighter.score <= 1900)
    {
        /// ostateczna zagadka
        finalStage = "Twoje losy sa niezwykle niepewne. Nie udalo ci sie pokonac Wladcy Zaru, ale nie zostales całkowicie pokonany.\n"
            "Zamiast tego, została ci ostatnia szansa, by odwrocić szalę zwyciestwa. Musisz odgadnac jedna wazna zagadke, która zadecyduje o twoim losie.\n\n"
            "Aby odnalezc wlasciwa droge, musisz rozwiazac starozytna zagadke:\n\n";

        displayTextSlowly(finalStage); // Wyswietlenie tekstu
        waitForEnterSec();  // Czekaj na naciśnięcie Enter
        clearScreen();  // Wyczyść ekran

        finalStage = "Zawsze masz z tym stycznosc, niezaleznie od tego, gdzie jestes.\n"
            "Bez tego nie przezyjesz, choc moze miec wiele postaci.\n"
            "Moze byc zimne lub gorace, spokojne lub burzliwe.\n"
            "Co to jest?\n\n"
            "Wpisz odpowiedz: ";


        displayTextSlowly(finalStage); // Wyswietlenie tekstu
        waitForEnterSec();  // Czekaj na naciśnięcie Enter
        clearScreen();  // Wyczyść ekran

        std::string userAnswer;
        std::cout << "Wpisz odpowieds: ";
        std::cin >> userAnswer;

        if (toLowerCase(userAnswer) == "woda") {
            finalStage = "Gratulacje! Twoja odwaga i determinacja pozwoliły ci pokonac Wladce Zaru i uratować Stare Miasto przed zniszczeniem.\n"
                "Ludzie klaszcza ci na czesc, a twoje imie będzie wspominane z podziwem przez wiele lat.\n"
                "Twoje zwyciestwo przynosi nadzieje i odrodzenie dla krainy. Swiat czeka na kolejne twoje przygody...\n\nWynik - " + std::to_string(firefighter.score);

            displayTextSlowly(finalStage); // Wyswietlenie tekstu
            waitForEnterSec();  // Czekaj na naciśnięcie Enter
            clearScreen();  // Wyczyść ekran
        }
        else {
            finalStage = "Niestety, nie udalo ci sie pokonac Wladcy Zaru. Jego potega okazala sie zbyt wielka, a twoje wysilki byly niewystarczajace.\n"
                "Miasto zostanie spalone, a ludzie pozostana bezbronni wobec atakow smokow. Twoja porazka zostanie zapamietana na wieki.\n"
                "Czy zdołasz zbierzec siły i sprobowac ponownie? To juz zalezy od ciebie...\n\nWynik - " + std::to_string(firefighter.score);

            displayTextSlowly(finalStage); // Wyswietlenie tekstu
            waitForEnterSec();  // Czekaj na naciśnięcie Enter
            clearScreen();  // Wyczyść ekran
        }
    }
    else
    {
        finalStage = "Gratulacje! Twoja odwaga i determinacja pozwoliły ci pokonać Wladce Zaru i uratować Stare Miasto przed zniszczeniem.\n"
            "Ludzie klaszcza ci na czesc, a twoje imie będzie wspominane z podziwem przez wiele lat.\n"
            "Twoje zwyciestwo przynosi nadzieje i odrodzenie dla krainy. Swiat czeka na kolejne twoje przygody...\n\nWynik - " + std::to_string(firefighter.score);

        displayTextSlowly(finalStage); // Wyswietlenie tekstu
        waitForEnterSec();  // Czekaj na naciśnięcie Enter
        clearScreen();  // Wyczyść ekran
    }

    return 0;
}
