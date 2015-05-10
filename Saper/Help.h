#pragma once
#include <map>
#include <string>
#include <vector>

class Help {
	public:
		//Help(unsigned int posibleToWriteChars, unsigned int possibleToWriteLines, unsigned int line = 0, unsigned int column = 0);
		/*~Help();

		std::vector<std::string>& operator[](const std::string &key) { return _help[key]; }

		static Help& current() { return *_currentHelp; }

		void View();

	private:
		std::map<std::string, std::vector<std::string>> _help;
		static Help* _currentHelp;
		unsigned int _posLine;
		unsigned int _posColumn;
		unsigned int _posibleToWriteChars;
		unsigned int _possibleToWriteLines;
*/
		static void View();
};
