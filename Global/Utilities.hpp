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

void displayMessage(errorMods error_mod, std::string message);

unsigned int getFirstDigits(size_t number, unsigned int digits);

size_t safe_multiply(size_t a, size_t b, size_t maximal_value);

void displayBits(char bits, bool endl=true);

#endif