#include <iostream>
#include <tuple>
#include <map>
#include <vector>
#include "Utilities.hpp"
// Parler de : Construction de getElementNumber / getPosInArray;
//          Pb mathematics pour l'ameiorer (*1000, decouverte float, peurs de floatr = apro, test)
// TODO: Remplacer jeu sur *1000 / 1000 dans par la methode dans maximumElementNumber getPosInArray 
// TODO:        Remplacer maximalInternalSize ??
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

    // Coords
    class Coords {
    private:
        size_t octet;
        unsigned short int bit;
    
    public:
        Coords();
        Coords(size_t octet, unsigned short int bit);
        Coords(size_t value);
        

        size_t toSize_t() const;
        std::string toString() const;

        unsigned short int getBit() const;
        size_t getOctet() const;

        void setOctet(size_t octet);
        void setBit(unsigned short int bit);
        void setSize_t(size_t octet);

        static size_t maximumOctetNumber();
        static size_t maximumSize_t();

        bool operator==(const Coords & other) const {
            return (this->octet == other.getOctet() && this->bit == other.getBit()) ;
        }

        bool operator!=(const Coords & other) const {
            return !(*this==other);
        }

        bool operator>(const Coords & other) const {
            return (this->octet > other.getOctet() || (this->octet == other.getOctet() && this->bit > other.getBit()));
        }

        bool operator>=(const Coords & other) const {
            return (this->octet > other.getOctet() || (this->octet == other.getOctet() && this->bit >= other.getBit()));
        }

        bool operator<(const Coords & other) const {
            return (this->octet < other.getOctet() || (this->octet == other.getOctet() && this->bit < other.getBit()));
        }

        bool operator<=(const Coords & other) const {
            return (this->octet < other.getOctet() || (this->octet == other.getOctet() && this->bit <= other.getBit()));
        }

        Coords & operator*=(size_t value) {
            //WARNING: no protection on value
            value = (value * 1000 * 7 / 1000);

            size_t this_size = this->toSize_t();
            if (value == 0) {
                // Avoid division by 0 in the next condition
                this->setSize_t(value);

            } else if (this_size > this->maximumSize_t() / value) {
                // The result will be greater than .
                displayLengthError(raise, "Can not proceed this multiplication, maximum size would be reached", __FILE__, __func__);

            } else {
                 this->setSize_t(value * this_size);
            }

            return *this;
        }

        Coords & operator/=(size_t value) {
            value = (value * 1000 * 7 / 1000);
            this->setSize_t(this->toSize_t() / value);
            return *this;
        }

        Coords operator+(const Coords other) {
            if (other.toSize_t() > this->maximumSize_t() - this->toSize_t())  {
                displayLengthError(raise, "Can not proceed this sum, maximum size would be reached", __FILE__, __func__);
            }

            return Coords(other.toSize_t() + this->toSize_t());
        }

        Coords operator-(const Coords other) {
            if (other.toSize_t() >  this->toSize_t())  {
                displayLengthError(raise, "Can not proceed this subtraction, a negative number would be reached", __FILE__, __func__);
            }

            return Coords(other.toSize_t() - this->toSize_t());
        }

        // TODO: ++ 
        // TODO: --

        void increment() {
            if (this->bit == 7) {
                this->setBit(0);
                this->setOctet(this->octet + 1);

            } else {
                this->setBit(this->bit + 1);
            }
        }

        void decrement() {
            if (this->bit == 0) {
                this->setBit(7);
                this->setOctet(this->octet - 1);

            } else {
                this->setBit(this->bit - 1);
            }
        }
    };


    
    // --- --- Constructors --- ---
    BitVector(short unsigned int block_size);

    // --- --- Destructor --- ---
    ~BitVector();

    // --- --- Getters --- ---
    size_t getDataSize() const;
    size_t getElementNumber() const;
    
    size_t size() const;

    // --- index ---
    Coords indexElement(size_t element_position) const;
    size_t indexElementUntreated(size_t element_position) const;

    size_t indexCoordinate(const Coords & coord, errorMods strictness=ignore) const;
    std::tuple<size_t, size_t, size_t> indexCoordinateUntreated(const Coords & coord) const;

   
    // --- Interaction ---

    // --- size ---
    void doubleSize();
    void resize(size_t data_size);
    void shrink();

    //
    Coords getCoordUnit() const;
    size_t getSize_tUnit() const;
    bool maxSizeIsReached() const;
    bool maxDataSizeIsReached() const;
    bool maxElementSizeIsReached() const;
    size_t upperOctetLimit() const;
    size_t upperElementLimit() const;
    
    static size_t maximumOctetNumber();
    static size_t maximumElementNumber();
    
    static void copyBits(char * main_tab, char * modif, Coords element_coord, Coords main_coord,  Coords modif_coord, bool from_right=false, bool to_right=false);
    
    //
    bool get(Coords coord) const;
    bool operator[](Coords coord) const;
    std::vector<char>  get(size_t index) const;
    std::vector<char>  operator[](size_t index) const;

    // test
    static int testClass();
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



