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
	DebugSliders();
	~DebugSliders();

	int getSliderCount();
	int getHeldSlider();

	void addSlider(float min, float max);
	void setSlidersSize(float, float);
	void setSlidersColor(sf::Color slider, sf::Color point);
	void setPosition(int, int);

	// use getSliderCount() to get the amount of sliders there are
	Slider editSlider(int it);
	void update(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
private:
	std::vector<Slider> sliders;

	int currentSliderHeld;
	int distanceSliders;
};

