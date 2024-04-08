#include <iostream>
#include <tuple>
#include <map>
#include <vector>
#include "Utilities.hpp"
// Parler de : Construction de getElementNumber / getPosInArray;

// TODO: Faire maxPositionInArray;
// TODO: Tester les func
// TODO: Finir les autres implementations

class BitVector {
private:
    char * _data = NULL;
    
    size_t _data_size = 0;
    size_t _element_number;
    short unsigned int _element_size;


protected:

    void _killInternalData();
    
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
        void increment() ;

        /**
         * @brief decrement this coordinates by 1 bit
         * | Complexity | |
         * |-------|------|
         * | Time  | O(1) |
         * | Space | O(1) |
         */
        void decrement() ;

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


    
    // --- --- Constructors --- ---
    BitVector(short unsigned int block_size, size_t alloc);
    BitVector(short unsigned int block_size) : BitVector(block_size, 2) {};
    void setElementNumber(size_t number);
    // --- --- Destructor --- ---
    ~BitVector();

    // --- --- Getters --- ---
    size_t getDataSize() const;
    size_t getElementNumber() const;
    
    size_t size() const;
    size_t currentElementCapacity() const;

    // --- index ---
    Coords indexElement(size_t element_position) const;
    size_t indexElementUntreated(size_t element_position) const;

    size_t indexCoordinate(const Coords & coord, errorMods strictness=ignore) const;
    std::tuple<size_t, size_t, size_t> indexCoordinateUntreated(const Coords & coord) const;

   
    // --- Interaction ---
    Coords start() const;
    Coords end() const;

    // --- size ---
    void doubleSize();
    void resize(size_t element_capacity);
    void shrink();
    void clear();

    size_t currentCapacity() const ;
    Coords lastBit() const ;
    
    //
    Coords getCoordUnit() const;
    size_t getSize_tUnit() const;
    bool maxSizeIsReached() const;
    bool maxDataSizeIsReached() const;
    bool maxElementSizeIsReached() const;
    size_t maxOctetLimit() const;
    size_t maxElementLimit() const;
    Coords MaximalCoordLimit() const;

    static size_t maximumOctetNumber();
    static size_t maximumElementNumber();
    
    static void copyBits(const char * pattern, char * final_list, const Coords element,  Coords pattern_coord, BitVector::Coords final_coord, bool final_end_is_right=false, bool pattern_end_is_right=false);
    void copyBits(const char * pattern, char * final_list,  Coords pattern_coord, Coords final_coord, bool final_end_is_right=false, bool pattern_end_is_right=false) ;
    //
    bool get(Coords coord) const;
    bool operator[](Coords coord) const;
    char * get(size_t index) const;
    char * operator[](size_t index) const;
    
    void set(size_t index, char * tab, bool restrictions = true);
    void set(size_t index, char value, bool restrictions = true);
    void set(Coords coord, bool value, bool restrictions = true);

};


//  public:
//   char *_data;
//   size_t _size;
//   size_t _raw_capacity;
//   EncodedSequence(const char *cstr = NULL);
//   EncodedSequence(const std::string &s);
//   EncodedSequence(const EncodedSequence &es);
//   ~EncodedSequence();
//   EncodedSequence &operator=(const EncodedSequence &es);
//   inline size_t size() const {
//     return _size;
//   }
//   inline size_t length() const {
//     return size();
//   }
//   inline size_t capacity() const {
//     return _raw_capacity << 2;
//   }
//   size_t rawSize() const;
//   std::string decode() const;
//   void affiche(std::ostream &os) const;
//   char operator[](size_t p) const;
//   void setNucleotide(size_t p, char c);
//   void ajouteNucleotide(char c);
//   void resize(size_t n);
//   void reserve(size_t n);
//   void clear();
//   void shrink_to_fit();
//   int compare(const EncodedSequence &e) const;
// };



