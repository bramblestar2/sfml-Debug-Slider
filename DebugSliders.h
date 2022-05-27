#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Slider.h"

using std::cout;
using std::string;


class DebugSliders
{
public:
	DebugSliders()
	{
		distanceSliders = 15;
		currentSliderHeld = -1;
	}
	~DebugSliders()
	{
	}

	int getSliderCount()
	{
		return sliders.size();
	}
	int getHeldSlider()
	{
		return currentSliderHeld;
	}

	void addSlider(float min, float max)
	{
		sliders.push_back(Slider());
		sliders.at(sliders.size() - 1).setPosition(0, sliders.size() * distanceSliders);
		sliders.at(sliders.size() - 1).setMinMax(min, max);
	}
	void setSlidersSize(float width, float height)
	{
		for (int i = 0; i < sliders.size(); i++)
		{
			sliders.at(i).setSize(width, height);
		}

		distanceSliders = height + 10;
	}
	void setSlidersColor(sf::Color slider, sf::Color point)
	{
		for (int i = 0; i < sliders.size(); i++)
		{
			sliders.at(i).setSliderColor(slider, point);
		}
	}
	void setPosition(int x, int y)
	{
		for (int i = 0; i < sliders.size(); i++)
		{
			sliders.at(i).setPosition(x, y + (distanceSliders * i));
		}
	}

	// use getSliderCount() to get the amount of sliders there are
	Slider editSlider(int it)
	{
		return sliders.at(it);
	}
	void update(sf::RenderWindow& window)
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
	void draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < sliders.size(); i++)
			sliders.at(i).draw(window);
	}
private:
	std::vector<Slider> sliders;

	int currentSliderHeld;
	int distanceSliders;
};

