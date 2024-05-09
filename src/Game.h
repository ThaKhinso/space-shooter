#include "Common.h"
#include "Entity.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "EntityManager.h"
#include <memory>
class Game{
public:
    Game();
    void sRender();
    void sMovement();
    void sInput();
    void sUpdate();
    void Run();
    void sInit();
    void sCollisoin();
    void spwanPlayer();
    void spwanBullet();
    void spwanEnemies();

private:
    bool m_running;
    char buf[250] = {0};
    float f;

    EntityManager m_entities;
    sf::Clock deltaclock;
    sf::RenderWindow m_window;
    sf::Texture m_window_texture;
    sf::Sprite m_window_sprite;
    std::shared_ptr<Entity> m_player;
    double speed;
    float velx, vely;
};