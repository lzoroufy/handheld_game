#ifndef _Timer_h_
#define _Timer_h_
class Timer{
  private:
    long current;
    long end_time;
    long duration;
  public:
    Timer(long t);
    ~Timer();
    int is_done();
    void reset();
    void reset(long t);
    
};
#endif
