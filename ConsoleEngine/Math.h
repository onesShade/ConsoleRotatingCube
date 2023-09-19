#pragma once

#include <math.h>
#include <vector>

struct mat4;

struct vec4
{
	float x, y, z, w;

	vec4 operator*(float a)
	{
		float x = this->x * a;
		float y = this->y * a;
		float z = this->z * a;
		float w = this->w * a;
		return vec4{ x, y, z, w };
	}
	vec4 operator/(float a)
	{
		return (*this) * (1.f / a);
	}
};

struct mat4
{
	float data[4][4];
	float* operator[](int a)
	{
		return data[a];
	}

	vec4 operator*(vec4& a)
	{
		float x = data[0][0] * a.x + data[0][1] * a.y + data[0][2] * a.z + data[0][3] * a.w;
		float y = data[1][0] * a.x + data[1][1] * a.y + data[1][2] * a.z + data[1][3] * a.w;
		float z = data[2][0] * a.x + data[2][1] * a.y + data[2][2] * a.z + data[2][3] * a.w;
		float w = data[3][0] * a.x + data[3][1] * a.y + data[3][2] * a.z + data[3][3] * a.w;

		return { x, y, z, w };
	}
};


struct Mesh
{
	char color = '@';
	std::vector<vec4> verteces;

	void MultipleToMatrix(mat4 m)
	{
		for (vec4& vertex : verteces)
		{
			vertex = m * vertex;
		}
	}
	Mesh operator*(mat4 m)
	{
		Mesh a;
		a.color = this->color;
		for (vec4& vertex : verteces)
		{
			a.verteces.push_back(m * vertex);
		}
		return a;
	}
};


mat4 IdinityMatrix()
{
	return mat4
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
}

mat4 TranslationMatrix(float x, float y, float z)
{
	return mat4
	{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1,
	};
}

mat4 RotationXMatrix(float a)
{
	return mat4
	{
			1, 0, 0, 0,
			0, cosf(a), -sinf(a), 0,
			0, sinf(a), cosf(a), 0,
			0, 0, 0, 1,
	};
}

mat4 RotationYMatrix(float a)
{
	return mat4
	{
		cosf(a), 0, sinf(a), 0,
		0, 1, 0, 0,
		-sinf(a), 0, cosf(a), 0,
		0, 0, 0, 1,
	};
}

mat4 RotationZMatrix(float a)
{
	return mat4
	{
		cosf(a), -sinf(a), 0, 0,
		sinf(a), cosf(a), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
}



mat4 PerspectiveMatrix(float n, float f, float fov, int width, int height)
{
	float tan_fov_dev = tanf(fov / 2.f);
	float aspect = (float)width / (float)height;

	return mat4
	{
		1 / (aspect * tan_fov_dev), 0, 0, 0,
		0, 1 / tan_fov_dev, 0, 0,
		0, 0, -(f + n) / (f - n), (- 2 * f * n) / (f - n),
		0, 0, 1, 0,
	};
}


