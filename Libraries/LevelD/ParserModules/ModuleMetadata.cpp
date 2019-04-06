#include "Top.hpp"

void ParserModuleMetadata::parse(const std::vector<uint8_t> &data, LevelD &leveld) const {

}

std::vector<uint8_t> ParserModuleMetadata::deparse(const LevelD &leveld) const {
    unsigned aggregateSize = leveld.meta.author.size() + leveld.meta.description.size();

    std::vector<uint8_t> result (4 + 4 + 2 + aggregateSize + sizeof(uint64_t));

    uint32_t *header = (uint32_t*)result.data();
    uint8_t  *data   = result.data() + 4 + 4 + sizeof(uint64_t);

    header[0] = *((uint32_t*)(std::string("META").data()));
    header[1] = result.size() - 8; // Identity and size is not part of this field
    ((uint64_t*)result.data())[1] = leveld.meta.timestamp;

    // TODO: author and description

    return result;
}