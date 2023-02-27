#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;


void StickerSheet::copy(const StickerSheet & other){
    max_ = other.max_;
    base = new Image(*(other.base));
    num_stickers = other.num_stickers;
    Images = new Image* [max_];
    Xaxis = new unsigned[max_];
    Yaxis = new unsigned[max_];
    for(unsigned i = 0; i < num_stickers; i++){
        Images[i] = new Image();
        * (Images[i]) = *(other.Images[i]);
        Xaxis[i] = other.Xaxis[i];
        Yaxis[i] = other.Yaxis[i];
    }
}

void StickerSheet::clear(){
    for(unsigned i = 0; i < num_stickers; i++){
        delete Images[i];
        Images[i] = NULL;
    }
    delete base;
    delete[] Images;
    delete[] Xaxis;
    delete[] Yaxis;
}

StickerSheet::StickerSheet(const Image& picture, unsigned max){
    max_ = max;
    num_stickers = 0;
    Images = new Image * [max_];
    Xaxis = new unsigned[max_];
    Yaxis = new unsigned[max_];
    base = new Image(picture);
    Xaxis[0] = 0;
    Yaxis[0] = 0;
}

StickerSheet::~StickerSheet(){
    clear();
}

StickerSheet::StickerSheet(const StickerSheet& other){
    copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
    if(this != &other){
        clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    Image ** temp_images = new Image * [max_];
    unsigned * temp_Xaxis = new unsigned [num_stickers];
    unsigned * temp_Yaxis = new unsigned [num_stickers];
    for(unsigned i = 0; i < num_stickers; i++){
        temp_images[i] = Images[i];
        temp_Xaxis[i] = Xaxis[i];
        temp_Yaxis[i] = Yaxis[i];
    }
    delete[] Images;
    delete[] Xaxis;
    delete[] Yaxis;
    Images = new Image * [max];
    Xaxis = new unsigned[max];
    Yaxis = new unsigned[max];

    if(max < num_stickers){
        for(unsigned i = max; i < num_stickers; i++){
            delete temp_images[i];
            temp_images[i] = NULL;
        }
        num_stickers = max;
        for(unsigned i = 0; i < num_stickers; i++){
            Images[i] = temp_images[i];
            Xaxis[i] = temp_Xaxis[i];
            Yaxis[i] = temp_Yaxis[i];
        }
    }
    else{
        for(unsigned i = 0; i < num_stickers; i++){
            Images[i] = temp_images[i];
            Xaxis[i] = temp_Xaxis[i];
            Yaxis[i] = temp_Yaxis[i];
        }
    }
    max_ = max;
    delete[] temp_images;
    delete[] temp_Xaxis;
    delete[] temp_Yaxis;
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y){
    for(unsigned i = 0; i < max_; i++){
        if(i == num_stickers){
            Images[i] = new Image(sticker);
            Xaxis[i] = x;
            Yaxis[i] = y;
            num_stickers ++;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index < num_stickers){
        Xaxis[index] = x;
        Yaxis[index] = y;
        return true;
    }
    return false;
}

void StickerSheet::removeSticker(unsigned index){
    delete Images[index];
    for(unsigned i = index; i < max_ -1; i++){
        Images[i] = Images[i + 1];
        Xaxis[i] = Xaxis[i + 1];
        Yaxis[i] = Yaxis[i + 1];
    }
    num_stickers --;
    Images[max_ - 1] = NULL;
    Xaxis[max_ - 1] = 0;
    Yaxis[max_ - 1] = 0;
}

Image * StickerSheet::getSticker(unsigned index){
    if(index >= num_stickers){
        return NULL;
    }
    return Images[index];
}

Image StickerSheet::render() const{
    Image result(*base);
    for(unsigned i = 0; i < num_stickers; i++){
        unsigned curWidth = Images[i]->width();
        unsigned curHeight = Images[i]->height();

        if((curWidth + Xaxis[i]) > result.width()){
            result.resize(curWidth + Xaxis[i], result.height());
        }

        if(curHeight + Yaxis[i] > result.height()){
            result.resize(result.width(), curHeight + Yaxis[i]);
        }

        for(unsigned j = 0; j < curWidth; j++){
            for(unsigned k = 0; k < curHeight; k++){
                HSLAPixel & result_pixel = result.getPixel(j + Xaxis[i], k + Yaxis[i]);
				HSLAPixel & image_pixel = Images[i]->getPixel(j, k);
                if(image_pixel.a != 0){
                    result_pixel = image_pixel;
                }
            }
        }
    }
    return result;
}