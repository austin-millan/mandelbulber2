/*
 * opencl_typedefs.h
 *
 *  Created on: 10 maj 2017
 *      Author: krzysztof
 */

inline float3 Matrix33MulFloat3(matrix33 matrix, float3 vect)
{
	float3 out;
	out.x = dot(vect, matrix.m1);
	out.y = dot(vect, matrix.m2);
	out.z = dot(vect, matrix.m3);
	return out;
}

matrix33 Matrix33MulMatrix33(matrix33 m1, matrix33 m2)
{
	matrix33 out;
	out.m1.x = m1.m1.x * m2.m1.x + m1.m1.y * m2.m2.x + m1.m1.z * m2.m3.x;
	out.m1.y = m1.m1.x * m2.m1.y + m1.m1.y * m2.m2.y + m1.m1.z * m2.m3.y;
	out.m1.z = m1.m1.x * m2.m1.z + m1.m1.y * m2.m2.z + m1.m1.z * m2.m3.z;
	out.m2.x = m1.m2.x * m2.m1.x + m1.m2.y * m2.m2.x + m1.m2.z * m2.m3.x;
	out.m2.y = m1.m2.x * m2.m1.y + m1.m2.y * m2.m2.y + m1.m2.z * m2.m3.y;
	out.m2.z = m1.m2.x * m2.m1.z + m1.m2.y * m2.m2.z + m1.m2.z * m2.m3.z;
	out.m3.x = m1.m3.x * m2.m1.x + m1.m3.y * m2.m2.x + m1.m3.z * m2.m3.x;
	out.m3.y = m1.m3.x * m2.m1.y + m1.m3.y * m2.m2.y + m1.m3.z * m2.m3.y;
	out.m3.z = m1.m3.x * m2.m1.z + m1.m3.y * m2.m2.z + m1.m3.z * m2.m3.z;
	return out;
}

matrix33 RotateX(matrix33 m, float angle)
{
	matrix33 out, rot;
	float s = sin(angle);
	float c = cos(angle);
	rot.m1 = (float3){1.0f, 0.0f, 0.0f};
	rot.m2 = (float3){0.0f, c, -s};
	rot.m3 = (float3){0.0f, s, c};
	out = Matrix33MulMatrix33(m, rot);
	return out;
}

matrix33 RotateY(matrix33 m, float angle)
{
	matrix33 out, rot;
	float s = sin(angle);
	float c = cos(angle);
	rot.m1 = (float3){c, 0.0f, s};
	rot.m2 = (float3){0.0f, 1.0f, 0.0f};
	rot.m3 = (float3){-s, 0.0f, c};
	out = Matrix33MulMatrix33(m, rot);
	return out;
}

matrix33 RotateZ(matrix33 m, float angle)
{
	matrix33 out, rot;
	float s = sin(angle);
	float c = cos(angle);
	rot.m1 = (float3){c, -s, 0.0f};
	rot.m2 = (float3){s, c, 0.0f};
	rot.m3 = (float3){0.0f, 0.0f, 1.0f};
	out = Matrix33MulMatrix33(m, rot);
	return out;
}
