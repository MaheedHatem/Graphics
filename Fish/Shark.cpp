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
#include "Shark.h"
#include "FishPart.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
Shark::Shark(float x , float y , float z , float s , GLuint TextureID,
           GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID)
    :Obj(x , y , z, s , TextureID ,vertexUVID,vertexPosition_modelspaceID,MatrixID){
    body = new FishPart(x,y,z,s,TextureID,vertexUVID, vertexPosition_modelspaceID,MatrixID,"shark.bmp","Shark.obj");
    shearvalue = 0;
    inc = true;
    if(x>= 8){
        this->invert(false);

    }
}
void Shark::setScaling(float s){
    Obj::setScaling(s);
    body->setScaling(s);
}
void Shark::setTranslation(float x, float y, float z){
    Obj::setTranslation(x,y,z);
    body->setTranslation(x,y,z);
}

void Shark::draw(mat4 ViewMatrix, mat4 ProjectionMatrix){
    updateShear();
    body->draw(ViewMatrix , ProjectionMatrix);
}
void Shark::updateShear(){
    if(inc){
        shearvalue+=0.05;
    }
    else{
        shearvalue-=0.05;
    }
    if(shearvalue >= 1.0f){
        inc = false;
    }
    if(shearvalue <= -1.0f){
        inc = true;
    }
    ShearMatrix[2].x = shearvalue;
    body->setShear(shearvalue);
}
void Shark::invert(bool z){
    body->invert(true);
ScalingMatrix[0].x = - ScalingMatrix[0].x;
}
