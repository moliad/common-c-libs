//------------------------------------------------
// file:    clibs_cast.h
// author:  (C) Maxim Olivier-Adlhoch
//
// date:    2020-02-20
// version: 1.0.1
//
// license: APACHE v2.0
//          https://www.apache.org/licenses/LICENSE-2.0
//
// purpose: datatype conversion
//------------------------------------------------


//--------------------------
//-     i64_to_charptr()
//--------------------------
int i64_to_charptr(long long int value, char *buffer, int len);

//--------------------------
//-     i32_to_charptr()
//--------------------------
int i32_to_charptr(int value, char *buffer, int len);

//--------------------------
//- double_to_charptr()
//--------------------------
int double_to_charptr(double value, int precision, char *buffer, int len );
