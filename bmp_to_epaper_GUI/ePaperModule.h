#ifndef __EPAPERMODULE_H__
#define __EPAPERMODULE_H__

#include "stdafx.h"
#include "CFA_FSO.h"

class module_t
{
private:
  std::string moduleMaster;
  int yBits;
  int rBits;
  int bwBits;
  int modWidth;
  int modLength;
  bool reverseColor;
  bool leftToRight;
  bool topToBot;

public:
  void initializeDisplay(int newrBits, int newyBits, int newbwBits, bool ltrInfo, bool ttbInfo, bool invInfo);
  int getRBits(void);
  int getYBits(void);
  int getBWBits(void);
  bool getLTR(void);
  bool getTTB(void);
  bool getInverted(void);
  FILE_SYSTEM_OBJECT sourceFile;
  FILE_SYSTEM_OBJECT destFile;
};


#endif // !EPAPERMODULE
