#include "Boid.h"

Boid::Boid(const glm::vec2& position, const glm::vec2& velocity) : m_position(position),
                                                                   m_velocity(velocity),
                                                                   m_acceleration(0.0f),
                                                                   m_alignment(0.0f),
                                                                   m_cohesion(0.0f),
                                                                   m_separation(0.0f) { }

void Boid::Update()
{
    m_acceleration *= 0.0f;
    m_acceleration += m_alignment;
    m_acceleration += m_cohesion;
    m_acceleration += m_separation;
    m_velocity += m_acceleration;
    m_velocity *= maxSpeed / glm::length(m_velocity);
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

float Boid::GetRotation() const
{
    return glm::degrees(glm::atan(m_velocity.y, m_velocity.x));
}

void Boid::Align(const std::vector<Boid>& boids)
{
    glm::vec2 steering(0.0f);

    double perceptionRadius = 50.0;
    int total = 0;
    for (auto& boid : boids)
    {
        if (this != &boid && InField(*this, boid, perceptionRadius, fov))
        {
            total++;
            steering += boid.m_velocity;
        }
    }
    if (total > 0)
    {
        steering /= total;
        steering *= maxSpeed / glm::length(steering);
        steering -= m_velocity;
        if (glm::length(steering) > maxForce)
        {
            steering = glm::normalize(steering) * maxForce;
        }
    }
    m_alignment = steering;
}

bool Boid::InField(const Boid& current, const Boid& other, float radius, float fov) const
{
    glm::vec2 diff = current.m_position - other.m_position;
    float distance = glm::length(diff);
    glm::vec2 velDiff = glm::normalize(current.m_velocity) - glm::normalize(other.m_velocity);
    float angle = glm::degrees(glm::atan(velDiff.x, velDiff.y));
    return distance < radius && glm::abs(angle) < fov / 2.0f;
}

void Boid::Cohesion(const std::vector<Boid>& boids)
{
    glm::vec2 steering(0.0f);
    double perceptionRadius = 50.0;
    int total = 0;
    for (auto& boid : boids)
    {
        if (this != &boid && InField(*this, boid, perceptionRadius, fov))
        {
            total++;
            steering += boid.m_position;
        }
    }
    if (total > 0)
    {
        steering /= total;
        steering -= m_position;
        steering = glm::normalize(steering) * maxSpeed;
        steering -= m_velocity;
        if (glm::length(steering) > maxForce)
        {
            steering = glm::normalize(steering) * maxForce;
        }
    }
    m_cohesion = steering;
}

void Boid::Separation(const std::vector<Boid>& boids)
{
    glm::vec2 steering(0.0f);
    double perceptionRadius = 15.0;
    int total = 0;
    for (auto& boid : boids)
    {
        double d = glm::length(m_position - boid.m_position);
        if (this != &boid && InField(*this, boid, perceptionRadius, fov))
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
        steering *= maxSpeed / glm::length(steering);
        steering -= m_velocity;
        if (glm::length(steering) > maxForce)
        {
            steering = glm::normalize(steering) * 2.0f * maxForce;
        }
    }
    m_separation = steering;
}

glm::vec2 Boid::AverageVelocity(const std::vector<Boid>& boids, float perceptionRadius)
{
    glm::vec2 cumulativeVelocity(0.0f);
    int boidsInRangeCount = 0;
    for (auto& boid : boids)
    {
        float distance = glm::length(m_position - boid.m_position);
        if (this != &boid && distance < perceptionRadius)
        {
            boidsInRangeCount++;
            cumulativeVelocity += boid.m_velocity;
        }
    }
    if (boidsInRangeCount > 0)
    {
        cumulativeVelocity /= boidsInRangeCount;
    }
    return cumulativeVelocity;
}
