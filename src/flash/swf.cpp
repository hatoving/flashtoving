#include "swf.hpp"
#include "types.hpp"

#include <stdio.h>
#include <psp2/kernel/clib.h>

using namespace flashtoving;

SWF::File::File() {
    sceClibPrintf("[flashtoving] Freeing SWF file\n");
}

SWF::File::~File() {
}

void ReadRecords(SWF::File* swf, FILE* file) {
    while(ftell(file) < swf->fileLength) {
        swf->records.push_back(SWF::Types::RECORD::ReadFromFile(file));
    }
}

SWF::File* SWF::File::Read(const char* path){
    SWF::File* swf = new SWF::File();
    FILE* file = fopen(path, "rb");

    sceClibPrintf("[flashtoving] Reading SWF file from \"%s\"\n", path);

    fread(&swf->signature, 1, 3, file);
    fread(&swf->version, 1, 1, file);
    fread(&swf->fileLength, 1, 4, file);

    sceClibPrintf("[flashtoving] ...with signature (%c%c%c)\n", swf->signature[0], swf->signature[1], swf->signature[2]);

    swf->frameSize = SWF::Types::RECT::ReadFromFile(file);

    uint16_t frameRate;
    fread(&frameRate, 2, 1, file);
    swf->frameRate = (frameRate / 256);

    fread(&swf->frameCount, 2, 1, file);
    sceClibPrintf("[flashtoving] %ix%i ... %ffps ... %i frames\n", swf->frameSize.xMax, swf->frameSize.yMax, swf->frameRate, swf->frameCount);

    ReadRecords(swf, file);
    return swf;
}