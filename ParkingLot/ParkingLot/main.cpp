//
//  main.cpp
//  ParkingLot
//
//  Created by Haochen Wang on 5/12/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
// enum type for Vehicle
enum class VehicleSize {
    Motorcycle,
    Compact,
    Large,
    Others
};

class Vehicle {
public:
    virtual VehicleSize size(){return VehicleSize::Others;}
};

class Bus: public Vehicle {
public:
    VehicleSize size(){return VehicleSize::Large;}
};

class Car: public Vehicle {
public:
    VehicleSize size(){return VehicleSize::Compact;}
};

class Motorcycle: public Vehicle {
public:
    VehicleSize size(){return VehicleSize::Motorcycle;}
};

class Level {
private:
    std::vector<Vehicle*> motor_cycle;
    std::vector<Vehicle*> compact;
    std::vector<Vehicle*> large;
    std::map<Vehicle*, std::map<VehicleSize,int>> mp;
    
public:
    Level(int spots_per_row, int num_rows){
        motor_cycle.resize(spots_per_row/4);
        compact.resize(spots_per_row*(3/4)-motor_cycle.size());
        large.resize(spots_per_row*(1/4)+1);
    }
    
    //Check which vehicle can be parked
    int spotsAvailable(Vehicle *vehicle, VehicleSize size, int num){
        switch (size) {
            case VehicleSize::Motorcycle:
                for(int i=0; i<motor_cycle.size(); i++){
                    if(!motor_cycle[i]) return i;
                }
                return -1;
            case VehicleSize::Compact:
                for(int i=0; i<compact.size(); i++){
                    if(!compact[i]) return i;
                }
                return -1;
            case VehicleSize::Large:
                for (int i=0; i<large.size(); i++){
                    if (!large[i]){
                        bool flag=true;
                        for (int j=i; j<i+num; j++){
                            if(large[j]) flag=false;
                            break;
                        }
                        if (flag) return i;
                    }
                }
                return -1;
            default:
                break;
        }
        return -1;
    }
    
    void parkVehicle(Vehicle* vehicle, VehicleSize spotType, int i, int num){
        if (spotType==VehicleSize::Motorcycle) motor_cycle[i]=vehicle;
        else if (spotType==VehicleSize::Compact) compact[i]=vehicle;
        else{
            for(int j=i; j<i+num; j++) large[j]=vehicle;
        }
        mp[vehicle][spotType]=i;
    }
    
    void unParkVechicle(Vehicle* vehicle){
        std::map<VehicleSize, int> spot_index_to_vehicle=mp[vehicle];
        VehicleSize size=vehicle->size();
        if (size==VehicleSize::Motorcycle) motor_cycle[spot_index_to_vehicle[size]]=NULL;
        else if (size==VehicleSize::Compact) compact[spot_index_to_vehicle[size]]=NULL;
        else {
            for (int i=spot_index_to_vehicle[size]; i<large.size(); i++){
                if (large[i]==vehicle) large[i]=NULL;
                else break;
            }
        }
    }
};

class ParkingLot {
    std::vector<Level*> level;
    std::map<Vehicle*, Level*> mp;
    bool parkVehicle(Vehicle &vehicle, VehicleSize size , int num){
        for (int i=0; i<level.size(); i++){
            int index=level[i]->spotsAvailable(&vehicle, size, num);
            if (index!=-1){
                level[i]->parkVehicle(&vehicle, size, index, num);
                mp[&vehicle]=level[i];
                return true;
            }
        }
        return false;
    }
//    bool parkMotorcycle(Vehicle &vehicle, int num){
//        for (int i=0; i<level.size(); i++){
//            int index=level[i]->spotsAvailable(&vehicle, VehicleSize::Motorcycle, num);
//            if (index!=-1){
//                level[i]->parkVehicle(&vehicle, VehicleSize::Motorcycle, index, num);
//                mp[&vehicle]=level[i];
//                return true;
//            }
//        }
//        return false;
//    }
//    
//    bool parkCompact(Vehicle &vehicle, int num){
//        for (int i=0; i<level.size(); i++){
//            int index=level[i]->spotsAvailable(&vehicle, VehicleSize::Compact, num);
//            if (index!=1){
//                level[i]->parkVehicle(&vehicle, VehicleSize::Compact, index, num);
//                mp[&vehicle]=level[i];
//                return true;
//            }
//        }
//        return false;
//    }
//    
//    bool parkBus(Vehicle &vehicle, int num){
//        for (int i=0; i<level.size(); i++) {
//            
//        }
//        return false;
//    }
public:
    // @param n number of leves
    // @param num_rows  each level has num_rows rows of spots
    // @param spots_per_row each row has spots_per_row spots
    ParkingLot(int n, int num_rows, int spots_per_row) {
        for (int i=0; i<n; i++){
            level.emplace_back(new Level(spots_per_row, num_rows));
        }
    }
    
    // Park the vehicle in a spot (or multiple spots)
    // Return false if failed
    bool parkVehicle(Vehicle &vehicle) {
        VehicleSize size=vehicle.size();
        int num=(size==VehicleSize::Large)?5:1;
        if(!parkVehicle(vehicle, size, num)) return parkVehicle(vehicle, size, num);
        else return false;
    }
    
    // unPark the vehicle
    void unParkVehicle(Vehicle &vehicle) {
        Level *lv=mp[&vehicle];
        if(lv) lv->unParkVechicle(&vehicle);
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    int n=1;
    int num_rows=1;
    int spots_per_row=11;
    ParkingLot plt(n,num_rows,spots_per_row);
    std::cout<<plt.parkVehicle("motor1");
    return 0;
}
