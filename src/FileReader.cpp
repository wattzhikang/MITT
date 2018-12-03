#include "FileReader.hpp"

std::string file_to_string(std::string name) {
        std::ifstream file;
        file.open(name);

	std::string fileOut;

        if (file) {
                std::cout << "Success !" << std::endl;

		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		std::cout << length << std::endl;

		char* buffer = new char[length + 1];
		file.read(buffer, length);
		buffer[length] = '\0';
		
		fileOut = buffer;
        }

        file.close();

	return fileOut;
}
