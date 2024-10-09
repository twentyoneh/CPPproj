#pragma once
#include <SFML/Graphics.hpp>

class Enemy : public sf::Drawable {
public:
    Enemy();
    virtual ~Enemy();

    // ���������� ������ �����, ����� �������������� � ����������� �������
    virtual void update(sf::Time deltaTime);

    // ��������� ������� �����
    void setPosition(const sf::Vector2f& position);

    // ��������� ����� �����
    void takeDamage(int damage);

    // ��������, ����� �� ����
    bool isDead() const;

protected:
    int mHealth;  // �������� �����
    sf::Sprite mSprite;  // ������ �����

private:
    // ��������� �����
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
