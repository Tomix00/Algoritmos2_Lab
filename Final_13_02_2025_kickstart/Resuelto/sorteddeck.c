#include "sorteddeck.h"
#include "card.h"
#include "card_helpers.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <assert.h>

struct s_sdeck {

    unsigned int red_count;
    unsigned int black_count;
    unsigned int cards_count;
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

    node = malloc(sizeof(struct s_node));

    node->c = c;
    node->color = card_color(c);
    node->next = NULL;

    return node;
}

static node_t destroy_node(node_t node) {

    card_destroy(node->c);
    free(node);
    node = NULL;

    assert(node == NULL);
    return node;
}

//negras -> rojas
static bool invrep(sdeck deck) {
    bool valid = true;
    node_t aux = deck->first;
    cardcolor_t c;
    bool change = false;

    if (aux == NULL){
        valid = true;
        return valid;
    }else{
        c = aux->color;

        while(aux->next!= NULL && valid){
            if(aux->color != c){
                change = true;
            }
            if(aux->color==c && change){
                valid = false;
            }
            aux = aux->next;
        }
        return valid;
    }


    return valid;
}


sdeck sorteddeck_create(void) {
    sdeck deck = NULL;
    deck = malloc(sizeof(struct s_sdeck));

    deck->black_count = 0;
    deck->red_count = 0;
    deck->first = NULL;

    assert(invrep(deck));
    return deck;
}

sdeck sorteddeck_destroy(sdeck deck) {
    if(deck != NULL){
        node_t aux = deck->first;
        node_t aux2 = aux;
        if(aux != NULL){
            if(aux->next == NULL){
                aux = destroy_node(aux);
            }else{
                while(aux->next != NULL){
                    aux2 = aux;
                    aux = aux->next;
    
                    aux2 = destroy_node(aux2);
                    aux2 = NULL;
                }
            }
            free(deck);
            deck = NULL;
        }
        
    }
    return deck;
}

sdeck sorteddeck_add(sdeck deck, card c) {
    assert(invrep(deck));
     
    node_t new_node = create_node(c);
    node_t aux = deck->first;
    node_t aux2 = deck->first;
    cardcolor_t col;

    if(aux == NULL){
        deck->first = new_node;
        col = deck->first->color;
        if(col == red){
            deck->red_count++;
        }else{
            deck->black_count++;
        }
    }else{
        col = deck->first->color;

        if(col == new_node->color){
            new_node->next = aux;
            deck->first = new_node;
            if(col == red){
               deck->red_count++;
            }else{
                deck->black_count++;
            }
        }else{
            unsigned int index;
            if(col == red){
                index = deck->red_count;
            }else{
                index = deck->black_count;
            }

            if(index == sorteddeck_size(deck)){
                while(aux->next != NULL){
                    aux = aux->next;
                }
                aux->next = new_node;

                if(new_node->color == red){
                    deck->red_count++;
                }else{
                    deck->black_count++;
                }

            }else{
                for(unsigned int i=1;i<=index;i++){
                    aux2 = aux;
                    aux = aux->next;
                }
                aux2->next = new_node;
                new_node->next = aux;
                if(new_node->color == red){
                    deck->red_count++;
                }else{
                    deck->black_count++;
                }
            }
        }
    }
    
    
    
    
    assert(invrep(deck) && !sorteddeck_is_empty(deck));
    return deck;
}

sdeck sorteddeck_remove(sdeck deck, card c) {
    assert(invrep(deck));
    
    if (sorteddeck_is_empty(deck)){
        return deck;
    }

    node_t aux = deck->first;
    node_t aux2;

    if (card_equals(c,aux->c) && aux->next==NULL){
        if (card_color(c) == red){
            deck->red_count--;
        }else{
            deck->black_count--;
        }

        aux = destroy_node(aux);
        deck->first = NULL;
    }else{
        while(aux->next != NULL){
            aux2 = aux->next;
            if(card_equals(c,aux2->c)){
                if(card_color(c)==red){
                    deck->red_count--;
                }else{
                    deck->black_count--;
                }

                aux->next = aux2->next;
                aux2->next = NULL;
                aux2 = destroy_node(aux2);

                return deck;

            }
            aux = aux->next;
        }
    }

    assert(invrep(deck));
    return deck;
}

card sorteddeck_first(sdeck deck) {
    return deck->first->c;
}

unsigned int sorteddeck_size(sdeck deck) {
    return (deck->black_count+deck->red_count);
}

unsigned int sorteddeck_redcount(sdeck deck) {
    return deck->red_count;
}

unsigned int sorteddeck_blackcount(sdeck deck) {
    return deck->black_count;
}

bool sorteddeck_is_empty(sdeck deck) {
    bool b;
    b = deck->first == NULL;

    return b;
}


card* sorteddeck_to_array(sdeck deck) {
    assert(invrep(deck));

    card* array = NULL;
    node_t aux = deck->first;
    unsigned int size = sorteddeck_size(deck);

    if(size != 0){
        array = calloc( sorteddeck_size(deck) , sizeof(card*) );
        for (unsigned int i=0;i<size;i++){
            array[i] = aux->c;
            aux = aux->next;
        }
    }

    return array;
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

