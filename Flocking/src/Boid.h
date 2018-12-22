#pragma once

#include <vector>

#include <glm/glm.hpp>

class Boid
{
public:
    /* Public methods */
    Boid(const glm::vec2& position, const glm::vec2& velocity);

    void Update();

    const glm::vec2& GetPosition() const
    {
        return m_position;
    }

    const glm::vec2& GetVelocity() const
    {
        return m_velocity;
    }

    const glm::vec2& GetAcceleration() const
    {
        return m_acceleration;
    }

    float GetRotation() const;

    void Align(const std::vector<Boid>& boids);
    void Cohesion(const std::vector<Boid>& boids);
    void Separation(const std::vector<Boid>& boids);

    bool InField(const Boid& current, const Boid& other, float radius, float fov) const;

    glm::vec2 AverageVelocity(const std::vector<Boid>& boids, float perceptionRadius);

private:
    /* Private members */
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    glm::vec2 m_acceleration;

    glm::vec2 m_alignment;
    glm::vec2 m_cohesion;
    glm::vec2 m_separation;

    float maxSpeed = 4.0f;
    float maxForce = 0.4f;
    float fov = 360.0f;
};
