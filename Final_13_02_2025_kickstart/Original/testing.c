#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "testing.h"
#include "sorteddeck.h"
#include "card_helpers.h"

// Axuliar function
void clear_stdin(void) {
    char garbage;
    while (scanf(" %c", &garbage) != 1);
}

// Show functions
void show_menu(void) {
    for (unsigned int opt=0; opt < OPTIONS; opt++) {
        if (opt!=opt_exit) {
            printf("%-2d ..... %s\n", opt, option_labels[opt]);
        }
    }
    printf("%-2d ..... %s\n", opt_exit, option_labels[opt_exit]);
}

void show_suit_ref(void) {
    for (int suit_index=0; suit_index < CARD_SUITS; suit_index++) {
        printf("%c ..... %s\n", 
                suit_chars[suit_index], suit_labels[suit_index]);
    }
    printf("\n");
}

void show_number_ref(void) {
    for (int num_index=CARD_NUM_FST; num_index <= CARD_NUM_LST; num_index++) {
        printf("%-2s ..... %s\n", 
                number_strings[num_index], number_labels[num_index]);
    }
    printf("\n");
}

void show_card_ref(void) {
    show_number_ref();
    show_suit_ref();
    printf("formato de carta: <código-num> <código-palo>\n\n");
}

// Convert functions
cardsuit_t suit_from_char(char chr_suit, bool *success) {
    assert(success!=NULL);
    cardsuit_t suit=0;
    while (suit < CARD_SUITS && chr_suit!=suit_chars[suit]) {
        suit++;
    }
    *success = suit < CARD_SUITS;
    return suit;
}

cardnum_t number_from_string(const char *str_num, bool *success) {
    assert(success!=NULL);
    cardnum_t num=CARD_NUM_FST;
    while (num <= CARD_NUM_LST && strcmp(str_num, number_strings[num]) != 0) {
        num++;
    }
    *success = num <= CARD_NUM_LST;
    return num;
}

// Functions to get input from user
cardsuit_t ask_suit(bool *success, bool testing) {
    assert(success!=NULL);
    cardsuit_t suit;
    char chr_suit;

    if (!testing) {
        show_suit_ref();
        printf("Elegi el palo:");
    }

    int res=scanf(" %c", &chr_suit);
    if (res==1) {
        suit = suit_from_char(chr_suit, success);
    } else {
        *success=false;
        clear_stdin();
    }
    return suit;
}

void ask_card(cardnum_t *num, cardsuit_t *suit, bool *success, bool testing) {
    assert(num != NULL && suit!=NULL && success!=NULL);
    bool suit_success=false, number_success=false;
    char num_str[CARD_NUMSTR_LEN + 1];
    char suit_chr_in;
    if (!testing) {
        printf("Ingrese una carta: ");
    }

    int res=scanf(CARD_INPUT_PATTERN, num_str, &suit_chr_in);
    if (res!=2) {
        fprintf(stderr, "Ingreso de carta incorrecto\n\n");
        clear_stdin();
        *success=false;
    } else {
        *suit=suit_from_char(suit_chr_in, &suit_success);
        *num=number_from_string(num_str, &number_success);
        *success = suit_success && number_success;
    }
    if (testing && *success) {
        printf(CARD_OUTPUT_PATTERN"\n",
                number_strings[*num], suit_chars[*suit]);
    }
}

// Menu functions
sdeck on_menu_exit(sdeck deck, bool testing) {
    deck = sorteddeck_destroy(deck);
    if (testing) {
        printf("OK\n");
    }
    return deck;
}

void on_checkempty(sdeck deck) {
    printf("El mazo %s vacío\n", sorteddeck_is_empty(deck) ? "está": "NO está");
}

void on_length(sdeck deck) {
    unsigned int length=sorteddeck_size(deck);
    printf("El mazo tiene %u carta%s\n", length, length ==1?"":"s");
}

void on_show(sdeck deck) {
    sorteddeck_dump(deck);
}

void on_countcolor(sdeck deck) {
    unsigned int redcount=sorteddeck_redcount(deck);
    unsigned int blackcount=sorteddeck_blackcount(deck);
    printf("Cartas rojas : %u\n"
           "Cartas negras: %u\n",  
            redcount,
            blackcount);
}

sdeck on_add(sdeck deck, bool testing) {
    cardnum_t num;
    cardsuit_t suit;
    bool success=false;
    if (!testing) {
        show_card_ref();
    }
    ask_card(&num, &suit, &success, testing);
    if (!success) {
        fprintf(stderr, "Error en carta ingresada\n\n");
    } else {
        deck = sorteddeck_add(deck, card_create(num, suit));
    }
    if (!testing) {
        sorteddeck_dump(deck);
        printf("\n");
    }
    return deck;
}

sdeck on_remove(sdeck deck, bool testing) {
    cardnum_t num;
    cardsuit_t suit;
    card aux;
    bool success=false;
    if (!testing) {
        show_card_ref();
        sorteddeck_dump(deck);
        printf("\n");
    }
    ask_card(&num, &suit, &success, testing);
    if (!success) {
        fprintf(stderr, "Error en carta ingresada\n\n");
    } else {
        deck = sorteddeck_remove(deck, aux=card_create(num, suit));
        aux = card_destroy(aux);
    }
    if (!testing) {
        sorteddeck_dump(deck);
        printf("\n");
    }
    return deck;
}

void on_arr(sdeck deck, bool testing) {
    card *arr=sorteddeck_to_array(deck);
    unsigned int length = sorteddeck_size(deck);
    if (!testing) {
        printf("Arreglo:\n\n");
    }
    printf("[");
    for (unsigned int i=0; i < length; i++) {
        printf(" %u: ", i);
        card_dump(arr[i]);
        arr[i] = card_destroy(arr[i]);
        if (i + 1 != length) printf(", ");
    }
    printf("]\n");
    free(arr);
}

sdeck on_fulldeck(sdeck deck, bool testing) {
    deck = sorteddeck_destroy(deck);
    deck = sorteddeck_create();
    for (cardsuit_t suit=0; suit < CARD_SUITS; suit++) {
        for (cardnum_t num=CARD_NUM_FST; num <= CARD_NUM_LST; num++) {
            deck = sorteddeck_add(deck, card_create(num, suit));
        }
    }
    if (testing) {
        printf("OK\n");
    }
    return deck;
}

sdeck on_clean(sdeck deck, bool testing) {
    if (!testing) {
        printf("\nDescartando mazo...\n\n");
    }
    while (!sorteddeck_is_empty(deck)) {
        card aux;
        card first = sorteddeck_first(deck);
        cardnum_t num=card_number(first);
        cardsuit_t suit=card_suit(first);
        deck = sorteddeck_remove(deck, aux=card_create(num, suit));
        aux = card_destroy(aux);
    }
    if (testing) {
        printf("\n");
    }

    return deck; 
}

// Argument handling functions
void print_help(char *program_name) {
    printf("Uso: %s [--testing\n\n]", program_name);
}

void parse_args(int argc, char *argv[], bool*testing) {
    // Default values
    *testing=false;
    // Parse arguments
    if (argc == 2 && strcmp(argv[1], "--testing")==0) {
        *testing=true;
    } else if (argc != 1) {
        print_help(argv[0]);
    }
}

int main(int argc, char *argv[]) {
    sdeck deck=sorteddeck_create();
    bool ask_exit=false, testing=false;
    // Parse arguments
    parse_args(argc, argv, &testing);
    // Begin user inteface
    while (!ask_exit) {
        unsigned int option;
        if (!testing) {
            show_menu();
        }
        if (!testing) {
            printf("\nElija una opción del menú: ");
        }
        int res = scanf("%u", &option);
        if (res==EOF || feof(stdin)) {
            fprintf(stderr, "Entrada finalizada\n\n");
            ask_exit=true;
            continue;
        } else if (res != 1 || option >= OPTIONS) {
            fprintf(stderr, "Opción incorrecta\n\n");
            clear_stdin();
            continue;
        }
        if (testing) {
            printf("%s: ", option_labels[option]);
        }
        switch (option) {
            case opt_exit      : deck=on_menu_exit(deck, testing); break;
            case opt_checkempty: on_checkempty(deck); break;
            case opt_length    : on_length(deck); break;
            case opt_show      : on_show(deck); break;
            case opt_countcolor : on_countcolor(deck); break;
            case opt_add       : deck = on_add(deck, testing); break;
            case opt_remove: deck = on_remove(deck, testing); break;
            case opt_arr     : on_arr(deck, testing); break;
            case opt_fulldeck: deck = on_fulldeck(deck, testing); break;
            case opt_clean: deck = on_clean(deck, testing); break;
        }
        if (!testing) {
            printf("\n\n");
        }
        ask_exit = option==opt_exit;
    }
    return EXIT_SUCCESS; 
}

