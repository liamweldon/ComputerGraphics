#include <iostream>
#include "BasicWidget.h"

void errorLog(int loc) {
    std::cout << "----------------" << std::to_string(loc) << "----------------" << std::endl;
    std::cout << glGetError() << std::endl;
}

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
    glDeleteProgram(shaderID_);
    glDeleteBuffers(1, &vboID_);
    glDeleteBuffers(1, &iboID_);

    delete obj1;
}

//////////////////////////////////////////////////////////////////////
// Privates

//TODO: Lab7 Shaders
QString BasicWidget::vertexShaderString() const
{
    QString str =
        "#version 330\n"
        "layout(location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\n";
    return str;
}

QString BasicWidget::fragmentShaderString() const
{
    QString str =
        "#version 330\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "  color = vec4(0.8f, 0.1f, 0.6f, 1.0f);\n"
        "}\n";
    return str;
}

void BasicWidget::createShader()
{
    unsigned int prog = glCreateProgram();
    unsigned int vert = compileShader(GL_VERTEX_SHADER, vertexShaderString());
    unsigned int frag = compileShader(GL_FRAGMENT_SHADER, fragmentShaderString());
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glValidateProgram(prog);

    // The shaders are build and ready to use.  We can now detach the individual shaders and destroy them
    glDetachShader(prog, vert);
    glDetachShader(prog, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);

    // Assign here in case there are failures we need to bail on - This has not yet been implemented, though.
    shaderID_ = prog;
}

unsigned int BasicWidget::compileShader(unsigned int type, const QString& shaderSrc)
{
    unsigned int id = glCreateShader(type);
    // Make sure we can create the shader
    if (id == 0) {
        return 0;
    }
    QByteArray ba = shaderSrc.toLocal8Bit();
    const char* src = ba.data();
    // Set the source
    glShaderSource(id, 1, &src, nullptr);
    // Compile
    glCompileShader(id);
    // Retrieve the result of our compilation
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* errorMessages = new char[length]; // Could also use alloca here.
        glGetShaderInfoLog(id, length, &length, errorMessages);
        if (type == GL_VERTEX_SHADER) {
            qDebug() << "ERROR: GL_VERTEX_SHADER compilation failed!\n" << errorMessages << "\n";
        }
        else if (type == GL_FRAGMENT_SHADER) {
            qDebug() << "ERROR: GL_FRAGMENT_SHADER compilation failed!\n" << errorMessages << "\n";
        }
        // Reclaim our memory
        delete[] errorMessages;
        // Delete our broken shader
        glDeleteShader(id);
        return 0;
    }

    return id;
}

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{

    if (keyEvent->key() == Qt::Key_1) {
        update();
    }
    else if (keyEvent->key() == Qt::Key_2) {
        update();
    }
    else {
        qDebug() << "You Pressed an unsupported Key!";
    }
}
void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();

  QOpenGLContext* curContext = this->context();
  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
  qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
  qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
  qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  createShader();

  obj1 = new Object(DEFAULT_OBJ_FILE);

  vao_.create();
  vao_.bind();

  loadVertexBuffer(&vboID_, obj1);

  loadIndexBuffer(&iboID_, obj1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  vao_.release();

  glViewport(0, 0, width(), height());

}

void BasicWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void BasicWidget::loadVertexBuffer(GLuint* bufferID, Object* obj)
{
    QVector<QVector3D> verticesVec = obj->vertices;
   

    float* vertices = (float*)malloc(sizeof(float) * 3 * verticesVec.size());

    for (int i = 0; i < verticesVec.size(); i++) {
        vertices[(3 * i) + 0] = verticesVec.at(i)[0];
        vertices[(3 * i) + 1] = verticesVec.at(i)[1];
        vertices[(3 * i) + 2] = verticesVec.at(i)[2];
    }

    glGenBuffers(1, bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, *bufferID);
    glBufferData(GL_ARRAY_BUFFER, obj->numVerts * sizeof(GL_FLOAT), vertices, GL_STATIC_DRAW);

    delete[] vertices;
}

void BasicWidget::loadIndexBuffer(GLuint* bufferID, Object* obj)
{
    QVector<unsigned int> indicesVec = obj->vertexIndices;
    unsigned int* indices = (unsigned int*)malloc(indicesVec.size() * sizeof(unsigned int));

    for (int i = 0; i < indicesVec.size(); i++) {
        indices[i] = indicesVec.at(i);
    }

    glGenBuffers(1, bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj->numIndices * sizeof(GL_UNSIGNED_INT), indices, GL_STATIC_DRAW);

    delete[] indices;
}

void BasicWidget::paintGL()
{
  vao_.bind();

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(1.f, 1.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderID_);
 
  glEnableVertexAttribArray(0);

  displayObject(vboID_, iboID_, obj1);
  glDisableVertexAttribArray(0);
  glUseProgram(NULL);
  vao_.release();
}


void BasicWidget::displayObject(GLuint vboID, GLuint iboID, Object* obj) {
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0,        // Attribute 1 matches our layout for vertex positions
        3,        // Size
        GL_FLOAT, // Type
        GL_FALSE, // Not normalized
        0,        // Stride - no interleaving
        (void*)0  // nullptr
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, obj->numIndices, GL_UNSIGNED_INT, nullptr);
}

