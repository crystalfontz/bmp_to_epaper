//============================================================================
// 
//
// 
// 
//============================================================================
#include "stdafx.h"
#include "ModuleType.h"
#define moduleCount 8
//This array classifies the existing ePaper modules
std::string moduleType[moduleCount] =
{
	"CFAP128296C00290",
	"CFAP128296D00290",
	"CFAP122250A00213",
	"CFAP200200A00154",
	"CFAP128296A00290",
	"CFAP152152A00154",
	"CFAP104212C00213",
	"CFAP176264A00270"
};

//This array associates the number of red bits
const int moduleRedBits[moduleCount] = { 0,1,0,0,0,1,1,1 };

//This array associates the number of grey bits
const int moduleGreyBits[moduleCount] = { 1,1,1,1,2,1,1,1 };

//this array sets the horizontal pixel length
const int screenWidth[moduleCount] = { 128,128,122,200,128,152,104,176 };

//this array sets the vertical pixel length
const int screenLength[moduleCount] = { 296,296,250,200,296,152,212,264 };

//this array sets if the colors are reverse - true for if reversed
bool reversedColor[moduleCount] = { false,false,false,true,false,false,false,false };

//this array sets if the screen updates left to right - true if left to right
bool leftToRightDisplay[moduleCount] = { true,true,true,false,true,true,true,true };

void Module::setModuleType(std::string enteredModule)
{
	bool found = false;
	for (int i = 0; i < moduleCount; i++) 
	{
		if (enteredModule == moduleType[i])
		{
			moduleMaster = moduleType[i];
			gBits = moduleGreyBits[i];
			rBits = moduleRedBits[i];
			modWidth = screenWidth[i];
			modLength = screenLength[i];
			reverseColor = reversedColor[i];
			leftToRight = leftToRightDisplay[i];
			found = true;
			break;
		}
	}
	if (!found)
	{
		printf("Module part number %s is not a valid Part number.\n", enteredModule.c_str());
		printf("The following are valid partnumbers:\n");
		for (int i = 0; i < moduleCount; i++)
		{
			printf("%s\n", moduleType[i].c_str());
		}
		system("pause");
		exit(3);
	}
}

int Module::getWidth()
{
	if (modWidth != NULL)
	{
		return(modWidth);
	}
	else
	{
		printf("No horizontal pixel value stored.");
		return 0;
	}
}


int Module::getLength()
{
	if (modLength != NULL)
	{
		return(modLength);
	}
	else
	{
		printf("No vertical pixel value stored.");
		return 0;
	}
}

int Module::getGBits()
{
	if (gBits != NULL)
	{
		return gBits;
	}
	else { printf("no grey bit value stored");
	return 0;
	}
}

int Module::getRBits()
{
	if (rBits != NULL)
	{
		return rBits;
	}
	else
	{
		printf("no red bit value stored");
		return 0;
	}
}


bool Module::getLTR(void)
{
	return leftToRight;

}
bool Module::getReverseColor(void)
{
	return reverseColor;
}