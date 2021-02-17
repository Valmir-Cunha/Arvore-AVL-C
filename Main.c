#include <stdio.h>
#include <stdlib.h>

struct no {
    int info;
    struct no *esq;
    struct no *dir;
};
typedef struct no No;

//==========Funções=======

No** criarRaiz(){
    No **aux;
    aux = (No**) malloc(sizeof(No));
    if(aux != NULL){
        (*aux) = NULL;
    }
    return aux;
}
No* criarNo(){
    No *aux;
    aux = (No*) malloc(sizeof(No));
    if(aux == NULL){
        return 0;
    }
    return aux;
}

void emOrdem (No **tree){
    if((*tree) == NULL){
        return;
    }
    emOrdem(&((*tree)->esq));
    printf("%d ",(*tree)->info);
    emOrdem(&((*tree)->dir));
}

int altura (No *tree){
    if(tree == NULL){
        return 0;
    }
    int tot_esq = altura(tree->esq);
    int tot_dir = altura(tree->dir);
    if (tot_esq > tot_dir)
        return (tot_esq + 1);
    else
        return(tot_dir + 1);
}

int balanceamento (No *tree){ 
    if (tree == NULL){
        return 0;
    }
    int d = altura(tree->dir);
    int e = altura(tree->esq);
    int b = d - e;
    return b;
}

//======================Rotações============================

void rotacaoSE(No **tree){
    No *aux;
    aux = (*tree)->dir;
    (*tree)->dir = aux->esq;
    aux->esq = (*tree);
    (*tree) = aux;
    
}

void rotacaoSD(No **tree){
    No *aux;
    aux = (*tree)->esq;
    (*tree)->esq = aux->dir;
    aux->dir = (*tree);
    (*tree) = aux;
}

void rotacaoDE(No **tree){
    rotacaoSE(&((*tree)->esq));
    rotacaoSD(&(*tree));
}

void rotacaoDD(No **tree){
    rotacaoSD(&((*tree)->dir));
    rotacaoSE(&(*tree));
}

void inserir (No **tree, int dado){
    if((*tree) == NULL){
        (*tree) = criarNo();
        (*tree)->info = dado;
        (*tree)->esq = NULL;
        (*tree)->dir = NULL;
    } 
    else if(dado < (*tree)->info){
        int x;
        inserir(&((*tree)->esq),dado);
        x = balanceamento(*tree);
        if(x < -1){
            int y;
            y = balanceamento((*tree)->esq);
            if (y <= -1){
                rotacaoSD(&((*tree)));
            }
            else if(y >= 1){
                rotacaoDE(&((*tree)));
            }
        }
    }
    else if (dado > (*tree)->info){
        int x;
        inserir(&((*tree)->dir),dado);
        x = balanceamento(*tree);
        if (x > 1){
            int y;
            y = balanceamento((*tree)->dir);
            if (y >= 1){
                rotacaoSE(&((*tree)));
            }
            else if(y <= -1){
                rotacaoDD(&((*tree)));
            }   
        }
        
    }
    else{
        printf("Elemento existente: %d\n",dado);
    }
}

No* maiorEsq(No *n){
    No *aux;
    aux = n;
    while (aux != NULL){
        n = aux;
        aux = aux->dir;
    }
    free(aux);
    return n;
    
}

void remover(No **tree, int dado){
    if((*tree != NULL)){
        int x;
        if(dado < (*tree)->info){
            remover(&(*tree)->esq,dado);
            x = balanceamento(*tree);
            if(x < -1){
            int y;
            y = balanceamento((*tree)->esq);
            if (y <= -1){
                rotacaoSD(&((*tree)));
            }
            else if(y >= 1){
                rotacaoDE(&((*tree)));
            }
        }
        }
        else if(dado > (*tree)->info){
            remover(&(*tree)->dir,dado);
            x = balanceamento(*tree);
            if (x > 1){
                int y;
                y = balanceamento((*tree)->dir);
                if (y >= 1){
                    rotacaoSE(&((*tree)));
                }
                else if(y <= -1){
                    rotacaoDD(&((*tree)));
                }   
            }
        }
        else if(dado == (*tree)->info){
            if (((*tree)->esq == NULL) && ((*tree)->dir == NULL)){
                free((*tree));
                (*tree) = NULL;
            }else if(((*tree)->esq == NULL) && ((*tree)->dir != NULL)){
                (*tree) = (*tree)->dir; 
            }else if(((*tree)->esq != NULL) && ((*tree)->dir == NULL)){
                (*tree) = (*tree)->esq;
            }else{
                No *aux;
                aux = maiorEsq((*tree)->esq);
                (*tree)->info = aux->info;
                remover(&((*tree)->esq),aux->info);
                free(aux);
            }
        }
        else{
            printf("Elemento não encontrado");
        }
    }
}




int main()
{
    printf("Hello world!\n");
    int x;
    No **tree;
    tree = criarRaiz();
    inserir(tree,15);
    inserir(tree,10);
    inserir(tree,9);
    inserir(tree,4);
    inserir(tree,7);
    inserir(tree,21);
    x = balanceamento((*tree));
    printf("Balanceamento: %d\n",x);
    emOrdem(tree);
    printf("\n");
    remover(tree,7);
    //remover(tree,15);
    printf("Em ordem: ");
    emOrdem(tree);
    x = balanceamento((*tree));
    printf("\nBalanceamento: %d\n",x);
    return 0;
}
