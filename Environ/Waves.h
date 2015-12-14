#ifndef WAVES_H
#define WAVES_H
#include "Obj/Obj.h"
class Waves : public Obj {

public:
    Waves(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID , const char* texturepath , const char* objpath);
    //void setShear(float s);
    void draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif

