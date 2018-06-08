#include "ePaperModule.h"

void Module::initializeDisplay(int newrBits, int newyBits, int newbwBits, bool ltrInfo, bool ttbInfo, bool invInfo)
{
  rBits = newrBits;
  yBits = newyBits;
  bwBits = newbwBits;
  leftToRight = ltrInfo;
  topToBot = ttbInfo;
  reverseColor = invInfo;
}

int Module::getRBits(void)
{
  return rBits;
}

int Module::getYBits(void)
{
  return yBits;
}

int Module::getBWBits(void)
{
  return bwBits;
}

bool Module::getLTR(void)
{
  if (leftToRight) {
    return true;
  }
  else {
    return false;
  }
}

bool Module::getTTB(void)
{
  return topToBot;
}

bool Module::getInverted(void)
{
  return reverseColor;
}
