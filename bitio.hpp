
#include <stdio.h>
#include <string.h>

#pragma once

#define FILE_INFO_READ 1
#define FILE_INFO_WRITE 2

namespace Bitio
{
    class File
    {
        private:

            int BitPosition_;
            unsigned long long Position_;

            bool DidFileLoaded_;

            int  OpeningMode;
            // 1 : read
            // 2 : write

            // for reading mode
            int  CacheReadingChar_;
            bool pCacheReadingCharBits_[8];

            // for writing mode
            int  CachewritingChar_;
            bool pQueueingPutbits[8];

            void CalcBitsOfCharMember(void);

        public:

            FILE* pFile_;

            File();
            ~File();

            void SeekBits (int position);
            void SeekBytes(int position);

            bool GetBit();
            bool GetBits(bool* pDes, int getBits);

            void PutBit (bool bit);
            void PutBits(bool* pBits, int putBits);

            int  GetChar(void);
            void PutChar(int character);

            bool Open(char* pPath, const char* mode);
            void UseFileObj(FILE* pFile, const char* mode);
    };
};

Bitio::File::File()
{
    DidFileLoaded_ = false;
    pFile_ = NULL;
}

Bitio::File::~File()
{
    if (DidFileLoaded_ == true && OpeningMode == 1)
    {
        fclose(pFile_);
    }
    else if (DidFileLoaded_ == true && OpeningMode == 2)
    {
    }
}





void Bitio::File::SeekBits(int position)
{
    BitPosition_ = position;
}


void Bitio::File::SeekBytes(int position)
{
    Position_ = position;
    _fseeki64(pFile_, Position_, SEEK_SET);

    CalcBitsOfCharMember();
}





bool Bitio::File::GetBit()
{

    if (DidFileLoaded_ == false)
    {
        return false;
    }

    if (BitPosition_ >= 8)
    {
        Position_++;

        CalcBitsOfCharMember();

        BitPosition_ %= 8;
    }

    bool retval = pCacheReadingCharBits_[BitPosition_];

    BitPosition_++;

    return retval;
}


bool Bitio::File::GetBits(bool* pBits, int getBits)
{
    if (DidFileLoaded_ == false)
    {
        return false;
    }

    for (int i = 0; i < getBits; i++)
    {
        pBits[i] = GetBit();
    }

    return true;
}





void Bitio::File::PutBit(bool bit)
{
}





int  Bitio::File::GetChar(void)
{
    return fgetc(pFile_);
}





bool Bitio::File::Open(char* pPath, const char* mode)
    // r read
    // w write
{

    FILE* p_file;

    p_file = fopen(pPath, mode);

    if (p_file == NULL)
    {
        return false;
    }

    UseFileObj(p_file, mode);

    return true;
}

void Bitio::File::UseFileObj(FILE* pFile, const char* mode)
{
    pFile_ = pFile;
    DidFileLoaded_ = true;

    Position_ = 0;
    BitPosition_ = 0;

    fseek(pFile_, 0L, SEEK_SET);

    if (strcmp(mode, "r"))
    {
        OpeningMode = FILE_INFO_READ;
        CalcBitsOfCharMember();
    }

    else if (strcmp(mode, "w"))
    {
        OpeningMode = FILE_INFO_WRITE;
    }
}



void Bitio::File::CalcBitsOfCharMember()
{
    CacheReadingChar_ = GetChar();

    int reading_char = CacheReadingChar_;
    for (int i = 7; i >= 0; i--)
    {
        pCacheReadingCharBits_[i] = reading_char % 2;
        reading_char >>= 1;
    }
}
