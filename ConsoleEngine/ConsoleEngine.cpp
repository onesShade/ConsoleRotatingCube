#include "window.h"
#include <thread>
#include <chrono>
#include "Math.h"

int main()
{
	const int width = 40;
	const int height = 20;
	Window window(width, height);


	std::chrono::time_point<std::chrono::system_clock> last_time_point = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current_time_point = last_time_point;

	mat4 mat_proj = PerspectiveMatrix(0.1f, 1000.f, 1.57f, width, height);

	Mesh test_mesh;

	test_mesh.color = '0';
	test_mesh.verteces.push_back({ -0.5f, -0.5f, -0.5f, 1.f });
	test_mesh.verteces.push_back({ 0.5f, -0.5f, -0.5f, 1.f });
	test_mesh.verteces.push_back({ 0.5f, 0.5f, -0.5f, 1.f });
	test_mesh.verteces.push_back({ -0.5f, 0.5f, -0.5f, 1.f });

	test_mesh.verteces.push_back({ -0.5f, -0.5f, 0.5f, 1.f });
	test_mesh.verteces.push_back({ 0.5f, -0.5f, 0.5f, 1.f });
	test_mesh.verteces.push_back({ 0.5f, 0.5f, 0.5f, 1.f });
	test_mesh.verteces.push_back({ -0.5f, 0.5f, 0.5f, 1.f });

	test_mesh.verteces.push_back({ -0.5f, -0.5f, -0.5f, 1.f });
	test_mesh.verteces.push_back({ -0.5f, -0.5f, 0.5f, 1.f });
	test_mesh.verteces.push_back({ -0.5f, 0.5f, 0.5f, 1.f });
	test_mesh.verteces.push_back({ -0.5f, 0.5f, -0.5f, 1.f });

	test_mesh.verteces.push_back({ 0.5f, -0.5f, -0.5f, 1.f });
	test_mesh.verteces.push_back({ 0.5f, -0.5f, 0.5f, 1.f });
	test_mesh.verteces.push_back({ 0.5f, 0.5f, 0.5f, 1.f });
	test_mesh.verteces.push_back({ 0.5f, 0.5f, -0.5f, 1.f });

	bool automatic = true;
	std::cout << "Press to proceed :\na. Automatic mode\nd. Manual mode";
	while (true)
	{
		if (window.IsCharKeyPressed('a'))
			break;
		if (window.IsCharKeyPressed('d'))
		{
			automatic = false;
			break;
		}
	}
	system("cls");
	while (true)
	{
		current_time_point = std::chrono::system_clock::now();
		std::chrono::duration<float> dt = current_time_point - last_time_point;
		last_time_point = current_time_point;
		float d_t = dt.count();

		HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(a, { 0, 0 });

		window.Fill(' ');
		
		const float speed = 50.f;

		//if (window.IsCharKeyPressed('a'))
		//	player_pos.x -= d_t * speed;
		//if (window.IsCharKeyPressed('d'))
		//	player_pos.x += d_t * speed;
		//if (window.IsCharKeyPressed('s'))
		//	player_pos.y -= d_t * speed;
		//if (window.IsCharKeyPressed('w'))
		//	player_pos.y += d_t * speed;
		//if (window.IsCharKeyPressed('z'))
		//	player_pos.z += d_t * 0.1f;
		//if (window.IsCharKeyPressed('x'))
		//	player_pos.z -= d_t * 0.1f;
		//
		//if (window.IsCharKeyPressed('e'))
		//{
		//	player_pos = RotationZMatrix(2.f * d_t) * player_pos;
		//}
		//if (window.IsCharKeyPressed('q'))
		//{
		//	player_pos = RotationZMatrix(-2.f * d_t) * player_pos;
		//}

		//vec4 projected = mat_proj * player_pos;

		//if (projected.w)
		//	projected = projected / projected.w;
		//
		//if (player_pos.z >= 0)
		//	window.SetPixel(projected.x + 1 * 0.5f * width , projected.y + 1 * 0.5f * height, 'P');

		if (automatic)
		{
			test_mesh.MultipleToMatrix(RotationXMatrix(d_t * 0.8f));
			test_mesh.MultipleToMatrix(RotationYMatrix(d_t * 0.6f));
			test_mesh.MultipleToMatrix(RotationZMatrix(d_t * -0.3f));
		}
		else
		{
		if (window.IsCharKeyPressed('w'))
			test_mesh.MultipleToMatrix(RotationXMatrix(d_t * 0.8f));
		if (window.IsCharKeyPressed('s'))
			test_mesh.MultipleToMatrix(RotationXMatrix(-d_t * 0.8f));
		if (window.IsCharKeyPressed('a'))
			test_mesh.MultipleToMatrix(RotationYMatrix(d_t * 0.8f));
		if (window.IsCharKeyPressed('d'))
			test_mesh.MultipleToMatrix(RotationYMatrix(-d_t * 0.8f));
		if (window.IsCharKeyPressed('q'))
			test_mesh.MultipleToMatrix(RotationZMatrix(d_t * 0.8f));
		if (window.IsCharKeyPressed('e'))
			test_mesh.MultipleToMatrix(RotationZMatrix(-d_t * 0.8f));
		}
		Mesh res = test_mesh * TranslationMatrix( -0.5f, 0.f, 1.2f );
		window.Draw(res, Window::QUADS);

		window.SwapBuffers();
		//std::cout << "------------------------------" << '\n';
		//std::cout << "                             \r" << "fps : " << 1.f / d_t << '\n';
	}
}

