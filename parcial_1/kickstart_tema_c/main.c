/*
  @file main.c
  @brief Defines main program function
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "cell.h"

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path> [draw | sequence]\n\n"
           "Load a battleship match from a given file in disk.\n"
           "\n"
           "The input file must exist in disk and every line in it must have the following format:\n\n"
           "(<row>, <column>)  [<content> <status> <round>] [<content> <status> <round>]\n\n"
           "Those elements will be copied into the multidimensional array in memory.\n\n"
           "Parameters\n"
           "==========\n\n"
           "Without a second parameter it shows the data loaded.\n\n"
           "With the  'draw' option it shows a grid whith ships and shots in red.\n\n"
           "With the 'sequence' option shows step by step the progress of the game loaded.\n\n",
           program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 * @param[out] draw indicates if the 'draw' option was selected
 * @param[out] sequence indicates if the 'sequence' option was selecte
 *
 * @return An string containing read filepath
 */
char *parse_arguments(int argc, char *argv[], bool *draw, bool *sequence) {
    assert(argc > 0 && argv!=NULL && draw!=NULL);
    /* Parse the filepath given by command line argument. */
    *draw = false;
    *sequence = false;
    char *result = NULL;

    if (argc < 2) {
        fprintf(stderr, "Missing parameters!\n\n");
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    } else if (argc==3) {
        if (strcmp(argv[2], "draw") == 0) {
            *draw = true;
        } else if (strcmp(argv[2], "sequence") == 0) {
            *sequence = true;
        } else {
            fprintf(stderr, "Unrecognized parameter '%s'.\n\n", argv[2]);
            print_help(argv[0]);
            exit(EXIT_FAILURE);
        }

    } else if (argc > 3) {
        fprintf(stderr, "Too many parameters!\n\n");
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    char *filepath = NULL;
    bool draw=false, sequence=false;

    /* parse the filepath and display options given in command line arguments */
    filepath = parse_arguments(argc, argv, &draw, &sequence);

    /* create an array to store battleship board information */
    Board battleship_board;

    /* parse the file to fill the array and get the maximun round of the game */
    unsigned int max_round = array_from_file(battleship_board, filepath);

    /* show the board on the screen */
    if (draw) {
        board_draw(battleship_board, player1, max_round);
        board_draw(battleship_board, player2, max_round);
    } else if (sequence) {
        board_draw(battleship_board, player1, 0);
        board_draw(battleship_board, player2, 0);
        for (unsigned int round=0; round <= max_round; round++) {
            board_draw(battleship_board, player1, round);
            board_draw(battleship_board, player2, round + 1);
            sleep(1);
        }
    } else {
        array_dump(battleship_board);
    }
    /* Show players points */
    /*
     * EJ2: COMPLETAR
     *
     */
    unsigned int p1_points;
    unsigned int p2_points;
    for (unsigned int ronda=0u;ronda<10;ronda++){
        p1_points = p1_points + get_points(battleship_board,player1,ronda);
        p2_points = p2_points + get_points(battleship_board,player2,ronda);
    }
    printf("Points: \n");
    printf("Player 1: %u\n",p1_points);
    printf("Player 2: %u\n",p2_points);
    return (EXIT_SUCCESS);
}

