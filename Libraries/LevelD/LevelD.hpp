#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <ctime>

/**
 *  \brief Class representing LevelD file in memory
 */
class LevelD {
public:
    /**
     *  \brief Section representing metadata
     */
    struct Metadata {
        std::string author;      // Name of the author (up to 255 symbols)
        std::string description; // Description of level (up to 255 symbols)
        uint64_t    timestamp;   // Timestamp of level creation

        Metadata() : timestamp(0) {}
		Metadata(std::string author, std::string description, uint64_t timestamp) : author(author), description(description), timestamp(timestamp) {}
    };

    /**
     *  \brief Section representing player
     */
    struct Player {
        uint32_t x, y;  // Coordinates on map
        uint16_t flags; // Flags for player
    };

    /**
     *  \brief Section representing level mesh
     */
    struct Mesh {
        uint32_t width;               // Number of tiles on X axis
        uint32_t height;              // Number of tiles on Y axis
        std::vector<uint16_t> tiles;  // Index number of tiles on map
        std::vector<bool>     blocks; // Whether tile on index i is blocking
    };

    Metadata            metadata; // Level has metadata (always there)
    Mesh                mesh;     // Level has mesh (always there)
    std::vector<Player> players;  // Level can have players (only if non-empty)

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