#ifndef _TESTING_H_
#define _TESTING_H_

#include "sorteddeck.h"


#define CARD_INPUT_PATTERN " %2s %c"
#define CARD_OUTPUT_PATTERN " [%2s %c]"


typedef enum {
    opt_show=1,
    opt_add,
    opt_remove,
    opt_checkempty,
    opt_length,
    opt_countcolor,
    opt_arr,
    opt_fulldeck,
    opt_clean,
    opt_exit=0
} option_t;

static const char* option_labels[]={
    [opt_show]       ="Mostrar el mazo por pantalla",
    [opt_add]        ="Agregar una carta al mazo",
    [opt_remove]     ="Sacar una carta a elección del mazo",
    [opt_checkempty] ="Verificar si el mazo está vacío",
    [opt_length]     ="Contar la cantidad de cartas en el mazo",
    [opt_countcolor] ="Contar cantidad de cartas rojas / negras",
    [opt_arr]        ="Obtener un arreglo con las cartas del mazo",
    [opt_fulldeck]   ="Cargar el mazo completo",
    [opt_clean]      ="Vaciar el mazo de cartas",
    [opt_exit]       ="Salir"
};

#define OPTIONS (sizeof(option_labels) / sizeof(*option_labels))

static const char *suit_labels[CARD_SUITS]={
    [spades]  ="picas",
    [hearts]  ="corazones",
    [diamonds]="diamantes",
    [clubs]   ="tréboles"
};

static const char suit_chars[CARD_SUITS]={
    [spades]  ='p',
    [hearts]  ='c',
    [diamonds]='d',
    [clubs]   ='t'
};

#define CARD_NUMSTR_LEN 2

static const char *number_strings[CARD_NUMS + 1]={
    "", "A",
    "2", "3","4","5","6","7","8","9","10",
    "J", "Q", "K"
};

static const char *number_labels[CARD_NUMS + 1]={
    "",
    "As",
    "2 (dos)",
    "3 (tres)",
    "4 (cuatro)",
    "5 (cinco)",
    "6 (seis)",
    "7 (siete)",
    "8 (ocho)",
    "9 (nueve)",
    "10 (diez)",
    "J (Jack)",
    "Q (Reyna)",
    "K (Rey)"
};

#endif /* _TESTING_H_ */

