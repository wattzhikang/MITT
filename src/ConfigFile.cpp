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

void ConfigFile::setUnits(ConfigFile unitFile) {
	ConfigFile* lengths = unitFile.getSections("length")[0];
	for (auto property : lengths->properties) {
		units[ut_distance][property.first] = lengths->getDouble(property.first);
	}

	lengths = unitFile.getSections("angle")[0];
	for (auto property : lengths->properties) {
		units[ut_angle][property.first] = lengths->getDouble(property.first);
	}

	for (auto sectionVector : sections) {
		for (auto section : sectionVector.second) {
			section->units = units;
		}
	}
}

void ConfigFile::setUnits(std::map<unitType, std::map<std::string, double>> inputUnits) {
	units = inputUnits;
}

ConfigFile::valUnit ConfigFile::getValueUnit(const std::string& key) {
	if (properties.find(key) == properties.end()) {
		//"Error: property [key] not found"
	}

	valUnit info;
	std::stringstream ss(properties[key]);

	ss >> info.value >> info.unit;

	return info;
}

double ConfigFile::getDistance(const std::string& key) {
	valUnit info = getValueUnit(key);

	if (info.unit.length()) {
		if (units[ut_distance].find(info.unit) == units[ut_distance].end()) {
			//Error: unit not found
		} else {
			info.value *= units[ut_distance][info.unit];
		}
	}

	return info.value;
}

double ConfigFile::getAngle(const std::string& key) {
	valUnit info = getValueUnit(key);

	if (info.unit.length()) {
		if (units[ut_angle].find(info.unit) == units[ut_angle].end()) {
			//Error: unknown unit
		} else {
			info.value *= units[ut_angle][info.unit];
		}
	}

	return info.value;
}

double ConfigFile::getDouble(const std::string& key) {
	valUnit info = getValueUnit(key);

	return info.value;
}

std::string ConfigFile::getToken(const std::string& key) {
	if (properties.find(key) == properties.end()) {
		//throw exception or whatever you do in C++
	}

	std::stringstream ss(properties[key]);

	std::string token;

	ss >> token;

	return token;
}

std::vector<ConfigFile*>& ConfigFile::getSections(const std::string& content) {
	return sections[content];
}

ConfigFile::ConfigFile(std::string content) {
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
	ConfigFile* sectionHolder;

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
		sectionHolder = new ConfigFile(section);
		sectionHolder->setUnits(units);
		sections[type].push_back(sectionHolder);
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
