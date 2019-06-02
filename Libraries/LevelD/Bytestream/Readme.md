# Bytestream

BytestreamIn and BytestreamOut are simple cin/cout-like classes that allow to read/write supported data types from/to binary file.

## Supported data types

 * uint8_t
 * uint16_t
 * uint32_t
 * uint64_t
 * std::string - Only supports strings up to 255 characters
 * std::vector<uint16_t>

## Tests

You can run tests by building and running the testrunner binary:

```
mkdir build && cd build
cmake ..
make
./testrunner
```