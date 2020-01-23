#include <Windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;
void checkInput(bool& quit);
boolean iniciar_Graficos();
SDL_Window* gWindow = NULL;

int main(int argc, char* args[])
{
	bool quit = false;
	iniciar_Graficos();
	Shader shader("vertex.vs", "fragment.fs");

	float vertices_cuadrado[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
	};

	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cuadrado), vertices_cuadrado, GL_STATIC_DRAW);
	//Attribute number in list, lenght of each vertex, type, normalized?, distance between each vertices,
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int eboID;
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	shader.use();
	glBindVertexArray(vaoID);
	glEnableVertexAttribArray(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

	if (gWindow == NULL) {
		cout << "errrrroooor" << std::endl;
	}

			while (!quit)
			{
				glClearDepth(1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearColor(0.15f, 0.2f, 0.3f, 1.0f);
				checkInput(quit);

				
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				//glDrawArrays(GL_TRIANGLES, 0, 6);
				//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //drawElement draws EBOs not VBOS!!!!!
				
				SDL_GL_SwapWindow(gWindow);
				SDL_UpdateWindowSurface(gWindow);
			}
			//glDisableVertexArrayAttrib(0);
			glBindVertexArray(0);
		glDeleteVertexArrays(1, &vaoID);
		glDeleteBuffers(1, &vboID);
		SDL_GL_DeleteContext(gWindow);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		IMG_Quit;
		SDL_Quit;
	return 0;
}
void checkInput(bool& quit) {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		if (e.type == SDL_KEYDOWN)
		{
			std::cout << "Anda" << std::endl;
		}
	}
}
boolean iniciar_Graficos() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize!: Archivo: %s linea %d\n", __FILE__, __LINE__);
		return false;
	}
	cout << "Pasa---";

	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (gWindow == nullptr)
	{
		printf("Window could not be created!: Archivo: %s linea %d\n", __FILE__, __LINE__);
		printf("SDL Error: %s\n", SDL_GetError());
		return false;
	}
	cout << "Pasa---";
	SDL_GLContext glcontext_local = SDL_GL_CreateContext(gWindow);
	if (glcontext_local == NULL) {
		printf("SDL_GLContext no se pudo rear: Archivo: %s linea %d\n", __FILE__, __LINE__);
		return false;
	}
	cout << "Pasa---";
	GLenum error_local = glewInit();
	if (error_local != GLEW_OK) {
		printf("Error glewInit: Archivo: %s linea %d\n", __FILE__, __LINE__);
		return false;
	}
	cout << "Pasa---";
	return true;
}