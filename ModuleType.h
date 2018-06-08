#include "stdafx.h"

#ifndef __moduletype_h__
#define __moduletype_h__

class Module
{
private:
	std::string moduleMaster;
	int rBits;
	int gBits;
	int modWidth;
	int modLength;
	bool reverseColor;
	bool leftToRight;

public:
	void setModuleType(std::string);
	int getWidth(void);
	int getLength(void);
	int getRBits(void);
	int getGBits(void);
	bool getLTR(void);
	bool getReverseColor(void);
};
#endif