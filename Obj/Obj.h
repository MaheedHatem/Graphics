#ifndef OBJ_H
#define OBJ_H
class Obj{
protected:
    //All matrices

    glm::mat4 TranslationMatrix;
    glm::mat4 ShearMatrix;
    glm::mat4 ScalingMatrix;
    //Body
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normbuffer;
    GLuint Texture;
    //IDs from main
    GLuint TextureID ,vertexUVID , vertexPosition_modelspaceID , MatrixID;

public:

    Obj(float x , float y , float z , float s, GLuint TextureID,
         GLuint vertexUVID,GLuint vertexPosition_modelspaceID , GLuint MatrixID);
    virtual void setTranslation(float x, float y, float z);
    virtual void setScaling(float s);
    virtual void invert(bool z);
    virtual bool draw( glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix) = 0;
    ~Obj();
};
#endif
