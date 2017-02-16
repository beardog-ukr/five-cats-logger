#ifndef __AppTestA__
#define __AppTestA__

#include <QObject>
#include <string>

class FiveCatsLogger;

class QTimer;

#include <QStringList>

// === =======================================================================

class AppTestA : public QObject
{
  Q_OBJECT
public:
  AppTestA(QObject *parent = 0);
  virtual ~AppTestA();

  bool prepareToStart();
  bool processCommandLine();

  FiveCatsLogger* getLoggerInstance();

  QString getErrorMessage();
  int getAppExitCode() const;

public slots:
  void action();

protected:
  QTimer* timer;
  int delay;
  int counter;
  int counterLimit;

  QString errorMessage;
  int appExitCode ;

  FiveCatsLogger* c5;

  void testDirectCall();
  void testFunctionCall();
};

// === =======================================================================

#endif
