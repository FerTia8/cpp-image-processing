#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <iomanip>
#include <algorithm>
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

    std::string color_to_hex(Color color) {
        std::stringstream stream;

        stream << '#' << std::hex << std::setw(2) << std::setfill('0') << (int) color.red();
        stream << std::hex << std::setw(2) << std::setfill('0') << (int) color.green();
        stream << std::hex << std::setw(2) << std::setfill('0') << (int) color.blue();

        std::string result = stream.str();
        std::transform(result.begin(), result.end(), result.begin(), toupper);

        return result;
    }

    Image* loadFromXPM2(const std::string& file) {
        std::ifstream in {file};
        std::string line;
        std::map<char, Color> color_map;
        int height {0}, width {0}, number_of_colors {0}, char_per_color {0};

        std::getline(in, line, '\n'); //exclude the first line ("! XPM2")
        std::getline(in, line, '\n');
        std::istringstream in_line {line};

        in_line >> width >> height >> number_of_colors >> char_per_color;

        //extract each color from a line and map it to a char
        for (int i = 0; i < number_of_colors; i++) {
            std::getline(in, line, '\n');
            char c = line[0];
            std::string color_str = line.substr(4, 7);
            Color color = hex_to_color(color_str);

            color_map[c] = color;
        }

        //create a new image with the given proportions
        Image* new_image = new Image(width, height);

        //map each char to a point using
        for (int iy = 0; iy < height; iy++) {
            std::getline(in, line, '\n');
              
            for (int ix = 0; ix < width; ix++) new_image->at(ix, iy) = color_map[line[ix]];
        }

        return new_image;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        std::ofstream out {file};
        std::map<std::string, char> color_map;
        std::unordered_set<std::string> colors;
        const std::string ascii_str = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";

        for (int ix = 0; ix < image->width(); ix++) {
        for (int iy = 0; iy < image->height(); iy++) {
            colors.insert(color_to_hex(image->at(ix, iy)));
        }}
        
        out << "! XPM2\n";
        out << image->width() << ' ' << image->height() << ' ' << colors.size() << ' ' << '1' << '\n';

        int ascii_counter {0};
        for (auto color : colors) {
            if (ascii_counter == (int) ascii_str.size()) throw std::out_of_range("string out of range");
            out << ascii_str[ascii_counter] << ' ' << 'c' << ' ' << color << '\n';
            color_map[color] = ascii_str[ascii_counter];
            ascii_counter++;
        }

        for (int iy = 0; iy < image->height(); iy++) {
        for (int ix = 0; ix < image->width(); ix++) {
            out << color_map[color_to_hex(image->at(ix, iy))];
        }
            out << '\n';
        }
    }
}
