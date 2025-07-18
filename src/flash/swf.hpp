#pragma once

#include <stdint.h>
#include <vector>

#include "types.hpp"

namespace flashtoving::SWF {
    class File {
        public:
            uint8_t version;
            char signature[3];

            uint32_t fileLength;
            float frameRate;

            SWF::Types::RECT frameSize;
            uint16_t frameCount;

            float frameDelay;
            int recordCount;

            std::vector<Types::RECORD> records;

            File();
            ~File();

            static File* Read(const char* path);
    };
}