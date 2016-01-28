#include "normal.h"
#include "difference.h"

Normal::Normal(float upper, float lower, float average)
    : upper(upper), lower(lower), average(average)
{

}

Difference Normal::difference(float value)
{
    return Difference(
                value - upper,
                value - lower,
                value - average
    );
}
