#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

//ShapeObject class
class ShapeObject
{
public:
    sf::Shape* shape = nullptr;
    sf::Vector2f velocity;
};

bool CreateShapeObject(string& line, ShapeObject* shapeObject);

bool ReadShapeConfig(string& windowConfig, string& fontConfig, vector<string>& shapesConfig);

void UpdatePhysics(vector<ShapeObject*>& shapeObjects, float width, float height);

bool GetWindowWidthHeight(const string& line, float& width, float& height);

bool GetFontFromConfig(string& line, sf::Font& font);

bool GetShapesFromConfig(vector<string>& shapesConfig, vector<ShapeObject*>& shapes);
