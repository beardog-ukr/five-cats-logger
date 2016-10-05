#include <QCoreApplication>

#include <QDebug>

#include "AppTestA.h"

//=============================================================================
//=============================================================================
//=============================================================================

int main(int argc, char* argv[])
{
  QCoreApplication app(argc,argv);
  AppTestA appTestA;

  if (!appTestA.processCommandLine()) {
    return appTestA.getAppExitCode();
  }

  if (!appTestA.prepareToStart()) {
    return appTestA.getAppExitCode();
  }

  qDebug() << "Starting event loop..." ;

  return app.exec();
}
