/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool state = true;
    if (x.rank > y.rank){
        state = false;
    }
    return state;
}

void swap(player_t a[],unsigned int i,unsigned int j){
    player_t aux;
    aux = a[i];
    a[i]=a[j];
    a[j]=aux;
}

unsigned int partition(player_t a[],unsigned int left,unsigned int right){
    unsigned int ppiv,i,j;
    ppiv = left;
    i=left +1;
    j=right;
    while(i<=j){
        if(goes_before(a[i],a[ppiv])){
            i++;
        }else if(goes_before(a[ppiv],a[j])){
            j--;

        }else if(goes_before(a[ppiv],a[i]) && goes_before(a[j],a[ppiv])){
            swap(a,i,j);
            i++;
            j--;
        }
    }
    swap(a,ppiv,j);
    ppiv = j;
    return ppiv;
}

void quicksort(player_t a[], unsigned int left,unsigned int right){
    unsigned int ppiv;
    if(right>left){
        ppiv = partition(a,left,right);

        quicksort(a,left,(ppiv==0) ? 0 : ppiv -1);
        quicksort(a,ppiv+1,right);
    }

}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void sort(player_t a[], unsigned int length) {
    quicksort(a,0,length);
}

