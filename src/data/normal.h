#ifndef NORMAL_H
#define NORMAL_H

class Difference;

class Normal
{
public:
    Normal(float upper, float lower, float average);

    Difference difference(float value);

    const float upper;
    const float lower;
    const float average;
};

#endif // NORMAL_H
