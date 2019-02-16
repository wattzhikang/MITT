#ifndef GRAV_SYSTEM_H
#define GRAV_SYSTEM_H

class GravitationalSystem {
    private:
        //a tree of frames, or an ordered set?

        //some structure of planets

    public:
        //user will request a frame at a certain time and to a certain precison
        //if frame has already been computed, it will return the frame,
        // if it does not exist, it will be computed, added to the tree,
        //and returned
        Frame getFrame(double epoch, double precision);
};

#endif