#include "Flock.h"

void Flock::Update()
{
    for (auto& boid : m_boids)
    {
        boid.Align(m_boids);
        boid.Cohesion(m_boids);
        boid.Separation(m_boids);
    }
    for (auto& boid : m_boids)
    {
        boid.Update();
    }
}

void Flock::Render(sf::RenderWindow& window)
{
    for (auto& boid : m_boids)
    {
        sf::CircleShape circle(3.0f, 3);
        circle.setOrigin(3.0f, 3.0f);
        circle.setRotation(boid.GetRotation() + 90.0f);
        circle.setPosition(boid.GetPosition().x, boid.GetPosition().y);
        circle.scale(1.0f, 2.0f);
        circle.setFillColor(sf::Color(0, 255, 255));
        window.draw(circle);
        //sf::Vertex velocityLine[] = {
        //    sf::Vertex(sf::Vector2f(boid.GetPosition().x, boid.GetPosition().y)),
        //    sf::Vertex(sf::Vector2f(boid.GetPosition().x + boid.GetVelocity().x * 10,
        //                            boid.GetPosition().y + boid.GetVelocity().y * 10)),
        //};
        //velocityLine[0].color = sf::Color::Red;
        //velocityLine[1].color = sf::Color::Red;
        //window.draw(velocityLine, 2, sf::Lines);

        //sf::Vertex accelerationLine[] = {
        //    sf::Vertex(sf::Vector2f(boid.GetPosition().x, boid.GetPosition().y)),
        //    sf::Vertex(sf::Vector2f(boid.GetPosition().x + boid.GetAcceleration().x * 100,
        //                            boid.GetPosition().y + boid.GetAcceleration().y * 100)),
        //};
        //accelerationLine[0].color = sf::Color::Green;
        //accelerationLine[1].color = sf::Color::Green;
        //window.draw(accelerationLine, 2, sf::Lines);
    }
}

void Flock::AddBoid(const Boid& boid)
{
    m_boids.push_back(boid);
}
