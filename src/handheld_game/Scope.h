#ifndef _Scope_h_
#define _Scope_h_
class Scope{
  private:
    int scope_x = 42;
    int scope_y = 24;
    int scope_visible = 0;
    void set_scope_coord(int x, int y);
    void calc_move_scope(double z, double y);
    int calc_x_move(double y, int y_move);
  public:
    Scope();
    ~Scope();
    void set_scope();
    void remove_scope();
    void move_scope(int x, int y);
    void update_scope();
    int get_x();
    int get_y();
};
#endif
