#include "Art.h"
using namespace std;

//constructor for an Arts class with a name, description, damage, cooldown, and stamina cost and effect
Art::Art(string name, string description, int intesity, int cooldown, int staminaCost, int effect, ArtType type)
{
  this->name = name;
  this->description = description;
  this->intesity = intesity;
  this->cooldown = cooldown;
  this->staminaCost = staminaCost;
  this->effect = effect;
  this->type = type;
}