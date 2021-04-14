
#pragma once

#include "vector"
namespace testspace {

    class ParentClass
    {
    public:
        virtual std::vector<uint8_t> Encode(std::vector<uint8_t> const& data) = 0;
        virtual std::vector<uint8_t> Decode(std::vector<uint8_t> const& data) = 0;
    };


    class Hamming74 :public ParentClass
    {
    private:
        uint8_t sum4BitsMod2(uint8_t x);
        uint8_t sum7BitsMod2(uint8_t x);
        uint8_t GetSindrom(uint8_t x);
    public:
        virtual std::vector<uint8_t> Encode(std::vector<uint8_t> const& data);
        virtual std::vector<uint8_t> Decode(std::vector<uint8_t> const& data);
    };

    class DiffCode :public ParentClass
    {

    public:
        virtual std::vector<uint8_t> Encode(std::vector<uint8_t> const& data);
        virtual std::vector<uint8_t> Decode(std::vector<uint8_t> const& data);
    };
}

