#include "FastaSequence.hpp"
#include <string>
#include <map>
#include <stdexcept>

// void FastaSequence::insertSeq(size_t position, std::string seq, bool verbose) {
//     size_t old_size = this->size();
//     Sequence::insertSeq(position, seq, verbose);

//     for (size_t displaced_pos = old_size; displaced_pos > position; displaced_pos--) {
//         // Iter à l'envers pour eviter de "pousser" un commentaire deja poussé.
//         if (this->isCommentedPos(displaced_pos)) {
//             this->displaceComment(displaced_pos, displaced_pos + seq.size());
//         }
//     }
// }

// void FastaSequence::insertSeq(size_t position, const FastaSequence & seq, bool verbose) {
//     insertSeq(position, seq.getSeq(), verbose);
//     const std::map<size_t, std::string>& comments_to_add = seq.getAllComment();
//     size_t pos;
//     std::string comment;

//     for (auto it = comments_to_add.begin(); it != comments_to_add.end(); ++it) {
//         pos = it->first;
//         comment = it->second;

//         if (1 <= pos && pos <= seq.size()) {
//             this->addComment(position + pos, comment);
//         }
//     } 
// }

void FastaSequence::eraseSeq(size_t index, size_t length) {
    size_t old_size = this->size();
    Sequence::erase(index, length);

    


    for (size_t displaced_pos = index + 1; displaced_pos < old_size; displaced_pos++) {
        // Iter à l'envers pour eviter de "pousser" un commentaire deja poussé.
        if (this->isCommentedPos(displaced_pos)) {
            if (displaced_pos <= length + 1) {
                // Remove comments
                this->removeComment(displaced_pos);
            
            } else {
                // Displace comments
                this->displaceComment(displaced_pos, displaced_pos - length);
            }
            

        }
    }

}




void FastaSequence::addComment(size_t position, std::string comment) {
    // 0 is not preocessed
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
        throw std::invalid_argument(" Current position do not have any comment.");
    }

    std::string comment = this->getComment(current_position);
    this->removeComment(current_position);
    this->addComment(new_position, comment);
}

std::string FastaSequence::getComment(size_t position) const {
    if (this->isCommentedPos(position)){
        return this->comments.at(position);
    } 
    return "";
}

bool FastaSequence::isCommentedPos(size_t position) const {
    return (this->comments.count(position) >= 1);
}

/* Unusable function for now. Since Sequences use BitVector, they do not have a toString() member.
    * 
std::string FastaSequence::toString() const {
    return toString(10, 6, true);
}

std::string FastaSequence::toString(bool comments) const {
    return toString(10, 6, comments);
}

std::string FastaSequence::toString(unsigned int word_size, bool comments) const {
    return toString(word_size, 6, comments);
}

std::string FastaSequence::toString(unsigned int word_size, unsigned int paragraph_size, bool comments) const {
    std::string result = "";
    const std::string& seq = this->getSeq();
 
    unsigned int current_paragraph_size = 0;
    unsigned int current_word_size = 0;

    size_t pos = 0;
    for (char c : seq) {
        result += c;
        pos += 1;

        current_word_size += 1;

        if (comments && this->isCommentedPos(pos)) {
            result += " ;" + this->getComment(pos) + '\n';
            current_paragraph_size = 0;
            current_word_size = 0;
        }

        else if (current_word_size >= word_size) {
            if (word_size > 0) {
                // When word_size == 0, a word have the same size as a paragraph
                result += ' ';
            }
            current_word_size = 0;

            current_paragraph_size += 1;

            if (current_paragraph_size >= paragraph_size) {

                if (paragraph_size > 0) {
                    result += '\n';
                }
                current_paragraph_size = 0;

            }
        }
    }

    return result;
}
*/