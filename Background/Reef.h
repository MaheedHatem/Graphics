#ifndef _REEF_H
#define _REEF_H
#include "Obj/Obj.h"
class Reef : public Obj {
private:
    float shearvalue;
    bool inc;
public:
    Reef(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID, const char* texturepath , const char* objpath);
    void draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
    void updateShear();
};
#endif
