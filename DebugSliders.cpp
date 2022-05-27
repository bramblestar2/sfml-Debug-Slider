#include "DebugSliders.h"

DebugSliders::DebugSliders()
{
	distanceSliders = 15;
	currentSliderHeld = -1;
}

DebugSliders::~DebugSliders()
{
}

int DebugSliders::getSliderCount()
{
	return sliders.size();
}

int DebugSliders::getHeldSlider()
{
	return currentSliderHeld;
}

void DebugSliders::addSlider(float min, float max)
{
	sliders.push_back(Slider());
	sliders.at(sliders.size() - 1).setPosition(0, sliders.size()*distanceSliders);
	sliders.at(sliders.size() - 1).setMinMax(min, max);
}

void DebugSliders::setSlidersSize(float width, float height)
{
	for (int i = 0; i < sliders.size(); i++)
	{
		sliders.at(i).setSize(width, height);
	}

	distanceSliders = height+10;
}

void DebugSliders::setSlidersColor(sf::Color slider, sf::Color point)
{
	for (int i = 0; i < sliders.size(); i++)
	{
		sliders.at(i).setSliderColor(slider, point);
	}
}

void DebugSliders::setPosition(int x, int y)
{
	for (int i = 0; i < sliders.size(); i++)
	{
		sliders.at(i).setPosition(x, y+(distanceSliders*i));
	}
}

Slider DebugSliders::editSlider(int it)
{
	return sliders.at(it);
}

void DebugSliders::update(sf::RenderWindow& window)
{
	for (int i = 0; i < sliders.size(); i++)
	{
		if (currentSliderHeld == -1)
		{
			sliders.at(i).update(sf::Vector2f(sf::Mouse::getPosition(window)));
			if (sliders.at(i).isEditing())
				currentSliderHeld = i;
		}
		else if (currentSliderHeld == i)
		{
			if (sliders.at(i).isEditing())
				sliders.at(i).update(sf::Vector2f(sf::Mouse::getPosition(window)));
			else
				currentSliderHeld = -1;
		}
	}
}

void DebugSliders::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < sliders.size(); i++)
		sliders.at(i).draw(window);
}
