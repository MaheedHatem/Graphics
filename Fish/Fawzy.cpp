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
#include "Fawzy.h"
#include "FishPart.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <iostream>
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
Fawzy::Fawzy(float x , float y , float z , float s , GLuint TextureID,
           GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID)
    :Obj(x , y , z, s , TextureID ,vertexUVID,vertexPosition_modelspaceID, MatrixID){
    body = new FishPart(x,y,z,s,TextureID,vertexUVID, vertexPosition_modelspaceID, MatrixID,"fish.bmp","fish.obj");
    shearvalue = 0;
    inc = true;
    this->x = x;
    this->y = y;
    this->z = z;
    this->s = s;
    dx = 0;
    dy = 0;
    right = true;
    xMouthPosition = -0.83;
    yMouthPosition = -0.22;
}
void Fawzy::setScaling(float s){
    body->setScaling(s);
}
void Fawzy::setTranslation(float x, float y, float z){
    Obj::setTranslation(x,y,z);
    body->setTranslation(x,y,z);
}

bool Fawzy::draw(mat4 ViewMatrix, mat4 ProjectionMatrix){
    //updateShear();
    x+=dx;
    y+=dy;
    this->setTranslation(x,y,z);
    body->draw(ViewMatrix , ProjectionMatrix);
    dx = 0;
    dy = 0;

    return true;
}
void Fawzy::movehoriz(bool r){
    if(r){
        if(x>-6.5){
             dx = -0.01;
        }
        if(!right){
            this->invert(false);
            right = true;
        }
    }
    else{
        if(x < 6.5){
            dx = 0.01;
        }
        if(right){
            this->invert(false);
            right = false;
        }
    }
}
void Fawzy::movevertic(bool u){
    if(u){
        if(y < 3){
            dy = 0.008;
        }
    }
    else{
        if(y>-3){
            dy = -0.008;
        }
    }
}

void Fawzy::updateShear(){
    if(inc){
        shearvalue+=0.01;
    }
    else{
        shearvalue-=0.01;
    }
    if(shearvalue >= 0.5f){
        inc = false;
    }
    if(shearvalue <= -0.5f){
        inc = true;
    }
    ShearMatrix[2].x = shearvalue;
    body->setShear(shearvalue);
}
void Fawzy::invert(bool z){
    body->invert(true);
    ScalingMatrix[0].x = - ScalingMatrix[0].x;

    float temp = xmin;
    xmin = xmax;
    xmax = temp;
    xMouthPosition = - xMouthPosition;
}
