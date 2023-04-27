#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include "XPM2.hpp"

namespace prog {
    int char_to_int(char& c) {
        char c_upper = toupper(c);
        if (c_upper >= '0' && c_upper <= '9') return c_upper - '0';
        else if (c_upper >= 'A' && c_upper <= 'F') return c_upper - 'A' + 10;
        else return -1;
    }

    Color hex_to_color(std::string str) {
        Color result;

        result.red() = char_to_int(str[1]) * 16 + char_to_int(str[2]);
        result.green() = char_to_int(str[3]) * 16 + char_to_int(str[4]);
        result.blue() = char_to_int(str[5]) * 16 + char_to_int(str[6]);

        return result;
    }

    Image* loadFromXPM2(const std::string& file) {
        std::ifstream in {file};
        std::string line;
        std::map<char, Color> color_map;
        int height {0}, width {0}, number_of_colors {0}, char_per_color {0};

        std::getline(in, line, '\n');
        std::getline(in, line, '\n');
        std::istringstream in_line {line};

        in_line >> width >> height >> number_of_colors >> char_per_color;

        for (int i = 0; i < number_of_colors; i++) {
            std::getline(in, line, '\n');
            std::istringstream in_line {line};
            char c;
            char c_type;
            std::string color_str;
            Color color;

            in_line >> c >> c_type >> color_str;

            color = hex_to_color(color_str);

            color_map[c] = color;
        }

        Image* new_image = new Image(width, height);

        for (int iy = 0; iy < height; iy++) {
            std::getline(in, line, '\n');
              
            for (int ix = 0; ix < width; ix++) new_image->at(ix, iy) = color_map[line[ix]];
        }

        return new_image;
    }

    void saveToXPM2(const std::string& file, const Image* image) {

    }
}
