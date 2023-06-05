#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse INPUT OUTPUT\n");
        return 1;
    }

    // Open input file for reading
    FILE *input_file = fopen(argv[1], "r");

    // Check if the file can be open
    if (input_file == NULL)
    {
        printf("The file %s can't be open\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER input_header;
    fread(&input_header, sizeof(WAVHEADER), 1, input_file);

    // Use check_format to ensure WAV format
    if (check_format(input_header) != 0)
    {
        printf("Incorrect file format\n");
        return 2;
    }

    // Open output file for writing
    FILE *output_file = fopen(argv[2], "wb");
    if (output_file == NULL)
    {
        printf("Output file con't be open/created\n");
        return 1;
    }

    // Write header to file
    fwrite(&input_header, sizeof(WAVHEADER), 1, output_file);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(input_header);

    // Write reversed audio to file
    if (fseek(input_file, block_size, SEEK_END))
    {
        return 1;
    }

    BYTE buffer[block_size];

    while (ftell(input_file) - block_size > sizeof(input_header))
    {
        if (fseek(input_file, - 2 * block_size, SEEK_CUR))
        {
            return 1;
        }
        fread(buffer, block_size, 1, input_file);
        fwrite(buffer, block_size, 1, output_file);
    }

    // Close the files
    fclose(input_file);
    fclose(output_file);
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 0;
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    int size = header.numChannels * header.bitsPerSample / 8;
    return size;
}