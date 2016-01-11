//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_PLAYER_H
#define KNOWLEDGE_ENGINEERING_PLAYER_H

#include <string>
#include "Dribbling.h"
#include "Shooting.h"
#include "Physical.h"
#include "Passing.h"
#include "Pace.h"
#include "Defending.h"

class Player {
public:
    std::string name;
    std::string surname;
    float height;
    void *picture; //placeholder
    bool notifySpecial;

    struct specialStatistics {
        Dribbling *dribbling;
        Shooting *shooting;
        Physical *physical;
        Passing *passing;
        Pace *pace;
        Defending *defending;
    };

private:
    unsigned int privateID;
};


#endif //KNOWLEDGE_ENGINEERING_PLAYER_H
