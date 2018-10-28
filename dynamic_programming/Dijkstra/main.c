#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.c"

void visit(int **graph, int from, int to, int *costs, int costs_n);

int main(int argc, char *argv[]) {
    int start = 0; // A
    int end = 5; // F
    FILE *f = fopen("graph", "r");
    if (!f) {
        printf("Cannot open graph file!");
        exit(1);
    }
    int nodes_n = 7;
    int **graph = (int**) calloc(nodes_n, sizeof(int*));
    for(size_t i = 0; i < nodes_n; i++) {
        graph[i] = (int*) calloc(nodes_n, sizeof(int));
        for (size_t j = 0; j < nodes_n; j++) { 
            fscanf(f, "%d", &(graph[i][j])); 
        }
    }

    printf(" ");
    for(size_t i = 0; i < nodes_n; i++) {
        printf("  %c", (int) i + 'A');
    }
    for(size_t i = 0; i < nodes_n; i++) {
        printf("\n%c", (int) i + 'A');
        for (size_t j = 0; j < nodes_n; j++) {
            printf(" %2d", graph[i][j]);
        }
    }
    printf("\n");

    LinkedListInt *unvisited = NULL;
    for (size_t i = nodes_n - 1; i > 0; i--) {
        add(&unvisited, (int) i, graph[0][i]);
    }

    // printAsc(unvisited);

    int costs[nodes_n - 1];
    for(size_t i = 0; i < nodes_n - 1; i++) {
        // costs[i] = 99;
        costs[i] = graph[0][i + 1];
    }
    int current = start;
    while (current != end) {
        int cost = 0;
        for (int i = 0; i < nodes_n - 1 && current != 0; i++) {
            visit(graph, current - 1, i - 1, costs, nodes_n - 1);
        }
        // printAsc(unvisited);
        parseCosts(&unvisited, costs, nodes_n - 1);
        int next = minCost(&unvisited, &cost)->val;
        costs[next] += cost;
        del(&unvisited, next);
        current = next;
        // printf("next: %d, cost: %d\n", next, costs[next]);
    }

    printf("The cost of going from %c to %c: %d\n", start + 'A', end + 'A', costs[end - 1]);
    
    free(graph);
    return 0;
}

void visit(int **graph, int from, int to, int *costs, int costs_n) {
    if (from == to) return;
    // printf("Cost from %c to %c: %d\n", from + 1 + 'A', to + 1 + 'A', graph[from][to] + costs[from]);
    if (graph[from][to] + costs[from] < costs[to]) {
        costs[to] = graph[from][to] + costs[from];
    }
}