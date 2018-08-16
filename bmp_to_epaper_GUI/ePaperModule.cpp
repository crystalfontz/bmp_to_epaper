#include "ePaperModule.h"

void module_t::initializeDisplay(int newrBits, int newyBits, int newbwBits, bool ltrInfo, bool ttbInfo, bool invInfo)
{
  rBits = newrBits;
  yBits = newyBits;
  bwBits = newbwBits;
  leftToRight = ltrInfo;
  topToBot = ttbInfo;
  reverseColor = invInfo;
}

int module_t::getRBits(void)
{
  return rBits;
}

int module_t::getYBits(void)
{
  return yBits;
}

int module_t::getBWBits(void)
{
  return bwBits;
}

bool module_t::getLTR(void)
{
  return leftToRight;
}

bool module_t::getTTB(void)
{
  return topToBot;
}

bool module_t::getInverted(void)
{
  return reverseColor;
}
