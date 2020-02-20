#include <iostream>
#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const
{
    QString str =
        "#version 330\n"
        "layout(location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = vec4(position, 1.0);\n"
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
        showObj1 = true;
        update();
    }
    if (keyEvent->key() == Qt::Key_2) {
        showObj1 = false;
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
  obj2 = new Object(ALTERNATE_OBJ_FILE);

  numVertsObj1 = 3 * obj1->vertices.size();
  numIndicesObj1 = 3 * obj1->faces.size();
  GLfloat* obj1Vertices = obj1->consolidateVertices();
  GLuint* obj1Indices = obj1->consolidateIndices();

  numVertsObj2 = 3 * obj2->vertices.size();
  numIndicesObj2 = 3 * obj2->faces.size();
  GLfloat* obj2Vertices = obj2->consolidateVertices();
  GLuint* obj2Indices = obj2->consolidateIndices();

  vao_.create();
  vao_.bind();

  glGenBuffers(1, &vboID_);
  glBindBuffer(GL_ARRAY_BUFFER, vboID_);
  glBufferData(GL_ARRAY_BUFFER, numVertsObj1 * sizeof(GL_FLOAT), obj1Vertices, GL_STATIC_DRAW);


  glGenBuffers(1, &iboID_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicesObj1 * sizeof(GLuint), obj1Indices, GL_STATIC_DRAW);

  glGenBuffers(1, &vboID2_);
  glBindBuffer(GL_ARRAY_BUFFER, vboID2_);
  glBufferData(GL_ARRAY_BUFFER, numVertsObj2 * sizeof(GL_FLOAT), obj2Vertices, GL_STATIC_DRAW);


  glGenBuffers(1, &iboID2_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID2_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicesObj2 * sizeof(GLuint), obj2Indices, GL_STATIC_DRAW);


  vao_.release();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glViewport(0, 0, width(), height());

  delete[] obj1Indices;
  delete[] obj1Vertices;
  delete[] obj2Indices;
  delete[] obj2Vertices;
  delete obj1;
  delete obj2;

}

void BasicWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderID_);
 
  int disable = 0;

  if (showObj1) {
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vboID_);
      glVertexAttribPointer(0,        // Attribute 0 matches our layout for vertex positions
          numVertsObj1,        // Size
          GL_FLOAT, // Type
          GL_FALSE, // Not normalized
          0,        // Stride - no interleaving
          (void*)0  // nullptr
      );

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID_);
      glDrawElements(GL_TRIANGLES, numIndicesObj1, GL_UNSIGNED_INT, nullptr);
      disable = 0;
  } 
  else {
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, vboID2_);
      glVertexAttribPointer(1,        // Attribute 1 matches our layout for vertex positions
          numVertsObj2,        // Size
          GL_FLOAT, // Type
          GL_FALSE, // Not normalized
          0,        // Stride - no interleaving
          (void*)0  // nullptr
      );

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID2_);
      glDrawElements(GL_TRIANGLES, numIndicesObj2, GL_UNSIGNED_INT, nullptr);
      disable = 1;
  }
  glDisableVertexAttribArray(disable);
  glUseProgram(NULL);

}


