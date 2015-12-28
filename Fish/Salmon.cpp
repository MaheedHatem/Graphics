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
#include "Salmon.h"
#include "FishPart.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
Salmon::Salmon(float x , float y , float z , float s , GLuint TextureID,
           GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID)
    :Obj(x , y , z, s , TextureID ,vertexUVID,vertexPosition_modelspaceID, MatrixID){
    body = new FishPart(x,y,z,s,TextureID,vertexUVID, vertexPosition_modelspaceID, MatrixID,"Salmon.bmp","SalmonBody.obj");
    eyes = new FishPart(x,y,z,s,TextureID,vertexUVID, vertexPosition_modelspaceID, MatrixID,"Salmon.bmp","SalmonEye.obj");
    mouth = new FishPart(x,y,z,s,TextureID,vertexUVID, vertexPosition_modelspaceID, MatrixID,"Salmon.bmp","SalmonMouth.obj");
    shearvalue = 0;
    inc = true;
    if(x>= 8){
        this->invert(false);
    }
}
void Salmon::setScaling(float s){
    Obj::setScaling(s);
    body->setScaling(s);
    eyes->setScaling(s);
    mouth->setScaling(s);
}
void Salmon::setTranslation(float x, float y, float z){
    Obj::setTranslation(x,y,z);
    body->setTranslation(x,y,z);
    eyes->setTranslation(x,y,z);
    mouth->setTranslation(x,y,z);
}

bool Salmon::draw(mat4 ViewMatrix, mat4 ProjectionMatrix){
    body->draw(ViewMatrix , ProjectionMatrix);
    eyes->draw(ViewMatrix , ProjectionMatrix);
    return(mouth->draw(ViewMatrix , ProjectionMatrix));
}
void Salmon::updateShear(){
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
void Salmon::updateTranslation(){
    body->updateTranslation();
    mouth->updateTranslation();
    eyes->updateTranslation();
}
void Salmon::invert(bool z){
    body->invert(true);
    mouth->invert(true);
    eyes->invert(true);
    ScalingMatrix[0].x = - ScalingMatrix[0].x;
}
