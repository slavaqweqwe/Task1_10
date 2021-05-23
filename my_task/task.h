
#pragma once

#include "vector"
namespace testspace {

    class ICoder
    {
    public:
        virtual ~ICoder() {};
        virtual std::vector<uint8_t> Encode(std::vector<uint8_t> const& data) = 0;
        virtual std::vector<uint8_t> Decode(std::vector<uint8_t> const& data) = 0;
    };


    class Hamming74 :public ICoder
    {
    private:
        uint8_t sum4BitsMod2(uint8_t x);
        uint8_t sum7BitsMod2(uint8_t x);
        uint8_t GetSindrom(uint8_t x);
    public:
        ~Hamming74() override;
        std::vector<uint8_t> Encode(std::vector<uint8_t> const& data) override;
        std::vector<uint8_t> Decode(std::vector<uint8_t> const& data) override;
    };

    class DiffCode :public ICoder
    {

    public:
        ~DiffCode() override;
        std::vector<uint8_t> Encode(std::vector<uint8_t> const& data) override;
        std::vector<uint8_t> Decode(std::vector<uint8_t> const& data) override;
    };
}

