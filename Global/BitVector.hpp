#include <iostream>
#include <tuple>
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
    size_t _element_number = 0;

    short unsigned int _element_size;

protected:
    void _killInternalData();
    
public:
    BitVector(short unsigned int block_size);
    ~BitVector();
    

    std::tuple<size_t, short unsigned int> getPosInArray(size_t element_number, errorMods error_mod=raise);
    size_t getElementNumber(size_t char_position, short unsigned int block_position_in_char, errorMods error_mod=raise);
    
    // size_t maximumElementNumber();
    std::tuple<size_t, short unsigned int> maxPositionInArray();

    size_t getDataSize();
    size_t getElementNumber();
    size_t size();
    size_t getCurrentCapacity();
    
    static size_t maximalInternalSize();

    size_t extractPosition(size_t position_in_data, short unsigned int position_in_char);

    void doubleSize();

    void resize(size_t data_size);
    // void reserveCapacity(size_t element_number);
    // void resizeCapacity(size_t element_number);
    // void shrinkCapacity();

    // void append(const & std::array<short unsigned int> values);
    // void insert(size_t position, const & std::array<short unsigned int> values);




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



