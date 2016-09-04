#ifndef __DemoApp__
#define __DemoApp__

#include <QObject>
#include <QStringList>

class QTimer;

class FiveCatsLogger;

class DemoApp : public QObject
{
  Q_OBJECT
public:
  DemoApp(QObject *parent = 0);
  virtual ~DemoApp();

  bool prepare();
  bool processCommandLine(const QStringList &arguments);

  int getAppExitCode() const;

public slots:
  void launch();

protected:
  int appExitCode;

  QTimer* startupTimer;

  QString lineToPrint;

  FiveCatsLogger* c5;
};



#endif
