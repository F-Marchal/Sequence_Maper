#ifndef HEADER_HPP
#define HEADER_HPP

#include <string>
/**
 * @brief Represent the header of a Fasta / FastQ file. 
 * 
 */
class Header { 
private:
    /**
     * @brief Comments that can be found inside the header (After the accession number / key)
     */
    std::string _comment;

    /**
     * @brief The Accession number contained inside the header
     */
    std::string _accession;


public:
    /**
     * @brief Get the comments related to this header;
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return std::string 
     * 
     */
    const std::string & getComment () const;

    /**
     * @brief Change the comments related to this header;
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @param comment New comments
     */
    void setComment (std::string comment);

    /**
     * @brief Get the accession number / key contained inside this header;
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @return std::string A string
     */
    const std::string & getAccession () const;
    
    /**
     * @brief Set the accession number / key contained inside this header;
     * | Complexity | |
     * |-------|------|
     * | Time  | O(1) |
     * | Space | O(1) |
     * @param accession An accession number / key
     */
    void setAccession (std::string accession);

};

#endif