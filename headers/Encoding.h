#ifndef ENCODING_H
#define ENCODING_H

#include <stdint.h>
#include <stdio.h>
#include "bitmaps.h"
#include "pixel_MCU_image.h"


typedef struct{
    int16_t value;
    int8_t size;
}size_value;

typedef struct{
    uint16_t code;
    uint8_t length;
}huffman_code;
extern const uint8_t STD_DC_LUMA_BITS[16];
extern const uint8_t STD_DC_LUMA_VALS[12];
extern const uint8_t STD_AC_LUMA_BITS[16];
extern const uint8_t STD_AC_LUMA_VALS[162];
extern const uint8_t STD_DC_CHROMA_BITS[16];
extern const uint8_t STD_DC_CHROMA_VALS[12];
extern const uint8_t STD_AC_CHROMA_BITS[16];
extern const uint8_t STD_AC_CHROMA_VALS[162];
extern huffman_code HT_DC_LUMA[256];
extern huffman_code HT_AC_LUMA[256];
extern huffman_code HT_DC_CHROMA[256];
extern huffman_code HT_AC_CHROMA[256];
size_value get_size_value(int16_t value);
size_value encode_dc_dpcm(int16_t current_dc, int16_t previous_dc);
void generate_huffman_table(const uint8_t* bits, const uint8_t* vals, huffman_code* table);
void init_jpeg_encoding();
void Encode_block (int16_t block[64], int16_t* previous_dc, void* dc_huffman_table, void* ac_huffman_table);
void MCU_Encode(int16_t zigzag_array[384], int16_t *previous_dc_y, int16_t *previous_dc_cb, int16_t *previous_dc_cr);
void Write_Physical_Bytes(uint8_t byte);
void Write_Huffman_bits(uint8_t symbol_byte, uint16_t value_bits, void* huffman_table);
void Print_Huffman_bits(uint8_t symbol_byte, uint16_t value_bits, void* huffman_table);
void Print_Physical_Bytes(uint8_t byte);
void Print_bits(uint32_t bits, uint8_t num_bits);
void Put_bits(uint32_t bits, uint8_t num_bits);
void Flush_bits();
void open_jpeg_file(char*);
void close_jpeg_file();


#endif /* ENCODING_H */