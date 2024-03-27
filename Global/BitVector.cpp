#include "BitVector.hpp"
#include "Utilities.hpp"
#include <map>
#include <string>

// TODO: Proteger les taleaux des copies

// --- --- Constructors --- ---
BitVector::BitVector(short unsigned int block_size) {
    if (block_size == 0) {
        displayInvalidArgument(raise, "Element size should be greater than 0. (Got 0.)", __FILE__, __func__);
    }

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
size_t BitVector::indexCoordinate(size_t octet, unsigned short int bit, errorMods strictness) {
    std::tuple<size_t, size_t, size_t> coord = this->indexUntreatedCoordinate(octet, bit);
    
    if (strictness) {
        // TODO:
    }

    return std::get<0>(coord);
}

std::tuple<size_t, size_t, size_t> BitVector::indexUntreatedCoordinate(size_t octet_number, unsigned short int bit) {
    unsigned short int element_size = this->_element_number;

    if (octet_number > BitVector::maximumOctetNumber()) {
        displayInvalidArgument(raise, "\\p octet_number is too large : " + std::to_string(octet_number) + " > " + std::to_string(BitVector::maximumOctetNumber()), __FILE__, __func__);
        return std::tuple<size_t, size_t, size_t> {0, 0, 0} ;

    } else if (element_size <= 0) {
        displayInvalidArgument(raise, "\\p element_size should be greater than 0. Got : " + std::to_string(element_size), __FILE__, __func__);
        return std::tuple<size_t, size_t, size_t> {0, 0, 0} ;
    
    } else if (octet_number > this->upperOctetLimit()) {
        // TODO: > or >=
        displayInvalidArgument(raise, "\\p octet_number should be smaller than upperOctetLimit(). Got : " 
                                + std::to_string(octet_number) + " > " + std::to_string(this->upperOctetLimit()), __FILE__, __func__);
        return std::tuple<size_t, size_t, size_t> {0, 0, 0} ;
    } 
    

    // Transform \p octet_number
    octet_number = octet_number * 1000 + ((bit / 8.0) * 1000);

    // Extract number of octet that can be filled by a unique element.
    unsigned short int uncompleted_octet_per_element = element_size / 8;  
    unsigned short int bit_per_element = element_size - uncompleted_octet_per_element * 8;  

    size_t octet_per_element = uncompleted_octet_per_element * 1000 + (bit_per_element / 8.0) * 1000;

    // Use the power of division to retrieve how much can be stuffed intoo octet_number
    size_t number_of_elements = octet_number / octet_per_element;
    size_t really_used_octet = octet_number / octet_per_element * octet_per_element;
    size_t unused_octet = octet_number - really_used_octet;

    return std::tuple<size_t, size_t, size_t> {number_of_elements, really_used_octet, unused_octet} ;
}
 


// --- limitations ---
// bool BitVector::stopFunctionGetMaximalNumberOfOctet(const std::map<char, size_t>& InfMap) {
//     return (InfMap.at('B') == maximumLength());
// }

// size_t BitVector::getMaximalNumberOfOctet() {
//     static std::map<short unsigned int, size_t> element_size_map;
//     if (this->_element_size <= 8) {

        
//         if (element_size_map.find(this->_element_size) == element_size_map.end()) { 
//             // This is the first time that this situation is encountered
//             // Let's count the number of element that can be filled inside this object until we reach the maximal number of octet.
           

//             std::map<char, size_t> research_result = this->searchElement(this->maximumLength(), this->_element_size, this->stopFunctionGetMaximalNumberOfOctet);
//             element_size_map[this->_element_size] = research_result['N'];
            

//         }

//         return element_size_map.at(_element_number);
//     } else {
//         // We might need all size_t value.
//         return this->maximumLength();;
//     }
   
// }

// bool BitVector::stopFunctionMaximalNumberOfElements(const std::map<char, size_t>& InfMap) {
//     return (InfMap.at('N') == maximumLength());
// }

// size_t BitVector::getMaximalNumberOfElements() {
//     // The following map store result of situation that require the usage of function with a complexity greater than O(1)
//     // in order to reduce time usage when getMaximalNumberOfElements is used multiple time by similar objects.
//     static std::map<short unsigned int, size_t> element_size_map;

//     if (this->_element_size <= 8) {
//         // The only limitation is the maximal value of size_t.
//         return this->maximumLength();

//     } else {
       
//         if (element_size_map.find(this->_element_size) == element_size_map.end()) { 
//             // This is the first time that this situation is encountered
//             // Let's count the number of element that can be filled inside this object until we reach the maximal number of octet.

//             std::map<char, size_t> research_result = this->searchElement(this->getMaximalNumberOfOctet(), this->_element_size, stopFunctionMaximalNumberOfElements);
//             element_size_map[this->_element_size] = research_result['B'];
//         }

//         return element_size_map.at(this->_element_size);
//     }
// }

// --- --- Utilities --- --- 
void BitVector::doubleSize() {
    if (maxSizeIsReached()) {
        displayLengthError(raise, "Maximal size reached, unable to upsize.", __FILE__, __func__);
        return ;
    }

    if (this->_data_size < (this->maximumOctetNumber()) / 2) {;
        this->resize(this->_data_size * 2);

    } else {
        this->resize(this->maximumOctetNumber());
    }

    
}

void BitVector::resize(size_t data_size) {
 
    if (data_size == 0) {
        this->_killInternalData ();
        return ;

    } else if (data_size > this->maximumOctetNumber()) {
         displayLengthError(raise, "Maximal size reached " + std::to_string(data_size) + " > " + std::to_string(this->maximumOctetNumber())  +  " unable to proceed.", __FILE__, __func__);
    }


    char * new_tab = new char[data_size];

    for (size_t i=0; i <= data_size - 1; i++) {
        if (i <= this->_data_size && this->_data != NULL) {
            new_tab[i] = _data[i];

        } else {
            new_tab[i] = 0b00000000;
        }
    }
    
    // TODO: Warning lost data this->_data_size > data_size

    this->_killInternalData ();
    this->_data_size = data_size;
    this->_data = new_tab;
    
}



size_t BitVector::upperOctetLimit() {
    // TODO: Finir
    return maximumOctetNumber();
}

size_t BitVector::upperElementLimit() {
    // TODO: Finir
    return maximumElementNumber();
}

bool BitVector::maxDataSizeIsReached() {
    return (this->upperOctetLimit() > this->_data_size);
}

bool BitVector::maxElementSizeIsReached() {
    return (this->upperElementLimit() > this->_element_number);
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
