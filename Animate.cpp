#include "Processing.h"
float Processing::map(float percent, float newLowest, float newHighest, Func mappingFunction)
{
    return mappingFunction(percent) * (newHighest - newLowest) + newLowest;
}
float Processing::map(float value, float lowestValue, float hightestValue, float newLowest, float newHighest, Func mappingFunction)
{
    return mappingFunction((value - lowestValue) / (hightestValue - lowestValue)) * (newHighest - newLowest) + newLowest;
}
float Processing::constrain(float value, float min, float max)
{
    if (value < min)
        return min;
    else if (max < value)
        return max;
    else
        return value;
}
float Processing::constrainMap(float percent, float newLowest, float newHighest, Func mappingFunction)
{
    return mappingFunction(constrain(percent, 0, 1)) * (newHighest - newLowest) + newLowest;
}
float Processing::constrainMap(float value, float lowestValue, float hightestValue, float newLowest, float newHighest, Func mappingFunction)
{
    return mappingFunction(constrain((value - lowestValue) / (hightestValue - lowestValue), 0, 1)) * (newHighest - newLowest) + newLowest;
}
