//
// Created by mvherweg on 01.08.18.
//

#include "../common.h"
#include "../localisation/Localisation.h"
#include "../ride/ShopItem.h"
#include "../scenario/Scenario.h"
#include "../world/Park.h"
#include "DataStream.h"


static constexpr const char *MessageTypeNames[] = {
        "event",
        "state",
        "timeseries"
};

static constexpr const char *ReporterTypeNames[] = {
        "other",
        "pos",
        "staff",
        "guest"
};

static constexpr const char *PayloadTypeNames[] = {
        "purchase"
};

uint64 gSaleId = 0;

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
    // TODO: permit leaving out interval?
    // TODO: repeated is turned into 0 when cast to string
    return R"({"message": ")" + messageTypeName() + "\"" \
         + R"(, "payload": ")" + payloadTypeName() + "\"" \
         + R"(, "site": ")" + park_name + "\"" \
         + R"(, "reporter": )" + reporter.json() \
         + R"(, "location": )" + location.json() \
         + R"(, "ts": )" + std::to_string(ts) \
         + R"(, "interval": )" + std::to_string(interval) \
         + R"(, "repeated": )" + std::to_string(repeated) \
         + R"(})";
}

msg_meta createMeta(MSG_MESSAGE_TYPE message_type, MSG_PAYLOAD_TYPE payload_type, msg_reporter reporter, msg_location location, uint32 interval, bool repeated) {
    utf8 park_name[128];
    format_string(park_name, 128, gParkName, &gParkNameArgs);

    return { message_type, payload_type, park_name, reporter, location, gScenarioTicks, interval, repeated };
}

msg_meta createEventMeta(MSG_PAYLOAD_TYPE payload_type, msg_reporter reporter, msg_location location, bool repeated) {
    return createMeta(MSG_MESSAGE_TYPE_EVENT, payload_type, reporter, location, 0, repeated);
}

std::string msg::json() {
    // Condensed Example: {"meta": ..., "data": ...}
    return R"({"meta": )" + meta.json() \
         + R"(, "data": )" + data \
         + R"(})";
}

void msg::sendMessage() {
    std::cout << json() << std::endl;
}


std::string msg_ride_identity::json() {
    // Example: {"id": 123, "type": "abc", "subtype": "def", "name": "Ghi"}
    return R"({"id": )" + std::to_string(id) \
         + R"(, "subtype": ")" + category +"\"" \
         + R"(, "name": ")" + name + "\"" \
         + R"(})";
}

std::string msg_peep_identity::json() {
    // Example: {"id": 123, "name": "Abc D."}
    return R"({"id": )" + std::to_string(id) + R"(, "name": ")" + name + R"("})";
}

std::string msg_item_sale::json() {
    // Example: {"id": 123, "name": "abc", "price": 10, "quantity": 1, "reduction": 0, "voucher": false}
    // TODO: voucher is turned into 0 when cast to string
    return R"({"id": )" + std::to_string(id) \
         + R"(, "name": ")" + name \
         + R"(", "price": )" + std::to_string(price) \
         + R"(, "quantity": )" + std::to_string(quantity) \
         + R"(, "reduction": )" + std::to_string(reduction) \
         + R"(, "voucher": )" + std::to_string(voucher) \
         + R"(})";
}

msg_item_sale itemSale(sint32 shopItem, money32 price, uint8 quantity, money32 reduction, bool voucher)
{
    char name[128];
    format_string(name, 128, ShopItemStringIds[shopItem].singular, nullptr);
    return { shopItem, name, price, quantity, reduction, voucher };
}

std::string msg_peep_purchase::json() {
    // Condensed Example: {"pos": ..., "customer": ..., "sale": ..., "tst": 123}
    return R"({"id": )" + std::to_string(gSaleId) \
         + R"(, "pos": )" + pos.json() \
         + R"(, "customer": )" + customer.json() \
         + R"(, "sold": )" + sold.json() \
         + R"(, "ts": )" + std::to_string(ticks) \
         + R"(})";
}