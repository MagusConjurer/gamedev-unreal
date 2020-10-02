#include <iostream>

void PrintIntro() {
    std::cout << "==================================\n\n";
    std::cout << "You have entered the forest realm.\n\n";
    std::cout << "==================================\n\n";
    std::cout << "Before you, there are three bags and a pile of small stones.\n";
    std::cout << "A man steps out from a door in a nearby tree and says:\n";
    std::cout << "\"You must fill the bags with the correct number of stones and place them on the pedestals to proceed into the next realm.\"\n\n";
}

void PlayGame() {
    PrintIntro();

    // Declare code variables
    int CodeA = 4;
    int CodeB = 7;
    int CodeC = 3;

    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;

    int LevelNum = 2 - 1;

    // Provide the player with required conditions
    std::cout << "Level " << LevelNum;
    std::cout << "\nThe three weights must add up to: " << CodeSum;
    std::cout << "\nThey must also multiply to equal: " << CodeProduct;

    int GuessA, GuessB, GuessC;

    std::cout << "\n\nEnter the number of stones you would like to place in each bag: \n";
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    // Check if the guess is correct
    if (GuessSum == CodeSum && GuessProduct == CodeProduct) {
        std::cout << "\nYou placed the correct number of stones in the bags!\n";
        std::cout << "You proceed to the next room.\n";
    } else {
        std::cout << "\nYou placed the incorrect number of stones in the bags!\n";
        std::cout << "A large stone falls from above, blocking the path forward.\n";
    }
}

int main() {
    PlayGame();
    return 0;
}