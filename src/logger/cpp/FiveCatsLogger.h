//This is free and unencumbered software released into the public domain.

//Anyone is free to copy, modify, publish, use, compile, sell, or
//distribute this software, either in source code form or as a compiled
//binary, for any purpose, commercial or non-commercial, and by any
//means.

//In jurisdictions that recognize copyright laws, the author or authors
//of this software dedicate any and all copyright interest in the
//software to the public domain. We make this dedication for the benefit
//of the public at large and to the detriment of our heirs and
//successors. We intend this dedication to be an overt act of
//relinquishment in perpetuity of all present and future rights to this
//software under copyright law.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.

//For more information, please refer to <http://unlicense.org>

// === ========================================================================

#ifndef __FiveCatsLogger__
#define __FiveCatsLogger__

#include <string>
#include <functional>

class QFile;
#include <QString>
#include <QCommandLineParser>

// === ========================================================================

class FiveCatsLogger {
  friend class TestFiveCatsLogger;
public:
  enum LogLevel {
    Critical = 0,
    Warning ,
    Info,
    Debug,
    Trace,
    Flood
  };

  FiveCatsLogger();
  FiveCatsLogger(LogLevel logLevel);
  virtual ~FiveCatsLogger();

  bool setFileName(const QString& fileName, bool append = false) ;

  void setUseStdOut(bool use);
  bool usesStdOut() const;

  bool setKeepFileExtension(const bool keep);

  QString getErrorMessage() const ;

  void setLogLevel(LogLevel logLevel) ;

  static void initCommandLineParser(QCommandLineParser& parser);
  void loadCommandLineParser(const QCommandLineParser& parser);

  void c(const QString& message);
  void w(const QString& message);
  void i(const QString& message);
  void d(const QString& message);
  void t(const QString& message);
  void f(const QString& message);

  void c(const QString& metaInfo, const QString& message) ;
  void w(const QString& metaInfo, const QString& message) ;
  void i(const QString& metaInfo, const QString& message) ;
  void d(const QString& metaInfo, const QString& message) ;
  void t(const QString& metaInfo, const QString& message) ;
  void f(const QString& metaInfo, const QString& message) ;

#if defined( __cpp_lambdas )  
  void c(std::function<QString()> makeMessage);
  void w(std::function<QString()> makeMessage);
  void i(std::function<QString()> makeMessage);
  void d(std::function<QString()> makeMessage);
  void t(std::function<QString()> makeMessage);
  void f(std::function<QString()> makeMessage);

  void c(const QString& metaInfo, std::function<QString()> makeMessage);
  void w(const QString& metaInfo, std::function<QString()> makeMessage);
  void i(const QString& metaInfo, std::function<QString()> makeMessage);
  void d(const QString& metaInfo, std::function<QString()> makeMessage);
  void t(const QString& metaInfo, std::function<QString()> makeMessage);
  void f(const QString& metaInfo, std::function<QString()> makeMessage);
#endif

protected:
  void selfSetup();

  LogLevel logLevel;

  void write(LogLevel messageLevel, const QString str);
#if defined( __cpp_lambdas ) 
  void writeL(LogLevel messageLevel, std::function<QString()> makeMessage);
  void writeL(LogLevel messageLevel, const QString& metaInfo, std::function<QString()> makeMessage);
#endif
  void writeFile(const QString& metaInfo, const QString& message);

  QFile* file;
  int flushCounter;
  //const int flushFrequency = 20;
  int flushFrequency ;
  QString prepareFileName(const QString& fn) const;
  QString prepareNewFileName(const QString& fn) const;

  QFile* echo;

  QString errorMessage;

  bool useStdout;
  QString composeLine(const QString& metaInfo, const QString& message) const;

  bool keepFileExtension;
};

// === ========================================================================

void c5c(FiveCatsLogger* logger, const QString message) ;
void c5w(FiveCatsLogger* logger, const QString message) ;
void c5i(FiveCatsLogger* logger, const QString message) ;
void c5d(FiveCatsLogger* logger, const QString message) ;
void c5t(FiveCatsLogger* logger, const QString message) ;
void c5f(FiveCatsLogger* logger, const QString message) ;

void c5c(FiveCatsLogger* logger, const QString metaInfo, const QString message) ;
void c5w(FiveCatsLogger* logger, const QString metaInfo, const QString message) ;
void c5i(FiveCatsLogger* logger, const QString metaInfo, const QString message) ;
void c5d(FiveCatsLogger* logger, const QString metaInfo, const QString message) ;
void c5t(FiveCatsLogger* logger, const QString metaInfo, const QString message) ;
void c5f(FiveCatsLogger* logger, const QString metaInfo, const QString message) ;

#if defined( __cpp_lambdas ) 
void c5c(FiveCatsLogger* logger, std::function<QString()> makeMessage) ;
void c5w(FiveCatsLogger* logger, std::function<QString()> makeMessage) ;
void c5i(FiveCatsLogger* logger, std::function<QString()> makeMessage) ;
void c5d(FiveCatsLogger* logger, std::function<QString()> makeMessage) ;
void c5t(FiveCatsLogger* logger, std::function<QString()> makeMessage) ;
void c5f(FiveCatsLogger* logger, std::function<QString()> makeMessage) ;

void c5c(FiveCatsLogger* logger, const QString metaInfo, std::function<QString()> makeMessage) ;
void c5w(FiveCatsLogger* logger, const QString metaInfo, std::function<QString()> makeMessage) ;
void c5i(FiveCatsLogger* logger, const QString metaInfo, std::function<QString()> makeMessage) ;
void c5d(FiveCatsLogger* logger, const QString metaInfo, std::function<QString()> makeMessage) ;
void c5t(FiveCatsLogger* logger, const QString metaInfo, std::function<QString()> makeMessage) ;
void c5f(FiveCatsLogger* logger, const QString metaInfo, std::function<QString()> makeMessage) ;
#endif

// === ========================================================================
// this came from http://stackoverflow.com/questions/1666802/is-there-a-class-macro-in-c
inline QString c5_methodName(const std::string& prettyFunction) {
    size_t colons = prettyFunction.find("::");
    size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    size_t end = prettyFunction.rfind("(") - begin;

    std::string ss = prettyFunction.substr(begin,end) + "()";
    return QString::fromStdString(ss);
}

#define __c5_MN__ c5_methodName(__PRETTY_FUNCTION__)

// === ========================================================================

#endif
