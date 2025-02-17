#pragma once

// Macros
#ifndef BEENGINE_VERSION_MAJOR
#define BEENGINE_VERSION_MAJOR 1
#define BEENGINE_VERSION_MINOR 0
#define BEENGINE_VERSION_PATCH 0
#define BEENGINE_VERSION_BUILD 1
#endif

// DLL Exports
#ifdef _WIN32
#ifdef BUILD_DLL
#define BEENGINE_API __declspec(dllexport)
#else
#define BEENGINE_API __declspec(dllimport)
#endif
#elif
#define BEENGINE_API
#endif