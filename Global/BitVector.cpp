#include "BitVector.hpp"
#include "Utilities.hpp"
#include <string>
#include <cstring> // memset
#include <cstdarg> // Variadics


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
BitVector::Coords::operator std::string() const {
    return this->toString();
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
    return Coords(this->toSize_t() - other.toSize_t());
}

BitVector::Coords BitVector::Coords::operator*(size_t value) {
    Coords final_coord;

    if (value == 0) {
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
        if (this->octet >= this->maximumOctetNumber()) {
            // Can not increment further
            return ;
        }
        this->setBit(0);
        this->setOctet(this->octet + 1);

    } else {
        this->setBit(this->bit + 1);
    }
}

void BitVector::Coords::decrement() {
    if (this->bit == 0) {
        if (this->octet == 0) {
            // Can not decrement further
            return ;
        }
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
    return (this->toSize_t() >= other.toSize_t());  
}

bool BitVector::Coords::canMultiplyBy(size_t value) {
    return (this->toSize_t() <= this->maximumSize_t() / value);
}


// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- Iterator --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
void BitVector::Iterator::_nullifyElement () {
    if ( this->_element != NULL) {
        delete[] _element;
    } 
    this->_element = NULL;
}

BitVector::Iterator::~Iterator() {
    delete[] this->_element;
}
void BitVector::Iterator::loadValue() {
    this->_nullifyElement();
    this->_element = this->_parent[this->_parent.indexCoordinate(*this)];
}

void BitVector::Iterator::increment() {
    *this += this->_parent.getCoordUnit();
    this->loadValue();
}

void BitVector::Iterator::decrement() {
    *this -= this->_parent.getCoordUnit();
    this->loadValue();
} 
    
BitVector::Iterator::operator bool() const {
    return (this->_element != NULL);
}

char * BitVector::Iterator::operator*() const {
    return this->_element;
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

BitVector::BitVector(const BitVector & bit_vector) : BitVector(bit_vector.getElementSize(), bit_vector.currentElementCapacity()) {
    size_t i=0;

    // Copy items
    for (char * c : bit_vector) {
        this->set(i, c);
        i++;
    }
    this->append(0b00000001);
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
    this->_element_number = 0;
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

unsigned short int BitVector::getElementSize() const {
    return this->_element_size;
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
    
    // Use the power of division to retrieve how much element can be stuffed into octet_number
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


BitVector::Iterator BitVector::begin() const {
    return BitVector::Iterator(*this, this->firstPos());
}
BitVector::Iterator  BitVector::end() const {
    return BitVector::Iterator(*this, this->lastPos());
}


BitVector::Coords BitVector::lastPos() const  {
    return getCoordUnit() * this->_element_number;
}

BitVector::Coords BitVector::firstPos() const {
    return Coords(0, 0);
}

BitVector::operator bool() const {
    return (this->_element_number != 0);
}
// --- --- Utilities --- --- 

void BitVector::doubleSize() {
    if (this->maxSizeIsReached()) {
        displayLengthError(raise, "Maximal size reached, can not extend data size.", __FILE__, __func__);
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
            new_tab[i] = 0b00000000; // Assure that all bits are equal to 0
        }
    }
    
    size_t element_number;
    if (this->_data_size > new_data_size) {
        element_number = (new_data_size * 1000 + (7 * 1000 / 8)) / this->getSize_tUnit();
    } else {
        element_number = this->_element_number;
    }

    this->_killInternalData ();
    this->_element_number = element_number;
    this->_data_size = new_data_size;
    this->_data = new_tab;


    
}

void BitVector::shrink() {
    // Extract number of octet needed and resize data.
    this->resize(this->_element_number * this->getSize_tUnit() / 1000 + 1) ;
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

// --- Access and modifications ---
void BitVector::copyBits(const char * pattern, char * final_list, const BitVector::Coords element,  BitVector::Coords pattern_coord, BitVector::Coords final_coord, 
                         bool final_end_is_right, bool pattern_end_is_right) {

    BitVector::Coords pattern_end_coord = pattern_coord + element;
    BitVector::Coords final_end_coord = final_coord + element;
    BitVector::Coords step_left = element;
 
    short unsigned int pattern_bit_value;
    short unsigned int final_list_bit_value;

    char pattern_bit;
    char final_mask;

    while (final_coord != final_end_coord) {
        step_left --;

        // Right or Left
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
        
        // Mask
        pattern_bit = 1 << pattern_bit_value;
        final_mask = 1 << final_list_bit_value;

        // Apply the mask
        if (pattern[pattern_coord.getOctet()] & pattern_bit) {
            final_list[final_coord.getOctet()] |= final_mask;

        } else {
            final_list[final_coord.getOctet()] &= ~final_mask;
        }
        
        final_coord++;
        pattern_coord++;
    }
}

void BitVector::makeRoomForElement(size_t element_position, size_t room_required, bool erase) {
    if (room_required == 0) {
        // nothing to do.
        return ;
    }
    if (room_required > this->maxElementLimit() || this->_element_number > this->maxElementLimit() - room_required) {
        // Avoid starting a memory doomed displacement. 
        displayLengthError(raise, "\\p can not add " + std::to_string(room_required) + " new elements. Maximum element limit would be reached.", __FILE__, __func__);
    }
    
    char * empty_element = new char[this->_element_size / 8 + 1 ];
    std::memset(empty_element, 0, this->_element_size / 8 + 1); // Assure that all bits are equals to 0
    size_t last_true_element = this->_element_number;

    // Add space required by \p room_required
 
    for (size_t pos = 0 ; pos < room_required; pos++) {
        this->append(empty_element);
    }

    // Displace all element between \p element_position and vector's end by n (=room_required) places.
    char * current_element = NULL;
    bool continue_ = true;
    size_t pos = last_true_element;
    
    while (continue_ && pos >= element_position) {
        current_element = this->get(pos);
        this->set(pos + room_required, current_element, true, false); // Push the element

        delete [] current_element; // Free memory

        if (erase) {
            this->set(pos, empty_element);
        }

        continue_ = (pos != 0);
        pos--;
    }
  
    delete [] empty_element;
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

    char * to_tab = new char[this->_element_size / 8 + 1 ];
    std::memset(to_tab, 0, this->_element_size / 8 + 1); // Assure that all bits are equals to 0

    this->copyBits(this->_data, to_tab, this->getCoordUnit(), start, Coords(0, 0), true, false);

    return to_tab;
}   

char * BitVector::operator[](size_t index) const {
    return this->get(index);
}

void BitVector::set(size_t index, char * tab, bool restrictions, bool push) {
    Coords coord = this->indexElement(index);
    while (coord > this->lastBit()) {
        this->doubleSize();
    }

    if (restrictions && coord > this->lastPos()) {
        displayLengthError(raise, "Invalid coordinates, last element position exceed : " + coord.toString() + " > " + this->lastPos().toString(), __FILE__, __func__);
    }
    
    bool push_limit = (coord == this->lastPos());
    
    this->copyBits(tab, this->_data,  this->getCoordUnit(), Coords(0, 0), coord, false, true);
 
    if (push && push_limit) {
        this->_element_number += 1;
    }
}

void BitVector::set(size_t index, char value, bool restrictions, bool push) {
    char * temp_tab = new char[1] {value};
    this->set(index, temp_tab, restrictions, push);
    delete [] temp_tab;
}

void BitVector::set(Coords coord, bool value, bool restrictions) {
    while (coord > this->lastBit()) {
        this->doubleSize();
    }

    if (restrictions && coord > this->lastPos()) {
        displayLengthError(raise, "Invalid coordinates, last element position exceed : " + coord.toString() + " > " + this->lastBit().toString(), __FILE__, __func__);
    }

    char mask = 1 << coord.getBit();
    if (value) {
        this->_data[coord.getOctet()] |= mask;
    } else {
        this->_data[coord.getOctet()] &= ~mask;
    }
}

void BitVector::append(char * tab) {
    this->set(this->_element_number, tab);
}

void BitVector::append(char value) {
    this->set(this->_element_number, value);
}


void BitVector::insert(size_t position, size_t number_of_elements, char c...) {
    va_list args;
    va_start(args, c);
    
    // Move items
 
    this->makeRoomForElement(position, number_of_elements);

    // Set items
    for (size_t i = 0; i < number_of_elements; i++) {
        
        this->set(position + i, c) ;
        c = va_arg(args, int);
    }
    
    va_end(args);
}

void BitVector::insert(size_t position, size_t number_of_elements, char * tab...) {
    va_list args;
    va_start(args, tab);
    
    // Move items
    this->makeRoomForElement(position, number_of_elements);

    // Set items
    for (size_t i = 0; i < number_of_elements; i++) {
        
        tab = va_arg(args, char *);
        this->set(position + i, tab) ;
        
    }
    
    va_end(args);
}

void BitVector::remove(size_t element_position, size_t number_of_element) {
    if (number_of_element == 0) {
        return ;
    }
    if (element_position >= this->_element_number) {

        return ;
    }
 
    number_of_element = std::min(number_of_element, this->_element_number - element_position);

    for (size_t pos=element_position + number_of_element; pos < this->_element_number; pos++) {
        char * tab = this->get(pos);
        this->set(pos - number_of_element, tab);
        delete [] tab;
    }

    this->setElementNumber(this->_element_number - number_of_element);

    
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
