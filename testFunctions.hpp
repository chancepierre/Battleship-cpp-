#include <SFML/Graphics.hpp>
#include "Battleship.hpp"
#include "Player.hpp"


//test 1
void testHitDetection() 
{
    std::cout << "Running Test Case 1 Hit Detection\n";

    Battleship game;

    // Force known ship placement at (0,0)
    game.initializeBoard(game.computerBoard);
    game.computerBoard[0][0] = 'D'; // Place a Destroyer part at (0,0)

    int initialHits = game.playerStats.hits;

    bool hit = game.checkShot(game.computerBoard, game.playerStats, 0, 0);


    std::cout << "Expected: Hit!\n";
    std::cout << "Actual:   " << (hit ? "Hit!" : "Miss.") << "\n";


    char cell = game.computerBoard[0][0];
    std::cout << "Expected Cell Value: *\n";
    std::cout << "Actual Cell Value:   " << cell << "\n";

    int expectedHits = initialHits + 1;
    std::cout << "Expected Hit Count: " << expectedHits << "\n";
    std::cout << "Actual Hit Count:   " << game.playerStats.hits << "\n";


    if (hit && cell == '*' && game.playerStats.hits == expectedHits) {
        std::cout << "Test Case 1: passed \n";
    }
    else {
        std::cout << "Test Case 1: failed\n";
    }

    std::cout << "--------------------------------------\n";
}



//test 2
void testMissDetection() {
    std::cout << "Running Test Case 2 Miss Detection\n";

    Battleship game;
    game.initializeBoard(game.playerBoard);
    game.playerBoard[9][9] = '-'; // Ensure empty cell

    int initialMisses = game.computerStats.misses;
    bool hit = game.checkShot(game.playerBoard, game.computerStats, 9, 9);

    std::cout << "Expected: Miss.\n";
    std::cout << "Actual:   " << (hit ? "Hit!" : "Miss.") << "\n";
    std::cout << "Expected Miss Count: " << (initialMisses + 1) << "\n";
    std::cout << "Actual Miss Count:   " << game.computerStats.misses << "\n";

    if (!hit && game.playerBoard[9][9] == 'm' &&
        game.computerStats.misses == initialMisses + 1) {
        std::cout << "Test Case 2: passed\n";
    }
    else {
        std::cout << "Test Case 2: failed \n";
    }

    std::cout << "--------------------------------------\n";
}//test 3
void testDoubleShotPrevention() {
    std::cout << "Running Test Case 3 Double Shot Prevention\n";

    Battleship game;
    game.initializeBoard(game.computerBoard);
    game.computerBoard[3][3] = 'D';

    game.checkShot(game.computerBoard, game.playerStats, 3, 3); // first shot
    int shotsBefore = game.playerStats.shots;
    bool secondShot = game.checkShot(game.computerBoard, game.playerStats, 3, 3); // second shot (same place)

    std::cout << "Expected: Already targeted!\n";
    std::cout << "Second shot registered: " << (secondShot ? "Yes" : "No") << "\n";
    std::cout << "Expected Shot Count: " << shotsBefore << "\n";
    std::cout << "Actual Shot Count:   " << game.playerStats.shots << "\n";

    if (!secondShot && game.playerStats.shots == shotsBefore) {
        std::cout << "Test Case 3:passed \n";
    }
    else {
        std::cout << "Test Case 3: failed\n";
    }

    std::cout << "--------------------------------------\n";
}


//test 4
void testWinDetection() {
    std::cout << "Running Test Case 4 Win Detection\n";

    Battleship game;
    game.initializeBoard(game.computerBoard);

    // simulate 17 hits
    for (int i = 0; i < 17; ++i) {
        game.playerStats.hits++;
    }

    bool winner = game.isWinner(game.playerStats);
    std::cout << "Expected: Player 1 Wins!\n";
    std::cout << "Actual:   " << (winner ? "Player 1 Wins!" : "Game Continues") << "\n";

    if (winner) 
    {
        std::cout << "Test Case 4:passed\n";
    }
    else {
        std::cout << "Test Case 4: failed\n";
    }

    std::cout << "--------------------------------------\n";
}
//test 5
void testGameRestart() {
    std::cout << "Running Test Case 5 Game Restart\n";

    Battleship game;
    game.playerStats.hits = 17; // Simulate win

    // Restart the game
    game = Battleship();  // Triggers constructor

    bool allReset = game.playerStats.hits == 0 &&
        game.playerStats.shots == 0 &&
        game.playerStats.misses == 0;

    std::cout << "Expected: Game reset\n";
    std::cout << "Hits: " << game.playerStats.hits
        << ", Shots: " << game.playerStats.shots
        << ", Misses: " << game.playerStats.misses << "\n";

    if (allReset) 
    {
        std::cout << "Test Case 5: passed\n";
    }
    else
    {
        std::cout << "Test Case 5: failed\n";
    }

    std::cout << "--------------------------------------\n";
}