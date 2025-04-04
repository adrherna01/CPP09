#include "BitcoinExchange.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <sys/_types/_size_t.h>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	_dataBaseMap = other._dataBaseMap;
	_inputMap = other._inputMap;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	_dataBaseMap = other._dataBaseMap;
	_inputMap = other._inputMap;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::parseLineDataBase(const string& line) {
	size_t commaPos = line.find(',');

	string date = trim(line.substr(0, commaPos));
	string value = trim(line.substr(commaPos + 1));

	if (isDateValid(date) || isValueValid(value))
		throw (std::runtime_error("Invalid line"));

	float fValue = std::stof(value);
	_dataBaseMap.insert(valuePair(date, fValue));

	// std::cout << "|" << date << "|" << std::endl;
	// std::cout << "|" << value << "|" << std::endl;
	// std::cout << std::endl;
}

void BitcoinExchange::parseDataBase(const string& fileName) {
	std::ifstream	file(fileName);
	string			line;
	string			date;
	float			value;

	while (std::getline(file, line))
	{
		// Might to a try catch here an throw and error for bad formating
		parseLineDataBase(line);
	}
}

void BitcoinExchange::parseLineInputFile(const string& line) {
	size_t commaPos = line.find('|');

	string date = trim(line.substr(0, commaPos));
	string value = trim(line.substr(commaPos + 1));

	if (isDateValid(date) || isValueValid(value))
		throw (std::runtime_error("Invalid line"));

	float fValue = std::stof(value);
	_inputMap.insert(valuePair(date, fValue));

	// std::cout << "|" << date << "|" << std::endl;
	// std::cout << "|" << value << "|" << std::endl;
	// std::cout << std::endl;
}

void BitcoinExchange::parseInputFile(const string& fileName) {
	std::ifstream	file(fileName);
	string			line;
	string			date;
	float			value;

	while (std::getline(file, line))
	{
		// Might to a try catch here an throw and error for bad formating
		parseLineInputFile(line);
	}
}

bool isValueValid(const string& value) {
	if (isNumeric(value) || isValidFormat(value) || stof(value) > 1000)
		return false;
	return true;
}

string trim(const std::string& str) {
	size_t start = 0;
	while (start < str.length() && std::isspace(str[start])) {
		start++;
	}

	size_t end = str.length();
	while (end > start && std::isspace(str[end - 1])) {
		end--;
	}

	return str.substr(start, end - start);

}

bool isNumeric(const std::string& str) {
	for (char ch : str)
	{
		if (ch == '.')
			continue;
		if (!std::isdigit(ch))
			return false;
	}
	return true;
}

bool isValidFormat(const std::string& value)
{
	int count = std::count(value.begin(), value.end(), '.');
	if (count > 1)
		return false;
	return true;
}
