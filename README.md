# BMP to ePaper

ePaper products that this code is used for can be found at:
https://www.crystalfontz.com/c/epaper-displays/519

Code generated in Visual Studio 2017 and all code supplied in the respective folders. Currently, only "*.bmp" files are accepted by the software.

## Command Line
Pass a .bmp file as the first argument and the CFA part number as the second argument to the executable.
A .h file will be generated and saved in the same folder as the .bmp file. The header file can be used to generate an image on an ePaper display using the demo code supplied by Crystalfontz. Simple copy the new code and replace the existing code in any one of the "..._Images.h" files in the sample code.

## GUI
Run the executable in the "Release" folder to see how this program works.

The bit resolution section is determined by how many bits are required to power one pixel: 1-bit if each pixel is controlled by a single bit, 2-bit if each pixel is controlled by two bits, and N/A if the color is not supported by the display.