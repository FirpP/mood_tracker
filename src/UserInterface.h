#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "MoodTracker.h"
#include <string>

class UserInterface {
private:
    MoodTracker& tracker; // Referencja do logiki biznesowej (bez kopiowania)

    // Pomocnicze metody rysujące UI
    void clearScreen() const;
    void printHeader() const;
    void printProgressBar() const;
    void printHistory() const;

    // Pomocnicze metody do bezpiecznego pobierania wejścia (Input Sanitation)
    std::string readLine(const std::string& prompt) const;
    int readInt(const std::string& prompt) const;

    void handleAddEvent(bool isPositive);

public:
    // explicit blokuje niejawną konwersję w C++
    explicit UserInterface(MoodTracker& trackerRef);

    // Główna pętla interfejsu
    void run();
};

#endif // USER_INTERFACE_H