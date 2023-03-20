#ifndef hydroautonomic_h
#define hydroautonomic_h

#include "Arduino.h"



class AutomaticGrowing{

    public:
        AutomaticGrowing();
        void setup();
        void loop();
        void bucket_init(int width , int length  , int height );
        void plant_init(int num );
        float get_water_level( int distaneFromSensorInCM);
        void check_water_statue(int day);
        void increase_DO(int timeInMinutes);
        void auto_adjust_water_level();
        void increase_water_level(int desired_water_level);
        void decrease_water_level(int desired_water_level);
        void tracking_grow_interval();

        // for mqtt flage
        bool air_pump = false;
        bool water_pump_in = false;
        bool water_pump_out = false;

        float water_level_monitor ;
        float absorption_rate_day ;

        int plant_number;

        unsigned long last_water_pump_millis = 0;
        unsigned long last_air_pump_millis = 0;
        unsigned long air_pump_time;
        
    private:
        float actual_water_level;
        int max_water_volume;
        int bucket_volume;
        int bucket_height;
        int bucket_width;
        int bucket_length;

        uint32_t pin_monitor_water_level;
        uint32_t pin_control_water_pupmIN;
        uint32_t pin_control_water_pupmOut;
        uint32_t pin_control_air_pupm;

};

#endif