#ifndef PROV_FIELD_H
#define PROV_FIELD_H

#include <vector>
#include <array>
#include "objects.hpp"
#include <tuple>
#include "network/network.hpp"
#include "./botlocale/lidar.hpp"
#include "./botlocale/mcl.hpp"
#include <ntcore.h>
#include <networktables/NetworkTable.h>
#include "botlocale/lidar.hpp"


struct SensorData {
    double leftEncoder;
    double rightEncoder;
    double accelX;
    double accelZ;
    double accelY;
    double yaw;
    bool operator==(const SensorData other) {
        return (leftEncoder == other.leftEncoder && rightEncoder == other.rightEncoder && accelX == other.accelX);
    }
};

class Field {
private:
    Field();
    static Field* instance;
public:
    static Field* getInstance();
    void load();
    void update(std::vector<bbox_t>);
    void update(LidarScan);
    void tick();
    void render();
    float dist_front_obstacle();
    void put_pose_nt(std::vector<Pose> poses, std::string mainKey, std::string parent);
    void put_arrays_nt(std::string mainKey, std::map<std::string, std::vector<double>> data, std::string parent);
    void put_arrays_nt(std::string mainKey, std::string parent, int count, ...);
    void put_values_nt(std::string mainKey, std::map<std::string, double> data, std::string parent);
    void put_values_nt(std::string mainKey, std::string parent, int count, ...);
    void put_value_nt(std::string key, double data, std::string parent);
    void put_value_nt(std::string key, std::vector<double> data, std::string parent);
    void get_sensor_data_nt();
    std::map<std::string, double> get_values_nt(std::vector<std::string> keys, std::string parent);
    std::vector<Segment> construct;
    std::vector<Pose> objects;
    std::vector<Pose> robots;
    Pose pose_distribution[SAMPLES];
    Pose me;
    cv::Mat renderedImage;
    NT_Inst nt_inst;
    SensorData latest_data;
    SensorData old_data;
    LidarScan latest_lidar_scan;
    double field_width;
    double field_height;
};

#endif