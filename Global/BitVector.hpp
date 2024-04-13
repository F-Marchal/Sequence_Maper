#include <iostream>
#include <tuple>
#include "Utilities.hpp"

/**
 * @brief Class that allow the storage of a number inside a  char *. All element must be converted to a number of bits.
 */
class BitVector {
private:
    /**
     * @brief Point toward a char tab that contain all bits.
     */
    char * _data = NULL;
    
    /**
     * @brief Size of BitVector::_data (number of octet that can be stored)
     */
    size_t _data_size = 0;

    /**
     * @brief Number of element stored inside BitVector::_data.
     */
    size_t _element_number;

    /**
     * @brief Number of bit used by each elements inside BitVector::_data.
     */
    short unsigned int _element_size;


protected:
    /**
     * @brief Free memory used by BitVector::_data.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n) |
     * | Space | O(1) |
     * n = BitVector::_data_size
     */
    void _killInternalData(); // In destructor section
    /**
     * @brief Insert a number of blank position inside BitVector::_data
     * | Complexity | Without BitVector::_data_size modification | With BitVector::_data_size modification|
     * |-------|------|------|
     * | Time  | O(n) | O(d) |
     * | Space | O(m) | O(2d)|
     * n = BitVector::_element_number - \p  element_position, + \p room_required ;
     * m = BitVector::_element_size ;
     * d = BitVector::_data_size + m;
     * 2d = BitVector::_data_size * 2 + m ;
     * @param element_position Where should we make space ? 
     * @param room_required How many spaces must be inserted ?
     * @param erase Do spaces are reset to 0 ? (if false, old value is kept (like it was a duplication)) 
     * 
     */
    void _makeRoomForElement(size_t element_position, size_t room_required, bool erase=true); // In access and modifications
    
public:

    /**
     * @brief Class that represent coordinates inside a \ref BitVector. It memorize octet position and bit position n order 
     * to facilitate accession to elements.
     */
    class Coords {
    private:
        /**
         * @brief Position of an octet inside a \ref BitVector. Can not be greater than : \ref Coords::maximumOctetNumber.
         */
        size_t octet;

        /**
         * @brief Position of a bit inside an octet. Can not be greater than 7.
         */
        unsigned short int bit;
    
    public:
        // --- --- Constructor --- ---

        /**
         * @brief Construct a new Coords object. \ref Coords::octet = 0 and \ref Coords::bit = 0. 
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         */
        Coords();

        /**
         * @brief Construct a new Coords object.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param octet initialise \ref Coords::octet.
         * @param bit initialise \ref Coords::bit.
         */
        Coords(size_t octet, unsigned short int bit);

        /**
         * @brief Construct a new Coords object using a size_t. (See \ref Coords::toSize_t)
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param value A size_t value that contain intel about bit value and octet value. See \ref Coords::toSize_t)
         */
        Coords(size_t value);

        /**
         * @brief Construct a new Coords object by copy.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other The object to copy.
         */
        Coords(const Coords & other) : Coords(other.toSize_t()) {}

        // --- --- Conversion --- ---

        /**
         * @brief Translate octet and bit value inside a size_t. Allow easier mathematic computations.
         *  - The last 3 digit represent the bit (n / 8 * 1000). The  
         *  - The other digit represent the octet
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return size_t that represent octet and bit value.
         */
        size_t toSize_t() const;

        /**
         * @brief Turn Coordinates inside a string.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return std::string "(O=X, B=N)"
         */
        std::string toString() const;

        // --- --- Getters and setters --- ---

        /**
         * @brief Get \ref Coords::bit .
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return unsigned short int Bit position int the octet.
         */
        unsigned short int getBit() const ;

        /**
         * @brief Get \ref Coords::octet .
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return size_t Octet position int a \ref BitVector.
         */
        size_t getOctet() const;

        /**
         * @brief Set \ref Coords::octet value.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param octet A size_t that should be inferior to Coords::>maximumOctetNumber()
         * @throw invalid_argument When \p octet > \ref Coords::maximumOctetNumber
         */
        void setOctet(size_t octet);

        /**
         * @brief Set \ref Coords::bit value
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param bit unsigned short int lower or equal to 7.
         * @throw invalid_argument When \p octet > 7.
         */
        void setBit(unsigned short int bit);

        /**
         * @brief Set \ref Coords::octet and \ref Coords::bit .
         * @param value  size_t formatted like in Coords::toSize_t() .
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         */
        void setSize_t(size_t value);
        
         /**
         * @brief Set \ref Coords::octet and \ref Coords::bit .
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * (Assuming mathematics operations are O(1))
         * @param value Coords .
         */
        void setSize_t(const Coords & coord);

        // --- --- Limitations --- ---

        /**
         * @brief return the last octet position that can be hold by a \ref Coords. 
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return size_t 
         */
        static size_t maximumOctetNumber();

        /**
         * @brief return the maximum Size_t value that can be returned by a \ref Coords. 
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return size_t formatted like in Coords::toSize_t() .
         */
        static size_t maximumSize_t();

        // --- --- operators --- ---

        /**
         * @brief Say if another Coords is equal to this one.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other Another Coords.
         * @return true 
         * @return false 
         */
        bool operator==(const Coords & other) const ;

        /**
         * @brief Say if another Coords is not equal to this one.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other Another Coords.
         * @return true 
         * @return false 
         */
        bool operator!=(const Coords & other) const ;

        /**
         * @brief Say if this object is bigger than another Coords.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other Another Coords.
         * @return true 
         * @return false 
         */
        bool operator>(const Coords & other) const ;

        /**
         * @brief Say if this object is bigger or equal than another Coords.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other Another Coords.
         * @return true 
         * @return false 
         */
        bool operator>=(const Coords & other) const ;

        /**
         * @brief Say if this object is lower than another Coords.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other Another Coords.
         * @return true 
         * @return false 
         */
        bool operator<(const Coords & other) const ;
        
        /**
         * @brief Say if this object is lower or equal than another Coords.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other Another Coords.
         * @return true 
         * @return false 
         */
        bool operator<=(const Coords & other) const ;

        /**
         * @brief Multiply this object by an integer.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param value an integer.
         * @return Coords & (this object)
         */
        Coords & operator*=(size_t value) ;

        /**
         * @brief Divide this coordinate by an integer. (Work as integer division)
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param value an integer.
         * @return Coords & (this object)
         */
        Coords & operator/=(size_t value) ;

        /**
         * @brief Addition of two Coords. An error can be raised if \p other is too big for \ref Coords::maximumOctetNumber.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other Another Coords.
         * @return Coords& 
         */
        Coords & operator+=(const Coords & other) ;
        
        /**
         * @brief subtraction of two Coords. An error can be raised if the result in lower than 0 octets.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other 
         * @return Coords& 
         */
        Coords & operator-=(const Coords & other) ;

        /**
         * @brief Addition of two Coords. An error can be raised if \p other is too big for \ref Coords::maximumOctetNumber.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other Another Coords.
         * @return Coords
         */
        Coords operator+(const Coords & other) ;

        /**
         * @brief subtraction of two Coords. An error can be raised if the result in lower than 0 octets.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other Another Coords.
         * @return Coords& 
         */
        Coords operator-(const Coords & other) ;

        /**
         * @brief Multiply this object by an integer.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param value an integer.
         * @return Coords
         */
        Coords operator*(size_t value) ;

        /**
         * @brief Divide this coordinate by an integer. (Work as integer division)
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param value an integer.
         * @return Coords
         */
        Coords operator/(size_t value) ;

        /**
         * @brief Increment this coordinates by 1 bit. (++Coord)
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return Coords & 
         */
        Coords& operator++() ;

        /**
         * @brief Increment this coordinates by 1 bit. (Coord++)
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return Coords & 
         */
        Coords operator++(int) ;
        
        /**
         * @brief decrement this coordinates by 1 bit. (--Coord)
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return Coords & 
         */
        Coords& operator--() ;
        
        /**
         * @brief decrement this coordinates by 1 bit. (Coord--)
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return Coords & 
         */
        Coords operator--(int) ;
        
        /**
         * @brief Increment this coordinates by 1 bit. (Coord++)
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         */
        virtual void increment() ;

        /**
         * @brief decrement this coordinates by 1 bit
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         */
        virtual void decrement() ;

        /**
         * @brief Do another Coords can be added to this coord (without any error) ?
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other another Coords
         * @return true 
         * @return false 
         */
        bool canBeAddedBy(const Coords & other) const ;
       
        /**
         * @brief Do another Coords can be subtracted to this coord (without any error) ?
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param other another Coords
         * @return true 
         * @return false 
         */
        bool canBeSubtractedBy(const Coords & other) const ;

        /**
         * @brief Do this value can be used to multiply this coordinate ?
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @param value size_t
         * @return true 
         * @return false 
         */
        bool canMultiplyBy(size_t value) ;
        
        /**
         * @brief Allow std::cout << Coords
         * 
         * @param os The os object
         * @param coords The coord object
         * @return std::ostream& \p os
         */
        friend std::ostream& operator<<(std::ostream& os, const BitVector::Coords& coords) {
            os << coords.toString();
            return os;
        }
    };

    /**
     * @brief Special version of a BitVector::Coords. 
     * Allow user to iter through a BitVector;
     */
    class Iterator : public Coords {
    private:
        /**
         * @brief BitVector in which the iterator iter.
         */
        const BitVector &_parent;

        /**
         * @brief A Tab that contain the current element during the iteration.
         */
        char * _element = NULL;

        /**
         * @brief Free memory occupied by BitVector::Iterator::_element.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(n) |
         * | Space | O(1) |
         * n = BitVector::Iterator::_element 's size.
         */
        void _nullifyElement ();

    public:
        /**
        * @brief Construct a new Iterator object
        * | Complexity | |
        * |-------|------|
        * | Time  | O(n) |
        * | Space | O(n) |
        * n = size of an element → BitVector::Iterator::_parent.getElementSize
        * @param parent A BitVector
        * @param octet Current Octet position
        * @param bit Current Bit position
        */
        Iterator(const BitVector &parent, size_t octet, unsigned short int bit) : Coords(octet, bit), _parent(parent) {loadValue();}
        /**
        * @brief Construct a new Iterator object
        * | Complexity | |
        * |-------|------|
        * | Time  | O(n) |
        * | Space | O(n) |
        * n = size of an element →  BitVector::Iterator::_parent.getElementSize
        * @param parent A BitVector
        * @param value A size_t value that contain intel about bit value and octet value. See \ref Coords::toSize_t)
        */
        Iterator(const BitVector &parent, size_t value) : Coords(value), _parent(parent) {loadValue();}
        /**
        * @brief Construct a new Iterator object
        * | Complexity | |
        * |-------|------|
        * | Time  | O(n) |
        * | Space | O(n) |
        * n = size of an element →  BitVector::Iterator::_parent.getElementSize
        * @param parent A BitVector
        * @param coord A BitVector::Coords object to cop.
        */
        Iterator(const BitVector &parent, const Coords & coord) : Coords(coord), _parent(parent) {loadValue();}

        /**
        * @brief Construct a new Iterator object
        * | Complexity | |
        * |-------|------|
        * | Time  | O(n) |
        * | Space | O(n) |
        * n = size of an element →  BitVector::Iterator::_parent.getElementSize
        * @param parent A BitVector
        */
        Iterator(const BitVector &parent) : Coords(), _parent(parent) {loadValue();}
        
        /**
         * @brief Free memory occupied by BitVector::Iterator::_element.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(n) |
         * | Space | O(1) |
         * n = BitVector::Iterator::_element 's size.
         */
        ~Iterator() ;

        /**
         * @brief Copy the element that correspond to the iterator position inside BitVector::Iterator::_parent
         * | Complexity | |
         * |-------|------|
         * | Time  | O(n) |
         * | Space | O(n) |
         * n = BitVector::Iterator::_element 's size.
         */
        void loadValue();

        /**
         * @brief Increment this coordinates by 1 coordUnit. (Coord++)
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         */
        void increment() override;

        /**
         * @brief decrement this coordinates by 1 coordUnit
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         */
        void decrement() override ;
            
        /**
         * @brief Conversion into a boolean.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return true BitVector::Iterator::_element is not NULL
         * @return false BitVector::Iterator::_element is NULL
         */
        operator bool() const;

        /**
         * @brief Retrieve BitVector::Iterator::_element.
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         * @return char* 
         */
        char * operator*() const ;
    };

    // --- --- Constructors --- ---
    /**
     * @brief Construct a new Bit Vector object
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n*m) |
     * | Space | O(n*m) |
     * n = \p block_size
     * m = \p alloc
     * @param block_size item size.
     * @param alloc How many item should be contained inside this object.
     */
    BitVector(short unsigned int block_size, size_t alloc);
    /**
     * @brief Construct a new Bit Vector object
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n) |
     * | Space | O(n) |
     * n = \p block_size * 2
     * @param block_size item size.
     */
    BitVector(short unsigned int block_size) : BitVector(block_size, 2) {};
    /**
     * @brief Construct a new Bit Vector object
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n*m) |
     * | Space | O(n*m) |
     * n = \p bit_vector 's size 
     * m = \p bit_vector element size
     */
    BitVector(const BitVector & bit_vector);
    
    /**
     * @brief Modify the number of known element in this object
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @param number 
     * @warning simply modify BitVector::_element_number if this function decrease the number of element, elements are not erase, they still exist in the vector.
     */
    void setElementNumber(size_t number);

    // --- --- Destructor --- ---
    /**
     * @brief Free memory used by BitVector::_data.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n) |
     * | Space | O(1) |
     * n = BitVector::_data_size
     */
    ~BitVector();

    // --- --- Getters --- ---
    /**
     * @brief Get BitVector::_data_size.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return size_t BitVector::_data_size. Number of octet that can be contained
     */
    size_t getDataSize() const;
    /**
     * @brief Get BitVector::_element_number.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return size_t BitVector::_element_number. Number of element contained
     */
    size_t getElementNumber() const;
        size_t getDataSize() const;
    /**
     * @brief Get BitVector::_element_size.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return size_t BitVector::_element_size. Number of bit used by one element
     */
    unsigned short int getElementSize() const;
    
    /**
     * @brief Number of element inside this object.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return size_t Number of element inside this object.
     */
    size_t size() const;

    /**
     * @brief How many element can fit in this vector without having to resize the vector ?
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return size_t number of element
     */
    size_t currentElementCapacity() const;

    // --- index ---
    /**
     * @brief Give the coords of the first bit of an element
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @param element_position Position of an element
     * @return Coords  of the first bit of an element
     */
    Coords indexElement(size_t element_position) const;
    /**
     * @brief Give A size_t that represent the coords of the first bit of an element
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @param element_position Position of an element
     * @return Coords size_t that represent the coords of the first bit of an element
     */
    size_t indexElementUntreated(size_t element_position) const;

    /**
     * @brief Find the element that correspond to \p coord .
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @param coord Coord object
     * @param strictness if raise / display a message is displayed \p coord is not the first bit of an object
     * @return size_t The element position
     */
    size_t indexCoordinate(const Coords & coord, errorMods strictness=ignore) const;

    /**
     * @brief Give more detailed on \ref BiteVector::indexCoordinate
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @param coord  Coord object
     * @return std::tuple<size_t, size_t, size_t> {element position, really used octet, unused octet}
     */
    std::tuple<size_t, size_t, size_t> indexCoordinateUntreated(const Coords & coord) const;

   
    // --- Interaction ---
    /**
    * @brief Give an iterator to begin an iteration.
    * | Complexity | |
    * |-------|------|
    * | Time  | O(n) |
    * | Space | O(n) |
    * n = size of an element → BitVector::_element_size
    * @return Iterator initialised to 0,0
    */
    Iterator begin() const ;
    /**
    * @brief Give an iterator to end an iteration.
    * | Complexity | |
    * |-------|------|
    * | Time  | O(n) |
    * | Space | O(n) |
    * n = size of an element → BitVector::_element_size
    * @return Iterator initialised to BitVector::lastPos
    */
    Iterator end() const ;
    /**
     * @brief First postion of the vector.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return Coords (0, 0)
     */
    Coords firstPos() const;
    /**
     * @brief Last postion of the vector.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return Coords 
     */
    Coords lastPos() const;

    /**
     * @brief Do this object is not empty
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return true is not empty
     * @return false is empty
     */
    operator bool() const;

    // --- size ---

    void doubleSize();
    /**
     * @brief Modify the length of BitVector::_data.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n) |
     * | Space | O(n) |
     * n = \p element_capacity
     * @param element_capacity new capacity of BitVector::_data. (in number of element)
     */
    void resize(size_t element_capacity);

    /**
     * @brief Reduce the size of BitVector::_data to fit BitVector::_element_number.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n*m) |
     * | Space | O(n*m) |
     * n = BitVector::_element_number
     * m = BitVector::_element_size
     * Note : In most cases n >> m.
     */
    void shrink();

    /**
     * @brief Free memory used by BitVector::_data.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n) |
     * | Space | O(1) |
     * n = BitVector::_data_size
     */
    void clear();

    // --- Utilities ---
    /**
     * @brief Say how many items can be hold inside this object with the current BitVector::_data_size:
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return size_t how many items can be hold inside this object 
     */
    size_t currentCapacity() const ;
    /**
     * @brief Give the last coordinates thar can be contained inside BitVector::_data with the current BitVector::_data_size
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return Coords Position of the last bit contained inside BitVector::_data.
     */
    Coords lastBit() const ;
    

    /**
     * @brief Give the a coord object that represent the size of 1 element inside BitVector::_data.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return Coords A coord object that represent the size of 1 element inside BitVector::_data.
     */
    Coords getCoordUnit() const;
    /**
     * @brief Get the Size_t value if a  BitVector::CoordUnit
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return Size_t value of a coord object that represent the size of 1 element inside BitVector::_data. 
     */
    size_t getSize_tUnit() const;

    /**
     * @brief Do maximum capacity is reached (With no possibility to push it further)
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return true Yes
     * @return false No
     */
    bool maxSizeIsReached() const;
    /**
     * @brief Do maximum BitVector::_data_size is reached (With no possibility to push it further)
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return true Yes
     * @return false No
     */
    bool maxDataSizeIsReached() const;
    /**
     * @brief Do maximum BitVector::_element_number is reached (With no possibility to push it further)
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return true Yes
     * @return false No
     */
    bool maxElementSizeIsReached() const;
    /**
     * @brief How many octet can be contained in this object knowing BitVector::_element_size
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     */
    size_t maxOctetLimit() const;
    /**
     * @brief How many element can be contained in this object knowing BitVector::_element_size
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     */
    size_t maxElementLimit() const;
    /**
     * @brief Last acceptable coordinate knowing BitVector::_element_size
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     */
    Coords MaximalCoordLimit() const;
    
    
    /**
     * @brief How many octet can be contained in this kind of object.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     */
    static size_t maximumOctetNumber();

    /**
     * @brief How many element can be contained in this kind of object.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     */
    static size_t maximumElementNumber();
    
    /**
     * @brief 
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n) |
     * | Space | O(1) |
     * n = size of element → element.getOctet() * 8 + element.getBit().
     * @param pattern What should be copied in \p final_list
     * @param final_list A container that will receive the content of \p pattern
     * @param element The size of the element that should be copied form \p pattern to \p final_list
     * @param pattern_coord Where the element start in \p pattern
     * @param final_coord Where the element start in \p final_list
     * @param final_end_is_right True : the last octet od \p final_list will be wrote as xxxppppp (x=unused and p=pattern) False : pppppxxx
     * @param pattern_end_is_right True : the last octet od \p pattern will be wrote as xxxppppp (x=unused and p=pattern) False : pppppxxx
     */
    static void copyBits(const char * pattern, char * final_list, const Coords element,  Coords pattern_coord, BitVector::Coords final_coord, bool final_end_is_right=false, bool pattern_end_is_right=false);

    // --- Access and modifications ---

    /**
     * @brief Return the value of the bit at the position \p coord
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @param coord Position of a bit
     * @return true bit=1
     * @return false bit=0
     */

    bool get(Coords coord) const;
    /**
     * @brief Return the value of the bit at the position \p coord
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @param coord Position of a bit
     * @return true bit=1
     * @return false bit=0
     */
    bool operator[](Coords coord) const;

    /**
     * @brief Return the element at the position \p index
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n) |
     * | Space | O(n) |
     * n = size of an element → BitVector::_element_size
     * @param index the position of the element
     * @return char* the element
     */
    char * get(size_t index) const;
    /**
     * @brief Return the element at the position \p index
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n) |
     * | Space | O(n) |
     * n = size of an element → BitVector::_element_size
     * @param index the position of the element
     * @return char* the element
     */
    char * operator[](size_t index) const;

    /**
     * @brief Replace an element by another element. Can add an element to the list if \p index = BitVector::_element_number
     * | Complexity | Without BitVector::_data_size modification | With BitVector::_data_size modification|
     * |-------|------|------|
     * | Time  | O(n) | O(d) |
     * | Space | O(1) | O(2d)|
     * n = BitVector::_element_size  ;
     * d = BitVector::_data_size + n;
     * 2d = BitVector::_data_size * 2 + n ;
     * @param index Position of the element
     * @param value The element to add.
     * @param restrictions Do un-allowed emplacement inside BitVector::_data ( \p index > BitVector::_element_number) are authorized.
     * @param push Do writing the last element increase  BitVector::_element_number.
     */
    void set(size_t index, char * tab, bool restrictions = true, bool push=true);
    /**
     * @brief Replace an element by another element. Can add an element to the list if \p index = BitVector::_element_number
     * | Complexity | Without BitVector::_data_size modification | With BitVector::_data_size modification|
     * |-------|------|------|
     * | Time  | O(n) | O(d) |
     * | Space | O(1) | O(2d)|
     * n = BitVector::_element_size  ;
     * d = BitVector::_data_size + n;
     * 2d = BitVector::_data_size * 2 + n ;
     * @param index Position of the element
     * @param value The element to add.
     * @param restrictions Do un-assigned emplacement inside BitVector::_data ( \p index > BitVector::_element_number) are authorized.
     * @param push Do writing the last element increase  BitVector::_element_number.
     */
    void set(size_t index, char value, bool restrictions = true, bool push=true);
    /**
     * @brief Modify a bit inside BitVector::_data.
     * 
     * @param coord Emplacement of the targeted bit.
     * @param value True=1, False=0
     * @param restrictions  Do un-assigned emplacement inside BitVector::_data ( \p coord > BitVector::lastPos()) are authorized.
     */
    void set(Coords coord, bool value, bool restrictions = true);

    /**
     * @brief Add an element at the end of the vector.
     * | Complexity | Without BitVector::_data_size modification | With BitVector::_data_size modification|
     * |-------|------|------|
     * | Time  | O(n) | O(d) |
     * | Space | O(1) | O(2d)|
     * n = BitVector::_element_size  ;
     * d = BitVector::_data_size + n;
     * 2d = BitVector::_data_size * 2 + n ;
     * @param tab A tab of char
     */
    void append(char * tab);
    /**
     * @brief Add an element at the end of the vector.
     * | Complexity | Without BitVector::_data_size modification | With BitVector::_data_size modification|
     * |-------|------|------|
     * | Time  | O(n) | O(d) |
     * | Space | O(1) | O(2d)|
     * n = BitVector::_element_size  ;
     * d = BitVector::_data_size + n;
     * 2d = BitVector::_data_size * 2 + n ;
     * @param tab A  char
     */
    void append(char value);

    /**
     * @brief Insert a \p number_of_elements inside the vector at the index \p pos .
     * | Complexity | Without BitVector::_data_size modification | With BitVector::_data_size modification|
     * |-------|------|------|
     * | Time  | O(n) | O(d) |
     * | Space | O(m) | O(2d)|
     * n = BitVector::_element_number - \p  pos, + \p number_of_elements ;
     * m = BitVector::_element_size ;
     * d = BitVector::_data_size + m;
     * 2d = BitVector::_data_size * 2 + m ;
     * @param pos Position od the insertion
     * @param number_of_elements number of element to add
     * @param tab list off element that should be added.
     * @warning If the number of \p tab is smaller than \p number_of_elements garbage will be inserted.
     */
    void insert(size_t pos, size_t number_of_elements, char * tab ...);

    /**
     * @brief Insert a \p number_of_elements inside the vector at the index \p pos .
     * | Complexity | Without BitVector::_data_size modification | With BitVector::_data_size modification|
     * |-------|------|------|
     * | Time  | O(n) | O(d) |
     * | Space | O(m) | O(2d)|
     * n = BitVector::_element_number - \p  pos, + \p number_of_elements ;
     * m = BitVector::_element_size ;
     * d = BitVector::_data_size + m;
     * 2d = BitVector::_data_size * 2 + m ;
     * @param pos Position od the insertion
     * @param number_of_elements number of element to add
     * @param c list off element that should be added.
     * @warning If the number of \p c is smaller than \p number_of_elements garbage will be inserted.
     */
    void insert(size_t pos, size_t number_of_elements, char c ...);
    
    /**
     * @brief Remove a number of element from the vector.
     * | Complexity | |
     * |-------|------|
     * | Time  | O(n) |
     * | Space | O(1) |
     * n = number_of_element
     * @param element_position beginning of the deletion
     * @param number_of_element number of element to delete
     */
    void remove(size_t element_position, size_t number_of_element);

};


/* ------------------------------------------------------- Small test ------------------------------------------------------------------
int main () {
    BitVector bv(2, 1);
    std::cout << "-- Set and Append --" << std::endl;
    bv.set(0, (char) 0b00000011);
    bv.append((char) 0b00000010);
    bv.append((char) 0b00000001);
    bv.set(3, (char) 0b00000000);
    bv.append((char) 0b00000011);
    bv.append((char) 0b00000001);
    // bv.set(2, (char) 0b00011111);
    std::cout << "-- Get --" << std::endl;
    displayBits(bv.get(0)[0]);
    std::cout << "-- Insert Append Remove --" << std::endl;

    bv.insert(2, 3, 0b00000011, 0b00000011, 0b00000011);
    bv.append((char) 0b00000001);
    bv.remove(9, 3);
    std::cout << "--Copy and display --" << std::endl;
    for (char * c: BitVector(bv)) {
        displayBits(c[0]);
    }
    bv.append((char) 0b00000011);
    for (char * c: BitVector(bv)) {
        displayBits(c[0]);
    }
    std::cout << "--'end'--" << std::endl;
    return 0;
}
*/