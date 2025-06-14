#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;
class Zombie
{
private:
    const float BLOATER_SPEED = 20;
    const float CHASER_SPEED = 40;
    const float CRAWLER_SPEED = 10;
    const float BLOATER_HEALTH = 5;
    const float CHASER_HEALTH = 1;
    const float CRAWLER_HEALTH = 3;
    Vector2f m_Position;
    Sprite m_Sprite;
    Texture m_Texture;
    float m_Speed;
    float m_Health;
    bool m_Alive = false;

public:
    FloatRect getPosition();
    Sprite getSprite();
    bool isAlive();
    void spawn(float startX, float startY, int type, int seed);
    void update(float elapsedTime, Vector2f playerLocation);
    bool hit();
};
FloatRect Zombie::getPosition()
{
    return m_Sprite.getGlobalBounds();
}
Sprite Zombie::getSprite()
{
    return m_Sprite;
}
bool Zombie::isAlive()
{
    return m_Alive;
}
void Zombie::spawn(float startX, float startY, int type, int seed)
{
    m_Position.x = startX;
    m_Position.y = startY;
    // m_Sprite.setPosition(m_Position);
    m_Sprite.setOrigin(25, 25);
    switch (type)
    {
    case 0:
        m_Texture.loadFromFile("bloater.png");
        m_Sprite.setTexture(m_Texture);
        m_Speed = BLOATER_SPEED;
        m_Health = BLOATER_HEALTH;
        m_Alive = true;
        break;
    case 1:
        m_Texture.loadFromFile("chaser.png");
        m_Sprite.setTexture(m_Texture);
        m_Speed = CHASER_SPEED;
        m_Health = CHASER_HEALTH;
        m_Alive = true;
        break;
    case 2:
        m_Texture.loadFromFile("crawler.png");
        m_Sprite.setTexture(m_Texture);
        m_Speed = CRAWLER_SPEED;
        m_Health = CRAWLER_HEALTH;
        m_Alive = true;
        break;
    }
    srand((int)time(0) * seed);
    float modifier = (rand() % (101 - 70) + 70);
    modifier = modifier / 100;
    m_Speed = m_Speed * modifier;
}
void Zombie::update(float elapsedTime, Vector2f playerLocation)
{
    if (m_Alive)
    {
        float playerX = playerLocation.x;
        float playerY = playerLocation.y;
        if (m_Position.x < playerX)
        {
            m_Position.x = m_Position.x + m_Speed * elapsedTime;
        }
        if (m_Position.x > playerX)
        {
            m_Position.x = m_Position.x - m_Speed * elapsedTime;
        }
        if (m_Position.y < playerY)
        {
            m_Position.y = m_Position.y + m_Speed * elapsedTime;
        }
        if (m_Position.y > playerY)
        {
            m_Position.y = m_Position.y - m_Speed * elapsedTime;
        }
        m_Sprite.setPosition(m_Position);
        
        float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / 3.141;
        m_Sprite.setRotation(angle);
    }
}
bool Zombie::hit()
{
    m_Health--;
    if (m_Health < 0)
    {
        m_Alive = false;
        m_Texture.loadFromFile("blood.png");
        m_Sprite.setTexture(m_Texture);
        return true;
    }
    return false;
}