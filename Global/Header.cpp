#include "Header.hpp"
#include <string>

std::string Header::getComment () {
    return this->_comment;
}

void Header::setComment (std::string comment) {
    this->_comment = comment;
}

std::string Header::getAccession () {
    return this->_accession;
};

void Header::setAccession (std::string accession) { 
    this->_accession = accession;
}
