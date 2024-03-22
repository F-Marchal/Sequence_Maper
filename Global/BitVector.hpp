#include <iostream>
#include <tuple>
#include "Utilities.hpp"
class BitVector
{
private:
    char * _data = NULL;
    
    size_t _data_size = 0;
    size_t _element_number = 0;

    short unsigned int block_size;

protected:
    void _killInternalData();

public:
    BitVector(short unsigned int block_size);
    ~BitVector();

    std::tuple<size_t, short unsigned int> getPosInArray(size_t element_number, errorMods error_mod=ignore);
    size_t getElementNumber(size_t char_position, short unsigned int block_position_in_char, errorMods error_mod=ignore);

    size_t getDataSize();
    size_t getElementNumber();
    size_t size();

};



