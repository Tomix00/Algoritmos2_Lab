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

bool goes_before( player_t x, player_t y){
    bool result;

    result = (*x).rank <= (*y).rank;

    return result;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap(player_t a[], unsigned int i, unsigned j){
    player_t aux;
    
    aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
  unsigned int i,j;
  unsigned int ppiv = izq;
  i = izq+1;
  j = der;
  
  while(i<=j){
    if(goes_before(a[i],a[ppiv])){
      i = i+1;
    }
    else{
      if(goes_before(a[ppiv],a[j])){
        j = j-1;
      }
      else{
        if((!goes_before(a[i],a[ppiv]))&&(!goes_before(a[ppiv],a[j]))){
          swap(a,i,j);
        }
      }
    }
  }
  swap(a,ppiv,j);
