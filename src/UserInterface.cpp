#include "UserInterface.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>

UserInterface::UserInterface(MoodTracker& trackerRef) 
    : tracker(trackerRef) {}

void UserInterface::clearScreen() const {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::system("clear");
#endif
}

void UserInterface::printProgressBar() const {
    int good = tracker.getGoodPoints();
    int totalWidth = 30; // Szerokość paska w znakach
    int filledWidth = (good * totalWidth) / 100;

    std::cout << "Stan nastroju: [";
    for (int i = 0; i < totalWidth; ++i) {
        if (i < filledWidth) {
            std::cout << "#"; // Dobre punkty
        } else {
            std::cout << "."; // Złe punkty
        }
    }
    std::cout << "] " << good << "/100 PKT (" << tracker.getMoodDescription() << ")\n";
}

void UserInterface::printHeader() const {
    clearScreen();
    std::cout << "==================================================\n";
    std::cout << "                MOOD TRACKER C++                  \n";
    std::cout << "==================================================\n\n";
    
    printProgressBar();
    std::cout << "Dobre punkty: " << tracker.getGoodPoints() 
              << " | Złe punkty: " << tracker.getBadPoints() << "\n";
    std::cout << "--------------------------------------------------\n";
}

void UserInterface::printHistory() const {
    const auto& history = tracker.getHistory();
    if (history.empty()) {
        std::cout << "\n[Brak zarejestrowanych zdarzeń w tej sesji]\n";
        return;
    }

    std::cout << "\nOstatnie zdarzenia:\n";
    // Wyświetlamy maksymalnie 5 ostatnich zdarzeń
    size_t startIdx = (history.size() > 5) ? history.size() - 5 : 0;

    for (size_t i = startIdx; i < history.size(); ++i) {
        const auto& ev = history[i];
        std::string sign = (ev.pointChange >= 0) ? "+" : "";
        std::cout << " [" << ev.getFormattedTimestamp() << "] "
                  << ev.description << " (" << sign << ev.pointChange 
                  << " pkt) -> Stan: " << ev.resultingGoodPoints << "/100\n";
    }
}

std::string UserInterface::readLine(const std::string& prompt) const {
    std::cout << prompt;
    std::string result;
    std::getline(std::cin >> std::ws, result); // std::ws czyszczenie białych znaków przed odczytem
    return result;
}

int UserInterface::readInt(const std::string& prompt) const {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        // Obsługa błędnego wpisania tekstu zamiast liczby
        std::cout << "Błąd: Wprowadź poprawną liczbę całkowitą.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void UserInterface::handleAddEvent(bool isPositive) {
    std::string desc = readLine("Podaj opis zdarzenia: ");
    int points = readInt("Podaj wartość punktową (liczba dodatnia): ");

    if (points < 0) {
        points = std::abs(points); // Zabezpieczenie przed ujemnym wkładem
    }

    int change = isPositive ? points : -points;
    tracker.addEvent(desc, change);
}

void UserInterface::run() {
    bool running = true;
    while (running) {
        printHeader();
        printHistory();

        std::cout << "\nOPCJE:\n";
        std::cout << " 1. Dodaj zdarzenie POZYTYWNE (+)\n";
        std::cout << " 2. Dodaj zdarzenie NEGATYWNE (-)\n";
        std::cout << " 3. Wyjdź\n";

        int choice = readInt("Wybierz opcję (1-3): ");

        switch (choice) {
            case 1:
                handleAddEvent(true);
                break;
            case 2:
                handleAddEvent(false);
                break;
            case 3:
                running = false;
                break;
            default:
                std::cout << "Nieprawidłowa opcja! Naciśnij Enter, aby kontynuować...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
        }
    }
}