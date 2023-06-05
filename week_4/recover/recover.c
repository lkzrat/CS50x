#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Checking command-line arguments
    if (argc != 2)
    {
        printf("Use exactly one command-line argument\n");
        return 1;
    }

    // Opening the file
    FILE *input_file = fopen(argv[1], "r");

    // Checking the file
    if (input_file == NULL)
    {
        printf("The file %s can't be opened\n", argv[1]);
        return 1;
    }

    // Setting memory
    FILE *output_file = NULL;
    BYTE buffer[512];
    char file_name[8] = {0};
    int image_counter = 0;

    // Read all the file's memory
    while (fread(buffer, sizeof(BYTE) * 512, 1, input_file) == 1)
    {
        // Checking Jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Checking valid input for output
            if (output_file != NULL)
            {
                fclose(output_file);
            }

            // Writing jpeg
            sprintf(file_name, "%03i.jpg", image_counter);
            output_file = fopen(file_name, "w");
            image_counter++;
        }

        // Keep writing to jpeg file if new jpeg is not found
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, output_file);
        }
    }

    // Closing files
    fclose(input_file);
    fclose(output_file);
}
