#include <stdexcept>
#include "bit_reader.hpp"

BitReader::BitReader(FILE *file) : file(file), bitBuffer(0), bitLen(0)
{
    if (!file)
    {
        throw std::runtime_error("BitReader: FILE* is null");
    }
}

void BitReader::Reset()
{
    bitBuffer = 0;
    bitLen = 0;
}

uint32_t BitReader::ReadUnsignedBits(int numBits)
{
    uint32_t value = 0;

    while (numBits > 0)
    {
        if (bitLen == 0)
        {
            int byte = fgetc(file);
            if (byte == EOF)
            {
                throw std::runtime_error("BitReader: Unexpected EOF");
            }
            bitBuffer = static_cast<uint8_t>(byte);
            bitLen = 8;
        }

        int takeBits = (numBits < bitLen) ? numBits : bitLen;
        uint8_t shift = bitLen - takeBits;
        uint8_t mask = (1 << takeBits) - 1;

        value = (value << takeBits) | ((bitBuffer >> shift) & mask);

        bitLen -= takeBits;
        numBits -= takeBits;
    }

    return value;
}

int32_t BitReader::ReadSignedBits(int numBits)
{
    uint32_t uvalue = ReadUnsignedBits(numBits);

    // Sign-extend manually
    if (uvalue & (1 << (numBits - 1)))
    {
        uvalue |= ~((1 << numBits) - 1); // extend sign bit to full int
    }

    return static_cast<int32_t>(uvalue);
}
