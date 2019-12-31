#include <Windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>
#include "MiShader.h"
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;
void checkInput(bool& quit);
boolean iniciar_Graficos();
SDL_Window* gWindow = NULL;


int main(int argc, char* args[])
{
	bool quit = false;
	iniciar_Graficos();
	MiShader shader("vertex.vs", "fragment.fs");
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	float tris[] = {
		// positions               // texture coords
		 0.5f,  0.5f, 0.0f,      1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,      1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,      0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,      0.0f, 1.0f  // top left 
	};
	unsigned int indice[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	//VERTICES
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tris), tris, GL_STATIC_DRAW);
	//INDICE
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice, GL_STATIC_DRAW);
	//POINTERS al Stack de datos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)( 3 * sizeof(float) ));
	glEnableVertexAttribArray(1);
	//Textura
	GLuint textura0;
	glGenTextures(1, &textura0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textura0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Carga de textura
	int width, height, nrChannels;
	unsigned char* data = stbi_load("..\\..\\Resources\\common_textures\\container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	shader.use();
	//glBindVertexArray(vaoID);

			while (!quit)
			{
				glClearDepth(1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
				checkInput(quit);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				SDL_GL_SwapWindow(gWindow);
				SDL_UpdateWindowSurface(gWindow);
			}
		

			glDeleteBuffers(1, &ebo);
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
/*
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	gPNGSurface = loadSurface("../../Resources/common_textures/TutorialFinal.png");
	if (gPNGSurface == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	return success;
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}
*/
boolean iniciar_Graficos() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (gWindow == nullptr)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(gWindow);
	if (glcontext == NULL) {
		printf("SDL_GLContext no se pudo rear\n");
		return false;
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		printf("Error glewInit\n");
		return false;
	}

	return true;
}