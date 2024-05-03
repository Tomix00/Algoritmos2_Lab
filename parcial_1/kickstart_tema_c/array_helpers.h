/*
  @file array_helpers.h
  @brief defines array helpers methods. These methods operates over multidimensional (ROWS, COLUMNS, PLAYERS) array of battleship cells
*/
#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>
#include "cell.h"


#define FST_COLUMN 1   // First column
#define FST_ROW 'A'    // First row of the board, to be used as a number value
#define FST_PLAYER 1   // First player


#define ROWS 10     // Sets the number of rows of the board
#define COLUMNS 10  // Sets the number of columns of the board
#define PLAYERS 2   // Sets the number of players in the board


#define MAX_COORDS (ROWS * COLUMNS)  // Inidcates how many different coordinates are
#define MAX_ROUNDS MAX_COORDS        // The maximun round posible.

typedef cell_t Board [ROWS][COLUMNS][PLAYERS];

/**
 * @brief Write the content of the array 'a' into stdout.
 * @param[in] a array to dump in stdout
 */
void array_dump(Board a);

/**
 * @brief Display the battleship board <board> of the player <player> into
 *        stdout with cool colors, discarding shots made after the round <round>.
 *
 * @param[in] board an array with de board data of a battleship game.
 * @param[in] player indicates which player's board will be displayed.
 * @param[in] round indicates until which turn will be taken into account.
 *
 */
void board_draw(Board board, player_t player, unsigned int round);


/**
 * @brief calculates the total points earned by player <player> up to round
 *        <round> as indicated by the game stored in <board>. Each shot that
 *        hits an opponent's ship must be worth 100 points.
 *
 *
 * @param[in] board an array with de board data of a battleship game.
 * @param[in] player indicates which player
 * @param[in] round indicates until which turn will be taken into account.
 *
 * @return the points of player <player> at round <round>
 */
unsigned int get_points(Board board, player_t player, unsigned int round);

/**
 * @brief reads an array with board information of a battleship game saved in a file
 * @details
 *
 *  Each element is read from the file located at 'filepath'.
 *  The file must exist in disk and must have its contents in a sequence of
 *  lines, each with the following format:
 *
 *   [<row> <column>] [<content> <status> <round>] [<content> <status> <round>]
 *
 *   Those elements are copied into the multidimensional array 'a'.
 *
 * @param a array which will contain read file
 * @param filepath file with battleship board data
 *
 * @return the maximun value for <round> in the given file
 */
unsigned int array_from_file(Board a, const char *filepath);

#endif
