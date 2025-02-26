#ifndef _CARD_H_
#define _CARD_H_

#include <stdbool.h>

typedef enum {
    spades,   // Black
    hearts,   // Red
    diamonds, // Red
    clubs     // Black
} cardsuit_t;

#define CARD_SUITS 4

typedef enum {
    ace=1,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king
} cardnum_t;

#define CARD_NUM_FST 1
#define CARD_NUM_LST 13

#define CARD_NUMS (CARD_NUM_LST - CARD_NUM_FST + 1)

typedef enum {red, black} cardcolor_t;

typedef struct s_card * card;

card card_create(cardnum_t num, cardsuit_t suit);

card card_destroy(card c);

cardcolor_t card_color(card c);

cardnum_t card_number(card c);

cardsuit_t card_suit(card c);

bool card_equals(card c1, card c2);


#endif

