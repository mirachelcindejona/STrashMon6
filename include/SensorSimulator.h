#ifndef SENSOR_SIMULATOR_H
#define SENSOR_SIMULATOR_H

#include <vector>
#include <string>
using namespace std;

struct TrashBin {
    string id;
    string location;
    float level;
};

extern vector<TrashBin> sensorList;

void updateSensorLevels();
void displaySensorStatus();
void resetSensorData();
void simpanTempatKeFile();
void updateSemuaHistori();
string getStatusIndikator(float level);

#endif