/**
 * The primary application code.
 */

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

class Application : public QMainWindow
{
  Q_OBJECT

public:
  Application(std::string objFile, QWidget* parent=0);
  virtual ~Application();
  
signals:

public slots:

private:
  std::string objFile;
  void buildGui();
};
