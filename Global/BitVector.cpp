#include "BitVector.hpp"
#include "Utilities.hpp"


// TODO: Proteger les taleaux des copies
BitVector::BitVector(short unsigned int block_size) {
    this->block_size = block_size;
}

// void BitVector::_killInternalVals() {
//     delete [] this->_internal_values ;
// }


BitVector::~BitVector() {
    this->_killInternalData();
}

void BitVector::_killInternalData() {
    if (this->_data_size == NULL) {
        return ;
    }

    delete [] _data;

}
std::tuple<size_t, short unsigned int> BitVector::getPosInArray(size_t element_number, errorMods error_mod) {
    if (element_number <= 0) {
         return std::tuple<size_t, short unsigned int> {0, 0};
    } else if (element_number > this->_element_number) {
        displayLengthError(error_mod, "Not enough elements. Current element number is : '" + 
                           std::string(1,  this->_element_number) + "'. Got : " + std::string(1, element_number), __FILE__, __func__);
    }
    float f_block_size = this->block_size; // Convert in float in order to allow division with a remainder

    size_t position_in_array = (f_block_size / 8) * element_number * 1000; // *1000 Permet d'avoir un int quoi qu'il arrive (a / 8 = n.xxx donc *100 nxxx.0)
    size_t char_position = position_in_array / 1000;

    float block_position_in_char = getFirstDigits(position_in_array, 3);

    return std::tuple<size_t, short unsigned int> {char_position, block_position_in_char / 1000 * 8};
}

size_t BitVector::getElementNumber(size_t char_position, short unsigned int block_position_in_char, errorMods error_mod) {
    if (char_position <= 0 && block_position_in_char <= 0) {
        return 0;
    } 
    
    if (block_position_in_char >= 8) {
        displayLengthError(error_mod, "Illegal block_position_in_char. Block position should be lower than 8. Got : " + std::string(1, block_position_in_char), __FILE__, __func__);
    } else if (char_position > SIZE_MAX / 1000) {
        size_t temp = SIZE_MAX;
        displayLengthError(error_mod, "Maximum value reached for element_number. element_number should be lower than" + std::string(1, temp / 1000) + "(SIZE_MAX / 1 000) Got : " + std::string(1, block_position_in_char), __FILE__, __func__);
    }  
   
    float f_block_position_in_char = block_position_in_char; // Convert in float in order to allow division with a remainder
    f_block_position_in_char = (f_block_position_in_char / 8.0) * 1000;   // Position score due to \p block_position_in_char
    size_t position_in_array = char_position * 1000 + f_block_position_in_char; // Position score due to \p block_position_in_char and \p char_position 

    float f_block_size = this->block_size; // Convert in float in order to allow division with a remainder
    size_t element_length = (f_block_size / 8.0) * 1000 ;  // position score of one element 

    position_in_array = position_in_array / element_length;

    return position_in_array;  // Number of element
 }   

size_t BitVector::getDataSize() {
    return this->_data_size;
}

size_t BitVector::getElementNumber() {
    return this->_element_number;
}

size_t BitVector::size() {
    return this->_element_number;
}