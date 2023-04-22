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
      delete data[i];
    }

    delete data;
  }
  int Image::width() const
  {
    return w_;
  }
  int Image::height() const
  {
    return h_;
  }

  Color& Image::at(int x, int y)
  {
    return data[x][y];
  }

  const Color& Image::at(int x, int y) const
  {
    return data[x][y];
  }
}
