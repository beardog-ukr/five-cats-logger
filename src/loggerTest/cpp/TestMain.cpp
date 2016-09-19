#include "TestFiveCatsLogger.h"

#include <QCoreApplication>

int main(int argc, char ** argv)
{
  QCoreApplication coreApp(argc,argv);

  QStringList testCmd;

  TestFiveCatsLogger testFiveCatsLogger;
  QTest::qExec(&testFiveCatsLogger,testCmd);

  return 0;
}
