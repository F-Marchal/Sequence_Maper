#include "BitVector.hpp"
#include "Utilities.hpp"

// TODO: Proteger les taleaux des copies
BitVector::BitVector(short unsigned int block_size) {
    this->_element_size = block_size;
}





BitVector::~BitVector() {
    this->_killInternalData();
}

void BitVector::_killInternalData() {
    if (this->_data == NULL) {
        return ;
    }

    delete [] _data;

}

// void BitVector::addElement(size_t element_number) {

// }



// void BitVector::reserveCapacity(size_t element_number) {

// }



// void BitVector::setCurrentCapacity(size_t element_number) {

// }

// void BitVector::shrinkCapacity() {

// }

std::tuple<size_t, short unsigned int> BitVector::getPosInArray(size_t element_number, errorMods error_mod) {
    if (element_number <= 0) {
         return std::tuple<size_t, short unsigned int> {0, 0};
    } else if (element_number > this->_element_number) {
        displayLengthError(error_mod, "Not enough elements. Current element number is : '" + 
                           std::string(1,  this->_element_number) + "'. Got : " + std::string(1, element_number), __FILE__, __func__);
    }
    float f_element_size = this->_element_size; // Convert in float in order to allow division with a remainder

    size_t position_in_array = (f_element_size / 8) * element_number * 1000; // *1000 Permet d'avoir un int quoi qu'il arrive (a / 8 = n.xxx donc *100 nxxx.0)
    size_t char_position = position_in_array / 1000;

    float block_position_in_char = getFirstDigits(position_in_array, 3);

    return std::tuple<size_t, short unsigned int> {char_position, block_position_in_char / 1000 * 8};
}

size_t BitVector::getElementNumber(size_t char_position, short unsigned int block_position_in_char, errorMods error_mod) {
    if (char_position <= 0 && block_position_in_char <= 0) {
        return 0;
    } 
    
    if (block_position_in_char >= 8) {
        displayLengthError(error_mod, "Illegal block_position_in_char. Block position should be lower than 8. Got : "  + std::to_string(block_position_in_char), __FILE__, __func__);
    } else if (char_position > BitVector::maximalInternalSize()) {
        displayLengthError(error_mod, "Maximum value reached for element_number. element_number should be lower than " +  std::to_string(BitVector::maximalInternalSize()) + " (BitVector::maximalInternalSize) Got : " + std::to_string(char_position), __FILE__, __func__);
    }  
   
    float f_block_position_in_char = block_position_in_char; // Convert in float in order to allow division with a remainder
    f_block_position_in_char = (f_block_position_in_char / 8.0) * 1000;   // Position score due to \p block_position_in_char

    size_t position_in_array = char_position * 1000 + f_block_position_in_char; // Position score due to \p block_position_in_char and \p char_position 

    float f_element_size = this->_element_size; // Convert in float in order to allow division with a remainder
    size_t element_length = (f_element_size / 8.0) * 1000 ;  // position score of one element 

    position_in_array = position_in_array / element_length;

    return position_in_array;  // Number of element
 }   

size_t BitVector::getDataSize() {
    return this->_data_size;
}

size_t BitVector::getElementNumber() {
    return this->_element_number;
}

size_t BitVector::getCurrentCapacity() {

    // size_t number_of_block this->_data_size - 
    // return this->getElementNumber(this-);

    return 0;
}

size_t BitVector::size() {
    return this->_element_number;
}

void BitVector::resize(size_t data_size) {
    std::cout << data_size << std::endl;
}

void BitVector::doubleSize() {
    if (this->_data_size < BitVector::maximalInternalSize() / 2) {;
        this->resize(this->_data_size * 2);

    } else {
        this->resize(BitVector::maximalInternalSize());
    }
}

// size_t BitVector::maximumElementNumber() {
//     if (this->_element_size <= 8) {
//         // The limiting factor is size_t capacity
//         return this->maximalInternalSize();
//     }

//     // When do a block stop at the end of an octet ? 
//     //      When the number of bit used is a multiple of 8.
//     //  <=> When last bit is in position _element_size * 8.
//     size_t number_of_element = this->maximalInternalSize() / (this->_element_size * 8)
//     size_t number_of_potentially_not_full_octets = this->maximalInternalSize() - (number_of_element * (this->_element_size * 8))

//     short unsigned int bit_number_since_last_full_element = 0;
//     short unsigned int bit_left_in_current_octet = 8;

//     while (number_of_potentially_not_full_octets > 0) {
//         bit_left_in_current_octet -= 1;
//         bit_number_since_last_full_element += 1;

//         if (bit_left_in_current_octet == 0) {
//             bit_left_in_current_octet = 8;
//             number_of_potentially_not_full_octets -= 1
//         }

//         if (bit_number_since_last_full_element == this->_element_size) {
//             number_of_element += 1;
//         }
//     }
    
//     return number_of_element;
//     // The limiting factor is _data capacity
    
// }

size_t BitVector::maximalInternalSize() {
    // Assure que la partie decimale sera accessible
    return SIZE_MAX / 1000;
}

size_t BitVector::extractPosition(size_t position_in_data, short unsigned int position_in_char) {
    /* Extract the number of elements :
    * To do so, we group element inside block of full octet. 
    *    --> With (this->_element_size == 5) :
    *       A block of full octet
    *
    *
    */ 

    // how many element in an octet ?
    float number_of_element_per_octet = 8.0 / this->_element_size;
    

    // size_t number_of_element = position_in_data / (this->_element_size * 8)
    // size_t number_of_potentially_not_full_octets = position_in_data - (number_of_element * (this->_element_size * 8))

    // short unsigned int bit_number_since_last_full_element = 0;
    // short unsigned int bit_left_in_current_octet = 8;

    // while (number_of_potentially_not_full_octets > 0) {
    //     bit_left_in_current_octet -= 1;
    //     bit_number_since_last_full_element += 1;

    //     if (bit_left_in_current_octet == 0) {
    //         bit_left_in_current_octet = 8;
    //         number_of_potentially_not_full_octets -= 1
    //     }

    //     if (bit_number_since_last_full_element == this->_element_size) {
    //         number_of_element += 1;
    //     }
    // }
    return position_in_data +position_in_char + number_of_element_per_octet ;
}