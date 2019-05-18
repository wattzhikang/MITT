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
            )
            : x_pos(x_pos),
            y_pos(y_pos),
            z_pos(z_pos),
            x_vel(x_vel),
            y_vel(y_vel),
            z_vel(z_vel),
            epoch(epoch)
        {};

        double getXPosition() {return x_pos;}
        double getYPosition() {return y_pos;}
        double getZPosition() {return z_pos;}
        
        double getXVelocity() {return x_vel;}
        double getYVelocity() {return y_vel;}
        double getZVelocity() {return z_vel;}

        double getEpoch() {return epoch;}
};

#endif