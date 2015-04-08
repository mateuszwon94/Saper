#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <string>

class MenuEntry {
	public:
	MenuEntry(std::string name, int special = 0);

	operator std::string() { return _name; }
	std::string& Name() { return _name; }
	int Special() { return _special; }

	private:
	std::string _name;
	int _special = 0;
};



#endif