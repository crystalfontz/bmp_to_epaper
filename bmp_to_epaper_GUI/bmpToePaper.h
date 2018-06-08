#ifndef  __BMP_TO_EPAPER_H__
#define __BMP_TO_EPAPER_H__

std::string getOutputFile(const char *path);
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
int processImage(Module moduleData, std::string stringPath);

#endif
