#include "BitVector.hpp"
#include "Utilities.hpp"
#include <map>
#include <string>

// TODO: Proteger les taleaux des copies

// --- --- Constructors --- ---
BitVector::BitVector(short unsigned int block_size) {
    this->_element_size = block_size;

    this->resize(100);
}

// --- --- Destructor --- ---
BitVector::~BitVector() {
    this->_killInternalData();
}

void BitVector::_killInternalData() {
    if (this->_data == NULL) {
        return ;
    }
    this->_data_size = 0;
    delete [] _data;

}


// --- --- Getters --- ---
size_t BitVector::getDataSize() {
    return this->_data_size;
}

// size_t BitVector::getElementNumber() {
//     return this->_element_number + 1;
// }

// size_t BitVector::size() {
//     return this->_element_number + 1;
// }



// --- --- Utilities --- --- 
void BitVector::doubleSize() {
    if (maxSizeIsReached()) {
        displayLengthError(raise, "Maximal size reached, unable to upsize.", __FILE__, __func__);
        return ;
    }

    if (this->_data_size < (this->maxOctetNumber()) / 2) {;
        this->resize(this->_data_size * 2);

    } else {
        this->resize(this->maxOctetNumber());
    }

    
}

void BitVector::resize(size_t data_size) {
 
    if (data_size == 0) {
        this->_killInternalData ();
        return ;

    } else if (data_size > this->maxOctetNumber()) {
         displayLengthError(raise, "Maximal size reached " + std::to_string(data_size) + " > " + std::to_string(this->maxOctetNumber())  +  " unable to proceed.", __FILE__, __func__);
    }
 
    char * new_tab = new char[data_size];

    for (size_t i=0; i <= data_size - 1; i++) {
        if (i <= this->_data_size && this->_data != NULL) {
            new_tab[i] = _data[i];

        } else {
            new_tab[i] = 0b00000000;
        }
    }
         
    // TODO: Recalculer le nombre d'elements à l'interieur de new_tab quand old_size > new_size

    this->_killInternalData ();
    this->_data_size = data_size;
    this->_data = new_tab;
    
}


size_t BitVector::maxOctetNumber() {
    return __SIZE_MAX__;
}

bool BitVector::maxSizeIsReached() {
    return (this->maxOctetNumber() == this->_data_size);
}



static std::map<char, size_t> searchElement(size_t data_size, short unsigned int element_size, size_t octet_position, short unsigned int  bit_position, bool (*func)(const std::map<char, size_t> &)) {
    // float temp = 1.0 / 3.0;
    // float a = 0;
    // float b = 0;
    // float temp2;
    // std::cout << temp * 3 <<  " " << temp * 3.0 + 1.0 / 10.0 << std::endl; 
    // short unsigned int i = 1;
    // float j = 1;
    // while (i != 0) {
    //     i+=1;
    //     j+=1;
    //     b = j;
    //     a = 8;
    //     temp = a / b;
    //     temp2 = (1.0 / temp * a);
    //     std::cout << "Bool=" << (temp2==j) << " " << temp2 << " " << j  << " "<< (j == i)<< " "<< (unsigned int)(temp2) <<std::endl;
    // }
    // std::cout << 1.0 / 3 * 3  <<std::endl;

    // Loop 
    short unsigned int item_remaining_bit = element_size;
    size_t element_number = 0;
    bool stop = false;
    std::map<char, size_t> f_map ;

    if (data_size == 0) {
        displayLengthError(raise, "Too small array. Can not proceed.", __FILE__, __func__);
    }

    while((octet_position < data_size - 1 || bit_position >= 8) && stop == false) {
        if (bit_position >= 8 && octet_position < data_size - 1) { 
            // New octet reached
            bit_position = 0;
            octet_position += 1;
        }
        
        if (item_remaining_bit >= bit_position) {
            item_remaining_bit -= bit_position;
            bit_position = 0;
        
        } else /*octet_remaining_capacity > item_remaining_bit*/  {
            bit_position -= item_remaining_bit;
            item_remaining_bit = 0;
        } 

        if (item_remaining_bit == 0) {
            item_remaining_bit = element_size;
            element_number += 1;
            f_map['C'] = true;

        } else {
            f_map['C'] = false;
        }

        f_map['B'] = bit_position;
        f_map['O'] = octet_position;
        f_map['R'] = item_remaining_bit;
        f_map['N'] = element_number;

        if (func != NULL) {
            stop = func(f_map);
        }
    }

    return  f_map;
}

std::map<char, size_t> BitVector::searchElement(size_t data_size, short unsigned int element_size, bool (*func)(const std::map<char, size_t> &)) {
    return BitVector::searchElement(data_size, element_size, 0, 0, func);
}


std::map<char, size_t> BitVector::searchElement(bool (*func)(const std::map<char, size_t> &)) {
    return BitVector::searchElement(this->_data_size, this->_element_size, func);
}
