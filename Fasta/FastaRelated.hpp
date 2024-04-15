#ifndef FASTACONSTS_HPP
#define FASTACONSTS_HPP
#include <set>

/**
 * @brief Class inherited by all class related to FastaFiles
 */
class FastaRelated {
private:
    /**
     * @brief Contain chars that can be used in multiple line header
     */
    static std::set<char> legalMultiHeaderChar;
    
    /**
     * @brief Contain chars that can be used in mono line header
     */
    static std::set<char> legalMonoHeaderChar;

    /**
     * @brief Contain chars that can be used to mark a comment
     */
    static std::set<char> legalCommentChar;

    /**
     * @brief Contain chars that can be ignored
     */
    static std::set<char> blankChar;

public:
    /**
     * @brief Do this char can mark a header
     * 
     * @param header_char A char
     * @return true Yes it can
     * @return false No it can't
     */
    static bool isHeaderChar(char header_char);

    /**
     * @brief Do this char can mark a mono line header
     * 
     * @param header_char A char
     * @return true Yes it can
     * @return false No it can't
     */
    static bool isMonoHeaderChar(char header_char);

    /**
     * @brief Do this char can mark a multiple line header
     * 
     * @param header_char A char
     * @return true Yes it can
     * @return false No it can't
     */
    static bool isMultiHeaderChar(char header_char);

    /**
     * @brief Do this char can mark a comment in a sequence
     * 
     * @param header_char A char
     * @return true Yes it can
     * @return false No it can't
     */
    static bool isCommentChar(char comment_char);


    /**
     * @brief Do this char can bbe ignored.
     * 
     * @param header_char A char
     * @return true Yes it can
     * @return false No it can't
     */
    static bool isBlankChar(char blank);
};





#endif