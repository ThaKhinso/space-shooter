#pragma once
#include "Common.h"
#include <SFML/Graphics/Sprite.hpp>

class CShape{
private:
sf::Texture texture;
public:
    sf::Sprite sprite;
    
    
    CShape(const std::string& path) {
        if(!texture.loadFromFile(path) ) {
            std::cerr << "Loading img from " << path << " failed." << std::endl;
        }
        sprite.setTexture(texture);
    };
    ~CShape(){};
};