#include <stdexcept>
#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    w_ = w;
    h_ = h;
    data = new Color*[w];

    for (int iw = 0; iw < w; iw++) {
      data[iw] = new Color[h];
      for (int ih = 0; ih < h; ih++) data[iw][ih] = fill;
    }
  }
  Image::~Image()
  {
    for (int i = 0; i < w_; i++) {
      delete[] data[i];
    }

    delete[] data;
  }
  int Image::width() const
  {
    return w_;
  }
  int Image::height() const
  {
    return h_;
  }

  Color** Image::get_ptr() const 
  {
    return data;
  }

  Color& Image::at(int x, int y)
  {
    if (x < 0 || y < 0 || x >= w_ || y >= h_) throw std::out_of_range("Value out of range!");

    return data[x][y];
  }

  const Color& Image::at(int x, int y) const
  {
    if (x < 0 || y < 0 || x >= w_ || y >= h_) throw std::out_of_range("Value out of range!");

    return data[x][y];
  }
}
