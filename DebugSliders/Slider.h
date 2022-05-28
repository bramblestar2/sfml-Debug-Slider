#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using std::cout;
using std::string;


class Slider {

public:
    Slider(float, float);
    Slider();
    ~Slider();

    float getNumber();
    float getPercentage();
    sf::Vector2f getSize();
    bool isEditing();

    void setPercentage(float);
    void setSliderColor(sf::Color slider, sf::Color point);
    void setMinMax(float _min, float _max);
    void setSize(float, float);
    void setPosition(int, int);

    void smoothSlider(bool);
    //Relates with smoothSlider()
    void transitionSpeed(float);

    void update(sf::Vector2f);
    void draw(sf::RenderWindow&);
private:
    sf::RectangleShape slide;
    sf::CircleShape point;

    void corrections();
    float lerp(float, float, float);

    bool holding;
    bool smoothTransition;
    float transitionTime;

    float min, max;
    float currentNumber;
    float percentage;
};