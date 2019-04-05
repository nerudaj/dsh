#pragma once

#include <string>
#include <cstdint>
#include <vector>

/**
 *  \brief Class representing LevelD file in memory
 */
class LevelD {
public:
    #pragma pack(push, 2)
    struct Player {
        uint32_t x;
        uint32_t y;
        uint16_t flags;
    };
    #pragma pack(pop)

    struct {
        uint32_t              width;      ///< Number of tiles on X axis
        uint32_t              height;     ///< Number of tiles on Y axis
        std::vector<uint16_t> tiles;      ///< Indices of tiles. tiles.size() == width * height
        std::vector<bool>     blocks;     ///< Whether tile at tiles[i] is blocking or not
    } mesh; ///< Environment of the level

    std::vector<Player> players;

    /**
     *  \brief Clear contents of the object
     *
     *  \details Use this method to get the object
     *  back to consistent state after failed \ref loadFromFile
     */
    void clear();

    /**
     *  \brief Load object from file
     *
     *  \param [in] filename Name of file to load
     *
     *  \details This function attempts to open the file
     *  \p filename and interpret binary data as LevelD
     *  structure, filling attributes in this class during
     *  the process.
     *  This might throw an exception at which case contents
     *  of this object will be in inconsistent state.
     */
    void loadFromFile(const std::string &filename);

    /**
     *  \brief Save object to file
     *
     *  \param [in] filename Name of file to save to
     *
     *  \details All non-empty attributes of this object
     *  will be stored in file. Exception might be thrown 
     *  during the process.
     */
    void saveToFile(const std::string &filename) const;
};