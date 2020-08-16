#include <stdio.h>
#include <math.h>

#include "helpers.h"

void grayscaleCalc(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    grayscaleCalc(height, width, image);
}

void grayscaleCalc(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float greyValue = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            greyValue = greyValue / 3;
            image[i][j].rgbtBlue = round(greyValue);
            image[i][j].rgbtGreen = round(greyValue);
            image[i][j].rgbtRed = round(greyValue);
        }
    }
    return;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < width / 2; j++, k--)
        {
            BYTE temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            image[i][k].rgbtBlue = temp;

            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][k].rgbtGreen = temp;

            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][k].rgbtRed = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = width - 1; j >= 0; j--)
        {
            imageCopy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            imageCopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageCopy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRgbtBlue = 0;
            float totalRgbtGreen = 0;
            float totalRgbtRed = 0;
            int divider = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int x = i + k;
                    int y = j + l;
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        totalRgbtBlue += imageCopy[x][y].rgbtBlue;
                        totalRgbtGreen += imageCopy[x][y].rgbtGreen;
                        totalRgbtRed += imageCopy[x][y].rgbtRed;
                        divider += 1;
                    }
                }
            }
            image[i][j].rgbtBlue = round(totalRgbtBlue / divider);
            image[i][j].rgbtGreen = round(totalRgbtGreen / divider);
            image[i][j].rgbtRed = round(totalRgbtRed / divider);
        }
    }
    return;
}

// Detect edges
/*
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int Gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    float calculatedXRedImageCopy[height][width];
    float calculatedXGreenImageCopy[height][width];
    float calculatedXBlueImageCopy[height][width];

    float calculatedYRedImageCopy[height][width];
    float calculatedYGreenImageCopy[height][width];
    float calculatedYBlueImageCopy[height][width];

    float totalRgbtRed = 0;
    float totalRgbtGreen = 0;
    float totalRgbtBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalRgbtRed = 0;
            totalRgbtGreen = 0;
            totalRgbtBlue = 0;
            for (int k = -1; k < 2; k++)
            {
                int x = i + k;
                int kPlusOne = k + 1;

                for (int l = -1; l < 2; l++)
                {
                    int y = j + l;
                    int lPlusOne = l + 1;

                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        int currentGxArrValue = Gx[kPlusOne][lPlusOne];
                        totalRgbtRed += (image[x][y].rgbtRed * currentGxArrValue);
                        totalRgbtGreen += (image[x][y].rgbtGreen * currentGxArrValue);
                        totalRgbtBlue += (image[x][y].rgbtBlue * currentGxArrValue);
                    }
                }
            }
            calculatedXRedImageCopy[i][j] = totalRgbtRed;
            calculatedXGreenImageCopy[i][j] = totalRgbtGreen;
            calculatedXBlueImageCopy[i][j] = totalRgbtBlue;
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            totalRgbtRed = 0;
            totalRgbtGreen = 0;
            totalRgbtBlue = 0;
            for (int k = -1; k < 2; k++)
            {
                int x = i + k;
                int kPlusOne = k + 1;

                for (int l = -1; l < 2; l++)
                {
                    int y = j + l;
                    int lPlusOne = l + 1;

                    if (x >= 0 && x < width && y >= 0 && y < height)
                    {
                        int currentGyArrValue = Gy[lPlusOne][kPlusOne];
                        totalRgbtRed += (image[y][x].rgbtRed * currentGyArrValue);
                        totalRgbtGreen += (image[y][x].rgbtGreen * currentGyArrValue);
                        totalRgbtBlue += (image[y][x].rgbtBlue * currentGyArrValue);
                    }
                }
            }
            calculatedYRedImageCopy[j][i] = totalRgbtRed;
            calculatedYGreenImageCopy[j][i] = totalRgbtGreen;
            calculatedYBlueImageCopy[j][i] = totalRgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalRgbtRed = 0;
            totalRgbtGreen = 0;
            totalRgbtBlue = 0;

            totalRgbtRed = fabs(sqrt((calculatedXRedImageCopy[i][j] * calculatedXRedImageCopy[i][j]) +
                                    (calculatedYRedImageCopy[i][j] * calculatedYRedImageCopy[i][j])));
            totalRgbtGreen = fabs(sqrt((calculatedXGreenImageCopy[i][j] * calculatedXGreenImageCopy[i][j]) +
                                    (calculatedYGreenImageCopy[i][j] * calculatedYGreenImageCopy[i][j])));
            totalRgbtBlue = fabs(sqrt((calculatedXBlueImageCopy[i][j] * calculatedXBlueImageCopy[i][j]) +
                                (calculatedYBlueImageCopy[i][j] * calculatedYBlueImageCopy[i][j])));

            if (totalRgbtBlue > 255)
            {
                totalRgbtBlue = 255;
            }
            if (totalRgbtGreen > 255)
            {
                totalRgbtGreen = 255;
            }
            if (totalRgbtRed > 255)
            {
                totalRgbtRed = 255;
            }
            image[i][j].rgbtBlue = round(totalRgbtBlue);
            image[i][j].rgbtGreen = round(totalRgbtGreen);
            image[i][j].rgbtRed = round(totalRgbtRed);
        }
    }
    return;
}
*/

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int Gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    float calculatedXRedImageCopy[height][width];
    float calculatedXGreenImageCopy[height][width];
    float calculatedXBlueImageCopy[height][width];

    float calculatedYRedImageCopy[height][width];
    float calculatedYGreenImageCopy[height][width];
    float calculatedYBlueImageCopy[height][width];

    float totalRgbtRed = 0;
    float totalRgbtGreen = 0;
    float totalRgbtBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalXRgbtRed = 0;
            float totalXRgbtGreen = 0;
            float totalXRgbtBlue = 0;

            float totalYRgbtRed = 0;
            float totalYRgbtGreen = 0;
            float totalYRgbtBlue = 0;

            for (int k = -1; k < 2; k++)
            {
                int x = i + k;
                int kPlusOne = k + 1;

                for (int l = -1; l < 2; l++)
                {
                    int y = j + l;
                    int lPlusOne = l + 1;

                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        int currentGxArrValue = Gx[kPlusOne][lPlusOne];
                        totalXRgbtRed += (image[x][y].rgbtRed * currentGxArrValue);
                        totalXRgbtGreen += (image[x][y].rgbtGreen * currentGxArrValue);
                        totalXRgbtBlue += (image[x][y].rgbtBlue * currentGxArrValue);

                        int currentGyArrValue = Gy[kPlusOne][lPlusOne];
                        totalYRgbtRed += (image[x][y].rgbtRed * currentGyArrValue);
                        totalYRgbtGreen += (image[x][y].rgbtGreen * currentGyArrValue);
                        totalYRgbtBlue += (image[x][y].rgbtBlue * currentGyArrValue);
                    }
                }
            }
            calculatedXRedImageCopy[i][j] = totalXRgbtRed;
            calculatedXGreenImageCopy[i][j] = totalXRgbtGreen;
            calculatedXBlueImageCopy[i][j] = totalXRgbtBlue;

            calculatedYRedImageCopy[i][j] = totalYRgbtRed;
            calculatedYGreenImageCopy[i][j] = totalYRgbtGreen;
            calculatedYBlueImageCopy[i][j] = totalYRgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalRgbtRed = 0;
            totalRgbtGreen = 0;
            totalRgbtBlue = 0;

            totalRgbtRed = fabs(sqrt((calculatedXRedImageCopy[i][j] * calculatedXRedImageCopy[i][j]) +
                                    (calculatedYRedImageCopy[i][j] * calculatedYRedImageCopy[i][j])));
            totalRgbtGreen = fabs(sqrt((calculatedXGreenImageCopy[i][j] * calculatedXGreenImageCopy[i][j]) +
                                    (calculatedYGreenImageCopy[i][j] * calculatedYGreenImageCopy[i][j])));
            totalRgbtBlue = fabs(sqrt((calculatedXBlueImageCopy[i][j] * calculatedXBlueImageCopy[i][j]) +
                                (calculatedYBlueImageCopy[i][j] * calculatedYBlueImageCopy[i][j])));

            if (totalRgbtBlue > 255)
            {
                totalRgbtBlue = 255;
            }
            if (totalRgbtGreen > 255)
            {
                totalRgbtGreen = 255;
            }
            if (totalRgbtRed > 255)
            {
                totalRgbtRed = 255;
            }
            image[i][j].rgbtBlue = round(totalRgbtBlue);
            image[i][j].rgbtGreen = round(totalRgbtGreen);
            image[i][j].rgbtRed = round(totalRgbtRed);
        }
    }
    return;
}

//working double loop sample
/*void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int Gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    float calculatedXRedImageCopy[height][width];
    float calculatedXGreenImageCopy[height][width];
    float calculatedXBlueImageCopy[height][width];

    float calculatedYRedImageCopy[height][width];
    float calculatedYGreenImageCopy[height][width];
    float calculatedYBlueImageCopy[height][width];

    float totalRgbtRed = 0;
    float totalRgbtGreen = 0;
    float totalRgbtBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalRgbtRed = 0;
            totalRgbtGreen = 0;
            totalRgbtBlue = 0;
            for (int k = -1; k < 2; k++)
            {
                int x = i + k;
                int kPlusOne = k + 1;

                for (int l = -1; l < 2; l++)
                {
                    int y = j + l;
                    int lPlusOne = l + 1;

                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        int currentGxArrValue = Gx[kPlusOne][lPlusOne];
                        totalRgbtRed += (image[x][y].rgbtRed * currentGxArrValue);
                        totalRgbtGreen += (image[x][y].rgbtGreen * currentGxArrValue);
                        totalRgbtBlue += (image[x][y].rgbtBlue * currentGxArrValue);
                    }
                }
            }
            calculatedXRedImageCopy[i][j] = totalRgbtRed;
            calculatedXGreenImageCopy[i][j] = totalRgbtGreen;
            calculatedXBlueImageCopy[i][j] = totalRgbtBlue;
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            totalRgbtRed = 0;
            totalRgbtGreen = 0;
            totalRgbtBlue = 0;
            for (int k = -1; k < 2; k++)
            {
                int x = j + k;
                int kPlusOne = k + 1;

                for (int l = -1; l < 2; l++)
                {
                    int y = i + l;
                    int lPlusOne = l + 1;

                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        int currentGyArrValue = Gy[kPlusOne][lPlusOne];
                        totalRgbtRed += (image[x][y].rgbtRed * currentGyArrValue);
                        totalRgbtGreen += (image[x][y].rgbtGreen * currentGyArrValue);
                        totalRgbtBlue += (image[x][y].rgbtBlue * currentGyArrValue);
                    }
                }
            }
            calculatedYRedImageCopy[j][i] = totalRgbtRed;
            calculatedYGreenImageCopy[j][i] = totalRgbtGreen;
            calculatedYBlueImageCopy[j][i] = totalRgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalRgbtRed = 0;
            totalRgbtGreen = 0;
            totalRgbtBlue = 0;

            totalRgbtRed = fabs(sqrt((calculatedXRedImageCopy[i][j] * calculatedXRedImageCopy[i][j]) +
                                    (calculatedYRedImageCopy[i][j] * calculatedYRedImageCopy[i][j])));
            totalRgbtGreen = fabs(sqrt((calculatedXGreenImageCopy[i][j] * calculatedXGreenImageCopy[i][j]) +
                                    (calculatedYGreenImageCopy[i][j] * calculatedYGreenImageCopy[i][j])));
            totalRgbtBlue = fabs(sqrt((calculatedXBlueImageCopy[i][j] * calculatedXBlueImageCopy[i][j]) +
                                (calculatedYBlueImageCopy[i][j] * calculatedYBlueImageCopy[i][j])));

            if (totalRgbtBlue > 255)
            {
                totalRgbtBlue = 255;
            }
            if (totalRgbtGreen > 255)
            {
                totalRgbtGreen = 255;
            }
            if (totalRgbtRed > 255)
            {
                totalRgbtRed = 255;
            }
            image[i][j].rgbtBlue = round(totalRgbtBlue);
            image[i][j].rgbtGreen = round(totalRgbtGreen);
            image[i][j].rgbtRed = round(totalRgbtRed);
        }
    }
    return;
}*/