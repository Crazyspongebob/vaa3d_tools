#ifndef RESAMPLING_H
#define RESAMPLING_H

#include "basic_surf_objs.h"
#include <vector>
using namespace std;

#define DISTP(a,b) sqrt(((a)->x-(b)->x)*((a)->x-(b)->x)+((a)->y-(b)->y)*((a)->y-(b)->y)+((a)->z-(b)->z)*((a)->z-(b)->z))

struct Point;
struct Point
{
    double x,y,z,r;
    V3DLONG type;
    Point* p;
    V3DLONG childNum;
};
typedef vector<Point*> Segment;
typedef vector<Point*> Tree;

void resample_path(Segment * seg, double step);
NeuronTree resample(NeuronTree input, double step);
#endif // RESAMPLING_H
