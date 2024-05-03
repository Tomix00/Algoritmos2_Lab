/*
  @file array_helpers.c
  @brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "ansicolors.h"
#include "cell.h"

#define ANSI_GRID ANSI_CYAN
#define ANSI_PLAYER ANSI_BRWHITE
#define ANSI_NORMAL ANSI_WHITE

static void draw_column_coords(void) {
    printf(ANSI_NORMAL " ");
    for (unsigned int col=0; col < COLUMNS; col++) {
        printf("   %u", col + FST_COLUMN);
    }
    printf("\n");
}

static void draw_row_coord(unsigned int row) {
    printf(ANSI_NORMAL
           "%c ", row + FST_ROW);
}

static void draw_separator(void) {
    printf(ANSI_GRID "--");
    for (unsigned int col = 0u; col < COLUMNS; ++col) {
        printf(ANSI_GRID "+---");
    }
    printf("+\n");
}

void board_draw(Board board, player_t player, unsigned int round) {
    assert(player < PLAYERS);
    printf(ANSI_PLAYER
           "Player %d:\n"
           "=========\n\n", player + FST_PLAYER);
    draw_column_coords();
    draw_separator();
    for (unsigned int row = 0u; row < ROWS ; ++row) {
        draw_row_coord(row);
        printf(ANSI_GRID "| ");
        for (unsigned int col = 0u; col < COLUMNS; ++col) {
            cell_draw(board[row][col][player], round);
            printf(ANSI_GRID " | ");
        }
        printf("\n");
        draw_separator();
    }
    printf("\n\n");
}

void array_dump(Board board) {
    for (unsigned int row = 0u; row < ROWS ; ++row) {
        for (unsigned int col = 0u; col < COLUMNS; ++col) {
            for (player_t player=player1; player < PLAYERS; ++player) {
                printf("(%c, %2u) player%d: ", row + FST_ROW, 
                                               col + FST_COLUMN,
                                               player + FST_PLAYER);
                cell_dump(board[row][col][player]);
                printf("\n");
            }
        }
        printf("\n");
    }
}

unsigned int get_points(Board board, player_t player, unsigned int round) {
    unsigned int points=0u;
    /*
     * COMPLETAR
     *
     */
    for (unsigned int row =0u;row<ROWS;row++){
        for (unsigned int column=0u;column<COLUMNS;column++){
            if(board[row][column][player].round == round && board[row][column][player].status)
            points = points + 100;
        }
    }
    return points;
}

static unsigned int max(unsigned int x, unsigned int y) {
    return x >= y ? x: y;
}

unsigned int array_from_file(Board board, const char *filepath) {
    FILE *file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    char s_row = 0;  // To store the readed symbol for row, 'A', 'B', ...
    unsigned int k_column = 0u;  // To store readed unsigned integer for column
    unsigned int check_filelines=0u; 
    unsigned int max_round=0u;  // Maximun round encountered

    while (!feof(file)){
        int res = fscanf(file,"(%c, %u)",&s_row,&k_column);
        if (res != EXPECTED_CELLDATA_FORMAT) {
            fprintf(stderr, "Error reading coordinates at line %u.\n", 
                    check_filelines + 1);
            exit(EXIT_FAILURE);
        }
        unsigned int row = s_row - FST_ROW;
        unsigned int column = k_column-FST_COLUMN;

        if ((row>ROWS) || (column>COLUMNS)){
            fprintf(stderr, "Invalid coordinates at %u.\n",check_filelines+1);
            exit(EXIT_FAILURE);
        }
        // Read data for first player cell
        cell_t player1_cell = cell_from_file(file);
        
        cell_t player2_cell = cell_from_file(file);
        
        board[row][column][0]=player1_cell;
        board[row][column][1]=player2_cell;

        max_round = max(player1_cell.round,player2_cell.round);

        check_filelines++;
    }
    
    if (check_filelines!=MAX_COORDS){
        fprintf(stderr, "Insuficientes cordenadas.\n");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    return max_round;
}
