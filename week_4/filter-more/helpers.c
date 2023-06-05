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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Var to receive new pixels
    RGBTRIPLE image_new[height][width];

    // Sobel operator vars
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterating image pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Gx and Gy RGB values
            float Gxr = 0;
            float Gxg = 0;
            float Gxb = 0;
            float Gyr = 0;
            float Gyg = 0;
            float Gyb = 0;

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

                    // Adding Gx and Gy RGB values
                    Gxr += image[i + h][j + w].rgbtRed * Gx[h + 1][w + 1];
                    Gxg += image[i + h][j + w].rgbtGreen * Gx[h + 1][w + 1];
                    Gxb += image[i + h][j + w].rgbtBlue * Gx[h + 1][w + 1];
                    Gyr += image[i + h][j + w].rgbtRed * Gy[h + 1][w + 1];
                    Gyg += image[i + h][j + w].rgbtGreen * Gy[h + 1][w + 1];
                    Gyb += image[i + h][j + w].rgbtBlue * Gy[h + 1][w + 1];
                }
            }

            // New RGB values
            int nr = round(sqrt(pow(Gxr, 2) + pow(Gyr, 2)));
            int ng = round(sqrt(pow(Gxg, 2) + pow(Gyg, 2)));
            int nb = round(sqrt(pow(Gxb, 2) + pow(Gyb, 2)));

            // Checking 255 limits
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

            // Adding new pixels to the copy
            image_new[i][j].rgbtRed = nr;
            image_new[i][j].rgbtGreen = ng;
            image_new[i][j].rgbtBlue = nb;
        }
    }

    // Apllying new pixels to the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_new[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_new[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_new[i][j].rgbtBlue;
        }
    }
    return;
}