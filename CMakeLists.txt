cmake_minimum_required(VERSION 3.16)

# Nazwa projektu, wersja oraz język
project(MoodTracker 
    VERSION 1.0.0
    LANGUAGES CXX
)

# Wymagany standard C++17 (dla std::clamp oraz udoskonaleń w std::chrono)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opcjonalnie: Włączenie flaga ostrzeżeń kompilatora (Dobra praktyka na uczelni)
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. Tworzymy bibliotekę statyczną zawierającą rdzeń logiki (Domain Layer)
add_library(mood_tracker_lib
    src/Event.cpp
    src/Event.h
    src/MoodTracker.cpp
    src/MoodTracker.h
)

# Wskazujemy katalog nagłówkowy dla naszej biblioteki
target_include_directories(mood_tracker_lib PUBLIC src)

# 2. Tworzymy główny plik wykonywalny (Aplikacja CLI)
add_executable(mood_tracker
    src/main.cpp
    src/UserInterface.cpp
    src/UserInterface.h
)

# Łączymy główną aplikację z naszą biblioteką logiki
target_link_libraries(mood_tracker PRIVATE mood_tracker_lib)

# 3. Aktywacja mechanizmu testów CTest oraz dołączenie podkatalogu tests/
enable_testing()
add_subdirectory(tests)