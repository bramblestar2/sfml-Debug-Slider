#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using std::cout;
using std::string;


class Slider {

public:
    Slider(float _min, float _max)
    {
        min = _min;
        max = _max;

        currentNumber = min;
        percentage = 0.f;

        holding = false;

        slide.setSize(sf::Vector2f(10, 10));
        slide.setFillColor(sf::Color(75, 75, 75));
        slide.setOrigin(0, slide.getSize().y / 2);

        point.setRadius(5.f);
        point.setOrigin(point.getRadius(), point.getRadius());
        point.setFillColor(sf::Color(75, 75, 125));
    }
    Slider()
    {
        min = 0;
        max = 1;

        currentNumber = min;
        percentage = 0.f;

        holding = false;

        slide.setSize(sf::Vector2f(10, 10));
        slide.setFillColor(sf::Color(75, 75, 75));
        slide.setOrigin(0, slide.getSize().y / 2);

        point.setRadius(5.f);
        point.setOrigin(point.getRadius(), point.getRadius());
        point.setFillColor(sf::Color(75, 75, 125));
    }
    ~Slider()
    {

    }

    float getNumber()
    {
        return currentNumber;
    }
    float getPercentage()
    {
        return percentage;
    }
    sf::Vector2f getSize()
    {
        return slide.getSize();
    }
    bool isEditing()
    {
        return holding;
    }

    void setNumber(float num)
    {
        currentNumber = num;
        corrections();
    }
    void setSliderColor(sf::Color sliderColor, sf::Color pointColor)
    {
        slide.setFillColor(sliderColor);
        point.setFillColor(pointColor);
    }
    void setMinMax(float _min, float _max)
    {
        min = _min;
        max = _max;
    }
    void setSize(float width, float height)
    {
        slide.setSize(sf::Vector2f(width, height));

        point.setRadius(slide.getSize().y);
        point.setOrigin(point.getRadius(), point.getRadius());
    }
    void setPosition(int x, int y)
    {
        slide.setPosition(x, y);
    }

    void update(sf::Vector2f mousePos)
    {
        float temp = max - min;

        if (slide.getGlobalBounds().contains(mousePos) && !holding)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                holding = true;
            }
        }
        else if (holding && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            float positionOnSlider = mousePos.x - slide.getPosition().x;

            percentage = (positionOnSlider * (temp / slide.getGlobalBounds().width) / temp) * 100;
        }
        else if (holding)
            holding = false;
        currentNumber = min + (temp * (percentage * 0.01f));

        corrections();

        point.setPosition(((percentage * 0.01f) / (temp / slide.getSize().x) * temp) + slide.getPosition().x,
            slide.getPosition().y);
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(slide);
        window.draw(point);
    }
private:
    sf::RectangleShape slide;
    sf::CircleShape point;

    void corrections()
    {
        if (min > max)
            min = max - 1;
        if (min == max)
            max++;


        if (currentNumber > max)
            currentNumber = max;
        if (currentNumber < min)
            currentNumber = min;

        if (percentage < 0)
            percentage = 0.f;
        if (percentage > 100)
            percentage = 100;
    }

    bool holding;

    float min, max;
    float currentNumber;
    float percentage;
};