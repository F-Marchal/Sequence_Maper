#include <iostream>
#include <tuple>
#include <map>

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
    // --- --- Constructors --- ---
    BitVector(short unsigned int block_size);

    // --- --- Destructor --- ---
    ~BitVector();

    // --- --- Getters --- ---
    size_t getDataSize();
    size_t getElementNumber();
    size_t size();

    // --- index ---
    std::tuple<size_t, unsigned short int> indexElement(size_t element_position);
    size_t indexCoordinate(size_t octet, unsigned short int bit, errorMods strictness=ignore);
    std::tuple<size_t, size_t, size_t> indexUntreatedCoordinate(size_t octet_number, unsigned short int bit);
   
    // --- Limitation ---
    // static bool stopFunctionGetMaximalNumberOfOctet(const std::map<char, size_t>& InfMap);
    // size_t getMaximalNumberOfOctet();
    // static bool stopFunctionMaximalNumberOfElements(const std::map<char, size_t>& InfMap);
    // size_t getMaximalNumberOfElements();

    // --- --- Utilities --- --- 


    // --- Research ---
    // static std::map<char, size_t> searchElement(size_t data_size, short unsigned int element_size, bool (*func)(const std::map<char, size_t> &)=NULL);
    // static std::map<char, size_t> searchElement(size_t data_size, short unsigned int element_size, size_t octet_position, short unsigned int bit_position, bool (*func)(const std::map<char, size_t> &)=NULL);
    // std::map<char, size_t>  searchElement(bool (*func)(const std::map<char, size_t> &)=NULL);

    // --- size ---
    void doubleSize();
    void resize(size_t data_size);

    // --- 
    
    // 

    //
    bool maxSizeIsReached();
    bool maxDataSizeIsReached();
    bool maxElementSizeIsReached();
    size_t upperOctetLimit();
    size_t upperElementLimit();
    
    static size_t maximumOctetNumber();
    static size_t maximumElementNumber();


    


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



