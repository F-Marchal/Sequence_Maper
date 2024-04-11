#include "BitVector.hpp"
#include "Utilities.hpp"
#include <map>
#include <string>
#include <vector>

// TODO: Proteger les taleaux des copies

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- Coords --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// --- --- Constructor --- ---
BitVector::Coords::Coords() {
    this->setBit(0);
    this->setOctet(0);
}

BitVector::Coords::Coords(size_t octet, unsigned short int bit) {
    this->setBit(bit);
    this->setOctet(octet);
}

BitVector::Coords::Coords(size_t value) {
    this->setSize_t(value);
}

// --- --- Conversion --- ---
size_t BitVector::Coords::toSize_t() const {
    return this->octet * 1000 + (this->bit * 1000 / 8.0);
}

std::string BitVector::Coords::toString() const {
    return "(O=" + std::to_string(this->octet) + " ; B=" + std::to_string(this->bit) + ")";
}

// --- --- Getters and setters --- ---
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

void BitVector::Coords::setSize_t(size_t number) {
    size_t octet_number = number / 1000;
    unsigned short int bit_number = (number - (octet_number * 1000)) * 8 / 1000;
    this->setBit(bit_number);
    this->setOctet(octet_number);
}

void BitVector::Coords::setSize_t(const BitVector::Coords & coord) {
    this->setSize_t(coord.toSize_t());
}

// --- --- Limitations --- ---
size_t BitVector::Coords::maximumOctetNumber() {
    return BitVector::maximumOctetNumber();
}

size_t BitVector::Coords::maximumSize_t() {
    return BitVector::maximumOctetNumber() * 1000 + (7 * 1000 / 8);
}

// --- --- operators --- ---

bool BitVector::Coords::operator==(const BitVector::Coords & other) const {
    return (this->octet == other.getOctet() && this->bit == other.getBit()) ;
}

bool BitVector::Coords::operator!=(const BitVector::Coords & other) const {
    return !(*this==other);
}

bool BitVector::Coords::operator>(const BitVector::Coords & other) const {
    return (this->octet > other.getOctet() || (this->octet == other.getOctet() && this->bit > other.getBit()));
}

bool BitVector::Coords::operator>=(const BitVector::Coords & other) const {
    return (this->octet > other.getOctet() || (this->octet == other.getOctet() && this->bit >= other.getBit()));
}

bool BitVector::Coords::operator<(const BitVector::Coords & other) const {
    return (this->octet < other.getOctet() || (this->octet == other.getOctet() && this->bit < other.getBit()));
}

bool BitVector::Coords::operator<=(const BitVector::Coords & other) const {
    return (this->octet < other.getOctet() || (this->octet == other.getOctet() && this->bit <= other.getBit()));
}

BitVector::Coords & BitVector::Coords::operator*=(size_t value) {
    this->setSize_t(*this * value);
    return *this;
}

BitVector::Coords & BitVector::Coords::operator/=(size_t value) {
    this->setSize_t(*this / value);
    return *this;
}

BitVector::Coords & BitVector::Coords::operator+=(const BitVector::Coords & other) {
    this->setSize_t(*this + other);
    return *this;
}

BitVector::Coords & BitVector::Coords::operator-=(const BitVector::Coords & other) {
    this->setSize_t(*this - other);
    return *this;
}

BitVector::Coords BitVector::Coords::operator+(const BitVector::Coords & other) {
    if (!this->canBeAddedBy(other)) {
        displayLengthError(raise, "Can not proceed this sum, maximum size would be reached", __FILE__, __func__);
    }
    std::cout << "  -  " << other << this->toString() <<other.toSize_t() << " "<<  this->toSize_t()<< std::endl;
    return Coords(other.toSize_t() + this->toSize_t());
}

BitVector::Coords BitVector::Coords::operator-(const BitVector::Coords & other) {
    if (!this->canBeSubtractedBy(other))  {
        displayLengthError(raise, "Can not proceed this subtraction, a negative number would be reached", __FILE__, __func__);
    }
    return Coords(other.toSize_t() - this->toSize_t());
}

BitVector::Coords BitVector::Coords::operator*(size_t value) {
    value = value * (1000 / 8);
    Coords final_coord;

    if (value == 0) {
        // Avoid division by 0 in the next condition
        final_coord.setSize_t(value);

    } else if (!this->canMultiplyBy(value)) {
        // The result will be greater than .
        displayLengthError(raise, "Can not proceed this multiplication, maximum size would be reached", __FILE__, __func__);

    } else {
            final_coord.setSize_t(value * this->toSize_t());
    }

    return final_coord;
}

BitVector::Coords BitVector::Coords::operator/(size_t value) {
    value =  value * (1000 / 8);
    return Coords(this->toSize_t() / value);
}

BitVector::Coords& BitVector::Coords::operator++() {
    this->increment();
    return *this;
}

BitVector::Coords BitVector::Coords::operator++(int) {
    Coords temp(this->getOctet(), this->getBit());
    this->increment();
    return temp;
}

BitVector::Coords& BitVector::Coords::operator--() {
    this->decrement();
    return *this;
}

BitVector::Coords BitVector::Coords::operator--(int) {
    Coords temp(this->getOctet(), this->getBit());
    this->decrement();
    return temp;
}

void BitVector::Coords::increment() {
    if (this->bit == 7) {
        this->setBit(0);
        this->setOctet(this->octet + 1);

    } else {
        this->setBit(this->bit + 1);
    }
}

void BitVector::Coords::decrement() {
    if (this->bit == 0) {
        this->setBit(7);
        this->setOctet(this->octet - 1);

    } else {
        this->setBit(this->bit - 1);
    }
}

bool BitVector::Coords::canBeAddedBy(const Coords & other) const {
    return (this->maximumSize_t() - this->toSize_t() > other.toSize_t());  
}

bool BitVector::Coords::canBeSubtractedBy(const Coords & other) const {
    return (other.toSize_t() > this->toSize_t());  
}

bool BitVector::Coords::canMultiplyBy(size_t value) {
    return (this->toSize_t() <= this->maximumSize_t() / value);
}
// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- BitVector --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// --- --- Constructors --- ---
BitVector::BitVector(short unsigned int block_size, size_t alloc) {
    if (block_size == 0) {
        displayInvalidArgument(raise, "Element size should be greater than 0. (Got 0.)", __FILE__, __func__);
    }
    this->_element_number = 0;
    this->_element_size = block_size;
    this->resize(alloc);
}

void BitVector::setElementNumber(size_t number) {
    if (number > currentElementCapacity()) {
        displayLengthError(raise, "Current maximal element capacity is " + std::to_string(currentElementCapacity()) + ". Can not set _element_number to " + std::to_string(number), __FILE__, __func__);
    }
    this->_element_number = number;
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
size_t BitVector::getDataSize()  const {
    return this->_data_size;
}

size_t BitVector::getElementNumber() const  {
    return this->_element_number;
}

size_t BitVector::size() const  {
    return this->getElementNumber();
}

size_t BitVector::currentElementCapacity() const {
    return this->indexCoordinate(this->lastBit(), ignore);
}

size_t  BitVector::currentCapacity() const {
    return this->indexCoordinate(BitVector::Coords(this->_data_size , 0)); 
}
BitVector::Coords  BitVector::lastBit() const {
    return Coords(this->_data_size, 7); 
}
    

// --- index ---

size_t BitVector::indexCoordinate(const Coords & coord, errorMods strictness) const  {
    std::tuple<size_t, size_t, size_t> untread_coord = this->indexCoordinateUntreated(coord);
    
    if (std::get<2>(untread_coord)!= 0) {
        displayDomainError(strictness, "Coordinate does not strictly match with any element. Got bit left" + std::to_string(std::get<2>(untread_coord) * 8 / 1000), __FILE__, __func__);
    }

    return std::get<0>(untread_coord);
}

std::tuple<size_t, size_t, size_t> BitVector::indexCoordinateUntreated(const Coords & coord) const  {
    size_t element = this->getSize_tUnit();
    size_t octet_number = coord.toSize_t();
    
    // Use the power of division to retrieve how much element can be stuffed intoo octet_number
    size_t number_of_elements = octet_number / element;
    size_t really_used_octet = number_of_elements * element;
    size_t unused_octet = octet_number - really_used_octet;

    return std::tuple<size_t, size_t, size_t> {number_of_elements, really_used_octet, unused_octet} ;
}

BitVector::Coords BitVector::indexElement(size_t element)  const {
    return Coords(indexElementUntreated(element));
}

size_t BitVector::indexElementUntreated(size_t element)  const {
    if (element > this->maxElementLimit()) {
        displayInvalidArgument(raise, "\\p element should be smaller than maxElementLimit(). Got : " 
                                + std::to_string(element) + " > " + std::to_string(this->maxElementLimit()), __FILE__, __func__);
        element = this->maxElementLimit();
    }

    // Elements
    return getSize_tUnit() * element ;
}

BitVector::Coords BitVector::getCoordUnit() const  {
    unsigned short int octet_per_element = this->_element_size / 8;  
    unsigned short int bit_per_element = this->_element_size - (octet_per_element * 8);  

    return BitVector::Coords(octet_per_element, bit_per_element);
} 

size_t BitVector::getSize_tUnit() const  {
    return getCoordUnit().toSize_t();
}

BitVector::Coords BitVector::start() const  {
    return Coords(0, 0);
}

BitVector::Coords BitVector::end() const  {
    return getCoordUnit() * this->_element_number;
}

// --- --- Utilities --- --- 
void BitVector::doubleSize() {
    if (this->maxSizeIsReached()) {
        displayLengthError(raise, "Maximal size reached, unable to upsize.", __FILE__, __func__);
        return ;
    }
    size_t element_capacity = this->currentElementCapacity();
    if (element_capacity < (this->maxElementLimit()) / 2) {;
        this->resize(element_capacity * 2);

    } else {
        this->resize(this->maxElementLimit());
    }

    
}

void BitVector::resize(size_t element_capacity) {
    size_t new_data_size = this->indexElement(element_capacity).getOctet() + 1;
    
    if (new_data_size == 0) {
        this->_killInternalData ();
        return ;

    } else if (new_data_size == this->_data_size) {
        return ;

    } else if (new_data_size > this->maxOctetLimit()) {
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
        this->_element_number = (new_data_size * 1000 + (1000 / 8)) / this->getSize_tUnit();
    }

    this->_killInternalData ();
    this->_data_size = new_data_size;
    this->_data = new_tab;


    
}

void BitVector::shrink() {
    // Extract number of octet needed and resize data.
    this->resize(this->_element_number * this->getSize_tUnit() / 1000) ;
}

void BitVector::clear() {
    this->resize(0);
}

BitVector::Coords BitVector::MaximalCoordLimit() const {
    return Coords(this->maxElementLimit() * this->getSize_tUnit());
} 

size_t BitVector::maxOctetLimit()  const {
    return this->MaximalCoordLimit().getOctet();
}

size_t BitVector::maxElementLimit() const  {
    return std::min(this->maximumOctetNumber() / this->getSize_tUnit(), this->maximumElementNumber());
}

bool BitVector::maxDataSizeIsReached() const  {
    return (this->maxOctetLimit() <= this->_data_size);
}

bool BitVector::maxElementSizeIsReached() const  {
    return (this->maxElementLimit() <= this->_element_number);
}

bool BitVector::maxSizeIsReached()  const {
    return (this->maxDataSizeIsReached() || this->maxElementSizeIsReached());
}

size_t BitVector::maximumOctetNumber() {
    return __SIZE_MAX__ / 1000 - 1;
}

size_t BitVector::maximumElementNumber() {
    return __SIZE_MAX__ - 1;
}


void BitVector::copyBits(const char * pattern, char * final_list, const BitVector::Coords element,  BitVector::Coords pattern_coord, BitVector::Coords final_coord, bool final_end_is_right, bool pattern_end_is_right) {
    BitVector::Coords pattern_end_coord = pattern_coord + element;
    BitVector::Coords final_end_coord = final_coord + element;
    BitVector::Coords step_left = element;

    short unsigned int pattern_bit_value;
    short unsigned int final_list_bit_value;

    char pattern_bit;
    char final_mask;
    std::cout << final_end_coord << element << std::endl;
    while (final_coord != final_end_coord) {
     
        if (final_end_is_right && final_coord.getOctet() == final_end_coord.getOctet()) {
            final_list_bit_value = step_left.getBit();
        } else {
            final_list_bit_value = 7 - final_coord.getBit();
        }

        if (pattern_end_is_right && pattern_coord.getOctet() == pattern_end_coord.getOctet()) {
            pattern_bit_value = step_left.getBit();
        } else {
            pattern_bit_value = 7 - pattern_coord.getBit();
        }
        
        pattern_bit = 1 << pattern_bit_value;
        final_mask = 1 << final_list_bit_value;

        if (pattern[pattern_coord.getOctet()] & pattern_bit) {
            final_list[final_coord.getOctet()] |= final_mask; 

        } else {
            final_list[final_coord.getOctet()] &= ~final_mask;
        }
        
        final_coord++;
        pattern_coord++;
        step_left --;
    }
}

void BitVector::copyBits(const char * pattern, char * final_list,  BitVector::Coords pattern_coord, BitVector::Coords final_coord, bool final_end_is_right, bool pattern_end_is_right) {
    BitVector::copyBits( pattern, final_list, this->getCoordUnit(), pattern_coord, final_coord, final_end_is_right, pattern_end_is_right);
}
bool BitVector::get( BitVector::Coords coord) const {
    char mask = 1 << coord.getBit();
    if (this->_data[coord.getOctet()] & mask) {
        return true;
    }
    return false;
}

bool BitVector::operator[]( BitVector::Coords coord) const {
    return this->get(coord);
}

char * BitVector::get(size_t index) const {
    if (index > this->_element_number) {
        displayLengthError(raise, "Maximum length reached : " + std::to_string(index) + " > " + std::to_string(this->_element_number) + ".", __FILE__, __func__);
    }
    BitVector::Coords start = this->indexElement(index);
    BitVector::Coords element = this->getCoordUnit();
    char * to_tab = new char[this->_element_size / 8 + 1 ];
    std::cout <<start << " " << this->getCoordUnit() << " " << this->_element_size / 8 + 1 << " " << sizeof(to_tab) <<std::endl;
    BitVector::copyBits(this->_data, to_tab, element, start, BitVector::Coords(), false, true);
    return to_tab;
}   

char * BitVector::operator[](size_t index) const {
    return this->get(index);
}

void BitVector::set(size_t index, char * tab, bool restrictions) {
    Coords coord = this->indexElement(index);
     std::cout << std::endl;
    displayBits((char)tab[0]);
    while (coord > this->lastBit()) {
        this->doubleSize();
    }
    
    if (restrictions && coord > this->end()) {
        displayLengthError(raise, "Invalid coordinates, last element position exceed : " + coord.toString() + " > " + this->end().toString(), __FILE__, __func__);
    }
    
    bool push_limit = (coord == this->end());
    
    std::cout << this->getCoordUnit()<< Coords(0, 0) << " _" <<coord<< "_" <<std::endl;
    BitVector::copyBits(tab, this->_data, Coords(0, 0), coord, false, true);
 
    if (push_limit) {
        this->_element_number += 1;
    }
    displayBits((char)this->_data[0]);
    displayBits((char)this->_data[1]);
    // for (long unsigned int i = 0; i < sizeof(this->_data); i++) {
    //     displayBits((char)this->_data[i]);
    // }
}

void BitVector::set(size_t index, char value, bool restrictions) {
    char * temp_tab = new char[1] {value};
    this->set(index, temp_tab, restrictions);

    delete [] temp_tab;
}

void BitVector::set(Coords coord, bool value, bool restrictions) {
    while (coord > this->lastBit()) {
        this->doubleSize();
    }

    if (restrictions && coord > this->end()) {
        displayLengthError(raise, "Invalid coordinates, last element position exceed : " + coord.toString() + " > " + this->lastBit().toString(), __FILE__, __func__);
    }

    char mask = 1 << coord.getBit();
    if (value) {
        this->_data[coord.getOctet()] |= mask;
    } else {
        this->_data[coord.getOctet()] &= ~mask;
    }
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
