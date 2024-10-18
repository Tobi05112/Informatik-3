#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>  // für std::chrono
#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
    CLI::App app{PROJECT_NAME};

    // CLI Option für --count Parameter (Standardwert: 20)
    int count = 20;
    app.add_option("-c,--count", count, "Anzahl der zufälligen Zahlen")->default_val(20);

    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    fmt::print("Hello, {}!\n", app.get_name());

    // Zufallszahlengenerator initialisieren
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // Vektor mit Zufallszahlen der Größe 'count' füllen
    std::vector<int> random_numbers(count);
    for (int &num : random_numbers) {
        num = dis(gen);
    }

    // Ausgabe des unsortierten Vektors
    fmt::print("Die zufälligen Zahlen sind: ");
    for (const auto &num : random_numbers) {
        fmt::print("{} ", num);
    }
    fmt::print("\n");

    // Zeitmessung starten
    auto start = std::chrono::system_clock::now();

    // Sortieren des Vektors
    std::sort(random_numbers.begin(), random_numbers.end());

    // Zeitmessung beenden
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Ausgabe des sortierten Vektors
    fmt::print("Die sortierten Zahlen sind: ");
    for (const auto &num : random_numbers) {
        fmt::print("{} ", num);
    }
    fmt::print("\n");

    // Ausgabe der Zeit, die für das Sortieren benötigt wurde
    fmt::print("Sortierung dauerte: {} ms\n", elapsed.count());

    return 0; /* exit gracefully */
}
