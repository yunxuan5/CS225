/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <string>
#include "Image.h"

using namespace cs225;

class StickerSheet{
    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator = (const StickerSheet& other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image& sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index);
        Image render() const;

    private:
        unsigned max_;
        Image * base;
        Image ** Images;
        unsigned num_stickers;
        unsigned * Xaxis;
        unsigned * Yaxis;
        void copy(const StickerSheet & other);
        void clear();
};
 
