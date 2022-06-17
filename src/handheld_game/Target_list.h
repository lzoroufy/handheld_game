#ifndef _Target_list_h_
#define _Target_list_h_
class Target_list{
  private:
    int target_counter = 0;
    int target[84][48];
    int score = 0;
  public:
    Target_list(int n);
    ~Target_list();
    int is_available(int x, int y);
    void update_list(int x, int y);
    void target_added();
    void remove_target(int t);
    int target_hit(int t);
    int is_hit(int x, int y);
    int get_score();
};
#endif
    
    
