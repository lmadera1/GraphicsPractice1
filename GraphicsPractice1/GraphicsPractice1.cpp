#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

//ShapeObject class
class ShapeObject 
{
public:
    sf::Shape* shape = nullptr;
    float vx;
    float vy;
};

bool CreateShapeObject(std::string& line, ShapeObject* shapeObject)
{
    std::stringstream ss(line);

    std::string shapeType;
    ss >> shapeType;
    std::cout << shapeType << " ";

    std::string shapeName;
    ss >> shapeName;
    std::cout << shapeName << " ";

    float x, y;
    ss >> x >> y;
    std::cout << x << " " << y << " ";

    float vx, vy;
    ss >> vx >> vy;
    std::cout << vx << " " << vy << " ";
    shapeObject->vx = vx;
    shapeObject->vy = vy;

    int r, g, b;
    ss >> r >> g >> b;
    std::cout << r << " " << g << " " << b << " ";
    sf::Shape* shape;

    //TODO: Below only creates circles
    if (shapeType == "Circle") 
    {
        float radius;
        ss >> radius;
        std::cout << radius << " ";
        sf::CircleShape circle(radius);
        shape = new sf::CircleShape(radius);
    }
    else if (shapeType == "Rectangle") 
    {
        float width, height;
        ss >> width >> height;
        std::cout << width << " " << height << " ";
        sf::Vector2f size(width, height);
        shape = new sf::RectangleShape(size);
    }
    else 
    {
        return false;
    }
    std::cout << std::endl;
    shape->setPosition(x, y);

    sf::Color color = sf::Color(r, g, b);
    shape->setFillColor(color);

    shapeObject->shape = shape;

    return true;
}

bool GetShapesFromConfig(std::ifstream* file, std::vector<ShapeObject*> &shapes) 
{
    if (!file->is_open()) return false;

    std::string line;
    while (std::getline(*file, line)) 
    {
        ShapeObject* shapeObject = new ShapeObject();
        if (!CreateShapeObject(line, shapeObject)) {
            return false;
        }
        shapes.push_back(shapeObject);
    }
    return true;
}

//TODO: Finish
bool GetFontFromConfig(std::ifstream* file, sf::Font &font) 
{
    if (!file->is_open()) return false;

    std::string line;
    if (!std::getline(*file, line))
    {
        return false;
    }

    std::stringstream ss(line);

    std::string lineHeader;
    ss >> lineHeader;

    if (lineHeader != "Font") return false;
    //TODO
    return true;
}


bool GetWindowWidthHeight(std::ifstream* file, float &width, float &height) 
{
    if (!file->is_open()) return false;

    std::string line;
    if (!std::getline(*file, line)) 
    {
        return false;
    }

    std::stringstream ss(line);

    std::string lineHeader;
    ss >> lineHeader;

    if (lineHeader != "Window") return false;

    ss >> width >> height;

    return true;
}

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
    float width, height;

    if (!GetWindowWidthHeight(&file, width, height)) 
    {
        std::cout << "Malformed ShapeConfig.txt file" << std::endl;
    }

    //Create Window
	sf::RenderWindow window(sf::VideoMode(width, height), "Graphics Practice 1");

    //Get font file from from ShapeConfig.txt
    sf::Font font;
    if (!GetFontFromConfig(&file, font)) 
    {
        std::cout << "Malformed ShapeConfig.txt file" << std::endl;
    }

    //Get Shapes from ShapeConfig.txt
    std::vector<ShapeObject*> shapes;
    if (!GetShapesFromConfig(&file, shapes)) 
    {
        std::cout << "Malformed ShapeConfig.txt file" << std::endl;
    }
   
    //Print how many shapes loaded
    std::cout << shapes.size() << " shapes loaded" << std::endl;

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

        //Draw all shapes
        for (auto shapeObject : shapes) 
        {
            window.draw(*shapeObject->shape);
        }

        window.display();
    }

    //Clean vector
    for (auto shape : shapes) 
    {
        delete shape;
    }

	return 0;
}