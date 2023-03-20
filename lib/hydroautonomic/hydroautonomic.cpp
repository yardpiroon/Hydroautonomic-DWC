#include "hydroautonomic.h"
#include "plant.h"

AutomaticGrowing::AutomaticGrowing(){
    // dummy pin
    pin_monitor_water_level = 10;
    pin_control_water_pupmIN = 11;
    pin_control_water_pupmOut = 8;
    pin_control_air_pupm = 9;

}

void AutomaticGrowing::setup(){

    pinMode(pin_monitor_water_level,    INPUT);

    pinMode(pin_control_air_pupm,       OUTPUT);
    pinMode(pin_control_water_pupmIN,     OUTPUT);
    pinMode(pin_control_water_pupmOut,     OUTPUT);

}

void AutomaticGrowing::loop(){
    water_level_monitor = digitalRead(pin_monitor_water_level);
    auto_adjust_water_level();
    increase_DO(add_DO_minius_day);
}

void AutomaticGrowing::bucket_init(int width , int length  , int height ){
    
    bucket_height = height;
    bucket_length = length;
    bucket_width = width;
    bucket_volume = width * length * height;
}

void AutomaticGrowing::plant_init(int numberofPlant ){
    
    plant_number = numberofPlant;
}


float AutomaticGrowing::get_water_level(int distaneFromSensorInCM){
    actual_water_level  = bucket_height - distaneFromSensorInCM;
    return actual_water_level;
}


void AutomaticGrowing::increase_water_level(int desired_water_level){
    if(actual_water_level < desired_water_level){

        digitalWrite(pin_control_water_pupmIN,HIGH);
    }else{

        digitalWrite(pin_control_water_pupmIN,LOW);
    }
}

void AutomaticGrowing::decrease_water_level(int desired_water_level){
    if(actual_water_level > desired_water_level){

        digitalWrite(pin_control_water_pupmIN,HIGH);
    }else{

        digitalWrite(pin_control_water_pupmIN,LOW);
    }
}

void AutomaticGrowing::auto_adjust_water_level(){
    if(water_pump_in){
        increase_water_level(30);}
    else if (water_pump_out)
    {       
        decrease_water_level(30);}
    else{
        digitalWrite(pin_control_water_pupmIN,LOW);
        digitalWrite(pin_control_water_pupmOut,LOW);
    } 
}


void AutomaticGrowing::increase_DO(int timeInMinutes){
    air_pump_time = timeInMinutes*60000;
    if(millis() - last_air_pump_millis > air_pump_time){
        if(air_pump){
            digitalWrite(pin_control_air_pupm,HIGH);
            last_air_pump_millis = millis();}
        else{
            digitalWrite(pin_control_air_pupm,LOW);
        }
    }
}




