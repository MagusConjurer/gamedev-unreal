#include <iostream>

int main() {
    // Print the introduction to the game 
    std::cout << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;
    std::cout << "You have entered the forest realm." << std::endl;
    std::cout << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Before you, there are three bags and a pile of small stones." << std::endl;
    std::cout << "A man steps out from a door in a nearby tree and says:" << std::endl;
    std::cout << "You must fill the bags with the correct number of stones and place them on the pedestals to proceed into the next realm." << std::endl;
    std::cout << std::endl;

    // Declare intial values for the code
    int CodeA = 4;
    int CodeB = 7;
    int CodeC = 3;

    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;

    int LevelNum = 2 - 1;

    std::cout << "Level " << LevelNum << std::endl;
    std::cout << "The three weights must add up to: " << CodeSum << std::endl;
    std::cout << "They must also multiply to equal: " << CodeProduct << std::endl;
    std::cout << std::endl;

    int GuessA, GuessB, GuessC;

    std::cout << "Enter the number of stones you would like to place in each bag: ";
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA + GuessB + GuessC;

    return 0;
}