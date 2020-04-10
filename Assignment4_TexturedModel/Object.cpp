
#include "Object.h"


Object::Object(std::string fileToParse) : vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer), texture_(QOpenGLTexture::Target2D), numTris_(0), vertexSize_(0), 
vertices(QVector<QVector3D>()), normalVertices(QVector<QVector3D>()), texCoords(QVector<QVector2D>()), vertexIndices(QVector<unsigned int>()), indexedVertices(QVector<VertexData>())
{
    //TODO:
    //      MVP matrices
    //      Read from command line
    //      Would probably be much easier to make a class for vertices, and keep a list of them

    parseObjFile(fileToParse);
    createShaders();

    vao_.create();
    vao_.bind();
    vbo_.create();
    vbo_.bind();
    loadVertexBuffer();
    ibo_.create();
    ibo_.bind();
    loadIndexBuffer();

    shader_.enableAttributeArray(0);
    shader_.setAttributeBuffer(0, GL_FLOAT, 0, 3, 5 * sizeof(float));
    shader_.enableAttributeArray(1);
    shader_.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));

    vao_.release();
    vbo_.release();
    ibo_.release();
}

Object::~Object() {
    if (texture_.isCreated()) {
        texture_.destroy();
    }
    if (vbo_.isCreated()) {
        vbo_.destroy();
    }
    if (ibo_.isCreated()) {
        ibo_.destroy();
    }
    if (vao_.isCreated()) {
        vao_.destroy();
    }
}

void Object::parseMtl(std::string mtlFile) {
    std::ifstream stream;
    stream.open(mtlFile);
    
    std::string path = getFilePathAndName(mtlFile).at(0);
    
    std::string line;

    while (stream.is_open() && getline(stream, line)) {

        std::vector<std::string> data = splitString(line, ' ');
        if (data.size() <= 1) {
            continue;
        }
        else if (data.at(0).compare("map_Kd") == 0 && data.size() == 2) {
            texture_.setData(QImage(QString::fromStdString(path + data.at(1))));
            stream.close();
            return;
        }
    }
    stream.close();


    qDebug() << "ERROR: Texture File not found in file " << QString::fromStdString(mtlFile) << "!!\n";
}

// split string by token
std::vector<std::string> Object::splitString(std::string splitMe, char token) {
    std::vector<std::string> split;
    int prevIndex = 0;

    for (int i = 0; i < splitMe.length(); i++) {
        if (splitMe.at(i) == token) {
            split.push_back(splitMe.substr(prevIndex, i - prevIndex));
            prevIndex = i + 1;
        }
    }

    split.push_back(splitMe.substr(prevIndex, splitMe.length() - prevIndex));

    return split;
}


std::vector<std::string> Object::getFilePathAndName(std::string relativePath) {
    std::vector<std::string> splitBySlash = splitString(relativePath, '/');
    std::vector<std::string> filePathName;
    std::string filePath;
    int lastIdx = splitBySlash.size() - 1;
    for (int i = 0; i < lastIdx; i++) {
        filePath = filePath + splitBySlash.at(i) + "/";
    }
    filePathName.push_back(filePath);
    filePathName.push_back(splitBySlash.at(lastIdx));
    return filePathName;
}

void Object::parseObjFile(std::string fileToParse) {
    std::string mtlFile;


    numVerts = 0;
    numIndices = 0;

    std::ifstream objFile;

    objFile.open(fileToParse);
    std::vector<std::string> fpName = getFilePathAndName(fileToParse);
    std::string path = fpName.at(0);

    std::string line;

    while (objFile.is_open() && getline(objFile, line)) {

        std::vector<std::string> data = splitString(line, ' ');
        if (data.size() <= 1) {
            continue;
        }
        else if (data.at(0).compare("mtllib") == 0 && data.size() == 2) {
            mtlFile = path + data.at(1);
        }

        else if (data.at(0).compare("v") == 0 && data.size() == 4) {
            QVector3D vertex = QVector3D(std::stof(data.at(1)), std::stof(data.at(2)), std::stof(data.at(3)));
            vertices.append(vertex);
            numVerts += 3;
        }
        else if (data.at(0).compare("vt") == 0 && data.size() == 3) {
            QVector2D texCoord = QVector2D(std::stof(data.at(1)), std::stof(data.at(2)));
            texCoords.append(texCoord);
        }
        else if (data.at(0).compare("vn") == 0 && data.size() == 4) {
            QVector3D vertexNormal = QVector3D(std::stof(data.at(1)), std::stof(data.at(2)), std::stof(data.at(3)));
            normalVertices.append(vertexNormal);
        }

        else if (data.at(0).compare("f") == 0 && data.size() == 4) {


            for (int i = 0; i < 3; i++) {
                std::string slashedFaceIdx = data.at(i + 1);
                std::vector<std::string> idxData = splitString(slashedFaceIdx, '/');

                VertexData newVert = VertexData(vertices.at((std::stoi(idxData.at(0)) - 1)), texCoords.at(std::stoi(idxData.at(1)) - 1));
                int idx = indexedVertices.indexOf(newVert);
                
                if (idx != -1) {
                    vertexIndices.append(idx);
                }
                else {
                    indexedVertices.append(newVert);
                    vertexIndices.append(indexedVertices.size() - 1);
                }

            }
            numIndices += 3;
        }
    }
    objFile.close();

    parseMtl(mtlFile);
}


void Object::createShaders() {

    QString vertexFilename = "../vert.glsl";
    bool ok = shader_.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexFilename);
    if (!ok) {
        qDebug() << shader_.log();
    }
    QString fragmentFilename = "../frag.glsl";
    ok = shader_.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentFilename);
    if (!ok) {
        qDebug() << shader_.log();
    }
    ok = shader_.link();
    if (!ok) {
        std::cout << "ERROR with shader :(" << std::endl;
        qDebug() << shader_.log();
    }    
}



void Object::loadVertexBuffer()
{
    float* verticesPtr = (float*)malloc(sizeof(float) * 5 * indexedVertices.size());

    for (int i = 0; i < indexedVertices.size(); i++) {
        verticesPtr[(5 * i) + 0] = indexedVertices.at(i).x;
        verticesPtr[(5 * i) + 1] = indexedVertices.at(i).y;
        verticesPtr[(5 * i) + 2] = indexedVertices.at(i).z;
        verticesPtr[(5 * i) + 3] = indexedVertices.at(i).s;
        verticesPtr[(5 * i) + 4] = indexedVertices.at(i).t;
    }


    vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);


    vbo_.allocate(verticesPtr, indexedVertices.size() * 5 * sizeof(float));

    delete[] verticesPtr;

}

void Object::loadIndexBuffer()
{
    
    unsigned int* indicesPtr = (unsigned int*)malloc(vertexIndices.size() * sizeof(unsigned int));

    for (int i = 0; i < vertexIndices.size(); i++) {
        indicesPtr[i] = vertexIndices.at(i);
    }


    ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo_.allocate(indicesPtr, vertexIndices.size() * sizeof(GL_UNSIGNED_INT));

    delete[] indicesPtr;
}


void Object::draw()
{
    shader_.bind();
    vao_.bind();
    texture_.bind();

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    texture_.release();
    vao_.release();
    shader_.release();
}