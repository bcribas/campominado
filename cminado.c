// Campo Minado implementado em sala com os alunos de EDA1 da UnB/FGA
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct cel_st {
  char valor;
  char status;
};

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

int inicializafila(struct fila_st *f,int s) {
  f->v=malloc(sizeof(Item)*s);
  f->size=s;
  f->inicio=-1;
  f->fim=0;
  f->ocupados=0;
  return 1;
}

int enfila(struct fila_st *f,Item e) {
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

Item espia(struct fila_st *f) {
  return f->v[(f->inicio+1)%f->size];
}

int esta_vazia(struct fila_st *f) {
  return f->ocupados==0;
}

#define N 10
#define posvalida(a,b) (a>=0 && a<N && b>=0 && b<N)
struct cel_st campo[N][N];

void inicializacampo() {
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      campo[i][j]= (struct cel_st) {'\0','\0'};
}

void imprimecampo() {
  printf("\033[0;0H");
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++)
      if(campo[i][j].status<=0)
        printf("#");
      else {
        printf("%c",'0'+campo[i][j].valor);
      }
    printf("\n");
  }
  usleep(500000);
}
void imprimecampoCHEAT() {
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++)
      printf("%c",'0'+campo[i][j].valor);
    printf("\n");
  }
}

#define MAXBOMBS 2
void firstclick(int l,int c) {
  campo[l][c].status=1;
  srand(time(NULL));
  for(int b=0;b<MAXBOMBS;b++)
  {
    int pl=rand()%N;
    int pc=rand()%N;
    while(campo[pl][pc].status!=0 ||
          campo[pl][pc].valor==9) {
      pl=rand()%N;
      pc=rand()%N;
    }
    campo[pl][pc].valor=9;
    for(int i=pl-1;i<pl+2;i++)
      for(int j=pc-1;j<pc+2;j++)
      {
        if(!posvalida(i,j)) continue;
        if(campo[i][j].valor==9) continue;
        campo[i][j].valor++;
      }
  }
}

void liberafila(struct fila_st *f) {
  free(f->v);
  f->size=0;
}

void abreclick(int l,int c) {
  struct fila_st f;
  Item e;
  e.l=l;
  e.c=c;
  if(campo[l][c].valor>0){
    campo[l][c].status=1;
    imprimecampo();
    return;
  }
  inicializafila(&f,N*N);
  enfila(&f,e);

  while(!esta_vazia(&f)) {
   e=espia(&f);
   campo[e.l][e.c].status=1;
   imprimecampo();
   desenfila(&f);
   for(int i=e.l-1;i<e.l+2;i++)
     for(int j=e.c-1;j<e.c+2;j++)
     {
       if(!posvalida(i,j)) continue;
       if(campo[i][j].status==0 && campo[i][j].valor==0) {
         campo[i][j].status=-1;
         Item xx;
         xx.l=i;
         xx.c=j;
         enfila(&f,xx);
       }
     }
  }
  liberafila(&f);
}
int main(void)
{
  inicializacampo();
  imprimecampo();
  int l,c;
  scanf("%d %d",&l,&c);
  firstclick(l,c);
  abreclick(l,c);
  imprimecampo();
  while(scanf("%d %d", &l,&c)==2) {
    if(!posvalida(l,c)) { printf("COLOQUE LUGAR CERTO DATEBAYO\n");exit(1);}
    abreclick(l,c);
  }
  //printf("\n\n");
  //mprimecampoCHEAT();
  return 0;
}
