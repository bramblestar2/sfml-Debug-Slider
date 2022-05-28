#include "Slider.h"

Slider::Slider(float _min, float _max)
{
    min = _min;
    max = _max;

    currentNumber = min;
    percentage = 0.f;
    transitionTime = 0.5f;

    holding = false;
    smoothTransition = false;

    slide.setSize(sf::Vector2f(10, 10));
    slide.setFillColor(sf::Color(75, 75, 75));
    slide.setOrigin(0, slide.getSize().y / 2);

    point.setRadius(5.f);
    point.setOrigin(point.getRadius(), point.getRadius());
    point.setFillColor(sf::Color(75, 75, 125));
}

Slider::Slider()
{
    min = 0;
    max = 1;

    currentNumber = min;
    percentage = 0.f;
    transitionTime = 0.5f;

    holding = false;
    smoothTransition = false;

    slide.setSize(sf::Vector2f(10, 10));
    slide.setFillColor(sf::Color(75, 75, 75));
    slide.setOrigin(0, slide.getSize().y / 2);

    point.setRadius(5.f);
    point.setOrigin(point.getRadius(), point.getRadius());
    point.setFillColor(sf::Color(75, 75, 125));
}

Slider::~Slider()
{

}

float Slider::getNumber()
{
    return currentNumber;
}

float Slider::getPercentage()
{
    return percentage;
}

sf::Vector2f Slider::getSize()
{
    return slide.getSize();
}

bool Slider::isEditing()
{
    return holding;
}

void Slider::setPercentage(float a)
{
    percentage = a;
}

void Slider::setSliderColor(sf::Color a, sf::Color b)
{
    slide.setFillColor(a);
    point.setFillColor(b);
}

void Slider::setMinMax(float a, float b)
{
    min = a;
    max = b;
}

void Slider::setSize(float width, float height)
{
    slide.setSize(sf::Vector2f(width, height));

    point.setRadius(slide.getSize().y);
    point.setOrigin(point.getRadius(), point.getRadius());
}

void Slider::setPosition(int x, int y)
{
    slide.setPosition(x, y);
}

void Slider::smoothSlider(bool a)
{
    smoothTransition = a;
}

void Slider::transitionSpeed(float a)
{
    transitionTime = a;
}

void Slider::update(sf::Vector2f mousePos)
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
    float xPos, yPos;
    xPos = ((percentage * 0.01f) / (temp / slide.getSize().x) * temp) + slide.getPosition().x;
    yPos = slide.getPosition().y;

    if (!smoothTransition)
        point.setPosition(xPos, yPos);
    else
        point.setPosition(lerp(point.getPosition().x, xPos, transitionTime),
            lerp(point.getPosition().y, yPos, transitionTime));
}

void Slider::draw(sf::RenderWindow& window)
{
    window.draw(slide);
    window.draw(point);
}

void Slider::corrections()
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

float Slider::lerp(float a, float b, float t)
{
    return a + t * (b - a);
}
