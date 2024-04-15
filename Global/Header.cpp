#include "Header.hpp"
#include <string>

const std::string & Header::getComment () const {
    return this->_comment;
}

void Header::setComment (std::string comment) {
    this->_comment = comment;
}

const std::string & Header::getAccession () const {
    return this->_accession;
};

void Header::setAccession (std::string accession) { 
    this->_accession = accession;
}
