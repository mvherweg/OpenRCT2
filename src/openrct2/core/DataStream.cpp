//
// Created by mvherweg on 01.08.18.
//

#include "../scenario/Scenario.h"
#include "DataStream.h"

namespace dstream {
    static constexpr const char *MessageTypeNames[] = {
            "event",
            "state",
            "timeseries"
    };

    static constexpr const char *ReporterTypeNames[] = {
            "other",
            "pos",
            "staff"
    };

    static constexpr const char *PayloadTypeNames[] = {
            "purchase"
    };

    std::string msg_location::json() {
        // Example: {"x": 123, "y": 456}
        return R"({"x": )" + std::to_string(x) \
             + R"(, "y": )" + std::to_string(y) \
             + R"(})";
    }


    std::string msg_reporter::typeName() {
        return ReporterTypeNames[type];
    }

    std::string msg_reporter::json() {
        // Example: {"type": "staff", "id": 123, "name": "J. Doe"}
        // TODO: permit empty name and translate to null
        return R"({"type": ")" + typeName() + "\"" \
             + R"(, "id": )" + std::to_string(id) \
             + R"(, "name": ")" + name + "\"" \
             + R"(})";
    }


    std::string msg_meta::messageTypeName() {
        return MessageTypeNames[message_type];
    }

    std::string msg_meta::payloadTypeName() {
        return PayloadTypeNames[payload_type];
    }

    std::string msg_meta::json() {
        // Condensed Example: {"message": "event", "payload": "purchase", "reporter": ..., "location": ..., "ts": 789, "interval": 0, "repeated": false}
        // TODO: permit leaving out interval
        return R"({"message": ")" + messageTypeName() + "\"" \
             + R"(, "payload": ")" + payloadTypeName() +  + "\"" \
             + R"(, "reporter": )" + reporter.json() \
             + R"(, "location": )" + location.json() \
             + R"(, "ts": )" + std::to_string(ts) \
             + R"(, "interval": )" + std::to_string(interval) \
             + R"(, "repeated": )" + std::to_string(repeated) \
             + R"(})";
    }


    std::string msg::json() {
        // Condensed Example: {"meta": ..., "data": ...}
        return R"({"meta": )" + meta.json() + R"(, "data": )" + data + R"(})";
    }
}