#pragma once

#include <string>

typedef void(*action)();

class MenuEntry {
	public:
		MenuEntry(std::string name, action function, int special = 0, bool isActive = true) : _name(name), _special(special), _isActive(isActive), _function(function) { }

		operator std::string() { return _name; }
		std::string& Name() { return _name; }
		int Special() { return _special; }
		operator bool() { return _isActive; }
		bool IsActive() { return _isActive; }
		void ChangeActive() { _isActive = !_isActive; }

		void operator()() { _function(); }

	private:
		std::string _name;
		int _special = 0;
		bool _isActive;
		void(*_function)();
};