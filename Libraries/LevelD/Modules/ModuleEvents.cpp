#include "Top.hpp"
#include <cmath>

uint8_t writeCastCodeToTopBitsOfNumber(uint8_t castCode, uint8_t number) {
    return number & uint8_t((castCode & 0x3) << 6);
}

uint8_t getCastCodeOfArgArray(const std::vector<uint32_t> &array) {
    uint8_t result = 0; // 8bits

    for (auto &arg : array) {
        if (arg > 255) result = 1; // We need at least 16 bits
        else if (arg > 65535) result = 2; // We need at least 32 bits
    }

    return result;
}

void checkEventArgSize(LevelD::Event &event) {
    if (event.arguments.size() >= 64) {
        throw std::runtime_error("Argument array of event is too big (Max is 63 elements)!");
    }
}

void serializeArgsToBstreamUsingCastCode(const std::vector<uint32_t> &args, BytestreamOut &bout, uint8_t castCode) {
    for (auto &arg : args) {
        if (castCode == 0) bout << uint8_t(arg);
        else if (castCode == 1) bout << uint16_t(arg);
        else if (castCode == 2) bout << uint32_t(arg);
    }
}

void ModuleEvents::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    bout << uint32_t(lvld.events.size());

    for (auto &event : lvld.events) {
        bout << event.id;

        if (event.arguments.empty()) bout << uint8_t(0);
        else {
            checkEventArgSize(event);

            uint8_t castCode = getCastCodeOfArgArray(event.arguments);
            bout << writeCastCodeToTopBitsOfNumber(castCode, uint8_t(event.arguments.size()));

            serializeArgsToBstreamUsingCastCode(event.arguments, bout, castCode);
        }
    }
}

void ModuleEvents::deserialize(BytestreamIn &bin, LevelD &lvld) const {

}