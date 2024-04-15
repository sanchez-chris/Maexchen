# Maexchen Console Game

---

## Description:

This project involves the development of a console-based game replicating the Maexchen game in C++, without using any graphical libraries. The game is designed to run on the Windows console.

---

## Rules:


Players take turns rolling two dice using a dice cup. The player rolling the dice can tilt the cup to view the roll in secret and then announces the value of the roll, which can be freely lied about. If a player did not start the round, the announced value must be higher than that of the previous player. The concealed dice are then passed to the next player. The next player has two choices:

If they believe the previous player, they must hope to surpass their result and roll without checking the true value of the dice. Regardless of what they roll, the value they announce for the subsequent player must be higher than the last announced value - they may need to lie if necessary.

If they do not believe the previous player and accuse them of lying, the cup is lifted for all to see. If the announced value was higher than the real value of the dice, the previous player is punished for lying; if the announced value was lower or equal to the real value of the dice, the accuser is punished - usually with point deduction. The round ends when a player accuses their predecessor of lying or when no further increase in value is possible. The new round begins with the winner of the last round.

At the beginning of the game, each player typically starts with a certain number of points, for example, 10. After each round, one point is deducted from the loser's score. The game is won by the player who still has points remaining on their scorecard at the end.

There are various ways to determine the values of the dice rolls, but the most common method interprets the higher die as the tens digit and the lower die as the ones digit. The highest value is often referred to as "Mäxchen" or similar. The order is as follows: 31, 32, 41, 42, 43, 51, 52, 53, 54, 61, 62, 63, 64, 65. This is followed by pairs, such as Pair of Ones up to Pair of Sixes, and finally the value 21.

Sometimes, the game is played with two differently colored dice. One die always represents the tens digit, and the other always represents the ones digit. Apart from a longer sequence of values and a more even distribution of frequencies, there are no differences.

---

## Technologies Used:

- **C++:** The game is programmed in C++ to provide efficient and platform-independent code.

- **Windows Console:** The game utilizes the standard Windows console for rendering and user input.

---

## Installation:

1. Clone this repository to your local machine.

2. Compile the source code using a C++ compiler compatible with your system.

3. Run the executable file generated after compilation to start the game.

---

## Contributions:

Contributions are welcome! Feel free to improve this project by opening issues or sending pull requests.

---

## Authors:

- Christian Sanchez

---

## License:

This project is licensed under the MIT License. See the `LICENSE` file for more information.
