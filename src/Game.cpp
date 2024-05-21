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
#include <SFML/Window/WindowStyle.hpp>
#include <cstddef>
#include <memory>

Game::Game()
    :f(0), velx(0), vely(0), speed(10) {
    m_running = true;
    spwan = false;
    if(! m_window_texture.loadFromFile("assets/pics/galaxy.jpg")) {
        std::cerr << "m window texture loading failed\n";
        
    }
    m_window_sprite.setTexture(m_window_texture);
}

void Game::Run() {
        sInit();
        spwanEnemies();
    // sf::Clock deltaclock;
    while(m_running) {
        m_entities.update();
        // sSpwan();
        sInput();
        sMovement();
        sCollisoin();
        sUpdate();
        // ImGui::SFML::Update(m_window, deltaclock.restart());
        sRender();
    }
    ImGui::SFML::Shutdown(m_window);
}

void Game::spwanPlayer() {
    //auto player = m_entities.addEntity("player");
    Vec2 middleWindowPos{ m_window.getSize().x * 0.5, m_window.getSize().y * 0.5 };
    // std::cout << middleWindowPos << std::endl;
    //Vec2 speed(10,10);
    //
    //player->ctransform = std::make_shared<CTransform>(middleWindowPos, speed);

    //player->cshape = std::make_shared<CShape>("assets/pics/player.png",m_player->ctransform->pos);
    ///*Vec2 spritepos(player->cshape->sprite.getPosition().x, player->cshape->sprite.getPosition().y);*/
    //player->collision = std::make_shared<CCollision>(m_player->ctransform->pos,speed);
    //player->cinput = std::make_shared<CInput>();
    //player->clifespan = std::make_shared<CLifeSpan>(1);
    //m_player = player;

    auto player = m_entities.addEntity("Player");
    Vec2 speed{ 50,50 };
    player->cshape = std::make_shared<CShape>("assets/pics/player.png");
    player->cinput = std::make_shared<CInput>();
    player->ctransform = std::make_shared<CTransform>(middleWindowPos,speed);
    Vec2 size{ player->cshape->sprite.getLocalBounds().width, player->cshape->sprite.getLocalBounds().height};
    player->collision = std::make_shared<CCollision>(middleWindowPos, size);
    // std::cout << player->ctransform->pos << std::endl;
    m_player = player;
    // std::cout << m_player->tag() << std::endl;
}

void Game::sInit() {
    m_window.create(sf::VideoMode(800,600),"Space shooter",sf::Style::Close);
    m_window.setFramerateLimit(120);
    ImGui::SFML::Init(m_window);
    spwanPlayer();
}

void Game::sUpdate() {
    
}

void Game::sMovement() {
    Vec2 playervelocity{ 0,0 };
    if (m_player->cinput->left == true) {
        //std::cout << "left\n";
        playervelocity.x -= speed;
    }

    if (m_player->cinput->right == true) {
        //std::cout << "right\n";
        playervelocity.x += speed;
    }

    if (m_player->cinput->up == true) {
        //std::cout << "up\n";
        playervelocity.y -= speed;
    }
    
    if (m_player->cinput->down == true) {
        //std::cout << "down\n";
        playervelocity.y += speed;
    }
    //std::cout << m_player->tag() << std::endl;
    /*for (auto e : m_entities.getEntities("Player")) {
        std::cout << "Player does exist\n";
    }*/
    for (auto e : m_entities.getEntities()) {
        if (e->tag() == "Player") {
            // std::cout << "Playercmp\n";
            m_player->ctransform->pos += playervelocity;
        }

        if(spwan){
            
                Vec2 bullet_pos{m_player->ctransform->pos.x + 2.5, m_player->ctransform->pos.y - e->cshape->sprite.getLocalBounds().height};
                spwanBullet(bullet_pos);
            
        }
        if (e->tag() == "Bullet") {
            e->ctransform->pos.y -= 10;
        }
        if (e->tag() == "Enemy") {
            e->ctransform->pos.y += 0.5;
        }
        /*if (strcmp("nigga", "nigga") == 0) {
            std::cout << "string compare success\n";
        }*/
    }

    //update collision position
    Vec2 player_pos { m_player->ctransform->pos };
    // Vec2 bullet_pos { m_player->ctransform->pos.x + 2.5, m_player->ctransform->pos.y -  };
    m_player->collision->position = player_pos;
    // if(spwan == true) {
    //     spwanBullet(player_pos);
    // }
    // std::cout << "This is collision: ";
    // std::cout << m_player->collision->position << std::endl;
    // std::cout << "This is transform: ";
    // std::cout << m_player->ctransform->pos << std::endl;
    m_player->cinput->left = false;
    m_player->cinput->right = false;
    m_player->cinput->up = false;
    m_player->cinput->down = false;
    spwan = false;
}

void Game::sRender() {
    // ImGui::SFML::Update(m_window, deltaclock.restart());
    m_window.clear();
    ImGui::Begin("Nigga");
    ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save")){
        
        printf("String value: %s\n",buf);
        printf("Float value: %f\n",f);
    }
    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::SliderFloat("speed", &speed, 0.0f, 150.f);
    ImGui::End();
    ImGui::BeginPopup("Nigga");
    ImGui::EndPopup();
    if (ImGui::BeginPopup("New Window")) {
        ImGui::Text("This is a new window!");
        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    
    m_window.draw(m_window_sprite);
    int bullet_amount;
    for (auto e : m_entities.getEntities())
    {
        e->cshape->sprite.setPosition(e->ctransform->pos.x, e->ctransform->pos.y);
        m_window.draw(e->cshape->sprite);
        if (e->tag() == "Bullet") {
            bullet_amount++;
        }
    }
    //std::cout << "amount of bullets: " << bullet_amount << "\n";
    // std::cout << m_player->ctransform->pos.x << " " << m_player->ctransform->pos.y << std::endl;
    // m_player->cshape->sprite.setPosition(m_player->ctransform->pos.x, m_player->ctransform->pos.y);
    // m_window.draw(m_player->cshape->sprite);
    
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

            if (e.key.code == sf::Keyboard::Space) {
                spwan = true;
            }

            break;

        case sf::Event::KeyReleased:
        {
            if (e.key.code == sf::Keyboard::A) { m_player->cinput->left = false; }
            else if (e.key.code == sf::Keyboard::D) { m_player->cinput->right = false; }
            else if (e.key.code == sf::Keyboard::W) { m_player->cinput->up = false; }
            else if (e.key.code == sf::Keyboard::S) { m_player->cinput->down = false; }
            else if (e.key.code == sf::Keyboard::Space) { spwan = false;; }
            break;
        }
        default:
            break;
        }
    }
    ImGui::SFML::Update(m_window,deltaclock.restart());
}

void Game::sCollisoin() {
    for (auto e : m_entities.getEntities("Player"))
	{
		//Checks to see if player collided with walls
		if (e->ctransform->pos.x + e->cshape->sprite.getLocalBounds().width > m_window.getSize().x)
		{
			e->ctransform->pos.x = m_window.getSize().x - e->cshape->sprite.getLocalBounds().width;
            // std::cout << e->ctransform->pos.x << std::endl;
            // std::cout << m_window . getSize().x << std::endl;
            // std::cout << m_window.getSize().x + e->ctransform->pos.x << std::endl;
		}
		else if (e->ctransform->pos.x < 0)
		{
			e->ctransform->pos.x = 0;
            // std::cout << e->ctransform->pos.x << std::endl<< std::endl;
		}

		if (e->ctransform->pos.y + e->cshape->sprite.getLocalBounds().width > m_window.getSize().y)
		{
			e->ctransform->pos.y = m_window.getSize().y - e->cshape->sprite.getLocalBounds().width;
            // std::cout << e->ctransform->pos.y << std::endl;
            // std::cout << m_window . getSize().y << std::endl;
            // std::cout << m_window.getSize().y + e->ctransform->pos.y << std::endl;
		}
		else if (e->ctransform->pos.y < 0)
		{
			e->ctransform->pos.y = 0;
            // std::cout << e->ctransform->pos.y << "\n";
		}
	}

    for(auto& e: m_entities.getEntities()) {
        if (e->tag() == "Bullet") {
            if(e->ctransform->pos.y < 0) {
                e->destroy();
            }
        }
    }
    for (auto& e : m_entities.getEntities("Enemy")) {
        for (auto& b : m_entities.getEntities("Bullet")) {
            std::cout << "Pre\n";
            std::cout << "enemy: " << e->ctransform->pos.y + e->cshape->sprite.getLocalBounds().height << "\n";
            std::cout << "BUllet: " << b->ctransform->pos.y << "\n";
            if (b->ctransform->pos.y == e->ctransform->pos.y + e->cshape->sprite.getLocalBounds().height)
            {
                std::cout << "After\n";
                std::cout << "enemy: " << e->ctransform->pos.y + e->cshape->sprite.getLocalBounds().height << "\n";
                std::cout << "BUllet: " << b->ctransform->pos.y << "\n";
                e->destroy();
                b->destroy();
            }
        }
        if (e->ctransform->pos.y > m_window.getSize().y) {
            e->destroy();
        }
    }
}

void Game::spwanBullet(Vec2& pos) {
    //std::cout << "spwanned bullet\n";
    Vec2 speed{ 10, 10 };
    auto bullet = m_entities.addEntity("Bullet");
    bullet->cshape = std::make_shared<CShape>("assets/pics/bullet.png");
    // bullet->clifespan = std::make_shared<CLifeSpan>();
    bullet->ctransform = std::make_shared<CTransform>(pos,speed);
    Vec2 size{ bullet->cshape->sprite.getLocalBounds().width, bullet->cshape->sprite.getLocalBounds().height};
    bullet->collision = std::make_shared<CCollision>(pos,size);
}

void Game::spwanEnemies() {
    Vec2 speed{ 10, 10 };
    auto enemy = m_entities.addEntity("Enemy");
    Vec2 pos{ 0, -100 };
    enemy->cshape = std::make_shared<CShape>("assets/pics/enemy.png");
    enemy->ctransform = std::make_shared<CTransform>(pos, speed);
    Vec2 size{ enemy->cshape->sprite.getLocalBounds().width, enemy->cshape->sprite.getLocalBounds().height };
    enemy->collision = std::make_shared<CCollision>(pos, size);
}