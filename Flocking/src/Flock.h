#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Boid.h"

class Flock
{
public:
    /* Public methods */
    void Update();
    void Render(sf::RenderWindow& window);

    void AddBoid(const Boid& boid);

private:
    /* Private members */
    std::vector<Boid> m_boids;
};