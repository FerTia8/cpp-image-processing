#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <future>
#include <chrono>
#include <time.h>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
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
                clock_t start = clock();
                invert();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            }
            if (command == "to_gray_scale") {
                clock_t start = clock();
                to_gray_scale();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            } 
            if (command == "replace") {
                clock_t start = clock();
                replace();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            }
            if (command == "fill") {
                clock_t start = clock();
                fill();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            } 
            if (command == "h_mirror") {
                clock_t start = clock();
                h_mirror();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            } 
            if (command == "v_mirror") {
                clock_t start = clock();
                v_mirror();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            } 
            if (command == "add") {
                clock_t start = clock();
                add();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            } 
            if (command == "crop") {
                clock_t start = clock();
                crop();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            }
            if (command == "rotate_left") {
                clock_t start = clock();
                rotate_left();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            }
            if (command == "rotate_right") {
                clock_t start = clock();
                rotate_right();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            }
            if (command == "median_filter") {
                clock_t start = clock();
                median_filter();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            }
            if (command == "xpm2_open") {
                clock_t start = clock();
                xpm2_open();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
                continue;
            }
            if (command == "xpm2_save") {
                clock_t start = clock();
                xpm2_save();
                clock_t end = clock();
                double execution_time = double(end - start) / CLOCKS_PER_SEC;
                std::cout << execution_time << endl;
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
    void Script::blank() {
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
    void invert_thread(int x, int y, int mx, int my, Image* image) {
        for (int ix = x; ix < mx; ix++) {
        for (int iy = y; iy < my; iy++) {
            Color& pixel = image->at(ix, iy);
            pixel.red() = 255 - pixel.red();
            pixel.green() = 255 - pixel.green();
            pixel.blue() = 255 - pixel.blue();
        }}
    }
    void Script::invert() {
        //inverts the colors of the current image

        //splits the image in 4 and inverts them simultaneously
        std::future<void> ft1 = std::async(invert_thread, 0, 0, image->width() / 2, image->height() / 2, image);
        std::future<void> ft2 = std::async(invert_thread, image->width() / 2, 0, image->width(), image->height() / 2, image);
        std::future<void> ft3 = std::async(invert_thread, 0, image->height() / 2, image->width() / 2, image->height(), image);
        std::future<void> ft4 = std::async(invert_thread, image->width() / 2, image->height() / 2, image->width(), image->height(), image);

        //wait for all the threads to finish
        ft1.wait();
        ft2.wait();
        ft3.wait();
        ft4.wait();
    }
    void Script::to_gray_scale() {
        //gray scales the current image

        for (int x = 0; x < image->width(); x++) {
        for (int y = 0; y < image->height(); y++) {
            Color& pixel = image->at(x, y);
            rgb_value v = (pixel.red() + pixel.green() + pixel.blue()) / 3;
            pixel = {v, v, v};
        }}
    }
    void Script::replace() {
        //replaces the color (r1, g1, b1) for (r2, g2, b2)

        int r1, g1, b1, r2, g2, b2;
        input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;

        for (int x = 0; x < image->width(); x++) {
        for (int y = 0; y < image->height(); y++) {
            Color& pixel = image->at(x, y);

            if (pixel.red() == r1 && pixel.green() == g1 && pixel.blue() == b1) {
                pixel.red() = r2;
                pixel.green() = g2;
                pixel.blue() = b2;
            }
        }}
    }
    void Script::fill() {
        //fills the given area with a specified color

        int x, y, w, h, r, g, b;
        input >> x >> y >> w >> h >> r >> g >> b;
        const Color fill_ {(rgb_value) r, (rgb_value) g, (rgb_value) b};
        
        for (int ix = x; ix < x + w; ix++) {
        for (int iy = y; iy < y + h; iy++) {
            image->at(ix, iy) = fill_;
        }}
    }
    void Script::h_mirror() {
        //mirrors horizontally

        Color** raw_data = image->get_ptr();

        for (int ix = 0; ix < image->width() / 2; ix++) {
            Color* temp {raw_data[ix]};

            raw_data[ix] = raw_data[image->width() - 1 - ix];
            raw_data[image->width() - 1 - ix] = temp;
        }
    }
    void Script::v_mirror() {
        //mirrors vertically

        for (int ix = 0; ix < image->width(); ix++) {
        for (int iy = 0; iy < image->height() / 2; iy++) {
            Color& left = image->at(ix, iy);
            Color& right = image->at(ix, image->height() - 1 - iy);
            Color temp {left};

            left = right;
            right = temp;
        }}
    }
    void Script::add() {
        //adds an image to the current loaded image given the upper left point

        std::string filename;
        int x, y, r, g, b;
        input >> filename >> r >> g >> b >> x >> y;
        Image* loaded = loadFromPNG(filename);

        for (int ix = 0; ix < loaded->width(); ix++) {
        for (int iy = 0; iy < loaded->height(); iy++) {
            const Color pixel_from = loaded->at(ix, iy);

            if (pixel_from.red() == r && pixel_from.green() == g && pixel_from.blue() == b) continue;
            else image->at(ix + x, iy + y) = pixel_from;
        }}

        delete loaded;
    }
    void Script::crop() {
        //crops the image given the upper left corner and the dimensions of the cropped image

        int x, y, w, h;
        input >> x >> y >> w >> h;
        Image* cropped_image = new Image(w, h);

        if (x + w > image->width() || y + h > image->height()) throw std::out_of_range("Croping region out of range!");

        Color** raw_data_o = image->get_ptr();
        Color** raw_data_c = cropped_image->get_ptr();

        for (int ix = x; ix < x + w; ix++) {
            std::copy(raw_data_o[ix] + y, raw_data_o[ix] + y + h, raw_data_c[ix - x]);
        }

        delete image;
        image = cropped_image;
    }
    void Script::rotate_left() {
        //rotates the image left

        Image* rotated_image = new Image(image->height(), image->width());

        for (int ix = 0; ix < image->width(); ix++) {
        for (int iy = 0; iy < image->height(); iy++) {
            rotated_image->at(iy, rotated_image->height() - 1 - ix) = image->at(ix, iy);
        }}

        delete image;
        image = rotated_image;
    }
    void Script::rotate_right() {
        //rotates the image right

        Image* rotated_image = new Image(image->height(), image->width());

        for (int ix = 0; ix < image->width(); ix++) {
        for (int iy = 0; iy < image->height(); iy++) {
            rotated_image->at(rotated_image->width() - 1 - iy, ix) = image->at(ix, iy);
        }}

        delete image;
        image = rotated_image;
    }
    rgb_value median(vector<rgb_value> v) {
        //median of a vector

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
    void filter_thread(int x, int y, int ws, int mx, int my, Image* original, Image* img) {
        //iterate through every point inside the given boundaries
        for (int ix = x; ix < mx; ix++) {
        for (int iy = y; iy < my; iy++) {
            vector<rgb_value> red_values, green_values, blue_values;
            rgb_value r_, g_, b_;
                
            //iterate through every (valid) neighborhood point
            for (int wx = - ws / 2; wx <= ws / 2; wx++) {
            if (ix + wx < 0 || ix + wx >= original->width()) continue;

            for (int wy = - ws / 2; wy <= ws / 2; wy++) {
            if (iy + wy < 0 || iy + wy >= original->height()) continue;
                red_values.push_back(original->at(ix + wx, iy + wy) .red());
                green_values.push_back(original->at(ix + wx, iy + wy).green());
                blue_values.push_back(original->at(ix + wx, iy + wy).blue());
            }}

            r_ = median(red_values);
            g_ = median(green_values);
            b_ = median(blue_values);

            //store the median value in a new image
            img->at(ix, iy) = {r_, g_, b_};
        }}
    }
    void Script::median_filter() {
        //aplies a median filter to the whole image given a specific window size

        int ws;
        input >> ws;
        Image* filtered_image = new Image(image->width(), image->height());

        //splits the image in 4 and applies the filter to them simultaneously
        std::future<void> ft1 = std::async(filter_thread, 0, 0, ws, image->width() / 2, image->height() / 2, image, filtered_image); //first quadrant
        std::future<void> ft2 = std::async(filter_thread, image->width() / 2, 0, ws, image->width(), image->height() / 2, image, filtered_image); //second quadrant
        std::future<void> ft3 = std::async(filter_thread, 0, image->height() / 2, ws, image->width() / 2, image->height(), image, filtered_image); //third quadran
        std::future<void> ft4 = std::async(filter_thread, image->width() / 2, image->height() / 2, ws, image->width(), image->height(), image, filtered_image); //forth quadrant

        //wait for all the threads to finish
        ft1.wait();
        ft2.wait();
        ft3.wait();
        ft4.wait();

        delete image;
        image = filtered_image;
    }
    void Script::xpm2_open() {
        //loads a xmp2 image

        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromXPM2(filename);
    }
    void Script::xpm2_save() {
        //saves the current image in the xpm2 format

        string filename;
        input >> filename;
        saveToXPM2(filename, image);
    }
}