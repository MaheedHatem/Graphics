#ifndef STONE_H
#define STONE_H
#include "Obj/Obj.h"
class Stone : public Obj {

public:
    Stone(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID , const char* texturepath , const char* objpath);
    void draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
