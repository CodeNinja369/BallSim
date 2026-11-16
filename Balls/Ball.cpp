#include "Ball.h"
#include <cmath>
#include <limits>
ball::ball(sf::Vector2<float> p, int s, float sp, int d, int cc, sf::Color c) {
    pos = p;
    size = s;
    speed = sp;
    health= size;
    dmg = d;
    internaltick = 1;
    colour = c;
    compatability = cc;
    circle.setRadius(size);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition(pos);
    circle.setFillColor(colour);
    dead = false;
}
sf::Vector2<float> ball::getPos(){
    return pos;
}

sf::CircleShape ball::getCircle() {
    return circle;
}
int ball::getSize() {
    return size;
}
int ball::getDMG() {
    return dmg;
}
int ball::getHealth() {
    return health;
}
void ball::updateCircle() {
    circle.setRadius(size);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition(pos);
    circle.setFillColor(colour);
}
void ball::damage(int d) {
    health -= d;
    if (health <= 0) {
        die();
    }
}
void ball::attack(std::vector<ball*> targetlist) {
    if (internaltick > 0) {
        internaltick--;
    }
    ball* target = findTarget(targetlist);
    if (dead || target->isDead()) return;

    float le = finddist(pos, target->getPos());
    if (le > 0.f) {
        float step = std::min(speed, le);
        sf::Vector2<float> direction = (target->getPos() - pos);
        direction = { direction.x / le, direction.y / le };
        pos += direction * step;
    }
    updateCircle();
}
ball* ball::findTarget(std::vector<ball*> bs) {
    ball* closest = bs[0];
    float lowdist = std::numeric_limits<float>::max();
    for (ball* b : bs) {
        if (b != this && finddist(this->pos, b->getPos())<lowdist&&!b->isDead()){
            lowdist = finddist(this->pos, b->pos);
            closest = b;
        }
    }
    return closest;
}
float ball::finddist(sf::Vector2<float> ppp, sf::Vector2<float> ttt) {
    sf::Vector2<float> direction = (ttt - ppp);
    float distance = sqrt((direction.x * direction.x + direction.y * direction.y));
    return distance;
}
void ball::collide(ball* b2, int t, std::vector<ball*>& ballist) {
    float distance = finddist(b2->getPos(), this->pos);
    bool touching = distance < (this->size + b2->getSize()) && b2 != this
        && !b2->isDead() && !this->isDead();
    if (!touching) return;

    float overlap = (this->size + b2->getSize()) - distance;
    sf::Vector2<float> direction = (pos - b2->getPos());
    if (distance > 0.f) {
        direction = { direction.x / distance, direction.y / distance };
    }
    else {
        direction = { 1.f, 0.f };
    }

    pos += direction * (overlap * 0.5f);

    if (internaltick == 0) {
        internaltick = 180;
        if (iscomp(b2)&&!(b2->isDead())) {
            ballist.push_back(this->bread(b2));
        }
        else {
            b2->damage(dmg);
        }
        if (b2->isDead()) {
            size += b2->getSize();
            dmg += b2->getDMG();
            updateCircle();
        }
    }
}
bool ball::isDead() {
    return dead;
}
void ball:: die() {
    dead = true;
}
float ball::getSpd() {
    return speed;
}
int ball::getcomp() {
    return compatability;
}
bool ball::iscomp(ball* m) {
    if (m->getcomp() == this->getcomp()) {
        return true;
    }
    return false;

}
sf::Color ball::getColour() {
    return colour;
}
ball* ball::bread(ball* m) {
    m->die();
    this->die();
    sf::Color c1 = m->getColour();
    sf::Color c2 = this->getColour();
    return new ball(m->getPos(), m->getSize() + this->getSize(), m->getSpd() + this->getSpd(), m->getDMG() + this->getDMG(), m->getcomp() + this->getcomp(), sf::Color((c1.r + c2.r) / 2, (c1.g + c2.g) / 2, (c1.b + c2.b) / 2));
}
