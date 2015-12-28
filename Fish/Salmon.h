#ifndef SALMON_H
#define SALMON_H
#include "Obj/Obj.h"
#include "FishPart.h"
class Salmon : public Obj {
private:
    void updateShear();
    float shearvalue;
    bool inc;
protected:
FishPart* eyes;
FishPart* body;
FishPart* mouth;
public:
    Salmon(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID);
    void setTranslation(float x, float y, float z);
    void setScaling(float s);
    void invert(bool z);
    bool draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
