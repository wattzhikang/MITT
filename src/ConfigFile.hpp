#include <string>
#include <vector>
#include <map>

class ConfigFile {
	private:
		std::map<std::string, std::string> properties;
		std::map<std::string, std::vector<ConfigFile*>> sections;

		void eat_whitespace(std::string& content,
				std::string::iterator& itr,
				std::string::iterator end);
		std::string get_token(std::string& content,
				std::string::iterator& itr,
				std::string::iterator end);
		std::string readUntilWhitespace(std::string& content,
				std::string::iterator& itr,
				std::string::iterator end);
		void eatUntilCloseBracket(std::string& content,
				std::string::iterator& itr,
				std::string::iterator end);
		std::string readUntilNextSection(std::string& content,
				std::string::iterator& itr,
				std::string::iterator end);
	public:
		ConfigFile(std::string);

		std::string to_string();

		std::vector<ConfigFile> getSections(std::string);

		std::string getToken(std::string);
};
