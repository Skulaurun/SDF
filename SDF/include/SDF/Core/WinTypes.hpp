#pragma once

typedef struct HWND__* HWND;
typedef struct HDC__* HDC;
typedef struct HGLRC__* HGLRC;

#if not defined(_WIN64)
    typedef long LONG_PTR;
    typedef unsigned int UINT_PTR;
#else
    typedef __int64 LONG_PTR;
    typedef unsigned __int64 UINT_PTR;
#endif

#if not defined(_M_IX86)
    typedef __int64 LONGLONG;
#else
    typedef double LONGLONG;
#endif

typedef unsigned int UINT;
typedef unsigned long DWORD;

typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;

typedef UINT_PTR SOCKET;
