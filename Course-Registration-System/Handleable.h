#pragma once
#include <string>

class Handleable
{
public:
	static bool toContinue();
	static int handlingInt(std::string numberName);
	static int handlingChoiceNotFound(int maxChoice);
	static std::string emptyString(std::string text, std::string message);
	static std::string handlingUsername(std::string username);
};