#pragma once

#ifdef LEAVER_EXPORTS
#define LEAVERLIBRARY_API __declspec(dllexport)
#else
#define LEAVERLIBRARY_API __declspec(dllimport)
#endif
#include <string>
namespace dunamo {
	class  Leaver {
	public:
		std::wstring LEAVERLIBRARY_API leave(std::wstring);
	};
}