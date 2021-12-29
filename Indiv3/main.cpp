#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>

#include "shaders.cpp"
#include "draw.cpp"

using namespace std;

int obstacle = 0;
bool play = false;
int score = 0;
bool obstaclePassed = false;

void generateObstacle() {
	srand((unsigned)time(0));
	obstacle = (rand() % 3) + 1;
	switch (obstacle)
	{
	case 1:
		cout << "generated obstacle box" << endl;
		break;

	case 2:
		cout << "generated obstacle cone" << endl;
		break;

	case 3:
		cout << "generated obstacle moose" << endl;
		break;
	default:
		break;
	}
	obstaclePassed = false;
}

int lane = 0;
bool movingLeft = false;
bool movingRight = false;

void gameOver() {
	movingLeft = false;
	movingRight = false;
	busPos[0] = 0.0f;
	lane = 0;
	boxPos[2] = -10.0f;
	conePos[2] = -10.0f;
	moosePos[2] = -10.0f;
	play = false;
	cout << "Game over! Your score was: " << score << endl << "Press space to restart." << endl;
	score = 0;
}

void roadMove() {
	road1Pos[2] -= 0.1;
	road2Pos[2] -= 0.1;
	road3Pos[2] -= 0.1;


	boxPos[2] -= 0.1;
	conePos[2] -= 0.1;
	moosePos[2] -= 0.1;

	switch (lane)
	{
	case -1:
		if (abs(busPos[2] - boxPos[2]) < 0.25)
			gameOver();
		break;
	case 0:
		if (abs(busPos[2] - conePos[2]) < 0.25)
			gameOver();
		break;
	case 1:
		if (abs(busPos[2] - moosePos[2]) < 0.25)
			gameOver();
		break;
	default:
		break;
	}

	if (obstaclePassed == false) {
		switch (obstacle)
		{
		case 1:
			if (boxPos[2] < 0.0f && boxPos[2] > -1.0f) {
				score += 10;
				obstaclePassed = true;
				cout << "Obstacle passed! +10" << endl << "Your score is: " << score << endl;
			}
			break;
		case 2:
			if (conePos[2] < 0.0f && conePos[2] > -1.0f) {
				score += 10;
				obstaclePassed = true;
				cout << "Obstacle passed! +10" << endl << "Your score is: " << score << endl;
			}
			break;
		case 3:
			if (moosePos[2] < 0.0f && moosePos[2] > -1.0f) {
				score += 10;
				obstaclePassed = true;
				cout << "Obstacle passed! +10" << endl << "Your score is: " << score << endl;
			}
			break;
		default:
			break;
		}
	}

	if (std::abs(road1Pos[2] + 10) < 0.1) {
		road1Pos[2] = 10;
		generateObstacle();
		switch (obstacle)
		{
		case 1:
			boxPos[2] = 10;
			break;
		case 2:
			conePos[2] = 10;
			break;
		case 3:
			moosePos[2] = 10;
			break;
		default:
			break;
		}
	}
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
		cout << "lights out" << endl;
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
		cout << "lights on" << endl;
	}
}

int main() {
	sf::Window window(sf::VideoMode(800, 600), "Game", sf::Style::Default, sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	// Инициализация glew
	glewInit();
	glEnable(GL_DEPTH_TEST);

	Init();

	cout << "Press space to start!" << endl;

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
					if (play) {
						if (!movingRight && (lane > -1)) {
							movingLeft = true;
							lane--;
						}
					}
					break;
				}
				case (sf::Keyboard::D):
				{
					if (play) {
						if (!movingLeft && (lane < 1)) {
							movingRight = true;
							lane++;
						}
					}
					break;
				}
				case (sf::Keyboard::Space):
				{
					if (play) {
						play = false;
						cout << "Game paused. Press space to continue." << endl;
					}
					else {
						play = true;
						cout << "Game started." << endl;
					}
					break;
				}
				case (sf::Keyboard::Up):
				{
					light.direction[1] -= 15.0;
					cout << "light direction x,y: " << light.direction[0] << " " << light.direction[1] << endl;
					break;
				}
				case (sf::Keyboard::Left):
				{
					light.direction[0] -= 15.0;
					cout << "light direction x,y: " << light.direction[0] << " " << light.direction[1] << endl;
					break;
				}
				case (sf::Keyboard::Right):
				{
					light.direction[0] += 15.0;
					cout << "light direction x,y: " << light.direction[0] << " " << light.direction[1] << endl;
					break;
				}
				case (sf::Keyboard::Down):
				{
					light.direction[1] += 15.0;
					cout << "light direction x,y: " << light.direction[0] << " " << light.direction[1] << endl;
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
		}


		if (movingLeft)
		{
			busPos[0] -= 0.05;
			busAngle[1] -= 0.05;
			if (busPos[0] < 0.01 && busPos[0] > -0.01) {
				movingLeft = false;
			}
			if (busPos[0] < -1.1) {
				movingLeft = false;
			}
		}
		if (movingRight)
		{
			busPos[0] += 0.05;
			busAngle[1] += 0.05;
			if (busPos[0] < 0.01 && busPos[0] > -0.01) {
				movingRight = false;
			}
			if (busPos[0] > 1.1) {
				movingRight = false;
			}
		}

		if (std::abs(busAngle[1] + 3.14) > 0.02f) {
			if (busAngle[1] < -3.14f)
			{
				busAngle[1] += 0.03f;
			}
			else if (busAngle[1] > -3.14f)
			{
				busAngle[1] -= 0.03f;
			}
		}

		if (play) {
			roadMove();
			grassMove();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Draw();

		window.display();
	}
	Release();
	return 0;
}


