#ifndef JELLYFISH_H
#define JELLYFISH_H
#include "Obj/Obj.h"
class Jellyfish : public Obj {
private:
    float shearvalue;
    bool inc;
public:
    Jellyfish(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID ,GLuint MatrixID , const char* texturepath , const char* objpath);
    void setShear(float s);
    void updateShear();
    bool draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
