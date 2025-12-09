#ifndef __RTCC_H__
#define __RTCC_H__

    void Read_RTCC_DateTime(void);
    
    void set_alarm_time (int value);
    void set_alarm_to_particular_time (uint32_t alarm_time);
    void set_time (uint32_t new_time);
    void set_date (uint32_t new_date);

#endif