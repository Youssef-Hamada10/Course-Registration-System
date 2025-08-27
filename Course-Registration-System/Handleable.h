#pragma once
#include <string>

class Handleable
{
public:
	static bool toContinue();
	static int handlingInt(std::string numberName);
	static int handlingChoiceNotFound(int maxChoice);
	static std::string emptyString(std::string text, std::string message);
	static std::string handlingMinInputs(std::string value, int min = 11);
	static std::string handlingNumbers(std::string value, std::string message = "TelephoneNumber");
	static std::string trim(std::string value);
	static std::string toLowerCase(std::string value);
	static std::string toUpperCase(std::string value);
};