#ifndef MOOD_TRACKER_H
#define MOOD_TRACKER_H

#include <string>
#include <vector>
#include "Event.h"

class MoodTracker {
private:
    int goodPoints;
    std::vector<Event> history;

    // Stałe określające granice punktowe (przejrzystość kodu)
    static constexpr int MIN_POINTS = 0;
    static constexpr int MAX_POINTS = 100;
    static constexpr int INITIAL_POINTS = 50;

public:
    // Konstruktor domyślny – ustawia początkowe 50 punktów
    MoodTracker();

    // Modyfikacja stanu
    void addEvent(const std::string& description, int change);

    // Gettery (oznaczone jako const, bo nie zmieniają stanu obiektu)
    int getGoodPoints() const;
    int getBadPoints() const;
    const std::vector<Event>& getHistory() const;
    std::string getMoodDescription() const;
};

#endif // MOOD_TRACKER_H