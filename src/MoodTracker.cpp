#include "MoodTracker.h"
#include <algorithm> // dla std::clamp

MoodTracker::MoodTracker() : goodPoints(INITIAL_POINTS) {}

void MoodTracker::addEvent(const std::string& description, int change) {
    // Obliczamy nową wartość i przycinamy do przedziału <0, 100>
    goodPoints = std::clamp(goodPoints + change, MIN_POINTS, MAX_POINTS);

    // Tworzymy i dodajemy nowe zdarzenie do historii
    // emplace_back tworzy obiekt Event bezpośrednio w pamięci wektora
    history.emplace_back(description, change, goodPoints);
}

int MoodTracker::getGoodPoints() const {
    return goodPoints;
}

int MoodTracker::getBadPoints() const {
    // Single Source of Truth: złe punkty to zawsze różnica od sumy 100
    return MAX_POINTS - goodPoints;
}

const std::vector<Event>& MoodTracker::getHistory() const {
    return history;
}

std::string MoodTracker::getMoodDescription() const {
    if (goodPoints >= 80) return "Entuzjaztyczny";
    if (goodPoints >= 60) return "Dobry";
    if (goodPoints >= 40) return "Neutralny";
    if (goodPoints >= 20) return "Zestresowany";
    return "Krytyczny!!!";
}