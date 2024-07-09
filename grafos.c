#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da lista de adjacência
typedef struct NoAdjacencia {
    int vertice;
    struct NoAdjacencia *proximo;
} NoAdjacencia;

// Definição da estrutura da lista de adjacência
typedef struct ListaAdjacencia {
    NoAdjacencia *cabeca;
} ListaAdjacencia;

// Definição da estrutura do grafo
typedef struct Grafo {
    int numVertices;
    ListaAdjacencia *listas;
} Grafo;

// Função para criar um grafo com um determinado número de vértices
Grafo* criarGrafo(int vertices) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->numVertices = vertices;
    grafo->listas = (ListaAdjacencia *)malloc(vertices * sizeof(ListaAdjacencia));
    for (int i = 0; i < vertices; i++) {
        grafo->listas[i].cabeca = NULL;
    }
    return grafo;
}

// Função para criar um novo nó de adjacência
NoAdjacencia* criarNoAdjacencia(int vertice) {
    NoAdjacencia *novoNo = (NoAdjacencia *)malloc(sizeof(NoAdjacencia));
    novoNo->vertice = vertice;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para verificar se um vértice existe no grafo
int verticeExiste(Grafo *grafo, int vertice) {
    return (vertice >= 0 && vertice < grafo->numVertices);
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(Grafo *grafo, int origem, int destino) {
    // Verificar se os vértices de origem e destino existem no grafo
    if (!verticeExiste(grafo, origem) || !verticeExiste(grafo, destino)) {
        printf("As vertices de origem ou destino nao existem no grafo.\n");
        return;
    }

    // Adicionar a aresta de origem para destino
    NoAdjacencia *novoNo = criarNoAdjacencia(destino);
    novoNo->proximo = grafo->listas[origem].cabeca;
    grafo->listas[origem].cabeca = novoNo;
    printf("Aresta adicionada com sucesso.\n");

}

// Função para buscar uma aresta no grafo
int buscarAresta(Grafo *grafo, int origem, int destino) {
    NoAdjacencia *no = grafo->listas[origem].cabeca;
    while (no != NULL) {
        if (no->vertice == destino)
            return 1; // Aresta encontrada
        no = no->proximo;
    }
    return 0; // Aresta não encontrada
}

// Função para remover uma aresta do grafo
int removerAresta(Grafo *grafo, int origem, int destino) {
    NoAdjacencia *no = grafo->listas[origem].cabeca;
    NoAdjacencia *anterior = NULL;

    while (no != NULL && no->vertice != destino) {
        anterior = no;
        no = no->proximo;
    }

    if (no == NULL) return 0; // Aresta não encontrada

    if (anterior == NULL)
        grafo->listas[origem].cabeca = no->proximo;
    else
        anterior->proximo = no->proximo;

    free(no);
    return 1; // Aresta removida com sucesso
}

// Função para liberar a memória alocada para o grafo
void liberarGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        NoAdjacencia *no = grafo->listas[i].cabeca;
        while (no != NULL) {
            NoAdjacencia *temp = no;
            no = no->proximo;
            free(temp);
        }
    }
    free(grafo->listas);
    free(grafo);
}

// Função para mostrar o grafo
void mostrarGrafo(Grafo *grafo) {
    for (int v = 0; v < grafo->numVertices; ++v) {
        NoAdjacencia *no = grafo->listas[v].cabeca;
        printf("\n Vertice %d\n esta ligada com: ", v);
        while (no) {
            printf(" %d", no->vertice);
            no = no->proximo;
        }
        printf("\n");
    }
}

// Função principal com o menu
int main() {
    int numVertices;
    printf("\n=============================================\n");
    printf("             Definindo as Vertices             ");
    printf("\n=============================================\n");
    printf("Digite o numero de Vertices do grafo --> ");
    scanf("%d", &numVertices);
    Grafo *grafo = criarGrafo(numVertices);
    int opcao, origem, destino;

    do {
        system("CLS");
        printf("\n===========================\n");
        printf("           Grafo           \n");
        printf("===========================\n");
        printf("[1] Adicionar aresta\n");
        printf("[2] Buscar aresta\n");
        printf("[3] Remover aresta\n");
        printf("[4] Mostrar grafo\n");
        printf("[0] Sair\n");
        printf("===========================\n");
        printf("Escolha uma opcao --> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("CLS");
                printf("\n=============================\n");
                printf("\n       Adicionar Aresta      \n");
                printf("\n=============================\n");
                printf("Digite a origem --> ");
                scanf("%d", &origem);
                printf("Digite o destino --> ");
                scanf("%d", &destino);
                adicionarAresta(grafo, origem, destino);
                // A mensagem de sucesso ou erro será exibida na própria função adicionarAresta
                system("PAUSE");
                break;
            case 2:
                system("CLS");
                printf("\n============================\n");
                printf("\n        Buscar Aresta       \n");
                printf("\n============================\n");
                printf("Digite a origem --> ");
                scanf("%d", &origem);
                printf("Digite o destino --> ");
                scanf("%d", &destino);
                if (buscarAresta(grafo, origem, destino))
                    printf("\nAresta encontrada.\n");
                else
                    printf("\nAresta nao encontrada.\n");
                system("PAUSE");
                break;
            case 3:
                system("CLS");
                printf("\n============================\n");
                printf("\n        Remover Aresta      \n");
                printf("\n============================\n");
                printf("Digite a origem --> ");
                scanf("%d", &origem);
                printf("Digite o destino --> ");
                scanf("%d", &destino);
                if (removerAresta(grafo, origem, destino))
                    printf("\nAresta removida com sucesso!\n");
                else
                    printf("\nAresta nao encontrada.\n");
                system("PAUSE");
                break;
            case 4:
                system("CLS");
                printf("\n===============\n");
                printf("      Grafo      ");
                printf("\n===============\n");
                mostrarGrafo(grafo);
                system("PAUSE");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                system("PAUSE");
                break;
        }
    } while (opcao != 0);

    liberarGrafo(grafo);
    return 0;
}
