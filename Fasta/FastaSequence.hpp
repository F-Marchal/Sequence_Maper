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
    std::map<size_t, std::string> getAllComment() {return this->comments;};
    std::map<size_t, std::string>  getComment() {return this->comments;}

    using Sequence::Sequence;

    // --- comments ---
    void addComment(size_t position, std::string comment);
    void loadComments(std::map<size_t, std::string>& comment_map);
    void removeComment(size_t position);
    bool isCommentedPos(size_t position);
    std::string getComment(size_t position);
};

#endif