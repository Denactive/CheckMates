#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include "../include/community.h"
//#include "../graphics.h"

/*in develop*/
struct Stats {
    int avgGameLen;
    int movesToWinQuantity;
    int staleMatePercentage;
    int gameLeavingPercentage;
    int giveUpsPercentage;
};

class IStatistics {
    virtual Stats * getStats(User * user) = 0;
    virtual int getAverageGameLen() = 0;
    virtual int getAverageMovesToWinQuantity()= 0;
    virtual int getStaleMatePercentage() = 0;
    virtual int getGameLeavingPercentage() = 0;
    virtual int giveUpsPercentage() = 0;
};


class Statistics : public IStatistics {
public:
    Stats * getStats(User * user) override { return nullptr; }
    int getAverageGameLen() override;
    int getAverageMovesToWinQuantity() override;
    int getStaleMatePercentage() override;
    int getGameLeavingPercentage() override;
    int giveUpsPercentage() override;
};

class IDatabase {
     virtual std::string query(std::string) const = 0;
};

class Database : public IDatabase
{
public:
    Database();
    std::string query(std::string) const override;
private:
    std::string fileDB;
};

#endif // DATABASE_H
