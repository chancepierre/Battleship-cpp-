#pragma once
#include "libraries.hpp"

constexpr int BOARD_SIZE = 10;

struct Stats 
{
    int hits = 0;
    int misses = 0;
    int shots = 0;
};

struct Ship 
{
    std::string name;
    int size;
    char symbol;
};

class Battleship 
{
public:
    Battleship();
    void play();

    std::vector<std::vector<char>> playerBoard;
    std::vector<std::vector<char>> computerBoard;
    Stats playerStats, computerStats;
    std::vector<Ship> ships;
    std::ofstream logfile;

    void welcomeScreen();
    void initializeBoard(std::vector<std::vector<char>>& board);
    int selectWhoStarts();
    void displayBoard(const std::vector<std::vector<char>>& board, bool isPlayer);
    void manuallyPlaceShips(std::vector<std::vector<char>>& board);
    void randomlyPlaceShips(std::vector<std::vector<char>>& board);
    bool checkShot(std::vector<std::vector<char>>& board, Stats& stats, int row, int col);
    bool isWinner(const Stats& stats) const;
    void outputCurrentMove(int row, int col, bool hit, const std::string& player);
    void outputStats(const std::string& playerName, const Stats& stats);
    void soundEffects(bool hit);
};
