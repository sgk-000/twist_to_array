#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>

class Converter
{
public:
    Converter()
    {
        ros::NodeHandle nh_;
        twist_sub = nh_.subscribe("key_vel", 1000, &Converter::TwistCallback_, this);
        array_pub = nh_.advertise<std_msgs::Float32MultiArray>("vel_array", 10);
    }

    void TwistCallback_(const geometry_msgs::Twist::ConstPtr twist_data) {
        output_.data.resize(3);
        output_.data[0] = twist_data->linear.x;
        output_.data[1] = twist_data->linear.y;
        output_.data[2] = twist_data->angular.z;
        array_pub.publish(output_);
    }
protected:
    std_msgs::Float32MultiArray output_;
    ros::Publisher array_pub;
    ros::Subscriber twist_sub;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "twist_to_array");
    Converter instance;
    ros::spin();
}
