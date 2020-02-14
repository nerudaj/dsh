#include <climits>

template <typename T>
T swapEndian(T u) {
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

static bool isBigEndian() {
    uint32_t num = 0x000000FF;
    return (((uint8_t*)(&num))[3]) == 0xFF;
}

static uint16_t sanitize(uint16_t num) {
    if (!isBigEndian()) {
        return swapEndian<uint16_t>(num);
    }
    return num;
}

static uint32_t sanitize(uint32_t num) {
    if (!isBigEndian()) {
        return swapEndian<uint32_t>(num);
    }
    return num;
}

static uint64_t sanitize(uint64_t num) {
    if (!isBigEndian()) {
        return swapEndian<uint64_t>(num);
    }
    return num;
}