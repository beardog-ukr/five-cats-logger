#include "Functions.h"
#include "FiveCatsLogger.h"

// === =======================================================================
//  This function invokes methods from c5 object
void directCall(FiveCatsLogger* c5) {
  //object method call, without metaInfo
  const QString basicMsg = "f dc ";

  c5->c(basicMsg + "Critical Message");
  c5->w(basicMsg + "Warning Message");
  c5->i(basicMsg + "Info Message");
  c5->d(basicMsg + "Debug Message");
  c5->t(basicMsg + "Trace Message");
  c5->f(basicMsg + "Flood Message");
  //
  // //object method call, with some additional message
  c5->c("ACM", basicMsg + "Critical Message");
  c5->w("AWM", basicMsg + "Warning Message");
  c5->i("AIM", basicMsg + "Info Message");
  c5->d("ADM", basicMsg + "Debug Message");
  c5->t("ATM", basicMsg + "Trace Message");
  c5->f("AFM", basicMsg + "Flood Message");

  // //object method call, with "method name" macro
  c5->c(__c5_MN__, basicMsg + "Critical Message");
  c5->w(__c5_MN__, basicMsg + "Warning Message");
  c5->i(__c5_MN__, basicMsg + "Info Message");
  c5->d(__c5_MN__, basicMsg + "Debug Message");
  c5->t(__c5_MN__, basicMsg + "Trace Message");
  c5->f(__c5_MN__, basicMsg + "Flood Message");
}

// === =======================================================================
//  This function uses various c5 functions
void functionCall(FiveCatsLogger* c5) {
  const QString basicMsg = "f fc ";

  //object method call, without metaInfo
  c5c(c5, basicMsg + "Critical Message");
  c5w(c5, basicMsg + "Warning Message");
  c5i(c5, basicMsg + "Info Message");
  c5d(c5, "FC Debug Message");
  c5t(c5, "FC Trace Message");
  c5f(c5, "FC Flood Message");

  //object method call, with some additional message
  c5c(c5, "ACM", "FC Critical Message");
  c5w(c5, "AWM", "FC Warning Message");
  c5i(c5, "AIM", "FC Info Message");
  c5d(c5, "ADM", "FC Debug Message");
  c5t(c5, "ATM", "FC Trace Message");
  c5f(c5, "AFM", "FC Flood Message");

  //object method call, with "method name" macro
  c5c(c5, __c5_MN__, "FC Critical Message");
  c5w(c5, __c5_MN__, "FC Warning Message");
  c5i(c5, __c5_MN__, "FC Info Message");
  c5d(c5, __c5_MN__, "FC Debug Message");
  c5t(c5, __c5_MN__, "FC Trace Message");
  c5f(c5, __c5_MN__, "FC Flood Message");
}

// === =======================================================================
//   This function calls c5 functions with zero pointer; it must be correctly
// processed and print nothing
void zeroCall() {
  FiveCatsLogger* zc5 = 0 ;

  c5c(zc5, "ZC Critical Message");
  c5w(zc5, "zC Warning Message");
  c5i(zc5, "zC Info Message");
  c5d(zc5, "zC Debug Message");
  c5t(zc5, "zC Trace Message");
  c5f(zc5, "zC Flood Message");

  c5c(zc5, __c5_MN__, "zC Critical Message");
  c5w(zc5, __c5_MN__, "zC Warning Message");
  c5i(zc5, __c5_MN__, "zC Info Message");
  c5d(zc5, __c5_MN__, "zC Debug Message");
  c5t(zc5, __c5_MN__, "zC Trace Message");
  c5f(zc5, __c5_MN__, "zC Flood Message");

  c5c(zc5, [](){ return QString("ZC Critical "); });
  c5w(zc5, [](){ return QString("zC Warning "); });
  c5i(zc5, [](){ return QString("zC Info "); });
  c5d(zc5, [](){ return QString("zC Debug "); });
  c5t(zc5, [](){ return QString("zC Trace "); });
  c5f(zc5, [](){ return QString("zC Flood "); });

  c5c(zc5, __c5_MN__, [](){ return QString("zC Critical "); });
  c5w(zc5, __c5_MN__, [](){ return QString("zC Warning "); });
  c5i(zc5, __c5_MN__, [](){ return QString("zC Info "); });
  c5d(zc5, __c5_MN__, [](){ return QString("zC Debug "); });
  c5t(zc5, __c5_MN__, [](){ return QString("zC Trace "); });
  c5f(zc5, __c5_MN__, [](){ return QString("zC Flood "); });

}

// === =======================================================================
// === =======================================================================

void performTestWithFunctions(FiveCatsLogger* c5) {
  //object method call, without metaInfo
  zeroCall();
  directCall(c5);
  functionCall(c5);
}

//=============================================================================
