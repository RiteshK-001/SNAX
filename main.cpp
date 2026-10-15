#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>


using namespace std;

int main() {

    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    window.setFramerateLimit(20);

    sf::Color bgColor = sf::Color::Black;
    sf::RectangleShape snakeHead(sf::Vector2f(20.0f, 20.0f));
    snakeHead.setFillColor(sf::Color::Green);
    snakeHead.setPosition(400.0f, 300.0f);
    sf::Vector2f currentDirection(0.0f, 0.0f);

    sf::RectangleShape apple(sf::Vector2f(20.0f, 20.0f));
    apple.setFillColor(sf::Color::Red);
    float randomX = (rand() % 40) * 20.0f;
    float randomY = (rand() % 30) * 20.0f;
    apple.setPosition(sf::Vector2f(randomX, randomY));
    
    vector<sf::RectangleShape> snakeBody;

    snakeBody.push_back(snakeHead);

    bool gameOver = false;

    sf::Font font;
    if (!font.loadFromFile("DejaVuSans.ttf")) {
        return -1; 
    }

    int score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.0f, 10.0f);
    scoreText.setString("Score: 0");

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(180.0f, 200.0f);
    gameOverText.setString("    GAME OVER \n Press R to Restart");

    while (window.isOpen()) {
        
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
            window.close();
            }
        }

        if (gameOver) {
            window.draw(gameOverText);
            window.display();
        }

        if (event.key.code == sf::Keyboard::R && gameOver) {
            gameOver = false;
            currentDirection = sf::Vector2f(0.0f, 0.0f);
            snakeHead.setPosition(400.0f, 300.f);
            snakeBody = {snakeHead};
            float randomX = (rand() % 40) * 20.0f;
            float randomY = (rand() % 30) * 20.0f;
            apple.setPosition(sf::Vector2f(randomX, randomY));

            score = 0;
            scoreText.setString("Score: 0");
        }
            
        if (!gameOver) {
            

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Up) {
                    if (currentDirection != sf::Vector2f(0.0f,20.0f))
                        currentDirection = sf::Vector2f(0.0f,-20.0f);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    if (currentDirection != sf::Vector2f(0.0f, -20.0f))
                        currentDirection = sf::Vector2f(0.0f, 20.0f);
                }
                
                if(event.key.code == sf::Keyboard::Left) {
                    if (currentDirection != sf::Vector2f(20.0f, 0.0f))
                        currentDirection = sf::Vector2f(-20.0f,0.0f);
                }

                if (event.key.code == sf::Keyboard::Right) {
                    if (currentDirection != sf::Vector2f(-20.0f, 0.0f))
                        currentDirection = sf::Vector2f(20.0f,0.0f);
                }

                
            }


            
            sf::Vector2f head = snakeHead.getPosition();
            sf::Vector2f tail = snakeBody.back().getPosition();

            snakeHead.move(currentDirection);
            sf::Vector2f pos = snakeHead.getPosition();

            int ix = (int)pos.x;
            int iy = (int)pos.y;

            ix = (800 + (ix % 800)) % 800;
            iy = (600 + (iy % 600)) % 600;
            
            snakeHead.setPosition((float)ix, (float)iy);

            for (int i = 1; i < snakeBody.size(); i++) {
                sf::Vector2f temp = head;
                head = snakeBody[i].getPosition();
                snakeBody[i].setPosition(temp);
            
            }

            window.clear(sf::Color::Black);

            if (snakeHead.getPosition() == apple.getPosition()) {
                float randomX = (rand() % 40) * 20.0f;
                float randomY = (rand() % 30) * 20.0f;
        
                apple.setPosition(sf::Vector2f(randomX, randomY));

                sf::RectangleShape new_tail(sf::Vector2f(20.0f, 20.0f));
                new_tail.setFillColor(sf::Color::Green);
                
                new_tail.setPosition(tail);
                snakeBody.push_back(new_tail);

                score += 20;
                scoreText.setString("Score: " + to_string(score));
            }

            snakeBody[0] = snakeHead;

            window.draw(apple);
            for (auto body : snakeBody) {
                window.draw(body);
            }

            window.draw(scoreText);

            window.display();

            for (int i = 1; i < snakeBody.size(); i++) {
                if (snakeHead.getPosition() == snakeBody[i].getPosition()) {
                    gameOver = true;
                }
            }
        }

    }

    return 0;
}