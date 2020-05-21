/**
 * @file CurrentTimeService.h
 * @author Christoph Honal
 * @author Takehisa Oneta
 * @brief Defines the CurrentTime BLE service and helpers
 * @version 0.1
 * @date 2020-05-21
 * 
 * Thanks to https://os.mbed.com/users/ohneta/code/BLE_CurrentTimeService/
 */

#ifndef CURRENT_TIME_SERVICE_H
#define CURRENT_TIME_SERVICE_H

#define BLE_FEATURE_GATT_SERVER 1
#define BLE_ROLE_BROADCASTER 1

#include <mbed.h>
#include <events/mbed_events.h>
#include <time.h>
#include "ble/BLE.h"

#define BLE_CURRENT_TIME_CHAR_VALUE_SIZE 10

/**
 * @brief Provides symbols for the weekdays
 * 
 */
typedef struct
{
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hours;
    uint8_t  minutes;
    uint8_t  seconds;
} BLE_DateTime;

/**
 * @brief Provides a BLE service to track and set the current time and RTC.
 * 
 */
class CurrentTimeService 
{
    
    public:
        /**
         * @brief Construct a new Current Time Service object
         * 
         * @param _ble BLE instance
         * @param event_queue Event queue for dispatching calls from interrupt
         */
        CurrentTimeService(BLE &_ble, events::EventQueue &event_queue);

        /**
         * @brief Sets the internal time using a date-time-stamp
         * 
         * @param dateTime The date-time-stamp
         * @param writeRtc Whether to update the RTC
         */
        void writeDateTime(const BLE_DateTime &dateTime, const bool writeRtc = false);

        /**
         * @brief Sets the internal time using a UNIX timestamp
         * 
         * @param epochTime The UNIX timestamp
         * @param writeRtc Whether to update the RTC
         */
        void writeEpoch(const time_t &epochTime, const bool writeRtc = false);

        /**
         * @brief Return the internal time as a date-time-stamp
         * 
         * @param dateTime The date-time-stamp
         */
        void readDateTime(BLE_DateTime &dateTime);

        /**
         * @brief Return the internal time as a UNIX time stamp
         * 
         * @param epochTime The UNIX timestamp
         */
        void readEpoch(time_t &epochTime);
    
    protected:
        BLE &_ble; //!< Reference to the BLE instance
        events::EventQueue &_event_queue; //!< Reference to the event queue for dispatching
        uint8_t _valueBytes[BLE_CURRENT_TIME_CHAR_VALUE_SIZE]; //!< Buffer for the internal time
        GattCharacteristic _currentTimeCharacteristic; //!< BLE characteristic definition
        Ticker _ticker; //!< Monotonic timer for ticking

        /**
         * @brief Writes the contents of the internal buffer to the BLE GATT server
         * 
         * @param writeRtc Whether to update the RTC
         */
        void writeBuffer(const bool writeRtc = false);

        /**
         * @brief Handles the ticking event of the monotonic timer
         * 
         */
        void onTickerCallback(void);

        /**
         * @brief Handles incoming data update requests from the GATT client
         * 
         * @param params The new timestamp to store
         */
        virtual void onDataWritten(const GattWriteCallbackParams *params);
        
};
 
#endif
 