#include "Event.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Event::Event(std::string desc, int change, int resultingPoints)
    : description(std::move(desc)),
      pointChange(change),
      resultingGoodPoints(resultingPoints),
      timestamp(std::chrono::system_clock::now()) {}

std::string Event::getFormattedTimestamp() const {
    std::time_t timeT = std::chrono::system_clock::to_time_t(timestamp);
    std::tm localTime{};

    // Wieloplatformowa, bezpieczna obsługa czasu (Thread-safe)
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&localTime, &timeT);
#else
    localtime_r(&timeT, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}