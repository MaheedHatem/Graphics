// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include "Fish/Tuna.h"
#include "Obj/Obj.h"
#include "Fish/FishPart.h"
#include "Fish/Shark.h"
#include "Background/Stone.h"
#include "Background/Reef.h"
int main( void )
{
    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 07 - Model Loading", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);   
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );
	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	// Get a handle for our buffers
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
	// Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
    Obj* tuna1 = new Tuna(0,0,0,1,TextureID,vertexUVID, vertexPosition_modelspaceID,MatrixID);
    Obj* shark = new Shark(3,0,0,2,TextureID,vertexUVID, vertexPosition_modelspaceID,MatrixID);
    Obj* stone1 = new Stone(5,-7.5,2,3,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "stone.bmp", "stone.obj");
    Obj* stone2 = new Stone(4,-7.5,1,3,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "stone.bmp", "stone2.obj");
    Obj* stone3 = new Stone(0.5,-8,0,1,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "stone.bmp", "stone.obj");
    Obj* stone4 = new Stone(-1.3,-7,0,2,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "stone.bmp", "stone.obj");
    Obj* stone5 = new Stone(-3.5,-7,2,3,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "stone.bmp", "stone.obj");
    Obj* stone6 = new Stone(-6.5,-6.6,1,3,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "stone.bmp", "stone.obj");
    Obj* stone7 = new Stone(-6.8,-7,0,3,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "stone.bmp", "stone.obj");
    int plants_size = 11;
    std::vector<Obj*> plants(plants_size);
    float xlimit = 2.0;
    float ylimit = 0;
    float zlimit = 0;

    for (int i = 0; i<4; i++) {
        plants.at(i)=new Reef(xlimit,-6.6+ylimit,zlimit,1,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "reef1.bmp", "reef1.obj");
        xlimit-=0.75;
        ylimit-=0.5;
    }
        xlimit = -3;
    for (int i = 4; i<6; i++) {
        plants.at(i)=new Reef(xlimit,-7+ylimit,-1,1.2,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "reef1.bmp", "reef1.obj");
        ylimit+=1.2;
        xlimit-=0.75;
    }
    for(int i=6; i<plants_size; i++) {
        plants.at(i)=new Reef(xlimit,-6.6+ylimit,-1,1.2,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "reef1.bmp", "reef1.obj");
        ylimit-=0.25;
        xlimit-=0.75;
    }
    do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(programID);

        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
        // Camera matrix
        glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(0,0,-10),glm::vec3(-1,0,0),glm::vec3(0,1,0));
        tuna1->draw(ViewMatrix,ProjectionMatrix);
        shark->draw(ViewMatrix,ProjectionMatrix);
        stone1->draw(ViewMatrix, ProjectionMatrix);
        stone2->draw(ViewMatrix, ProjectionMatrix);
        stone3->draw(ViewMatrix,ProjectionMatrix);
        stone4->draw(ViewMatrix,ProjectionMatrix);
        stone5->draw(ViewMatrix,ProjectionMatrix);
        stone6->draw(ViewMatrix,ProjectionMatrix);
        stone7->draw(ViewMatrix,ProjectionMatrix);
        for (int i =0 ;i<plants_size; i++) {
            plants[i]->draw(ViewMatrix,ProjectionMatrix);
        }
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
		glDisableVertexAttribArray(vertexUVID);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	glDeleteProgram(programID);
    glDeleteTextures(1, &TextureID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

    return 0;
}

