// #pragma once
// #include <string>
// #include <locale>
// // #include <atlconv.h>
// // #include <atlbase.h> 
// // #include <atlstr.h> 
//
//
// //https://stackoverflow.com/questions/246806/i-want-to-convert-stdstring-into-a-const-wchar-t
// /*
// wchar_t* std_string2wchar_t(std::string str)
// {
// 	// std::wstring wide_str(L"");
// 	std::wstring wide_str = std::wstring(str.begin(), str.end());
// 	wchar_t* wide_c_str = wide_str.c_str();
// 	return wide_c_str;
// }
// */
//
// /*
// wchar_t* std_string2wchar_t(std::string str)
// {
// 	ATL::CA2W pszWide(str.c_str());
// 	// ATL::CA2W pszWide(str.c_str(), CP_UTF8);
// 	return pszWide;
// }
// */
//
//
// wchar_t* std_string2wchar_t(std::string str)
// {
// 	// std::wstring wide_str(L"");
// 	// std::wstring wide_str = std::wstring(str.begin(), str.end());
// 	// wchar_t* wide_c_str = wide_str.c_str();
//
// 	// std::wstring_convert< std::codecvt<wchar_t, char, std::mbstate_t> > conv;
// 	// std::wstring wstr = conv.from_bytes(str) ;
// 	// wchar_t* wide_c_str = wstr;
//
// 	const size_t len = str.length() + 1;
// 	wchar_t* wcstring = new wchar_t[len];
// 	
// 	swprintf(wcstring, len, L"%s", str.c_str());
//
// 	// wchar_t x = new wchar_t[wstr.size()];
//
// 	return wcstring;
// }
