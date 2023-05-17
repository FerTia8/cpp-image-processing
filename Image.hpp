#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
  class Image
  {
  private:
    Color** data;
    int w_;
    int h_;
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color** get_ptr() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
  };
}
#endif
