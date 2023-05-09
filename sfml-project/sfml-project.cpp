

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

using namespace std;

int randomnumber(float min ,  float max, float player_pos) {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the distribution of the generated numbers
    std::normal_distribution<> dis(player_pos, 1.0);

    // Generate a random number between a and b (inclusive) that is close to c
    int randomNumber;
    do {
        randomNumber = std::round(dis(gen));
    } while (randomNumber < min || randomNumber > max);

    return randomNumber;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 768), "My game");

    //defining player
    sf::RectangleShape player(sf::Vector2f(75 , 75));
    player.setFillColor(sf::Color::Blue);
    player.setOrigin(player.getSize().x / 2, player.getSize().y / 2);
    player.setPosition(window.getSize().x/2, 560);

    //defining asteroids 
    sf::CircleShape asteroid(20.0f);
    asteroid.setFillColor(sf::Color::Red);
    asteroid.setOrigin(asteroid.getGlobalBounds().width / 2, asteroid.getGlobalBounds().height / 2);
    asteroid.setPosition(100, 0);

    sf::CircleShape asteroids[5];
    int l = 0;

    //global variables
    float speed = 270.0f;
    float gravity = 350.0f;
    int score = 0;



    //clock to check time and then calculate delta time
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //checking delta time
        sf::Time deltaTime = clock.restart();

        //movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -speed*deltaTime.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, speed*deltaTime.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A ) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-speed * deltaTime.asSeconds() * window.getSize().x / 500, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(speed * deltaTime.asSeconds() * window.getSize().x / 500, 0);


        // Keep the player within the screen bounds
        sf::Vector2f position = player.getPosition();
        position.x = std::max(position.x, 0.f);
        position.x = std::min(position.x, window.getSize().x - player.getGlobalBounds().width);
        position.y = std::max(position.y, 0.f);
        position.y = std::min(position.y, window.getSize().y - player.getGlobalBounds().height);
        player.setPosition(position);


        asteroid.move(0, gravity* deltaTime.asSeconds());


        
        if (asteroid.getPosition().y > window.getSize().y) {
            asteroid.setPosition(randomnumber(0, window.getSize().x, player.getPosition().x), 0);
            score++;
            cout << score;
        }

        if (asteroid.getGlobalBounds().intersects(player.getGlobalBounds())){
            asteroid.setPosition(randomnumber(0, window.getSize().x, player.getPosition().x), 0);
            cout << "You ded";
            window.close();
        }

        window.clear();
        window.draw(player);
        window.draw(asteroid);
        window.display();
    }

    return 0;
}

