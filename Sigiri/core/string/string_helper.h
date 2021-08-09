#pragma once

#include "../declarations.h"
#include "sigiri_string.h"

uint StringLength(const char* ptr);
bool StringCompare(const char* s1, const char* s2);
bool StringCompare(String* s1, String* s2);
int StringToInt(String* str);
double StringToFloat(String* str);
String* IntToString(int i);