#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// 메뉴 실행 함수
void runMenu(GraphMatType* g);

int main() {
    GraphMatType* g = create_mat_graph();  // 그래프 생성
    init_mat_graph(g);  // 그래프 초기화

    // 예시 데이터: 그래프에 정점과 간선 추가
    insert_vertex_mat_graph(g, 0);
    insert_vertex_mat_graph(g, 1);
    insert_vertex_mat_graph(g, 2);
    insert_vertex_mat_graph(g, 3);
    insert_vertex_mat_graph(g, 4);
    insert_vertex_mat_graph(g, 5);
    insert_vertex_mat_graph(g, 6);
    insert_vertex_mat_graph(g, 7);
    insert_vertex_mat_graph(g, 8);
    insert_vertex_mat_graph(g, 9);
    insert_vertex_mat_graph(g, 10);

    insert_edge_mat_graph(g, 0, 1);
    insert_edge_mat_graph(g, 0, 4);
    insert_edge_mat_graph(g, 1, 2);
    insert_edge_mat_graph(g, 2, 3);
    insert_edge_mat_graph(g, 2, 4);
    insert_edge_mat_graph(g, 4, 5);
    insert_edge_mat_graph(g, 5, 6);
    insert_edge_mat_graph(g, 6, 7);
    insert_edge_mat_graph(g, 7, 8);
    insert_edge_mat_graph(g, 8, 9);
    insert_edge_mat_graph(g, 7, 10);

    runMenu(g);  // 메뉴 실행

    destroy_mat_graph(g);  // 그래프 해제
    return 0;
}

// 메뉴 실행 함수 정의
void runMenu(GraphMatType* g) {
    int choice, start, target;

    while (1) {
        printf("\n1: 깊이 우선 탐색\n");
        printf("2: 너비 우선 탐색\n");
        printf("3: 종료\n");
        printf("메뉴 입력: ");
        scanf("%d", &choice);

        if (choice == 3) {
            printf("프로그램 종료\n");
            break;
        }

        printf("시작 번호와 목표 번호 입력: ");
        scanf("%d %d", &start, &target);

        if (start < 0 || start >= MAX_VERTICES || target < 0 || target >= MAX_VERTICES) {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            continue;
        }

        switch (choice) {
            case 1:
                dfs(g, start, target);
                break;
            case 2:
                bfs(g, start, target);
                break;
            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
}

