#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

//Main program loop
int main()
{
    //Open ShapeConfig.txt file
    std::ifstream file("ShapeConfig.txt");

    if (!file.is_open()) 
    {
        std::cout << "Can't open file ShapeConfig.txt" << std::endl;
        return -1;
    }

    //Get window dimensions from ShapeConfig.txt
    std::string line;
    if (!std::getline(file, line)) 
    {
        std::cout << "Malformed file" << std::endl;
    }
    std::stringstream ss(line);

    std::string lineHeader;
    float width, height;

    ss >> lineHeader >> width >> height;

    if (lineHeader != "Window") {
        std::cout << "Malformed file" << std::endl;
    }

	sf::RenderWindow window(sf::VideoMode(width, height), "Graphics Practice 1");


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    //Close ShapeConfig.txt file
    file.close();

    //Main Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

	return 0;
}