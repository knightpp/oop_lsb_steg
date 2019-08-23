//
// Created by daniel on 23/08/19.
//
#ifndef STEGANOGRAPHY_PIXELBITITERATOR_H
#define STEGANOGRAPHY_PIXELBITITERATOR_H

#include <vector>
#include <memory>
#include "PixelsData.h"
#include <iostream>

class PixelBitIterator{
private:
  //  PixelsData* col;
    std::vector<Pixel>* pixels;
    std::vector<Pixel>::iterator pixelIterator;
    size_t index;
    size_t pos;
    size_t size;
public:
    explicit PixelBitIterator(PixelsData* col) : index(0), pos(0) {
        pixels = col->pixels;
        pixelIterator = pixels->begin();
        size = Pixel::bits * pixels->size();
    }

    explicit PixelBitIterator(std::shared_ptr<PixelsData> col) : index(0), pos(0) {
        pixels = col->pixels;
        pixelIterator = pixels->begin();
        size = Pixel::bits * pixels->size();
    }

    PixelBitIterator& operator++(){
        if(index < 2){
            ++index;
        }else{
            index = 0;
            ++pixelIterator;
        }
        ++pos;
        return *this;
    }

    bool hasMore() const{
        return pos != size;
    }

    byte getNextByte(){
        std::bitset<8> bitset;
        for(int i = 0; i < 8; ++i){
            bitset[i] = getNextBit();
        }
        return static_cast<byte>(bitset.to_ulong());
    }

    bool getNextBit(){
        byte rez = (*pixelIterator)[index];
        this->operator++();
        return (rez & 0x1);
    }

    void pushBit(byte b){
        byte& ref = (*pixelIterator)[index];
        ref = (ref & ~1UL) | (b & 1UL);
        this->operator++();
    }
};

#endif //STEGANOGRAPHY_PIXELBITITERATOR_H
