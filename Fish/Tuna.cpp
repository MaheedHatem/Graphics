// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include "Tuna.h"
#include "FishPart.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
Tuna::Tuna(float x , float y , float z , float s , GLuint TextureID,
           GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID)
    :Obj(x , y , z, s , TextureID ,vertexUVID,vertexPosition_modelspaceID,MatrixID){
    body = new FishPart(x,y,z,s,TextureID,vertexUVID, vertexPosition_modelspaceID, MatrixID,"body.bmp","Tuna.obj");
    eyes = new FishPart(x,y,z,s,TextureID,vertexUVID, vertexPosition_modelspaceID, MatrixID,"eyes.bmp","Eyes.obj");
    mouth = new FishPart(x,y,z,s,TextureID,vertexUVID, vertexPosition_modelspaceID, MatrixID,"body.bmp","Mouth.obj");
    shearvalue = 0;
    inc = true;
    if(x>= 8){
        this->invert(false);
    }
    xmin = 0.46;
    xmax = -0.8;
    ymin = 0.2592;
    ymax = -0.27;
}
void Tuna::setScaling(float s){
    Obj::setScaling(s);
    body->setScaling(s);
    eyes->setScaling(s);
    mouth->setScaling(s);
}
void Tuna::setTranslation(float x, float y, float z){
    Obj::setTranslation(x,y,z);
    body->setTranslation(x,y,z);
    eyes->setTranslation(x,y,z);
    mouth->setTranslation(x,y,z);
}

bool Tuna::draw(mat4 ViewMatrix, mat4 ProjectionMatrix){
    //updateShear();
    body->draw(ViewMatrix , ProjectionMatrix);
    eyes->draw(ViewMatrix , ProjectionMatrix);
    return(mouth->draw(ViewMatrix , ProjectionMatrix));
}
void Tuna::updateShear(){
    if(inc){
        shearvalue+=0.3;
    }
    else{
        shearvalue-=0.3;
    }
    if(shearvalue >= 1.0f){
        inc = false;
    }
    if(shearvalue <= -1.0f){
        inc = true;
    }
    ShearMatrix[2].x = shearvalue;
    body->setShear(shearvalue);
    mouth->setShear(shearvalue);
    eyes->setShear(shearvalue);
}
void Tuna::updateTranslation(){
    body->updateTranslation();
    this->x = body->x;
    this->y = body->y;
    mouth->updateTranslation();
    eyes->updateTranslation();
}
void Tuna::invert(bool z){
    body->invert(false);
    mouth->invert(false);
    eyes->invert(false);
    ScalingMatrix[0].x = -ScalingMatrix[0].x;
    float temp = xmin;
    xmin = ymax;
    xmax = temp;
    temp = ymin;
    ymin = ymax;
    ymax = temp;
}
