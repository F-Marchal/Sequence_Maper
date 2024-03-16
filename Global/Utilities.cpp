#include <string>
#include <stdexcept>
#include <iostream>
#include "Utilities.hpp"

std::string makeErrorMessage(std::string message, std::string file_name, std::string function_name) {
    return message + " | " + "function=" + function_name + " file=" + file_name + ".";
}

void displayInvalidArgument(errorMods error_mod, std::string message, std::string file_name, std::string function_name) {
    message = makeErrorMessage(message, file_name, function_name);
    
     if (error_mod >= raise) {
        throw std::invalid_argument(message);
    }
    if (error_mod >= display) {
        std::cout << "(invalid argument ignored) " << message << std::endl;
     } 
}

void displayLogicError(errorMods error_mod, std::string message, std::string file_name, std::string function_name) {
    message = makeErrorMessage(message, file_name, function_name);
    
     if (error_mod >= raise) {
        throw std::logic_error(message);
    }
    if (error_mod >= display) {
        std::cout << "(logic error ignored) " << message << std::endl;
     } 
}

void displayDomainError(errorMods error_mod, std::string message, std::string file_name, std::string function_name) {
    message = makeErrorMessage(message, file_name, function_name);
    
     if (error_mod >= raise) {
        throw std::domain_error(message);
    }
    if (error_mod >= display) {
        std::cout << "(domain error ignored) " << message << std::endl;
     } 
}

void displayLengthError(errorMods error_mod, std::string message, std::string file_name, std::string function_name) {
    message = makeErrorMessage(message, file_name, function_name);
    
     if (error_mod >= raise) {
        throw std::length_error(message);
    }
    if (error_mod >= display) {
        std::cout << "(length error ignored) " << message << std::endl;
     } 
}

void displayOutOfRangeError(errorMods error_mod, std::string message, std::string file_name, std::string function_name) {
    message = makeErrorMessage(message, file_name, function_name);
    
     if (error_mod >= raise) {
        throw std::out_of_range(message);
    }
    if (error_mod >= display) {
        std::cout << "(out of range error ignored) " << message << std::endl;
     } 
}