#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INSERT_OP      0x01
#define DELETE_OP      0x02
#define SUBSTITUTE_OP  0x04
#define MATCH_OP       0x08
#define TRANSPOSE_OP   0x10

#define INSERT_COST	1
#define DELETE_COST	1
#define SUBSTITUTE_COST	1
#define TRANSPOSE_COST	1

int count = 0;

// 재귀적으로 연산자 행렬을 순회하며, 두 문자열이 최소편집거리를 갖는 모든 가능한 정렬(alignment) 결과를 출력한다.
// op_matrix : 이전 상태에 대한 연산자 정보(backtrace)가 저장된 행렬 (1차원 배열임에 주의!)
// col_size : op_matrix의 열의 크기
// str1 : 문자열 1
// str2 : 문자열 2
// n : 문자열 1의 길이
// m : 문자열 2의 길이
// level : 재귀호출의 레벨 (0, 1, 2, ...)
// align_str : 정렬된 문자쌍들의 정보가 저장된 문자열 배열 예) "a - a", "a - b", "* - b", "ab - ba"
void backtrace_main( int *op_matrix, int col_size, char *str1, char *str2, int n, int m, int level, char align_str[][8]);

// 강의 자료의 형식대로 op_matrix를 출력 (좌하단(1,1) -> 우상단(n, m))
// 각 연산자를  괄호 안의 기호로 표시한다. 삽입(I), 삭제(D), 교체(S), 일치(M), 전위(T)
void print_matrix( int *op_matrix, int col_size, int n, int m);

// 두 문자열 str1과 str2의 최소편집거리를 계산한다.
// return value : 최소편집거리
// 이 함수 내부에서 print_matrix 함수와 backtrace 함수를 호출함
int min_editdistance( char *str1, char *str2);

////////////////////////////////////////////////////////////////////////////////
// 세 정수 중에서 가장 작은 값을 리턴한다.
int __GetMin3( int a, int b, int c)
{
	int min = a;
	if (b < min)
		min = b;
	if(c < min)
		min = c;
	return min;
}

////////////////////////////////////////////////////////////////////////////////
// 네 정수 중에서 가장 작은 값을 리턴한다.
int __GetMin4( int a, int b, int c, int d)
{
	int min = __GetMin3( a, b, c);
	return (min > d) ? d : min;
}

////////////////////////////////////////////////////////////////////////////////
// 정렬된 문자쌍들을 출력 
void print_alignment( char align_str[][8], int level)
{
	int i;
	
	for (i = level; i >= 0; i--)
	{
		printf( "%s\n", align_str[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////
// backtrace_main을 호출하는 wrapper 함수
void backtrace( int *op_matrix, int col_size, char *str1, char *str2, int n, int m)
{
	char align_str[n+m][8]; // n+m strings
	
	backtrace_main( op_matrix, col_size, str1, str2, n, m, 0, align_str);
}

////////////////////////////////////////////////////////////////////////////////
int main()
{
	char str1[30];
	char str2[30];
	
	int distance;
	
	printf( "INSERT_COST = %d\n", INSERT_COST);
	printf( "DELETE_COST = %d\n", DELETE_COST);
	printf( "SUBSTITUTE_COST = %d\n", SUBSTITUTE_COST);
	printf( "TRANSPOSE_COST = %d\n", TRANSPOSE_COST);
	
	while( fscanf( stdin, "%s\t%s", str1, str2) != EOF)
	{
		printf( "\n==============================\n");
		printf( "%s vs. %s\n", str1, str2);
		printf( "==============================\n");
				
		distance = min_editdistance( str1, str2);
		
		printf( "\nMinEdit(%s, %s) = %d\n", str1, str2, distance);
	}
	return 0;
}

// 재귀적으로 연산자 행렬을 순회하며, 두 문자열이 최소편집거리를 갖는 모든 가능한 정렬(alignment) 결과를 출력한다.
// op_matrix : 이전 상태에 대한 연산자 정보(backtrace)가 저장된 행렬 (1차원 배열임에 주의!)
// col_size : op_matrix의 열의 크기
// str1 : 문자열 1
// str2 : 문자열 2
// n : 문자열 1의 길이
// m : 문자열 2의 길이
// level : 재귀호출의 레벨 (0, 1, 2, ...)
// align_str : 정렬된 문자쌍들의 정보가 저장된 문자열 배열 예) "a - a", "a - b", "* - b", "ab - ba"
void backtrace_main( int *op_matrix, int col_size, char *str1, char *str2, int n, int m, int level, char align_str[][8]){
	if(n == 0 && m == 0){
		count++;
		printf("\n[%d]==============================\n", count);

		for(int i = level - 1; i >= 0; i--){
			printf("%s\n", align_str[i]);
		}

		return;
	}

	int op = op_matrix[n * col_size + m];

	if(op & MATCH_OP){
		char str[8];
		str[0] = str1[n-1];
		str[1] = ' ';
		str[2] = '-';
		str[3] = ' ';
		str[4] = str2[m-1];
		str[5] = '\0';

		strcpy(align_str[level], str);
		backtrace_main(op_matrix, col_size, str1, str2, n - 1, m - 1, level+1, align_str);
	}
	if(op & SUBSTITUTE_OP){
		char str[8];
		str[0] = str1[n-1];
		str[1] = ' ';
		str[2] = '-';
		str[3] = ' ';
		str[4] = str2[m-1];
		str[5] = '\0';	

		strcpy(align_str[level], str);
		backtrace_main(op_matrix, col_size, str1, str2, n - 1, m - 1, level+1, align_str);
	}
	if(op & INSERT_OP){
		char str[8];
		str[0] = '*';
		str[1] = ' ';
		str[2] = '-';
		str[3] = ' ';
		str[4] = str2[m-1];
		str[5] = '\0';

		strcpy(align_str[level], str);
		backtrace_main(op_matrix, col_size, str1, str2, n, m - 1, level+1, align_str);
	}
	if(op & DELETE_OP){
		char str[8];
		str[0] = str1[n-1];
		str[1] = ' ';
		str[2] = '-';
		str[3] = ' ';
		str[4] = '*';
		str[5] = '\0';

		strcpy(align_str[level], str);
		backtrace_main(op_matrix, col_size, str1, str2, n - 1, m, level+1, align_str);

	}
    if(op & TRANSPOSE_OP){
		char str[8];
		str[0] = str1[n-2];
		str[1] = str1[n-1];
		str[2] = ' ';
		str[3] = '-';
		str[4] = ' ';
		str[5] = str2[m-2];
		str[6] = str2[m-1];
		str[7] = '\0';

		strcpy(align_str[level], str);
		backtrace_main(op_matrix, col_size, str1, str2, n - 2, m - 2, level+1, align_str);
	}
}

// 강의 자료의 형식대로 op_matrix를 출력 (좌하단(1,1) -> 우상단(n, m))
// 각 연산자를  괄호 안의 기호로 표시한다. 삽입(I), 삭제(D), 교체(S), 일치(M), 전위(T)
void print_matrix( int *op_matrix, int col_size, int n, int m){
	for(int i = n; i > 0; i--){
		for(int j = 1; j <= m; j++){
			int count = 0;
			int op = op_matrix[i*col_size + j];

			if(op & INSERT_OP){
				printf("I");
				count++;
			}
			if(op & DELETE_OP){
				printf("D");
				count++;
			}
			if(op & SUBSTITUTE_OP){
				printf("S");
				count++;
			}
			if(op & TRANSPOSE_OP){
				printf("T");
				count++;
			}
			if(op & MATCH_OP){
				printf("M");
				count++;
			}

			for(int k = 0; k < 5 - count; k++){
				printf(" ");
			}
		}

		printf("\n");
	}	
}

// 두 문자열 str1과 str2의 최소편집거리를 계산한다.
// return value : 최소편집거리
// 이 함수 내부에서 print_matrix 함수와 backtrace 함수를 호출함
int min_editdistance( char *str1,char *str2){
	count = 0;

	int len1 = strlen(str1);
	int len2 = strlen(str2);

	int D[len1+1][len2+1]; // distance
	int back[(len1+1) * (len2+1)]; // backtrace (op bit form)

	// D init
	D[0][0] = 0;
	back[0] = 0;
	for(int i = 1; i <= len1; i++){
		D[i][0] = i;
		back[i * (len2+1)] = 0 | DELETE_OP;
	}
	for(int j = 1; j <= len2; j++){
		D[0][j] = j;
		back[j] = 0 | INSERT_OP;
	}
	
	for(int i = 1; i <= len1; i++){
		for(int j = 1; j <= len2; j++){
			int op = 0;
			int plus;

			if(str1[i-1] == str2[j-1]){ // Match
				plus = D[i-1][j-1];
				op = op | MATCH_OP;
			}
			else if(i > 1 && j > 1 && str1[i-1] == str2[j-2] && str1[i-2] == str2[j-1]){ // Transpose
				plus = __GetMin4(D[i][j-1] + INSERT_COST, D[i-1][j] + DELETE_COST, D[i-1][j-1] + SUBSTITUTE_COST, D[i-2][j-2] + TRANSPOSE_COST);

				if(plus == D[i-2][j-2] + TRANSPOSE_COST){
					op = op | TRANSPOSE_OP;
				}
			}
			else{
				plus = __GetMin3(D[i][j-1] + INSERT_COST, D[i-1][j] + DELETE_COST, D[i-1][j-1] + SUBSTITUTE_COST);
			}

			D[i][j] = plus;				

			if(plus == D[i][j-1] + INSERT_COST) // Insert
				op = op | INSERT_OP;
			if(plus == D[i-1][j] + DELETE_COST) // Delete
				op = op | DELETE_OP;
			if(plus == D[i-1][j-1] + SUBSTITUTE_COST) // Substitute
				op = op | SUBSTITUTE_OP;

			back[i * (len2+1) + j] = op;
		}
	}
	
	print_matrix(back, len2 + 1, len1, len2);
	
	backtrace(back, len2 + 1, str1, str2, len1, len2);

	return D[len1][len2];
}