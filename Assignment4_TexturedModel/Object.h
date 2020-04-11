#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

/**
 * Class for parsing and storing object information from a .obj file
 */
class Object
{


private:

    struct VertexData {
        float x, y, z;
        float s, t;

        VertexData(float _x, float _y, float _z, float _s, float _t) : x(_x), y(_y), z(_z), s(_s), t(_t) { }

        VertexData(QVector3D pos, QVector2D tex) : x(pos[0]), y(pos[1]), z(pos[2]), s(tex[0]), t(tex[1]) { }

        // Tests if two VertexData are equal
        bool operator== (const VertexData& rhs) {
            if ((x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (s == rhs.s) && (t == rhs.t)) {
                return true;
            }
            return false;
        }

        std::string toString() {
            return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," + std::to_string(s) + "," + std::to_string(t) + ")";
        }
    };

    // Relative path is path to a file, returns a vector
    // with path @ 0 and name @ 1
    std::vector<std::string> getFilePathAndName(std::string relativePath);
    std::vector<std::string> splitString(std::string splitMe, char token);

    // Each renderable has its own model matrix
    QMatrix4x4 modelMatrix_;

    // We have a single draw call, so a single vao
    QOpenGLVertexArrayObject vao_;
    // Keep track of how many triangles we actually have to draw in our ibo

    // For now, we have only one texture per object
    QOpenGLTexture texture_;

    // For now, we have only one shader per object
    QOpenGLShaderProgram shader_;

    // For now, we have a single unified buffer per object
    QOpenGLBuffer vbo_;

    // Make sure we have an index buffer.
    QOpenGLBuffer ibo_;

    void loadVertexBuffer();
    void loadIndexBuffer();

    unsigned int numTris_;
    int vertexSize_;

    // Create our shader and fix it up
    void createShaders();

    void parseMtl(std::string mtlFile);
    void parseObjFile(std::string fileToParse);


protected:


public:



    QVector<QVector3D> vertices;
    QVector<QVector3D> normalVertices;
    QVector<QVector2D> texCoords;

    QVector<VertexData> indexedVertices;

    QVector<unsigned int> vertexIndices;

    int numVerts;
    int numIndices;

    ////TODO: why virtual?
    //virtual void update(const qint64 msSinceLastFrame);
    //virtual void draw(const QMatrix4x4& view, const QMatrix4x4& projection);

    //TODO: this is never called?
    void setModelMatrix(const QMatrix4x4& transform);

    virtual void draw();


    Object(std::string fileToParse);
    ~Object();
};
