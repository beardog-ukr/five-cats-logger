#include "DemoApp.h"
#include "FiveCatsLogger.h"

// === =======================================================================
#include <typeinfo>
#include <vector>

#include <QDebug>
#include <QDateTime>
#include <QCommandLineParser>
#include <QTimer>
// === =======================================================================
// === =======================================================================
// === =======================================================================

DemoApp::DemoApp(QObject* parent)
         :QObject(parent){
  appExitCode=0;//
  startupTimer = 0;
  c5 = new FiveCatsLogger();
  c5->setLogLevel(FiveCatsLogger::Debug);
}

// === =======================================================================

DemoApp::~DemoApp() {
  delete startupTimer;
  delete c5;
}

// === =======================================================================

bool DemoApp::processCommandLine(const QStringList &arguments) {
  QCommandLineParser parser;
  parser.setApplicationDescription("This is demo app to show FiveCats logger features");
  parser.addHelpOption();
  parser.addVersionOption();

  // command line options
  QCommandLineOption lineOption("line");
  lineOption.setDescription("String value to print (like for echo))");
  lineOption.setValueName("line");
  parser.addOption(lineOption);

  // note how FiveCats can work with QCommandLineParser (and one line below)
  c5->initCommandLineParser(parser);

  // Process the actual command line arguments given by the user
  if (!parser.parse(arguments)) {
    qCritical(qPrintable(parser.errorText())) ;
    appExitCode=1;
    return false;
  }

  c5->loadCommandLineParser(parser);

  lineToPrint = parser.value(lineOption);

  // === finally
  return true;
}

// === =======================================================================

bool DemoApp::prepare() {
  // === prepare statrup timer
  startupTimer = new QTimer(this) ;
  startupTimer->setSingleShot(true);
  connect(startupTimer, SIGNAL(timeout()),this, SLOT(launch()) );
  startupTimer->start(100);

  // See how we can use functions here
  c5c(c5, __c5_MN__, "Here C");
  c5w(c5, __c5_MN__, "Here W");
  c5i(c5, __c5_MN__, "Here I");
  c5d(c5, __c5_MN__, "Here D");
  c5t(c5, __c5_MN__, "Here T");
  c5f(c5, __c5_MN__, "Here F");

  // === finally
  return true;
}

// === =======================================================================

void DemoApp::launch() {
  delete startupTimer;
  startupTimer =0;

  // Also we can use c5 metrods directly
  c5->c("Launch message Critical");
  c5->w("Launch message Warning");
  c5->i("Launch message Info");
  c5->d("Launch message Debug");
  c5->t("Launch message Trace");
  c5->f("Launch message Flood");

  // Some lambdas can be used
  std::vector<int> iarr = {12,23,34,45,56};
  c5->c([&iarr]() {
    QString ss("Array elements: ");
    for (auto ii = iarr.cbegin(); ii!=iarr.cend(); ii++) {
      ss += QString("%1").arg(*ii) + " | ";
    }

    ss.chop(2);
    ss += ".";
    return ss;
  });

  // Also lambdas can be used to add timestamp to message
  int someNumberToLog = 12345;
  c5w(c5, [someNumberToLog]() {
    return QString("%1 :: some number is %2")
              .arg(QDateTime::currentDateTime().toString()).arg(someNumberToLog);
  });

  QCoreApplication::exit(0);
}

// === =======================================================================

int DemoApp::getAppExitCode() const {
  return appExitCode;
}

// === =======================================================================
// === =======================================================================
