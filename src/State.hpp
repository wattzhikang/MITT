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

        //default assignment operator and copy constructors are ok

        double getXPosition() {return x_pos;}
        double getYPosition() {return y_pos;}
        double getZPosition() {return z_pos;}
        
        double getXVelocity() {return x_vel;}
        double getYVelocity() {return y_vel;}
        double getZVelocity() {return z_vel;}

        double getEpoch() {return epoch;}

        bool operator==(const State& rhs) {
            if (x_pos == rhs.x_pos &&
                y_pos == rhs.y_pos &&
                z_pos == rhs.z_pos &&
                x_vel == rhs.x_vel &&
                y_vel == rhs.y_vel &&
                z_vel == rhs.z_vel &&
                epoch == rhs.epoch)
            {
                    return true;
            }
            else
            {
                return false;
            }
        }
        bool operator!=(const State& rhs) {
            return !(*this == rhs);
        }
};

#endif