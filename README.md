Tafl C++ - A Strategic Board Game
Created by Mihail Georgiev

This project is a C++ implementation of Tafl, a traditional and ancient strategy board game. The game features two opposing sides: The Attacker and The Defender. Players alternate turns, each with distinct rules and objectives, as they seek to either capture the King or help them escape.

Game Overview
Tafl is a two-player strategy game played on a grid-based board. One side plays as the Defender, tasked with protecting the King, while the other side plays as the Attacker, trying to capture the King.

Objective
Defender: The main goal of the Defender is to move the King to one of the board’s corner squares to escape and win the game.
Attacker: The Attacker’s goal is to surround the King on all four sides, capturing it to win the game.
Features
1. Customizable Board Sizes
Choose the ideal board size to suit your preference. Available sizes are:

7x7
9x9
11x11
13x13
2. Piece Types
The game includes several types of pieces with unique roles and abilities:

Defenders: The pieces controlled by the Defender player. They aim to protect the King.
Attackers: The pieces controlled by the Attacker player. Their goal is to capture the King.
King: A special piece controlled by the Defender. It must be protected or guided to a corner to win the game.
3. Command List
Players can interact with the game through a set of predefined commands:

1. Clear screen & print board: Refresh the board display and show the current state of the game.
2. Quit the game: Exit the game.
3. Move a piece: Select and move a piece to a new position on the board. Valid moves depend on the piece type and the current game state.
4. Undo the last move (Back): Revert the previous move, allowing players to try a different strategy.
5. Get help (explanation of rules and controls): Display a help section outlining commands.
6. Display game information (Info): Show additional game details, such as current player turn, pieces left, and board size.
4. Game Logic
The game logic encompasses the following key elements:

Piece Movement: Each type of piece (Defender, Attacker, and King) has movement rules. Pieces move along the board’s grid, like a rook in chess.

Capture Mechanics: Logic for capturing regular pieces and the King that should be surrounded by attackers from all sides to be captured.

King’s Escape: The King can escape by moving to one of the corner squares. To win, the Defender must get the King to a corner square, while the Attacker must prevent this by surrounding the King.

Alternating Turns: The game alternates between the Attacker and Defender players, each making moves in their turn.

Player Interaction
The game requires active participation from both players:

The Attacker tries to encircle the King and prevent its escape.
The Defender strives to keep the King safe, either by blocking the Attackers or guiding the King to one of the corners of the board.
During their turn, players can choose from a set of commands to make moves or access game information.

Win Conditions
Attacker Wins: The Attacker wins by completely surrounding the King on all four sides.
Defender Wins: The Defender wins if they manage to move the King to one of the corner squares on the board.
Stalemate: A player has no more legal available moves, so they lose the game.
Game Flow
Start the Game: Players choose board size. The game begins with the Attacker moving first.
Alternating Turns: Players take turns moving their pieces.
Endgame: The game concludes when either the King escapes to a corner (Defender wins) or is captured (Attacker wins) or by stalemate if either side has no available legal moves.
