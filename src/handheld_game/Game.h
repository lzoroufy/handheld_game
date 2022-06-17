#ifndef _Game_h_
#define _Game_h_
class Game{
  private:
    long game_time;
    int total_rounds;
    long target_gen;
    int auto_reload;
    int score = 0;
    void game_loop();
    void shoot();
    int reload();
    void set_lights(int num);
    void start_up();
    void end_game();
    void set_target();
  public:
    Game(long g, long t, int r, int a);
    ~Game();
    int run_game();
    void update_scope();
};
#endif
