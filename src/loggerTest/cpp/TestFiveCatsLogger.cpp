#include "TestFiveCatsLogger.h"
#include "FiveCatsLogger.h"

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

// ============================================================================
// ============================================================================
// ============================================================================

void TestFiveCatsLogger::prepareNewFileName_NotExists() {
  FiveCatsLogger c5;

  QString fn = QCoreApplication::applicationDirPath() + "/" + "t1.txt";
  QFileInfo finfo(fn);
  QCOMPARE(finfo.exists(), false); // just to be sure it doesn't exist

  QString tfn = c5.prepareNewFileName(fn);
  QCOMPARE(tfn, fn);
}

// ============================================================================

void TestFiveCatsLogger::prepareNewFileName_Basic1Exists() {
  QString f1name=  QCoreApplication::applicationDirPath() + "/" + "t2.txt";
  createSomeFile(f1name);

  FiveCatsLogger c5;
  c5.setKeepFileExtension(true);

  QString tfn = c5.prepareNewFileName(f1name);
  QString expectedfn = QCoreApplication::applicationDirPath() + "/" + "t2.000.txt";
  QCOMPARE(tfn, expectedfn);

  QFile::remove(f1name);
}

// ============================================================================

void TestFiveCatsLogger::prepareNewFileName_Basic3Exists() {
  QString f1name=  QCoreApplication::applicationDirPath() + "/" + "t3.txt";
  createSomeFile(f1name);
  QString f2name=  QCoreApplication::applicationDirPath() + "/" + "t3.000.txt";
  createSomeFile(f2name);
  QString f3name=  QCoreApplication::applicationDirPath() + "/" + "t3.001.txt";
  createSomeFile(f3name);

  FiveCatsLogger c5;
  c5.setKeepFileExtension(true);

  QString tfn = c5.prepareNewFileName(f1name);
  QString expectedfn = QCoreApplication::applicationDirPath() + "/" + "t3.002.txt";
  QCOMPARE(tfn, expectedfn);

  QFile::remove(f1name);
  QFile::remove(f2name);
  QFile::remove(f3name);
}

// ============================================================================
// ============================================================================

void TestFiveCatsLogger::createSomeFile(const QString fileName) {
  QFile fl(fileName);
  bool tboo = fl.open(QIODevice::WriteOnly | QIODevice::Text);
  QCOMPARE(tboo, true);
  fl.write( QString("Dummy text\nMore text\n").toUtf8() ) ;
  fl.flush();
  fl.close();
}

// ============================================================================

void TestFiveCatsLogger::readAndRemoveFile(const QString& filename, QString& outStr) {
  QFile fl(filename);
  if (! fl.open(QFile::ReadOnly )) {
    QFAIL("Absolutely unexpected error");
  }
  QTextStream stream(&fl);

  outStr = "";
  QString line;
  while (stream.readLineInto(&line)) {
    outStr += line;
  }
  fl.close();

  QFile::remove(filename);
}

// ============================================================================
// ============================================================================
