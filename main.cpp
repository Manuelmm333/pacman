#include <SFML/Graphics.hpp>

int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}, 32), "CMake SFML Project");  
  while (window.isOpen()) 
  { 
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
        }
    }
    window.clear(sf::Color::Black);
    window.display();
  }
  
  return 0;
}