#include <psp2/kernel/clib.h>
#include <math.h>

#include "../bit_reader.hpp"
#include "types.hpp"

using namespace flashtoving;

SWF::Types::RECORD SWF::Types::RECORD::ReadFromFile(FILE* file) {
    SWF::Types::RECORD recordHeader;

    uint16_t tagAndLen;
    fread(&tagAndLen, 2, 1, file);

    recordHeader.tagType = tagAndLen >> 6;
    recordHeader.len = tagAndLen & 0x3F;

    if (recordHeader.len >= 0x3F) {
        fread(&recordHeader.len, 4, 1, file);
    }

    recordHeader.offset = ftell(file);

    switch (recordHeader.tagType)
    {
        default:
            sceClibPrintf("[flashtoving::SWF] Unknown tag type, skipping... (%i)\n", recordHeader.tagType);
            fseek(file, recordHeader.len, SEEK_CUR);
            break;
    }

    return recordHeader;
}

SWF::Types::RECT SWF::Types::RECT::ReadFromFile(FILE *file) {
    BitReader reader(file);
    SWF::Types::RECT rect;

    uint8_t nBits = reader.ReadUnsignedBits(5);
    rect.xMin = reader.ReadSignedBits(nBits) * TWIP;
    rect.xMax = reader.ReadSignedBits(nBits) * TWIP;
    rect.yMin = reader.ReadSignedBits(nBits) * TWIP;
    rect.yMax = reader.ReadSignedBits(nBits) * TWIP;

    return rect;
}