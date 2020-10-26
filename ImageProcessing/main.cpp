#include <iostream>
#include "ImageProcessing.h"

using namespace std;

int main() {
	int imgWidth, imgHeight, imgBitDepth;
	unsigned char imgHeader[BMP_HEADER_SIZE];
	unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
	unsigned char imgInBuffer[_512BY512];
	unsigned char imgOutBuffer[_512BY512];

	const char imgName[] = "images/girlface.bmp";
	const char newImgName[] = "images/girlface_copy.bmp";

	ImageProcessing* myImage = new ImageProcessing(imgName,
												   newImgName, 
												   &imgHeight, 
												   &imgWidth, 
												   &imgBitDepth, 
												   &imgHeader[0], 
												   &imgColorTable[0], 
												   &imgInBuffer[0], 
												   &imgOutBuffer[0]
												   );
	myImage->readImage();
	myImage->copyImgData(imgInBuffer, imgOutBuffer, _512BY512);
	myImage->writeImage();

	cout << "Success!" << endl;
	cout << "Image height :" << imgHeight << endl;
	cout << "Image width :" << imgWidth << endl;

	return 0;
}