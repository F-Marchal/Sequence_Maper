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
    return this->octet + (this->bit * 1000 / 8.0);
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
    return (other.toSize_t() > this->maximumSize_t() - this->toSize_t());  
}

bool BitVector::Coords::canBeSubtractedBy(const Coords & other) const {
    return (other.toSize_t() > this->toSize_t());  
}

bool BitVector::Coords::canMultiplyBy(size_t value) {
    return (this->toSize_t() <= this->maximumSize_t() / value);
}
// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- BitVector --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// --- --- Constructors --- ---
BitVector::BitVector(short unsigned int block_size) {
    if (block_size == 0) {
        displayInvalidArgument(raise, "Element size should be greater than 0. (Got 0.)", __FILE__, __func__);
    }
    this->_element_number = 0;
    this->_element_size = block_size;
    this->resize(2);

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
    if (element > this->upperElementLimit()) {
        displayInvalidArgument(raise, "\\p element should be smaller than upperOctetLimit(). Got : " 
                                + std::to_string(element) + " > " + std::to_string(this->upperElementLimit()), __FILE__, __func__);
        element = this->upperElementLimit();
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

BitVector::Coords BitVector::MaximalCoordLimit() const {
    return Coords(this->upperElementLimit() * this->getSize_tUnit());
} 

size_t BitVector::upperOctetLimit()  const {
    return this->MaximalCoordLimit().getOctet();
}

size_t BitVector::upperElementLimit() const  {
    return std::min(this->maximumOctetNumber() / this->getSize_tUnit(), this->maximumElementNumber());
}

bool BitVector::maxDataSizeIsReached() const  {
    return (this->upperOctetLimit() <= this->_data_size);
}

bool BitVector::maxElementSizeIsReached() const  {
    return (this->upperElementLimit() <= this->_element_number);
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


void BitVector::copyBits(const char * from, char * to_tab, const BitVector::Coords element_coord,  BitVector::Coords from_coord, BitVector::Coords to_coord, bool from_right, bool to_right) {
    unsigned short int to_pos;
    unsigned short int from_pos;
    BitVector::Coords current_coord_in_element;

    while (current_coord_in_element != element_coord) {
        if (current_coord_in_element.getOctet() == element_coord.getOctet()) {
            // Only bit at the left interesse us (the others are just placeholder)
            if (from_right) {
                from_pos = from_coord.getBit();
            } else {
                from_pos = 7 - from_coord.getBit();
            }

            if (to_right) {
                to_pos = to_coord.getBit();
            } else {
                to_pos = 7 - to_coord.getBit(); 
            }
            
        } else {
            to_pos = 7 - to_coord.getBit(); 
            from_pos = 7 - from_coord.getBit();
        }

        char to_mask = 1 << to_pos;
        char from_mask = 1 << from_pos;
        
        if (from[from_coord.getOctet()] & to_mask) { // Do a bit is present at the postion [to_pos] of this octet ?
            // Set the from_pos th bit to  from_mask
            to_tab[to_coord.getOctet()] |= from_mask;
        } else {
            // Set the from_pos th bit  to from_mask
            to_tab[to_coord.getOctet()] &= ~from_mask;
        }

        current_coord_in_element.increment();
        to_coord.increment();
        from_coord.increment();
    }
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
    BitVector::copyBits(this->_data, to_tab, element, start, BitVector::Coords(), true, false);
    return to_tab;
}   

char * BitVector::operator[](size_t index) const {
    return this->get(index);
}

void BitVector::set(size_t index, char * tab, bool restrictions) {
    Coords coord = this->indexElement(index);
    if (coord > this->lastBit()) {
        displayLengthError(raise, "Invalid coordinates, maximal position exceed : " + coord.toString() + " > " + this->lastBit().toString(), __FILE__, __func__);
    } 
    if (restrictions && coord > this->end()) {
        displayLengthError(raise, "Invalid coordinates, last element position exceed : " + coord.toString() + " > " + this->lastBit().toString(), __FILE__, __func__);
    }
    BitVector::copyBits(tab, this->_data, this->getCoordUnit(), Coords(0, 0), coord, false, true);
}

void BitVector::set(Coords coord, bool value, bool restrictions) {
    if (coord > this->MaximalCoordLimit()) {
        displayLengthError(raise, "Invalid coordinates, maximal position exceed : " + coord.toString() + " > " + this->lastBit().toString(), __FILE__, __func__);

    } if (restrictions && coord > this->end()) {
        displayLengthError(raise, "Invalid coordinates, last element position exceed : " + coord.toString() + " > " + this->lastBit().toString(), __FILE__, __func__);
    }

    char mask = 1 << coord.getBit();
    if (value) {
        this->_data[coord.getOctet()] |= mask;
    } else {
        this->_data[coord.getOctet()] &= ~mask;
    }
}


int BitVector::testClass(errorMods error_mod) {
    displayMessage(error_mod, " -- Initialisation of a vector with element size 8 -- ");
    BitVector vec8(8);

    displayMessage(error_mod, " -- Initialisation of a vector with element size 11 -- ");
    BitVector vec11(11);

    displayMessage(error_mod, " -- Initialisation of a vector with element size 5 -- ");
    BitVector vec5(5);

    unsigned short int max_element_size = 0;
    max_element_size -= 1;
    displayMessage(error_mod, " -- Initialisation of a vector with element size " + std::to_string(max_element_size) + " (maximum size)");
    BitVector vecMax(max_element_size);

    displayMessage(error_mod, vec5.end().toString());
    vec5.set(Coords(0, 1), true);
    std::cout << vec5.get(Coords(0, 2)) << std::endl; 
    return 0;
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
