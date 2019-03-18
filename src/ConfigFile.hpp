#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <string>
#include <vector>
#include <map>
#include <sstream>

class ConfigFile {
	private:
		std::map<std::string, std::string> properties;
		std::map<std::string, std::vector<ConfigFile*>> sections;

		enum unitType {
			ut_distance,
			ut_angle,
			ut_date,
		};
		std::map<unitType, std::map<std::string, double>> units;

		void setUnits(std::map<unitType, std::map<std::string, double>>);

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

		struct valUnit {
			double value;
			std::string unit;
		};

		valUnit getValueUnit(const std::string& key);
	public:
		ConfigFile(std::string);

		void setUnits(ConfigFile);

		std::string to_string();

		std::vector<ConfigFile*>& getSections(const std::string&);

		std::string getToken(const std::string&);
		double getDistance(const std::string&);
		double getAngle(const std::string&);
		double getDate(const std::string&);
		double getDouble(const std::string&);
};

#endif