#pragma once

#define MAX_VERTICES 11  // 최대 정점 수

// 그래프 구조체 정의
typedef struct GraphMatType {
    int adj_mat[MAX_VERTICES][MAX_VERTICES];  // 인접 행렬
    int vertex_list[MAX_VERTICES];            // 정점 존재 여부
} GraphMatType;

// 함수 선언
extern GraphMatType* create_mat_graph();
extern void init_mat_graph(GraphMatType* g);
extern void insert_vertex_mat_graph(GraphMatType* g, int v);
extern void insert_edge_mat_graph(GraphMatType* g, int s, int e);
extern void dfs(GraphMatType* g, int start, int target);
extern void bfs(GraphMatType* g, int start, int target);
extern void destroy_mat_graph(GraphMatType* g);

