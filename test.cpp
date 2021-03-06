
#include "bitio.hpp"
#include <stdio.h>

int main()
{
    Bitio::File bitFile;

    bitFile.Open("test.txt", "r");

    bool bits_in_byte[8];

    for (int i = 0; i < 3; i++)
    {
        bitFile.GetBits(bits_in_byte, 8);

        printf("\n");
        for (int j = 0; j < 8; j++)
        {
            printf("%d\n", bits_in_byte[j]);
        }
    }
    printf("\n");

    bitFile.Open("write_test.txt", "w");

    for (int i = 0; i < 30; i++)
    {
        bitFile.PutBit(i % 2 == 0);
    }

}
