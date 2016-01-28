#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include "normal.h"

class Difference : public Normal
{
public:
    Difference(float upper, float lower, float average);
};

#endif // DIFFERENCE_H
