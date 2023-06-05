#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Taking RGB values
            float r = image[i][j].rgbtRed;
            float g = image[i][j].rgbtGreen;
            float b = image[i][j].rgbtBlue;

            // Turning gray
            float gray = (r + g + b) / 3;

            // Swapping RGB values
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = round(gray);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Taking RGB values
            float r = image[i][j].rgbtRed;
            float g = image[i][j].rgbtGreen;
            float b = image[i][j].rgbtBlue;

            // Converting into sepia values
            float nr = (0.393 * r) + (0.769 * g) + (0.189 * b);
            float ng = (0.349 * r) + (0.686 * g) + (0.168 * b);
            float nb = (0.272 * r) + (0.534 * g) + (0.131 * b);

            // Checking 255 limit
            if (nr > 255)
            {
                nr = 255;
            }
            if (ng > 255)
            {
                ng = 255;
            }
            if (nb > 255)
            {
                nb = 255;
            }

            // Swapping RGB values
            image[i][j].rgbtRed = round(nr);
            image[i][j].rgbtGreen = round(ng);
            image[i][j].rgbtBlue = round(nb);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Copying image
    RGBTRIPLE image_copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    // Reflecting image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][width - (j + 1)];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Var to receive blur pixels
    RGBTRIPLE image_blur[height][width];

    // Iterating image pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // New RGB values
            float nr = 0;
            float nb = 0;
            float ng = 0;
            int counter = 0;

            // Iterating surouding pixels
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    // Checking corners and edges
                    if (i + h > height - 1 || i + h < 0)
                    {
                        continue;
                    }
                    if (j + w > width - 1 || j + w < 0)
                    {
                        continue;
                    }

                    // Adding new RGB values
                    nr += image[i + h][j + w].rgbtRed;
                    ng += image[i + h][j + w].rgbtGreen;
                    nb += image[i + h][j + w].rgbtBlue;
                    counter++;
                }
            }

            // Adding blur pixels
            image_blur[i][j].rgbtRed = round(nr / counter);
            image_blur[i][j].rgbtGreen = round(ng / counter);
            image_blur[i][j].rgbtBlue = round(nb / counter);
        }
    }

    // Bluring the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_blur[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_blur[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_blur[i][j].rgbtBlue;
        }
    }
    return;
}