#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <chrono>

struct Event {
    std::string description;
    int pointChange;          // zmiana np. +30 lub -10
    int resultingGoodPoints;  // stan dobrych punktów po zdarzeniu
    std::chrono::system_clock::time_point timestamp; // C++ chrono time_point

    // Konstruktor inicjalizujący pola
    Event(std::string desc, int change, int resultingPoints);

    // Metoda pomocnicza do zamiany timestampu na czytelny tekst (np. "2026-10-08 15:30:00")
    std::string getFormattedTimestamp() const;
};

#endif // EVENT_H