#ifndef GRND_H
#define GRND_H
#include "Obj/Obj.h"
class Ground: public Obj {

public:
    Ground(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID , const char* texturepath , const char* objpath);
    //void setShear(float s);
    void draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif


