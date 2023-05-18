#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
  class Image
  {
  private:
    Color** data;
    //pointer to an array containing arrays of objects of type Color
    int w_;
    int h_;
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color** get_ptr() const;
    //gets the pointer to the raw data, for faster image manipulation
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
  };
}
#endif
