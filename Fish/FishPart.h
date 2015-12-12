#ifndef FISHPART_H
#define FISHPART_H
#include "Obj/Obj.h"
class FishPart : public Obj {

public:
    FishPart(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID , const char* texturepath , const char* objpath);
    void setShear(float s);
    void draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
