#ifndef __FILA__
#define __FILA__

typedef struct Item {
  int l, c;
} Item;

struct fila_st {
  Item *v;
  int size;
  int inicio;
  int fim;
  int ocupados;
};

int inicializafila(struct fila_st *f,int s);
int enfila(struct fila_st *f, Item e);
void desenfila(struct fila_st *f);
Item espia(struct fila_st *f);
int esta_vazia(struct fila_st *f);
void liberafila(struct fila_st *f);
#endif
