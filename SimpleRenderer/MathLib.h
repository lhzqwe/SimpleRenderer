#pragma once
#include <cmath>

namespace Math
{
	typedef unsigned int UINT32;

	typedef struct { float m[4][4]; } matrix_t;
	typedef struct { float x, y, z, w; } vector_t;
	typedef vector_t point_t;

	int CMID(int x, int min, int max) { return (x < min) ? min : (x > max) ? max : x; }

	float interpolation(float x1, float x2, float t) { return x1 + (x2 - x1) * t; }

	float vector_length(const vector_t &v)
	{
		float sq = v.x * v.x + v.y * v.y + v.z * v.z;
		return (float)sqrt(sq);
	}

	void vector_add(vector_t &z, const vector_t &x, const vector_t &y)
	{
		z.x = x.x + y.x;
		z.y = x.y + y.y;
		z.z = x.z + y.z;
		z.w = 1.0;
	}

	void vector_sub(vector_t &z, const vector_t &x, const vector_t &y)
	{
		z.x = x.x - y.x;
		z.y = x.y - y.y;
		z.z = x.z - y.z;
		z.w = 1.0;
	}

	float vector_dotproduct(const vector_t &x, const vector_t &y)
	{
		return x.x * y.x + x.y * y.y + x.z * y.z;
	}

	void vector_crossproduct(const vector_t &x, const vector_t &y, vector_t & z)
	{
		z.x = x.y * y.z - x.z * y.y;
		z.y = x.z * y.x - x.x * y.z;
		z.z = x.x * y.y - x.y * y.x;
		z.w = 1.0;
	}

	void vector_interpolation(vector_t& v, vector_t &v1, vector_t &v2, float t)
	{
		v.x = interpolation(v1.x, v2.x, t);
		v.y = interpolation(v1.y, v2.y, t);
		v.z = interpolation(v1.z, v2.z, t);
		v.w = 1.0;
	}

	void vector_normalize(vector_t& v)
	{
		float length = vector_length(v);
		
		float delta = 0.000000001f;

		if (length < delta && length > -delta)
		{
			float inv = 1.0 / length;

			v.x *= inv;
			v.y *= inv;
			v.z *= inv;
		}
	}

	void matrix_add(matrix_t& c, const matrix_t& a, const matrix_t& b)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				c.m[i][j] = a.m[i][j] + b.m[i][j];
			}
		}
	}

	void matrix_sub(matrix_t& c, const matrix_t &a, const matrix_t &b)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				c.m[i][j] = a.m[i][j] - b.m[i][j];
			}
		}
	}

	void matrix_mul(matrix_t& c, const matrix_t &a, const matrix_t &b)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				c.m[i][j] = a.m[i][0] * b.m[0][j]
					+ a.m[i][1] * b.m[1][j]
					+ a.m[i][2] * b.m[2][j]
					+ a.m[i][3] * b.m[3][j];
			}
		}
	}

	void matrix_scale(matrix_t& c, const matrix_t& a, float f)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				c.m[i][j] *= f;
			}
		}
	}

	void matrix_apply(vector_t &y, const vector_t& x, const matrix_t &m)
	{
		float X = x.x, Y = x.y, Z = x.z, W = x.w;

		y.x = X * m.m[0][0] + Y * m.m[1][0] + Z * m.m[2][0] + W * m.m[3][0];
		y.y = X * m.m[0][1] + Y * m.m[1][1] + Z * m.m[2][1] + W * m.m[3][1];
		y.z = X * m.m[0][2] + Y * m.m[1][2] + Z * m.m[2][2] + W * m.m[3][2];
		y.w = X * m.m[0][3] + Y * m.m[1][3] + Z * m.m[2][3] + W * m.m[3][3];
	}

	void matrix_set_identity(matrix_t &m)
	{
		m.m[0][0] = m.m[1][1] = m.m[2][2] = m.m[3][3] = 1.0f;
		m.m[0][1] = m.m[0][2] = m.m[0][3] = 0.0f;
		m.m[1][0] = m.m[1][2] = m.m[1][3] = 0.0f;
		m.m[2][0] = m.m[2][1] = m.m[2][3] = 0.0f;
		m.m[3][0] = m.m[3][1] = m.m[3][2] = 0.0f;
	}

	void matrix_set_zero(matrix_t &m)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m.m[i][j] = 0.0f;
			}
		}
	}

	void matrix_set_translate(matrix_t &m, float x, float y, float z)
	{
		matrix_set_identity(m);

		m.m[3][0] = x;
		m.m[3][1] = y;
		m.m[3][2] = z;
	}

	void matrix_set_scale(matrix_t &m, float x, float y, float z)
	{
		matrix_set_identity(m);
		m.m[0][0] = x;
		m.m[1][1] = y;
		m.m[2][2] = z;
 	}

	void matrix_set_rotate(matrix_t &m, float x, float y, float z, float theta)
	{
		float qsin = (float)sin(theta * 0.5f);
		float qcos = (float)cos(theta * 0.5f);
		vector_t vec = { x, y, z, 1.0f };
		float w = qcos;
		vector_normalize(vec);
		x = vec.x * qsin;
		y = vec.y * qsin;
		z = vec.z * qsin;
		m.m[0][0] = 1 - 2 * y * y - 2 * z * z;
		m.m[1][0] = 2 * x * y - 2 * w * z;
		m.m[2][0] = 2 * x * z + 2 * w * y;
		m.m[0][1] = 2 * x * y + 2 * w * z;
		m.m[1][1] = 1 - 2 * x * x - 2 * z * z;
		m.m[2][1] = 2 * y * z - 2 * w * x;
		m.m[0][2] = 2 * x * z - 2 * w * y;
		m.m[1][2] = 2 * y * z + 2 * w * x;
		m.m[2][2] = 1 - 2 * x * x - 2 * y * y;
		m.m[0][3] = m.m[1][3] = m.m[2][3] = 0.0f;
		m.m[3][0] = m.m[3][1] = m.m[3][2] = 0.0f;
		m.m[3][3] = 1.0f;
	}

	void matrix_set_lookat(matrix_t &m, const vector_t& eye, const vector_t& at, const vector& up)
	{
		vector_t xaxis, yaxis, zaxis;

		vector_sub(zaxis, at, eye);
		vector_normalize(zaxis);
		vector_crossproduct(xaxis, up, zaxis);
		vector_normalize(xaxis);
		vector_crossproduct(yaxis, zaxis, xaxis);

		m.m[0][0] = xaxis.x;
		m.m[1][0] = xaxis.y;
		m.m[2][0] = xaxis.z;
		m.m[3][0] = -vector_dotproduct(xaxis, eye);

		m.m[0][1] = yaxis.x;
		m.m[1][1] = yaxis.y;
		m.m[2][1] = yaxis.z;
		m.m[3][1] = -vector_dotproduct(yaxis, eye);

		m.m[0][2] = zaxis.x;
		m.m[1][2] = zaxis.y;
		m.m[2][2] = zaxis.z;
		m.m[3][2] = -vector_dotproduct(zaxis, eye);

		m.m[0][3] = m.m[1][3] = m.m[2][3] = 0.0f;
		m.m[3][3] = 1.0f;
	}

	void matrix_set_perspective(matrix_t &m, float fovy, float aspect, float zn, float zf)
	{
		float fax = 1.0 / (float)tan(fovy * 0.5f);
		matrix_set_zero(m);
		m.m[0][0] = (float)(fax / aspect);
		m.m[1][1] = (float)(fax);
		m.m[2][2] = zf / (zf - zn);
		m.m[3][2] = -zn * zf / (zf - zn);
		m.m[2][3] = 1;
	}

	typedef struct {
		matrix_t world;
		matrix_t view;
		matrix_t projection;
		matrix_t transform;
		float w, h;
	} transform_t;
}