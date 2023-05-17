#include "Color.hpp"

namespace prog {
    Color::Color() {
        red_ = 0; green_ = 0; blue_ = 0;
    }
    Color::Color(const Color& other) {
        red_ = other.red_; green_ = other.green_; blue_ = other.blue_;
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) : red_(red), green_(green), blue_(blue) {};
    
    rgb_value Color::red() const {
        return red_;
    }
    rgb_value Color::green() const {
        return green_;
    }
    rgb_value Color::blue() const {
        return blue_;
    }

    rgb_value& Color::red()  {
        return red_;
    }
    rgb_value& Color::green()  {
      return green_;
    }
    rgb_value& Color::blue()  {
      return blue_;
    }
}
