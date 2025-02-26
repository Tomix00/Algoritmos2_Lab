#include "sorteddeck.h"
#include "card.h"
#include "card_helpers.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <assert.h>

struct s_sdeck {
    
    //completar
    struct s_node *first;
};

struct s_node {
    card c;
    cardcolor_t color;
    struct s_node *next;
};


typedef struct s_node * node_t;

static node_t create_node(card c) {
    node_t node = NULL;

    //completar;

    return node;
}

static node_t destroy_node(node_t node) {

    //completar

    return node;
}


static bool invrep(sdeck deck) {
    
    //completar
    
    return true;
}


sdeck sorteddeck_create(void) {
    sdeck deck = NULL;
    
    //completar

    assert(invrep(deck));
    return deck;
}

sdeck sorteddeck_destroy(sdeck deck) {
    
    //completar

    return deck;
}

sdeck sorteddeck_add(sdeck deck, card c) {
    assert(invrep(deck));
    
    //completar    
    
    assert(invrep(deck) && !sorteddeck_is_empty(deck));
    return deck;
}

sdeck sorteddeck_remove(sdeck deck, card c) {
    assert(invrep(deck));
    
    //completar

    assert(invrep(deck));
    return deck;
}

card sorteddeck_first(sdeck deck) {
    return deck->first->c;
}

unsigned int sorteddeck_size(sdeck deck) {

    //completar

    return 0;
}

unsigned int sorteddeck_redcount(sdeck deck) {
    
    //completar

    return 0;
}

unsigned int sorteddeck_blackcount(sdeck deck) {

    //completar

    return 0;
}

bool sorteddeck_is_empty(sdeck deck) {
    
    //completar

    return true;
}


card* sorteddeck_to_array(sdeck deck) {
    assert(invrep(deck));

    //completar

    return NULL;
}

void sorteddeck_dump(sdeck deck) {
    assert(invrep(deck));
    node_t node = deck->first;
    if (node != NULL) {
        card_dump(node->c);
        while (node->next != NULL) {
            printf(" -> ");
            node = node->next;
            card_dump(node->c);
        }
        printf("\n");
    } else {
        printf("<>\n");
    }
}

