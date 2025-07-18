#pragma once

#include <stdio.h>
#include <stdint.h>
#include <vector>

#include "tag.hpp"

// 1/20th of a logical pixel
constexpr float TWIP = (1.0f / 20.0f);

namespace flashtoving::SWF {
    class Types {
        public:
            typedef struct RGBA {
                uint8_t r, g, b, a;
            } RGBA;

            typedef struct RECORD {
                uint16_t tagType;
                uint32_t len;
                long offset;

                SWF::Tag tag;
                static RECORD ReadFromFile(FILE* file);
            };
            
            typedef struct RECT {
                int xMin, yMin, xMax, yMax;
                static RECT ReadFromFile(FILE* file);
            } RECT;

            typedef struct MATRIX {
                uint8_t hasScale;
                float scaleX, scaleY;

                uint8_t hasRot;
                float rotX, rotY;

                float translateX, translateY; // originally in twips
            } MATRIX;

#pragma region Shape structs
            typedef struct FILLSTYLE {
                uint8_t styleType;
                RGBA color;

                MATRIX gradientMatrix;
                //FOCALGRADIENT gradient;

                uint16_t bitmapIndex;
                MATRIX bitmapMatrix;
            } FILLSTYLE;

            typedef struct FILLSTYLEARRAY {
                uint8_t count;
                uint16_t extendedCount;
                std::vector<FILLSTYLE> fillStyles;
            } FILLSTYLEARRAY;

            typedef struct LINESTYLE {
                float width;
                RGBA color;
            } LINESTYLE;

            typedef struct LINESTYLEARRAY {
                uint8_t count;
                uint16_t extendedCount;
                std::vector<FILLSTYLE> fillStyles;
            } LINESTYLEARRAY;

            typedef struct SHAPEWITHSTYLE {
                FILLSTYLEARRAY fillStyles;
                LINESTYLEARRAY lineStyles;
            } SHAPEWITHSTYLE;

#pragma endregion
    };
}