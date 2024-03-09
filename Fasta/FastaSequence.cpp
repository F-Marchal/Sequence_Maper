#include "FastaSequence.hpp"
#include <string>
#include <map>
#include <stdexcept>

void FastaSequence::insertSeq(size_t position, std::string seq, bool verbose) {
    Sequence::insertSeq(position, seq, verbose);

    for (size_t displaced_pos = position; displaced_pos < position + seq.size(); displaced_pos++) {
        this->displaceComment(position, position + seq.size());
    }
}

void FastaSequence::eraseSeq(size_t index, size_t length) {
    Sequence::eraseSeq(index, length);
}


void FastaSequence::addComment(size_t position, std::string comment) {
    if (position > this->size()) {
        return ;
    }
    
    size_t lineB_pos = comment.find('\n');
    if (lineB_pos < comment.length()) {
        throw std::invalid_argument("Comments are not allowed to contain \\n");
    }

    if (this->isCommentedPos(position)){
        this->comments[position] += comment;

    } else {
        this->comments[position] = comment;
    }
}

void FastaSequence::loadComments(std::map<size_t, std::string>& comment_map) {
     for(const auto& elem : comment_map) {
        std::cout << "COM:" << elem.first << " " << elem.second << std::endl;
        this->addComment(elem.first, elem.second);
     }
}

void FastaSequence::removeComment(size_t position) {
    if (this->isCommentedPos(position)){
        this->comments.erase(position);
 
    } 
}

void FastaSequence::displaceComment(size_t current_position, size_t new_position) {
    if (!this->isCommentedPos(current_position)) {
        throw std::invalid_argument("Current position does not have any comment : " + current_position);
    }

    std::string comment = this->getComment(current_position);
    this->removeComment(current_position);
    this->addComment(new_position, comment);
}

std::string FastaSequence::getComment(size_t position) {
    if (this->isCommentedPos(position)){
        return this->comments[position];
    } 
    return "";
}

bool FastaSequence::isCommentedPos(size_t position) {
    return (this->comments.count(position) >= 1);
}

