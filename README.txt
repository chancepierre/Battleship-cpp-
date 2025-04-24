Video Demo: https://youtube.com/shorts/DdxeVWeGm_4?si=UE5CaM7y9O-Y7Y_I

Team Members:
- Chance Shungu, Section 12
- Joshua Leon Ortiz, Section 11
- Kwadwo Afriyie, Section 10
Game:
-Battleship with multiplayer
-Randomly placed ships
-Arial font added for easier understanding of board
-Menu at start of game
Instructions:
- Sink all 5 enemy ships to win.
- After turn player switches automatically after turn 
- Red = Hit, Gray = Miss.

Added a file font for into our file for code to read and display from 


Test cases:
Test Case 1 – Hit Detection
Description: Player 1 fires at a cell that contains a ship.
Steps:
Ensure a ship is placed at cell (0,0) for Player 2, or observe that random placement includes it.
Player 1 clicks on cell (0,0).
Expected Outcome:
Message “Hit!” is printed
Cell color changes to red
Player 1's hit count increases
Actual Outcome:
Passed

Test Case 2 – Miss Detection
Description: Player 2 fires at a cell that contains no ship.
Steps:
Player 2 clicks a known empty cell (e.g., (9,9)).
Expected Outcome:
Message “Miss.” is printed
Cell color changes to gray
Player 2’s miss count increases
Actual Outcome:
Passed

Test Case 3 – Double Shot Prevention
Description: Game prevents shooting the same cell twice.
Steps:
Player 1 clicks cell (3,3).
Player 1 clicks cell (3,3) again.
Expected Outcome:
Message “Already targeted!” is printed
Stats are not updated
Cell appearance remains the same
Actual Outcome:
Passed

Test Case 4 – Win Detection
Description: Game ends when all ships of one player are sunk.
Steps:
Player 1 hits all 17 ship cells of Player 2.
Expected Outcome:
Message “Player 1 Wins!” appears
Game no longer accepts input
Player 1’s hits equal 17
Actual Outcome:
Passed

Test Case 5 – Game Restart
Description: Clicking after a game ends starts a new game.
Steps:
Complete a game until someone wins.
Click anywhere to trigger restart.
Expected Outcome:
New ships placed for both players
All stats reset to zero
Game runs from the beginning
Actual Outcome:
Passed
