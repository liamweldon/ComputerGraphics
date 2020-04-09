#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include "Object.h"


#define DEFAULT_OBJ_FILE "../objects/house/house_obj.obj"
#define TEXTURED_OBJ true

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

private:

    QString vertexShaderString() const;
    QString fragmentShaderString() const;
    void createShader();
    QOpenGLVertexArrayObject vao_;

    void displayObject(GLuint vboID, GLuint iboID, Object* obj);

    void loadVertexBuffer(GLuint* bufferID, Object* obj);
    void loadIndexBuffer(GLuint* bufferID, Object* obj);

    Object* obj1;

protected:
    GLuint vboID_;
    GLuint iboID_;
    unsigned int shaderID_;
    unsigned int compileShader(unsigned int type, const QString& shaderSrc);


  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();
  
  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}
};
