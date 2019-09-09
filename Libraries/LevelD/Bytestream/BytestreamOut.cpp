#include "Bytestream.hpp"
#include <fstream>
#include <stdexcept>

const std::size_t ALLOC_CHUNK_SIZE = 1024;

void BytestreamOut::checkBufferSize(std::size_t bytecount) {
    if (pos + bytecount > data.size()) {
        data.resize(data.size() + ALLOC_CHUNK_SIZE);
    }
}

BytestreamOut &BytestreamOut::operator<<(uint8_t num) {
    checkBufferSize(sizeof(num));

    data[pos] = num;
    pos += sizeof(num);

    return *this;
}

BytestreamOut &BytestreamOut::operator<<(uint16_t num) {
    checkBufferSize(sizeof(num));

    *((uint16_t*)(data.data() + pos)) = num;
    pos += sizeof(num);

    return *this;
}

BytestreamOut &BytestreamOut::operator<<(uint32_t num) {
    checkBufferSize(sizeof(num));

    *((uint32_t*)(data.data() + pos)) = num;
    pos += sizeof(num);

    return *this;
}

BytestreamOut &BytestreamOut::operator<<(uint64_t num) {
    checkBufferSize(sizeof(num));

    *((uint64_t*)(data.data() + pos)) = num;
    pos += sizeof(num);

    return *this;
}

BytestreamOut &BytestreamOut::operator<<(const std::string &str) {
    if (str.size() > 255) {
        throw std::runtime_error("Trying to export std::string longer than 255 symbols");
    }

    *this << uint8_t(str.size());

    checkBufferSize(str.size());

    for (unsigned i = 0;  i < str.size(); i++) {
        data[pos++] = str[i];
    }

    return *this;
}

BytestreamOut &BytestreamOut::operator<<(const std::vector<uint16_t> &vec) {
    *this << uint32_t(vec.size());

    checkBufferSize(vec.size() * sizeof(uint16_t));

    uint16_t *vecdata = (uint16_t*)(data.data() + pos);

    for (unsigned i = 0; i < vec.size(); i++) {
        vecdata[i] = vec[i];
    }

    pos += vec.size() * sizeof(uint16_t);

    return *this;
}


void BytestreamOut::close() {
    std::ofstream save(filename, std::ios::binary);

    save.write((char*)data.data(), pos);

    save.close();
    save.clear();
}