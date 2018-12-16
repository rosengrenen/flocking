#include "Flock.h"

void Flock::Update()
{
    for (auto& boid : m_boids)
    {
        boid.Align(m_boids);
        boid.Cohesion(m_boids);
        boid.Separation(m_boids);
        boid.Update();
    }
    for (auto& boid : m_boids)
    {
    }
}

void Flock::Render(sf::RenderWindow& window)
{
    sf::CircleShape circle;
    circle.setRadius(5.0f);
    circle.setFillColor(sf::Color(255, 255, 255));

    for (auto& boid : m_boids)
    {
        circle.setPosition(boid.GetPosition().x, boid.GetPosition().y);
        window.draw(circle);
    }
}

void Flock::AddBoid(const Boid& boid)
{
    m_boids.push_back(boid);
}
