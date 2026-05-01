#include<stdio.h>
#include<time.h>
#include<x86intrin.h>

#include "bitmaps.h"
#include "JPEG_Encode.h"
#include "JPEG_steps.h"
#include "pixel_MCU_image.h"
//#include "test.h"


int main(){
    uint64_t start_cycles, end_cycles, total_cycles;
    start_cycles = __rdtsc();
        float startTime = (float)clock() / CLOCKS_PER_SEC;
        rgb_image* image = read_bitmap("test_image.bmp");
        ycbcr_image* ycbcr_image_ori = color_space_transform(image);
        jpeg_encode(ycbcr_image_ori, ycbcr_image_ori->width, ycbcr_image_ori->height);
        float endTime = (float)clock() / CLOCKS_PER_SEC;
        printf("Execution time: %f seconds\n", endTime - startTime);
        free_ycbcr_image(ycbcr_image_ori);
        free_rgb_image(image);
    end_cycles = __rdtsc();
    total_cycles = end_cycles - start_cycles;
    printf("Total CPU cycles: %lu\n", total_cycles);
    return 0;
}