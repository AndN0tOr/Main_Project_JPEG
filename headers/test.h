#ifndef TEST_H
#define TEST_H

#include "pixel_MCU_image.h"
#include <x86intrin.h>
#include <time.h>
#include "JPEG_Encode.h"
#include "Encoding.h"

void print_block_MCU(ycbcr_pixel block[16][16]);
void print_block_8x8(ycbcr_pixel block[8][8]);
void print_block_16x16_1channel(int16_t block[16][16]);
void print_block_8x8_1channel(int16_t block[8][8]);
void print_DCT_block_8x8(double block[8][8]);
void print_DCT_block_16x16(double block[16][16]);
void Test_Chroma_Downsample_420();
void Test_DCT_8x8();
void Test_Quantization_50();
void Test_Get_Size_Value();
void Test_Encode_DC_DPCM();
void Test_Encode_Block();
void Test_Everything();
void Test_Performance();


#endif /* TEST_H */
