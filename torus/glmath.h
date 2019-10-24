#include <math.h>
#include <GL/gl.h>

#define PI		3.1415926535897932384626433832795
#define GLMATH_EPSILON	1.0e-6

typedef struct {
	GLfloat x, y;
} vec2;

typedef struct {
	GLfloat x, y, z;
} vec3;

typedef struct {
	GLfloat x, y, z, w;
} vec4;

typedef struct {
	GLfloat a11, a21;
	GLfloat a12, a22;
} mat2;

typedef struct {
	GLfloat a11, a21, a31;
	GLfloat a12, a22, a32;
	GLfloat a13, a23, a33;
} mat3;

typedef struct {
	GLfloat a11, a21, a31, a41;
	GLfloat a12, a22, a32, a42;
	GLfloat a13, a23, a33, a43;
	GLfloat a14, a24, a34, a44;
} mat4;

static inline GLfloat pi(void)
{
	return PI;
}

static inline GLfloat to_degrees(GLfloat radians)
{
	return radians * (180. / pi());
}

static inline GLfloat to_radians(GLfloat degrees)
{
	return degrees * (pi() / 180.);
}


/* 2D vector operations */

static inline vec2 vec2_zero(void)
{
	return (vec2) { 0., 0. };
}

static inline vec2 vec2_e_x(void)
{
	return (vec2) { 1., 0. };
}

static inline vec2 vec2_e_y(void)
{
	return (vec2) { 0., 1. };
}

static inline vec2 vec2_neg(const vec2 a)
{
	return (vec2) {
		.x = -a.x,
		.y = -a.y
	};
}

static inline GLfloat vec2_abs(const vec2 a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

static inline vec2 vec2_normalize(const vec2 a)
{
	const GLfloat norm = vec2_abs(a);

	if (norm < GLMATH_EPSILON) {
		return vec2_zero();
	}

	return (vec2) {
		.x = a.x / norm,
		.y = a.y / norm
	};
}

static inline vec2 vec2_add(const vec2 a, const vec2 b)
{
	return (vec2) {
		.x = a.x + b.x,
		.y = a.y + b.y
	};
}

static inline vec2 vec2_sub(const vec2 a, const vec2 b)
{
	return (vec2) {
		.x = a.x - b.x,
		.y = a.y - b.y
	};
}

static inline vec2 vec2_mulf(const vec2 a, const GLfloat value)
{
	return (vec2) {
		.x = a.x * value,
		.y = a.y * value
	};
}

static inline vec2 vec2_mul(const vec2 a, const vec2 b)
{
	return (vec2) {
		.x = a.x * b.x,
		.y = a.y * b.y
	};
}

static inline GLfloat vec2_dot(const vec2 a, const vec2 b)
{
	return a.x * b.x + a.y * b.y;
}


/* 3D vector operations */

static inline vec3 vec3_zero(void)
{
	return (vec3) { 0., 0., 0. };
}

static inline vec3 vec3_e_x(void)
{
	return (vec3) { 1., 0., 0. };
}

static inline vec3 vec3_e_y(void)
{
	return (vec3) { 0., 1., 0. };
}

static inline vec3 vec3_e_z(void)
{
	return (vec3) { 0., 0., 1. };
}

static inline vec3 vec3_neg(const vec3 a)
{
	return (vec3) {
		.x = -a.x,
		.y = -a.y,
		.z = -a.z
	};
}

static inline GLfloat vec3_abs(const vec3 a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

static inline vec3 vec3_normalize(const vec3 a)
{
	const GLfloat norm = vec3_abs(a);

	if (norm < GLMATH_EPSILON) {
		return vec3_zero();
	}

	return (vec3) {
		.x = a.x / norm,
		.y = a.y / norm,
		.z = a.z / norm
	};
}

static inline vec3 vec3_add(const vec3 a, const vec3 b)
{
	return (vec3) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	};
}

static inline vec3 vec3_sub(const vec3 a, const vec3 b)
{
	return (vec3) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	};
}

static inline vec3 vec3_mulf(const vec3 a, const GLfloat value)
{
	return (vec3) {
		.x = a.x * value,
		.y = a.y * value,
		.z = a.z * value
	};
}

static inline vec3 vec3_mul(const vec3 a, const vec3 b)
{
	return (vec3) {
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	};
}

static inline GLfloat vec3_dot(const vec3 a, const vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline vec3 vec3_cross(const vec3 a, const vec3 b)
{
	return (vec3) {
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};
}


/* 4D vector operations */

static inline vec4 vec4_zero(void)
{
	return (vec4) { 0., 0., 0., 0. };
}

static inline vec4 vec4_e_x(void)
{
	return (vec4) { 1., 0., 0., 0. };
}

static inline vec4 vec4_e_y(void)
{
	return (vec4) { 0., 1., 0., 0. };
}

static inline vec4 vec4_e_z(void)
{
	return (vec4) { 0., 0., 1., 0. };
}

static inline vec4 vec4_e_w(void)
{
	return (vec4) { 0., 0., 0., 1. };
}

static inline vec4 vec4_neg(const vec4 a)
{
	return (vec4) {
		.x = -a.x,
		.y = -a.y,
		.z = -a.z,
		.w = -a.w
	};
}

static inline GLfloat vec4_abs(const vec4 a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

static inline vec4 vec4_normalize(const vec4 a)
{
	const GLfloat norm = vec4_abs(a);

	if (norm < GLMATH_EPSILON) {
		return vec4_zero();
	}

	return (vec4) {
		.x = a.x / norm,
		.y = a.y / norm,
		.z = a.z / norm,
		.w = a.w / norm
	};
}

static inline vec4 vec4_add(const vec4 a, const vec4 b)
{
	return (vec4) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z,
		.w = a.w + b.w
	};
}

static inline vec4 vec4_sub(const vec4 a, const vec4 b)
{
	return (vec4) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z,
		.w = a.w - b.w
	};
}

static inline vec4 vec4_mulf(const vec4 a, const GLfloat value)
{
	return (vec4) {
		.x = a.x * value,
		.y = a.y * value,
		.z = a.z * value,
		.w = a.w * value
	};
}

static inline vec4 vec4_mul(const vec4 a, const vec4 b)
{
	return (vec4) {
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z,
		.w = a.w * b.w
	};
}

static inline GLfloat vec4_dot(const vec4 a, const vec4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}


/* 2x2 matrix operations */

static inline mat2 mat2_zero(void)
{
	return (mat2) {
		0., 0.,
		0., 0.
	};
}

static inline mat2 mat2_identity(void)
{
	return (mat2) {
		1., 0.,
		0., 1.
	};
}

static inline mat2 mat2_add(const mat2 a, const mat2 b)
{
	return (mat2) {
		.a11 = a.a11 + b.a11,
		.a21 = a.a21 + b.a21,

		.a12 = a.a12 + b.a12,
		.a22 = a.a22 + b.a22
	};
}

static inline mat2 mat2_sub(const mat2 a, const mat2 b)
{
	return (mat2) {
		.a11 = a.a11 - b.a11,
		.a12 = a.a12 - b.a12,

		.a21 = a.a21 - b.a21,
		.a22 = a.a22 - b.a22
	};
}

static inline mat2 mat2_mulf(const mat2 a, const GLfloat scale)
{
	return (mat2) {
		.a11 = a.a11 * scale,
		.a12 = a.a12 * scale,

		.a21 = a.a21 * scale,
		.a22 = a.a22 * scale
	};
}

static inline mat2 mat2_mul(const mat2 a, const mat2 b)
{
#define ROW(M, row) (vec2) { M.a##row##1, M.a##row##2 }
#define COL(M, col) (vec2) { M.a1##col, M.a2##col }
	return (mat2) {
		.a11 = vec2_dot(ROW(a, 1), COL(b, 1)),
		.a12 = vec2_dot(ROW(a, 1), COL(b, 2)),

		.a21 = vec2_dot(ROW(a, 2), COL(b, 1)),
		.a22 = vec2_dot(ROW(a, 2), COL(b, 2))
	};
#undef ROW
#undef COL
}


/* 3x3 matrix operations */

static inline mat3 mat3_zero(void)
{
	return (mat3) {
		0., 0., 0.,
		0., 0., 0.,
		0., 0., 0.
	};
}

static inline mat3 mat3_identity(void)
{
	return (mat3) {
		1., 0., 0.,
		0., 1., 0.,
		0., 0., 1.
	};
}

static inline mat3 mat3_add(const mat3 a, const mat3 b)
{
	return (mat3) {
		.a11 = a.a11 + b.a11,
		.a12 = a.a12 + b.a12,
		.a13 = a.a13 + b.a13,

		.a21 = a.a21 + b.a21,
		.a22 = a.a22 + b.a22,
		.a23 = a.a23 + b.a23,

		.a31 = a.a31 + b.a31,
		.a32 = a.a32 + b.a32,
		.a33 = a.a33 + b.a33
	};
}

static inline mat3 mat3_sub(const mat3 a, const mat3 b)
{
	return (mat3) {
		.a11 = a.a11 - b.a11,
		.a12 = a.a12 - b.a12,
		.a13 = a.a13 - b.a13,

		.a21 = a.a21 - b.a21,
		.a22 = a.a22 - b.a22,
		.a23 = a.a23 - b.a23,

		.a31 = a.a31 - b.a31,
		.a32 = a.a32 - b.a32,
		.a33 = a.a33 - b.a33
	};
}

static inline mat3 mat3_mulf(const mat3 a, const GLfloat scale)
{
	return (mat3) {
		.a11 = a.a11 * scale,
		.a12 = a.a12 * scale,
		.a13 = a.a13 * scale,

		.a21 = a.a21 * scale,
		.a22 = a.a22 * scale,
		.a23 = a.a23 * scale,

		.a31 = a.a31 * scale,
		.a32 = a.a32 * scale,
		.a33 = a.a33 * scale
	};
}

static inline mat3 mat3_mul(const mat3 a, const mat3 b)
{
#define ROW(M, row) (vec3) { M.a##row##1, M.a##row##2, M.a##row##3 }
#define COL(M, col) (vec3) { M.a1##col, M.a2##col, M.a3##col }
	return (mat3) {
		.a11 = vec3_dot(ROW(a, 1), COL(b, 1)),
		.a12 = vec3_dot(ROW(a, 1), COL(b, 2)),
		.a13 = vec3_dot(ROW(a, 1), COL(b, 3)),

		.a21 = vec3_dot(ROW(a, 2), COL(b, 1)),
		.a22 = vec3_dot(ROW(a, 2), COL(b, 2)),
		.a23 = vec3_dot(ROW(a, 2), COL(b, 3)),

		.a31 = vec3_dot(ROW(a, 3), COL(b, 1)),
		.a32 = vec3_dot(ROW(a, 3), COL(b, 2)),
		.a33 = vec3_dot(ROW(a, 3), COL(b, 3))
	};
#undef ROW
#undef COL
}


/* 4x4 matrix operations */

static inline mat4 mat4_zero(void)
{
	return (mat4) {
		0., 0., 0., 0.,
		0., 0., 0., 0.,
		0., 0., 0., 0.,
		0., 0., 0., 0.
	};
}

static inline mat4 mat4_identity(void)
{
	return (mat4) {
		1., 0., 0., 0.,
		0., 1., 0., 0.,
		0., 0., 1., 0.,
		0., 0., 0., 1.
	};
}

static inline mat4 mat4_add(const mat4 a, const mat4 b)
{
	return (mat4) {
		.a11 = a.a11 + b.a11,
		.a12 = a.a12 + b.a12,
		.a13 = a.a13 + b.a13,
		.a14 = a.a14 + b.a14,

		.a21 = a.a21 + b.a21,
		.a22 = a.a22 + b.a22,
		.a23 = a.a23 + b.a23,
		.a24 = a.a24 + b.a24,

		.a31 = a.a31 + b.a31,
		.a32 = a.a32 + b.a32,
		.a33 = a.a33 + b.a33,
		.a34 = a.a34 + b.a34,

		.a41 = a.a41 + b.a41,
		.a42 = a.a42 + b.a42,
		.a43 = a.a43 + b.a43,
		.a44 = a.a44 + b.a44
	};
}

static inline mat4 mat4_sub(const mat4 a, const mat4 b)
{
	return (mat4) {
		.a11 = a.a11 - b.a11,
		.a12 = a.a12 - b.a12,
		.a13 = a.a13 - b.a13,
		.a14 = a.a14 - b.a14,

		.a21 = a.a21 - b.a21,
		.a22 = a.a22 - b.a22,
		.a23 = a.a23 - b.a23,
		.a24 = a.a24 - b.a24,

		.a31 = a.a31 - b.a31,
		.a32 = a.a32 - b.a32,
		.a33 = a.a33 - b.a33,
		.a34 = a.a34 - b.a34,

		.a41 = a.a41 - b.a41,
		.a42 = a.a42 - b.a42,
		.a43 = a.a43 - b.a43,
		.a44 = a.a44 - b.a44
	};
}

static inline mat4 mat4_mulf(const mat4 a, const GLfloat scale)
{
	return (mat4) {
		.a11 = a.a11 * scale,
		.a12 = a.a12 * scale,
		.a13 = a.a13 * scale,
		.a14 = a.a14 * scale,

		.a21 = a.a21 * scale,
		.a22 = a.a22 * scale,
		.a23 = a.a23 * scale,
		.a24 = a.a24 * scale,

		.a31 = a.a31 * scale,
		.a32 = a.a32 * scale,
		.a33 = a.a33 * scale,
		.a34 = a.a34 * scale,

		.a41 = a.a41 * scale,
		.a42 = a.a42 * scale,
		.a43 = a.a43 * scale,
		.a44 = a.a44 * scale
	};
}

static inline mat4 mat4_mul(const mat4 a, const mat4 b)
{
#define ROW(M, row) (vec4) { M.a##row##1, M.a##row##2, M.a##row##3, M.a##row##4 }
#define COL(M, col) (vec4) { M.a1##col, M.a2##col, M.a3##col, M.a4##col }
	return (mat4) {
		.a11 = vec4_dot(ROW(a, 1), COL(b, 1)),
		.a12 = vec4_dot(ROW(a, 1), COL(b, 2)),
		.a13 = vec4_dot(ROW(a, 1), COL(b, 3)),
		.a14 = vec4_dot(ROW(a, 1), COL(b, 4)),

		.a21 = vec4_dot(ROW(a, 2), COL(b, 1)),
		.a22 = vec4_dot(ROW(a, 2), COL(b, 2)),
		.a23 = vec4_dot(ROW(a, 2), COL(b, 3)),
		.a24 = vec4_dot(ROW(a, 2), COL(b, 4)),

		.a31 = vec4_dot(ROW(a, 3), COL(b, 1)),
		.a32 = vec4_dot(ROW(a, 3), COL(b, 2)),
		.a33 = vec4_dot(ROW(a, 3), COL(b, 3)),
		.a34 = vec4_dot(ROW(a, 3), COL(b, 4)),

		.a41 = vec4_dot(ROW(a, 4), COL(b, 1)),
		.a42 = vec4_dot(ROW(a, 4), COL(b, 2)),
		.a43 = vec4_dot(ROW(a, 4), COL(b, 3)),
		.a44 = vec4_dot(ROW(a, 4), COL(b, 4))
	};
#undef ROW
#undef COL
}

static inline vec3 mat4_mulv3(const mat4 m, const vec3 v)
{
	return (vec3) {
		.x = m.a11 * v.x + m.a12 * v.y + m.a13 * v.z,
		.y = m.a21 * v.x + m.a22 * v.y + m.a23 * v.z,
		.z = m.a31 * v.x + m.a32 * v.y + m.a33 * v.z
	};
}

static inline mat4 mat4_scaling(const vec3 scale)
{
	return (mat4) {
		.a11 = scale.x, .a12 = 0., .a13 = 0., .a14 = 0.,
		.a21 = 0., .a22 = scale.y, .a23 = 0., .a24 = 0.,
		.a31 = 0., .a32 = 0., .a33 = scale.z, .a34 = 0.,
		.a41 = 0., .a42 = 0., .a43 = 0., .a44 = 1.
	};
}

static inline mat4 mat4_translation(const vec3 translate)
{
	return (mat4) {
		.a11 = 1., .a12 = 0., .a13 = 0., .a14 = translate.x,
		.a21 = 0., .a22 = 1., .a23 = 0., .a24 = translate.y,
		.a31 = 0., .a32 = 0., .a33 = 1., .a34 = translate.z,
		.a41 = 0., .a42 = 0., .a43 = 0., .a44 = 1.
	};
}

static inline mat4 mat4_transformation(const vec3 scale, const vec3 translate)
{
	return (mat4) {
		.a11 = scale.x, .a12 = 0., .a13 = 0., .a14 = translate.x,
		.a21 = 0., .a22 = scale.y, .a23 = 0., .a24 = translate.y,
		.a31 = 0., .a32 = 0., .a33 = scale.z, .a34 = translate.z,
		.a41 = 0., .a42 = 0., .a43 = 0., .a44 = 1.
	};
}

static inline mat4 mat4_rotation_x(const GLfloat angle)
{
	const GLfloat sin_a = sin(angle);
	const GLfloat cos_a = cos(angle);

	return (mat4) {
		.a11 = 1., .a12 = 0., .a13 = 0., .a14 = 0.,
		.a21 = 0., .a22 = cos_a, .a23 = -sin_a, .a24 = 0.,
		.a31 = 0., .a32 = sin_a, .a33 = cos_a, .a34 = 0.,
		.a41 = 0., .a42 = 0., .a43 = 0., .a44 = 1.
	};
}

static inline mat4 mat4_rotation_y(const GLfloat angle)
{
	const GLfloat sin_a = sin(angle);
	const GLfloat cos_a = cos(angle);

	return (mat4) {
		.a11 = cos_a, .a12 = 0., .a13 = sin_a, .a14 = 0.,
		.a21 = 0., .a22 = 1., .a23 = 0., .a24 = 0.,
		.a31 = -sin_a, .a32 = 0., .a33 = cos_a, .a34 = 0.,
		.a41 = 0., .a42 = 0., .a43 = 0., .a44 = 1.
	};
}

static inline mat4 mat4_rotation_z(const GLfloat angle)
{
	const GLfloat sin_a = sin(angle);
	const GLfloat cos_a = cos(angle);

	return (mat4) {
		.a11 = cos_a, .a12 = -sin_a, .a13 = 0., .a14 = 0.,
		.a21 = sin_a, .a22 = cos_a, .a23 = 0., .a24 = 0.,
		.a31 = 0., .a32 = 0., .a33 = 1., .a34 = 0.,
		.a41 = 0., .a42 = 0., .a43 = 0., .a44 = 1.
	};
}

static inline mat4 mat4_rotation(const GLfloat angle, const vec3 axis)
{
	const GLfloat sin_a = sin(angle);
	const GLfloat cos_a = cos(angle);
	const vec3 unit = vec3_normalize(axis);

	return (mat4) {
		.a11 = unit.x * unit.x * (1. - cos_a) + cos_a,
		.a12 = unit.x * unit.y * (1. - cos_a) - unit.z * sin_a,
		.a13 = unit.x * unit.z * (1. - cos_a) + unit.y * sin_a,
		.a14 = 0.,

		.a21 = unit.y * unit.x * (1. - cos_a) + unit.z * sin_a,
		.a22 = unit.y * unit.y * (1. - cos_a) + cos_a,
		.a23 = unit.y * unit.z * (1. - cos_a) - unit.x * sin_a,
		.a24 = 0.,

		.a31 = unit.z * unit.x * (1. - cos_a) - unit.y * sin_a,
		.a32 = unit.z * unit.y * (1. - cos_a) + unit.x * sin_a,
		.a33 = unit.z * unit.z * (1. - cos_a) + cos_a,
		.a34 = 0.,

		.a41 = 0.,
		.a42 = 0.,
		.a43 = 0.,
		.a44 = 1.
	};
}

static inline mat4 mat4_ortho(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far)
{
	return (mat4) {
		.a11 = 2. / (right - left), .a12 = 0., .a13 = 0., .a14 = -(right + left) / (right - left),
		.a21 = 0., .a22 = 2. / (top - bottom), .a23 = 0., .a24 = -(top + bottom) / (top - bottom),
		.a31 = 0., .a32 = 0., .a33 = -2. / (far - near), .a34 = -(far + near) / (far - near),
		.a41 = 0., .a42 = 0., .a43 = 0., .a44 = 1.
	};
}

static inline mat4 mat4_perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)
{
	const GLfloat tan_fov_2 = tan(fov / 2.);

	return (mat4) {
		.a11 = 1. / (aspect * tan_fov_2), .a12 = 0., .a13 = 0., .a14 = 0.,
		.a21 = 0., .a22 = 1. / tan_fov_2, .a23 = 0., .a24 = 0.,
		.a31 = 0., .a32 = 0., .a33 = -(far + near) / (far - near), .a34 = -2. * far * near / (far - near),
		.a41 = 0., .a42 = 0., .a43 = -1., .a44 = 0.
	};
}

static inline mat4 mat4_look_at(vec3 position, vec3 target, vec3 up)
{
	const vec3 direction = vec3_normalize(vec3_sub(position, target));
	const vec3 right = vec3_normalize(vec3_cross(up, direction));
	const vec3 cam_up = vec3_cross(direction, right);

	const mat4 look = {
		.a11 = right.x, .a12 = right.y, .a13 = right.z, .a14 = 0.,
		.a21 = cam_up.x, .a22 = cam_up.y, .a23 = cam_up.z, .a24 = 0.,
		.a31 = direction.x, .a32 = direction.y, .a33 = direction.z, .a34 = 0.,
		.a41 = 0., .a42 = 0., .a43 = 0., .a44 = 1.
	};

	return mat4_mul(look, mat4_translation(vec3_neg(position)));
}


#ifdef DEBUG

static inline void vec2_print(const vec2 a)
{
	g_print("(%.6f, %.6f)n", a.x, a.y);
}

static inline void vec3_print(const vec3 a)
{
	g_print("(%.6f, %.6f, %.6f)n", a.x, a.y, a.z);
}

static inline void vec4_print(const vec4 a)
{
	g_print("(%.6f, %.6f, %.6f, %.6f)n", a.x, a.y, a.z, a.w);
}

static inline void mat2_print(const mat2 M)
{
	g_print("[%.6f, %.6f]n", M.a11, M.a12);
	g_print("[%.6f, %.6f]n", M.a21, M.a22);
}

static inline void mat3_print(const mat3 M)
{
	g_print("[%.6f, %.6f, %.6f]n", M.a11, M.a12, M.a13);
	g_print("[%.6f, %.6f, %.6f]n", M.a21, M.a22, M.a23);
	g_print("[%.6f, %.6f, %.6f]n", M.a31, M.a32, M.a33);
}

static inline void mat4_print(const mat4 M)
{
	g_print("[%.6f, %.6f, %.6f, %.6f]n", M.a11, M.a12, M.a13, M.a14);
	g_print("[%.6f, %.6f, %.6f, %.6f]n", M.a21, M.a22, M.a23, M.a24);
	g_print("[%.6f, %.6f, %.6f, %.6f]n", M.a31, M.a32, M.a33, M.a34);
	g_print("[%.6f, %.6f, %.6f, %.6f]n", M.a41, M.a42, M.a43, M.a44);
}

#endif
