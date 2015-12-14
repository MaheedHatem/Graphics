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

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
Fawzy::Fawzy(float x , float y , float z , float s , GLuint TextureID,
           GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID)
    :Obj(x , y , z, s , TextureID ,vertexUVID,vertexPosition_modelspaceID,MatrixID){
    body = new FishPart(x,y,z,s,TextureID,vertexUVID, vertexPosition_modelspaceID,MatrixID,"fish.bmp","fish.obj");
    shearvalue = 0;
    inc = true;
}
void Fawzy::setScaling(float s){
    Obj::setScaling(s);
    body->setScaling(s);
}
void Fawzy::setTranslation(float x, float y, float z){
    Obj::setTranslation(x,y,z);
    body->setTranslation(x,y,z);
}

void Fawzy::draw(mat4 ViewMatrix, mat4 ProjectionMatrix){
    updateShear();
    body->draw(ViewMatrix , ProjectionMatrix);
}
void Fawzy::updateShear(){
    if(inc){
        shearvalue+=0.05;
    }
    else{
        shearvalue-=0.05;
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
