#include "Bytestream.hpp"
#include "SwapEndian.hpp"
#include <fstream>
#include <stdexcept>

void BytestreamIn::checkStreamSize(std::size_t bytecount) {
    if (data.size() < pos + bytecount) {
        throw std::runtime_error("File corrupted");
    }
}

BytestreamIn &BytestreamIn::operator>>(uint8_t &num) {
    checkStreamSize(sizeof(num));

    num = data[pos];
    pos++;

    return *this;
}

BytestreamIn &BytestreamIn::operator>>(uint16_t &num) {
    checkStreamSize(sizeof(num));

    num = sanitize(*((uint16_t*)(data.data() + pos)));
    pos += sizeof(num);

    return *this;
}

BytestreamIn &BytestreamIn::operator>>(uint32_t &num) {
    checkStreamSize(sizeof(num));

    num = sanitize(*((uint32_t*)(data.data() + pos)));
    pos += sizeof(num);

    return *this;
}

BytestreamIn &BytestreamIn::operator>>(uint64_t &num) {
    checkStreamSize(sizeof(num));

    num = sanitize(*((uint64_t*)(data.data() + pos)));
    pos += sizeof(num);

    return *this;
}

BytestreamIn &BytestreamIn::operator>>(std::string &str) {
    uint8_t strsize;
    *this >> strsize;

    checkStreamSize(strsize);

    str = std::string(data.begin() + pos, data.begin() + pos + strsize);
    pos += strsize;

    return *this;
}

BytestreamIn &BytestreamIn::operator>>(std::vector<uint16_t> &vec) {
    uint32_t vecsize;
    *this >> vecsize;

    checkStreamSize(vecsize * sizeof(uint16_t));

    uint16_t *vecdata = (uint16_t*)(data.data() + pos);

    vec.resize(vecsize);
    for (unsigned i = 0; i < vecsize; i++) vec[i] = sanitize(vecdata[i]);
    pos += sizeof(uint16_t) * vecsize;

    return *this;
}

BytestreamIn::BytestreamIn(const std::string &filename) {
    std::ifstream load(filename, std::ios::binary);

    load.seekg(0, load.end);
    unsigned size = load.tellg();
    load.seekg(0, load.beg);

    data.resize(size, 0);
    load.read((char*)data.data(), data.size());

    pos = 0;

    load.clear();
    load.close();
}