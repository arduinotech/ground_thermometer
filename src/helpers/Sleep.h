#ifndef GROUND_THERMOMETER_SLEEP_H
#define GROUND_THERMOMETER_SLEEP_H


class Sleep
{
    public:
        static Sleep *getInstance();
        bool isWakeUpByInterrupt();
        void setWakeUpByInterrupt(bool value);


    protected:
        Sleep();

    private:
        static Sleep *_instance;
        bool _wakeUpByInterrupt = false;
};


#endif //GROUND_THERMOMETER_SLEEP_H
