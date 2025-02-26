#include <stdio.h>

#include "card_helpers.h"
#include "card.h"

#define RED_ANSI "\033[31;47m"
#define BLACK_ANSI "\033[30;47m"
#define NOCOLOR_ANSI  "\033[0m"

// Auxiliar dump functions
static void dump_suit(cardsuit_t suit) {
    printf("%s", suit==spades   ? "♠️  ":
                 suit==hearts   ? "♥️  ":
                 suit==diamonds ? "♦️  ":
                 suit==clubs    ? "♣️  ": "???");
}

static void dump_num(cardnum_t num) {
    if (1 < num && num < 11) {
        printf("%-2d", num);
    } else {
        printf("%-2s", num==1 ? "A":
                       num==11 ? "J":
                       num==12 ? "Q":
                       num==13 ? "K": "???");
    }
}

void card_dump(card c) {
    cardnum_t num=card_number(c);
    cardsuit_t suit=card_suit(c);
    if (card_color(c) == red) {
        printf(RED_ANSI);
    } else {
        printf(BLACK_ANSI);
    }

    printf("|");
    dump_num(num);
    printf(" ");
    dump_suit(suit);
    printf("|");
    printf(NOCOLOR_ANSI);
}



