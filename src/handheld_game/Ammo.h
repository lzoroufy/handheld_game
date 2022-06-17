#ifndef _Ammo_h_
#define _Ammo_h_
class Ammo{
  private:
    int shot_1 = 1;
    int shot_2 = 2;
    int shot_3 = 3;
    int shot_4 = 4;
    int shot_5 = 5;
    int rounds_left = 0;
    int total;
    void update();
  public:
    Ammo(int r);
    ~Ammo();
    int fire();
    void reload();
    void set_rounds(int num);
    int get_remaining();
};
#endif
