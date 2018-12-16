#include "Boid.h"

Boid::Boid(const glm::vec2& position, const glm::vec2& velocity) : m_position(position),
                                                                   m_velocity(velocity) { }

void Boid::Update()
{
    m_acceleration *= 0.0f;
    m_acceleration += m_align;
    m_acceleration += m_cohesion;
    m_acceleration += m_separation;
    m_velocity += m_acceleration;
    m_velocity *= MAX_SPEED / glm::length(m_velocity);
    m_position += m_velocity;

    if (m_position.x < 0)
    {
        m_position.x = 800.0;
    }
    else if (m_position.x > 800.0)
    {
        m_position.x = 0;
    }
    if (m_position.y < 0)
    {
        m_position.y = 600.0;
    }
    else if (m_position.y > 600.0)
    {
        m_position.y = 0;
    }
}

void Boid::Align(const std::vector<Boid>& boids)
{
    glm::vec2 steering(0.0f);

    double maxForce = 0.08;
    double perceptionRadius = 25.0;
    int total = 0;
    for (auto& boid : boids)
    {
        if (this != &boid && glm::length(m_position - boid.m_position) < perceptionRadius)
        {
            total++;
            steering += boid.m_velocity;
        }
    }
    if (total > 0)
    {
        steering /= total;
        steering *= MAX_SPEED / glm::length(steering);
        steering -= m_velocity;
        if (glm::length(steering) > maxForce)
        {
            steering *= maxForce / glm::length(steering);
        }
    }
    m_align = steering;
}

void Boid::Cohesion(const std::vector<Boid>& boids)
{
    glm::vec2 steering(0.0f);

    double maxForce = 0.08;
    double perceptionRadius = 50.0;
    int total = 0;
    for (auto& boid : boids)
    {
        if (this != &boid && glm::length(m_position - boid.m_position) < perceptionRadius)
        {
            total++;
            steering += boid.m_position;
        }
    }
    if (total > 0)
    {
        steering /= total;
        steering -= m_position;
        double value = glm::length(steering);
        steering *= MAX_SPEED / glm::length(steering);
        steering -= m_velocity;
        if (glm::length(steering) > maxForce)
        {
            steering *= maxForce / glm::length(steering);
        }
    }
    m_cohesion = steering;
}

void Boid::Separation(const std::vector<Boid>& boids)
{

    glm::vec2 steering(0.0f);

    double maxForce = 0.5;
    double perceptionRadius = 24.0;
    int total = 0;
    for (auto& boid : boids)
    {
        double d = glm::length(m_position - boid.m_position);
        if (this != &boid && d < perceptionRadius)
        {
            total++;
            glm::vec2 diff = m_position - boid.m_position;
            diff /= d * d;
            steering += diff;
        }
    }
    if (total > 0)
    {
        steering /= total;
        steering *= MAX_SPEED / glm::length(steering);
        steering -= m_velocity;
        if (glm::length(steering) > maxForce)
        {
            steering *= maxForce / glm::length(steering);
        }
    }
    m_separation = steering;
}
