
#include "BITMAP.h"

CustomImgType __stdcall LoadBitmapFunc
(
    BSTR Filename,    //им€ файла, из которого грузим картинку
    unsigned int NewColor,     //цвет в который перекрашиваем рамку, в RGB
    int BorderSize    //толщина рамки
)
{
	NewColor = (NewColor << 8) >> 8;

	char color[3];
	color[0] = (NewColor >> 16);		// red
	color[1] = (NewColor << 16) >> 24;	// green
	color[2] = (NewColor << 24) >> 24;	// blue

	tagBITMAPFILEHEADER fileHeader;
	tagBITMAPINFOHEADER infoHeader;

	CustomImgType bmp;

	HANDLE fh;

	fh = CreateFileW(Filename,
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(fh, (void*)&fileHeader, sizeof(fileHeader), 0, 0);

	ReadFile(fh, (void*)&infoHeader, sizeof(infoHeader), 0, 0);

	char* body = new char[infoHeader.biSizeImage];
	unsigned long body_size = infoHeader.biSizeImage;

	LONG width = infoHeader.biWidth;
	LONG height = infoHeader.biHeight;

	int padding = width % 4;

	ReadFile(fh, (void*)body, body_size, 0, 0);

	CloseHandle(fh);

	for (int i{}; i < width; i++) // ¬ерхн€€ и нижн€€ граница
	{
		for (int j{}; j < BorderSize && j < height; j++)
		{

			body[i * 3 + j * width * 3 + j * padding] = color[2];
			body[i * 3 + j * width * 3 + j * padding + 1] = color[1];
			body[i * 3 + j * width * 3 + j * padding + 2] = color[0];

			body[i * 3 + (height - 1 - j) * width * 3 + (height - 1 - j) * padding] = color[2];
			body[i * 3 + (height - 1 - j) * width * 3 + (height - 1 - j) * padding + 1] = color[1];
			body[i * 3 + (height - 1 - j) * width * 3 + (height - 1 - j) * padding + 2] = color[0];

		}

	}

	for (int i{}; i < height; i++) // Ћева€ и права€ граница
	{
		for (int j{}; j < BorderSize && j < width; j++)
		{

			body[j * 3 + i * width * 3 + i * padding] = color[2];
			body[j * 3 + i * width * 3 + i * padding + 1] = color[1];
			body[j * 3 + i * width * 3 + i * padding + 2] = color[0];

			body[(width - j - 1) * 3 + i * width * 3 + i * padding] = color[2];
			body[(width - j - 1) * 3 + i * width * 3 + i * padding + 1] = color[1];
			body[(width - j - 1) * 3 + i * width * 3 + i * padding + 2] = color[0];
		}

	}


	HANDLE fhout = CreateFileW(L"output.bmp",
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	WriteFile(fhout, (void*)&fileHeader, sizeof(fileHeader), 0, 0);

	int g = GetLastError();

	WriteFile(fhout, (void*)&infoHeader, sizeof(infoHeader), 0, 0);

	g = GetLastError();

	WriteFile(fhout, (void*)body, body_size, 0, 0);

	g = GetLastError();

	CloseHandle(fhout);

	//delete[] body;

	bmp.bmType = fileHeader.bfType;
	bmp.bmWidth = width;
	bmp.bmHeight = height;
	bmp.bmBitsPixel = 24;
	bmp.bmWidthBytes = ((bmp.bmWidth * bmp.bmBitsPixel + 31) / 32) * 4;
	bmp.bmPlanes = infoHeader.biPlanes;
	bmp.bmBits = (void*)body;

	return bmp;
}