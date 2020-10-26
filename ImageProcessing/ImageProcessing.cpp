// ImageProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "ImageProcessing.h"
using namespace std;

ImageProcessing::ImageProcessing(
	const char* _inImgName,
	const char* _outImgName,
	int* _height,
	int* _width,
	int* _bitDepth,
	unsigned char* _header,
	unsigned char* _colorTable,
	unsigned char* _inBuf,
	unsigned char* _outBuf
)
{
	inImgName = _inImgName;
	outImgName = _outImgName;
	height = _height;
	width = _width;
	bitDepth = _bitDepth;
	header = _header;
	colorTable = _colorTable;
	inBuf = _inBuf;
	outBuf = _outBuf;
}

void ImageProcessing::readImage() {
	int i;
	FILE *streamIn;
	errno_t err;
	err = fopen_s(&streamIn, inImgName, "rb");
	if (!err && streamIn != NULL) {
		std::cout << "Unable to open file. Maybe file does not exist" << std::endl;
		exit(0);
	} else {
		for (i = 0; i < BMP_HEADER_SIZE; i++) {
			header[i] = getc(streamIn);
		}
	}
	
	*width = *(int*)&header[10];
	*height = *(int*)&header[22];
	*bitDepth = *(int*)&header[28];

	if (*bitDepth <= 8) {
		fread(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
	}

	fread(inBuf, sizeof(unsigned char), _512BY512, streamIn);
	fclose(streamIn);
}

void ImageProcessing::writeImage() {
	FILE* fo;
	errno_t err;
	err = fopen_s(&fo, outImgName, "wb");

	if (!err && fo != NULL) {
		std::cout << "Unable to open file. Maybe file does not exist" << std::endl;
		exit(0);
	}

	fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, fo);
	if (*bitDepth <= 8) {
		fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, fo);
	}
	fwrite(outBuf, sizeof(unsigned char), _512BY512, fo);
	fclose(fo);
}

void ImageProcessing::copyImgData(unsigned char *_srcBuf, unsigned char *_destBuf, int bufSize) {
	for (int i = 0; i < bufSize; i++) {
		_destBuf[i] = _srcBuf[i];
	}
}
