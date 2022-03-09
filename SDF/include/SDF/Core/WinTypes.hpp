/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

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

typedef __int64 LONGLONG;

typedef unsigned int UINT;
typedef unsigned long DWORD;

typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;

typedef UINT_PTR SOCKET;
