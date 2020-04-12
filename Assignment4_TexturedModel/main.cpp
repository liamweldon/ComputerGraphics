/**
 * Support code written by Erik W. Anderson
 */

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

// Lab application
#include "Application.h"

// allows us to pass in Windows or Unix paths
std::string replaceBackSlash(std::string filePath) {
    for (int i = 0; i < filePath.length(); i++) {
        if (filePath.at(i) == '\\' ) {
            filePath.replace(i, 1, "/");
    }
}
return filePath;
}

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  QString appDir = a.applicationDirPath();
  QDir::setCurrent(appDir);

  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);
  fmt.setStencilBufferSize(8);
  //TODO: maybe comment out
  fmt.setVersion(3,3);
  fmt.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(fmt);
  std::string objFile; 
  if (argc == 2) {
      objFile = replaceBackSlash(std::string(argv[1]));
  }
  Application app(objFile);
 


  app.show();
  return QApplication::exec();
}

