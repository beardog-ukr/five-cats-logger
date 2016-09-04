#include "FiveCatsLogger.h"

#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

#include <QDebug> // TODO: remove it

// === ========================================================================

FiveCatsLogger::FiveCatsLogger() {
  selfSetup();
}

// === ========================================================================

FiveCatsLogger::FiveCatsLogger(LogLevel inLogLevel) {
  selfSetup();
  logLevel = inLogLevel;
}

// === ========================================================================

FiveCatsLogger::~FiveCatsLogger() {
  if (file) {
    file->flush();
    file->close();
  }
  delete file;

  delete echo;
}

// === ========================================================================

void FiveCatsLogger::selfSetup() {
  file =0;
  flushCounter =0;
  errorMessage = "";
  echo = 0;

  setLogLevel(FiveCatsLogger::Critical);
  setUseStdOut(true);
}

// === ========================================================================

QString FiveCatsLogger::getErrorMessage() const {
  return errorMessage ;
}

// === ========================================================================

void FiveCatsLogger::setLogLevel(LogLevel inLogLevel) {
  logLevel = inLogLevel;//
}

// === ========================================================================

bool FiveCatsLogger::setFileName(const QString& inFileName, bool append) {
  if (file) {
    file->close();
    delete file;
    flushCounter =0;
  }

  QString fileName = prepareFileName(inFileName);

  file = new QFile(fileName);

  if ( file->exists() && (append==false)) {
    int fnc = 1000;
    QString tmpfns;

    do {
      tmpfns = fileName + "." + QString::number(fnc);
      file->setFileName(tmpfns);
      fnc++;
    } while ( file->exists() && (fnc<10000) ) ;

    if (fnc>=10000) {
      errorMessage = QString( "File (%1) exists").arg(inFileName);
      return false;
    }
  }

  bool tboo;
  if (append) {
    tboo = file->open(QIODevice::Append | QIODevice::Text);
  }
  else {
    tboo = file->open(QIODevice::WriteOnly | QIODevice::Text);
  }

  if (!tboo) {
    errorMessage = "Failed to open " + fileName;
    delete file;
    file =0;
    return false;
  }

  // finally
  return true;
}

// === ========================================================================

QString FiveCatsLogger::prepareFileName(const QString& fn) const {
  QString result = fn;
  const QString keyAppPath = "__APP_PATH" ;
  if (fn.startsWith(keyAppPath)) {
    result.replace(keyAppPath, QCoreApplication::applicationDirPath());
  }
  return result;
}

// === ========================================================================

void FiveCatsLogger::write(LogLevel messageLevel, const QString str) {
//  qDebug() << "FiveCatsLogger::write >> " << logLevel << messageLevel << str;
  if (messageLevel>logLevel) {
    return;
  }

  const QByteArray tba = str.toUtf8() ;

  if (echo) {
    echo->write( tba ) ;
    echo->write( QString("\n").toUtf8() ) ;
    echo->flush();
  }

  if (file) {
    file->write( tba ) ;
    file->write( QString("\n").toUtf8() ) ;
//    file->flush();

//    QTextStream out(file);
//    out << str << "\n";
  }

  flushCounter++;
  if (flushCounter>flushFrequency) {
    flushCounter =0;
    if (file) {
      file->flush();
    }
  }
}

// === ========================================================================

QString FiveCatsLogger::composeLine(const QString& metaInfo, const QString& message) const {
  QString tmps = metaInfo + " >> " + message ;
  return tmps;
}

// === ========================================================================

void FiveCatsLogger::setUseStdOut(bool use) {
  if (use) {
    if (echo != 0) {
      return;
    }

    echo = new QFile();
    bool tboo = echo->open(stdout, QIODevice::WriteOnly);
    if (!tboo) {
      errorMessage = "Failed to use stdout";
      delete echo;
      echo = 0;
    }
  }
  else {
    if (echo == 0) {
      return;
    }

    delete echo;
    echo = 0;
  }
}

// === ========================================================================

void FiveCatsLogger::initCommandLineParser(QCommandLineParser& parser) {
  QCommandLineOption llOption("c5ll");
  llOption.setDescription("Application log level (Critical, Warning, Info, Debug, Trace, Flood)");
  llOption.setValueName("c5ll");
  parser.addOption(llOption);

  QCommandLineOption fnOption("c5fn");
  fnOption.setDescription("Filename to save output)");
  fnOption.setValueName("c5fn");
  parser.addOption(fnOption);
}

// === ========================================================================

void FiveCatsLogger::loadCommandLineParser(const QCommandLineParser& parser) {
  QString tmps ;
  tmps = parser.value("c5ll");
  if ( tmps=="Critical" ) {
    setLogLevel(Critical);
  }
  else if ( tmps=="Warning" ) {
    setLogLevel(Warning);
  }
  else if ( tmps=="Info" ) {
    setLogLevel(Info);
  }
  else if ( tmps=="Debug" ) {
    setLogLevel(Debug);
  }
  else if ( tmps=="Trace" ) {
    setLogLevel(Trace);
  }
  else if ( tmps=="Flood" ) {
    setLogLevel(Flood);
  } ;

  tmps = parser.value("c5fn");
  if ( !tmps.isEmpty() ) {
    setFileName(tmps) ;
  }
}

// === ========================================================================

bool FiveCatsLogger::usesStdOut() const {
  return (echo != 0) ;
}

// === ========================================================================

void FiveCatsLogger::c(const QString& message) {
  write(Critical, message);
}

// === ========================================================================

void FiveCatsLogger::c(const QString& metaInfo, const QString& message) {
  write(Critical, composeLine(metaInfo, message) );
}

// === ========================================================================

void FiveCatsLogger::w(const QString& message) {
  write(Warning, message);
}

// === ========================================================================

void FiveCatsLogger::w(const QString& metaInfo, const QString& message) {
  write(Warning, composeLine(metaInfo, message) );
}

// === ========================================================================

void FiveCatsLogger::i(const QString& message) {
  write(Info, message);
}

// === ========================================================================

void FiveCatsLogger::i(const QString& metaInfo, const QString& message) {
  write(Info, composeLine(metaInfo, message) );
}

// === ========================================================================

void FiveCatsLogger::d(const QString& message) {
  write(Debug, message);
}

// === ========================================================================

void FiveCatsLogger::d(const QString& metaInfo, const QString& message) {
  write(Debug, composeLine(metaInfo, message) );
}

// === ========================================================================

void FiveCatsLogger::t(const QString& metaInfo, const QString& message) {
  write(Trace, composeLine(metaInfo, message) );
}

// === ========================================================================

void FiveCatsLogger::t(const QString& message) {
  write(Trace, message);
}

// === ========================================================================

void FiveCatsLogger::f(const QString& metaInfo, const QString& message) {
  write(Flood, composeLine(metaInfo, message) );
}

// === ========================================================================

void FiveCatsLogger::f(const QString& message) {
  write(Flood, message);
}

// === ========================================================================

void c5c(FiveCatsLogger* logger, const QString message) {
  if (logger==0) {
    return;
  }

  logger->c(message);
}

// === ========================================================================

void c5c(FiveCatsLogger* logger, const QString metaInfo, const QString message)  {
  if (logger==0) {
    return;
  }

  logger->c(metaInfo, message);
}

// === ========================================================================

void c5w(FiveCatsLogger* logger, const QString message) {
  if (logger==0) {
    return;
  }

  logger->w(message);
}

// === ========================================================================

void c5w(FiveCatsLogger* logger, const QString metaInfo, const QString message)  {
  if (logger==0) {
    return;
  }

  logger->w(metaInfo, message);
}

// === ========================================================================

void c5i(FiveCatsLogger* logger, const QString message) {
  if (logger==0) {
    return;
  }

  logger->i(message);
}

// === ========================================================================

void c5i(FiveCatsLogger* logger, const QString metaInfo, const QString message)  {
  if (logger==0) {
    return;
  }

  logger->i(metaInfo, message);
}

// === ========================================================================

void c5d(FiveCatsLogger* logger, const QString message) {
  if (logger==0) {
    return;
  }

  logger->d(message);
}

// === ========================================================================

void c5d(FiveCatsLogger* logger, const QString metaInfo, const QString message)  {
  if (logger==0) {
    return;
  }

  logger->d(metaInfo, message);
}

// === ========================================================================

void c5t(FiveCatsLogger* logger, const QString message) {
  if (logger==0) {
    return;
  }

  logger->t(message);
}

// === ========================================================================

void c5t(FiveCatsLogger* logger, const QString metaInfo, const QString message)  {
  if (logger==0) {
    return;
  }

  logger->t(metaInfo, message);
}

// === ========================================================================

void c5f(FiveCatsLogger* logger, const QString message) {
  if (logger==0) {
    return;
  }

  logger->f(message);
}

// === ========================================================================

void c5f(FiveCatsLogger* logger, const QString metaInfo, const QString message)  {
  if (logger==0) {
    return;
  }

  logger->f(metaInfo, message);
}

// === ========================================================================




















