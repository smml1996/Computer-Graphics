#include <vector>
#include "Bullet.h"

class Main_Character{
  float actualAngle;
  int t;
  int tbase;
  int tbaseSpecialStatus;

  float V_0;

  void drawBullets(const int &velocity);
public:
  std::vector<Bullet *> bullets;
  int actualColumn;
  int status;
    // 0: natural status
    // 1: jumping
    // 2: deslizar echado
    // 3: protect
  float sizeCharacter;
  float y;
  int score;
  int textureNormal;
  int textureProtected;
  Main_Character();
  ~Main_Character();
  void draw(const int &velocity);
  void jump();
  void deslizar();
  void throwbullet();

  void protect();
};
