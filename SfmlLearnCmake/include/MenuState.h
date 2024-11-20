#pragma once

#include<SFML/Graphics.hpp>
#include "ResourceManager.h"

class MenuState {
public:
    MenuState(sf::RenderWindow& window);

    // �������� ������� ����
    void draw();  // ��������� ����
    void moveUp();  // ����������� ����� �� ����
    void moveDown();  // ����������� ���� �� ����
    int getSelectedItem() const;  // ��������� ���������� �������� ����

private:
    sf::Font mFont;  // ����� ��� ������ ����
    std::vector<sf::Text> mMenuItems;  // �������� ����
    int mSelectedItemIndex;  // ������ ���������� ��������
    sf::RenderWindow& mWindow;  // ������ �� ���� ��� ���������
};
