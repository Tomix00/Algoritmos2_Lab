/*
  @file cell.h
  @brief Defines a battleship board cell structure and methods
*/
#ifndef _CELL_H
#define _CELL_H

#include <stdio.h>

#define EXPECTED_CELLDATA_FORMAT 2

typedef enum {water, ship} content_t;
typedef enum {untouched, hit} status_t;
typedef enum {player1, player2} player_t;

/** @brief Type used to represent a the cell data of a battleship board.*/
typedef struct
{
    content_t content;   // ship or water
    status_t status;     // untouched or hit
    unsigned int round;  // if status is untouched must be 0
} cell_t;

/**
 * @brief reads cell data information from file line. 
 *        
 *        It could be a good idea to check that the value for <round> is in a
 *        valid range. The maximum value is determined by the size of the grid,
 *        and that definition is out of scope for this module, so it can't be
 *        validated.
 *
 *
 * @details
 * battleship board file line must contain:
 *  [<char> <int> <unsigned int>]
 *
 * @param[in] file Opened file stream
 * @return cell_t structure which contain read information from file
 */
cell_t cell_from_file(FILE* file);

/**
 * @brief dumps cell data into stdout 
 * @details
 * The line will be written using this format:
 *  [<char> <int> <unsigned int>]
 *
 * @param[in] cell the data structure with cell information
 */
void cell_dump(cell_t cell);

/**
 * @brief Display cell data using cool colors
 * @details
 *
 * @param[in] cell the data structure with cell information
 */
void cell_draw(cell_t cell, unsigned int row);

#endif //_CELL_H
