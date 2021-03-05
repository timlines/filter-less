#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <cs50.h>


//My Function prototypes
int max(int value);
void swap(RGBTRIPLE *x, RGBTRIPLE *y);
RGBTRIPLE pixelB(int i, int j, int height, int width, RGBTRIPLE image[height][width]);
bool validPixel(int i, int j, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //cycle through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //get the average of the values, keep in mind float and rounding
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00);

            //update the values to be grayscale
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
}



// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Cycle through all the pixel based on their height and width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //save a copy of the original values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            //change values to sepia via magic (ie. sepia formula) also round and check for max.
            int sepiaRed = max(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            int sepiaGreen = max(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            int sepiaBlue = max(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

            //Update the values to sepia
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //cycle through all the pixels
    for (int i = 0; i < height; i++)
    {
        //only cycle through have the width because we'll be swaping them
        for (int j = 0; j < width / 2; j++)
        {
            //swap two pixels
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make a copy of the image
    RGBTRIPLE imageB[height][width];

    //loop through all the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //swap each pixel with the blurred pixel
            imageB[i][j] = pixelB(i, j, height, width, image);
        }
    }

    //after all the pixel's are blurred based off the orginal image then
    for (int i = 0; i < height; i++)
    {
        //cycle through all the pixels
        for (int j = 0; j < width; j++)
        {

            //update every pixel to the blurred pixel
            image[i][j] = imageB[i][j];
        }
    }
}

//Included Functions

//Check if the value for an RGB value is over 255
int max(int value)
{
    //if a pixel is over 255 then return 255, else return the value
    return value > 255 ? 255 : value;
}

//Swap Two Pixels
void swap(RGBTRIPLE *x, RGBTRIPLE *y)
{
    RGBTRIPLE temp = *x;
    *x = *y;
    *y = temp;
}

//Get a blurred Pixel
RGBTRIPLE pixelB(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    //define integers for each value
    int red, blue, green;

    //set integers to 0
    red = blue = green = 0;

    //create an interger to count the number of pixels
    int pixelcount = 0;

    //cycle through the pixel, starting with one before and going till on after on each row
    for (int di = -1; di <= 1; di++)
    {
        //and each column
        for (int dj = -1; dj <= 1; dj++)
        {
            //create a new integer ni and nj to store the new pixel locations
            int ni = i + di;
            int nj = j + dj;

            //test that each new pixel location is a valid Pixel
            if (validPixel(ni, nj, height, width))
            {
                //update the pixelcount
                pixelcount++;

                //add value to red
                red += image[ni][nj].rgbtRed;

                //add value to green
                green += image[ni][nj].rgbtGreen;

                //add value to blue
                blue += image[ni][nj].rgbtBlue;
            }
        }
    }

    //define a new RGBTRIPLE called blurry
    RGBTRIPLE blurry;

    //find average of red and update
    blurry.rgbtRed = round((float) red / pixelcount);

    //find average of green and update
    blurry.rgbtGreen = round((float) green / pixelcount);

    //find average of ble and update
    blurry.rgbtBlue = round((float) blue / pixelcount);

    //return the new RGBTRIPLE called blurry which now stores the blurry values
    return blurry;
}

bool validPixel(int i, int j, int height, int width)
{
    //Check if the pixel is outside the image or an edge case
    return i >= 0 && i < height && j >= 0 && j < width;
}



/* References

?: Ternary operator or binary operator, retrieved from: https://en.wikipedia.org/

Swap two Numbers: https://www.geeksforgeeks.org/c-program-swap-two-numbers/

*/
