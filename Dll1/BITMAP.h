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
    BSTR Filename,    //��� �����, �� �������� ������ ��������
    unsigned int NewColor,     //���� � ������� ������������� �����, � RGB
    int BorderSize    //������� �����
);
