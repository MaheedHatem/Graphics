#ifndef SHARK_H
#define SHARK_H
#include "Obj/Obj.h"
#include "FishPart.h"
class Shark : public Obj {
private:
    float shearvalue;
    bool inc;
protected:
FishPart* body;

public:
    Shark(float x , float y , float z , float s, GLuint TextureID,
          GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID);
    void updateTranslation();
    void setTranslation(float x, float y, float z);
    void setScaling(float s);
    void updateShear();
    void invert(bool z);
    bool draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix);
};
#endif
