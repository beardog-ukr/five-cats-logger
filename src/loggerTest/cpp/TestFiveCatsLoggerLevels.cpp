#include "TestFiveCatsLogger.h"
#include "FiveCatsLogger.h"

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

//#include <QDebug>

// ============================================================================
// ============================================================================
// ============================================================================

void TestFiveCatsLogger::levels_AllCascade() {
  QString fn = QCoreApplication::applicationDirPath() + "/" + "t_ac.txt";
  FiveCatsLogger* c5 = new FiveCatsLogger();
  c5->setFileName(fn);

  FiveCatsLogger::LogLevel ll[] =
    {FiveCatsLogger::Critical, FiveCatsLogger::Warning, FiveCatsLogger::Info,
     FiveCatsLogger::Debug, FiveCatsLogger::Trace, FiveCatsLogger::Flood };

  for (int i=0; i<6;i++) {
    c5->setLogLevel(ll[i]);
    c5->c("1");
    c5->w("2");
    c5->i("3");
    c5->d("4");
    c5->t("5");
    c5->f("6");
  }

  delete c5;

  QString cs("");
  readAndRemoveFile(fn, cs);

  const QString expected = "112123123412345123456";
  QCOMPARE(cs, expected );
}

// ============================================================================

void TestFiveCatsLogger::levels_BasicCritical() {
  QString fn = QCoreApplication::applicationDirPath() + "/" + "t_bc.txt";
  FiveCatsLogger* c5 = new FiveCatsLogger(FiveCatsLogger::Critical);
  c5->setFileName(fn);

  c5->c("1");
  c5->c("A", "2") ;
  c5->c([]{return QString("3");});
  c5->c("B", []{return QString("4");});

  c5c(c5, "5");
  c5c(c5, "C", "6") ;
  c5c(c5, []{return QString("7");});
  c5c(c5, "D", []{return QString("8");});

  delete c5;

  QString cs("");
  readAndRemoveFile(fn, cs);

  const QString expected = "1A >> 23B >> 45C >> 67D >> 8";
  QCOMPARE(cs, expected );
}

// ============================================================================

void TestFiveCatsLogger::levels_BasicWarning() {
  QString fn = QCoreApplication::applicationDirPath() + "/" + "t_bw.txt";
  FiveCatsLogger* c5 = new FiveCatsLogger(FiveCatsLogger::Warning);
  c5->setFileName(fn);

  c5->w("1");
  c5->w("A", "2") ;
  c5->w([]{return QString("3");});
  c5->w("B", []{return QString("4");});

  c5w(c5, "5");
  c5w(c5, "C", "6") ;
  c5w(c5, []{return QString("7");});
  c5w(c5, "D", []{return QString("8");});

  delete c5;

  QString cs("");
  readAndRemoveFile(fn, cs);

  const QString expected = "1A >> 23B >> 45C >> 67D >> 8";
  QCOMPARE(cs, expected );
}

// ============================================================================

void TestFiveCatsLogger::levels_BasicInfo() {
  QString fn = QCoreApplication::applicationDirPath() + "/" + "t_bi.txt";
  FiveCatsLogger* c5 = new FiveCatsLogger(FiveCatsLogger::Info);
  c5->setFileName(fn);

  c5->i("1");
  c5->i("A", "2") ;
  c5->i([]{return QString("3");});
  c5->i("B", []{return QString("4");});

  c5i(c5, "5");
  c5i(c5, "C", "6") ;
  c5i(c5, []{return QString("7");});
  c5i(c5, "D", []{return QString("8");});

  delete c5;

  QString cs("");
  readAndRemoveFile(fn, cs);

  const QString expected = "1A >> 23B >> 45C >> 67D >> 8";
  QCOMPARE(cs, expected );
}

// ============================================================================

void TestFiveCatsLogger::levels_BasicDebug() {
  QString fn = QCoreApplication::applicationDirPath() + "/" + "t_bd.txt";
  FiveCatsLogger* c5 = new FiveCatsLogger(FiveCatsLogger::Debug);
  c5->setFileName(fn);

  c5->d("1");
  c5->d("A", "2") ;
  c5->d([]{return QString("3");});
  c5->d("B", []{return QString("4");});

  c5d(c5, "5");
  c5d(c5, "C", "6") ;
  c5d(c5, []{return QString("7");});
  c5d(c5, "D", []{return QString("8");});

  delete c5;

  QString cs("");
  readAndRemoveFile(fn, cs);

  const QString expected = "1A >> 23B >> 45C >> 67D >> 8";
  QCOMPARE(cs, expected );
}

// ============================================================================

void TestFiveCatsLogger::levels_BasicTrace() {
  QString fn = QCoreApplication::applicationDirPath() + "/" + "t_bt.txt";
  FiveCatsLogger* c5 = new FiveCatsLogger(FiveCatsLogger::Trace);
  c5->setFileName(fn);

  c5->t("1");
  c5->t("A", "2") ;
  c5->t([]{return QString("3");});
  c5->t("B", []{return QString("4");});

  c5t(c5, "5");
  c5t(c5, "C", "6") ;
  c5t(c5, []{return QString("7");});
  c5t(c5, "D", []{return QString("8");});

  delete c5;

  QString cs("");
  readAndRemoveFile(fn, cs);

  const QString expected = "1A >> 23B >> 45C >> 67D >> 8";
  QCOMPARE(cs, expected );
}

// ============================================================================

void TestFiveCatsLogger::levels_BasicFlood() {
  QString fn = QCoreApplication::applicationDirPath() + "/" + "t_bf.txt";
  FiveCatsLogger* c5 = new FiveCatsLogger(FiveCatsLogger::Flood);
  c5->setFileName(fn);

  c5->f("1");
  c5->f("A", "2") ;
  c5->f([]{return QString("3");});
  c5->f("B", []{return QString("4");});

  c5f(c5, "5");
  c5f(c5, "C", "6") ;
  c5f(c5, []{return QString("7");});
  c5f(c5, "D", []{return QString("8");});

  delete c5;

  QString cs("");
  readAndRemoveFile(fn, cs);

  const QString es("1A >> 23B >> 45C >> 67D >> 8");
  QCOMPARE(cs, es );
}

// ============================================================================
// ============================================================================
// ============================================================================
