/*
    MEMBROS DO GRUPO:
    Sofia Baldissera Pereira
    Eduardo Dourado Gomes Mouro de Angelo
    Fillipe Reis Tomazelli
    Tiago Francisco Moreira de Oliveira
    Joaquim Fernandes Cardoso Neto
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARQUIVO_ENTRADA "listaOdenada__1_.txt"
#define ARQUIVO_SAIDA   "lista_ordenada_saida.txt"

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void quickSort(int vetor[], int esq, int dir) {
    while (esq < dir) {
       
        int meio = esq + (dir - esq) / 2;
        int a = vetor[esq], b = vetor[meio], c = vetor[dir];
        int pivo;
        if ((a <= b && b <= c) || (c <= b && b <= a)) pivo = b;
        else if ((b <= a && a <= c) || (c <= a && a <= b)) pivo = a;
        else pivo = c;
        int i = esq, j = dir;
     
        while (i <= j) {
            while (vetor[i] < pivo) i++;
            while (vetor[j] > pivo) j--;
            if (i <= j) {
                trocar(&vetor[i], &vetor[j]);
                i++;
                j--;
            }
        }

        if (j - esq < dir - i) {
            quickSort(vetor, esq, j);
            esq = i;
        } else {
            quickSort(vetor, i, dir);
            dir = j;
        }
    }
}

int estaOrdenado(int vetor[], int n) {
    for (int i = 1; i < n; i++) {
        if (vetor[i - 1] > vetor[i]) return 0;
    }
    return 1;
}

int main(void) {

    FILE *arq = fopen(ARQUIVO_ENTRADA, "r");
    if (arq == NULL) {
        printf("Erro: nao foi possivel abrir %s\n", ARQUIVO_ENTRADA);
        return 1;
    }

    int capacidade = 1000000;
    int total_elementos = 0;
    int *vetor = malloc(capacidade * sizeof(int));
    if (vetor == NULL) {
        printf("Erro: sem memoria\n");
        return 1;
    }

    int numero;
    while (fscanf(arq, "%d", &numero) == 1) {
        if (total_elementos == capacidade) {   
            capacidade *= 2;
            int *novo = realloc(vetor, capacidade * sizeof(int));
            if (novo == NULL) {
                printf("Erro: sem memoria\n");
                free(vetor);
                return 1;
            }
            vetor = novo;
        }
        vetor[total_elementos++] = numero;
    }
    fclose(arq);
    printf("Numeros lidos: %d\n", total_elementos);

    clock_t inicio = clock();

    quickSort(vetor, 0, total_elementos - 1);

    clock_t fim = clock();
    double tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Tempo de ordenacao: %f segundos (%f ms)\n",
           tempo_gasto, tempo_gasto * 1000.0);

    if (estaOrdenado(vetor, total_elementos))
        printf("Verificacao: vetor em ordem crescente. OK!\n");
    else
        printf("Verificacao: ERRO, vetor fora de ordem!\n");

    FILE *saida = fopen(ARQUIVO_SAIDA, "w");
    if (saida != NULL) {
        for (int i = 0; i < total_elementos; i++)
            fprintf(saida, "%d\n", vetor[i]);
        fclose(saida);
        printf("Resultado salvo em %s\n", ARQUIVO_SAIDA);
    }

    free(vetor);
    return 0;
}