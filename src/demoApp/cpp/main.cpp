#include <QtCore/QCoreApplication>
#include <QDebug>

#include "DemoApp.h"

int main(int argc, char *argv[])
{
  QCoreApplication coreApp(argc, argv);

  DemoApp* demoApp = new DemoApp();

  int exitCode = 0;
  bool status = demoApp->processCommandLine(coreApp.arguments());

  if (status) {
    status = demoApp->prepare();
  }

  if (status) {
    exitCode = coreApp.exec();
  }
  else {
    exitCode = demoApp->getAppExitCode();
  }

  delete demoApp;

  return exitCode;
}
