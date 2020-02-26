#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Object.h"

std::vector<std::string> splitString(std::string splitMe, char token);

Object::Object(std::string fileToParse) {
    std::ifstream objFile;

    objFile.open(fileToParse);

    std::string line;

    while (objFile.is_open() && getline(objFile, line)) {
      
        std::vector<std::string> data = splitString(line, ' ');

        if (data.size() <= 1) {
            continue;
        }
        else if (data.at(0).compare("v") == 0 && data.size() == 4) {
            GLfloat* vertex = (GLfloat*) malloc(3 * sizeof(GLfloat));
            vertex[0] = std::stof(data.at(1));
            vertex[1] = std::stof(data.at(2));
            vertex[2] = std::stof(data.at(3));
            vertices.push_back(vertex);
        }
        else if (data.at(0).compare("vn") == 0 && data.size() == 4) {
            GLfloat* vertexNormal = (GLfloat*) malloc(3 * sizeof(GLfloat));;
            vertexNormal[0] = std::stof(data.at(1));
            vertexNormal[1] = std::stof(data.at(2));
            vertexNormal[2] = std::stof(data.at(3));
            normalVertices.push_back(vertexNormal);
        }
        else if (data.at(0).compare("f") == 0 && data.size() == 4) {
            GLuint* face = (GLuint*) malloc(6 * sizeof(GLuint));
            for (int i = 0; i < 3; i++) {
                std::string slashedFaceIdx = data.at(i + 1);
                int pos = slashedFaceIdx.find('/');
                if (pos != std::string::npos)
                    slashedFaceIdx.erase(pos, 1);
                std::vector<std::string> idxNormalIdxTouple = splitString(slashedFaceIdx, '/');
                face[i] = std::stoi(idxNormalIdxTouple.at(0)) - 1;
                face[3 + i] = std::stoi(idxNormalIdxTouple.at(1)) - 1;
            }
            faces.push_back(face);
        }
    }
    objFile.close();
}

Object::~Object() {
    for (int i = 0; i < vertices.size(); i++) {
        delete[] vertices.at(i);
    }

    for (int i = 0; i < normalVertices.size(); i++) {
        delete[] normalVertices.at(i);
    }

    for (int i = 0; i < faces.size(); i++) {
        delete[] faces.at(i);
    }

}

// split string by token
std::vector<std::string> splitString(std::string splitMe, char token) {
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

GLuint* Object::consolidateIndices() {

    const int numInts = 3 * faces.size();
    GLuint* indices = (GLuint*)malloc(numInts * sizeof(GL_UNSIGNED_INT));
    for (int i = 0; i < faces.size(); i++) {
        indices[3 * i + 0] = faces.at(i)[0];
        indices[3 * i + 1] = faces.at(i)[1];
        indices[3 * i + 2] = faces.at(i)[2];
    }
    return indices;
}

GLfloat* Object::consolidateVertices() {
    const int numFloats = 3 * vertices.size();
    GLfloat* allVertices = (GLfloat*)malloc(numFloats * sizeof(GL_FLOAT));

    for (int i = 0; i < vertices.size(); i++) {
        allVertices[3 * i + 0] = vertices.at(i)[0];
        allVertices[3 * i + 1] = vertices.at(i)[1];
        allVertices[3 * i + 2] = vertices.at(i)[2];
    }

    return allVertices;
}