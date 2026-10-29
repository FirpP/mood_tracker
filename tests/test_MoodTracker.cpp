#include "MoodTracker.h"
#include <cassert>
#include <iostream>

void test_initial_state() {
    MoodTracker tracker;
    assert(tracker.getGoodPoints() == 50);
    assert(tracker.getBadPoints() == 50);
}

void test_clamping() {
    MoodTracker tracker;
    tracker.addEvent("Wielka wygrana", 200); // Przekroczenie 100
    assert(tracker.getGoodPoints() == 100);
    assert(tracker.getBadPoints() == 0);

    tracker.addEvent("Tragedia", -500); // Poniżej 0
    assert(tracker.getGoodPoints() == 0);
    assert(tracker.getBadPoints() == 100);
}

int main() {
    test_initial_state();
    test_clamping();
    std::cout << "[OK] Wszystkie testy MoodTracker przeszły pomyślnie!\n";
    return 0;
}