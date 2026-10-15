#include "MoodTracker.h"
#include "UserInterface.h"
#include <iostream>
#include <exception>

int main() {
    try {
        // 1. Inicjalizacja logiki biznesowej na stosie (Stack allocation)
        MoodTracker tracker;

        // 2. Inicjalizacja interfejsu i przekazanie referencji (Dependency Injection)
        UserInterface ui(tracker);

        // 3. Uruchomienie głównej pętli zdarzeń
        ui.run();

    } catch (const std::exception& e) {
        std::cerr << "\n[CRITICAL ERROR] Wystąpił nieoczekiwany błąd: " 
                  << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n[CRITICAL ERROR] Wystąpił nieznany błąd systemu!" 
                  << std::endl;
        return 1;
    }

    std::cout << "\nDziękujemy za skorzystanie z Mood Trackera. Do zobaczenia!\n";
    return 0;
}