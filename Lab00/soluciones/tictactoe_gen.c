#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define T 3 //tamaño de la grilla en fila y columna

//separador de filas
void separador(int tam){
    printf("\t ");
    for (int i=0; i<tam ; i++){
        printf("................");
    }
    printf("\n");
}

//graficadora de la grilla con tamaño T*T
void draw_board(char board[T][T]){
    int cell = 0;

    separador(T);
    for (int row=0; row<T;++row){
        for (int column=0;column<T;++column){
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        separador(T);
    }
}

//verifica si hay algun ganador en cada turno
char get_winner(char board[T][T]){
    char winner = '-';
    
    //diagonal
    int row=0,column=0,count_x=0,count_o=0;
    while (row<T && winner=='-'){
        if (board[row][row]=='X'){
            count_x++;
            if (count_x==T){
                winner = 'X';
            }
        }else if(board[row][row]=='O'){
            count_o++;
            if (count_o==T){
                winner = 'O';
            }
        }
        row++;
    }

    //anti-diagonal
    count_x=0,count_o=0,row=0,column = T-1;
    while (row<T && column>-1 && winner=='-'){
        if (board[row][column]=='X'){
            count_x++;
            if (count_x==T){
                winner='X';
            }
        }else if (board[row][column]=='O'){
            count_o++;
            if (count_o==T){
                winner='O';
            }
        }
        row++;
        column--;
    }

    //horizontal
    row=0;
    bool win_x=true,win_o=true;
    while (row<T && winner=='-'){
        for(column=0;column<T;column++){
            win_x = win_x && (board[row][column]=='X');
        }
        for(column=0;column<T;column++){
            win_o = win_o && (board[row][column]=='O');
        }

        if (win_x){
            winner = 'X';
        }else if(win_o){
            winner = 'O';
        }
        row++;
        win_x=true,win_o=true;
    }

    //vertical
    column=0;
    win_x=true,win_o=true;
    while (column<T && winner=='-'){
        for(row=0;row<T;row++){
            win_x = win_x && (board[row][column]=='X');
        }
        for(row=0;row<T;row++){
            win_o = win_o && (board[row][column]=='O');
        }

        if (win_x){
            winner = 'X';
        }else if(win_o){
            winner = 'O';
        }
        column++;
        win_x=true,win_o=true;
    }
    
    return winner;
}

//verifica si queda lugar disponible para un turno
bool has_free_cell(char board[T][T]){
    bool free_cell = false;
    int row =0,column=0;

    while (row<T){
        while (column<T){
            free_cell = free_cell || (board[row][column]=='-');
            column++;
        }
        row++;
        column=0;
    }
    return free_cell;
}

int main(void){
    printf("TicTacToe incompleto. \n");

    char board[T][T];
    int row=0,column=0;
    int cell_max = (T*T-1);
    
    //frame de la board con tamaño T*T
    while (row<T){
        while(column<T){
            board[row][column] = '-';
            column++;
        }
        row++;
        column=0;
    }
    
    //game loop
    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)){
        draw_board(board);
        printf("\nTurno %c - Elija posicion (numero del 0 al %d): ", turn,cell_max);

        int result = scanf("%d",&cell);
        if (result <= 0){
            printf("Error al leer un numero desde teclado\n");
            exit(EXIT_FAILURE);
        }
        
        if (cell >=0 && cell<=cell_max){
            row = cell/T;
            column = cell % T;
            if (board[row][column] == '-'){
                board[row][column] = turn;
                turn = turn =='X' ? 'O' : 'X';
                winner = get_winner(board);
            }else{
                printf("\nCelda ocupada!\n");
            }
        }else{
            printf("\nCelda invalida!\n");
        }
    }

    //muestra la grilla y dice quien gano o si hubo empate
    draw_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Gano %c\n", winner);
    }
    return 0;
}

