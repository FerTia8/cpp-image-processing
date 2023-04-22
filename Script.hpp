#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();
    void invert();
    void to_gray_scale();
    void replace(int r1, int g1, int b1, int r2, int g2, int b2);
    void fill(int x, int y, int w, int h, int r, int g, int b);
    void h_mirror();
    void v_mirror();
    void add(std::string& filename, int x, int y, int r, int g, int b);
    void crop(int x, int y, int w, int h);
    void rotate_left();
    void rotate_right();
    void median_filter(int ws);
    void xpm2_open(std::string& filename);
    void xpm2_save(std::string& filename);
  };
}
#endif
