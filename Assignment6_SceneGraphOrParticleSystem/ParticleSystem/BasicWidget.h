#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include "Object.h"
#include "Camera.h"
#include "Emitter.h"

#define DEFAULT_OBJ_FILE "../objects/capsule/capsule.obj"
#define TEXTURED_OBJ true

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

private:
    QMatrix4x4 world_;
    Camera camera_;
    Emitter* em_;

    bool wireframeMode = false;
    bool stopRotating = true;

    QElapsedTimer frameTimer_;

    std::string objFile;
    Object* obj1;

    // Mouse controls.
    enum MouseControl { NoAction = 0, Rotate, Zoom };
    QPoint lastMouseLoc_;
    MouseControl mouseAction_;

protected:


  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;
  void mousePressEvent(QMouseEvent* mouseEvent) override;
  void mouseMoveEvent(QMouseEvent* mouseEvent) override;
  void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

public:
  BasicWidget(QWidget* parent=nullptr);
  void setObjFile(std::string objFile);
  virtual ~BasicWidget();
  
  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}
};
