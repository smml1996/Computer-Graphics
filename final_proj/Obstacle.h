class Obstacle{

private:
  int t;
  int tbase;
protected:
  const float limitZ = 22;
  int columnIndex;
  float translationZ;
  float dt;
  float actualAngle;
  float actualAngleHueco;

public:
  bool isValid;
  bool isCaja;
  bool isCoin;
  static int level;
  Obstacle();
  virtual void draw() = 0;
  virtual bool checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ) = 0;
  void move(int velocity);
  void setColumnIndex(const int &column);
};
