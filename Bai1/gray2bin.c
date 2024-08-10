#include <stdio.h>

#define WIDTH 256
#define HEIGHT 256

void readFile(const char *inputName, unsigned char gray_matrix[])
{
    FILE *fptr = fopen(inputName, "rb");
    fread(gray_matrix, sizeof(char), WIDTH * HEIGHT, fptr);
    fclose(fptr);
}

void Gray2Bin(unsigned char bin_matrix[], unsigned char gray_matrix[])
{
    unsigned char threshold = 0x7F;
    unsigned char temp = 0x00;
    unsigned char countBit = 0;
    unsigned int index = 0;
    for (int x = 0; x < HEIGHT; x++)
    {
        for (int y = 0; y < WIDTH; y++)
        {
            if (countBit == 8)
            {
                bin_matrix[index++] = temp;
                temp = 0x00;
                countBit = 0;
            }
            temp <<= 1;
            countBit++;
            if (gray_matrix[x * WIDTH + y] > threshold)
            {
                temp |= 0x01;
            }
        }
    }
}

void writeFile(const char *outputName, unsigned char bin_matrix[])
{
    FILE *fptr = fopen(outputName, "wb");
    fwrite(bin_matrix, sizeof(char), (WIDTH * HEIGHT) / 8, fptr);
    fclose(fptr);
}

int main()
{
    unsigned char gray_matrix[WIDTH * HEIGHT];
    unsigned char bin_matrix[(WIDTH * HEIGHT) / 8];

    const char *inputName = "output/raw_gray.dat";
    const char *outputName = "output/raw_bin.dat";

    readFile(inputName, gray_matrix);
    Gray2Bin(bin_matrix, gray_matrix);
    writeFile(outputName, bin_matrix);
    return 0;
}