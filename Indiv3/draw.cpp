#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "loader.cpp"
#include "shaders.cpp"

GLuint shaderProgram;
GLint attribVertex;
GLint attribTex;
GLint attribNormal;
GLint unifTexture;
GLint unifRotate;
GLint unifMove;
GLint unifScale;

GLuint roadVBO;
GLuint grassVBO;
GLuint busVBO;
GLuint boxVBO;
GLuint coneVBO;
GLuint mooseVBO;
GLuint skyVBO;

GLint roadTextureHandle;
GLint busTextureHandle;
GLint grassTextureHandle;
GLint boxTextureHandle;
GLint coneTextureHandle;
GLint mooseTextureHandle;
GLint skyTextureHandle;

sf::Texture roadTextureData;
sf::Texture busTextureData;
sf::Texture grassTextureData;
sf::Texture boxTextureData;
sf::Texture coneTextureData;
sf::Texture mooseTextureData;
sf::Texture skyTextureData;

GLuint roadVAO;
GLuint busVAO;
GLuint grassVAO;
GLuint boxVAO;
GLuint coneVAO;
GLuint mooseVAO;
GLuint skyVAO;

GLint Unif_transform_viewPosition;

GLint Unif_material_emission;
GLint Unif_material_ambient;
GLint Unif_material_diffuse;
GLint Unif_material_specular;
GLint Unif_material_shininess;

GLint Unif_light_ambient;
GLint Unif_light_diffuse;
GLint Unif_light_specular;
GLint Unif_light_attenuation;
GLint Unif_light_direction;


//
float busAngle[3] = { 0.0f, -3.14f, 0.0f };
float busPos[3] = { 0.0f, -1.0f, 0.7f };
float busScale[3] = { 0.1f, 0.1f, 0.1f };

float road1Pos[3] = { 0.0f, -1.0f, 10.0f };
float road2Pos[3] = { 0.0f, -1.0f, 30.0f };
float road3Pos[3] = { 0.0f, -1.0f, 50.0f };
float roadRotate[3] = { 0.0f, 0.0f, 0.0f };
float roadScale[3] = { 0.15f, 0.15f, 0.1f };

float grassLAngle[3] = { 0.0f, -3.1415f, 0.0f };
float grassRAngle[3] = { 0.0f, 0.0f, 0.0f };
float grassL1Pos[3] = { -12.0f, -1.0f, 10.0f };
float grassL2Pos[3] = { -12.0f, -1.0f, 30.0f };
float grassL3Pos[3] = { -12.0f, -1.0f, 50.0f };
float grassR1Pos[3] = { 12.0f, -1.0f, 10.0f };
float grassR2Pos[3] = { 12.0f, -1.0f, 30.0f };
float grassR3Pos[3] = { 12.0f, -1.0f, 50.0f };
float grassScale[3] = { 0.1f, 0.1f, 0.1f };

float boxAngle[3] = { 0.0f, 0.0f, 0.0f };
float boxPos[3] = { -1.5f, -1.0f, -10.0f };
float boxScale[3] = { 0.1f, 0.1f, 0.1f };

float coneAngle[3] = { 0.0f, 0.0f, 0.0f };
float conePos[3] = { 0.0f, -1.0f, -10.0f };
float coneScale[3] = { 0.15f, 0.15f, 0.15f };

float mooseAngle[3] = { 0.0f, 0.0f, 0.0f };
float moosePos[3] = { 1.5f, -1.0f, -10.0f };
float mooseScale[3] = { 0.1f, 0.1f, 0.1f };

float skyAngle[3] = { -1.7f, 0.0f, 3.1415f };
float skyPos[3] = { 0.0f, 20.0f, 30.0f };
float skyScale[3] = { 100.0f, 20.0f, 50.0f };


float viewPosition[3] = { 0.0, 0.0, -100.0 };
struct Material
{
	float emission[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float ambient[4] = { 0.1f, 0.1f, 0.1f , 1.0f };
	float diffuse[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float shininess = 10.0f;
};
Material material;

struct Light
{
	float ambient[4] = { 0.5f, 0.5f, 0.1f , 1.0f };
	float diffuse[4] = { 0.9f, 0.9f, 0.8f , 1.0f };
	float specular[4] = { 1.0f, 1.0f, 0.8f , 1.0f };
	float direction[3] = { 0.0f, 90.0f, -100.0f };
};
Light light;

// Проверка ошибок OpenGL, если есть то вывод в консоль тип ошибки
void checkOpenGLerror() {
	GLenum errCode;
	// Коды ошибок можно смотреть тут
	// https://www.khronos.org/opengl/wiki/OpenGL_Error
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGl error!: " << errCode << std::endl;
}

// Функция печати лога шейдера
void ShaderLog(unsigned int shader)
{
	int infologLen = 0;
	int charsWritten = 0;
	char* infoLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);
	if (infologLen > 1)
	{
		infoLog = new char[infologLen];
		if (infoLog == NULL)
		{
			std::cout << "ERROR: Could not allocate InfoLog buffer" << std::endl;
			exit(1);
		}
		glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
		std::cout << "InfoLog: " << infoLog << "\n\n\n";
		delete[] infoLog;
	}
}

int roadInd = 0;
int grassInd = 0;
int busInd = 0;
int boxInd = 0;
int coneInd = 0;
int mooseInd = 0;
int skyInd = 0;

void InitVBO()
{
	std::vector<float> pos_tex = InitializeVBO("models/road.obj", roadInd);
	glGenBuffers(1, &roadVBO);
	glGenVertexArrays(1, &roadVAO);
	glBindVertexArray(roadVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, roadVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	pos_tex = InitializeVBO("models/grass.obj", grassInd);
	glGenBuffers(1, &grassVBO);
	glGenVertexArrays(1, &grassVAO);
	glBindVertexArray(grassVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	pos_tex = InitializeVBO("models/bus2.obj", busInd);
	glGenBuffers(1, &busVBO);
	glGenVertexArrays(1, &busVAO);
	glBindVertexArray(busVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, busVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	pos_tex = InitializeVBO("models/sky.obj", skyInd);
	glGenBuffers(1, &skyVBO);
	glGenVertexArrays(1, &skyVAO);
	glBindVertexArray(skyVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	pos_tex = InitializeVBO("models/box.obj", boxInd);
	glGenBuffers(1, &boxVBO);
	glGenVertexArrays(1, &boxVAO);
	glBindVertexArray(boxVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	pos_tex = InitializeVBO("models/cone.obj", coneInd);
	glGenBuffers(1, &coneVBO);
	glGenVertexArrays(1, &coneVAO);
	glBindVertexArray(coneVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, coneVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	pos_tex = InitializeVBO("models/los.obj", mooseInd);
	glGenBuffers(1, &mooseVBO);
	glGenVertexArrays(1, &mooseVAO);
	glBindVertexArray(mooseVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, mooseVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	checkOpenGLerror();
}

void InitUniform(GLint& id, const char* name)
{
	id = glGetUniformLocation(shaderProgram, name);
	if (id == -1)
	{
		std::cout << "could not bind uniform " << name << std::endl;
		return;
	}
}

void InitShader() {
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vShader);
	std::cout << "vertex shader \n";
	ShaderLog(vShader);

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &FragShaderSource, NULL);
	glCompileShader(fShader);
	std::cout << "fragment shader \n";
	ShaderLog(fShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);

	glLinkProgram(shaderProgram);
	int link_status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &link_status);
	if (!link_status)
	{
		std::cout << "error attach shaders \n";
		return;
	}

	attribVertex = glGetAttribLocation(shaderProgram, "coord");
	if (attribVertex == -1)
	{
		std::cout << "could not bind attrib coord" << std::endl;
		return;
	}

	attribTex = glGetAttribLocation(shaderProgram, "texcoord");
	if (attribVertex == -1)
	{
		std::cout << "could not bind attrib texcoord" << std::endl;
		return;
	}

	attribNormal = glGetAttribLocation(shaderProgram, "normal");
	if (attribNormal == -1)
	{
		std::cout << "could not bind attrib normal" << std::endl;
		return;
	}

	InitUniform(unifTexture, "textureData");
	InitUniform(unifRotate, "rotate");
	InitUniform(unifMove, "move");
	InitUniform(unifScale, "scale");
	InitUniform(Unif_transform_viewPosition, "viewPosition");
	InitUniform(Unif_material_emission, "material.emission");
	InitUniform(Unif_material_ambient, "material.ambient");
	InitUniform(Unif_material_diffuse, "material.diffuse");
	InitUniform(Unif_material_specular, "material.specular");
	InitUniform(Unif_material_shininess, "material.shininess");
	InitUniform(Unif_light_ambient, "light.ambient");
	InitUniform(Unif_light_diffuse, "light.diffuse");
	InitUniform(Unif_light_specular, "light.specular");
	InitUniform(Unif_light_direction, "light.direction");

	checkOpenGLerror();
}

void InitTexture()
{
	const char* road = "textures/road.png";
	const char* grass = "textures/grass.png";
	const char* bus = "textures/bus2.png";
	const char* sky = "textures/sky.jpg";
	const char* box = "textures/box.png";
	const char* cone = "textures/cone.png";
	const char* moose = "textures/los.png";

	if (!roadTextureData.loadFromFile(road))
	{
		std::cout << "could not load texture road";
		return;
	}
	if (!grassTextureData.loadFromFile(grass))
	{
		std::cout << "could not load texture grass";
		return;
	}
	if (!busTextureData.loadFromFile(bus))
	{
		std::cout << "could not load texture bus";
		return;
	}
	if (!boxTextureData.loadFromFile(box))
	{
		std::cout << "could not load texture box";
		return;
	}
	if (!coneTextureData.loadFromFile(cone))
	{
		std::cout << "could not load texture cone";
		return;
	}
	if (!mooseTextureData.loadFromFile(moose))
	{
		std::cout << "could not load texture los";
		return;
	}
	if (!skyTextureData.loadFromFile(sky))
	{
		std::cout << "could not load texture sky";
		return;
	}

	roadTextureHandle = roadTextureData.getNativeHandle();
	grassTextureHandle = grassTextureData.getNativeHandle();
	busTextureHandle = busTextureData.getNativeHandle();
	boxTextureHandle = boxTextureData.getNativeHandle();
	coneTextureHandle = coneTextureData.getNativeHandle();
	mooseTextureHandle = mooseTextureData.getNativeHandle();
	skyTextureHandle = skyTextureData.getNativeHandle();
}


void Init() {
	InitShader();
	InitVBO();
	InitTexture();
}

void Draw() {
	// Устанавливаем шейдерную программу текущей
	glUseProgram(shaderProgram);

	//material
	glUniform4fv(Unif_material_emission, 1, material.emission);
	glUniform4fv(Unif_material_ambient, 1, material.ambient);
	glUniform4fv(Unif_material_diffuse, 1, material.diffuse);
	glUniform4fv(Unif_material_specular, 1, material.specular);
	glUniform1f(Unif_material_shininess, material.shininess);

	//light
	glUniform4fv(Unif_light_ambient, 1, light.ambient);
	glUniform4fv(Unif_light_diffuse, 1, light.diffuse);
	glUniform4fv(Unif_light_specular, 1, light.specular);
	glUniform3fv(Unif_light_direction, 1, light.direction);

	glUniform3fv(Unif_transform_viewPosition, 1, viewPosition);


	//bus
	glUniform3fv(unifRotate, 1, busAngle);
	glUniform3fv(unifMove, 1, busPos);
	glUniform3fv(unifScale, 1, busScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&busTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(busVAO);
	glDrawArrays(GL_TRIANGLES, 0, busInd);
	glBindVertexArray(0);

	//road1
	glUniform3fv(unifRotate, 1, roadRotate);
	glUniform3fv(unifMove, 1, road1Pos);
	glUniform3fv(unifScale, 1, roadScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, roadInd);
	glBindVertexArray(0);

	//road2
	glUniform3fv(unifRotate, 1, roadRotate);
	glUniform3fv(unifMove, 1, road2Pos);
	glUniform3fv(unifScale, 1, roadScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, roadInd);
	glBindVertexArray(0);

	//road3
	glUniform3fv(unifRotate, 1, roadRotate);
	glUniform3fv(unifMove, 1, road3Pos);
	glUniform3fv(unifScale, 1, roadScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, roadInd);
	glBindVertexArray(0);

	//grassleft1
	glUniform3fv(unifRotate, 1, grassLAngle);
	glUniform3fv(unifMove, 1, grassL1Pos);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grassInd);
	glBindVertexArray(0);
	//grassleft2
	glUniform3fv(unifRotate, 1, grassLAngle);
	glUniform3fv(unifMove, 1, grassL2Pos);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grassInd);
	glBindVertexArray(0);
	//grassleft3
	glUniform3fv(unifRotate, 1, grassLAngle);
	glUniform3fv(unifMove, 1, grassL3Pos);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grassInd);
	glBindVertexArray(0);

	//grassright1
	glUniform3fv(unifRotate, 1, grassRAngle);
	glUniform3fv(unifMove, 1, grassR1Pos);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grassInd);
	glBindVertexArray(0);
	//grassright2
	glUniform3fv(unifRotate, 1, grassRAngle);
	glUniform3fv(unifMove, 1, grassR2Pos);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grassInd);
	glBindVertexArray(0);
	//grassright3
	glUniform3fv(unifRotate, 1, grassRAngle);
	glUniform3fv(unifMove, 1, grassR3Pos);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grassInd);
	glBindVertexArray(0);

	//box
	glUniform3fv(unifRotate, 1, boxAngle);
	glUniform3fv(unifMove, 1, boxPos);
	glUniform3fv(unifScale, 1, boxScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&boxTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(boxVAO);
	glDrawArrays(GL_TRIANGLES, 0, boxInd);
	glBindVertexArray(0);

	//cone
	glUniform3fv(unifRotate, 1, coneAngle);
	glUniform3fv(unifMove, 1, conePos);
	glUniform3fv(unifScale, 1, coneScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&coneTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(coneVAO);
	glDrawArrays(GL_TRIANGLES, 0, coneInd);
	glBindVertexArray(0);

	//moose
	glUniform3fv(unifRotate, 1, mooseAngle);
	glUniform3fv(unifMove, 1, moosePos);
	glUniform3fv(unifScale, 1, mooseScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&mooseTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(mooseVAO);
	glDrawArrays(GL_TRIANGLES, 0, mooseInd);
	glBindVertexArray(0);

	//sky
	glUniform3fv(unifRotate, 1, skyAngle);
	glUniform3fv(unifMove, 1, skyPos);
	glUniform3fv(unifScale, 1, skyScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&skyTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(skyVAO);
	glDrawArrays(GL_TRIANGLES, 0, skyInd);
	glBindVertexArray(0);

	glUseProgram(0);
	checkOpenGLerror();
}

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