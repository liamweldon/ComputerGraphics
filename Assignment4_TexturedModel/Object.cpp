
#include "Object.h"


Object::Object(std::string fileToParse) : vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer), texture_(QOpenGLTexture::Target2D), numTris_(0), vertexSize_(0)
{
    //TODO: use getFilePathAndName to correctly get correct mtllib & texture file paths
    //      Actually draw everything
    //      MVP matrices
    //      Read from command line
    //      Would probably be much easier to make a class for vertices, and keep a list of them

    vertices = QVector<QVector3D>();
    normalVertices = QVector<QVector3D>();
    texCoords = QVector<QVector2D>();
    
    std::string mtlFile;


    numVerts = 0;
    numIndices = 0;

    std::ifstream objFile;
    
    objFile.open(fileToParse);

    std::string line;

    while (objFile.is_open() && getline(objFile, line)) {
      
        std::vector<std::string> data = splitString(line, ' ');

        if (data.size() <= 1) {
            continue;
        }
        else if (data.at(0).compare("mtllib") && data.size == 2) {
            mtlFile = data.at(1);
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
                vertexIndices.append(std::stoi(idxData.at(0)) - 1);
                textureIndices.append(std::stoi(idxData.at(1)) - 1);
                normalIndices.append(std::stoi(idxData.at(2)) - 1);
            }
            numIndices += 3;
        }
    }
    objFile.close();

    parseMtl(mtlFile);
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

    std::string line;

    while (stream.is_open() && getline(stream, line)) {

        std::vector<std::string> data = splitString(line, ' ');
        if (data.size() <= 1) {
            continue;
        }
        else if (data.at(0).compare("map_Kd") && data.size == 2) {
            texture_.setData(QImage(QString::fromStdString(data.at(1))));
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
    int lastIdx = splitBySlash.size - 1;
    for (int i = 0; i < lastIdx; i++) {
        filePath = filePath + splitBySlash.at(i);
    }
    filePathName.push_back(filePath);
    filePathName.push_back(splitBySlash.at(lastIdx));
}