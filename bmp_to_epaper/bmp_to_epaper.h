#ifndef __BMP_TO_EPAPER_H__
#define __BMP_TO_EPAPER_H__

#include <queue>

#include <stdio.h>
#include <string>
#include "targetver.h"
#include "windows.h"
#include "ModuleType.h"
#include "..\shared\CFA_FSO.h"

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
int processImage(bool rlEncoded, bool oneDimArray, Module moduleData, std::string stringPath);


#endif
