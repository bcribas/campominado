#include <stdlib.h> 
#include "fila.h"

int inicializafila(struct fila_st *f,int s) {
  f->v=malloc(sizeof(Item)*s);
  f->size=s;
  f->inicio=-1;
  f->fim=0;
  f->ocupados=0;
  return 1;
}

int enfila(struct fila_st *f, struct Item e) {
  if(f->ocupados>=f->size) return 0;
  f->v[f->fim]=e;
  f->fim=(f->fim+1)%f->size;
  f->ocupados++;
  return 1;
}

void desenfila(struct fila_st *f) {
  f->ocupados--;
  f->inicio= (f->inicio+1)%f->size;
}

struct Item espia(struct fila_st *f) {
  return f->v[(f->inicio+1)%f->size];
}

int esta_vazia(struct fila_st *f) {
  return f->ocupados==0;
}

void liberafila(struct fila_st *f) {
  free(f->v);
  f->size=0;
}


