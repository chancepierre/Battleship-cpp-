#pragma once
#include "libraries.hpp"
#include "shipfleet.hpp"

constexpr int BOARD_SIZE = 10;

struct Stats
{
    int hits = 0;
    int misses = 0;
    int shots = 0;
};



class Battleship
{
public:
    Battleship();
    void play();

    std::vector<std::vector<char>> playerBoard;
    std::vector<std::vector<char>> computerBoard;
    Stats playerStats, computerStats;
    std::ofstream logfile;

    void welcomeScreen();
    void initializeBoard(std::vector<std::vector<char>>& board);
    int selectWhoStarts();
    void displayBoard(const std::vector<std::vector<char>>& board, bool isPlayer);
    //void manuallyPlaceShips(std::vector<std::vector<char>>& board);
    void randomlyPlaceShips(std::vector<std::vector<char>>& board);
    bool checkShot(std::vector<std::vector<char>>& board, Stats& stats, int row, int col);
    bool isWinner(const Stats& stats) const;
    void outputCurrentMove(int row, int col, bool hit, const std::string& player);
    void outputStats(const std::string& playerName, const Stats& stats);
    void soundEffects(bool hit);
    void checkFleetHit(std::vector<std::shared_ptr<Ship>>& fleet, int row, int col);
private:
    std::vector<std::shared_ptr<Ship>> playerFleet;
    std::vector<std::shared_ptr<Ship>> computerFleet;
};
