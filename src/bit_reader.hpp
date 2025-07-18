#pragma once

#include <stdio.h>
#include <stdint.h>

class BitReader {
    public:
        explicit BitReader(FILE *file);

        uint32_t ReadUnsignedBits(int numBits);
        int32_t ReadSignedBits(int numBits);

        void Reset();

    private:
        FILE *file;
        uint8_t bitBuffer = 0;
        int bitLen = 0;
};
