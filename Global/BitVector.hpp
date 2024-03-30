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

        static size_t maximumOctetNumber();

        // TODO: += 
        // TODO: -= 

        bool operator==(const Coords & other) const {
            return (this->octet == other.getOctet() && this->bit == other.getBit()) ;
        }


        bool operator!=(const Coords & other) const {
            return !(*this==other);
        }

        // TODO: >
        // TODO: >=
        // TODO: <
        // TODO: <=
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
    size_t getDataSize();
    size_t getElementNumber();
    
    size_t size();

    // --- index ---
    Coords indexElement(size_t element_position);
    size_t indexElementUntreated(size_t element_position);

    size_t indexCoordinate(const Coords & coord, errorMods strictness=ignore);
    std::tuple<size_t, size_t, size_t> indexCoordinateUntreated(const Coords & coord);

   
    // --- Interaction ---

    // --- size ---
    void doubleSize();
    void resize(size_t data_size);
    void shrink();

    //
    Coords getCoordUnit();
    
    bool maxSizeIsReached();
    bool maxDataSizeIsReached();
    bool maxElementSizeIsReached();
    size_t upperOctetLimit();
    size_t upperElementLimit();
    
    static size_t maximumOctetNumber();
    static size_t maximumElementNumber();
    
    //
    char operator[](size_t p) const;

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



