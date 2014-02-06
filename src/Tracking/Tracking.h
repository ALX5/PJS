#include "../Main.h"

class Tracking
{
public :
    Tracking();
    void setupTracking ();
    double X;
    double Y;
    double Z;

    double getX() { return X; }
    double getY() { return Y; }
    double getZ() { return Z; }
};
