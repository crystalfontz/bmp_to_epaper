
//------------------------------------------------------------------------------
// Implmentation
//------------------------------------------------------------------------------

#include "CFA_FSO.h"

/* return the filename by itself */
std::string FILE_SYSTEM_OBJECT::getFileName(void)
{
  return fname;
}

/* return the filename and extension */
std::string FILE_SYSTEM_OBJECT::getFileNameAndExtension(void)
{
  std::string fullPath;
  fullPath = fname;
  fullPath += ext;
  return fullPath;
}

/* return the drive and path*/
std::string FILE_SYSTEM_OBJECT::getPath(void)
{
  std::string path;
  path = drive;
  path += dir;
  return path;
}

/* return the drive, path, filename, and extension */
std::string FILE_SYSTEM_OBJECT::getFullFile(void)
{
  std::string fullPath;
  fullPath = drive;
  fullPath += dir;
  fullPath += fname;
  fullPath += ext;
  return fullPath;
}

/* Sets the full path using a file */
void FILE_SYSTEM_OBJECT::setFullFile(const char *path)
{
  _splitpath_s(path, drive, dir, fname, ext);
}

