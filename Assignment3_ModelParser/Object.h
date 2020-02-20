#include <vector>
#include <QtOpenGL>

/**
 * Class for parsing and storing object information from a .obj file
 */
class Object
{


private:
    



protected:


public:
    // pointers to arrays
    std::vector<float*> vertices;
    std::vector<float*> normalVertices;
    std::vector<int*> faces;
    // each face is an int[6], face[0-2] = idx in vertices, face[3-5] = idx in normalVertices

    //returns vertices as an array
    GLfloat* consolidateVertices();
    
    //returns indices as an array
    GLuint* consolidateIndices();

    Object(std::string fileToParse);
    ~Object();

};
