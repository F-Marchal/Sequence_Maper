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

 unsigned int getFirstDigits(size_t number, unsigned int digits) {
    // https://stackoverflow.com/questions/62857025/how-do-i-get-the-only-the-first-3-digits-of-a-number
    std::string str_number = std::to_string(number);

    if (str_number.size() <= digits) {
        return number;
    }

    return std::stoi(str_number.substr(str_number.size() - digits, str_number.size() - 1));
}

size_t safe_multiply(size_t a, size_t b, size_t maximal_value) {
    if (a == 0 || b == 0) {
        // Avoid division by 0 in the next condition
        return 0;

    } else if (a > maximal_value / b) {
        // Le résultat de la multiplication dépasserait SIZE_MAX.
        return maximal_value;

    } else {
        return a * b;
    }
}

void displayBits(char bits, bool endl) {
    for (int i = 7; i >= 0; --i) {
        std::cout << ((bits >> i) & 1); // Extract each bit
    }
    if (endl) {
        std::cout << std::endl;
    }
}
