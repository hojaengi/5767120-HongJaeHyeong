#include <stdio.h>
#include <limits.h>

#define V 10  // 그래프의 정점 수, 예를 들어 10개의 노드
#define INF INT_MAX

// 최단 거리를 갖는 노드를 찾는 함수
int minDistance(int dist[], int found[]) {
    int min = INF, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!found[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Dijkstra 알고리즘 구현
void dijkstra(int graph[V][V], int src) {
    int dist[V];   // 최단 거리를 저장하는 배열
    int found[V];  // 방문 상태를 저장하는 배열 (0: 방문 X, 1: 방문 O)
    int order[V];  // 노드의 방문 순서를 저장하는 배열
    int order_index = 0;

    // 초기화: 모든 거리를 무한대로 설정하고 방문 배열을 0으로 초기화
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        found[i] = 0;
    }
    dist[src] = 0;

    // 모든 정점에 대해 Dijkstra 알고리즘을 수행
    for (int count = 0; count < V; count++) {
        int u = minDistance(dist, found);  // 방문하지 않은 노드 중 최단 거리 노드를 선택
        if (u == -1) break;  // 더 이상 방문할 노드가 없으면 중단
        found[u] = 1;
        order[order_index++] = u + 1;  // 순서를 저장 (노드 번호 1부터 시작)

        // 방문한 노드를 기준으로 인접한 노드의 거리를 업데이트
        for (int v = 0; v < V; v++) {
            if (!found[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }

        // 중간 결과 출력
        printf("Distance: ");
        for (int i = 0; i < V; i++) {
            if (dist[i] == INF)
                printf("* ");
            else
                printf("%d ", dist[i]);
        }

        printf("\nFound: ");
        for (int i = 0; i < V; i++) {
            printf("%d ", found[i]);
        }
        printf("\n\n");
    }

    // 방문 순서 출력
    printf("Found Order: ");
    for (int i = 0; i < order_index; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");
}

int main() {
    // 그래프의 인접 행렬 (예제에 맞게 가중치를 수정)
    int graph[V][V] = {
        {0, 3, 8, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 0, 7, 0, 1, 0, 0, 0, 0},
        {8, 0, 0, 0, 2, 0, 5, 6, 0, 0},
        {0, 7, 0, 0, 4, 0, 0, 3, 0, 0},
        {0, 0, 2, 4, 0, 9, 0, 0, 13, 0},
        {0, 1, 0, 0, 9, 0, 0, 0, 10, 0},
        {0, 0, 5, 0, 0, 0, 0, 6, 0, 15},
        {0, 0, 6, 3, 0, 0, 6, 0, 0, 14},
        {0, 0, 0, 0, 13, 10, 0, 0, 0, 17},
        {0, 0, 0, 0, 0, 0, 15, 14, 17, 0}
    };

    int src = 0; // 시작 노드 (0번 노드, 1번 노드로 가정)
    dijkstra(graph, src);

    return 0;
}

