#ifndef FASTASEQUENCE_HPP
#define FASTASEQUENCE_HPP
#include "FastaRelated.hpp"
#include "../Global/Sequence.hpp"
#include <string>
#include <map>

class FastaSequence : public FastaRelated, public Sequence {
private:
    std::map<size_t, std::string> comments;

public:
    const std::map<size_t, std::string>& getAllComment() const {return this->comments;};

    using Sequence::Sequence;

    // Polymorphism
    void insertSeq(size_t position, std::string seq, bool verbose=false);
    void insertSeq(size_t position, const FastaSequence & seq, bool verbose=false);
    void eraseSeq(size_t index, size_t length);

    std::string toString() const;
    std::string toString(bool comments) const;
    std::string toString(unsigned int word_size, unsigned int paragraph_size, bool comments=true) const;
    std::string toString(unsigned int word_size, bool comments=true) const;

    // --- comments ---
    void addComment(size_t position, std::string comment);
    void loadComments(std::map<size_t, std::string>& comment_map);
    void removeComment(size_t position);
    void displaceComment(size_t current_position, size_t new_position);
    
    bool isCommentedPos(size_t position) const;

    std::string getComment(size_t position) const;

};

#endif