#include "TestFiveCatsLogger.h"

int main(int , char **)
{
  QStringList testCmd;

  TestFiveCatsLogger testFiveCatsLogger;
  QTest::qExec(&testFiveCatsLogger,testCmd);

  return 0;
}
