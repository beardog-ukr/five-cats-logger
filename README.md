# five-cats-logger
Logging library for Qt

## Features

*FiveCats* got following features:
* five levels of debug messages (or logging can be turned off at all)
* save log messages to file, or to stdout or both
* nicely add class and method name to the messages
* easily process command line options with *QCommandLineParser*

However there is also something NOT implemented here:
* singletone stuff, because singletones are evil
* multithreading. If you have few threads, you should use few *FiveCatsLogger* instances.


## Usage
You have manually create *FiveCats* instance and then use one of the logging functions:
```cpp
c5 = new FiveCatsLogger();
c5->setLogLevel(FiveCatsLogger::Debug);

c5c(c5, "Critical message");
c5w(c5, "Warning message");
c5i(c5, "Info message");
c5d(c5, "Debug message");
c5t(c5, "Trace message");
c5f(c5, "Flood message");
```  

In the above example we've set *Debug* logging level so it will not write *Trace* and *Flood* lines

Lambda functions can be used to create some complex output.
```cpp
std::vector<int> iarr = {12,23,34,45,56};
c5->t([&iarr]() {
  QString ss("Array elements: ");
  for (auto ii = iarr.cbegin(); ii!=iarr.cend(); ii++) {
    ss += QString("%1").arg(*ii) + " | ";
  }

  ss.chop(2);
  ss += ".";
  return ss;
});
```

Here we print some message at "trace" log level. Lambda will not be called if log level is not enough, so it will not affect perfomance.

### Method names
Also there is a __c5_MN__ macro; it expands to method name, so
```cpp
void SomeClass::SomeAction() {
  c5t(c5, __c5_MN__, "Trace msg");
}
```
will actually print
```
SomeClass::SomeAction() >> Trace msg
```

### Timestamp

Current c5 version can't add timestamps to log lines. However it can be done with lambdas:
```cpp
int someNumberToLog = 12345;
c5w(c5, [someNumberToLog]() {
  return QString("%1 :: some number is %2")
            .arg(QDateTime::currentDateTime().toString()).arg(someNumberToLog);
});
```


:construction: to be continued :construction:
