#ifndef __BMP_TO_EPAPER_H__
#define __BMP_TO_EPAPER_H__

#include <queue>
#include "stdafx.h"
#include "windows.h"
#include "ePaperModule.h"

class rlePair_t
{
public:
  unsigned char count;
  unsigned char val;
};

class rows_t
{
public:
  std::deque <rlePair_t>	rlePairs;
};

std::string getOutputFile(const char *path);
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
int processImage(bool rlEncoded, bool oneDimArray, module_t moduleData, std::string stringPath);


#endif
