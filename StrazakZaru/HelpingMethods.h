#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <chrono>

// wyswietlenie menu w glownym menu
void displayMenu(int score, std::string place);

// Wyswietleniu menu w walce
std::string fightMenu();

// Zamienianie slowa na male litery
std::string toLowerCase(const std::string& str);

// czyszczenie konsoli
void clearScreen();

// Czekanie na enter
void waitForEnter();

// Czekanie na podwojny enter
void waitForEnterSec();

// wyswietlanie tekstu po malu
void displayTextSlowly(const std::string& text, int delay_ms);

// Wybieranie miedzy dwiema opcjami
int choice2Options(std::string text);

// Wybieranie miedzy trzema opcjami
int choice3Options(std::string text);

// Opis celu gry
void target();

// Opis miejsc w ktorych sie znajdzie uzytkownik
void showMap();