#ifndef CART_H
#define CART_H
#include <st_ty.h>

class Cartridge
{
    public:
        CartridgeHeader *header;
        

        Cartridge(const char* filename);
        ~Cartridge();
        void loadROM(const char* filename);
};

class CartridgeHeader
{
    public:
        char title[16];
        u8 cgb_flag;
        u8 new_licensee_code[2];
        u8 sgb_flag;
        u8 cartridge_type;
        u8 rom_size;
        u8 ram_size;
        u8 destination_code;
        u8 old_licensee_code;
        u8 mask_rom_version_number;
        u8 header_checksum;
        char global_checksum[2];

        CartridgeHeader(u8* data);
};


#endif