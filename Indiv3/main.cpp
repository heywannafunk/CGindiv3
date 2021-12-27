#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include <iostream>

#include "shaders.cpp"
#include "draw.cpp"


void ReleaseShader() {
	glUseProgram(0);
	glDeleteProgram(shaderProgram);
}

// Освобождение буфера
void ReleaseVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &roadVAO);
	glDeleteBuffers(1, &roadVBO);

	glDeleteVertexArrays(1, &busVAO);
	glDeleteBuffers(1, &busVBO);
}

void Release() {
	ReleaseShader();
	ReleaseVBO();
}

void roadMove() {
	road1Pos[2] -= 0.1;
	road2Pos[2] -= 0.1;
	road3Pos[2] -= 0.1;
	if (std::abs(road1Pos[2] + 10) < 0.1)
		road1Pos[2] = 10;
	if (std::abs(road2Pos[2] - 10) < 0.1)
		road2Pos[2] = 30;
	if (std::abs(road3Pos[2] - 30) < 0.1)
		road3Pos[2] = 50;
}

void grassMove() {
	grassL1Pos[2] -= 0.1;
	grassL2Pos[2] -= 0.1;
	grassL3Pos[2] -= 0.1;
	grassR1Pos[2] -= 0.1;
	grassR2Pos[2] -= 0.1;
	grassR3Pos[2] -= 0.1;

	if (std::abs(grassL1Pos[2] + 10) < 0.1)
		grassL1Pos[2] = 10;
	if (std::abs(grassL2Pos[2] - 10) < 0.1)
		grassL2Pos[2] = 30;
	if (std::abs(grassL3Pos[2] - 30) < 0.1)
		grassL3Pos[2] = 50;
	if (std::abs(grassR1Pos[2] + 10) < 0.1)
		grassR1Pos[2] = 10;
	if (std::abs(grassR2Pos[2] - 10) < 0.1)
		grassR2Pos[2] = 30;
	if (std::abs(grassR3Pos[2] - 30) < 0.1)
		grassR3Pos[2] = 50;
}

bool lightsOn = true;

void onOff() {
	if (lightsOn) {
		light.ambient[0] = 0.0f;
		light.ambient[1] = 0.0f;
		light.ambient[2] = 0.0f;
		light.ambient[3] = 0.0f;

		light.diffuse[0] = 0.0f;
		light.diffuse[1] = 0.0f;
		light.diffuse[2] = 0.0f;
		light.diffuse[3] = 0.0f;

		light.specular[0] = 0.0f;
		light.specular[1] = 0.0f;
		light.specular[2] = 0.0f;
		light.specular[3] = 0.0f;
		
		lightsOn = false;
	}
	else {
		light.ambient[0] = 0.5f;
		light.ambient[1] = 0.5f;
		light.ambient[2] = 0.1f;
		light.ambient[3] = 1.0f;

		light.diffuse[0] = 0.9f;
		light.diffuse[1] = 0.9f;
		light.diffuse[2] = 0.8f;
		light.diffuse[3] = 1.0f;

		light.specular[0] = 1.0f;
		light.specular[1] = 1.0f;
		light.specular[2] = 0.8f;
		light.specular[3] = 1.0f;

		lightsOn = true;
	}
}

bool moveLeft = false;
bool moveRight = false;

double angle = 0.1;
double solarRadius = 100.0;

int main() {
	sf::Window window(sf::VideoMode(800, 600), "Game", sf::Style::Default, sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	// Инициализация glew
	glewInit();
	glEnable(GL_DEPTH_TEST);

	Init();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				glViewport(0, 0, event.size.width, event.size.height);
			}


			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case (sf::Keyboard::A):
				{
					moveLeft = true;
					break;
				}
				case (sf::Keyboard::D):
				{
					moveRight = true;
					break;
				}


				case (sf::Keyboard::L):
				{
					angle += 0.1;
					light.direction[0] = solarRadius * std::sin(angle);
					light.direction[1] = solarRadius * std::cos(angle);
					break;
				}
				case (sf::Keyboard::O):
				{
					onOff();
					break;
				}
				default: break;
				}
			}

			else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
				case (sf::Keyboard::A):
				{
					moveLeft = false;
					break;
				}
				case (sf::Keyboard::D):
				{
					moveRight = false;
					break;
				}
				default: break;
				}
			}
		}


		if (moveLeft)
		{
			busPos[0] -= 0.05;
			busAngle[1] -= 0.05;
		}
		if (moveRight)
		{
			busPos[0] += 0.05;
			busAngle[1] += 0.05;
		}

		if (std::abs(busAngle[1] + 3.14) > 0.05f) {
			if (busAngle[1] < -3.14f) 
			{
				busAngle[1] += 0.025f;
			}
			else if (busAngle[1] > -3.14f) 
			{
				busAngle[1] -= 0.025f;
			}
		}

		roadMove();
		grassMove();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Draw();

		window.display();
	}

	Release();
	return 0;
}

