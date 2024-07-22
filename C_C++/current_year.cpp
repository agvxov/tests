// @COMPILECMD g++ $@
#include <iostream>
#include <chrono>
#include <ctime>

int main() {
    // Get the current system time
    std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // Convert the time to a local time
    std::tm* localTime = std::localtime(&currentTime);

    // Extract the year from the local time
    int currentYear = localTime->tm_year + 1900;

    // Display the current year
    std::cout << "Current year: " << currentYear << std::endl;

    return 0;
}
