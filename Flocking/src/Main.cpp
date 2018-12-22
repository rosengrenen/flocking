#include <SFML/Graphics.hpp>

#include <chrono>
#include <functional>
#include <random>

#include <glm/glm.hpp>

#include "Flock.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!", sf::Style::Default, settings);

    std::mt19937::result_type seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto rand = std::bind(std::uniform_real_distribution<double>(0.0, 1.0), std::mt19937_64(seed));

    Flock flock;

    for (int i = 0; i < 100; ++i)
    {
        glm::vec2 position(rand() * WINDOW_WIDTH, rand() * WINDOW_HEIGHT);
        double angle = rand() * 2.0 * 3.141592;
        glm::vec2 velocity(glm::cos(angle), glm::sin(angle));
        velocity *= rand() + 0.5;
        Boid boid(position, velocity);
        flock.AddBoid(boid);
    }

    //window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        flock.Update();

        window.clear();

        flock.Render(window);

        window.display();
    }

    return 0;
}
