#ifndef __CFA_FSO_H__
#define __CFA_FSO_H__

#include <stdlib.h>
#include <iostream>
//HEADER
//------------------------------------------------------------------------------
class FILE_SYSTEM_OBJECT
{
private:
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];

public:
  //	FILE_SYSTEM_OBJECT();

  /* Sets the full path using a file */
  void setFullFile(const char *path);

  /* return the filename by itself */
  std::string getFileName(void);

  /* return the filename and extension */
  std::string getFileNameAndExtension(void);

  /* return the drive, path, filename, and extension */
  std::string getFullFile(void);

  /* return the drive and path*/
  std::string getPath(void);
};


#endif
