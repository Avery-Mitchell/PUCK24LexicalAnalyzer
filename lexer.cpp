/*
	NAME: AVERY MITCHELL
	CLASS: CS3500
	ASSIGNMENT: HOMEWORK #1
*/

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

bool isKeyword(const std::string& input){
	return (input == "PROCEDURE" || input == "IF" || input == "THEN" || input == "WHILE" || input == "FUNCTION" || input == "WRITE");
}

bool isInteger(const std::string& input){
	try{
		size_t x;
		std::stoi(input, &x);
		return x == input.length();
	}
	catch (std::invalid_argument&){
		return false;
	}
	catch (std::out_of_range&){
		return false;
	}
}

bool isDecimal(const std::string& input){
	const int length = input.length();
	char* inputArray = new char[length+1];
	strcpy(inputArray, input.c_str());
	int integers = 0;
	int decimal = 0;
	bool isDecimal = false;
	if((inputArray[0] == '-') || (inputArray[0] == '+')){
		integers++;
	}
	for(int x=0; x<length; x++){
		if(isdigit(inputArray[x])){
			integers++;
		}
		else if(inputArray[x] == '.'){
			decimal++;
			isDecimal = true;
		}
	}
	if((decimal + integers == length) && (inputArray[length-1] != '.') && (isDecimal) && (decimal == 1) && (length != 0)){
		delete[] inputArray;
		return true;
	}
	delete[] inputArray;
	return false;
}

bool isScientific(const std::string& input){
	const int length = input.length();
	char* inputArray = new char[length+1];
	strcpy(inputArray, input.c_str());
	bool e = false;
	int eCount = 0;
	int eIndex = 0;
	std::string front = "";
	std::string back = "";
	int intBack = 0;
	for(int x=0; x<length; x++){
		if(inputArray[x] == 'E'){
			eIndex = x;
		}
		if(eCount > 1){
			delete[] inputArray;
			return false;
		}
	}
	for(int x=0; x<eIndex; x++){
		front.append(1, inputArray[x]);
	}
	for(int x=eIndex+1; x<length; x++){
		back.append(1, inputArray[x]);
	}
	if(isDecimal(front) && isInteger(back)){
		intBack = stoi(back);
		if(intBack != 0){
			return true;
		}
	}
	delete[] inputArray;
	return false;
}

bool isHexadecimal(const std::string& input){
	const int length = input.length();
	char* inputArray = new char[length+1];
	strcpy(inputArray, input.c_str());
	int characters = 0;
	int digits = 0;
	if(length == 0){
		delete[] inputArray;
		return false;
	}
	if(inputArray[length-1] != 'H'){
		delete[] inputArray;
		return false;
	}
	for(int x=0; x<length; x++){
		if(inputArray[x] == 'A' || inputArray[x] == 'B' || inputArray[x] == 'C' || inputArray[x] == 'D' || inputArray[x] == 'E' || inputArray[x] == 'F'){
			characters++;
		}
		else if(isdigit(inputArray[x])){
			digits++;
		}
	}
	if(characters + digits + 1 == length){
		delete[] inputArray;
		return true;
	}
	delete[] inputArray;
	return false;
}

bool isStringLiteral(const std::string& input){
	const int length = input.length();
	char* inputArray = new char[length+1];
	strcpy(inputArray, input.c_str());
	int characters = 0;
	if(length == 0){
		delete[] inputArray;
		return false;
	}
	if(inputArray[0] != '"' || inputArray[length-1] != '"'){
		delete[] inputArray;
		return false;
	}
	for(int x=0; x<length; x++){
		if(inputArray[x] != ' ' && inputArray[x] != '"'){
			characters++;
		}
	}
	if(characters + 2 == length){
		delete[] inputArray;
		return true;
	}
	delete[] inputArray;
	return false;
}

bool isCharacterLiteral(const std::string& input){
	const int length = input.length();
	char* inputArray = new char[length+1];
	strcpy(inputArray, input.c_str());
	int characters = 0;
	if(length != 3){
		delete[] inputArray;
		return false;
	}
	for(int x=0; x<length-1; x++){
		if(inputArray[x] == 'A' || inputArray[x] == 'B' || inputArray[x] == 'C' || inputArray[x] == 'D' || inputArray[x] == 'E' || inputArray[x] == 'F'){
			characters++;
		}
		else if(isdigit(inputArray[x])){
			characters++;
		}
	}
	if(inputArray[2] == 'X' && characters == 2){
		delete[] inputArray;
		return true;
	}
	delete[] inputArray;
	return false;
}

bool isIdentifier(const std::string& input){
	const int length = input.length();
	char* inputArray = new char[length+1];
	strcpy(inputArray, input.c_str());
	if(length == 0){
		delete[] inputArray;
		return false;
	}
	if((!isalpha(inputArray[0])) || isKeyword(input) || isHexadecimal(input) || isCharacterLiteral(input)){
		delete[] inputArray;
		return false;
	}
	for(int x=0; x<length; x++){
		if(inputArray[x] == ' ' || inputArray[x] == '.'){
			delete[] inputArray;
			return false;
		}
	}
	delete[] inputArray;
	return true;
}

int main(){

	// Variable Initialization
	int size;

	// Inputting the Strings
	std::cin >> size;
	std::string* strings = new std::string[size];
	for(int x=0; x<size; x++){
		std::cin >> strings[x];
	}

	// Code Goes Here:
	std::cout << size << std::endl;
	for(int x=0; x<size; x++){
		if(isKeyword(strings[x])){
			std::cout << x+1 << ": Keyword" << std::endl;
		}
		else if(isHexadecimal(strings[x])){
			std::cout << x+1 << ": Hexadecimal" << std::endl;
		}
		else if(isStringLiteral(strings[x])){
			std::cout << x+1 << ": String" << std::endl;
		}
		else if(isCharacterLiteral(strings[x])){
			std::cout << x+1 << ": Character" << std::endl;
		}
		else if(isInteger(strings[x])){
			std::cout << x+1 << ": Integer" << std::endl;
		}
		else if(isDecimal(strings[x])){
			std::cout << x+1 << ": Decimal" << std::endl;
		}
		else if(isScientific(strings[x])){
			std::cout << x+1 << ": Scientific" << std::endl;
		}
		else if(isIdentifier(strings[x])){
			std::cout << x+1 << ": Identifier" << std::endl;
		}
		else{
			std::cout << x+1 << ": INVALID!" << std::endl;
		}
	}

	delete[] strings;

	return 0;
}
