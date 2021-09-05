#pragma once

#include <cstdint>
#include <string>
#include <vector>

/**
 *  \brief cin-like class for loading data from binary file
 *
 *  \details Whole file is loaded into memory at once with
 *  construction of this class.
 */
class BytestreamIn {
private:
    std::vector<uint8_t> data;
    std::size_t pos;

    void checkStreamSize(std::size_t bytecount);

public:
    bool eof() { return pos == data.size(); }

    BytestreamIn &operator>>(uint8_t &num);
    BytestreamIn &operator>>(uint16_t &num);
    BytestreamIn &operator>>(uint32_t &num);
    BytestreamIn &operator>>(uint64_t &num);
    BytestreamIn &operator>>(std::string &str);
    BytestreamIn &operator>>(std::vector<uint16_t> &vec);

    BytestreamIn(const std::string &filename);
};

/**
 *  \brief cout-like class for storing data in binary file
 *
 *  \details Changes are buffered in memory of the class and
 *  once you've written everything you want, you have to actually
 *  store them to file using \ref close.
 */
class BytestreamOut {
private:
    std::string filename;
    std::vector<uint8_t> data;
    std::size_t pos;

    void updateBufferSize(std::size_t bytecount);

public:
    BytestreamOut &operator<<(uint8_t num);
    BytestreamOut &operator<<(uint16_t num);
    BytestreamOut &operator<<(uint32_t num);
    BytestreamOut &operator<<(uint64_t num);
    BytestreamOut &operator<<(const std::string &str);
    BytestreamOut &operator<<(const std::vector<uint16_t> &vec);

    void close();

    BytestreamOut(const std::string &filename) : filename(filename), data(1024, 0), pos(0) {}
};