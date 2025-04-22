#include <string>
class Handleable
{
public:
	static bool toContinue();
	static int handlingInt(std::string numberName);
	static int handlingChoiceNotFound(int maxChoice);
	static std::string handlingUsername(std::string username);
};