#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Sweeping through the pixels array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the pixel is black
            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtBlue == 0)
            {
                // Changing pixel color
                image[i][j].rgbtRed = 50;
                image[i][j].rgbtGreen = 150;
                image[i][j].rgbtBlue = 200;
            }
        }
    }
    return;
}
