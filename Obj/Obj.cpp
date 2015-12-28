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
#include "Obj.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>


Obj::Obj(float x , float y , float z , float s, GLuint TextureID,
                      GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID){
    this->TranslationMatrix = translate(mat4(), vec3(x, y, z));
    this->ScalingMatrix = scale(mat4(), vec3(s, s, s));
    this->ShearMatrix = glm::mat4(1.0f);
    this->vertexUVID = vertexUVID;
    this->vertexPosition_modelspaceID = vertexPosition_modelspaceID;
    this->MatrixID = MatrixID;
    this->TextureID = TextureID;


}
void Obj::setTranslation(float x, float y, float z){
    this->TranslationMatrix = translate(mat4(), vec3(x, y, z));
}

void Obj::setScaling(float s){
     this->ScalingMatrix = scale(mat4(), vec3(s, s, s));
}
void Obj::invert(bool z){

}

Obj::~Obj(){
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normbuffer);
}
void Obj:: updateShear() {}
void Obj:: updateTranslation() {}
