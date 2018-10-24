#include "stdafx.h"

#ifndef __moduletype_h__
#define __moduletype_h__

class Module
{
private:
	std::string moduleMaster;
	int rBits = 0;
  int yBits = 0;
	int gBits = 0;
	int modWidth = 0;
	int modLength = 0;
	bool reverseColor = false;
	bool leftToRight = true;
  bool TopToBottom = true;

public:
	void setModuleType(std::string);
  void setModuleType(int g, int r, int y);
  void setWidth(int w);
  void setLength(int w);
  int getWidth(void);
	int getLength(void);
  int getRBits(void);
  int getYBits(void);
	int getGBits(void);
	bool getLTR(void);
  bool getTTB(void);
	bool getReverseColor(void);
};
#endif