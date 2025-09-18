#pragma once

#include <string>
#include <iostream>

class Key {
	public:
		Key() {}
		virtual ~Key() {}
		const std::string getKeyName() { return m_name; };
		const int getKey() { return m_key; };
		virtual void onPress() const = 0;
		virtual void onRelease() const = 0;
	private:
		const std::string m_name;
		const int m_key = 0;
};