#include "Top.hpp"

void ModuleMetadata::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    bout << LVLD_METADATA_CODE;
    bout << lvld.metadata.timestamp;
    bout << lvld.metadata.author;
    bout << lvld.metadata.description;
}

void ModuleMetadata::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    bin >> lvld.metadata.timestamp;
    bin >> lvld.metadata.author;
    bin >> lvld.metadata.description;
}