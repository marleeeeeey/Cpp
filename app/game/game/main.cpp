
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>
#include <optional>

void changeBallColor(sf::CircleShape & ball)
{
    const sf::Color newColor(std::rand() % 0xff, std::rand() % 0xff, std::rand() % 0xff);
    ball.setFillColor(newColor);
}

class Paddle
{
    sf::RectangleShape m_shape;
    sf::Vector2f m_paddleSize{ 25, 100 };

public:
    Paddle()
    {
        m_shape.setSize(m_paddleSize - sf::Vector2f(3, 3));
        m_shape.setOutlineThickness(3);
        m_shape.setOutlineColor(sf::Color::Black);
        m_shape.setFillColor(sf::Color(100, 100, 200));
        m_shape.setOrigin(m_paddleSize / 2.f);        
    }

    void setFillColor(const sf::Color& color) { m_shape.setFillColor(color); }
    void setPosition(float x, float y) { m_shape.setPosition(x, y); }
    const sf::Vector2f& getPosition() const { return m_shape.getPosition(); }
    void draw(sf::RenderWindow& window)
    {
        correctPosition(window);
        window.draw(m_shape);
    }
    void move(float offsetX, float offsetY) { m_shape.move(offsetX, offsetY); }
    const sf::Vector2f& getSize() const { return m_shape.getSize(); }

private:
    void correctPosition(sf::RenderWindow& window)
    {
        std::pair<int, int> verticalBounds{ 0 + m_paddleSize.x / 2, window.getSize().x - m_paddleSize.x / 2 };
        std::pair<int, int> horizontalBounds{ 0 + m_paddleSize.y / 2, window.getSize().y - m_paddleSize.y / 2 };

        std::optional<int> xPos;
        std::optional<int> yPos;

        if (m_shape.getPosition().x > verticalBounds.second)
            xPos = std::make_optional(verticalBounds.second);
        else if (m_shape.getPosition().x < verticalBounds.first)
            xPos = std::make_optional(verticalBounds.first);
        else if (m_shape.getPosition().y > horizontalBounds.second)
            yPos = std::make_optional(horizontalBounds.second);
        else if (m_shape.getPosition().y < horizontalBounds.first)
            yPos = std::make_optional(horizontalBounds.first);

        if (xPos.has_value())
            m_shape.setPosition(xPos.value(), m_shape.getPosition().y);

        if (yPos.has_value())
            m_shape.setPosition(m_shape.getPosition().x, yPos.value());        
    }
};

class World
{
    // Define some constants;
    const int gameWidth = 800;
    const int gameHeight = 600;
    float ballRadius = 10.f;
    bool isAutoChangeColor = true;
    bool isSurpriseMode = true;

    sf::RenderWindow window;
    sf::Sound ballSound;

public:
    World()
        : window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML Pong", 
            sf::Style::Titlebar | sf::Style::Close)
    {
        std::srand(static_cast<unsigned int>(std::time(NULL)));
        window.setVerticalSyncEnabled(true);

        // Load the sounds used in the game
        sf::SoundBuffer ballSoundBuffer;
        if (!ballSoundBuffer.loadFromFile("resources/ball.wav"))
            throw std::exception("can't load sound from file resources/ball.wav");
        sf::Sound ballSound{ ballSoundBuffer };
    }

    int main()
    {
        // Create the left paddle
        Paddle leftPaddle;
        leftPaddle.setFillColor(sf::Color(100, 100, 200));

        // Create the right paddle
        Paddle rightPaddle;
        rightPaddle.setFillColor(sf::Color(200, 100, 100));

        // Create the ball
        sf::CircleShape ball;
        ball.setRadius(ballRadius - 3);
        ball.setOutlineThickness(3);
        ball.setOutlineColor(sf::Color::Black);
        ball.setFillColor(sf::Color::White);
        ball.setOrigin(ballRadius / 2, ballRadius / 2);

        // Load the text font
        sf::Font font;
        if (!font.loadFromFile("resources/sansation.ttf"))
            return EXIT_FAILURE;

        // Initialize the pause message
        sf::Text pauseMessage;
        pauseMessage.setFont(font);
        pauseMessage.setCharacterSize(40);
        pauseMessage.setPosition(170.f, 150.f);
        pauseMessage.setFillColor(sf::Color::White);
        pauseMessage.setString("Welcome to SFML pong!\nPress space to start the game");

        // Define the paddles properties
        sf::Clock AITimer;
        const sf::Time AITime = sf::seconds(0.1f);
        const float paddleSpeed = 400.f;
        float rightPaddleSpeed = 0.f;
        const float ballSpeed = 400.f;
        float ballAngle = 0.f; // to be changed later

        sf::Clock clock;
        bool isPlaying = false;
        while (window.isOpen())
        {
            // Handle events
            sf::Event event;
            while (window.pollEvent(event))
            {
                // Window closed or escape key pressed: exit
                if ((event.type == sf::Event::Closed) ||
                    ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
                {
                    window.close();
                    break;
                }

                // Space key pressed: play
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
                {
                    if (!isPlaying)
                    {
                        // (re)start the game
                        isPlaying = true;
                        clock.restart();

                        // Reset the position of the paddles and ball
                        leftPaddle.setPosition(10 + leftPaddle.getSize().x / 2, gameHeight / 2);
                        rightPaddle.setPosition(gameWidth - 10 - leftPaddle.getSize().x / 2, gameHeight / 2);
                        ball.setPosition(gameWidth / 2, gameHeight / 2);

                        // Reset the ball angle
                        do
                        {
                            // Make sure the ball initial angle is not too much vertical
                            ballAngle = Math::degToRad(std::rand() % 360);
                        } while (std::abs(std::cos(ballAngle)) < 0.7f);
                    }
                }
            }

            if (isPlaying)
            {
                float deltaTime = clock.restart().asSeconds();

                // Move the player's paddle
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    leftPaddle.move(0.f, -paddleSpeed * deltaTime);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    leftPaddle.move(0.f, paddleSpeed * deltaTime);

                // Move the computer's paddle
                if (((rightPaddleSpeed < 0.f) && (rightPaddle.getPosition().y - rightPaddle.getSize().y / 2 > 5.f)) ||
                    ((rightPaddleSpeed > 0.f) && (rightPaddle.getPosition().y + rightPaddle.getSize().y / 2 < gameHeight - 5.f)))
                {
                    rightPaddle.move(0.f, rightPaddleSpeed * deltaTime);
                }

                // Update the computer's paddle direction according to the ball position
                if (AITimer.getElapsedTime() > AITime)
                {
                    AITimer.restart();
                    if (ball.getPosition().y + ballRadius > rightPaddle.getPosition().y + rightPaddle.getSize().y / 2)
                        rightPaddleSpeed = paddleSpeed;
                    else if (ball.getPosition().y - ballRadius < rightPaddle.getPosition().y - rightPaddle.getSize().y / 2)
                        rightPaddleSpeed = -paddleSpeed;
                    else
                        rightPaddleSpeed = 0.f;
                }

                // Move the ball
                float factor = ballSpeed * deltaTime;
                ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

                // Check collisions between the ball and the screen
                // LEFT
                if (ball.getPosition().x - ballRadius < 0.f)
                {
                    isPlaying = false;
                    pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
                }
                // RIGHT
                if (ball.getPosition().x + ballRadius > gameWidth)
                {
                    isPlaying = false;
                    pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
                }
                // TOP
                if (ball.getPosition().y - ballRadius < 0.f)
                {
                    ballSound.play();
                    ballAngle = -ballAngle;
                    if (isSurpriseMode)
                    {
                        ballAngle += Math::degToRad(Math::randRange(-30, 30));
                    }
                    ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);
                }
                // BOTTOM
                if (ball.getPosition().y + ballRadius > gameHeight)
                {
                    ballSound.play();
                    ballAngle = -ballAngle;
                    if (isSurpriseMode)
                    {
                        ballAngle += Math::degToRad(Math::randRange(-30, 30));
                    }
                    ball.setPosition(ball.getPosition().x, gameHeight - ballRadius - 0.1f);
                }

                // Check the collisions between the ball and the paddles
                // Left Paddle
                if (ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + leftPaddle.getSize().x / 2 &&
                    ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
                    ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - leftPaddle.getSize().y / 2 &&
                    ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + leftPaddle.getSize().y / 2)
                {
                    if (ball.getPosition().y > leftPaddle.getPosition().y)
                        ballAngle = M_PI - ballAngle + Math::degToRad(std::rand() % 50);
                    else
                        ballAngle = M_PI - ballAngle - Math::degToRad(std::rand() % 50);

                    ballSound.play();
                    if (isAutoChangeColor)
                    {
                        changeBallColor(ball);
                    }
                    ball.setPosition(leftPaddle.getPosition().x + ballRadius + leftPaddle.getSize().x / 2 + 0.1f, ball.getPosition().y);
                }

                // Right Paddle
                if (ball.getPosition().x + ballRadius > rightPaddle.getPosition().x - rightPaddle.getSize().x / 2 &&
                    ball.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
                    ball.getPosition().y + ballRadius >= rightPaddle.getPosition().y - rightPaddle.getSize().y / 2 &&
                    ball.getPosition().y - ballRadius <= rightPaddle.getPosition().y + rightPaddle.getSize().y / 2)
                {
                    if (ball.getPosition().y > rightPaddle.getPosition().y)
                        ballAngle = M_PI - ballAngle + Math::degToRad(std::rand() % 50);
                    else
                        ballAngle = M_PI - ballAngle - Math::degToRad(std::rand() % 50);

                    ballSound.play();
                    if (isAutoChangeColor)
                    {
                        changeBallColor(ball);
                    }
                    ball.setPosition(rightPaddle.getPosition().x - ballRadius - rightPaddle.getSize().x / 2 - 0.1f, ball.getPosition().y);
                }
            }

            // Clear the window
            window.clear(sf::Color(50, 200, 50));

            if (isPlaying)
            {
                // Draw the paddles and the ball
                leftPaddle.draw(window);
                rightPaddle.draw(window);
                window.draw(ball);
            }
            else
            {
                // Draw the pause message
                window.draw(pauseMessage);
            }

            // Display things on screen
            window.display();
        }

        return EXIT_SUCCESS;
    }    
};


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    World world;
    return world.main();
}