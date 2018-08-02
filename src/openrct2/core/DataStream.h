//
// Created by mvherweg on 01.08.18.
//

#ifndef OPENRCT2_DATASTREAM_H
#define OPENRCT2_DATASTREAM_H

#include <string>
#include "../common.h"

namespace dstream {
    enum MESSAGE_TYPE
    {
        MESSAGE_TYPE_EVENT = 0,
        MESSAGE_TYPE_STATE = 1,
        MESSAGE_TYPE_TIMESERIES = 2

    };

    enum REPORTER_TYPE
    {
        REPORTER_TYPE_OTHER = 0,  // Anything else
        REPORTER_TYPE_POS = 1,    // Point-of-sales
        REPORTER_TYPE_STAFF = 2   // Park employee
    };

    enum PAYLOAD_TYPE
    {
        PAYLOAD_TYPE_PURCHASE = 0
    };

    struct msg_location
    {
        uint16 x;
        uint16 y;

    public:
        std::string json();
    };

    struct msg_reporter
    {
        REPORTER_TYPE type;
        uint32 id;
        std::string name;

    private:
        std::string typeName();
    public:
        std::string json();
    };

    struct msg_meta
    {
        MESSAGE_TYPE message_type;
        PAYLOAD_TYPE payload_type;
        msg_reporter reporter;
        msg_location location;
        uint32 ts;
        uint32 interval;
        bool repeated;

    private:
        std::string messageTypeName();
        std::string payloadTypeName();
    public:
        std::string json();
    };

    using msg_data = std::string;

    struct msg
    {
        msg_meta meta;
        msg_data data;

    public:
        std::string json();
    };
}
#endif //OPENRCT2_DATASTREAM_H
