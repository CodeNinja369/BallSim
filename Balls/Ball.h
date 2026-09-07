#ifndef BALL_H
#define BALL_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
class ball {
private:
	sf::Vector2<float> pos;
	sf::CircleShape circle;
	int size;
	float speed;
	sf::Color colour;
	bool dead;
	int dmg;
	int health;
	void updateCircle();
	int internaltick;
	float finddist(sf::Vector2<float> ppp, sf::Vector2<float> ttt);
public:
	ball(sf::Vector2<float> p, int s, float sp, int d, sf::Color c);
	sf::Vector2<float> getPos();
	sf::CircleShape getCircle();
	int getSize();
	int getDMG();
	int getHealth();
	void attack(std::vector<ball*> target);
	ball* findTarget(std::vector<ball*> bs);
	bool isDead();
	void die();
	void damage(int d);
	void collide(ball* b2, int t);
};

#endif