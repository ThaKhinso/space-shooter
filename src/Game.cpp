#include "Game.h"
#include "CCollision.h"
#include "CInput.h"
#include "CLifeSpan.h"
#include "CShape.h"
#include "CTransform.h"
#include "Vec2.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

Game::Game()
    :f(0), velx(0), vely(0) {
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
    auto player = m_entities.addEntity("player");
    Vec2 middleWindowPos{ m_window.getSize().x * 0.5, m_window.getSize().y * 0.5 };
    player->ctransform = std::make_shared<CTransform>(middleWindowPos, Vec2(0,0));
    player->cshape = std::make_shared<CShape>("assets/pics/player.png");
    player->collision = std::make_shared<CCollision>(Vec2(player->cshape->sprite.getPosition().x,player->cshape->sprite.getPosition().y),Vec2(velx,vely));
    player->cinput = std::make_shared<CInput>();
    player->clifespan = std::make_shared<CLifeSpan>();
    m_player = player;
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
        
        printf("String value: %s\n",buf);
        printf("Float value: %f\n",f);
    }
    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::SliderFloat("speed for x axis", &velx, 0.0f, 30.f);
    ImGui::SliderFloat("speed for x axis", &vely, 0.0f, 30.f);
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

            if(e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up) {
                m_player->cinput->up = true;
            }

            if(e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down) {
                m_player->cinput->down = true;
            }

            if(e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left) {
                m_player->cinput->left = true;
            }

            if(e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right) {
                m_player->cinput->right = true;
            }

            break;
        default:
            break;
        }
    }
    ImGui::SFML::Update(m_window,deltaclock.restart());
}

void Game::sCollisoin() {
    for (auto e : m_entities.getEntities("player"))
	{
		//Checks to see if player collided with walls
		if (e->ctransform->pos.x + m_playerConfig.CR > m_window.getSize().x)
		{
			e->cTransform->pos.x -= m_playerConfig.S;
		}
		else if (e->cTransform->pos.x - m_playerConfig.CR < 0)
		{
			e->cTransform->pos.x += m_playerConfig.S;
		}

		if (e->cTransform->pos.y + m_playerConfig.CR > m_window.getSize().y)
		{
			e->cTransform->pos.y -= m_playerConfig.S;
		}
		else if (e->cTransform->pos.y - m_playerConfig.CR < 0)
		{
			e->cTransform->pos.y += m_playerConfig.S;
		}
	}
}