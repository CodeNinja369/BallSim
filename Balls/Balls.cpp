#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <random>
int main() {
    unsigned int width = 500;
    unsigned int height = 500;
    int bsize = 10;
    int occurence = 20;
    int chaos = 2;
    int tick = 0;
    float speed = 0.5f;
    
    std::random_device rd;

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Balls");
    window->setFramerateLimit(60);
    
    std::vector<ball*> blist = {};
    for (unsigned int i = 0; i < width-10; i++) {
        for (unsigned int j = 0; j < height-10; j++) {
            std::uniform_int_distribution<int> red(0, 255);
            std::uniform_int_distribution<int> green(0, 255);
            std::uniform_int_distribution<int> blue(0, 255);
            std::uniform_int_distribution<int> sz(1, bsize);
            std::uniform_int_distribution<int> ir(1, chaos);
            std::uniform_int_distribution<int> jr(1, chaos);
            int bsize = sz(rd);
            int damage = 1;
            if (i % (occurence+ ir(rd)) == 0 && j % (occurence + jr(rd)) == 0) {
                sf::Color tempc = sf::Color(red(rd), green(rd), blue(rd));
                blist.push_back(new ball({ static_cast<float>(i),static_cast<float>(j) }, bsize, speed, damage, tempc));
            }
        }
    }
    while(window->isOpen()) {
        if (tick == 180) {
            tick = 0;
        }
        else {
            tick++;
        }
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
        }
        window->clear();
        
        for (int i = 0; i < blist.size();i++) {
            if (blist[i]->isDead()) {
                delete blist[i];
                blist.erase(blist.begin() + i);
            }
            else {
                blist[i]->attack(blist);
                for (int j=0; j < blist.size(); j++) {
                    blist[i]->collide(blist[j], tick);
                }
                window->draw(blist[i]->getCircle());
            }
            
        }
        window->display();
    }
    for (ball* b : blist) {
        std::cout << b->getDMG()<<"\n";
        std::cout << b->getHealth()<<"\n";
        delete b;
    }
    delete window;
    return 0;
}