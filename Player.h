#include <iostream>
#include <vector>
#include "Art.h"
using namespace std;

// this is a class called Player that has the attributes name, health, and skill
class Player
{
  public:
    Player(string name, int health, int stamina, vector<Art> arts);

  public:
    string name;
    int health;
    int stamina;
    vector<Art> arts;
};
