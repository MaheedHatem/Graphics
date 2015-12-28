// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include "FishPart.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>

FishPart::FishPart(float x , float y , float z , float s , GLuint TextureID,
                   GLuint vertexUVID,GLuint vertexPosition_modelspaceID, GLuint MatrixID , const char* texturepath ,
                   const char* objpath ):Obj(x , y , z, s , TextureID ,vertexUVID,vertexPosition_modelspaceID,MatrixID ){
bool res = loadOBJ(objpath, vertices, uvs, normals);
Texture = loadBMP_custom(texturepath);
glGenBuffers(1, &vertexbuffer);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

glGenBuffers(1, &uvbuffer);
glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

glGenBuffers(1, &normbuffer);
glBindBuffer(GL_ARRAY_BUFFER, normbuffer);

glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

this->x = x;
this->y = y;
this->z = z;
srand(time(NULL));
    if(x <= -8){
        dx = (rand()%35 + 5) * 0.01;

    }
    else if (x >= 8){
        dx = -(rand()%35 + 5) * 0.01;
    }
    else{
        dx = 0;
    }
}
void FishPart::setTranslation(float x, float y, float z){
    Obj::setTranslation(x , y , z);
    this->x = x;
    this->y = y;
    this->z = z;
}
void FishPart::updateTranslation() {
    x+= dx;
}

bool FishPart::draw(mat4 ViewMatrix, mat4 ProjectionMatrix){
    this->setTranslation(x,y,z);   //translates object with dx every time it is called
    glm::mat4 ModelMatrix = TranslationMatrix* ScalingMatrix * ShearMatrix;
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


    glm::mat3 ModelInv = glm::mat3(ModelMatrix);
    ModelInv = glm::transpose(glm::inverse(ModelInv));

    glm::mat4 ModelInv2 = glm::mat4(1.0f);

    for(int i =0; i <= 2; i++)
    {
        for(int j = 0; j <= 2; j++)
        {
            ModelInv2[i][j] = ModelInv[i][j];
        }
    }

    for(int i = 0; i <= 3; i++)
    {
        ModelInv2[3][i] = ModelMatrix[3][i];
        ModelInv2[i][3] = ModelMatrix[i][3];
    }

    glUniformMatrix4fv(Obj::ModelMID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(Obj::ViewMID, 1, GL_FALSE, &ViewMatrix[0][0]);
    glUniformMatrix4fv(Obj::ModelInvMID, 1, GL_FALSE, &ModelInv2[0][0]);


    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    //Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(TextureID, 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(vertexPosition_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(vertexPosition_modelspaceID,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(vertexUVID);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(vertexUVID,2,GL_FLOAT,GL_FALSE,0,(void*)0);

    // 3d attribute buffer : normals
    glEnableVertexAttribArray(vertexNormID);
    glBindBuffer(GL_ARRAY_BUFFER, normbuffer);
    glVertexAttribPointer(vertexNormID,3,GL_FLOAT,GL_FALSE,0,(void*)0);


    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return(!((dx>0 && x>=8) || (dx<0 && x<=-8)));
}
void FishPart::setShear(float s){
    ShearMatrix[2].x = s;
}
void FishPart::invert(bool z){
    ScalingMatrix[0].x = - ScalingMatrix[0].x;
    if(z){
      ScalingMatrix[2].z = - ScalingMatrix[2].z;
    }
}
