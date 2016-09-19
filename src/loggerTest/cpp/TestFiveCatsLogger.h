#include <QtTest/QtTest>

#include <QString>

class TestFiveCatsLogger: public QObject
{
  Q_OBJECT
private slots:
  void prepareNewFileName_NotExists();
  void prepareNewFileName_Basic1Exists();
  void prepareNewFileName_Basic3Exists();



protected:
  void createSomeFile(const QString fileName);
};
