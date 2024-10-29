#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_EDGES 30

// 간선 구조체 정의
typedef struct {
    int u, v, weight;
} Edge;

// 그래프 구조체 정의
typedef struct {
    int num_vertices;
    int num_edges;
    Edge edges[MAX_EDGES];
} GraphType;

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->num_vertices = 0;
    g->num_edges = 0;
}

void insert_edge(GraphType* g, int u, int v, int weight) {
    g->edges[g->num_edges].u = u;
    g->edges[g->num_edges].v = v;
    g->edges[g->num_edges].weight = weight;
    g->num_edges++;
}

// 예제 그래프 생성 함수 (사진 속 그래프와 동일한 구조)
void GenerateGraph(GraphType* g) {
    g->num_vertices = 10;

    insert_edge(g, 2, 5, 1);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 9, 10, 10);
    insert_edge(g, 8, 10, 15);
}

int parent[MAX_VERTICES];

void init_union_find(int n) {
    for (int i = 0; i < n; i++) parent[i] = i;
}

int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}

void union_sets(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) parent[u] = v;
}

int compare(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

void QuickKruskal(GraphType* g) {
    printf("Quick Based Kruskal\n");
    qsort(g->edges, g->num_edges, sizeof(Edge), compare);

    init_union_find(g->num_vertices);

    int edge_count = 0;
    for (int i = 0; i < g->num_edges && edge_count < g->num_vertices - 1; i++) {
        Edge e = g->edges[i];
        if (find(e.u) != find(e.v)) {
            printf("Edge (%d, %d) select %d\n", e.u, e.v, e.weight);
            union_sets(e.u, e.v);
            edge_count++;
        }
    }
    printf("\n");
}

typedef struct {
    Edge heap[MAX_EDGES];
    int size;
} MinHeap;

void init_min_heap(MinHeap* h) {
    h->size = 0;
}

void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void insert_min_heap(MinHeap* h, Edge e) {
    h->heap[h->size] = e;
    int i = h->size++;
    while (i != 0 && h->heap[i].weight < h->heap[(i - 1) / 2].weight) {
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Edge extract_min(MinHeap* h) {
    Edge root = h->heap[0];
    h->heap[0] = h->heap[--h->size];
    int i = 0, smallest = 0;
    while (i * 2 + 1 < h->size) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        if (right < h->size && h->heap[right].weight < h->heap[left].weight)
            smallest = right;
        else
            smallest = left;
        if (h->heap[i].weight <= h->heap[smallest].weight) break;
        swap(&h->heap[i], &h->heap[smallest]);
        i = smallest;
    }
    return root;
}

void MinHeapKruskal(GraphType* g) {
    MinHeap h;
    init_min_heap(&h);

    for (int i = 0; i < g->num_edges; i++) {
        insert_min_heap(&h, g->edges[i]);
    }

    init_union_find(g->num_vertices);

    printf("MinHeap Based Kruskal\n");
    int edge_count = 0;
    while (h.size > 0 && edge_count < g->num_vertices - 1) {
        Edge e = extract_min(&h);
        if (find(e.u) != find(e.v)) {
            printf("Edge (%d, %d) select %d\n", e.u, e.v, e.weight);
            union_sets(e.u, e.v);
            edge_count++;
        }
    }
    printf("\n");
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    // 그래프 생성
    GenerateGraph(g);

    // QuickSort 기반 Kruskal 알고리즘 실행
    QuickKruskal(g);

    // MinHeap 기반 Kruskal 알고리즘 실행
    MinHeapKruskal(g);

    free(g);
    return 0;
}

