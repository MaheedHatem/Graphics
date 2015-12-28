#ifndef FAWZY_H
#define FAWZY_H
#include "Obj/Obj.h"
#include "FishPart.h"
class Fawzy : public Obj {
private:
    float x;
    float y;
    float z;
    float dx;
    float dy;
    bool right;
    void updateShear();
    float shearvalue;
    bool inc;
protected:
FishPart* body;

public:
    Fawzy(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID);
    void setTranslation(float x, float y, float z);
    void setScaling(float s);
    void invert(bool z);
    void movehoriz(bool r);
    void movevertic(bool u);
    bool draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
