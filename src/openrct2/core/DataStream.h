//
// Created by mvherweg on 01.08.18.
//

#ifndef _DATASTREAM_H_
#define _DATASTREAM_H_

#include <string>
#include "../common.h"

enum MSG_MESSAGE_TYPE
{
    MSG_MESSAGE_TYPE_EVENT = 0,
    MSG_MESSAGE_TYPE_STATE = 1,
    MSG_MESSAGE_TYPE_TIMESERIES = 2

};

enum MSG_REPORTER_TYPE
{
    MSG_REPORTER_TYPE_OTHER = 0,  // Anything else
    MSG_REPORTER_TYPE_POS = 1,    // Point-of-sales
    MSG_REPORTER_TYPE_STAFF = 2,  // Park employee
    MSG_REPORTER_TYPE_GUEST = 3   // Guest
};

enum MSG_PAYLOAD_TYPE
{
    MSG_PAYLOAD_TYPE_PURCHASE = 0
};

struct msg_location
{
    sint32 x;
    sint32 y;

public:
    std::string json();
};

struct msg_reporter
{
    MSG_REPORTER_TYPE type;
    uint32 id;
    std::string name;

private:
    std::string typeName();
public:
    std::string json();
};

struct msg_meta
{
    MSG_MESSAGE_TYPE message_type;
    MSG_PAYLOAD_TYPE payload_type;
    std::string park_name;
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

msg_meta createMeta(MSG_MESSAGE_TYPE message_type, MSG_PAYLOAD_TYPE payload_type, msg_reporter reporter, msg_location location, uint32 interval, bool repeated);
msg_meta createEventMeta(MSG_PAYLOAD_TYPE payload_type, msg_reporter reporter, msg_location location, bool repeated);

using msg_data = std::string;

struct msg
{
    msg_meta meta;
    msg_data data;

public:
    std::string json();
    void sendMessage();
};


struct msg_ride_identity
{
    uint16 id;
    std::string type;
    std::string subtype;
    std::string name;

public:
    std::string json();
};

struct msg_peep_identity
{
    uint32 id;
    std:: string name;

public:
    std::string json();
};

struct msg_item_sale
{
    sint32 id;
    std::string name;
    money32 price;
    uint8 quantity;
    money32 reduction;
    bool voucher;

public:
    std::string json();
};

msg_item_sale itemSale(sint32 shopItem, money32 price, uint8 quantity, money32 reduction, bool voucher);

extern uint64 gSaleId;

struct msg_peep_purchase
{
    uint64 id;
    msg_ride_identity pos;
    msg_peep_identity customer;
    msg_item_sale sold;
    uint32 ticks;
public:
    std::string json();
};

#endif
