#ifndef DATABASE_H
#define DATABASE_H
#include "../include/graphics.h"

/*in develop*/
struct Stats {
    int avgGameLen;
    int movesToWinQuantity;
    int staleMatePercentage;
    int gameLeavingPercentage;
    int giveUpsPercentage;
};

class IStatistics {
    virtual Stats getStats(User& user) const = 0;
    virtual Stats getfullStats(User& user) const = 0;
};


class Statistics : public IStatistics {
public:
    Stats getStats(User& user) const override;
    Stats getfullStats(User& user) const override;
    int getAverageGameLen() const;
    int getAverageMovesToWinQuantity() const;
    int getStaleMatePercentage() const;
    int getGameLeavingPercentage() const;
    int giveUpsPercentage() const;
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
