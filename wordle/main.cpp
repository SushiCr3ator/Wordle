#include <cstring>
#include <iostream>
#include <fstream>
#include <random>
#include <bits/this_thread_sleep.h>
int lang; // 0 for eng <82094> , 1 for ger <not fixed with �, so not usuable>
double randValue;
bool start;
std::string value,wordOfTheGame, playerMove;
std::pmr::vector<std::string> values;
std::pmr::vector<char> vecLetters, vecPlayer;

/* struct {
    char wrong = '-';
    char in_Word = 'o';
    char correct = '#';
}LETTERVALUES;*/

void _randomGen() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1,82094);

    randValue = distrib(gen);
    // std::cout << randValue << std::endl; //release to find the generated number
}
void _lang() {
    printf("%s", "Please select one language \n");
    printf("%s", "0: English \n");
    printf("%s", "1: Deutsch \n");
    std::cin >> lang;
    if (lang == 0) {
        printf("%s", "You have picked English GLHF!!! :) \n");
        printf("%s", "---------------------------------------------------\n");
        std::this_thread::sleep_for(std::chrono::seconds(2));
    } else if (lang == 1) {
        printf("%s", "Sie haben Deutsch ausgewaehlt VEVS!!! :) \n");
        printf("%s", "---------------------------------------------------\n");
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }else {
        printf("%s","Please enter a valid language \n");
        printf("%s", "---------------------------------------------------\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        _lang();
    }
}
void _reader(double vline) {
    if (lang == 0) {
        std::ifstream _engFile("ukenglish.txt");
        if (_engFile.is_open()) {
            while (std::getline(_engFile, value)) {
                values.push_back(value);
            }
            wordOfTheGame = values[vline];

        }
        _engFile.close();
    }else {
        std::ifstream _deuFile("deutsch.txt");
        if (_deuFile.is_open()) {
            while (std::getline(_deuFile, value)) {
                values.push_back(value);
            }
            wordOfTheGame = values[vline];
        }
        _deuFile.close();
    }
}
void _converter(std::string givenWord,int translator){
    char arr[givenWord.length()];
    strcpy(arr,givenWord.c_str()); // converts to letters
    for (int i = 0 ; i < givenWord.length(); i++) {
        switch (translator) {
            case(0):
                vecLetters.push_back(arr[i]);
                // std::cout << vecLetters[i] << std::endl; //release for individual letters in array <arr>
                break;
            case(1):
                vecPlayer.push_back(arr[i]);
                // std::cout << vecPlayer[i] << std::endl; //release for individual letters in array <arr>
                break;
        }
    }
}
void _markMatches() {// goal is to get GREENS first before YELLOWS and fill the rest with GREYS
    //TDL:shows yellow for repeating words that has alr been green
    //i.e. 'whiteness' & 'whiteshit' = 'white0000'
    char tempArr[wordOfTheGame.length()];
    for (int x = 0 ; x < wordOfTheGame.length(); x++) {
        tempArr[x] = '-';
    }

    for (int i = 0 ; i < wordOfTheGame.length(); i++) {
        if (vecPlayer[i] == vecLetters[i]) {
            tempArr[i] = vecLetters[i];
        }else {
            for (int y = 0 ; y < wordOfTheGame.length(); y++) {
                if (vecPlayer[i] == vecLetters[y]) {
                    tempArr[i] = '0';
                    break;
                }
            }
        }
    }

    for (int f = 0 ; f < wordOfTheGame.length(); f++) {
        std::cout << tempArr[f] << " | ";
    }
}
void _endGame() {
        printf("%s","You WON!!!! Congratulations!!! :)");
}
void _gameLogic() {
    if (start == false){
        std::cout << "Hint: '-' = not found; '0' = Word found; '#' = correct; \n"
                     "and if you quit write '/give_up'  TOTAL: " << wordOfTheGame.length() << " words\n";
        for (int i = 0 ; i < wordOfTheGame.length() ; i++)
        std::cout << "- | ";
    }
    start = true;

    if (wordOfTheGame != playerMove) {
        vecPlayer.clear();
        printf("%s", "Please enter a move: \n");
        printf("%s", "---------------------------------------------------\n");
        std::cin >> playerMove;//better way of getting input in cpp
        _converter(playerMove,1);

        /*  std::cout << "vecPlayer: ";
            for (char c : vecPlayer) std::cout << c << " ";
                std::cout << std::endl;
            std::cout << "vecLetters: ";
            for (char c : vecLetters) std::cout << c << " ";
                std::cout << std::endl;
         * vector testing
         */
        if (playerMove == "/give_up") {
            std::cout << wordOfTheGame << std::endl;
            exit(0);
        }
        _markMatches();
        _gameLogic();
    }else {
        printf("%s", "\n ---------------------------------------------------\n");
        _endGame();
    }
}
int main() {
    _lang();
    _randomGen();
    _reader(randValue);
    _converter(wordOfTheGame,0);
    _gameLogic();

    return 0;
}