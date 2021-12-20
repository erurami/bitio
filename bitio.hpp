
#include <stdio.h>
#pragma once

namespace Bitio
{
    class File
    {
        private:

            int mBitPosition_;
            unsigned long long mPosition_;

            int  CacheReadingChar_;
            bool pCacheReadingCharBits_[8];

            bool DidFileLoaded_;

            void CalcBitsOfCharMember(void);

        public:

            FILE* pFile_;

            File();

            void SeekBits (int position);
            void SeekBytes(int position);

            bool GetBit();
            bool GetBits(bool* pDes, int getBits);

            void PutBit (bool bit);
            void PutBits(bool* pBits, int putBits);

            int  GetChar();
            void PutChar(int character);

            bool Open(char* pPath);
            void UseFileObj(FILE* pFile);
    };
};

Bitio::File::File()
{
    DidFileLoaded_ = false;
    pFile_ = NULL;
}


void Bitio::File::SeekBits(int position)
{
    mBitPosition_ = position;
}

void Bitio::File::SeekBytes(int position)
{
    mPosition_ = position;
    fseek(pFile_, mPosition_, SEEK_SET);

    CacheReadingChar_ = getchar(pFile_);
    CalcBitsOfCharMember();
}



bool Bitio::File::GetBit();
{

    if (DidFileLoaded_ == false)
    {
        return false;
    }

    mBitPosition_++;

    if (mBitPosition_ >= 8)
    {
        mPosition_++;

        CacheReadingChar_ = getchar(pFile_);
        CalcBitsOfCharMember();

        mBitPosition_ %= 8;
    }

    return pCacheReadingCharBits_[mBitPosition_];
}

void Bitio::File::UseFileObj(FILE* pFile)
{
    pFile_ = pFile;
    DidFileLoaded_ = true;
}
