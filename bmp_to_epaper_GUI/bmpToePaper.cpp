//=============================================================================
//
//  CRYSTALFONTZ ePaper 24-bit BMP file to data structure conversion code
//
//  Visual Studio 2017
//
//  ref: https://www.crystalfontz.com/
//
//=============================================================================
//This is free and unencumbered software released into the public domain.
//
//Anyone is free to copy, modify, publish, use, compile, sell, or
//distribute this software, either in source code form or as a compiled
//binary, for any purpose, commercial or non-commercial, and by any
//means.
//
//In jurisdictions that recognize copyright laws, the author or authors
//of this software dedicate any and all copyright interest in the
//software to the public domain. We make this dedication for the benefit
//of the public at large and to the detriment of our heirs and
//successors. We intend this dedication to be an overt act of
//relinquishment in perpetuity of all present and future rights to this
//software under copyright law.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
//
//For more information, please refer to <http://unlicense.org/>
//=============================================================================
//
// To make this static linked (no DLLs required)
//
//ref: https://social.msdn.microsoft.com/Forums/vstudio/en-US/845617aa-ab76-4fe1-a658-d020828598b8/static-linking-in-vs2010-runtime?forum=vcgeneral
//
//To set static linking:
//Configuration Properties, C/C++, Code Generation, Runtime Library -> MultiThreaded (/MT)
//In addition, if using MFC:
//Configuration Properties, General, Use of MFC -> Use MFC in a Static Library
//In addition, if using ATL:
//Configuration Properties, Genera, Use of ATL -> Static Link to ATL
//
//=============================================================================
#include "bmpToePaper.h"


//Set to 1 for a one dimensional array. Set to 0 for the more conventional
//2-dimensional array.
#define ONE_DIM (1)

//===========================================================================
//
//  ref http://stackoverflow.com/questions/14279242/read-bitmap-file-into-structure
//
//  These are the defines that are buried somewhere in windows.h
//
//typedef struct tagBITMAPFILEHEADER
//  {
//  WORD  bfType;       //specifies the file type
//  DWORD bfSize;       //specifies the size in bytes of the bitmap file
//  WORD  bfReserved1;  //reserved; must be 0
//  WORD  bfReserved2;  //reserved; must be 0
//  DWORD bOffBits;     //species the offset in bytes from the
//                      //bitmapfileheader to the bitmap bits
//  }BITMAPFILEHEADER;
//
//typedef  struct  tagBITMAPINFOHEADER
//  {
//  DWORD biSize;          //specifies the number of bytes required by the struct
//  LONG  biWidth;         //specifies width in pixels
//  LONG  biHeight;        //species height in pixels
//  WORD  biPlanes;        //specifies the number of color planes, must be 1
//  WORD  biBitCount;      //specifies the number of bit per pixel
//  DWORD biCompression;   //spcifies the type of compression
//  DWORD biSizeImage;     //size of image in bytes
//  LONG  biXPelsPerMeter; //number of pixels per meter in x axis
//  LONG  biYPelsPerMeter; //number of pixels per meter in y axis
//  DWORD biClrUsed;       //number of colors used by the bitmap
//  DWORD biClrImportant;  //number of colors that are important
//  }BITMAPINFOHEADER;
//
//===========================================================================
std::string getOutputFile(const char *path)
{
  std::string
    myPath;
  char
    drive[_MAX_DRIVE];
  char
    dir[_MAX_DIR];
  char
    fname[_MAX_FNAME];
  char
    ext[_MAX_EXT];

  _splitpath_s(path, drive, dir, fname, ext);

  myPath = drive;
  myPath += dir;
  myPath += fname;
  myPath += ".h";

  return myPath;
}

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
  FILE
    *filePtr;
  BITMAPFILEHEADER
    bitmapFileHeader;

  //We will allocate memory for the bitmap, image data at this pointer.
  unsigned char
    *bitmapImage;
  size_t
    bytes_read_from_bitmap;
  errno_t
    file_open_err;

  //open filename in read binary mode
  file_open_err = fopen_s(&filePtr, filename, "rb");
  if (file_open_err)
  {
    printf("Error# %d: %s reading the BMP in: \"%s\"\n", file_open_err, strerror(file_open_err), filename);
    return(NULL);
  }

  //read the bitmap file header
  fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

  //verify that this is a bmp file by check bitmap id
  if (0x4D42 != bitmapFileHeader.bfType)
  {
    fclose(filePtr);
    return(NULL);
  }

  //read the bitmap info header
  fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

  //move file point to the begining of bitmap data
  fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

  int imageSize = bitmapInfoHeader->biHeight*bitmapInfoHeader->biWidth * 3;

  //allocate enough memory for the bitmap image data
  bitmapImage = (unsigned char*)malloc(imageSize);


  //verify memory allocation
  if (NULL == bitmapImage)
  {
    fclose(filePtr);
    return(NULL);
  }

  //read in the bitmap image data
  bytes_read_from_bitmap =
    fread(bitmapImage, 1, imageSize, filePtr);

  //make sure bitmap image data was read
  if (bytes_read_from_bitmap != imageSize)
  {
    free(bitmapImage);
    fclose(filePtr);
    return(NULL);
  }

  //We are only set up to do 24 bit BMPs, which are
  //more or less standard.
  if (bitmapInfoHeader->biBitCount != 24)
  {
    free(bitmapImage);
    fclose(filePtr);
    return(NULL);
  }

  //close file
  fclose(filePtr);
  //return bitmap image data
  return(bitmapImage);
}
//===========================================================================
void usage(char *our_name)
{
  printf("Usage:\n");
  printf("  %s [infile]\n", our_name);
  printf("  [infile] is 24-bit BMP\n");
  printf("  This application will generate a c based header file for Gray 2BPP and Red 1BPP packed source\n");
}
//===========================================================================
int processImage(bool rlEncoded, bool oneDimArray, module_t moduleData, std::string stringPath)
{

  char* pathName = &stringPath[0u];

  BITMAPINFOHEADER
    bitmapInfoHeader;
  unsigned char
    *bitmapData;

  std::string outputFile = getOutputFile(pathName);

  printf("Reading input bitmap: %s\n", pathName);
  //Crack open the BMP, and read the image data
  bitmapData = LoadBitmapFile(pathName, &bitmapInfoHeader);

  //Check that the operation went OK.
  if (NULL == bitmapData)
  {
    printf("Error reading/processing the BMP.\n");
    system("pause");
    return(1);
  }

  printf("biWidth = %d\n", bitmapInfoHeader.biWidth);
  printf("biHeight = %d\n", bitmapInfoHeader.biHeight);
  printf("biBitCount = %d\n", bitmapInfoHeader.biBitCount);


  errno_t
    file_open_err;
  FILE
    *OutputDataFile;

  file_open_err = fopen_s(&OutputDataFile, outputFile.c_str(), "wt");
  if (file_open_err)
  {
    printf("Error# %d: %s opening the OutputDataFile file: \"%s\"\n", file_open_err, strerror(file_open_err), outputFile.c_str());
    //free the memory allocated by LoadBitmapFile
    free(bitmapData);
    //Indcicate failure, exit
    return(NULL);
  }
  printf("Opened \"%s\" as the 2bpp grey + 1bpp red output file.\n", outputFile.c_str());

  //The output file is open. Write out the header information to the grey file.
  fprintf(OutputDataFile, 
    "/* \n"
    " * Generated using \"BMP TO EPAPER\" by Crystalfontz of America\n"
    " * \n"
    " * The program can be found on our website at : \n"
    " *     https://www.crystalfontz.com/product/bmptoepaper-bitmap-to-epaper-software \n"
    " * \n"
    " * Or, the code can be forked from GitHub : \n"
    " *     https://github.com/crystalfontz/bmp_to_epaper \n"
    " * \n"
    " * RLE Image: %s\n"
    " * Non-Inverted Image: %s\n"
    " * One Dimensional Array: %s\n"
    " */\n\n",
    (rlEncoded ? "true" : "false"),
    (moduleData.getInverted() ? "true" : "false"),
    (oneDimArray ? "true" : "false")
  );

  fprintf(OutputDataFile, "//Source image file: \"%s\"\n", pathName);
  fprintf(OutputDataFile, "#define HEIGHT_PIXELS    (%d)\n", bitmapInfoHeader.biHeight);
  fprintf(OutputDataFile, "#define WIDTH_PIXELS     (%d)\n", bitmapInfoHeader.biWidth);

  if (moduleData.getBWBits() == 2)
    fprintf(OutputDataFile, "#define WIDTH_GREY_BYTES (%d)\n", (bitmapInfoHeader.biWidth + 0x03) >> 2);

  if (moduleData.getBWBits() == 1)
    fprintf(OutputDataFile, "#define WIDTH_MONO_BYTES (%d)\n", (bitmapInfoHeader.biWidth + 0x07) >> 3);

  if (moduleData.getRBits() == 1)
    fprintf(OutputDataFile, "#define WIDTH_RED_BYTES  (%d)\n", (bitmapInfoHeader.biWidth + 0x07) >> 3);

  if (moduleData.getYBits() == 1)
    fprintf(OutputDataFile, "#define WIDTH_YELLOW_BYTES  (%d)\n", (bitmapInfoHeader.biWidth + 0x07) >> 3);

  //Now we just loop down the file, line by line (bottom first),
  //create the 16-bit words and spool them out.
  int
    col;
  int
    row;

  //Our pointer into the bitmap data
  unsigned char
    *data_pointer;

  //The width of a line, in bytes, bust be a multiple of 4;
  int
    line_width;

  //3 bytes per pixel, round up to next 4-byte alignment
  line_width = ((3 * bitmapInfoHeader.biWidth) + 3) & ~0x03;

  //---------------------------------------------------------------------------
  if (moduleData.getBWBits() == 2)
  {

    if (oneDimArray)
    {
      fprintf(OutputDataFile,
        "\nconst uint8_t Grey_2BPP[%d] PROGMEM = \n  {",
        bitmapInfoHeader.biHeight*((bitmapInfoHeader.biWidth + 0x03) >> 2));
    }
    else
    {
      fprintf(OutputDataFile,
        "\nconst uint8_t Grey_2BPP[%d][%d] PROGMEM =\n  {{",
        bitmapInfoHeader.biHeight,
        (bitmapInfoHeader.biWidth + 0x03) >> 2);
    }

    for (row = 0; row < bitmapInfoHeader.biHeight; row++)
    {
      int
        first_data_of_this_line_written;
      first_data_of_this_line_written = 0;

      if (moduleData.getTTB()) {
        //Point to the current row in the bitmap data (starting at the bottom since bitmaps are upside down)
        data_pointer = bitmapData + (bitmapInfoHeader.biHeight - 1 - row)*line_width;
      }
      else {
        data_pointer = bitmapData + row * line_width;
      }

      if (!moduleData.getLTR())
      {
        data_pointer += ((bitmapInfoHeader.biWidth) * 3) - 1;
      }

      //We need to push 4 pixels into one 8-bit byte.
      unsigned char
        this_2bpp_byte;
      int
        sub_pixel_count;

      this_2bpp_byte = 0x00;
      sub_pixel_count = 0;

      //work across the row.
      for (col = 0; col < bitmapInfoHeader.biWidth; col++)
      {
        unsigned char
          red;
        unsigned char
          green;
        unsigned char
          blue;

        //pull the pixel out of the stream first statement is if the display goes left to right
        //second statement is if the display goes right to left
        if (moduleData.getLTR())
        {
          blue = *data_pointer++;
          green = *data_pointer++;
          red = *data_pointer++;
        }
        else
        {
          red = *data_pointer--;
          green = *data_pointer--;
          blue = *data_pointer--;
        }

        //Now decide what color of the ink we are
        //going to use for this pixel.
        unsigned char
          sub_pixel_2bit;

        //Check for the special case of it being a red pixel
        if ((171 < red) && (green < 85) && (blue < 85))
        {
          //since we are writing the black/grey/white plane, we
          //want to put white wherre this red pixel would fall.
          sub_pixel_2bit = 0x00;  // 00 = White
        }
        else
        {
          //See if it is a white pixel
          if ((171 < red) && (171 < green) && (171 < blue))
          {
            sub_pixel_2bit = 0x00;  // 00 = White
          }
          else
          {
            //See if it is a 50% gray pixel
            if ((85 < red) && (red < 171) &&
              (85 < green) && (green < 171) &&
              (85 < blue) && (blue < 171))
            {
              sub_pixel_2bit = 0x01;  // 01 or 10 = Grey 
            }
            else
            {
              //default to black
              sub_pixel_2bit = 0x03;  //11 = black
            }
          }
        }

        //Insert those bits into the correct slot of this_2bpp_byte
        this_2bpp_byte |= (sub_pixel_2bit) << ((3 - sub_pixel_count) * 2);

        //Move to the next sub-pixel
        sub_pixel_count++;
        //If this byte is full, write it out and clear for the 
        //next 4 bytes.
        if (3 < sub_pixel_count)
        {
          if (first_data_of_this_line_written)
          {
            fprintf(OutputDataFile, ",");
          }
          first_data_of_this_line_written = 1;
          //Then write out the 8-bit packed pixel
          fprintf(OutputDataFile, "0x%02X", this_2bpp_byte);
          //Reset the byte accumulator and count
          this_2bpp_byte = 0;
          sub_pixel_count = 0;
        }
      }
      //This is the last entry for this line. If we have not just written
      //out the last byte, of this line write it out now.
      if (sub_pixel_count)
      {
        if (first_data_of_this_line_written)
        {
          fprintf(OutputDataFile, ",");
        }
        first_data_of_this_line_written = 1;
        //Then write out the 8bit packed pixel.
        fprintf(OutputDataFile, "0x%02X", this_2bpp_byte);
      }

      if (oneDimArray)
      {
        //That is the end of one line. Complete the C syntax.
        if (row == (bitmapInfoHeader.biHeight - 1))
        {
          fprintf(OutputDataFile, "};\n");
        }
        else
        {
          fprintf(OutputDataFile, ",\n   ");
        }
      }
      else
      {
        //That is the end of one line. Complete the C syntax.
        if (row == (bitmapInfoHeader.biHeight - 1))
        {
          fprintf(OutputDataFile, "}};\n");
        }
        else
        {
          fprintf(OutputDataFile, "},\n   {");
        }
      }
    }
  }//  OUTPUT2BPPGREY
//===========================================================================





  if (moduleData.getBWBits() == 1)
  {
    //Write out the header information to the red file.
    if (!rlEncoded)
    {
      if (oneDimArray)
      {
      fprintf(OutputDataFile,
        "\nconst uint8_t Mono_1BPP[%d] PROGMEM =\n  {",
        bitmapInfoHeader.biHeight*((bitmapInfoHeader.biWidth + 0x07) >> 3));
      }
      else
      {
      fprintf(OutputDataFile,
        "\nconst uint8_t Mono_1BPP[%d][%d] PROGMEM =\n  {{",
        bitmapInfoHeader.biHeight,
        (bitmapInfoHeader.biWidth + 0x07) >> 3);
      }
    }
    //Now we just loop down the file, line by line (bottom first),
    std::deque <rows_t>	redQueue;
    rows_t rows;
    int arraySize = 0;
    int longestRow = 0;
    for (row = 0; row < bitmapInfoHeader.biHeight; row++)
    {
      int
        first_data_of_this_line_written;
      first_data_of_this_line_written = 0;
      int thisRow = arraySize;

      if (moduleData.getTTB()) {
        //Point to the current row in the bitmap data (starting at the bottom since bitmaps are upside down)
        data_pointer = bitmapData + (bitmapInfoHeader.biHeight - 1 - row)*line_width;
      }
      else {
        data_pointer = bitmapData + row * line_width;
      }

      //check to see if the module updates from left to right, if it's right to left we need to move the pointer
      if (!moduleData.getLTR())
      {
        data_pointer += ((bitmapInfoHeader.biWidth) * 3) - 1;
      }

      //We need to push 8 pixels into one 8-bit byte.
      unsigned char
        this_1bpp_byte;
      int
        sub_pixel_count;
      unsigned char holder1 = 0x00;
      unsigned char holder2 = 0x00;
      unsigned char holder3 = 0x00;
      unsigned char rle_counter = 0;
      bool rle_active = false;

      this_1bpp_byte = 0x00;
      sub_pixel_count = 0;

      //work across the row
      for (col = 0; col < bitmapInfoHeader.biWidth; col++)
      {
        unsigned char
          red;
        unsigned char
          green;
        unsigned char
          blue;

        //pull the pixel out of the stream first statement is if the display goes left to right
        //second statement is if the display goes right to left
        if (moduleData.getLTR())
        {
          blue = *data_pointer++;
          green = *data_pointer++;
          red = *data_pointer++;
        }
        else
        {
          red = *data_pointer--;
          green = *data_pointer--;
          blue = *data_pointer--;
        }

        //Now decide what color of the ink we are
        //going to use for this pixel.
        unsigned char
          sub_pixel_1bit;

        //White is just above 50% grey
        if (127 > ((red*.21) + (green*.72) + (blue*.07)))
        {
          //black, put the ink
          if (!moduleData.getInverted())
          {
            sub_pixel_1bit = 0x01;  // 1 = black
          }
          else
          {
            sub_pixel_1bit = 0x00;  // 0 = black
          }
        }
        else
        {
          //This is white, no ink
          if (!moduleData.getInverted())
          {
            sub_pixel_1bit = 0x00;  // 0 = white
          }
          else
          {
            sub_pixel_1bit = 0x01;  // 1 = white
          }
        }

        //Insert those bits into the correct slot of this_2bpp_byte
        this_1bpp_byte |= (sub_pixel_1bit) << (7 - sub_pixel_count);

        //Move to the next sub-pixel
        sub_pixel_count++;
        //If this byte is full, write it out and clear for the 
        //next 4 bytes.
        if (7 < sub_pixel_count)
        {

          //TODO: finish IF statement to check if RLE decoding is selected
          if (rlEncoded)
          {

            //  //if we're past the first two bytes of data
            if (first_data_of_this_line_written == 1)
            {
              //addToRow(rlEncoded, &rle_active, &rle_counter, &arraySize, &rows, holder1, holder2, this_1bpp_byte);
                  //if we have a situation where we can increment the rle counter
                  if (holder1 == holder2 && holder2 == this_1bpp_byte)
                  {
                    if (rle_active)
                    {
                      rle_counter++;
                    }
                    else
                    {
                      rle_counter = 3;
                      rle_active = true;
                    }
                  }
                  //situation where we've hit a byte that stops us from incrementing the rle counter
                  else if (rle_active)
                  {
                    if (holder1 != holder2)
                    {
                      rows.rlePairs.push_back(rlePair_t{ rle_counter, holder1 });
                      rle_active = false;
                      arraySize += 2;
                    }
                  }
                  //situation where we are not in a loop of the rle counter working
                  else
                  {
                    rows.rlePairs.push_back(rlePair_t{ 1,holder1 });
                    arraySize += 2;
                  }
            }
            else
            {
              if (first_data_of_this_line_written == -1)
              {
                first_data_of_this_line_written = 1;
              }
              else
              {
                first_data_of_this_line_written = -1;
              }
            }
            holder1 = holder2;
            holder2 = this_1bpp_byte;
          }
          else
          {
            if (first_data_of_this_line_written)
            {
              fprintf(OutputDataFile, ",");
            }
            first_data_of_this_line_written = 1;
            //Then write out the 16-bit packed pixel to the bin file.
            fprintf(OutputDataFile, "0x%02X", this_1bpp_byte);
          }
          //Reset the byte accumulator and count
          this_1bpp_byte = 0;
          sub_pixel_count = 0;
        }
      }

      //This is the last entry for this line. If we have not just written
      //out the last byte, of this line write it out now.

      //check to see if we're going to use RLE or just print out each byte
      if (rlEncoded)
      {
        if (rle_active)
        {
          rows.rlePairs.push_back(rlePair_t{ rle_counter,holder1 });
          //If holder1 and holder2 do not match, that means we have another 
          //unique byte at the end of the line to account for
          if (holder1 != holder2)
          {
            rows.rlePairs.push_back(rlePair_t{ 1,holder2 });
            arraySize += 2;
          }
          rle_active = false;
          arraySize += 2;
        }
        //TODO: check to make sure this works for pixels that are trailing
        else
        {
          rows.rlePairs.push_back(rlePair_t{ 1, holder1 });
          rows.rlePairs.push_back(rlePair_t{ 1, holder2 });
          arraySize += 4;
        }
      }
      else
      {
        if (sub_pixel_count)
        {
          if (first_data_of_this_line_written)
          {
            fprintf(OutputDataFile, ",");
          }
          first_data_of_this_line_written = 0;
          //Then write out the 16-bit packed pixel to the bin file.
          fprintf(OutputDataFile, "0x%02X", this_1bpp_byte);
        }

        if (oneDimArray)
        {
          //That is the end of one line. Complete the C syntax.
          if (row == (bitmapInfoHeader.biHeight - 1))
          {
            fprintf(OutputDataFile, "};\n");
          }
          else
          {
            fprintf(OutputDataFile, ",\n   ");
          }
        }
        else
        {
          //That is the end of one line. Complete the C syntax.
          if (row == (bitmapInfoHeader.biHeight - 1))
          {
            fprintf(OutputDataFile, "}};\n");
          }
          else
          {
            fprintf(OutputDataFile, "},\n   {");
          }
        }
      }
      //only used for two dimensional arrays to capture the longest row
      if (longestRow < (arraySize - thisRow))
      {
        longestRow = (arraySize - thisRow);
      }
      //before going to the next row, push this row into the deque
      redQueue.push_back(rows);
      rows.rlePairs.clear();
    }
    //write the file at the end of the statement
    if (rlEncoded)
    {

      if (oneDimArray)
      {
        fprintf(OutputDataFile, "\n#define MONO_ARRAY_SIZE (%d)\n", arraySize);
        fprintf(OutputDataFile,
          "\nconst uint8_t Mono_1BPP[%d] PROGMEM =\n  {", arraySize);
      }
      else
      {
        fprintf(OutputDataFile, "\n#define MONO_WIDTH_SIZE (%d)", longestRow);
        fprintf(OutputDataFile, "\n#define MONO_HEIGHT_SIZE (%d)\n", bitmapInfoHeader.biHeight);
        fprintf(OutputDataFile,
          "\nconst uint8_t Mono_1BPP[%d][%d] PROGMEM =\n  {{",
          bitmapInfoHeader.biHeight,
          longestRow);
      }
      //loop through the queue to print to the file
      unsigned char rle_count;
      unsigned char rle_val;
      while (redQueue.size() > 0)
      {
        while (redQueue.at(0).rlePairs.size() > 0)
        {
          rle_count = redQueue.at(0).rlePairs.at(0).count;
          rle_val = redQueue.at(0).rlePairs.at(0).val;
          fprintf(OutputDataFile, "%d,", rle_count);
          fprintf(OutputDataFile, "0x%02X", rle_val);
          //check to see if it's the last character
          if (redQueue.size() != 1 && redQueue.at(0).rlePairs.size() != 1)
          {
            fprintf(OutputDataFile, ",");
          }
          redQueue.at(0).rlePairs.pop_front();
        }
        redQueue.pop_front();

        if (oneDimArray)
        {
          //That is the end of one line. Complete the C syntax.
          if (redQueue.size() == 0)
          {
            fprintf(OutputDataFile, "};\n");
          }
          else
          {
            fprintf(OutputDataFile, ",\n   ");
          }
        }
        else
        {
          //That is the end of one line. Complete the C syntax.
          if (row == (bitmapInfoHeader.biHeight - 1))
          {
            fprintf(OutputDataFile, "}};\n");
          }
          else
          {
            fprintf(OutputDataFile, "},\n   {");
          }
        }
      }
    }
  }  //  OUTPUT1BPPMONO
//===========================================================================




  if (moduleData.getRBits() == 1)
  {
    //Write out the header information to the red file.
    if (!rlEncoded)
    {
      if (oneDimArray)
      {
        fprintf(OutputDataFile,
          "\nconst uint8_t Red_1BPP[%d] PROGMEM =\n  {",
          bitmapInfoHeader.biHeight*((bitmapInfoHeader.biWidth + 0x07) >> 3));
      }
      else
      {
        fprintf(OutputDataFile,
          "\nconst uint8_t Red_1BPP[%d][%d] PROGMEM =\n  {{",
          bitmapInfoHeader.biHeight,
          (bitmapInfoHeader.biWidth + 0x07) >> 3);
      }
    }
    //Now we just loop down the file, line by line (bottom first),
    std::deque <rows_t>	redQueue;
    rows_t rows;
    int arraySize = 0;
    int longestRow = 0;
    for (row = 0; row < bitmapInfoHeader.biHeight; row++)
    {
      int
        first_data_of_this_line_written;
      first_data_of_this_line_written = 0;
      int thisRow = arraySize;

      if (moduleData.getTTB()) {
        //Point to the current row in the bitmap data (starting at the bottom since bitmaps are upside down)
        data_pointer = bitmapData + (bitmapInfoHeader.biHeight - 1 - row)*line_width;
      }
      else {
        data_pointer = bitmapData + row * line_width;
      }

      //check to see if the module updates from left to right, if it's right to left we need to move the pointer
      if (!moduleData.getLTR())
      {
        data_pointer += ((bitmapInfoHeader.biWidth) * 3) - 1;
      }

      //We need to push 8 pixels into one 8-bit byte.
      unsigned char
        this_1bpp_byte;
      int
        sub_pixel_count;
      unsigned char holder1 = 0x00;
      unsigned char holder2 = 0x00;
      unsigned char holder3 = 0x00;
      unsigned char rle_counter = 0;
      bool rle_active = false;

      this_1bpp_byte = 0x00;
      sub_pixel_count = 0;

      //work across the row
      for (col = 0; col < bitmapInfoHeader.biWidth; col++)
      {
        unsigned char
          red;
        unsigned char
          green;
        unsigned char
          blue;

        //pull the pixel out of the stream first statement is if the display goes left to right
        //second statement is if the display goes right to left
        if (moduleData.getLTR())
        {
          blue = *data_pointer++;
          green = *data_pointer++;
          red = *data_pointer++;
        }
        else
        {
          red = *data_pointer--;
          green = *data_pointer--;
          blue = *data_pointer--;
        }

        //Now decide what color of the ink we are
        //going to use for this pixel.
        unsigned char
          sub_pixel_1bit;

        //Check to see if it's a red pixel
        if ((155 < red) && (green < 110) && (blue < 110))
        {
          //red, put the ink
          if (!moduleData.getInverted())
          {
            sub_pixel_1bit = 0x01;  // 1 = black
          }
          else
          {
            sub_pixel_1bit = 0x00;  // 0 = black
          }
        }
        else
        {
          //This is not red, no ink
          if (!moduleData.getInverted())
          {
            sub_pixel_1bit = 0x00;  // 0 = white
          }
          else
          {
            sub_pixel_1bit = 0x01;  // 1 = white
          }
        }

        //Insert those bits into the correct slot of this_2bpp_byte
        this_1bpp_byte |= (sub_pixel_1bit) << (7 - sub_pixel_count);

        //Move to the next sub-pixel
        sub_pixel_count++;
        //If this byte is full, write it out and clear for the 
        //next 4 bytes.
        if (7 < sub_pixel_count)
        {

          //TODO: finish IF statement to check if RLE decoding is selected
          if (rlEncoded)
          {

            //  //if we're past the first two bytes of data
            if (first_data_of_this_line_written == 1)
            {
              //if we have a situation where we can increment the rle counter
              if (holder1 == holder2 && holder2 == this_1bpp_byte)
              {
                if (rle_active)
                {
                  rle_counter++;
                }
                else
                {
                  rle_counter = 3;
                  rle_active = true;
                }
              }
              //situation where we've hit a byte that stops us from incrementing the rle counter
              else if (rle_active)
              {
                if (holder1 != holder2)
                {
                  rows.rlePairs.push_back(rlePair_t{ rle_counter, holder1 });
                  rle_active = false;
                  arraySize += 2;
                }
              }
              //situation where we are not in a loop of the rle counter working
              else
              {
                rows.rlePairs.push_back(rlePair_t{ 1,holder1 });
                arraySize += 2;
              }
            }
            else
            {
              if (first_data_of_this_line_written == -1)
              {
                first_data_of_this_line_written = 1;
              }
              else
              {
                first_data_of_this_line_written = -1;
              }
            }
            holder1 = holder2;
            holder2 = this_1bpp_byte;
          }
          else
          {
            if (first_data_of_this_line_written)
            {
              fprintf(OutputDataFile, ",");
            }
            first_data_of_this_line_written = 1;
            //Then write out the 16-bit packed pixel to the bin file.
            fprintf(OutputDataFile, "0x%02X", this_1bpp_byte);
          }
          //Reset the byte accumulator and count
          this_1bpp_byte = 0;
          sub_pixel_count = 0;
        }
      }

      //This is the last entry for this line. If we have not just written
      //out the last byte, of this line write it out now.

      //check to see if we're going to use RLE or just print out each byte
      if (rlEncoded)
      {
        if (rle_active)
        {
          rows.rlePairs.push_back(rlePair_t{ rle_counter,holder1 });
          //If holder1 and holder2 do not match, that means we have another 
          //unique byte at the end of the line to account for
          if (holder1 != holder2)
          {
            rows.rlePairs.push_back(rlePair_t{ 1,holder2 });
            arraySize += 2;
          }
          rle_active = false;
          arraySize += 2;
        }
        //TODO: check to make sure this works for pixels that are trailing
        else
        {
          rows.rlePairs.push_back(rlePair_t{ 1, holder1 });
          rows.rlePairs.push_back(rlePair_t{ 1, holder2 });
          arraySize += 4;
        }
      }
      else
      {
        if (sub_pixel_count)
        {
          if (first_data_of_this_line_written)
          {
            fprintf(OutputDataFile, ",");
          }
          first_data_of_this_line_written = 0;
          //Then write out the 16-bit packed pixel to the bin file.
          fprintf(OutputDataFile, "0x%02X", this_1bpp_byte);
        }

        if (oneDimArray)
        {
          //That is the end of one line. Complete the C syntax.
          if (row == (bitmapInfoHeader.biHeight - 1))
          {
            fprintf(OutputDataFile, "};\n");
          }
          else
          {
            fprintf(OutputDataFile, ",\n   ");
          }
        }
        else
        {
          //That is the end of one line. Complete the C syntax.
          if (row == (bitmapInfoHeader.biHeight - 1))
          {
            fprintf(OutputDataFile, "}};\n");
          }
          else
          {
            fprintf(OutputDataFile, "},\n   {");
          }
        }
      }
      //only used for two dimensional arrays to capture the longest row
      if (longestRow < (arraySize - thisRow))
      {
        longestRow = (arraySize - thisRow);
      }
      //before going to the next row, push this row into the deque
      redQueue.push_back(rows);
      rows.rlePairs.clear();
    }
    //write the file at the end of the statement
    if (rlEncoded)
    {

      if (oneDimArray)
      {
        fprintf(OutputDataFile, "\n#define RED_ARRAY_SIZE (%d)\n", arraySize);
        fprintf(OutputDataFile,
          "\nconst uint8_t Red_1BPP[%d] PROGMEM =\n  {", arraySize);
      }
      else
      {
        fprintf(OutputDataFile, "\n#define RED_WIDTH_SIZE (%d)", longestRow);
        fprintf(OutputDataFile, "\n#define RED_HEIGHT_SIZE (%d)\n", bitmapInfoHeader.biHeight);
        fprintf(OutputDataFile,
          "\nconst uint8_t Red_1BPP[%d][%d] PROGMEM =\n  {{",
          bitmapInfoHeader.biHeight,
          longestRow);
      }
      //loop through the queue to print to the file
      unsigned char rle_count;
      unsigned char rle_val;
      while (redQueue.size() > 0)
      {
        while (redQueue.at(0).rlePairs.size() > 0)
        {
          rle_count = redQueue.at(0).rlePairs.at(0).count;
          rle_val = redQueue.at(0).rlePairs.at(0).val;
          fprintf(OutputDataFile, "%d,", rle_count);
          fprintf(OutputDataFile, "0x%02X", rle_val);
          //check to see if it's the last character
          if (redQueue.size() != 1 && redQueue.at(0).rlePairs.size() != 1)
          {
            fprintf(OutputDataFile, ",");
          }
          redQueue.at(0).rlePairs.pop_front();
        }
        redQueue.pop_front();

        if (oneDimArray)
        {
          //That is the end of one line. Complete the C syntax.
          if (redQueue.size() == 0)
          {
            fprintf(OutputDataFile, "};\n");
          }
          else
          {
            fprintf(OutputDataFile, ",\n   ");
          }
        }
        else
        {
          //That is the end of one line. Complete the C syntax.
          if (row == (bitmapInfoHeader.biHeight - 1))
          {
            fprintf(OutputDataFile, "}};\n");
          }
          else
          {
            fprintf(OutputDataFile, "},\n   {");
          }
        }
      }
    }
  }  //  OUTPUT1BPPRED
//===========================================================================





  if (moduleData.getYBits() == 1)
  {
    //Write out the header information to the red file.
    if (!rlEncoded)
    {
      if (oneDimArray)
      {
        fprintf(OutputDataFile,
          "\nconst uint8_t Yellow_1BPP[%d] PROGMEM =\n  {",
          bitmapInfoHeader.biHeight*((bitmapInfoHeader.biWidth + 0x07) >> 3));
      }
      else
      {
        fprintf(OutputDataFile,
          "\nconst uint8_t Yellow_1BPP[%d][%d] PROGMEM =\n  {{",
          bitmapInfoHeader.biHeight,
          (bitmapInfoHeader.biWidth + 0x07) >> 3);
      }
    }
    //Now we just loop down the file, line by line (bottom first),
    std::deque <rows_t>	redQueue;
    rows_t rows;
    int arraySize = 0;
    int longestRow = 0;
    for (row = 0; row < bitmapInfoHeader.biHeight; row++)
    {
      int
        first_data_of_this_line_written;
      first_data_of_this_line_written = 0;
      int thisRow = arraySize;

      if (moduleData.getTTB()) {
        //Point to the current row in the bitmap data (starting at the bottom since bitmaps are upside down)
        data_pointer = bitmapData + (bitmapInfoHeader.biHeight - 1 - row)*line_width;
      }
      else {
        data_pointer = bitmapData + row * line_width;
      }

      //check to see if the module updates from left to right, if it's right to left we need to move the pointer
      if (!moduleData.getLTR())
      {
        data_pointer += ((bitmapInfoHeader.biWidth) * 3) - 1;
      }

      //We need to push 8 pixels into one 8-bit byte.
      unsigned char
        this_1bpp_byte;
      int
        sub_pixel_count;
      unsigned char holder1 = 0x00;
      unsigned char holder2 = 0x00;
      unsigned char holder3 = 0x00;
      unsigned char rle_counter = 0;
      bool rle_active = false;

      this_1bpp_byte = 0x00;
      sub_pixel_count = 0;

      //work across the row
      for (col = 0; col < bitmapInfoHeader.biWidth; col++)
      {
        unsigned char
          red;
        unsigned char
          green;
        unsigned char
          blue;

        //pull the pixel out of the stream first statement is if the display goes left to right
        //second statement is if the display goes right to left
        if (moduleData.getLTR())
        {
          blue = *data_pointer++;
          green = *data_pointer++;
          red = *data_pointer++;
        }
        else
        {
          red = *data_pointer--;
          green = *data_pointer--;
          blue = *data_pointer--;
        }

        //Now decide what color of the ink we are
        //going to use for this pixel.
        unsigned char
          sub_pixel_1bit;

        //check to see if it's a yellow pixel
        if ((228 < red) && (180 < green) && (blue < 30))
        {
          //yellow, put the ink
          if (!moduleData.getInverted())
          {
            sub_pixel_1bit = 0x01;  // 1 = yellow
          }
          else
          {
            sub_pixel_1bit = 0x00;  // 0 = yellow
          }
        }
        else
        {
          //This is non-yellow, no ink
          if (!moduleData.getInverted())
          {
            sub_pixel_1bit = 0x00;  // 0 = non-yellow
          }
          else
          {
            sub_pixel_1bit = 0x01;  // 1 = non-yellow
          }
        }

        //Insert those bits into the correct slot of this_2bpp_byte
        this_1bpp_byte |= (sub_pixel_1bit) << (7 - sub_pixel_count);

        //Move to the next sub-pixel
        sub_pixel_count++;
        //If this byte is full, write it out and clear for the 
        //next 4 bytes.
        if (7 < sub_pixel_count)
        {

          //TODO: finish IF statement to check if RLE decoding is selected
          if (rlEncoded)
          {

            //  //if we're past the first two bytes of data
            if (first_data_of_this_line_written == 1)
            {
              //if we have a situation where we can increment the rle counter
              if (holder1 == holder2 && holder2 == this_1bpp_byte)
              {
                if (rle_active)
                {
                  rle_counter++;
                }
                else
                {
                  rle_counter = 3;
                  rle_active = true;
                }
              }
              //situation where we've hit a byte that stops us from incrementing the rle counter
              else if (rle_active)
              {
                if (holder1 != holder2)
                {
                  rows.rlePairs.push_back(rlePair_t{ rle_counter, holder1 });
                  rle_active = false;
                  arraySize += 2;
                }
              }
              //situation where we are not in a loop of the rle counter working
              else
              {
                rows.rlePairs.push_back(rlePair_t{ 1,holder1 });
                arraySize += 2;
              }
            }
            else
            {
              if (first_data_of_this_line_written == -1)
              {
                first_data_of_this_line_written = 1;
              }
              else
              {
                first_data_of_this_line_written = -1;
              }
            }
            holder1 = holder2;
            holder2 = this_1bpp_byte;
          }
          else
          {
            if (first_data_of_this_line_written)
            {
              fprintf(OutputDataFile, ",");
            }
            first_data_of_this_line_written = 1;
            //Then write out the 16-bit packed pixel to the bin file.
            fprintf(OutputDataFile, "0x%02X", this_1bpp_byte);
          }
          //Reset the byte accumulator and count
          this_1bpp_byte = 0;
          sub_pixel_count = 0;
        }
      }

      //This is the last entry for this line. If we have not just written
      //out the last byte, of this line write it out now.

      //check to see if we're going to use RLE or just print out each byte
      if (rlEncoded)
      {
        if (rle_active)
        {
          rows.rlePairs.push_back(rlePair_t{ rle_counter,holder1 });
          //If holder1 and holder2 do not match, that means we have another 
          //unique byte at the end of the line to account for
          if (holder1 != holder2)
          {
            rows.rlePairs.push_back(rlePair_t{ 1,holder2 });
            arraySize += 2;
          }
          rle_active = false;
          arraySize += 2;
        }
        //TODO: check to make sure this works for pixels that are trailing
        else
        {
          rows.rlePairs.push_back(rlePair_t{ 1, holder1 });
          rows.rlePairs.push_back(rlePair_t{ 1, holder2 });
          arraySize += 4;
        }
      }
      else
      {
        if (sub_pixel_count)
        {
          if (first_data_of_this_line_written)
          {
            fprintf(OutputDataFile, ",");
          }
          first_data_of_this_line_written = 0;
          //Then write out the 16-bit packed pixel to the bin file.
          fprintf(OutputDataFile, "0x%02X", this_1bpp_byte);
        }

        if (oneDimArray)
        {
          //That is the end of one line. Complete the C syntax.
          if (row == (bitmapInfoHeader.biHeight - 1))
          {
            fprintf(OutputDataFile, "};\n");
          }
          else
          {
            fprintf(OutputDataFile, ",\n   ");
          }
        }
        else
        {
          //That is the end of one line. Complete the C syntax.
          if (row == (bitmapInfoHeader.biHeight - 1))
          {
            fprintf(OutputDataFile, "}};\n");
          }
          else
          {
            fprintf(OutputDataFile, "},\n   {");
          }
        }
      }
      //only used for two dimensional arrays to capture the longest row
      if (longestRow < (arraySize - thisRow))
      {
        longestRow = (arraySize - thisRow);
      }
      //before going to the next row, push this row into the deque
      redQueue.push_back(rows);
      rows.rlePairs.clear();
    }
    //write the file at the end of the statement
    if (rlEncoded)
    {

      if (oneDimArray)
      {
        fprintf(OutputDataFile, "\n#define YELLOW_ARRAY_SIZE (%d)\n", arraySize);
        fprintf(OutputDataFile,
          "\nconst uint8_t Yellow_1BPP[%d] PROGMEM =\n  {", arraySize);
      }
      else
      {
        fprintf(OutputDataFile, "\n#define YELLOW_WIDTH_SIZE (%d)", longestRow);
        fprintf(OutputDataFile, "\n#define YELLOW_HEIGHT_SIZE (%d)\n", bitmapInfoHeader.biHeight);
        fprintf(OutputDataFile,
          "\nconst uint8_t Yellow_1BPP[%d][%d] PROGMEM =\n  {{",
          bitmapInfoHeader.biHeight,
          longestRow);
      }
      //loop through the queue to print to the file
      unsigned char rle_count;
      unsigned char rle_val;
      while (redQueue.size() > 0)
      {
        while (redQueue.at(0).rlePairs.size() > 0)
        {
          rle_count = redQueue.at(0).rlePairs.at(0).count;
          rle_val = redQueue.at(0).rlePairs.at(0).val;
          fprintf(OutputDataFile, "%d,", rle_count);
          fprintf(OutputDataFile, "0x%02X", rle_val);
          //check to see if it's the last character
          if (redQueue.size() != 1 && redQueue.at(0).rlePairs.size() != 1)
          {
            fprintf(OutputDataFile, ",");
          }
          redQueue.at(0).rlePairs.pop_front();
        }
        redQueue.pop_front();

        if (oneDimArray)
        {
          //That is the end of one line. Complete the C syntax.
          if (redQueue.size() == 0)
          {
            fprintf(OutputDataFile, "};\n");
          }
          else
          {
            fprintf(OutputDataFile, ",\n   ");
          }
        }
        else
        {
          //That is the end of one line. Complete the C syntax.
          if (row == (bitmapInfoHeader.biHeight - 1))
          {
            fprintf(OutputDataFile, "}};\n");
          }
          else
          {
            fprintf(OutputDataFile, "},\n   {");
          }
        }
      }
    }
  }  //  OUTPUT1BPPYELLOW
//===========================================================================



     //Done with the output file.
  fclose(OutputDataFile);

  //free the memory allocated by LoadBitmapFile
  free(bitmapData);

  printf("Complete.\n");

  //Indicate success, exit
  return(0);
}
//===========================================================================
