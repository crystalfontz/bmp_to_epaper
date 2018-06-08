//============================================================================
// 
//
// 
// 
//============================================================================
#include "stdafx.h"
#include "ModuleType.h"
//This array classifies the existing ePaper modules


//============================================================================
//Information on the following block of code:
//gBits sets the number of bits the ePaper uses for black and white
//cBits sets the number of bits the ePaper uses for color;
//colorType
//  0: Mono
//  1: Red
//  2: Yellow
//
//modWidth sets the width of the dispaly
//modLength sets the length of the display
//reverseColor sets which polarity the bits are stored in the bitmap
//leftToRight true if the screen is set to update left to right, false if vice versa
void Module::setModuleType(std::string enteredModule)
{
	bool found = false;
    moduleMaster = enteredModule;
    if (enteredModule == "CFAP104212C00213")
    {
      gBits = 1;
      cBits = 1;
      colorType = 1;

      modWidth = 104;
      modLength = 212;
      reverseColor = false;
      leftToRight = true;
    }
    if (enteredModule == "CFAP104212D00213")
    {
      gBits = 1;
      cBits = 0;
      colorType = 0;

      modWidth = 104;
      modLength = 212;
      reverseColor = false;
      leftToRight = true;
    }
  else if (enteredModule == "CFAP122250A00213")
  {
    gBits = 1;
    cBits = 0;
    colorType = 0;

    modWidth = 122;
    modLength = 250;
    reverseColor = false;
    leftToRight = true;
  }
    else if (enteredModule == "CFAP128296A00290")
    {
      gBits = 2;
      cBits = 0;
      colorType = 0;

      modWidth = 128;
      modLength = 296;
      reverseColor = false;
      leftToRight = true;
    }
  else if (enteredModule == "CFAP128296C00290")
  {
    gBits = 1;
    cBits = 0;
    colorType = 0;

    modWidth = 128;
    modLength = 296;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP128296D00290")
  {
    gBits = 1;
    cBits = 1;
    colorType = 1;

    modWidth = 128;
    modLength = 296;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP128296E00290")
  {
    gBits = 1;
    cBits = 1;
    colorType = 2;

    modWidth = 128;
    modLength = 296;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP152152A00154")
  {
    gBits = 1;
    cBits = 1;
    colorType = 1;

    modWidth = 152;
    modLength = 152;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP176264A00270")
  {
    gBits = 1;
    cBits = 1;
    colorType = 1;

    modWidth = 176;
    modLength = 264;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP176264B00270")
  {
    gBits = 1;
    cBits = 0;
    colorType = 0;

    modWidth = 176;
    modLength = 264;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP200200A00154")
  {
    gBits = 1;
    cBits = 0;
    colorType = 0;

    modWidth = 122;
    modLength = 250;
    reverseColor = false;
    leftToRight = false;
  }
  else if (enteredModule == "CFAP400300C00420")
  {
    gBits = 1;
    cBits = 1;
    colorType = 2;

    modWidth = 400;
    modLength = 300;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP640384A00750")
  {
    gBits = 1;
    cBits = 0;
    colorType = 0;

    modWidth = 640;
    modLength = 384;
    reverseColor = false;
    leftToRight = true;
  }
  else
	{
    int size = 12;
    std::string moduleType[] =
    {
      "CFAP104212C00213",
      "CFAP122250A00213",
      "CFAP128296A00290",
      "CFAP128296C00290",
      "CFAP128296D00290",
      "CFAP128296E00290",
      "CFAP152152A00154",
      "CFAP176264A00270",
      "CFAP176264B00270",
      "CFAP200200A00154",
      "CFAP400300C00420",
      "CFAP640384A00750"
    };
		printf("Module part number %s is not a valid Part number.\n", enteredModule.c_str());
		printf("The following are valid partnumbers:\n");
		for (int i = 0; i < size; i++)
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

int Module::getCBits()
{
	if (cBits != NULL)
	{
		return cBits;
	}
	else
	{
		printf("no color bit value stored");
		return 0;
	}
}

int Module::getColor()
{
  if (colorType == 0)
  {
    return 0;
  }
  if (colorType == 1)
  {
    return 1;
  }
  if (colorType == 2)
  {
    return 2;
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