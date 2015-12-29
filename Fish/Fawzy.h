#ifndef FAWZY_H
#define FAWZY_H
#include "Obj/Obj.h"
#include "FishPart.h"
class Fawzy : public Obj {
private:
    float dx;
    float dy;
    bool right;
    float shearvalue;
    bool inc;
protected:
FishPart* body;

public:
    float x;
    float y;
    float z;
    float xMouthPosition;
    float yMouthPosition;
    Fawzy(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID);
    void updateShear();
    void setTranslation(float x, float y, float z);
    void setScaling(float s);
    void invert(bool z);
    void movehoriz(bool r);
    void movevertic(bool u);
    bool draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
