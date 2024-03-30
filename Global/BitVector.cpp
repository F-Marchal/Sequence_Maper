#include "BitVector.hpp"
#include "Utilities.hpp"
#include <map>
#include <string>
#include <vector>
// TODO: Proteger les taleaux des copies

BitVector::Coords::Coords() {
    this->setBit(0);
    this->setOctet(0);
}

BitVector::Coords::Coords(size_t octet, unsigned short int bit) {
    this->setBit(bit);
    this->setOctet(octet);
}

BitVector::Coords::Coords(size_t value) {
    size_t octet_number = value / 1000;
    unsigned short int bit_number = (value - (octet_number * 1000)) * 8 / 1000;
    this->setBit(bit_number);
    this->setOctet(octet_number);
}

size_t BitVector::Coords::toSize_t() const {
    return this->octet + (this->bit * 1000 / 8.0);
}

std::string BitVector::Coords::toString() const {
    return "(O=" + std::to_string(this->octet) + " ; B=" + std::to_string(this->bit) + ")";
}

unsigned short int BitVector::Coords::getBit() const {
    return this->bit;
}

size_t BitVector::Coords::getOctet() const {
    return this->octet;
}

void BitVector::Coords::setOctet(size_t octet) {
    if (octet > this->maximumOctetNumber()) {
        displayInvalidArgument(raise, "\\p octet should be smaller than maximumOctetNumber(). Got : " 
                                + std::to_string(octet) + " > " + std::to_string(this->maximumOctetNumber()), __FILE__, __func__);
        octet = this->maximumOctetNumber();
    }

    this->octet = octet;
}

void BitVector::Coords::setBit(unsigned short int bit) {
    if (bit >= 8) {
        displayInvalidArgument(raise, "\\p bit should be strictly lower than 8. Got : " 
                                + std::to_string(bit), __FILE__, __func__);
        bit = 7;
    }
    this->bit = bit;
}

size_t BitVector::Coords::maximumOctetNumber() {
    return BitVector::maximumOctetNumber();
}


// --- --- Constructors --- ---
BitVector::BitVector(short unsigned int block_size) {
    if (block_size == 0) {
        displayInvalidArgument(raise, "Element size should be greater than 0. (Got 0.)", __FILE__, __func__);
    }
    std::cout << block_size << std::endl;
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

size_t BitVector::getElementNumber() {
    return this->_element_number;
}

size_t BitVector::size() {
    return this->getElementNumber();
}





// --- index ---

size_t BitVector::indexCoordinate(const Coords & coord, errorMods strictness) {
    std::tuple<size_t, size_t, size_t> untread_coord = this->indexCoordinateUntreated(coord);
    
    if (std::get<2>(untread_coord)!= 0) {
        displayDomainError(strictness, "Coordinate does not strictly match with any element. Got bit left" + std::to_string(std::get<2>(untread_coord) * 8 / 1000), __FILE__, __func__);
    }

    return std::get<0>(untread_coord);
}

std::tuple<size_t, size_t, size_t> BitVector::indexCoordinateUntreated(const Coords & coord) {
    size_t element = this->getCoordUnit().toSize_t();
    size_t octet_number = coord.toSize_t();
    
    // Use the power of division to retrieve how much element can be stuffed intoo octet_number
    size_t number_of_elements = octet_number / element;
    size_t really_used_octet = number_of_elements * element;
    size_t unused_octet = octet_number - really_used_octet;

    return std::tuple<size_t, size_t, size_t> {number_of_elements, really_used_octet, unused_octet} ;
}

BitVector::Coords BitVector::indexElement(size_t element) {
    return Coords(indexElementUntreated(element));
}

size_t BitVector::indexElementUntreated(size_t element) {
    if (element > this->upperElementLimit()) {
        displayInvalidArgument(raise, "\\p element should be smaller than upperOctetLimit(). Got : " 
                                + std::to_string(element) + " > " + std::to_string(this->upperElementLimit()), __FILE__, __func__);
        element = this->upperElementLimit();
    }

    // Elements
    return getCoordUnit().toSize_t() * element ;
    
}

BitVector::Coords BitVector::getCoordUnit() {
    unsigned short int octet_per_element = this->_element_size / 8;  
    unsigned short int bit_per_element = this->_element_size - (octet_per_element * 8);  

    return BitVector::Coords(octet_per_element, bit_per_element);
} 


// --- --- Utilities --- --- 
void BitVector::doubleSize() {
    if (maxSizeIsReached()) {
        displayLengthError(raise, "Maximal size reached, unable to upsize.", __FILE__, __func__);
        return ;
    }

    if (this->_data_size < (this->upperOctetLimit()) / 2) {;
        this->resize(this->_data_size * 2);

    } else {
        this->resize(this->upperOctetLimit());
    }

    
}

void BitVector::resize(size_t new_data_size) {
 
    if (new_data_size == 0) {
        this->_killInternalData ();
        return ;

    } else if (new_data_size == this->_data_size) {
        return ;

    } else if (new_data_size > this->upperOctetLimit()) {
         displayLengthError(raise, "Maximal size reached " + std::to_string(new_data_size) + " > " + std::to_string(this->maximumOctetNumber())  +  " unable to proceed.", __FILE__, __func__);
    }

    char * new_tab = new char[new_data_size];

    for (size_t i=0; i <= new_data_size - 1; i++) {
        if (i <= this->_data_size && this->_data != NULL) {
            new_tab[i] = _data[i];

        } else {
            new_tab[i] = 0b00000000;
        }
    }
    
    if (this->_data_size > new_data_size) {
        this->_element_number = (new_data_size * 1000 + (1000 / 8)) / this->getCoordUnit().toSize_t();
    }

    this->_killInternalData ();
    this->_data_size = new_data_size;
    this->_data = new_tab;
    
}

void BitVector::shrink() {
    // Extract number of octet needed and resize data.
    this->resize(this->_element_number * this->getCoordUnit().toSize_t() / 1000) ;
}

size_t BitVector::upperOctetLimit() {
    return this->upperElementLimit() * this->getCoordUnit().toSize_t();
}

size_t BitVector::upperElementLimit() {
    return std::min(this->maximumOctetNumber() / this->getCoordUnit().toSize_t(), this->maximumElementNumber());
}

bool BitVector::maxDataSizeIsReached() {
    return (this->upperOctetLimit() <= this->_data_size);
}

bool BitVector::maxElementSizeIsReached() {
    return (this->upperElementLimit() <= this->_element_number);
}

bool BitVector::maxSizeIsReached() {
    return (this->maxDataSizeIsReached() || this->maxElementSizeIsReached());
}

size_t BitVector::maximumOctetNumber() {
    // TODO: Garder le max de la puissance
    return __SIZE_MAX__ / 1000 - 1;
}

size_t BitVector::maximumElementNumber() {
    return __SIZE_MAX__ - 1;
}




// std::map<char, size_t> BitVector::searchElement(size_t data_size, short unsigned int element_size, size_t octet_position, short unsigned int  bit_position, bool (*func)(const std::map<char, size_t> &)) {
//     // float temp = 1.0 / 3.0;
//     // float a = 0;
//     // float b = 0;
//     // float temp2;
//     // std::cout << temp * 3 <<  " " << temp * 3.0 + 1.0 / 10.0 << std::endl; 
//     // short unsigned int i = 1;
//     // float j = 1;
//     // while (i != 0) {
//     //     i+=1;
//     //     j+=1;
//     //     b = j;
//     //     a = 8;
//     //     temp = a / b;
//     //     temp2 = (1.0 / temp * a);
//     //     std::cout << "Bool=" << (temp2==j) << " " << temp2 << " " << j  << " "<< (j == i)<< " "<< (unsigned int)(temp2) <<std::endl;
//     // }
//     // std::cout << 1.0 / 3 * 3  <<std::endl;

//     // Loop 
//     short unsigned int item_remaining_bit = element_size;   // Represent the number of bit that we should find to have a full element
//     size_t element_number = 0;                              // Represent the number of full element found.
//     bool stop = false;                                      // Do the loop should stop. This variable is modified by \p func in order to 'break' the loop.
    
//     std::map<char, size_t> f_map ;                          // A map that will be returned. Also used by \p func.

//     if (data_size == 0) {
//         displayLengthError(raise, "Too small array (0 items). Can not proceed.", __FILE__, __func__);
//     }

//     while((octet_position < data_size - 1 || bit_position >= 8) && stop == false) {
        
//         if (bit_position >= 8 && octet_position < data_size - 1) { 
//             // New octet reached
//             bit_position = 0;
//             octet_position += 1;
//         }
        
//         // Advance in the analyze.
//         if (item_remaining_bit >= 8 - bit_position) {
//             item_remaining_bit -= 8 - bit_position;
//             bit_position = 8;
        
//         } else /*8 - bit_position > item_remaining_bit*/  {
//             bit_position += item_remaining_bit;
//             item_remaining_bit = 0;
//         } 

//         // Did we find a new element ?
//         if (item_remaining_bit == 0) {
//             item_remaining_bit = element_size;
//             element_number += 1;
//             f_map['C'] = true;

//             f_map['S'] = f_map['E'];
//             f_map['T'] = f_map['F'];
//             f_map['E'] = octet_position;
//             f_map['F'] = bit_position;

//         } else {
//             f_map['C'] = false;
//         }

//         // This is very likely to be inefficient BUT I do believe that this improve readability. |
//         // Alternative could be to :                                                             |
//         //      - replace all vars and only use the dict                                         |
//         //      - only fill the dict if (func != NULL) and at the end of the loop                |
//         f_map['B'] = bit_position;          //                                                   |
//         f_map['O'] = octet_position;        //                                                   |
//         f_map['R'] = item_remaining_bit;    //                                                   |
//         f_map['N'] = element_number;        //                                                   |
//         // ------------------------------------------------------------------------------------- |

//         // Call func
//         if (func != NULL) {
//             stop = func(f_map);
//         }
//     }

//     return  f_map;
// }

// std::map<char, size_t> BitVector::searchElement(size_t data_size, short unsigned int element_size, bool (*func)(const std::map<char, size_t> &)) {
//     return BitVector::searchElement(data_size, element_size, 0, 0, func);
// }


// std::map<char, size_t> BitVector::searchElement(bool (*func)(const std::map<char, size_t> &)) {
//     return BitVector::searchElement(this->_data_size, this->_element_size, func);
// }
