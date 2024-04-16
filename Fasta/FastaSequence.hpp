#ifndef FASTASEQUENCE_HPP
#define FASTASEQUENCE_HPP
#include "FastaRelated.hpp"
#include "../Global/Sequence.hpp"
#include <string>
#include <map>

/**
 * @brief Class that represent Sequence inside a fasta File.
 * Can hold comment
 * @warning NotImplemented
 */
class FastaSequence : public FastaRelated, public Sequence {
private:
    /**
     * @brief Map that hold comments 
     */
    std::map<size_t, std::string> comments;

public:
    /**
     * @brief Return comments contained inside this sequence
     * @return const std::map<size_t, std::string>& Position : comment
     */
    const std::map<size_t, std::string>& getAllComment() const {return this->comments;};

    FastaSequence() {
         displayLogicError(raise, "Unimplemented class. This class is not implemented yet.", __FILE__, __func__);
    }
    /**
     * @brief Same as Sequence::insert but should move comments when position is not at the end.
     * @warning not implemented
     * @param sequence The sequence
     * @param position Insertion position
     * @param error_mod Should error be raised / displayed / ignored
     */
    void insert(const std::string & sequence, size_t position, errorMods error_mod) ;

    // using Sequence::Sequence;

    // Polymorphism
    // void insertSeq(size_t position, std::string seq, bool verbose=false);
    // void insertSeq(size_t position, const FastaSequence & seq, bool verbose=false);
    void eraseSeq(size_t index, size_t length);




    // --- comments ---
    /**
     * @brief Add a comment to a position
     * 
     * @param position Where the comment should be placed
     * @param comment A comment
     */
    void addComment(size_t position, std::string comment);

    /**
    * @brief Load a number of comment from a map
    * 
    * @param comment_map A map that contain comments
    */
    void loadComments(std::map<size_t, std::string>& comment_map);

    /**
     * @brief Remove a comment
     * 
     * @param position Comment position
     */
    void removeComment(size_t position);
    /**
     * @brief Change the position of a comment. If a comment is present at \p new_position , The two comments are merged.
     * 
     * @param current_position Comment to displace
     * @param new_position Where the comment should be positioned a the end.
     */
    void displaceComment(size_t current_position, size_t new_position);
    
    /**
     * @brief Do this position is commented
     * 
     * @param position Position to test
     * @return true Yes
     * @return false No
     */
    bool isCommentedPos(size_t position) const;

    /**
     * @brief Retrieve the comment at the position \p position
     * 
     * @param position Where
     * @return std::string The comment
     */
    std::string getComment(size_t position) const;

    /* Unusable function for now. Since Sequences use BitVector, they do not have a toString() member.
     * 
    std::string toString() const;
    std::string toString(bool comments) const;
    std::string toString(unsigned int word_size, unsigned int paragraph_size, bool comments=true) const;
    std::string toString(unsigned int word_size, bool comments=true) const;
    */

};

#endif