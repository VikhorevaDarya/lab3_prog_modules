#include <comdef.h>
#include <Windows.h>

typedef tagBITMAP CustomImgType;  

typedef CustomImgType(__cdecl* MYPROC)(BSTR, unsigned int, int);

int main()
{
    HINSTANCE hinstLib;
    MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    hinstLib = LoadLibrary(TEXT("Dll1.dll")); //загрузка библиотеки

    int i = GetLastError();

    if (hinstLib != NULL)
    {
        ProcAdd = (MYPROC)GetProcAddress(hinstLib, "LoadBitmapFunc");
        tagBITMAP bitmap;
        if (NULL != ProcAdd)
        {
            fRunTimeLinkSuccess = TRUE;
            bitmap = (ProcAdd)(SysAllocString(L"img1.bmp"), 0x00FFFF, 3);
        }

        fFreeResult = FreeLibrary(hinstLib);
    }

    if (!fRunTimeLinkSuccess)
        printf("Message printed from executable\n");

    return 0;
}