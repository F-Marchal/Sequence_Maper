#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <stdexcept>
#include <iostream>
#include "Utilities.hpp"

enum errorMods {
    ignore  = 0,
    display = 1, 
    raise   = 2,
};

std::string makeErrorMessage(std::string message, std::string file_name, std::string function_name) ;

void displayInvalidArgument(errorMods error_mod, std::string message, std::string file_name, std::string function_name) ;

void displayLogicError(errorMods error_mod, std::string message, std::string file_name, std::string function_name) ;

void displayDomainError(errorMods error_mod, std::string message, std::string file_name, std::string function_name) ;

void displayLengthError(errorMods error_mod, std::string message, std::string file_name, std::string function_name);

void displayOutOfRangeError(errorMods error_mod, std::string message, std::string file_name, std::string function_name);

unsigned int getFirstDigits(size_t number, unsigned int digits);

#endif