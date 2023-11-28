#include <SFML/Graphics.hpp>
#include <string.h>
#include <fstream>
#include <iostream>
#include <stdint.h>

int main()
{
    std::vector<int> xCircleAxisSpeeds;
    std::vector<int> yCircleAxisSpeeds;
    std::vector<int> xRectangleAxisSpeeds;
    std::vector<int> yRectangleAxisSpeeds;
    std::vector<sf::Text> circleShapeTexts;
    std::vector<sf::Text> rectangleShapeTexts;
    std::vector<sf::CircleShape> shapeCircles;
    std::vector<sf::RectangleShape> shapeRectangles;
    std::string windowName, fontName, fontFile;
    int winWidth, winHeight, fontSize, fontR, fontG, fontB;
    std::ifstream fin("config2.txt");
    fin >> windowName >> winWidth >> winHeight;
    fin >> fontName >> fontFile >> fontSize >> fontR >> fontG >> fontB;
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), windowName);
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile(fontFile);
    if (!font.loadFromFile(fontFile))
    {
        std::cout << "Error while loading config!";
        return -1;
    }

    while (!fin.eof())
    {
        std::string shapeCheck;
        fin >> shapeCheck;
        if (shapeCheck == "Circle")
        {
            std::string tempName;
            int posX, posY, r, g, b, radius;
            float speedX, speedY;
            fin >> tempName >> posX >> posY >> speedX >> speedY >> r
                >> g >> b >> radius;
            sf::CircleShape tempCircle(radius);
            tempCircle.setPosition(posX, posY);
            tempCircle.setFillColor(sf::Color(r, g, b));
            shapeCircles.push_back(tempCircle);
            sf::Text tempText(tempName,font,fontSize);
            tempText.setFillColor(sf::Color(fontR, fontG, fontB));
            circleShapeTexts.push_back(tempText);
            xCircleAxisSpeeds.push_back(speedX);
            yCircleAxisSpeeds.push_back(speedY);
        }
        else
            {
            std::string tempName;
            int posX, posY, r, g, b, width, height;
            float speedX, speedY;
            fin >> tempName >> posX >> posY >> speedX >> speedY >> r
                >> g >> b >> width >> height;
            sf::RectangleShape tempRectangle;
            tempRectangle.setPosition(posX, posY);
            tempRectangle.setSize(sf::Vector2f(width, height));
            tempRectangle.setFillColor(sf::Color(r, g, b));
            shapeRectangles.push_back(tempRectangle);
            sf::Text tempText(tempName, font, fontSize);
            tempText.setFillColor(sf::Color(fontR, fontG, fontB));
            rectangleShapeTexts.push_back(tempText);
            xRectangleAxisSpeeds.push_back(speedX);
            yRectangleAxisSpeeds.push_back(speedY);
            }

    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        for (int i = 0; i < shapeCircles.size(); ++i)
        {
            if (shapeCircles[i].getPosition().x <= 0 || shapeCircles[i].getPosition().x + shapeCircles[i].getRadius() * 2 >= winWidth)
            {
                xCircleAxisSpeeds[i] *= -1;
            }
            if (shapeCircles[i].getPosition().y <= 0 || shapeCircles[i].getPosition().y + shapeCircles[i].getRadius() * 2 >= winHeight)
            {
                yCircleAxisSpeeds[i] *= -1;
            }
            shapeCircles[i].setPosition(shapeCircles[i].getPosition().x + xCircleAxisSpeeds[i], shapeCircles[i].getPosition().y + yCircleAxisSpeeds[i]);
            circleShapeTexts[i].setPosition(shapeCircles[i].getPosition().x + shapeCircles[i].getRadius() - circleShapeTexts[i].getLocalBounds().width / 2,
                shapeCircles[i].getPosition().y + shapeCircles[i].getRadius() - circleShapeTexts[i].getLocalBounds().height / 2);
            window.draw(shapeCircles[i]);
            window.draw(circleShapeTexts[i]);
        }

        for (int i = 0; i < shapeRectangles.size(); ++i)
        {
            if (shapeRectangles[i].getPosition().x <= 0 || shapeRectangles[i].getPosition().x  + shapeRectangles[i].getLocalBounds().width >= winWidth)
            {
                xRectangleAxisSpeeds[i] *= -1;
            }
            if (shapeRectangles[i].getPosition().y <= 0 || shapeRectangles[i].getPosition().y + shapeRectangles[i].getLocalBounds().height >= winHeight)
            {
                yRectangleAxisSpeeds[i] *= -1;
            }
            shapeRectangles[i].setPosition(shapeRectangles[i].getPosition().x + xRectangleAxisSpeeds[i], shapeRectangles[i].getPosition().y + yRectangleAxisSpeeds[i]);
            rectangleShapeTexts[i].setPosition(shapeRectangles[i].getPosition().x + shapeRectangles[i].getLocalBounds().width / 2 - rectangleShapeTexts[i].getLocalBounds().width / 2,
                shapeRectangles[i].getPosition().y  + shapeRectangles[i].getLocalBounds().height / 2 - rectangleShapeTexts[i].getLocalBounds().height / 2);
            window.draw(shapeRectangles[i]);
            window.draw(rectangleShapeTexts[i]);
        }
        window.display();
    }
    
    return 0;
}