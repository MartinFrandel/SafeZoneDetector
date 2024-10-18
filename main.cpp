#include <iostream>
#include "SafeZoneDetector.h"

int main() {
    SafeZoneDetector detector;

    if (detector.isAnyVirtualEnvironment()) {
        std::cout << "Virtual environment detected!" << std::endl;
    } else {
        std::cout << "No virtual environment detected." << std::endl;
    }

    // wait for user input
    std::cin.get();
    return 0;
}
