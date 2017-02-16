#include "AppTestA.h"
#include "FiveCatsLogger.h"

#include <QTimer>
//#include <QDebug>

// === =======================================================================

AppTestA::AppTestA(QObject* parent)
             :QObject(parent){
  timer = 0;
  delay = 500;
  counter = 0;
  counterLimit = 1;

  errorMessage = "";

  c5 = new FiveCatsLogger(FiveCatsLogger::Info);
}

// === =======================================================================

AppTestA::~AppTestA() {
  delete timer;
  delete c5;
}

// === =======================================================================

bool AppTestA::processCommandLine() {
  bool result = true;

  QCommandLineParser parser;
  parser.setApplicationDescription("Test \"A\" application. Writes a lot ob debug messages in various ways");
  parser.addHelpOption();
  parser.addVersionOption();

  // command line options
  QCommandLineOption timeao("tc","Time between writes (ms, default 500)", "tc");
  parser.addOption(timeao);

  QCommandLineOption numao("num","Number of write attempts (0 for infinite, 1 by default)", "num");
  parser.addOption(numao);

  c5->initCommandLineParser(parser);

  // Process the actual command line arguments given by the user
  QCoreApplication* ca = QCoreApplication::instance();
  parser.process(*ca);

  QString tmps;
  tmps = parser.value("tc");
  if (!tmps.isEmpty()) {
    bool  convOk = true;
    delay = tmps.toInt(&convOk);
    if (!convOk) {
      errorMessage = "Bad delay option (--tc)";
      return false;
    }
  }

  tmps = parser.value("num");
  if (!tmps.isEmpty()) {
    bool  convOk = true;
    counterLimit = tmps.toInt(&convOk);
    if (!convOk) {
      errorMessage = "Bad delay option (--num)";
      return false;
    }
  }

  c5->loadCommandLineParser(parser);

  return result;
}

// === =======================================================================

bool AppTestA::prepareToStart() {
  timer = new QTimer(this) ;
  connect(timer, SIGNAL(timeout()),this, SLOT(action()) );
  timer->start(delay);

//  c5d(c5, __c5_MN__, QString("Started %1\n").arg(delay) ) ;
//  qDebug() <<"Started " << delay ;
  return true;
}

// === =======================================================================

void AppTestA::action() {
//  c5d(c5, __c5_MN__, QString("Writing %1\n").arg(counter) ) ;
//  qDebug() <<"Action " << counter;
  testDirectCall();
  testFunctionCall();

  //
  counter++ ;
  if ((counterLimit>0)&&(counter>=counterLimit)) {
    QCoreApplication::exit(0);
  }
}

// === =======================================================================

int AppTestA::getAppExitCode() const {
  return appExitCode;
}

// === =======================================================================

FiveCatsLogger* AppTestA::getLoggerInstance() {
  return c5;
}

// === =======================================================================

QString AppTestA::getErrorMessage() {
  return errorMessage;
}

// === =======================================================================
//  This method invokes methods from c5 object
void AppTestA::testDirectCall() {
  //object method call, without metaInfo
  const QString bmsg = "obj dc ";

  c5->c(bmsg + "Critical Message");
  c5->w(bmsg + "Warning Message");
  c5->i(bmsg + "Info Message");
  c5->d(bmsg + "Debug Message");
  c5->t(bmsg + "Trace Message");
  c5->f(bmsg + "Flood Message");

  //object method call, with some additional message
  c5->c("OCM", bmsg + "Critical Message");
  c5->w("OWM", bmsg + "Warning Message");
  c5->i("OIM", bmsg + "Info Message");
  c5->d("ODM", bmsg + "Debug Message");
  c5->t("OTM", bmsg + "Trace Message");
  c5->f("OFM", bmsg + "Flood Message");

  //object method call, with "method name" macro
  c5->c(__c5_MN__, bmsg + "Critical Message");
  c5->w(__c5_MN__, bmsg + "Warning Message");
  c5->i(__c5_MN__, bmsg + "Info Message");
  c5->d(__c5_MN__, bmsg + "Debug Message");
  c5->t(__c5_MN__, bmsg + "Trace Message");
  c5->f(__c5_MN__, bmsg + "Flood Message");
}

// === =======================================================================
//  This method uses c5 shortcut functions
void AppTestA::testFunctionCall() {
  //object method call, without metaInfo
  const QString bmsg = "obj dc ";

  c5c(c5, bmsg + "Critical Message");
  c5w(c5, bmsg + "Warning Message");
  c5i(c5, bmsg + "Info Message");
  c5d(c5, bmsg + "Debug Message");
  c5t(c5, bmsg + "Trace Message");
  c5f(c5, bmsg + "Flood Message");

  //object method call, with some additional message
  c5c(c5, "OCM", bmsg + "Critical Message");
  c5w(c5, "OWM", bmsg + "Warning Message");
  c5i(c5, "OIM", bmsg + "Info Message");
  c5d(c5, "ODM", bmsg + "Debug Message");
  c5t(c5, "OTM", bmsg + "Trace Message");
  c5f(c5, "OFM", bmsg + "Flood Message");

  //object method call, with "method name" macro
  c5c(c5, __c5_MN__, bmsg + "Critical Message");
  c5w(c5, __c5_MN__, bmsg + "Warning Message");
  c5i(c5, __c5_MN__, bmsg + "Info Message");
  c5d(c5, __c5_MN__, bmsg + "Debug Message");
  c5t(c5, __c5_MN__, bmsg + "Trace Message");
  c5f(c5, __c5_MN__, bmsg + "Flood Message");
}

// === =======================================================================
// === =======================================================================
