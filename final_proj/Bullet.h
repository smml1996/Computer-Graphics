class Bullet{

  float offsetX;

  int t;
  int tbase;
public:
  float offsetZ;
  int column;
  bool isValid;
  Bullet(const int &column);
  ~Bullet();
  void move(const int &velocity);
};
