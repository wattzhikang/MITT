#ifndef STATE_H
#define STATE_H

class State {
    private:
        double x_pos, y_pos, z_pos;
        double x_vel, y_vel, z_vel;
        double epoch;
    public:
        State(
            double x_pos,
            double y_pos,
            double z_pos,
            double x_vel,
            double y_vel,
            double z_vel,
            double epoch
            ) : x_pos(x_pos),
            y_pos(y_pos),
            z_pos(z_pos),
            x_vel(x_vel),
            z_vel(z_vel),
            epoch(epoch)
        {}

        double getXPosition();
        double getYPosition();
        double getZPosition();
        
        double getXVelocity();
        double getYVelocity();
        double getZPosition();

        double getEpoch();
}

#endif