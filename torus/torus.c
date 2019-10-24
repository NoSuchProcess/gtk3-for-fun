#include <stdio.h>
#include <math.h>
#include <glmath.h>

#define RADIUS 0.5
#define WIDTH 0.2

#define N 32
#define M 32

/*
0   N+0
  /
1   N+1
  /
2   N+2
  /
3   N+3
  /
4   N+4
  /
.   +.

N-1   +N-1
   /
0    +0
*/
void torus()
{
	printf("vertex_t vertices[] = {");
	for (int j = 0; j < M; ++j) {
		const double alpha = 2 * j * M_PI / M;

		printf("\n");
		for (int i = 0; i < N; ++i) {
			const double phy = 2 * i * M_PI / N;
			vec3 norm = { cos(phy), sin(phy), 0 };
			vec3 p;
			double x, y;

			x = WIDTH * norm.x + RADIUS;
			y = WIDTH * norm.y;
			p = mat4_mulv3(mat4_rotation_y(alpha), (vec3) {
				       x, y, 0});
			printf("\t{{%+lf, %+lf, %+lf},", p.x, p.y, p.z);
			p = mat4_mulv3(mat4_rotation_y(alpha), norm);
			printf(" {%+lf, %+lf, %+lf}},\n", p.x, p.y, p.z);
		}
	}
	printf("};\n");

	printf("GLuint indices[] = {");
	for (int j = 0; j < M; ++j) {
		printf("\n");
		for (int i = 0; i < N; ++i) {
			int i0, i1, i2, i3;

			i0 = (j * N + (i) % N) % (N * M);
			i1 = (j * N + (i + 1) % N) % (N * M);
			i2 = (j * N + (i) % N + N) % (N * M);
			i3 = (j * N + (i + 1) % N + N) % (N * M);
			printf("\t%3u, %3u, %3u,  %3u, %3u, %3u,\n", i0, i1, i2, i1, i3, i2);
		}
	}
	printf("};\n");
}


/*
0 \    N
|   1/ |    N+1
| / | \
2 \ |  N+2
|   3/
| / |
4 \ |
|   5
... 
|  /
N-2 |
| \ |
|  N-1
0/  |
*/

void torus1()
{
	printf("vertex_t vertices[] = {\n");
	for (int j = 0; j < M; j += 2) {
		double alpha0 = 2 * j * M_PI / M;
		double alpha1 = 2 * (j + 1) * M_PI / M;
		for (int i = 0; i < N; i += 2) {
			double phy0 = 2 * i * M_PI / N;
			double phy1 = (2 * i + 1) * M_PI / N;
			double x, y;
			vec3 norm;
			vec3 p;

			norm = (vec3) {cos(phy0), sin(phy0), 0.0};
			x = WIDTH * norm.x + RADIUS;
			y = WIDTH * norm.y;
			p = mat4_mulv3(mat4_rotation_y(alpha0), (vec3) {x, y, 0.0});
			printf("\t{{%+lf, %+lf, %+lf}, ", p.x, p.y, p.z);
			p = mat4_mulv3(mat4_rotation_y(alpha0), norm);
			printf("{%+lf, %+lf, %+lf}},\n", p.x, p.y, p.z);

			norm = (vec3) {cos(phy1), sin(phy1), 0.0};
			x = WIDTH * norm.x + RADIUS;
			y = WIDTH * norm.y;
			p = mat4_mulv3(mat4_rotation_y(alpha1), (vec3) {x, y, 0.0});
			printf("\t{{%+lf, %+lf, %+lf}, ", p.x, p.y, p.z);
			p = mat4_mulv3(mat4_rotation_y(alpha1), norm);
			printf("\{%+lf, %+lf, %+lf}},\n", p.x, p.y, p.z);
		}
	}
	printf("};\n\n");

	printf("GLuint indices[] = {\n");
	for (int j = 0; j < M / 2; ++j) {
		for (int i = 0; i < N; i += 2) {
			unsigned i0, i1, i2;

			// 0,2,1 1,2,3
			i0 = (j * N + (i + 0) % N) % (N * M / 2);
			i1 = (j * N + (i + 2) % N) % (N * M / 2);
			i2 = (j * N + (i + 1) % N) % (N * M / 2);
			printf("\t%3u, %3u, %3u,", i0, i1, i2);
			i0 = (j * N + (i + 1) % N) % (N * M / 2);
			i1 = (j * N + (i + 2) % N) % (N * M / 2);
			i2 = (j * N + (i + 3) % N) % (N * M / 2);
			printf("  %3u, %3u, %3u,\n", i0, i1, i2);
			//1,N+2,N 1,3,N+2
			i0 = (j * N + (i + 1) % N) % (N * M / 2);
			i1 = (j * N + (i + 2) % N + N) % (N * M / 2);
			i2 = (j * N + (i + 0) % N + N) % (N * M / 2);
			printf("\t%3u, %3u, %3u,", i0, i1, i2);
			i0 = (j * N + (i + 1) % N) % (N * M / 2);
			i1 = (j * N + (i + 3) % N) % (N * M / 2);
			i2 = (j * N + (i + 2) % N + N) % (N * M / 2);
			printf("  %3u, %3u, %3u,\n", i0, i1, i2);
		}
	}
	printf("};\n");
}

int main()
{
    // torus();
    torus1();
    return 0;
}
