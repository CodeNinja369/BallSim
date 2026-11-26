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
	int compatability;
	int deathCountdown;
	int internaltick;
	float finddist(sf::Vector2<float> ppp, sf::Vector2<float> ttt);
	bool iscomp(ball* m);
	int getcomp();
	ball* bread(ball* m);
	float getSpd();
public:
	ball(sf::Vector2<float> p, int s, float sp, int d, int cc, sf::Color c);
	void updateCircle();
	sf::Vector2<float> getPos();
	sf::CircleShape getCircle();
	sf::Color getColour();
	int getSize();
	int getDMG();
	int getHealth();
	void attack(std::vector<ball*> target);
	ball* findTarget(std::vector<ball*> bs);
	bool isDead();
	void die();
	void damage(int d);
	void bound(int w, int h);
	void collide(ball* b2, int t, std::vector<ball*>& ballist);
};

#endif