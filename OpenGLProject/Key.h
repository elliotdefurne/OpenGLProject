#include <string>
#include <iostream>

class Key {
public:
	Key(const std::string& name, int key) : m_name(name), m_key(key) {}
	virtual ~Key() {}
	const std::string& getKeyName() const { return m_name; }
	int getKey() const { return m_key; }
	virtual void onPress() const = 0;
	virtual void onRelease() const = 0;

protected:
	const std::string m_name;
	const int m_key;
};