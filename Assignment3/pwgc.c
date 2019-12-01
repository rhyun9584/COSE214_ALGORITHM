#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define PEASANT 0x08
#define WOLF	0x04
#define GOAT	0x02
#define CABBAGE	0x01

void print_graph( int graph[][16], int num);
void bit_print( FILE *fp, int state);
void get_pwgc( int state, int *p, int *w, int *g, int *c);
void save_graph( char *filename, int graph[][16], int num);
int is_dead_end( int state);
int is_possible_transition( int state1,	int state2);
void make_adjacency_matrix( int graph[][16]);
int changeP( int state);
int changePW( int state);
int changePG( int state);
int changePC( int state);
int is_visited( int *visited, int level, int state);
void print_states( int *visited, int count);
void dfs_main( int state, int goal_state, int level, int *visited);
void depth_first_search( int init_state, int goal_state);

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	int graph[16][16] = {0,};
	
	// 인접 행렬 만들기
	make_adjacency_matrix( graph);

	// 인접 행렬 출력
	//print_graph( graph, 16);
	
	// .net 파일 만들기 pajek
	save_graph( "pwgc.net", graph, 16);

	//////////////////////////////////////////
	depth_first_search( 0, 15); // initial state, goal state
	
	return 0;
}

// 인접행렬로 표현된 graph를 화면에 출력
void print_graph( int graph[][16], int num){
	printf("     ");
	for(int i = 0; i < num; i++){
		printf("%2d ", i);
	}
	printf("\n");

	for(int i = 0; i < num; i++){
		printf("%2d : ", i);
		for(int j = 0; j < num; j++){
			printf("%2d ", graph[i][j]);
		}
		printf("\n");
	}
}

// 주어진 상태 state의 마지막 4비트를 파일에 출력 (화면 출력은 stdout)
void bit_print( FILE *fp, int state){
	int p, w, g, c;
	get_pwgc(state, &p, &w, &g, &c);

	fprintf(fp, "\"%d%d%d%d\"\n", p, w, g, c);
}

// 주어진 상태 state에서 농부, 늑대, 염소, 양배추의 상태를 각각 추출하여 p, w, g, c에 저장
void get_pwgc( int state, int *p, int *w, int *g, int *c){
	*p = ((state & PEASANT) == PEASANT);
	*w = ((state & WOLF) == WOLF);
	*g = ((state & GOAT) == GOAT);
	*c = ((state & CABBAGE) == CABBAGE);
}

// 주어진 그래프(graph)를 .net 파일로 저장
// pgwc.net 참조
void save_graph( char *filename, int graph[][16], int num){
	FILE* fp = fopen(filename, "wt");

	fprintf(fp, "*Vertices %d\n", num);
	for(int i = 0; i < num; i++){
		fprintf(fp, " %2d ", i + 1);
		bit_print(fp, i);
	}

	fprintf(fp, "*Edges\n");
	for(int i = 0; i < num / 2; i++){
		for(int j = 0; j < num; j++){
			if(graph[i][j])
				fprintf(fp, " %2d  %2d\n", i + 1, j + 1);
		}
	}

	fclose(fp);
}

// 허용되지 않는 상태인지 검사
// 예) 농부없이 늑대와 염소가 같이 있는 경우 / 농부없이 염소와 양배추가 같이 있는 경우
// return value: 1 허용되지 않는 상태인 경우, 0 허용되는 상태인 경우
int is_dead_end( int state){
	int p, w, g, c;

	get_pwgc(state, &p, &w, &g, &c);

	if(p == 0){
		if(w && g)
			return 1;
		if(g && c)
			return 1;
	}
	else{
		if(!w && !g)
			return 1;
		if(!g && !c)
			return 1;
	}

	return 0;
}

// state1 상태에서 state2 상태로의 전이 가능성 점검
// 농부 또는 농부와 다른 하나의 아이템이 강 반대편으로 이동할 수 있는 상태만 허용
// return value: 1 전이 가능한 경우, 0 전이 불이가능한 경우 
int is_possible_transition( int state1,	int state2){
	if(is_dead_end(state1) || is_dead_end(state2))
		return 0;

	int p1, w1, g1, c1;
	int p2, w2, g2, c2;

	get_pwgc(state1, &p1, &w1, &g1, &c1);
	get_pwgc(state2, &p2, &w2, &g2, &c2);

	if(p1 == p2){ // PEASANT is not moved
		return 0;
	}

	int movecount = 0;
	movecount += (w1 != w2);
	movecount += (g1 != g2);
	movecount += (c1 != c2);

	if(movecount > 1)
		return 0;
	else
		return 1;
}

// 상태들의 인접 행렬을 구하여 graph에 저장
// 상태간 전이 가능성 점검
// 허용되지 않는 상태인지 점검 
void make_adjacency_matrix( int graph[][16]){
	for(int i = 0; i < 16; i++){
		if(is_dead_end(i))
			continue;
			
		for(int j = 0; j < 16; j++){
			if(is_possible_transition(i, j)){
				graph[i][j] = 1;
				graph[j][i] = 1;
			}
		}
	}
}

// 상태 변경: 농부 이동
// return value : 새로운 상태
int changeP( int state){
	return state ^ PEASANT;
}

// 상태 변경: 농부, 늑대 이동
// return value : 새로운 상태
int changePW( int state){
	return state ^ (PEASANT + WOLF);
}

// 상태 변경: 농부, 염소 이동
// return value : 새로운 상태
int changePG( int state){
	return state ^ (PEASANT + GOAT);
}

// 상태 변경: 농부, 양배추 이동
// return value : 새로운 상태
int changePC( int state){
	return state ^ (PEASANT + CABBAGE);
}

// 방문한 상태인지 검사
// return value : 1 visited, 0 not visited
int is_visited( int *visited, int level, int state);

// 방문한 상태들을 차례로 화면에 출력
void print_states( int *visited, int count){
	int p, w, g, c;

	for(int i = 0; i < count; i++){
		for(int j = 0; j < 16; j++){
			if(visited[j] == i + 1){
				get_pwgc(j, &p, &w, &g, &c);
				printf("%d%d%d%d\n", p, w, g, c);
				continue;
			}
		}
	}

	printf("\n");

}

// recursive function
void dfs_main( int state, int goal_state, int level, int *visited){
	if(state == goal_state){
		printf("Goal-state found!\n");
		visited[state] = level;
		print_states(visited, level);
	}
	else{
		visited[state] = level;

		int p, pw, pg, pc;
		p = changeP(state);
		pw = changePW(state);
		pg = changePG(state);
		pc = changePC(state);

		if(is_possible_transition(state, p) && visited[p] == 0)
			dfs_main(p, goal_state, level+1, visited);

		if(is_possible_transition(state, pw) && visited[pw] == 0)
			dfs_main(pw, goal_state, level+1, visited);

		if(is_possible_transition(state, pg) && visited[pg] == 0)
			dfs_main(pg, goal_state, level+1, visited);

		if(is_possible_transition(state, pc) && visited[pc] == 0)
			dfs_main(pc, goal_state, level+1, visited);
	}

	visited[state] = 0;
}

// 깊이 우선 탐색 (초기 상태 -> 목적 상태)
void depth_first_search( int init_state, int goal_state){
	int visited[16] = {0,};

	dfs_main(init_state, goal_state, 1, visited);
}