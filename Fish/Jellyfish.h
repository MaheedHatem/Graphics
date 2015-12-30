#ifndef JELLYFISH_H
#define JELLYFISH_H
#include "Obj/Obj.h"
class Jellyfish : public Obj {
private:
    float shearvalue;
    bool inc,incY;
    float dy;
public:
    Jellyfish(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID ,GLuint MatrixID , const char* texturepath , const char* objpath);
    void setShear(float s);
    void updateShear();
    void setTranslation(float x, float y, float z);
    void updateTranslation();
    bool draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
