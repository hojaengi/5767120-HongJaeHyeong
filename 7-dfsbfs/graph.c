#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // bool, true, false 사용을 위해 포함
#include "graph.h"

// 인접 행렬 그래프 생성
GraphMatType* create_mat_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}

// 그래프 메모리 해제
void destroy_mat_graph(GraphMatType* g) {
    free(g);
}

// 그래프 초기화
void init_mat_graph(GraphMatType* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->vertex_list[i] = 0;
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// 정점 삽입
void insert_vertex_mat_graph(GraphMatType* g, int v) {
    if (v >= MAX_VERTICES) {
        fprintf(stderr, "정점 번호가 범위를 벗어났습니다: %d\n", v);
        return;
    }
    g->vertex_list[v] = 1;
}

// 간선 삽입
void insert_edge_mat_graph(GraphMatType* g, int s, int e) {
    if (g->vertex_list[s] == 0 || g->vertex_list[e] == 0) {
        fprintf(stderr, "간선을 삽입할 수 없습니다: %d 또는 %d 정점이 존재하지 않습니다.\n", s, e);
        return;
    }
    g->adj_mat[s][e] = 1;
    g->adj_mat[e][s] = 1;
}

// 깊이 우선 탐색 (DFS)
void dfs(GraphMatType* g, int start, int target) {
    bool visited[MAX_VERTICES] = {false};
    int stack[MAX_VERTICES], top = -1;
    int visited_count = 0;
    bool found = false;

    stack[++top] = start;
    printf("DFS 탐색 수행...\n");

    while (top >= 0) {
        int node = stack[top--];

        if (!visited[node]) {
            printf("%d ", node);  // 방문한 노드 출력
            visited[node] = true;
            visited_count++;

            if (node == target) {
                found = true;
                break;
            }

            for (int i = MAX_VERTICES - 1; i >= 0; i--) {
                if (g->adj_mat[node][i] && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }

    if (found) {
        printf("\n탐색 성공: %d\n", target);
    } else {
        printf("\n탐색 실패: %d\n", target);
    }
    printf("방문한 노드의 수: %d\n", visited_count);
}

// 너비 우선 탐색 (BFS)
void bfs(GraphMatType* g, int start, int target) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES], front = 0, rear = 0;
    int visited_count = 0;
    bool found = false;

    queue[rear++] = start;
    printf("BFS 탐색 수행...\n");

    while (front < rear) {
        int node = queue[front++];

        if (!visited[node]) {
            printf("%d ", node);  // 방문한 노드 출력
            visited[node] = true;
            visited_count++;

            if (node == target) {
                found = true;
                break;
            }

            for (int i = 0; i < MAX_VERTICES; i++) {
                if (g->adj_mat[node][i] && !visited[i]) {
                    queue[rear++] = i;
                }
            }
        }
    }

    if (found) {
        printf("\n탐색 성공: %d\n", target);
    } else {
        printf("\n탐색 실패: %d\n", target);
    }
    printf("방문한 노드의 수: %d\n", visited_count);
}

