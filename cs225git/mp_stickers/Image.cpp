#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

void Image::lighten(){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & cur_pixel = getPixel(x, y);
			cur_pixel.l += 0.1;
			if (cur_pixel.l > 1.0) cur_pixel.l = 1.0;
			if (cur_pixel.l < 0.0) cur_pixel.l = 0.0;
        }
    }
}

void Image::lighten(double amount){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if(pixel.l >= 0 && pixel.l <= 1){
                pixel.l += amount;
            }
        }
    }
}

void Image::darken(){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if(pixel.l >= 0 && pixel.l <= 1){
                pixel.l -= 0.1;
            }
        }
    }
}

void Image::darken(double amount){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & cur_pixel = getPixel(x, y);
			cur_pixel.l -= amount;
			if (cur_pixel.l < 0.0) cur_pixel.l = 0.0;
			if (cur_pixel.l > 1.0) cur_pixel.l = 1.0;
        }
    }
}

void Image::saturate(){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if(pixel.s >= 0 && pixel.s <= 1){
                pixel.s += 0.1;
            }
        }
    }
}

void Image::saturate(double amount){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if(pixel.s >= 0 && pixel.s <= 1){
                pixel.s += amount;
            }
        }
    }
}

void Image::desaturate(){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if(pixel.s >= 0 && pixel.s <= 1){
                pixel.s -= 0.1;
            }
        }
    }
}

void Image::desaturate(double amount){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if(pixel.s >= 0 && pixel.s <= 1){
                pixel.s -= amount;
            }
        }
    }
}

void Image::grayscale(){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            double hue = pixel.h;
            double result = hue + degrees;
            if(result >= 0 && result <= 360){
                pixel.h = result;
            }
            if(result < 0){
                pixel.h = result + 360;
            }
            if(result > 360){
                pixel.h = result - 360;
            }
        }
    }
}

void Image::illinify(){
    unsigned image_width = width();
    unsigned image_height = height();
    for (unsigned x = 0; x < image_width; x++) {
        for (unsigned y = 0; y < image_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            double hue = pixel.h;
            if((hue > 293.5 && hue < 360) || (hue >= 0 && hue <= 113.5)){
                pixel.h = 11;
            }
            else{
                pixel.h = 216;
            }
        }
    }
}

void Image::scale(double factor){
    unsigned new_width = factor * width();
    unsigned new_height = factor * height();
    Image *copyImage = new Image();
    *copyImage = *this;
    resize(new_width, new_height);
    for (unsigned x = 0; x < new_width; x++) {
        for (unsigned y = 0; y < new_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            HSLAPixel & copy_pixel = copyImage->getPixel(x / factor, y / factor);
            pixel = copy_pixel;
        }
    }
}

void Image::scale(unsigned w, unsigned h){
    double width_ratio = (double) w/width();
    double height_ratio = (double) h/height();
    double factor = std::min(width_ratio, height_ratio);
    scale(factor);
}