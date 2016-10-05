#include "AppTestA.h"
#include "FiveCatsLogger.h"

#include <QTimer>
//#include <QDebug>

// === =======================================================================

AppTestA::AppTestA(QObject* parent)
             :QObject(parent){
  timer = 0;
  delay = 5;
  counter = 0;
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
  parser.setApplicationDescription("Test \"A\" application. Writes a sencence to the log every tc seconds");
  parser.addHelpOption();
  parser.addVersionOption();

  // command line options
  QCommandLineOption actionOption("tc","Time between writes", "tc");
  parser.addOption(actionOption);

  c5->initCommandLineParser(parser);

  // Process the actual command line arguments given by the user
  QCoreApplication* ca = QCoreApplication::instance();
  parser.process(*ca);

  QString tmps = parser.value("tc");
  if (tmps.isEmpty()) {
    return false;
  }
  delay = tmps.toInt();

  c5->loadCommandLineParser(parser);

  return result;
}

// === =======================================================================

bool AppTestA::prepareToStart() {
  timer = new QTimer(this) ;
//  timer->setSingleShot(true);
  connect(timer, SIGNAL(timeout()),this, SLOT(action()) );
  timer->start(delay*1000);

  c5d(c5, __c5_MN__, QString("Started %1\n").arg(delay) ) ;
//  qDebug() <<"Started " << delay ;
  return true;
}

// === =======================================================================

void AppTestA::action() {
  c5d(c5, __c5_MN__, QString("Writing %1\n").arg(counter) ) ;
//  qDebug() <<"Action " << counter;
  counter++ ;

  if (counter>5) {
    QTimer* tm;
    tm->setSingleShot(true);// this causes segfault
  }

  if (counter>10) {
    QCoreApplication::exit(0);
  }
}

// === =======================================================================

int AppTestA::getAppExitCode() const {
  return appExitCode;
}

// === =======================================================================



// === =======================================================================
// === =======================================================================
