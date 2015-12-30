// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <fstream>
using namespace std;

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
#include <common/vboindexer.hpp>
#include "Fish/Tuna.h"
#include "Fish/Salmon.h"
#include "Fish/Fawzy.h"
#include "Obj/Obj.h"
#include "Fish/FishPart.h"
#include "Fish/Shark.h"
#include "Fish/Star.h"
#include "Fish/Jellyfish.h"
#include "Environ/Ground.h"
#include "Background/Stone.h"
#include "Background/Reef.h"
#include "common/text2D.hpp"

GLuint Obj::ModelMID = 0;
GLuint Obj::ModelInvMID = 0;
GLuint Obj::ViewMID = 0;
GLuint Obj::ProgramID = 0;
GLuint Obj::vertexNormID = 0;
GLuint TextureID;
GLuint vertexUVID;
GLuint vertexPosition_modelspaceID;
GLuint MatrixID;

int RandomSign() {
    /* initialize random seed: */
    int sign = (rand()%2) - 1;
    if (sign == 0) sign = 1;
    return sign;
}

Tuna* GenerateTunaFish() {
    int signX = RandomSign();
    int signY = RandomSign();
    float x = signX* ((rand()%2) + 8); // *8
    float y = signY* ((rand()%300)*0.01); // rand()%6
    return new Tuna(x,y,0,0.8,TextureID, vertexUVID, vertexPosition_modelspaceID, MatrixID);
}
Salmon* GenerateSalmonFish() {
    int signX = RandomSign();
    int signY = RandomSign();
    float x = signX* ((rand()%2) + 8);
    float y = signY* ((rand()%300)*0.01);
    return new Salmon(x,y,0,1.2,TextureID, vertexUVID, vertexPosition_modelspaceID, MatrixID);
}
Shark* GenerateSharkFish() {
    int signX = RandomSign();
    int signY = RandomSign();
    float x = signX* ((rand()%2) + 8);
    float y = signY* ((rand()%300)*0.01);
    return new Shark(x,y,0,1.3,TextureID, vertexUVID, vertexPosition_modelspaceID, MatrixID);
}

Jellyfish* GenerateJellyFish(){
    float x = (rand()%16)-8;
    return new Jellyfish(x,4,1.2,0.2,TextureID, vertexUVID, vertexPosition_modelspaceID, MatrixID , "Jellyfish.bmp","Jellyfish.obj");
}

int main( void )
{
    bool RedLight = false;
    // Initialise GLFW
    srand (time(NULL));
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
    window = glfwCreateWindow( 1024, 768, "Feeding Fawzy", NULL, NULL);
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
    glClearColor(0.176470588f, 0.443137255f, 0.768627451f, 0.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


    //glEnable(GL_NORMALIZE);
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );
    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(programID, "MVP");
    // Get a handle for our buffers

    vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    vertexUVID = glGetAttribLocation(programID, "vertexUV");
    Obj::vertexNormID = glGetAttribLocation(programID,"vertexNormal_modelspace");
    // Get a handle for our "myTextureSampler" uniform
    TextureID  = glGetUniformLocation(programID, "myTextureSampler");

    Obj::ProgramID = programID;
    Obj::ViewMID = glGetUniformLocation(programID, "V");
    Obj::ModelMID = glGetUniformLocation(programID, "M");
    Obj::ModelInvMID = glGetUniformLocation(programID, "MInv");

    Obj* ground = new Ground(0,-7,15,1,TextureID,vertexUVID, vertexPosition_modelspaceID,MatrixID,"groundTex.bmp","ground.obj");
    Obj* star=new Star(-3,2,0,0.2,TextureID,vertexUVID, vertexPosition_modelspaceID, MatrixID,"Star.bmp","Star.obj");
    Obj* bg = new Ground(0,-7,20,1,TextureID,vertexUVID, vertexPosition_modelspaceID,  MatrixID,"BG2.bmp","BG.obj");
  //  Obj* ceil = new Ground(0,10,20,1,TextureID,vertexUVID, vertexPosition_modelspaceID,  MatrixID,"water.bmp","Ceil.obj");
    Obj* bgcont = new Ground(0,20,20,1,TextureID,vertexUVID, vertexPosition_modelspaceID,  MatrixID,"BGcont.bmp","BGcont.obj");
    Fawzy* fawzy = new Fawzy(-3,0,-1,0.5,TextureID,vertexUVID, vertexPosition_modelspaceID,MatrixID);
    Obj* stone0 = new Stone(6.5,-7,2,3, TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "stone.bmp", "stone.obj");
    Obj* stone1 = new Stone(5,-7.5,2,3,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "stone.bmp", "stone.obj");
    Obj* stone2 = new Stone(4,-7.5,1,3,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "stone.bmp", "stone2.obj");
    Obj* stone3 = new Stone(0.5,-8,0,1,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "stone.bmp", "stone.obj");
    Obj* stone4 = new Stone(-1.3,-7,0,2,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "stone.bmp", "stone.obj");
    Obj* stone5 = new Stone(-3.5,-7,2,3,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "stone.bmp", "stone.obj");
    Obj* stone6 = new Stone(-6.5,-6.6,1,3,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "stone.bmp", "stone.obj");
    Obj* stone7 = new Stone(-6.8,-5.5,0,3,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "stone.bmp", "stone.obj");
    Obj* stone8 = new Stone(0,-7,6,1,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "shell.bmp", "stone.obj");
    Obj* stone9 = new Stone(10,-7,10,1,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "shell.bmp", "stone.obj");
    Obj* stone10 = new Stone(6,-7,8,0.7,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "shell.bmp", "stone.obj");
    Obj* stone11 = new Stone(-7,-7,9,0.8,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "shell.bmp", "stone.obj");
    Obj* stone12 = new Stone(13,-7,12,1,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "shell.bmp", "stone.obj");
    Obj* stone13 = new Stone(1,-7,11,0.7,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "shell.bmp", "stone.obj");
    Obj* stone14 = new Stone(-7,-7,15,0.8,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "shell.bmp", "stone.obj");
    Obj* stone15 = new Stone(10,-7,15,0.8,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "shell.bmp", "stone.obj");
    Obj* stone16 = new Stone(-13.5,-7,15,0.8,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "shell.bmp", "stone.obj");
    Obj* plant1 = new Reef(6.5,-7,0,1.6,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "reefxx.bmp", "reef1.obj");
    Obj* plant2 = new Reef(6.3,-7.3,1.5,1.8,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "reefxx.bmp", "reef1.obj");

    std::vector<Obj*> Fish;
    std::vector<Obj*> JellyFish;

    int plants_size = 12;
    std::vector<Obj*> plants(plants_size);
    float xlimit = 2.0;
    float ylimit = 0;
    float zlimit = 0;
    for (int i = 0; i<4; i++) {
        plants.at(i)=new Reef(xlimit,-6+ylimit,-1.5+zlimit,1,TextureID, vertexUVID, vertexPosition_modelspaceID,MatrixID, "reefzz.bmp", "reef1.obj");
        xlimit-=0.75;
        ylimit-=0.5;
    }
        xlimit = -2.5;
    for (int i = 4; i<6; i++) {
        plants.at(i)=new Reef(xlimit,-7+ylimit,-1,1.2,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "reef1.bmp", "reef1.obj");
        ylimit+=1;
        xlimit-=0.75;
    }

    for(int i=6; i<plants_size; i++) {
        plants.at(i)=new Reef(xlimit,-6+ylimit,-1,1.2,TextureID, vertexUVID, vertexPosition_modelspaceID,  MatrixID, "reef1.bmp", "reef1.obj");
        ylimit-=0.25;
        xlimit-=0.75;
    }
    double lastTime1 = glfwGetTime(); //for shearing
    double lastTime2 = glfwGetTime(); //for translation
    double lastTime3 = glfwGetTime(); //for generation
    double lastTime4 = glfwGetTime(); //for red screen
    double lastTimeJelly = glfwGetTime(); //for jellyfish
    double lastFrameTime1 = lastTime1;
    double lastFrameTime2 = lastTime2;
    double lastFrameTime3 = lastTime3;
    double lastFrameTime4 = lastTime4;
    double lastFrameTimeJelly = lastTimeJelly;


    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
    int FishCounter = 0;
    int score=0;
    int currentLevel = 1;
    int counter1=0, counter2=0;
    int lives = 3;
    bool Firstgame = true;
    bool GameOver = false;
    initText2D( "Holstein.DDS" );

    GLuint LightColorID = glGetUniformLocation(programID, "LightColor");
    glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0);
    glUniform3f(LightColorID, lightColor.x, lightColor.y, lightColor.z);

    do{
        double  currentTime = glfwGetTime();



        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Use our shader
        glUseProgram(programID);

        glm::vec3 lightPos = glm::vec3(0, 8, -15);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
        // Camera matrix
        glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(0 ,0, -10),glm::vec3(0,0,0),glm::vec3(0,1,0));
        if(Firstgame){
        glClearColor(0.176470588f, 0.443137255f, 0.768627451f, 0.0f);
        char start[256];
        sprintf(start,"Press Enter" );
        printText2D(start, 75, 500, 60);
        sprintf(start, " To Start");
        printText2D(start, 75, 400, 60);
        sprintf(start," Press ESC" );
        printText2D(start, 75, 200, 60);
        sprintf(start, "  To Exit");
        printText2D(start, 75, 100, 60);
        if(glfwGetKey(window,GLFW_KEY_ENTER) == true){
            Firstgame = false;
             lastTime1 = glfwGetTime(); //for shearing
             lastTime2 = glfwGetTime(); //for translation
             lastTime3 = glfwGetTime(); //for generation
             lastTimeJelly = glfwGetTime(); //for jellyfish
             lastFrameTime1 = lastTime1;
             lastFrameTime2 = lastTime2;
             lastFrameTime3 = lastTime3;
             lastFrameTimeJelly = lastTimeJelly;

        }
        }
        else if(GameOver){
             char start[256];
             Fish.clear();
             JellyFish.clear();
             glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
             glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
             sprintf(start,"GameOver" );
             printText2D(start, 150, 300, 60);
             sprintf(start, "Score= %d " , score);
             printText2D(start, 150, 200, 60);

             ifstream input;
             ofstream output;
             int highscore;

             input.open("highscore",ios::in);
             input>>highscore;
             input.close();
             if (highscore < score)
             {
                 output.open("highscore",ios::out);
                 highscore=score;
                 output<<highscore;
                 output.close();
             }

             sprintf(start, "Highscore=%d " , highscore);
             printText2D(start, 5, 100, 60);
             glfwSwapBuffers(window);
             glfwPollEvents();
             //sleep(5);

             for (int i=0;i<3;i++){
                 sprintf(start, "Starting in");
                 printText2D(start, 70, 450, 60);
                 sprintf(start,"%d",3-i);
                 printText2D(start, 200+i*150, 400, 60);
                 glfwSwapBuffers(window);
                 glfwPollEvents();
                 sleep(1);
             }


             lastTime1 = glfwGetTime(); //for shearing
             lastTime2 = glfwGetTime(); //for translation
             lastTime3 = glfwGetTime(); //for generation
             lastTimeJelly = glfwGetTime(); //for jellyfish
             lastFrameTime1 = lastTime1;
             lastFrameTime2 = lastTime2;
             lastFrameTime3 = lastTime3;
             lastFrameTimeJelly = lastTimeJelly;
             FishCounter = 0;
             fawzy->setScaling(0.5);
             lives = 3;
             score = 0;
             currentLevel = 1;
             counter1=0;
             counter2=0;
             GameOver = false;

        }
        else{
        //Moving Fawzy
        if (glfwGetKey( window, GLFW_KEY_LEFT) ==GLFW_PRESS) {
            fawzy->movehoriz(false);
        }
        else if (glfwGetKey(window,  GLFW_KEY_RIGHT) ==GLFW_PRESS) {
            fawzy->movehoriz(true);
        }
        if (glfwGetKey(window,  GLFW_KEY_UP) ==GLFW_PRESS) {
            fawzy->movevertic(true);
        }
        else if (glfwGetKey(window,  GLFW_KEY_DOWN) ==GLFW_PRESS) {
            fawzy->movevertic(false);
        }

        currentTime = glfwGetTime();
        lastFrameTime3 = currentTime;
        if (currentTime - lastTime3 >= 1 ){
             lastTime3 += 1;
            if (Fish.size()<15) {
                if(currentLevel == 1) {
                    if (counter1%2==0 || counter1 %5==0) //0,2,4,5,6,8,10,12,14    9/15
                        Fish.push_back(GenerateTunaFish());
                    else if (counter1%3==0 || counter1 >10) //3,9,11,13    4/15
                        Fish.push_back(GenerateSalmonFish());
                    else if (counter1%2!=0)  //1,7 2/15
                        Fish.push_back(GenerateSharkFish());
                    if (counter1<15)
                        counter1++;
                    else
                        counter1=0;
                }
                else if (currentLevel == 2) {
                    if (counter2%2==0 || counter2%3 ==0) {
                        int random = rand()%2;
                        if (random == 1)
                            Fish.push_back(GenerateTunaFish());
                        else
                            Fish.push_back(GenerateSalmonFish());
                    }
                    else
                        Fish.push_back(GenerateSharkFish());
                    if (counter2<15)
                        counter2++;
                    else
                        counter2=0;
                }
                else {
                    int random = rand()%3;
                    if (random == 0)
                        Fish.push_back(GenerateTunaFish());
                    else if (random == 1)
                        Fish.push_back(GenerateSalmonFish());
                    else
                        Fish.push_back(GenerateSharkFish());
                }
            }
        } 

        currentTime = glfwGetTime();
        lastFrameTimeJelly = currentTime;
        if ( currentTime - lastTimeJelly >= 6/currentLevel ){
            lastTimeJelly += 10/currentLevel;
            JellyFish.push_back((GenerateJellyFish()));
        }

        ground->draw(ViewMatrix, ProjectionMatrix);
        bgcont->draw(ViewMatrix, ProjectionMatrix);
        bg->draw(ViewMatrix, ProjectionMatrix);
        stone0->draw(ViewMatrix, ProjectionMatrix);
        stone1->draw(ViewMatrix, ProjectionMatrix);
        stone2->draw(ViewMatrix, ProjectionMatrix);
        stone3->draw(ViewMatrix,ProjectionMatrix);
        stone4->draw(ViewMatrix,ProjectionMatrix);
        stone5->draw(ViewMatrix,ProjectionMatrix);
        stone6->draw(ViewMatrix,ProjectionMatrix);
        stone7->draw(ViewMatrix,ProjectionMatrix);
        stone8->draw(ViewMatrix,ProjectionMatrix);
        stone9->draw(ViewMatrix,ProjectionMatrix);
        stone10->draw(ViewMatrix,ProjectionMatrix);
        stone11->draw(ViewMatrix,ProjectionMatrix);
        stone12->draw(ViewMatrix,ProjectionMatrix);
        stone13->draw(ViewMatrix,ProjectionMatrix);
        stone14->draw(ViewMatrix,ProjectionMatrix);
        stone15->draw(ViewMatrix,ProjectionMatrix);
        stone16->draw(ViewMatrix,ProjectionMatrix);
        plant1->draw(ViewMatrix,ProjectionMatrix);
        plant2->draw(ViewMatrix,ProjectionMatrix);

        for (int i =0 ;i<plants_size; i++) {
            plants[i]->draw(ViewMatrix,ProjectionMatrix);
        }

        currentTime = glfwGetTime();
        lastFrameTime1 = currentTime;
        if ( currentTime - lastTime1 >= 0.01 ){
            lastTime1 += 0.01;
            fawzy->updateShear();
            for(int i=0; i<Fish.size(); i++)
                Fish.at(i)->updateShear();
            for(int i=0; i<JellyFish.size(); i++)
                JellyFish.at(i)->updateShear();
        }

        currentTime = glfwGetTime();
        lastFrameTime2 = currentTime;
        if ( currentTime - lastTime2 >= 0.025 ){
            lastTime2 += 0.025;
            for(int i=0; i<Fish.size(); i++) {
                Fish.at(i)->updateTranslation();
            }
            for(int i=0; i<JellyFish.size(); i++) {
                JellyFish.at(i)->updateTranslation();
            }
        }

        for (int i=0; i<Fish.size(); i++){
            if(!(Fish.at(i))->draw(ViewMatrix,ProjectionMatrix)){
                Fish.erase(Fish.begin()+i);
                i--;
            }
        }
        for (int i=0; i<JellyFish.size(); i++){
            if(!(JellyFish.at(i))->draw(ViewMatrix,ProjectionMatrix)){
                JellyFish.erase(JellyFish.begin()+i);
                i--;
            }
        }

        //Collision Detection
        for (int i=0; i<Fish.size(); i++) {
            float fawzyMouthPositionX = fawzy->x;
            float fawzyMouthPositionY = fawzy->y;
            float xmin, xmax, ymin, ymax;
            xmin = Fish.at(i)->x-0.8*fawzy->s;
            xmax = Fish.at(i)->x+0.8*fawzy->s;
            ymin = Fish.at(i)->y-1.2*fawzy->s;
            ymax = Fish.at(i)->y+1*fawzy->s;
            if(Fish.at(i)->typeNumber == 3){
                xmin = Fish.at(i)->x-1.2*fawzy->s;
                xmax = Fish.at(i)->x+1.2*fawzy->s;
                ymin = Fish.at(i)->y-1.2*fawzy->s;
                ymax = Fish.at(i)->y+1.5*fawzy->s;
            }

            if(fawzyMouthPositionX < xmax && fawzyMouthPositionX > xmin
                    && fawzyMouthPositionY < ymax && fawzyMouthPositionY > ymin) {
                if (currentLevel==1 && Fish.at(i)->typeNumber > 1) {
                    lives--;
                    RedLight = true;
                    currentLevel = 1;
                    FishCounter=-1;
                    if(Fish.at(i)->typeNumber==2){
                        score-=2;
                    }
                    else if (Fish.at(i)->typeNumber == 3) {
                        score-=3;
                    }
                }
                else if (currentLevel==2 && Fish.at(i)->typeNumber > 2) {
                    lives--;
                    RedLight = true;
                    currentLevel = 1;
                    fawzy->setScaling(0.5);
                    FishCounter=-1;
                    score-=3;
                }

                if(Fish.at(i)->typeNumber == 1){
                    score++;
                }
                else if (Fish.at(i)->typeNumber == 2) {
                    score+=2;
                }
                else if (Fish.at(i)->typeNumber == 3){
                    score+=3;
                }

                Fish.erase(Fish.begin()+i);
                FishCounter++;
                i--;
            }
        }
        if (FishCounter == 5 && currentLevel == 1) {
            currentLevel++;
            fawzy->setScaling(0.8);
        }
        else if(FishCounter == 10 && currentLevel == 2) {
            currentLevel++;
            fawzy->setScaling(1.1);
        }
        //Collision Detection jellyfish
        for (int i=0; i<JellyFish.size(); i++) {
            float fawzyMouthPositionX = fawzy->x;
            float fawzyMouthPositionY = fawzy->y;
            float xmin, xmax, ymin, ymax;
            xmin = JellyFish.at(i)->x-0.5;
            xmax = JellyFish.at(i)->x+0.35;
            ymin = JellyFish.at(i)->y-0.8;
            ymax = JellyFish.at(i)->y+0.2;

            if(fawzyMouthPositionX < xmax && fawzyMouthPositionX > xmin
                    && fawzyMouthPositionY < ymax && fawzyMouthPositionY > ymin) {
                if (currentLevel==1) {
                    lives--;
                    RedLight = true;
                    currentLevel = 1;
                    FishCounter = 0;
                }
                else if (currentLevel==2) {
                    lives--;
                    RedLight = true;
                    currentLevel = 1;
                    fawzy->setScaling(0.5);
                    FishCounter = 0;
                }
                else if(currentLevel ==3){
                    lives--;
                    RedLight = true;
                    currentLevel = 2;
                    fawzy->setScaling(0.8);
                    FishCounter = 5;
                }
                JellyFish.erase(JellyFish.begin()+i);
                i--;
            }
        }

        fawzy->draw(ViewMatrix,ProjectionMatrix);
        char text[256];
        sprintf(text,"Level:  %d   Lives:   %d   Score   %d", currentLevel,lives , score );
        printText2D(text, 10, 550, 20);
}
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glDisableVertexAttribArray(vertexUVID);
        glDisableVertexAttribArray(Obj::vertexNormID);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        if(lives == 0 ){
            GameOver = true;
        }

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glDeleteProgram(programID);
    glDeleteTextures(1, &TextureID);
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

