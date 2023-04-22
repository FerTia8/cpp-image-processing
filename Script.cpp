#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    rgb_value median(vector<rgb_value> v) {
        int middle = v.size() / 2;
        
        std::sort(v.begin(), v.end());

        if (v.size() % 2 == 0) {
            int left = v[middle - 1];
            int right = v[middle];
            return (left + right) / 2;
        } 
        else {
            return v[middle];
        }
    }
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 
            // TODO ...
            if (command == "invert") {
                invert();
                continue;
            }
            if (command == "to_gray_scale") {
                to_gray_scale();
                continue;
            } 
            if (command == "replace") {
                int r1, g1, b1, r2, g2, b2;
                input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
                replace(r1, g1, b1, r2, g2, b2);
                continue;
            }
            if (command == "fill") {
                int x, y, w, h, r, g, b;
                input >> x >> y >> w >> h >> r >> g >> b;
                fill(x, y, w, h, r, g, b);
                continue;
            } 
            if (command == "h_mirror") {
                h_mirror();
                continue;
            } 
            if (command == "v_mirror") {
                v_mirror();
                continue;
            } 
            if (command == "add") {
                std::string filename;
                int x, y, r, g, b;
                input >> filename >> r >> g >> b >> x >> y;
                add(filename, x, y, r, g, b);
                continue;
            } 
            if (command == "crop") {
                int x, y, w, h;
                input >> x >> y >> w >> h;
                crop(x, y, w, h);
                continue;
            }
            if (command == "rotate_left") {
                rotate_left();
                continue;
            }
            if (command == "rotate_right") {
                rotate_right();
                continue;
            }
            if (command == "median_filter") {
                int ws;
                input >> ws;
                median_filter(ws);
                continue;
            }  

        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() { //works
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::invert() { //works
        // ...
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y);
                pixel.red() = 255 - pixel.red();
                pixel.green() = 255 - pixel.green();
                pixel.blue() = 255 - pixel.blue();
            }
        }
    }

    void Script::to_gray_scale() { //works
        //...
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y);
                rgb_value v = (pixel.red() + pixel.green() + pixel.blue()) / 3;
                pixel = {v, v, v};
            }
        }
    }

    void Script::replace(int r1, int g1, int b1, int r2, int g2, int b2) { //works
        //...
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y);
                if (pixel.red() == r1 && pixel.green() == g1 && pixel.blue() == b1) {
                    pixel.red() = r2;
                    pixel.green() = g2;
                    pixel.blue() = b2;
                }
            }
        }
    }

    void Script::fill(int x, int y, int w, int h, int r, int g, int b) { //works
        //...
        const Color fill_ {(rgb_value) r, (rgb_value) g, (rgb_value) b};
        for (int ix = x; ix < x + w; ix++) {
            for (int iy = y; iy < y + h; iy++) {
                image->at(ix, iy) = fill_;
            }
        }
    }

    void Script::h_mirror() { //works
        //...
        for (int ix = 0; ix < image->width() / 2; ix++) {
            for (int iy = 0; iy < image->height(); iy++) {
                Color& left = image->at(ix, iy);
                Color& right = image->at(image->width() - 1 - ix, iy);
                Color temp {left};

                left = right;
                right = temp;
            }
        }
    }

    void Script::v_mirror() { //works
        //...
        for (int ix = 0; ix < image->width(); ix++) {
            for (int iy = 0; iy < image->height() / 2; iy++) {
                Color& left = image->at(ix, iy);
                Color& right = image->at(ix, image->height() - 1 - iy);
                Color temp {left};

                left = right;
                right = temp;
            }
        }
    }

    void Script::add(string& filename, int x, int y, int r, int g, int b) { //works
        //...
        Image* im = loadFromPNG(filename);

        for (int ix = x; ix < im->width() + x; ix++) {
            for (int iy = y; iy < im->height() + y; iy++) {
                const Color pixel_from = im->at(ix - x, iy - y);

                if (pixel_from.red() == r && pixel_from.green() == g && pixel_from.blue() == b) continue;
                else {
                    image->at(ix, iy) = pixel_from;
                }
            }
        }

        delete im;
    }

    void Script::crop(int x, int y, int w, int h) { //works
        //...
        Image* cropped_image = new Image(w, h);

        for (int ix = x; ix < x + w; ix++) {
            for (int iy = y; iy < y + h; iy++) {
                cropped_image->at(ix - x, iy - y) = image->at(ix, iy);
            }
        }

        delete image;
        image = cropped_image;
    }

    void Script::rotate_left() { //works
        //...
        Image* rotated_image = new Image(image->height(), image->width());

        for (int ix = 0; ix < image->width(); ix++) {
            for (int iy = 0; iy < image->height(); iy++) {
                rotated_image->at(iy, rotated_image->height() - 1 - ix) = image->at(ix, iy);
            }
        }

        delete image;
        image = rotated_image;
    }

    void Script::rotate_right() { //works
        //...
        Image* rotated_image = new Image(image->height(), image->width());

        for (int ix = 0; ix < image->width(); ix++) {
            for (int iy = 0; iy < image->height(); iy++) {
                rotated_image->at(rotated_image->width() - 1 - iy, ix) = image->at(ix, iy);
            }
        }

        delete image;
        image = rotated_image;
    }

    void Script::median_filter(int ws) { //works
        //...
        Image* filtered_image = new Image(image->width(), image->height());

        for (int ix = 0; ix < image->width(); ix++) {
            for (int iy = 0; iy < image->height(); iy++) {
                vector<rgb_value> red_values, green_values, blue_values;
                rgb_value r_, g_, b_;
                
                for (int wx = - ws / 2; wx <= ws / 2; wx++) {
                    if (ix + wx < 0 || ix + wx >= image->width()) continue;
                    for (int wy = - ws / 2; wy <= ws / 2; wy++) {
                        if (iy + wy < 0 || iy + wy >= image->height()) continue;
                        red_values.push_back(image->at(ix + wx, iy + wy).red());
                        green_values.push_back(image->at(ix + wx, iy + wy).green());
                        blue_values.push_back(image->at(ix + wx, iy + wy).blue());
                    }
                }

                r_ = median(red_values);
                g_ = median(green_values);
                b_ = median(blue_values);

                filtered_image->at(ix, iy) = {r_, g_, b_};
            }
        }

        delete image;
        image = filtered_image;
    }
}
