#pragma once

#ifdef EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

#include <comdef.h>

typedef tagBITMAP CustomImgType;

extern "C" LIBRARY_API CustomImgType __stdcall LoadBitmapFunc
(
    BSTR Filename,    //имя файла, из которого грузим картинку
    unsigned int NewColor,     //цвет в который перекрашиваем рамку, в RGB
    int BorderSize    //толщина рамки
);
