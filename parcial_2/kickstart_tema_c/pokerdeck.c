#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <assert.h>

#include "pokerdeck.h"

struct s_pokerdck {
    unsigned int cards;
    struct s_node *first;
};

struct s_node {
    cardnum_t num;
    cardsuit_t suit;
    struct s_node *nextcard;
};

typedef struct s_node * node_t;

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


// Representation invariant
static bool invrep(pokerdeck deck) {
    bool valid = false;
    
    //if(deck->first != NULL){
    //    node_t ptr_node = deck->first;
    //    bool wrong_card = false;
    //    while(ptr_node->nextcard != NULL && !wrong_card){
    //        if(ptr_node->num < CARD_NUM_FST || ptr_node->num > CARD_NUM_LST || ptr_node->suit < 0 || ptr_node->suit >CARD_SUITS){
    //            wrong_card = true;
    //        }
    //    }
    //    valid = (wrong_card) ? false : true;
    //}

    valid = (deck!=NULL);
    return valid;
}

// Creates a single node in dynamic memory with a given card
static node_t create_node(cardnum_t num, cardsuit_t suit) {
    node_t newnode=NULL;

    newnode = malloc(sizeof(struct s_node));
    newnode->num = num;
    newnode->suit = suit;
    newnode->nextcard = NULL;

    assert(newnode!=NULL);
    return newnode;
}

// Destroy a single node
static node_t destroy_node(node_t node) {

    free(node);
    node = NULL;
    //aca seguro hay leak
    assert(node==NULL);
    return node;
}

// Public functions of the Abstract Data Type
pokerdeck pokerdeck_empty(void) {

    pokerdeck deck=NULL;

    deck = malloc(sizeof(struct s_pokerdck));
    deck->cards = 0;
    deck->first = NULL;

    assert(deck != NULL);

    return deck;
}

bool pokerdeck_is_empty(pokerdeck deck) {
    
    bool res = deck->first == NULL;

    return res;
}

pokerdeck pokerdeck_add(pokerdeck deck, cardnum_t num, cardsuit_t suit) {


    node_t node = create_node(num,suit);    

    if (deck->first == NULL){

        deck->first = node;
        deck->cards++;
        

    }else{

        node_t ptr_node = deck->first;

        while(ptr_node->nextcard != NULL){
            ptr_node = ptr_node->nextcard;
        }
        
        ptr_node->nextcard = node;
        deck->cards++;
    }

    assert(!pokerdeck_is_empty(deck));

    return deck;
}

pokerdeck pokerdeck_push(pokerdeck deck,  cardnum_t num, cardsuit_t suit) {
    assert(invrep(deck));
    node_t newnode = create_node(num, suit);
    newnode->nextcard = deck->first;//no tiene sentido esto
    deck->first = newnode;
    /*
     * COMPLETAR: si fuera necesario actualizar datos de la estructura
     * principal.
     *
    */

    assert(invrep(deck) && !pokerdeck_is_empty(deck));
    return deck;
}

pokerdeck pokerdeck_pop(pokerdeck deck, cardnum_t *popped_num, cardsuit_t *popped_suit) {
    assert(!pokerdeck_is_empty(deck));

    node_t kill_node = deck->first;

    cardnum_t num = kill_node->num;
    cardsuit_t suit = kill_node->suit;
    
    deck->first = kill_node->nextcard;

    kill_node = destroy_node(kill_node);

    if (popped_num!=NULL) *popped_num= num;
    if (popped_suit!=NULL) *popped_suit= suit;
    return deck;
}

unsigned int pokerdeck_length(pokerdeck deck) {
    unsigned int size = deck->cards;

    assert(pokerdeck_is_empty(deck) == (size == 0));
    return size;
}

pokerdeck pokerdeck_remove(pokerdeck deck, cardnum_t num, cardsuit_t suit) {
    
    node_t ptr_node = deck->first;
    bool found = false;
    while(ptr_node->nextcard != NULL && !found){
        if(ptr_node->num == num && ptr_node->suit == suit){
            found = true;
        }else{
            ptr_node = ptr_node->nextcard;
        }
    }

    if(found){
        node_t kill_node = ptr_node;
        ptr_node = ptr_node->nextcard;
        kill_node = destroy_node(kill_node);
    }

    return deck;
}

unsigned int pokerdeck_count(pokerdeck deck, cardsuit_t suit) {
    unsigned int count = 0;

    printf("entre \n");
    if(deck != NULL){
        node_t ptr_node = deck->first;
        while(ptr_node->nextcard != NULL){

            if(ptr_node->suit == suit){
                count++;
            }
            ptr_node = ptr_node->nextcard;
        }
    }

    assert(count <= pokerdeck_length(deck));
    printf("sali \n");
    return count;
}

struct card * pokerdeck_to_array(pokerdeck deck) {

    struct card *array = NULL;
    unsigned int size = pokerdeck_length(deck);

    if(size != 0){
        array = calloc( size , sizeof(struct card) );
        node_t ptr_node = deck->first;

        for (unsigned int i=0; i<size;i++){

            array[i].num = ptr_node->num;
            array[i].suit = ptr_node->suit;

            ptr_node = ptr_node->nextcard;
        }
    }

    assert((pokerdeck_length(deck)==0) == (array==NULL));
    return array;
}

void card_dump(cardnum_t num, cardsuit_t suit) {
    printf("|");
    dump_num(num);
    printf(" ");
    dump_suit(suit);
    printf("|");
}

void pokerdeck_dump(pokerdeck deck) {
    assert(invrep(deck));
    node_t node = deck->first;
    while (node != NULL) {
        card_dump(node->num, node->suit);
        printf(" ");
        node = node->nextcard;
    }
    printf("\n");
}

pokerdeck pokerdeck_destroy(pokerdeck deck) {
    
    assert(invrep(deck));
    node_t ptr_node = deck->first;
    while (ptr_node != NULL) {
        node_t killme = ptr_node;
        ptr_node = ptr_node->nextcard;
        killme = destroy_node(killme);
    }
    free(deck);
    deck = NULL;
    assert(deck == NULL);
    return deck;
}

