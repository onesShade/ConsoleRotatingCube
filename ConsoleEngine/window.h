#pragma once
#include <iostream>
#include <Windows.h>
#include "Math.h"

class VideoBuffer
{
public:
	VideoBuffer(int width, int height)
	{
		m_width = width;
		m_height = height;
		pixels = new char[(width + 1) * height + 1];

		for (int i = 0; i < (width + 1) * height; i += 1)
			pixels[i] = ' ';
		for (int i = width; i < (width + 1) * height; i += (width + 1))
			pixels[i] = '\n';

		pixels[(width + 1) * height] = '\0';
	}
	void SetPixel(int x, int y, char c)
	{
		pixels[y * (m_width + 1) + x] = c;
	}
	int m_width, m_height;
	char* pixels;
};

class Window
{
private:
	int m_width, m_height;
	VideoBuffer m_buffer1, m_buffer2;
	bool m_current_buffer;


public:

	mat4 m_projection_mat;

	enum DrawStyle
	{
		CONNECTED_LINE_STRIP,
		DOTS,
		QUADS,
	};


	Window(int width, int height) : m_buffer1(width, height), m_buffer2(width, height)
	{
		m_width = width;
		m_height = height;

		m_projection_mat = PerspectiveMatrix(0.1f, 1000.f, 1.57f, m_width, m_height);
	}
	void Fill(char c)
	{
		for (int x = 0; x < m_width; x++)
			for (int y = 0; y < m_height; y++)
				SetPixel(x, y, c);
	}
	void DrawLine(int x1, int y1, int x2, int y2, char c)
	{
		auto abs = [](int a) {return a < 0 ? -a : a; };
		auto max = [](int a, int b) {return b > a ? b : a; };

		int d_x, d_y;

		d_x = x2 - x1;
		d_y = y2 - y1;

		int steps = max(abs(d_x), abs(d_y));

		float x_step = (float)d_x / (float)steps;
		float y_step = (float)d_y / (float)steps;


		for (int i = 0; i < steps + 1; i++)
		{
			int x = std::roundf(x_step * i) + x1;
			int y = std::roundf(y_step * i) + y1;
			SetPixel(x, y, c);
		}

	}
	void DrawLine(vec4 a, vec4 b, char c)
	{
		vec4 projected[2];

		projected[0] = m_projection_mat * a;
		projected[1] = m_projection_mat * b;

		if (projected[0].w)
			projected[0] = projected[0] / projected[0].w;
		if (projected[1].w)
			projected[1] = projected[1] / projected[1].w;

		projected[0].x += 1.f;
		projected[0].y += 1.f;
		projected[1].x += 1.f;
		projected[1].y += 1.f;

		projected[0].x *= 0.5f * m_width;
		projected[0].y *= 0.5f * m_height;
		projected[1].x *= 0.5f * m_width;
		projected[1].y *= 0.5f * m_height;

		DrawLine(roundf(projected[0].x), roundf(projected[0].y), roundf(projected[1].x), roundf(projected[1].y), c);
	}


	void SetPixel(int x, int y, char c)
	{
		if (x < 0 || x >= m_width)
			return;
		if (y < 0 || y >= m_height)
			return;

		if (m_current_buffer)
			m_buffer1.SetPixel(x, m_height - y - 1, c);
		else
			m_buffer2.SetPixel(x, m_height - y - 1, c);
	}
	void SwapBuffers()
	{
		if (m_current_buffer)
		{
			std::cout << m_buffer1.pixels;
		}
		else
		{
			std::cout << m_buffer2.pixels;
		}

		m_current_buffer = !m_current_buffer;
	}




	bool IsCharKeyPressed(char a)
	{
		if (a >= 'a' && a <= 'z')
			return IsKeyPressed(0x41 + a - 'a');
		return false;
	}
	bool IsKeyPressed(int a)
	{
		return (GetKeyState(a) & 0x8000);
	}

	void Draw(Mesh mesh, DrawStyle d)
	{
		switch (d)
		{
		case DrawStyle::CONNECTED_LINE_STRIP:
			{
				int size = mesh.verteces.size();

				if (size < 3)
					return;
				
				for (int i = 0; i < size - 1; i++)
				{
					DrawLine(mesh.verteces[i] ,mesh.verteces[i + 1], mesh.color);
				}
				 
				DrawLine(mesh.verteces[0], mesh.verteces[size - 1], mesh.color);
				break;
			}
		case DrawStyle::DOTS:
			{
				break;	
			}
		case DrawStyle::QUADS:
			{
			int size = mesh.verteces.size();

			if (size < 4)
				return;

			for (int i = 0; i < size / 4; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					DrawLine(mesh.verteces[i * 4 + j], mesh.verteces[i * 4 + j+ 1], mesh.color);
				}
				DrawLine(mesh.verteces[i * 4], mesh.verteces[i * 4 + 3], mesh.color);
			}
				break;
			}
		}
	}
};

