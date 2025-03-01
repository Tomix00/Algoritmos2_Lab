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

static bool invrep(sdeck deck) {
    bool valid = true;
    unsigned int size;
    size = deck->black_count + deck->red_count;

    if((size>0 && deck->first == NULL) || (size==0 && deck->first != NULL)){
        valid = false;
    }

    if(size>0 && deck->first != NULL && valid){
        bool change = false;

        node_t node = NULL;
        node = deck->first;

        cardcolor_t first_color;
        first_color = node->color;
       
        unsigned int red_c = 0,black_c = 0;

        while(node!= NULL && valid){
            if(node->color == red){
                red_c++;
            }else{
                black_c++;
            }
            if(node->color != first_color){
                change = true;
            }
            if(node->color==first_color && change){
                valid = false;
            }
            node = node->next;
        }

        if(((deck->black_count != black_c) || (deck->red_count != red_c)) && valid){
            valid = false;
        }
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
    if(!sorteddeck_is_empty(deck)){
        node_t move = NULL;
        node_t kill = NULL;

        move = deck->first;
        while(move != NULL){
            kill = move;
            move = move->next;
            destroy_node(kill);
        }
    }

    free(deck);
    deck = NULL;

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

    if(!sorteddeck_is_empty(deck)){
        node_t move = NULL;
        node_t kill = NULL;

        move = deck->first;
        kill = move;

        if(card_equals(kill->c,c)){
            deck->first = kill->next;
            destroy_node(kill);

            if(card_color(c)==red){
                deck->red_count--;
            }else{
                deck->black_count--;
            }
        }else{
            bool found;

            found = false;
            kill = move->next;

            while(kill != NULL && !found){
                if(card_equals(kill->c,c)){
                    found = true;
                }else{
                    move = move->next;
                    kill = move->next;
                }
            }

            if(found){
                move->next = kill->next;
                destroy_node(kill);

                if(card_color(c)==red){
                    deck->red_count--;
                }else{
                    deck->black_count--;
                }
            }
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
        array = calloc( sorteddeck_size(deck) , sizeof(card) );
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

