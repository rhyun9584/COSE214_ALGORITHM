#include <stdlib.h> // atoi, rand
#include <stdio.h>
#include <assert.h> // assert
#include <time.h> //time

#define RANGE 100

typedef struct
{
	int x;
	int y;
} point;

typedef struct
{
	point from;
	point to;
} line_segment;

////////////////////////////////////////////////////////////////////////////////
void print_header(char *filename)
{
	printf( "#! /usr/bin/env Rscript\n");
	printf( "png(\"%s\", width=700, height=700)\n", filename);
	
	printf( "plot(1:%d, 1:%d, type=\"n\")\n", RANGE, RANGE);
}
////////////////////////////////////////////////////////////////////////////////
void print_footer(void)
{
	printf( "dev.off()\n");
}

////////////////////////////////////////////////////////////////////////////////
void print_points( point *p, int n);

// [input] p : set of points
// [input] n : number of points
// [output] l : set of line segments that form the convex hull
// return value : number of line segments
int convex_hull( point *p, int n, line_segment *l);

void print_line_segments( line_segment *l, int num_line);

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	int x, y;
	int n; // number of points
	
	if (argc != 2)
	{
		printf( "%s number_of_points\n", argv[0]);
		return 0;
	}

	n = atoi( argv[1]);
	if (n <= 0)
	{
		printf( "The number of points should be a positive integer!\n");
		return 0;
	}

	point p[n];
	line_segment l[n];

	fprintf( stderr, "Create %d points\n", n);

	// making n points
	srand( time(NULL));
	for (int i = 0; i < n; i++)
	{
		x = rand() % RANGE + 1; // 1 ~ RANGE random number
		y = rand() % RANGE + 1;
		
		p[i].x = x;
		p[i].y = y;
 	}

	print_header( "convex.png");
	
	print_points( p, n);
	
	int num_line = convex_hull( p, n, l);

	print_line_segments( l, num_line);
	
	print_footer();
	
	return 0;
}

///////////////////////////////////////////////////////////////////////

void print_points( point *p, int n){
	printf("\n#points\n");
	for(int i = 0; i < n; i++){
		printf("points(%d,%d)\n", p[i].x, p[i].y);
	}
}

int _Equation(point p1, point p2, point p){
	return (p2.y - p1.y) * p.x + (p1.x - p2.x) * p.y - (p1.x*p2.y - p1.y*p2.x);
}
int _IsPostive(int x){
	if(x > 0)
		return 1;
	else if(x == 0)
		return 0;
	else
		return -1;
}
int _CmpDistance(point p1, point p2, point p){//p가 p1과 p2사이면 1, 아니면 0
	int a = p2.x - p1.x;
	int b = p2.y - p1.y;
	int dis_12 = a * a + b * b;

	int c = p.x - p1.x;
	int d = p.y - p1.y;
	int dis_p1 = c * c + d * d;

	int e = p2.x - p.x;
	int f = p2.y = p.y;
	int dis_p2 = e * e + f * f;

	if(dis_p1 + dis_p2 == dis_12)
		return 1;
	else
		return 0;
}
// [input] p : set of points
// [input] n : number of points
// [output] l : set of line segments that form the convex hull
// return value : number of line segments
int convex_hull( point *p, int n, line_segment *l){
	int numOfLine = 0;

	for(int i = 0; i < n -1; i++){
		for(int j = i + 1; j < n; j++){
			int isWhere = 0; //1 or -1, init은 0로로 아직 척도가 주어지지 않음을 의미

			for(int k = 0; k < n; k++){
				if(i != k && j != k){
					int rst = _Equation(p[i], p[j], p[k]);
					rst = _IsPostive(rst); //양수면 1, 0이면 0, 음수면 -1

					if(rst == 0){
						if(_CmpDistance(p[i], p[j], p[k]) == 1) //세 점이 한 line에 있을때 양 끝점 끼리 선을 긋지 않도록 하기위함
							break;
					}
					else if(isWhere == 0){ //해당 i,j 값에서 처음 계산해보는 k일때 동일함의 척도
						isWhere = rst;
					}
					else {
						if(rst != isWhere)
							break;	
					}
				}

				if(k == n-1){
					l[numOfLine].from = p[i];
					l[numOfLine].to = p[j];
					numOfLine++;
				}
			}
		}
	}
	return numOfLine;
}

void print_line_segments( line_segment *l, int num_line){
	printf("\n#line segments\n");
	for(int i = 0; i < num_line; i++){
		printf("segments(%d,%d,%d,%d)\n",l[i].from.x, l[i].from.y, l[i].to.x, l[i].to.y);
	}
}