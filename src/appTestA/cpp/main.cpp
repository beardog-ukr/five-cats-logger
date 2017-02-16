#include <QCoreApplication>

#include <QDebug>

#include "AppTestA.h"
#include "Functions.h"


//=============================================================================
//=============================================================================
//=============================================================================

int main(int argc, char* argv[])
{
  QCoreApplication app(argc,argv);
  AppTestA appTestA;

  if (!appTestA.processCommandLine()) {
    qDebug() << appTestA.getErrorMessage() ;
    return appTestA.getAppExitCode();
  }

  if (!appTestA.prepareToStart()) {
    qDebug() << appTestA.getErrorMessage() ;
    return appTestA.getAppExitCode();
  }

  performTestWithFunctions(appTestA.getLoggerInstance());

  //qDebug() << "Starting event loop..." ;

  return app.exec();
}
