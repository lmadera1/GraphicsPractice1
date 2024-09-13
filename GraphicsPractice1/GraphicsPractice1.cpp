#include "GraphicsPractice1.h"

using namespace std;

string SHAPE_CONFIG_FILE = "ShapeConfig.txt";

//Main program loop
int main()
{

    //Open ShapeConfig.txt file
    string windowConfig;
    string fontConfig;
    vector<string> shapesConfig;
    if (!ReadShapeConfig(windowConfig, fontConfig, shapesConfig))
    {
        cout << "Can't open file ShapeConfig.txt" << endl;
    }

    //Get window dimensions from ShapeConfig.txt
    float width, height;
    if (!GetWindowWidthHeight(windowConfig, width, height))
    {
        cout << "Malformed ShapeConfig.txt file" << endl;
    }

    //Create Window
    sf::RenderWindow window(sf::VideoMode(width, height), "Graphics Practice 1");

    //Get font file from from ShapeConfig.txt
    sf::Font font;
    if (!GetFontFromConfig(fontConfig, font))
    {
        cout << "Malformed ShapeConfig.txt file" << endl;
    }

    //Get Shapes from ShapeConfig.txt
    vector<ShapeObject*> shapeObjects;
    if (!GetShapesFromConfig(shapesConfig, shapeObjects))
    {
        cout << "Malformed ShapeConfig.txt file" << endl;
    }

    //Print how many shapes loaded
    cout << shapeObjects.size() << " shapes loaded" << endl;

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
        for (auto shapeObject : shapeObjects)
        {
            window.draw(*shapeObject->shape);
        }

        UpdatePhysics(shapeObjects);

        window.display();
    }

    //Clean vector
    for (auto shape : shapeObjects)
    {
        delete shape;
    }

    return 0;
}

bool CreateShapeObject(string &line, ShapeObject* shapeObject)
{
    stringstream ss(line);

    string shapeType;
    ss >> shapeType;
    cout << shapeType << " ";

    string shapeName;
    ss >> shapeName;
    cout << shapeName << " ";

    float x, y;
    ss >> x >> y;
    cout << x << " " << y << " ";

    float vx, vy;
    ss >> vx >> vy;
    cout << vx << " " << vy << " ";
    shapeObject->velocity = sf::Vector2f(vx, vy);

    int r, g, b;
    ss >> r >> g >> b;
    cout << r << " " << g << " " << b << " ";
    sf::Shape* shape;

    //TODO: Below only creates circles
    if (shapeType == "Circle") 
    {
        float radius;
        ss >> radius;
        cout << radius << " ";
        sf::CircleShape circle(radius);
        shape = new sf::CircleShape(radius);
    }
    else if (shapeType == "Rectangle") 
    {
        float width, height;
        ss >> width >> height;
        cout << width << " " << height << " ";
        sf::Vector2f size(width, height);
        shape = new sf::RectangleShape(size);
    }
    else 
    {
        return false;
    }
    cout << endl;
    shape->setPosition(x, y);

    sf::Color color = sf::Color(r, g, b);
    shape->setFillColor(color);

    shapeObject->shape = shape;

    return true;
}

bool GetShapesFromConfig(vector<string> &shapesConfig, vector<ShapeObject*> &shapes) 
{
    for (string line : shapesConfig) {

        ShapeObject* shapeObject = new ShapeObject();
        if (!CreateShapeObject(line, shapeObject)) {
            return false;
        }
        shapes.push_back(shapeObject);
    }
    return true;
}

//TODO: Finish
bool GetFontFromConfig(string &line, sf::Font &font) 
{

    stringstream ss(line);

    string lineHeader;
    ss >> lineHeader;

    if (lineHeader != "Font") return false;
    //TODO
    return true;
}

bool GetWindowWidthHeight(const string &line, float &width, float &height)
{
    stringstream ss(line);

    string lineHeader;
    ss >> lineHeader;

    if (lineHeader != "Window") return false;

    ss >> width >> height;

    return true;
}

void UpdatePhysics(vector<ShapeObject*> &shapeObjects) 
{
    for (auto shapeObject : shapeObjects) 
    {
        shapeObject->shape->move(shapeObject->velocity);
    }
}

bool ReadShapeConfig(string& windowConfig, string& fontConfig, vector<string>& shapesConfig) 
{
    ifstream file(SHAPE_CONFIG_FILE);

    if (!file.is_open())
    {
        return false;
    }

    //get windowConfig line
    if (!getline(file, windowConfig)) 
    {
        return false;
    }

    if (!getline(file, fontConfig)) 
    {
        return false;
    }

    string shapeConfig;
    while (getline(file, shapeConfig))
    {
        shapesConfig.push_back(shapeConfig);
    }

    file.close();

    return true;
}


