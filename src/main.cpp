#include <stdio.h>
#include "flash/swf.hpp"

using namespace flashtoving;

int main() {
    printf("[flashtoving] Welcome!\n");

    SWF::File* swf = SWF::File::Read("ux0:data/flash/test.swf");
    delete swf;
    return 0;
}