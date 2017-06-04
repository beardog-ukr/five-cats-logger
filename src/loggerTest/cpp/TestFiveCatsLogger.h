#include <QtTest/QtTest>

#include <QString>

class TestFiveCatsLogger: public QObject
{
  Q_OBJECT
private slots:
  void prepareNewFileName_NotExists();
  void prepareNewFileName_Basic1Exists();
  void prepareNewFileName_Basic3Exists();

  void levels_AllCascade();
  void levels_BasicCritical();
  void levels_BasicWarning() ;
  void levels_BasicInfo() ;
  void levels_BasicDebug();
  void levels_BasicTrace() ;
  void levels_BasicFlood() ;



protected:
  void createSomeFile(const QString fileName);
  void readAndRemoveFile(const QString& filename, QString& out);
};
