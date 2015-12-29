#ifndef TUNA_H
#define TUNA_H
#include "Obj/Obj.h"
#include "FishPart.h"
class Tuna : public Obj {
private:
    float shearvalue;
    bool inc;
protected:
    FishPart* eyes;
    FishPart* body;
    FishPart* mouth;
public:
    Tuna(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID);
    void updateShear();
    void updateTranslation();
    void setTranslation(float x, float y, float z);
    void setScaling(float s);
    void invert(bool z);
    bool draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
