#include "Game.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

Game::Game() {
    m_running = true;
    if(! m_window_texture.loadFromFile("assets/pics/galaxy.jpg")) {
        std::cerr << "m window texture loading failed\n";
    }
    m_window_sprite.setTexture(m_window_texture);
}

void Game::Run() {
        sInit();
    while(m_running) {
        sInput();
        sMovement();
        sUpdate();
        sRender();
    }
}

void Game::sInit() {
    m_window.create(sf::VideoMode(800,600),"Space shooter",sf::Style::Close);
    m_window.setFramerateLimit(60);
}

void Game::sUpdate() {
    
}

void Game::sMovement() {

}

void Game::sRender() {

    m_window.draw(m_window_sprite);
    m_window.display();
}

void Game::sInput() {
    sf::Event e;
    while (m_window.pollEvent(e)!= 0) {
        switch (e.type) {
        case sf::Event::Closed:
            m_running = false;
            break;
        case sf::Event::KeyPressed:
            if(e.key.code == sf::Keyboard::Escape) {
                m_running = false;
            }

            if(e.key.code == sf::Keyboard::A) {
                m_window.clear(sf::Color(0xFF,0x00,0x00));
            }
            break;
        default:
            break;
        }
    }
}