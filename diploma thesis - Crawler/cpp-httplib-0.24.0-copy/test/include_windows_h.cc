// Test if including windows.h conflicts with httplib_S.h

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <httplib_S.h>
