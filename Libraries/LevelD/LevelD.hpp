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
        std::string id;          // Id of the level
        std::string name;        // Name of the level
        std::string author;      // Name of the author (up to 255 symbols)
        std::string description; // Description of level (up to 255 symbols)
        uint64_t    timestamp;   // Timestamp of level creation

        Metadata() : timestamp(0) {}
        Metadata(std::string id, std::string name, std::string author, std::string description, uint64_t timestamp) : id(id), name(name), author(author), description(description), timestamp(timestamp) {}
    };

    /**
     *  \brief Section representing level mesh
     */
    struct Mesh {
        uint32_t width;               // Number of tiles on X axis
        uint32_t height;              // Number of tiles on Y axis
        std::vector<uint16_t> tiles;  // Index number of tiles on map
        std::vector<bool>     blocks; // Whether tile on index i is blocking

        bool empty() const { return width == 0 || height == 0; }

        Mesh() : width(0), height(0) {}
        Mesh(uint32_t width, uint32_t height, const std::vector<uint16_t> &tiles, const std::vector<bool> &blocks) : width(width), height(height), tiles(tiles), blocks(blocks) {}
    };

    /**
     *  \brief Section representing actor - anything with coordinates and flags
     */
    struct Actor {
        uint32_t id;    // Identifier of actor
        uint32_t x, y;  // Coordinates on map
        uint16_t flags; // Behavioral flags for actor
    };
    typedef std::vector<Actor> Players;
    typedef std::vector<Actor> Items;
    typedef std::vector<Actor> Npcs;

    struct Event {
        uint32_t id;                     // Identifier of event
        std::vector<uint32_t> arguments; // Optional arguments of event
    };
    typedef std::vector<Event> Events;

    Metadata  metadata; // Level has metadata (always there)
    Mesh      mesh;     // Level can have mesh (only if non-empty)
    Players   players;  // Level can have players (only if non-empty)
    Items     items;    // Level can have items (only if non-empty)
    Npcs      npcs;     // Level can have NPCs
    /*Events    events;*/

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

    LevelD() {}
    LevelD(const LevelD::Metadata &meta, const LevelD::Mesh &mesh, const Players &players, const Items &items, const Npcs &npcs) : metadata(meta), mesh(mesh), players(players), items(items), npcs(npcs) {}
};