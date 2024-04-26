#include "Common.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Game{
public:
    Game();
    void sRender();
    void sMovement();
    void sInput();
    void sUpdate();
    void Run();
    void sInit();

private:
    bool m_running;
    sf::RenderWindow m_window;
    sf::Texture m_window_texture;
    sf::Sprite m_window_sprite;
};