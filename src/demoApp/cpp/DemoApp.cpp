#include "DemoApp.h"
#include "FiveCatsLogger.h"

// === =======================================================================
#include <typeinfo>

#include <QDebug>
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

  // === preform some other actions here

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

  QCoreApplication::exit(0);
}

// === =======================================================================

int DemoApp::getAppExitCode() const {
  return appExitCode;
}

// === =======================================================================
// === =======================================================================
