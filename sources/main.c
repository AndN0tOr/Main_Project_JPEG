#include<stdio.h>
#include<time.h>

#include "../headers/bitmaps.h"
#include "../headers/JPEG_Encode.h"
#include "../headers/JPEG_steps.h"
#include "../headers/pixel_MCU_image.h"
#include "../headers/test.h"


int main(){
    // uint64_t start_cycles, end_cycles, total_cycles;
    // start_cycles = __rdtsc();
    //     float startTime = (float)clock() / CLOCKS_PER_SEC;
    //     rgb_image* image = read_bitmap("test_image.bmp");
    //     ycbcr_image* ycbcr_image_ori = color_space_transform(image);
    //     jpeg_encode(ycbcr_image_ori, ycbcr_image_ori->width, ycbcr_image_ori->height);
    //     float endTime = (float)clock() / CLOCKS_PER_SEC;
    //     printf("Execution time: %f seconds\n", endTime - startTime);
    //     free_rgb_image(image);
    // end_cycles = __rdtsc();
    // total_cycles = end_cycles - start_cycles;
    // printf("Total CPU cycles: %lu\n", total_cycles);
    // printf("Average CPU cycles per pixel: %f\n", (double)total_cycles / (ycbcr_image_ori->width * ycbcr_image_ori->height));
    // printf("Throughput: %f pixels/second\n", (ycbcr_image_ori->width * ycbcr_image_ori->height) / (endTime - startTime));
    // free_ycbcr_image(ycbcr_image_ori);

    // getTestQuantization();
    Test_Encode_block();
    return 0;
}