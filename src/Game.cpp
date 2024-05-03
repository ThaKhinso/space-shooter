#include "Game.h"
#include "imgui-SFML.h"
#include <SFML/System/Clock.hpp>

Game::Game() {
    m_running = true;
    if(! m_window_texture.loadFromFile("assets/pics/galaxy.jpg")) {
        std::cerr << "m window texture loading failed\n";
    }
    m_window_sprite.setTexture(m_window_texture);
}

void Game::Run() {
        sInit();
    // sf::Clock deltaclock;
    while(m_running) {
        sInput();
        sMovement();
        sUpdate();
        // ImGui::SFML::Update(m_window, deltaclock.restart());
        sRender();
    }
    ImGui::SFML::Shutdown(m_window);
}

void Game::spwanPlayer() {
    
}

void Game::sInit() {
    m_window.create(sf::VideoMode(800,600),"Space shooter",sf::Style::Close);
    m_window.setFramerateLimit(60);
    ImGui::SFML::Init(m_window);
}

void Game::sUpdate() {
    
}

void Game::sMovement() {

}

void Game::sRender() {
    // ImGui::SFML::Update(m_window, deltaclock.restart());
    
    ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save")){
        printf("nigga\n");
        printf("String value: %s\n",buf);
        printf("Float value: %f\n",f);
    }
    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    m_window.clear();
    m_window.draw(m_window_sprite);
    ImGui::SFML::Render(m_window);
    m_window.display();
}

void Game::sInput() {
    sf::Event e;
    while (m_window.pollEvent(e)!= 0) {
        ImGui::SFML::ProcessEvent(m_window,e);
        switch (e.type) {
        case sf::Event::Closed:
            m_running = false;
            break;
        case sf::Event::KeyPressed:
            if(e.key.code == sf::Keyboard::Escape) {
                m_running = false;
            }

            if(e.key.code == sf::Keyboard::A) {
                m_window.clear(sf::Color(0x00,0x00,0x00));
            }
            break;
        default:
            break;
        }
    }
    ImGui::SFML::Update(m_window,deltaclock.restart());
}