#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <unordered_map>

#include "Key.h"
#include "Forward.h"


class KeyManager {
    public:
        KeyManager() { loadKeys(); };
        ~KeyManager() {
        
        };
        void loadKeys() {
            
        }
        Key* getKey(const std::string& name) {
			return keys.at(name);
        }
    private:
        std::unordered_map<std::string& , Key> keys;
};
