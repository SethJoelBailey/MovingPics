#include <iostream>
#pragma once
using namespace std;

// this is a class called Player that has the attributes name, health, and skill
class Art
{ 
  public:
  enum ArtType {attack, defend, heal, dodge};

  public:
    Art(string name, string description, int intesity, int cooldown, int staminaCost, int effect, ArtType type);

  public:
    string name;
    string description;
    int intesity;
    int cooldown;
    int staminaCost;
    int effect;
    ArtType type;

};