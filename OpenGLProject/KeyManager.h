#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <memory>

#include "Key.h"
#include "Forward.h"

class KeyManager {
public:
    KeyManager() { loadKeys(); }

    ~KeyManager() {
        for (auto& pair : m_keys) {
            delete pair.second;
        }
    }

    void loadKeys() {
        m_keys["Forward"] = new Forward();
        // Ajoutez d'autres touches ici
    }

    Key* getKey(const std::string& name) {
        auto it = m_keys.find(name);
        if (it != m_keys.end()) {
            return it->second;
        }
        throw std::out_of_range("Key not found: " + name);
    }

private:
    std::unordered_map<std::string, Key*> m_keys;
};