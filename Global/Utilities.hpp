#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <stdexcept>
#include <iostream>
#include "Utilities.hpp"

/**
 * @brief Change the behaviour of "display" functions.
 * - ignore : Errors are not thrown nor shown.
 * - display : Errors are not thrown but are shown.
 * - raise : throw an error.
 */
enum errorMods {
    ignore  = 0,
    display = 1, 
    raise   = 2,
};

/**
 * @brief Generate a message for the 'display' functions by the concatenation of a \p message with \p file_name and a \p function_name.
 * | Complexity | |
 * |-------|------|
 * | Time  | O(n) |
 * | Space | O(n^2)| 
 * n = message.size() + file_name.size() + function_name.size()
 * @param message The text displayed inside the message.
 * @param file_name Name of the file that contain the function that use the message. (__FILE__)
 * @param function_name Name of the function that use the message. (__func__) 
 * @return std::string {Message} | function={function_name} file={file_name}
 */
std::string makeErrorMessage(std::string message, std::string file_name, std::string function_name) ;

/**
 * @brief Throw / show / ignore an std::invalid_argument using an errorMods as a switch.
 * | Complexity | |
 * |-------|------|
 * | Time  | O(n) |
 * | Space | O(n^2)| 
 * n = message.size() + file_name.size() + function_name.size()
 * @param error_mod ignore=hide the error ; display=cout the message ; raise=throw the error;
 * @param message The text displayed inside the message.
 * @param file_name Name of the file that contain the function that use the message. (__FILE__)
 * @param function_name  Name of the function that use the message. (__func__) 
 */
void displayInvalidArgument(errorMods error_mod, std::string message, std::string file_name, std::string function_name) ;

/**
 * @brief Throw / show / ignore an std::logic_error using an errorMods as a switch.
 * | Complexity | |
 * |-------|------|
 * | Time  | O(n) |
 * | Space | O(n^2)| 
 * n = message.size() + file_name.size() + function_name.size()
 * @param error_mod ignore=hide the error ; display=cout the message ; raise=throw the error;
 * @param message The text displayed inside the message.
 * @param file_name Name of the file that contain the function that use the message. (__FILE__)
 * @param function_name  Name of the function that use the message. (__func__) 
 */
void displayLogicError(errorMods error_mod, std::string message, std::string file_name, std::string function_name) ;

/**
 * @brief Throw / show / ignore an std::domain_error using an errorMods as a switch.
 * | Complexity | |
 * |-------|------|
 * | Time  | O(n) |
 * | Space | O(n^2)| 
 * n = message.size() + file_name.size() + function_name.size()
 * @param error_mod ignore=hide the error ; display=cout the message ; raise=throw the error;
 * @param message The text displayed inside the message.
 * @param file_name Name of the file that contain the function that use the message. (__FILE__)
 * @param function_name  Name of the function that use the message. (__func__) 
 */
void displayDomainError(errorMods error_mod, std::string message, std::string file_name, std::string function_name) ;

/**
 * @brief Throw / show / ignore an std::length_error using an errorMods as a switch.
 * | Complexity | |
 * |-------|------|
 * | Time  | O(n) |
 * | Space | O(n^2)| 
 * n = message.size() + file_name.size() + function_name.size()
 * @param error_mod ignore=hide the error ; display=cout the message ; raise=throw the error;
 * @param message The text displayed inside the message.
 * @param file_name Name of the file that contain the function that use the message. (__FILE__)
 * @param function_name  Name of the function that use the message. (__func__) 
 */
void displayLengthError(errorMods error_mod, std::string message, std::string file_name, std::string function_name);

/**
 * @brief Throw / show / ignore an std::out_of_range using an errorMods as a switch.
 * | Complexity | |
 * |-------|------|
 * | Time  | O(n) |
 * | Space | O(n^2)| 
 * n = message.size() + file_name.size() + function_name.size()
 * @param error_mod ignore=hide the error ; display=cout the message ; raise=throw the error;
 * @param message The text displayed inside the message.
 * @param file_name Name of the file that contain the function that use the message. (__FILE__)
 * @param function_name  Name of the function that use the message. (__func__) 
 */
void displayOutOfRangeError(errorMods error_mod, std::string message, std::string file_name, std::string function_name);

/**
 * @brief Display (or not) a message using an errorMods as a switch.
 * | Complexity | |
 * |-------|------|
 * | Time  | O(1) |
 * | Space | O(1) | 
 * @param error_mod ignore=nothing ; display (or superior)=cout the message
 * @param message The text that should be displayed
 */
void displayMessage(errorMods error_mod, std::string message);

/**
 * @brief return the first (right) digit of a number.
 * | Complexity | |
 * |-------|------|
 * | Time  | O(n) |
 * | Space | O(n) | 
 *  n = max(number of digit in \p number , digits)
 *  Function vastly inspired by https://stackoverflow.com/questions/62857025/how-do-i-get-the-only-the-first-3-digits-of-a-number
 * @param number an integer
 * @param digits the number of wanted digit
 * @return unsigned int 
 */
unsigned int getFirstDigits(size_t number, unsigned int digits);

/**
 * @brief Multiply two number and assure that the result can not be greater than \p maximal_value
 * | Complexity | |
 * |-------|------|
 * | Time  | O(1) |
 * | Space | O(1) | 
 * @param a first number
 * @param b second value
 * @param maximal_value value that should not be 
 * @return size_t \p a * \p b if \p a * \p b lower than \p maximal_value else \p maximal_value
 */
size_t safe_multiply(size_t a, size_t b, size_t maximal_value);

/**
 * @brief Display a char as it was a bit.
 * | Complexity | |
 * |-------|------|
 * | Time  | O(1) |
 * | Space | O(1) | 
 * @param bits the car that should be displayed
 * @param endl if true, endl is used at the end
 */
void displayBits(char bits, bool endl=true);

#endif