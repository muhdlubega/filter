#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //apply for every pixel on the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //take the average of the red, green and blue values as floating points
            float gB = image[i][j].rgbtBlue;
            float gG = image[i][j].rgbtGreen;
            float gR = image[i][j].rgbtRed;
            float gRGB = round((gB + gG + gR) / 3.0);

            //insert the average value as the new red, green and blue values to output grayscale image
            image[i][j].rgbtBlue = gRGB;
            image[i][j].rgbtGreen = gRGB;
            image[i][j].rgbtRed = gRGB;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //apply for every pixel on the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int max = 255;

            //input sepia algorithm for red, green and blue respectively
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //cap the limit for red, blue and green at 255
            if (sepiaRed > max)
            {
                sepiaRed = max;
            }
            if (sepiaGreen > max)
            {
                sepiaGreen = max;
            }
            if (sepiaBlue > max)
            {
                sepiaBlue = max;
            }

            //insert new red, blue and green values respectively to output sepia image
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    //apply for every pixel on the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //set up temorary space for swapping the pixels
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

//set up calculation for the box blur
int calc(int i, int j, int height, int width, RGBTRIPLE image[height][width], int number)
{
    float n = 0;
    int sum = 0;

    //apply equation for 3 rows and 3 columns
    for (int a = i - 1; a < (i + 2); a++)
    {
        for (int b = j - 1; b < (j + 2); b++)
        {
            //sets calculation limits for height and width at the borders
            if (a < 0 || a >= height)
            {
                break;
            }

            if (b < 0 || b >= width)
            {
                continue;
            }

            //add respective values of pixels in the 3x3 box
            if (number == 0)
            {
                sum += image[a][b].rgbtRed;
            }

            else if (number == 1)
            {
                sum += image[a][b].rgbtGreen;
            }

            else
            {
                sum += image[a][b].rgbtBlue;
            }
            n++;
        }
    }
    return round(sum / n);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    //apply for every pixel on the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //create copy of image to not affect blur of surrounding images
            copy[i][j] = image[i][j];
        }
    }

    //apply for every pixel on the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //get RGB values from the box blur calculation
            image[i][j].rgbtRed = calc(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = calc(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = calc(i, j, height, width, copy, 2);
        }
    }

    return;
}