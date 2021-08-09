#include "string_helper.h"

uint StringLength(const char* ptr) {
	uint i = 0;
	while (ptr[i++] != '\0');
	return i - 1;
}

bool StringCompare(const char* s1, const char* s2) {
	if (StringLength(s1) != StringLength(s2))
		return false;
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] != s2[i])
			return false;
		i++;
	}
	return true;
}

bool StringCompare(String* s1, String* s2) {
	if (s1->length != s2->length)
		return false;
	int i = 0;
	while (s1->ptr[i] != '\0' && s2->ptr[i] != '\0') {
		if (s1->ptr[i] != s2->ptr[i])
			return false;
		i++;
	}
	return true;
}

String* IntToString(int i) {
	if (i == 0)
		return new String('0');
	String* str = new String(5);
	if (i < 0)
	{
		i *= -1;
		str->Append('-');
	}
	while (i > 0) {
		int digit = i % 10;
		str->Append(digit + '0');
		i /= 10;
	}
	return str;
}

int StringToInt(String* str) {
	int value = 0;
	int i = 0;
	while (i < str->length) {
		int digit = str->ptr[i++] - '0';
		value *= 10;
		value += digit;
	}
	return value;
}

double StringToFloat(String* str) {
	double value = 0;
	int dotIndex = str->IndexOf('.');
	dotIndex = dotIndex >= 0 ? dotIndex : str->length;

	for (size_t i = 0; i < dotIndex; i++)
	{
		int digit = str->ptr[i] - '0';
		for (size_t j = 0; j < dotIndex - i - 1; j++)
			digit *= 10;
		value += digit;
	}

	double decimal = 0;
	for (size_t i = dotIndex + 1; i < str->length; i++)
	{
		int digit = str->ptr[i] - '0';
		uint divide = 1;
		for (size_t j = 0; j < i - dotIndex; j++)
			divide *= 10;
		decimal += (digit / (double)divide);
	}
	return value + decimal;
}