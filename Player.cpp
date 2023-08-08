#include "Player.h"
using namespace std;

//constructor for Player class
Player::Player(string name, int health, int stamina, vector<Art> arts)
{
  this->name = name;
  this->health = health;
  this->stamina = stamina;
  this->arts = arts;
}
