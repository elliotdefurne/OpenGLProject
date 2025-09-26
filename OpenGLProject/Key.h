#pragma once
#include <string>
#include <iostream>

#include "Player.h"

class Key {
	public:
		Key(Player* player, const std::string& name, int key) : m_name(name), m_key(key), m_player(player), m_isPressed(false) {}
		virtual ~Key() {}
		const std::string& getKeyName() const { return m_name; }
		int getKey() const { return m_key; }
		virtual void onPress() = 0;
		virtual void onRelease() = 0;
		virtual void ifPressed() = 0;
		bool getStatus() const { return m_isPressed; }

	protected:
		Player* m_player;
		const std::string m_name;
		const int m_key;

		bool m_isPressed;
};