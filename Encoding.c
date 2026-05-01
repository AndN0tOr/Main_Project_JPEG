#include "Encoding.h"
#include <stdio.h>
#include <stdlib.h>

FILE *jpeg_file = NULL;
huffman_code HT_DC_LUMA[256];
huffman_code HT_AC_LUMA[256];
huffman_code HT_DC_CHROMA[256];
huffman_code HT_AC_CHROMA[256];
const uint8_t STD_DC_LUMA_BITS[16] = {
    0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0
};
const uint8_t STD_DC_LUMA_VALS[12] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B
};

// --- 2. BẢNG AC LUMA (Độ sáng) ---
const uint8_t STD_AC_LUMA_BITS[16] = {
    0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7D
};
const uint8_t STD_AC_LUMA_VALS[162] = {
    0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
    0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0,
    0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5,
    0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2,
    0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
    0xF9, 0xFA
};

// --- 3. BẢNG DC CHROMA (Màu sắc) ---
const uint8_t STD_DC_CHROMA_BITS[16] = {
    0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
};
const uint8_t STD_DC_CHROMA_VALS[12] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B
};

// --- 4. BẢNG AC CHROMA (Màu sắc) ---
const uint8_t STD_AC_CHROMA_BITS[16] = {
    0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77
};
const uint8_t STD_AC_CHROMA_VALS[162] = {
    0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
    0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52, 0xF0,
    0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16, 0x24, 0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5,
    0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3,
    0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA,
    0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
    0xF9, 0xFA
};  
size_value get_size_value(int16_t value){
    // This function will return the size and value for the given input value.
    // The size is determined by the number of bits needed to represent the value in binary.
    size_value result;
    if (value == 0){
        result.size = 0;
        result.value = 0;
    } else {
        int32_t abs_value = abs(value);
        result.size = 32 - __builtin_clz(abs_value); // Calculate size based on absolute value
        if (value < 0){
            result.value = value + (1 << result.size) - 1; // Convert to positive range for negative values
        } else {
            result.value = value; // Positive values remain unchanged
        }
    }
    return result;
}
size_value encode_dc_dpcm(int16_t current_dc, int16_t previous_dc){
    int16_t diff = current_dc - previous_dc;
    return get_size_value(diff);
}
void Encode_block (int16_t block[64], int16_t* previous_dc, void* dc_huffman_table, void* ac_huffman_table){
    // This function will encode a single 8x8 block using the provided Huffman tables.
    // It will first encode the DC coefficient using DPCM and then encode the AC coefficients using run-length encoding and Huffman coding.
    int16_t current_dc = block[0];
    size_value dc_size_value = encode_dc_dpcm(current_dc, *previous_dc);
    *previous_dc = current_dc; // Update previous DC for the next block
    // Encode DC coefficient using dc_huffman_table and dc_size_value
    Write_Huffman_bits(dc_size_value.size, dc_size_value.value, dc_huffman_table);
    // Encode AC coefficients using ac_huffman_table, run-length encoding, and zigzag order
    int8_t run_length = 0;
    uint32_t bit_buffer = 0;
    uint8_t bit_count = 0;
    for (int8_t i = 1; i < 64; i++){
        if (block[i] == 0){
            run_length++;
        } else {
            while (run_length > 15){
                // Encode a run of 16 zeros
                 // Size 0 with run length 15
                Write_Huffman_bits(0xF0, 0, ac_huffman_table);
                run_length -= 16;
            }
            size_value ac_size_value = get_size_value(block[i]);
            ac_size_value.size |= (run_length << 4); // Combine run length and size
            Write_Huffman_bits(ac_size_value.size, ac_size_value.value, ac_huffman_table);
            run_length = 0; // Reset run length after encoding a non-zero coefficient
        }
    }
    if (run_length > 0){
        // Encode end of block (EOB) if there are remaining zeros
        Write_Huffman_bits(0x00, 0, ac_huffman_table); // EOB symbol
    }
}
uint32_t bit_buffer = 0;
uint8_t bit_count = 0;
void Put_bits(uint32_t bits, uint8_t length){
    // This function will put the specified number of bits into the output buffer.
    // It will handle bit buffering and ensure that bits are written to the output in the correct order.
    // ...
    if (length == 0){
        return; // No bits to write
    }
    bit_buffer = (bit_buffer << length) | (bits & ((1 << length) - 1)); // Add new bits to buffer
    bit_count += length; // Update bit count

    while (bit_count >= 8){
        uint8_t byte_to_write = (bit_buffer >> (bit_count - 8)) & 0xFF; // Get the top 8 bits to write
        Write_Physical_Bytes(byte_to_write);
        if (byte_to_write == 0xFF){
            // If the byte is 0xFF, we need to write a zero byte after it to prevent marker confusion
            Write_Physical_Bytes(0x00);
        }
        bit_count -= 8; // Remove the written bits from the buffer
    }
}
void Flush_bits(){
    // This function will flush any remaining bits in the buffer to the output, padding with zeros if necessary.
    if (bit_count > 0){
        uint8_t padding_bits = 8 - bit_count; // Calculate how many padding bits are needed
        uint8_t filler = (1 << padding_bits) - 1; // Create a filler byte with the necessary padding bits
        Put_bits(filler, padding_bits); // Write the padding bits to the output

    }
    bit_buffer = 0; // Clear the buffer
    bit_count = 0; // Reset bit count
}
void Write_Huffman_bits(uint8_t symbol_byte, uint16_t value_bits, void* huffman_table){
    // This function will write the Huffman bits for the given size and value using the provided Huffman table.
    // It will look up the Huffman code for the size and then write the bits for the value.
    // ...
    huffman_code* table = (huffman_code*)huffman_table;
    int16_t huff_code = table[symbol_byte].code;
    uint8_t huff_length = table[symbol_byte].length;


    Put_bits(huff_code, huff_length); // Write the Huffman code
    uint8_t value_size = symbol_byte & 0x0F; // Size is in the lower 4 bits of symbol_byte
    if (value_size > 0){
        Put_bits(value_bits, value_size); // Write the value bits (size is in the lower 4 bits of symbol_byte)
    }
}
void generate_huffman_table(const uint8_t *bits, const uint8_t *vals, huffman_code *table) {
    uint16_t code = 0;
    int val_idx = 0;

    // Quét qua các độ dài mã từ 1 bit đến 16 bit
    for (int length = 1; length <= 16; length++) {
        
        // Đọc xem có bao nhiêu mã có độ dài này (từ mảng BITS)
        int num_codes = bits[length - 1]; 

        for (int i = 0; i < num_codes; i++) {
            // Lấy ký hiệu tương ứng từ mảng VALS
            uint8_t symbol = vals[val_idx++];
            
            // Lưu vào mảng đích ở đúng vị trí (O(1) lookup)
            table[symbol].code = code;
            table[symbol].length = length;
            
            code++; // Tăng mã nhị phân lên 1
        }
        
        // Chuẩn bị mã nhị phân cho độ dài tiếp theo (Dịch trái 1 bit)
        code <<= 1; 
    }
}
void MCU_Encode(int16_t zigzag_array[384], int16_t *previous_dc_y, int16_t *previous_dc_cb, int16_t *previous_dc_cr){
    // This function will encode the entire MCU (16x16 block) using the zigzag order and the provided Huffman tables.
    // It will call Encode_block for each 8x8 block within the MCU and handle the necessary state (e.g., previous DC values).
    
    
    // Encode Y blocks
    for (int i = 0; i < 4; i++){
        Encode_block(&zigzag_array[i * 64], previous_dc_y, HT_DC_LUMA, HT_AC_LUMA);
    }
    // Encode Cb block
    Encode_block(&zigzag_array[256], previous_dc_cb, HT_DC_CHROMA, HT_AC_CHROMA);
    // Encode Cr block
    Encode_block(&zigzag_array[320], previous_dc_cr, HT_DC_CHROMA, HT_AC_CHROMA);
}   
void init_jpeg_encoding(){
    // This function will initialize the Huffman tables and any other necessary state for JPEG encoding.
    // It will call generate_huffman_table for each of the standard Huffman tables (DC Luma, AC Luma, DC Chroma, AC Chroma).
    generate_huffman_table(STD_DC_LUMA_BITS, STD_DC_LUMA_VALS, HT_DC_LUMA);
    generate_huffman_table(STD_AC_LUMA_BITS, STD_AC_LUMA_VALS, HT_AC_LUMA);

    // 2. Tạo bảng Chroma (cho khối Cb, Cr)
    generate_huffman_table(STD_DC_CHROMA_BITS, STD_DC_CHROMA_VALS, HT_DC_CHROMA);
    generate_huffman_table(STD_AC_CHROMA_BITS, STD_AC_CHROMA_VALS, HT_AC_CHROMA);
    
}
void Write_Physical_Bytes(uint8_t byte){
    // This function will write a single byte to the output (e.g., file or memory buffer).
    // It will handle any necessary buffering and ensure that bytes are written in the correct order.
    if (jpeg_file != NULL) {
        fputc(byte, jpeg_file); // Ghi 1 byte vào file
    }
}
void open_jpeg_file( char* filename) {
    printf("Writing JPEG file: %s\n", filename); // For demonstration, print the file being opened
    jpeg_file = fopen(filename, "wb");
    if (jpeg_file == NULL) {
        printf("Error opening file: %s\n", filename);
    }
}
void close_jpeg_file() {
    if (jpeg_file != NULL) {
        fclose(jpeg_file); // Đóng file sau khi ghi xong
        jpeg_file = NULL; // Đặt lại con trỏ file về NULL
    }
    printf("JPEG file written.\n"); // For demonstration, print that the file has been closed
}