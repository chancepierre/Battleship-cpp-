#include "Battleship.h"

Battleship::Battleship() : playerBoard(BOARD_SIZE, std::vector<char>(BOARD_SIZE, '-')),
computerBoard(BOARD_SIZE, std::vector<char>(BOARD_SIZE, '-')),

ships({
    {"Carrier", 5, 'C'},
    {"Battleship", 4, 'B'},
    {"Cruiser", 3, 'R'},
    {"Submarine", 3, 'S'},
    {"Destroyer", 2, 'D'}
    }) 

{
    logfile.open("battleship.log");
    srand(static_cast<unsigned>(time(nullptr)));
}

void Battleship::welcomeScreen() 
{
    std::cout << "Welcome to Battleship!\n"
        << "Sink all enemy ships before they sink yours.\n"
        << "Ships: Carrier(5), Battleship(4), Cruiser(3), Submarine(3), Destroyer(2).\n\n";
}

void Battleship::initializeBoard(std::vector<std::vector<char>>& board) 
{
    for (auto& row : board)

        std::fill(row.begin(), row.end(), '-');
}

int Battleship::selectWhoStarts() 
{
    return rand() % 2;
}

void Battleship::displayBoard(const std::vector<std::vector<char>>& board, bool isPlayer) 
{
    std::cout << "  ";

    for (int i = 0; i < BOARD_SIZE; ++i)

        std::cout << i << ' ';
    std::cout << '\n';

    for (int i = 0; i < BOARD_SIZE; ++i) 
    {
        std::cout << i << ' ';
        for (int j = 0; j < BOARD_SIZE; ++j) 
        {
            char c = board[i][j];
        
            if (!isPlayer && c != '-' && c != '*' && c != 'm')
                std::cout << "- ";
            
            else
                std::cout << c << ' ';
        }
        
        std::cout << '\n';
    }
}

void Battleship::manuallyPlaceShips(std::vector<std::vector<char>>& board) 
{
    for (const auto& ship : ships) 
    {
        int row, col, orientation;
    
        bool placed = false;
        
        std::cout << "Place your " << ship.name << " (" << ship.size << " cells):\n";

        while (!placed) 
        {
            std::cout << "Row, Column, Orientation (0-horizontal, 1-vertical): ";
            std::cin >> row >> col >> orientation;

            placed = true;
            if (orientation == 0 && col + ship.size <= BOARD_SIZE) 
            {
                for (int j = col; j < col + ship.size; ++j)
                    if (board[row][j] != '-') placed = false;

                if (placed)
                    for (int j = col; j < col + ship.size; ++j)
                        board[row][j] = ship.symbol;
            }
            
            else if (orientation == 1 && row + ship.size <= BOARD_SIZE) 
            {
                for (int j = row; j < row + ship.size; ++j)
                    if (board[j][col] != '-') placed = false;

                if (placed)
                    for (int j = row; j < row + ship.size; ++j)
                        board[j][col] = ship.symbol;
            }
            else 
            {
                placed = false;
            }
        }
    }
}

void Battleship::randomlyPlaceShips(std::vector<std::vector<char>>& board) 
{
    for (const auto& ship : ships) 
    {
        bool placed = false;
        while (!placed) 
        {
            int row = rand() % BOARD_SIZE, col = rand() % BOARD_SIZE, orientation = rand() % 2;
            placed = true;

            if (orientation == 0 && col + ship.size <= BOARD_SIZE) 
            {
                for (int j = col; j < col + ship.size; ++j)
                    if (board[row][j] != '-') placed = false;

                if (placed)
                    for (int j = col; j < col + ship.size; ++j)
                        board[row][j] = ship.symbol;
            }
            
            else if (orientation == 1 && row + ship.size <= BOARD_SIZE) 
            {
                for (int j = row; j < row + ship.size; ++j)
                    if (board[j][col] != '-') placed = false;

                if (placed)
                    for (int j = row; j < row + ship.size; ++j)
                        board[j][col] = ship.symbol;
            }
            else {
                placed = false;
            }
        }
    }
}

bool Battleship::checkShot(std::vector<std::vector<char>>& board, Stats& stats, int row, int col) 
{
    if (board[row][col] == '*' || board[row][col] == 'm') {
        std::cout << "Already targeted!\n";
        return false;
    }

    stats.shots++;
    bool hit = board[row][col] != '-';

    board[row][col] = hit ? '*' : 'm';
    if (hit) {
        stats.hits++;
        std::cout << "Hit!\n";
    }
    else {
        stats.misses++;
        std::cout << "Miss.\n";
    }

    return hit;
}

bool Battleship::isWinner(const Stats& stats) const {
    return stats.hits == 17;
}

void Battleship::outputCurrentMove(int row, int col, bool hit, const std::string& player) {
    logfile << player << " shot at (" << row << "," << col << ") was a " << (hit ? "hit" : "miss") << ".\n";
}

void Battleship::outputStats(const std::string& playerName, const Stats& stats) {
    float ratio = (float(stats.hits) / stats.shots) * 100;
    logfile << playerName << " - Hits: " << stats.hits << ", Misses: " << stats.misses
        << ", Shots: " << stats.shots << ", Hit Ratio: " << ratio << "%\n";
}

void Battleship::soundEffects(bool hit) 
{
    if (hit) std::cout << "\a";
}

void Battleship::play() 
{
    welcomeScreen();

    char choice;
    std::cout << "Manually place ships? (y/n): ";
    std::cin >> choice;

    (choice == 'y') ? manuallyPlaceShips(playerBoard) : randomlyPlaceShips(playerBoard);
    randomlyPlaceShips(computerBoard);

    int turn = selectWhoStarts();
    while (!isWinner(playerStats) && !isWinner(computerStats)) 
    {
        if (turn == 0) 
        {
            displayBoard(computerBoard, false);
        
            std::cout << "Your turn (row col): ";
            
            int r, c;
            
            std::cin >> r >> c;
            
            bool hit = checkShot(computerBoard, playerStats, r, c);
            
            outputCurrentMove(r, c, hit, "Player");
            
            soundEffects(hit);
        }
        
        else 
        {
        
            int r = rand() % BOARD_SIZE, c = rand() % BOARD_SIZE;
            
            bool hit = checkShot(playerBoard, computerStats, r, c);
            
            outputCurrentMove(r, c, hit, "Computer");
        }
        turn = 1 - turn;
    }

    outputStats("Player", playerStats);
    outputStats("Computer", computerStats);
    logfile.close();
}
