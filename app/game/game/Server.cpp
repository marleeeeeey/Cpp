#include "stdafx.h"
#include "Server.h"
#include <sstream>

void Server::loadBallSoundBuffer()
{
    // Load the sounds used in the game
    const std::string soundFileName = "resources/ball.wav";
    if (!ballSoundBuffer.loadFromFile(soundFileName))
    {
        std::stringstream ss;
        ss << "can't load sound from file " << soundFileName;
        throw std::runtime_error(ss.str());
    }
    ball.setSoundBuffer(ballSoundBuffer);
}

void Server::loadTextFont()
{
    // Load the text font
    const std::string fontFileName = "resources/sansation.ttf";
    if (!font.loadFromFile(fontFileName))
    {
        std::stringstream ss;
        ss << "can't load font from file " << fontFileName;
        throw std::runtime_error(ss.str());
    }
}

Server::Server(const int gameWidht, const int gameHeight)
    : gameWidth(gameWidht)
    , gameHeight(gameHeight)
{
    loadBallSoundBuffer();
    loadTextFont();

    leftPaddle.setFillColor(sf::Color(100, 100, 200));
    rightPaddle.setFillColor(sf::Color(200, 100, 100));

    pauseMessage.setFont(font);
    pauseMessage.setString("Welcome to SFML pong!\nPress space to start the game");
}

void Server::restartGame()
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
        }
        while (std::abs(std::cos(ballAngle)) < 0.7f);
    }
}

void Server::draw(sf::RenderWindow& window)
{
    // Clear the window
    window.clear(sf::Color(50, 200, 50));

    if (isPlaying)
    {
        leftPaddle.draw(window);
        rightPaddle.draw(window);
        ball.draw(window);
    }
    else
    {
        pauseMessage.draw(window);
    }
}

void Server::checkPaddlesCollision()
{
    // Check the collisions between the ball and the paddles
    // Left Paddle
    if (ball.getPosition().x - ball.getRadius() < leftPaddle.getPosition().x + leftPaddle.getSize().x / 2 &&
        ball.getPosition().x - ball.getRadius() > leftPaddle.getPosition().x &&
        ball.getPosition().y + ball.getRadius() >= leftPaddle.getPosition().y - leftPaddle.getSize().y / 2 &&
        ball.getPosition().y - ball.getRadius() <= leftPaddle.getPosition().y + leftPaddle.getSize().y / 2)
    {
        if (ball.getPosition().y > leftPaddle.getPosition().y)
            ballAngle = M_PI - ballAngle + Math::degToRad(std::rand() % 50);
        else
            ballAngle = M_PI - ballAngle - Math::degToRad(std::rand() % 50);

        ball.playSound();
        if (isAutoChangeColor)
        {
            ball.changeRandomColor();
        }
        ball.setPosition(leftPaddle.getPosition().x + ball.getRadius() + leftPaddle.getSize().x / 2 + 0.1f,
                         ball.getPosition().y);
    }

    // Right Paddle
    if (ball.getPosition().x + ball.getRadius() > rightPaddle.getPosition().x - rightPaddle.getSize().x / 2 &&
        ball.getPosition().x + ball.getRadius() < rightPaddle.getPosition().x &&
        ball.getPosition().y + ball.getRadius() >= rightPaddle.getPosition().y - rightPaddle.getSize().y / 2 &&
        ball.getPosition().y - ball.getRadius() <= rightPaddle.getPosition().y + rightPaddle.getSize().y / 2)
    {
        if (ball.getPosition().y > rightPaddle.getPosition().y)
            ballAngle = M_PI - ballAngle + Math::degToRad(std::rand() % 50);
        else
            ballAngle = M_PI - ballAngle - Math::degToRad(std::rand() % 50);

        ball.playSound();
        if (isAutoChangeColor)
        {
            ball.changeRandomColor();
        }
        ball.setPosition(rightPaddle.getPosition().x - ball.getRadius() - rightPaddle.getSize().x / 2 - 0.1f,
                         ball.getPosition().y);
    }
}

void Server::checkScreenCollision()
{
    // Check collisions between the ball and the screen
    // LEFT
    if (ball.getPosition().x - ball.getRadius() < 0.f)
    {
        isPlaying = false;
        pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
    }
    // RIGHT
    if (ball.getPosition().x + ball.getRadius() > gameWidth)
    {
        isPlaying = false;
        pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
    }
    // TOP
    if (ball.getPosition().y - ball.getRadius() < 0.f)
    {
        ball.playSound();
        ballAngle = -ballAngle;
        if (isSurpriseMode)
        {
            ballAngle += Math::degToRad(Math::randRange(-30, 30));
        }
        ball.setPosition(ball.getPosition().x, ball.getRadius() + 0.1f);
    }
    // BOTTOM
    if (ball.getPosition().y + ball.getRadius() > gameHeight)
    {
        ball.playSound();
        ballAngle = -ballAngle;
        if (isSurpriseMode)
        {
            ballAngle += Math::degToRad(Math::randRange(-30, 30));
        }
        ball.setPosition(ball.getPosition().x, gameHeight - ball.getRadius() - 0.1f);
    }
}

void Server::movePaddles(const float deltaTime)
{
    // Move the player's paddle
    if (client01->paddleUp())
        leftPaddle.move(0.f, -paddleSpeed * deltaTime);

    if (client01->paddleDown())
        leftPaddle.move(0.f, paddleSpeed * deltaTime);

    // Move the player's paddle
    if (client02->paddleUp())
        rightPaddle.move(0.f, -paddleSpeed * deltaTime);

    if (client02->paddleDown())
        rightPaddle.move(0.f, paddleSpeed * deltaTime);
}

void Server::moveBall(const float deltaTime)
{
    // Move the ball
    const auto factor = ballSpeed * deltaTime;
    ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);
}

void Server::iterate()
{
    if (!isPlaying)
        return;

    const auto deltaTime = clock.restart().asSeconds();

    movePaddles(deltaTime);
    moveBall(deltaTime);
    checkScreenCollision();
    checkPaddlesCollision();
}

void Server::setClient01(const std::shared_ptr<IClient> client)
{
    client01 = client;
}

void Server::setClient02(const std::shared_ptr<IClient> client)
{
    client02 = client;
}

ServerPackage Server::getPackage() const
{
    ServerPackage sp{};
    sp.screenSize = {gameWidth, gameHeight};
    sp.leftPaddleCenter = leftPaddle.getPosition();
    sp.leftPaddleSize = leftPaddle.getSize();
    sp.rightPaddleCenter = rightPaddle.getPosition();
    sp.rightPaddleSize = rightPaddle.getSize();
    sp.ballCenter = ball.getPosition();
    sp.ballRadius = ball.getRadius();
    sp.paddleSpeed = paddleSpeed;
    sp.ballSpeed = ballSpeed;
    return sp;
}
