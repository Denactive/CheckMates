//
// Created by yura11011 on 15.04.2021.
//

#ifndef CHECKMATES_STATS_H
#define CHECKMATES_STATS_H
class iStats{
public:
    virtual void get_user_info(size_t user_id) = 0;
    virtual void get_user_stats(size_t user_id) = 0;

};

class Stats: public iStats {
public:
    Stats();
    virtual void get_user_info(size_t user_id);
    virtual void get_user_stats(size_t user_id);
private:
    Stats& stats;
};



#endif //CHECKMATES_STATS_H
