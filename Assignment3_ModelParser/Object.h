#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <QtOpenGL>

/**
 * Class for parsing and storing object information from a .obj file
 */
class Object
{


private:
    

    std::vector<std::string> splitString(std::string splitMe, char token);


protected:


public:
    // pointers to arrays
    std::vector<GLfloat*> vertices;
    std::vector<GLfloat*> normalVertices;
    std::vector<GLuint*> faces;
    std::vector<GLuint*> facesNormal;

    int numVerts;
    int numIndices;

    //returns vertices as an array
    GLfloat* consolidateVertices();
    
    //returns indices as an array
    GLuint* consolidateIndices();

    Object(std::string fileToParse, bool texturedObj);
    ~Object();

};
