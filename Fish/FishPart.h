#ifndef FISHPART_H
#define FISHPART_H
#include "Obj/Obj.h"
class FishPart : public Obj {
private:
    //Moving attributes
    float dx;
    float x;
    float y;
    float z;
public:
    FishPart(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID , const char* texturepath , const char* objpath);
    void setShear(float s);
    void setTranslation(float x, float y, float z);
    void invert(bool z);
    void draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
