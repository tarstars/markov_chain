#pragma once

#include <locale>
#include <codecvt>

typedef std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> ConverterType;
