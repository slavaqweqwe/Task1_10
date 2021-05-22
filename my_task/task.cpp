#include "task.h"
using namespace testspace;

uint8_t Hamming74::sum4BitsMod2(uint8_t x)
{
    return (((x & 8) >> 3) ^ ((x & 16) >> 4) ^ ((x & 32) >> 5) ^ ((x & 64) >> 6));
}

std::vector<uint8_t> Hamming74::Encode(std::vector<uint8_t> const& data) {
    size_t out_size;
    if (data.size() % 4 == 0)
        out_size = (data.size() * 7) / 4;

    else
        out_size = (data.size() * 7) / 4 + 1;


    std::vector<uint8_t>  out_data(out_size);
    int NumbRecordedBits = 0;
    uint8_t x;

    for (int i = 0; i < data.size() * 2; i++)
    {
        if (i % 2 == 0) {
            x = (15 & data[i / 2]) << 3;
        }
        else {
            x = (240 & data[i / 2]) >> 1;
        }

        x = x | sum4BitsMod2(x & 104) | (sum4BitsMod2(x & 56) << 1) | (sum4BitsMod2(x & 112) << 2);

        out_data[NumbRecordedBits / 8] = out_data[NumbRecordedBits / 8] | (x << (NumbRecordedBits % 8));


        if (NumbRecordedBits % 8 > 1)
        {
            int ost = 8 - NumbRecordedBits % 8;
            out_data[NumbRecordedBits / 8 + 1] = x >> ost;
        }
        NumbRecordedBits += 7;
    }

    return out_data;
}




std::vector<uint8_t> DiffCode::Encode(std::vector<uint8_t> const& data) {

    std::vector<uint8_t>  out_data(data.size());

    out_data[0] = (0 ^ data[0]);
    for (int j = 1; j < 8; j++)
    {
        out_data[0] = (out_data[0] << 1 ^ data[0]);
    }


    for (int i = 1; i < data.size(); i++)
    {
        out_data[i] = ((out_data[i - 1] >> 7) ^ data[i]) & 1;
        for (int j = 1; j < 8; j++)
        {
            out_data[i] = out_data[i] | ((out_data[i] << 1) ^ data[i]) & (1 << j);
        }

    }
    return out_data;
};


uint8_t Hamming74::sum7BitsMod2(uint8_t x)
{
    return ((x & 1) ^ ((x & 2) >> 1) ^ ((x & 4) >> 2) ^ ((x & 8) >> 3) ^ ((x & 16) >> 4) ^ ((x & 32) >> 5) ^ ((x & 64) >> 6));
}
uint8_t Hamming74::GetSindrom(uint8_t x) {

    return (sum7BitsMod2(x & 105)) | (sum7BitsMod2(x & 58) << 1) | (sum7BitsMod2(x & 116) << 2);

}

std::vector<uint8_t> Hamming74::Decode(std::vector<uint8_t> const& data) {
    size_t out_size = data.size() * 8 / 7;
    out_size = (out_size + 1) / 2;

    std::vector<uint8_t>  out_data(out_size);

    int NumRecordedBits = 0;
    int NumRecordedByts = 0;
    uint8_t x;
    uint8_t sindrom;
    for (int i = 0; i < out_size * 2; i++)
    {
        if (NumRecordedBits < 2)
            x = (data[NumRecordedByts] >> NumRecordedBits);
        else
            x = (data[NumRecordedByts] >> NumRecordedBits) | (data[NumRecordedByts + 1] << (8 - NumRecordedBits));
        x &= 127;
        sindrom = GetSindrom(x);
        if (sindrom == 3) {
            if ((x & 8) == 0) {
                x += 8;
            }
            else {
                x -= 8;
            }
        }
        if (sindrom == 5) {
            if ((x & 64) == 0) {
                x += 64;
            }
            else {
                x -= 64;
            }
        }
        if (sindrom == 6) {
            if ((x & 16) == 0) {
                x += 16;
            }
            else {
                x -= 16;
            }
        }
        if (sindrom == 7) {
            if ((x & 32) == 0) {
                x += 32;
            }
            else {
                x -= 32;
            }
        }
        if (i % 2 == 0)
            out_data[i / 2] = (x & 120) >> 3;
        else {
            out_data[i / 2] |= (x & 120) << 1;
        }
        NumRecordedByts += (NumRecordedBits + 7) / 8;
        NumRecordedBits = (NumRecordedBits + 7) % 8;

    }
    return out_data;
}
    std::vector<uint8_t> DiffCode::Decode(std::vector<uint8_t> const& data) {

        std::vector<uint8_t>  out_data(data.size());

        out_data[0] = (data[0] ^ (data[0] << 1));

        for (int i = 1; i < data.size(); i++)
        {
            out_data[i] = ((data[i - 1] >> 7) | (data[i] << 1)) ^ data[i];
        }
        return out_data;
    }