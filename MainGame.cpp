#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Player.h"
#include "MovingPictures.h"
using namespace std;

// this function creates a text based title screen for my game called "The Game"
void titleScreen()
{
  cout << "Welcome to The Game!" << endl;
  cout << "Press Enter to continue..." << endl;
  cin.get();
}

// this function creates an array of arts that the player can choose from
  Art slash("slash", "casual slash with sword", 10, 5, 1, 1, Art::attack);
  Art stab("stab", "casual stab with sword", 15, 10, 2, 1, Art::attack);
  Art fireball("fireball", "casual fireball", 20, 15, 3, 1, Art::attack);
  Art sunlight("sunlight", "casual heal", 30, 10, 2, 1, Art::heal);
  Art sheild("defend", "casual defend", 5, 10, 2, 1, Art::defend);
  Art sidestep("dodge", "casual dodge", 13, 10, 2, 1, Art::dodge);
  vector<Art> arts = {slash, stab, fireball, sunlight, sheild, sidestep};
  vector<Art> playerArts = {stab, fireball, sunlight, sidestep};


// this function will give the player the option ot choose one art from the array of arts called arts
Art playerArt(vector<Art> arts)
{
  string type = "player";

  cout << "Choose an art: " << endl;
  for (int i = 0; i < arts.size(); i++)
  {
    cout << i + 1 << ". " << arts[i].name << endl;
  }
  int choice;
  cin >> choice;
  cout << "You chose " << arts[choice - 1].name << endl;
  return arts[choice - 1];
}

//this function has the enemy pick an art at random
Art enemyArt(vector<Art> arts)
{
  string type = "enemy";

  // create an int called choice and assigin it the value of a random number with time as its seed
  srand(time(NULL));
  int choice = rand() % 5;

  cout << choice << endl;
  cout << "The enemy chose " << arts[choice].name << endl;
  return arts[choice];
}

void attack(Art CurrentArt, Player& victim)
{
  victim.health = victim.health - CurrentArt.intesity;
  cout << victim.name << " took " << CurrentArt.intesity << " damage!" << endl;
}

void defend(Art attackArt, Art defenceArt, Player& attacker, Player& defender)
{
  defender.health = attackArt.intesity * (defenceArt.intesity / 100);
  cout << defender.name << " Took " << attackArt.intesity << " damage!" << endl;
}

void heal(Art CurrentArt, Player& user)
{
  user.health =+ CurrentArt.intesity;
  cout << user.name << " regained " << CurrentArt.intesity << " health!" << endl;
}

void dodge(Art attackArt, Art dodgeArt, Player& dodger)
{
  if (dodgeArt.intesity > attackArt.intesity)
  {
    cout << dodger.name << " dodged the attack!" << endl;
  }
  else
  {
    dodger.health =- attackArt.intesity;
    cout << dodger.name << " failed to dodge and took " << attackArt.intesity << " damage!" << endl;
  }
}

//this function enacts the effects of the current players art
void Battle(Art goodGuyCurrentArt, Art badGuyCurrentArt, Player& goodGuy, Player& badGuy)
{
  switch (goodGuyCurrentArt.type)
  {
  case Art::attack:

    switch (badGuyCurrentArt.type)
    {
    case Art::attack:
      attack(goodGuyCurrentArt, badGuy);
      attack(badGuyCurrentArt, goodGuy);
      break;

    case Art::defend:
      defend(goodGuyCurrentArt, badGuyCurrentArt, goodGuy, badGuy);
      break;
    
    case Art::heal:
      heal(badGuyCurrentArt, badGuy);
      attack(goodGuyCurrentArt, badGuy);
      break;

    case Art::dodge:
      dodge(goodGuyCurrentArt, badGuyCurrentArt, badGuy);
      break;
    }
    break;

  case Art::defend:
    switch (badGuyCurrentArt.type)
    {
    case Art::attack:
      defend(badGuyCurrentArt, goodGuyCurrentArt, badGuy, goodGuy);
      break;

    case Art::defend:
      cout << "Both players defended (you look like real prunes)" << endl;
      break;

    case Art::heal:
      heal(badGuyCurrentArt, badGuy);
      break;

    case Art::dodge:
      cout << goodGuy.name + " defends while " + badGuy.name + " dodges (what a waste of time)" << endl;
      break;
    }
    break;

  case Art::heal:
    switch (badGuyCurrentArt.type)
    {
    case Art::attack:
      heal(goodGuyCurrentArt, goodGuy);
      attack(badGuyCurrentArt, goodGuy);
      break;
    
    case Art::defend:
      heal(goodGuyCurrentArt, goodGuy);
      break;

    case Art::heal:
      heal(goodGuyCurrentArt, goodGuy);
      heal(badGuyCurrentArt, badGuy);
      break;

    case Art::dodge:
      heal(goodGuyCurrentArt, goodGuy);
      break;
    }
    break;

  case Art::dodge:
    switch (badGuyCurrentArt.type)
    {
    case Art::attack:
      dodge(badGuyCurrentArt, goodGuyCurrentArt, goodGuy);
      break;

    case Art::defend:
      cout << goodGuy.name + " dodges while " + badGuy.name + " defends (what a waste of time)" << endl;
      break;

    case Art::heal:
      heal(badGuyCurrentArt, badGuy);

    case Art::dodge:
      cout << "Both players dodged (what a lovly dance)" << endl;
      break;
    }
    break;
  
  default:
    cout << "Error, no matching type" << endl;
    break;
  }
}

vector<string> createAnimation(string path)
{
  // read the animation file and push each line into the animationSequence vector
  
  vector<string> animationSequence;
  string line = "";

  ifstream anmFile;
  anmFile.open("./AnimSequences/" + path);

  while (getline(anmFile, line))
  {
    animationSequence.push_back(line);
  }

  anmFile.close();

  vector<string> animation;
  for (int i = 0; i < animationSequence.size(); i++)
  {
    string fileName = "./animations/" + animationSequence[i] + ".txt";
    animation.push_back(readFile(fileName));
  }
  return animation;
}

int main() 
{
  Player goodGuy("Player", 100, 10, playerArts);
  Player badGuy("Enemy", 100, 10, arts);

  cout << goodGuy.name << endl;
  titleScreen();

  while (goodGuy.health > 0 && badGuy.health > 0)
  {
    cout << "Player health: " << goodGuy.health << endl;
    cout << "Enemy health: " << badGuy.health << endl;

    Art goodGuyCurrentArt = playerArt(goodGuy.arts);
    Art badGuyCurrentArt = enemyArt(badGuy.arts);

    Battle(goodGuyCurrentArt, badGuyCurrentArt, goodGuy, badGuy);
    cout << endl;
    
    images(createAnimation("Wave.anm"));
  }
  return 0;
}

