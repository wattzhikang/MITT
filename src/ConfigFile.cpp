#include "ConfigFile.hpp"

//TODO There's a ton of code duplication in these functions. I should do
//something about it
//
//TODO There's no check for EOF in these methods

void ConfigFile::eat_whitespace(std::string& content, std::string::iterator& itr,
		std::string::iterator end) {
	for (; isspace(*itr) && itr < end; itr++);
}

std::string ConfigFile::get_token(std::string& content, std::string::iterator& itr,
		std::string::iterator end) {
	std::string tok;
	for (; !isblank(*itr) && *itr != ']' && itr < end; itr++) {
		tok += *itr;
	}
	return tok;
}

std::string ConfigFile::readUntilWhitespace(std::string& content,
		std::string::iterator& itr, std::string::iterator end) {
	std::string val;
	for (; *itr != '\n' && itr < end; itr++) {
		val += *itr;
	}
	return val;
}

void ConfigFile::eatUntilCloseBracket(std::string& content,
		std::string::iterator& itr, std::string::iterator end) {
	for (; *itr != ']' && itr < end; itr++);
	itr++; //places iterator /after/ the close bracket
}

std::string ConfigFile::readUntilNextSection(std::string& content,
		std::string::iterator& itr, std::string::iterator end) {
	std::string sec;
	for (; *itr != '[' && itr < end; itr++) {
		sec += *itr;
	}
	return sec;
}

ConfigFile::ConfigFile(std::string content) {
	/*
	 * This constructor will accept the contents of a config file. It will
	 * parse the entire file, storing all properties in the properties map,
	 * where they will remain as uninterpreted strings. Every character
	 * between the '=' and the '\n' will go as the value of the property.
	 * Specific methods will interpret them. For example, a value such as
	 * " 21600 km" should be interpreted by getDistance().
	 *
	 * Sections will be stored as ConfigFiles, stored in the map structure
	 * in a vector. For example, all 'planet' or 'maneuver' sections will
	 * be hashed under "planet" and "maneuver" in the map, respectively.
	 */

	std::string::iterator itr = content.begin();
	std::string::iterator end = content.end();

	eat_whitespace(content, itr, end);

	std::string name;
	std::string value;

	while (*itr != '[' && itr < end) {
		name = get_token(content, itr, end);
		eat_whitespace(content, itr, end);
		//TODO throw exception if there isn't an '='
		itr++; //for now just assume there is one
		value = readUntilWhitespace(content, itr, end);
		eat_whitespace(content, itr, end);

		properties.insert(std::pair<std::string,
				std::string>(name, value));
	}

	std::string type;
	std::string section;
	std::vector<ConfigFile*> emptyTypes;

	while (*itr == '[' && itr < end) {
		itr++; //TODO potential for seg fault

		type = get_token(content, itr, end);
		eatUntilCloseBracket(content, itr, end);
		section = readUntilNextSection(content, itr, end);

		if (sections.find(type) == sections.end()) {
			//create the vector
			sections.insert(
				std::pair<std::string, std::vector<ConfigFile*>>
					(type, emptyTypes)
				);
		}
		sections[type].push_back(new ConfigFile(section));
	}
}

std::string ConfigFile::to_string() {
	std::string sout;
	sout += "This configuration text contains the following";
	sout += " global properties: ";

	for (auto& keyVal : properties) {
		sout += keyVal.first + ": " + keyVal.second + "; ";
	}

	int i;
	for (auto& secType : sections) {
		sout += "\nThis configuration file contains ";
		sout += std::to_string(secType.second.size());
		sout += " sections of type ";
		sout += secType.first;
		sout += '\n';

		i = 0;
		for (auto& section : secType.second) {
			sout += "\t";
			sout += secType.first;
			sout += "text ";
			sout += std::to_string(i);
			sout += section->to_string();
			sout += '\n';
			i++;
		}
	}

	return sout;
}
