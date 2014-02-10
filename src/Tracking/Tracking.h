#include "../Main.h"

class Tracking
{
public :
    Tracking();
    void setupTracking ();
    double X = 0.0;
    double Y = 0.0;
    double Z = 0.0;

    double getX() { return X; }
    double getY() { return Y; }
    double getZ() { return Z; }
};
