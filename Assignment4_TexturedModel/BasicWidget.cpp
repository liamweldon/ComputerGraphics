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
  camera_.setPosition(QVector3D(0.5, 0.5, -2.0));
  camera_.setLookAt(QVector3D(0.5, 0.5, 0.0));
  world_.setToIdentity();
}

BasicWidget::~BasicWidget()
{
    delete obj1;
}
void BasicWidget::setObjFile(std::string objFile) {
    this->objFile = objFile;
}

void BasicWidget::mousePressEvent(QMouseEvent* mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        mouseAction_ = Rotate;
    }
    else if (mouseEvent->button() == Qt::RightButton) {
        mouseAction_ = Zoom;
    }
    lastMouseLoc_ = mouseEvent->pos();
}

void BasicWidget::mouseMoveEvent(QMouseEvent* mouseEvent)
{
    if (mouseAction_ == NoAction) {
        return;
    }
    QPoint delta = mouseEvent->pos() - lastMouseLoc_;
    lastMouseLoc_ = mouseEvent->pos();
    float deltaY = (float)delta.y() * .01;
    float deltaX = (float)delta.x() * .01;
    if (mouseAction_ == Rotate) {
        camera_.translateLookAt(QVector3D(deltaX, deltaY, 0.0f));
    }
    else if (mouseAction_ == Zoom) {
        camera_.translateCamera(deltaY * camera_.gazeVector());
    }
    update();
}

void BasicWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    mouseAction_ = NoAction;
}

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
    if (keyEvent->key() == Qt::Key_W) {
        wireframeMode = !wireframeMode;
        update();
    }
    else if (keyEvent->key() == Qt::Key_R) {
        camera_.setPosition(QVector3D(0.5, 0.5, -2.0));
        camera_.setLookAt(QVector3D(0.5, 0.5, 0.0));
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

  if (objFile.empty()) {
      obj1 = new Object(DEFAULT_OBJ_FILE);
  }
  else {
      obj1 = new Object(objFile);
  }
  glViewport(0, 0, width(), height());
  frameTimer_.start();
}

void BasicWidget::resizeGL(int w, int h)
{
  camera_.setPerspective(70.f, (float)w / (float)h, 0.001, 1000.0);
  glViewport(0, 0, w, h);
}


void BasicWidget::paintGL()
{
  qint64 msSinceRestart = frameTimer_.restart();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);


  glClearColor(0.f, 0.f, 0.f, 0.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);

  obj1->update(msSinceRestart);
  obj1->draw(world_, camera_.getViewMatrix(), camera_.getProjectionMatrix());
  update();
}