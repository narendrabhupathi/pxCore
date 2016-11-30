// pxCore CopyRight 2007-2015 John Robinson
// Portable Framebuffer and Windowing Library
// pxColors.h

#ifndef PXOFFSCREEN_H
#define PXOFFSCREEN_H

#include "pxCore.h"
#include "pxBuffer.h"

// Class used to create and manage offscreen pixmaps
// This class subclasses pxBuffer (pxBuffer.h)
// Please refer to pxBuffer.h for additional methods
class pxOffscreen: public pxOffscreenNative
{
public:
  
  pxOffscreen();
  virtual ~pxOffscreen();
  
  // This will initialize the offscreen for the given height and width 
  // but will not clear it.
  pxError init(int width, int height);
    
  // This will initialize the offscreen for the given height and width and
  // will clear it with the provided color.
  pxError initWithColor(int width, int height, const pxColor& color);
  
  pxError term();
  
  void swizzleTo(rtPixelFmt fmt);
  
  pxError compressedImageData(char*& data, size_t& dataSize);
  void setCompressedImageData(const char* data, const size_t dataSize);
  pxError moveCompressedImageDataTo(char*& destData, size_t& destDataSize);
  pxError transferCompressedImageDataFrom(char*& srcData, size_t& srcDataSize);
  

private:
  char* mCompressedImageData;
  size_t mCompressedImageDataSize;

};

#endif // PXOFFSCREEN_H
