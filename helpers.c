#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;
            float Blue = image[i][j].rgbtBlue;
            int average = round((red + Green + Blue) / 3);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp[i][j];
        }
    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float sumRed = 0, sumGreen = 0, sumBlue = 0;
            int rowCoord[] = { i - 1, i, i + 1 };
            int colCoord[] = { j - 1, j, j + 1};

            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int curRow = rowCoord[r];
                    int curCol = colCoord[c];

                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        RGBTRIPLE pixel = image[curRow][curCol];

                        sumRed += pixel.rgbtRed;
                        sumGreen += pixel.rgbtGreen;
                        sumBlue += pixel.rgbtBlue;
                        count++;
                    }
                }
            }
            temp[i][j].rgbtRed = round(sumRed / count);
            temp[i][j].rgbtGreen = round(sumGreen / count);
            temp[i][j].rgbtBlue = round(sumBlue / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_red = 0, Gx_green = 0, Gx_blue = 0, Gy_red = 0, Gy_green = 0, Gy_blue = 0;
            
            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + r >= 0 && i + r < height && j + c >= 0 && j + c < width)
                    {
                        Gx_red += temp[i + r][j + c].rgbtRed * Gx[r + 1][c + 1];
                        Gx_green += temp[i + r][j + c].rgbtGreen * Gx[r + 1][c + 1];
                        Gx_blue += temp[i + r][j + c].rgbtBlue * Gx[r + 1][c + 1];
                        Gy_red += temp[i + r][j + c].rgbtRed * Gy[r + 1][c + 1];
                        Gy_green += temp[i + r][j + c].rgbtGreen * Gy[r + 1][c + 1];
                        Gy_blue += temp[i + r][j + c].rgbtBlue * Gy[r + 1][c + 1];
                    }
                }
            }
            int Red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int Green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int Blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            
            image[i][j].rgbtRed = Red > 255 ? 255 : Red;
            image[i][j].rgbtGreen = Green > 255 ? 255 : Green;
            image[i][j].rgbtBlue = Blue > 255 ? 255 : Blue;
            
        }
    }

    return;
}
