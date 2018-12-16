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

    void Align(const std::vector<Boid>& boids);
    void Cohesion(const std::vector<Boid>& boids);
    void Separation(const std::vector<Boid>& boids);

private:
    /* Private members */
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    glm::vec2 m_acceleration;

    glm::vec2 m_align;
    glm::vec2 m_cohesion;
    glm::vec2 m_separation;

    static constexpr double MAX_SPEED = 1.0f;
};