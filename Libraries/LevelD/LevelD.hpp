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
        Metadata(std::string id, std::string name, std::string author, std::string description, uint64_t timestamp)
			: id(id), name(name), author(author), description(description), timestamp(timestamp) {}
    };

	/**
	 *  \brief Tiled layer. Each tile is either blocking or non-blocking
	 *
	 *  Dimensions are defined in mesh
	 */
	struct TileLayer {
		std::vector<uint16_t>  tiles;  // Index number of tiles on map
		std::vector<bool>      blocks; // Whether tile on index i is blocking

        bool empty() const { return tiles.empty() && blocks.empty(); }

		TileLayer() {}
		TileLayer(const std::vector<uint16_t> &tiles, const std::vector<bool> &blocks)
			: tiles(tiles), blocks(blocks) {}
	};

    /**
     *  \brief Section representing level mesh, consisting from several layers of tilesets
     */
    struct Mesh {
        uint16_t tileWidth; // Width of tile
        uint16_t tileHeight; // Height of tile
		uint32_t layerWidth; // Numbe of tiles on a row
		uint32_t layerHeight; // Number of tiles in a column
		std::vector<TileLayer> layers;

		bool empty() const {
			return layers.empty() && tileWidth == 0 && tileHeight == 0 && layerWidth == 0 && layerHeight == 0;
		}

        Mesh() : tileWidth(0), tileHeight(0), layerWidth(0), layerHeight(0) {}
        Mesh(uint16_t tileWidth, uint16_t tileHeight, uint32_t layerWidth, uint32_t layerHeight, const std::vector<TileLayer> &layers)
			: tileWidth(tileWidth), tileHeight(tileHeight), layerWidth(layerWidth), layerHeight(layerHeight), layers(layers) {}
    };

    /**
     *  \brief Things - items, spawns, ...
     */
    struct Thing {
        uint32_t id;    // Identifier of actor
		uint32_t tag;   // Numerical tag reference
        uint32_t x, y;  // Coordinates on map
        uint16_t flags; // Behavioral flags for actor
		std::string metadata; // Text metadata
    };
    typedef std::vector<Thing> Things;

	/**
	 *  \brief Structure for marking areas (rectangular or circular) which
	 *  can trigger various events.
	 */
    struct Trigger {
		enum class AreaType : uint8_t {
			Rectangle = 0, Circle
		};

		uint32_t x, y; // Coordinates of origin
		AreaType areaType;
		uint16_t radius; // Only used for Circle
		uint16_t width, height; // Only used for rectangle

        uint32_t id; // Can be used to identify action to execute
		uint32_t tag; // Can be used to identify this particular object
		uint16_t type; // Can be used to enumerate kind of trigger (interact, walk-into, ...)
        uint32_t a1, a2, a3, a4, a5; // Can be used as arguments for executed action
		std::string metadata; // Text metadata;

		Trigger() : x(0), y(0), areaType(AreaType::Rectangle),
			radius(0), width(0), height(0), id(0),
			tag(0), type(0), a1(0), a2(0), a3(0), a4(0), a5(0),
			metadata("") {}
    };
    typedef std::vector<Trigger> Triggers;

    Metadata metadata; // Level has metadata (always there)
    Mesh mesh; // Level can have mesh (only if non-empty)
    Things things; // Item placement
    Triggers triggers; // Event trigger placement
	// TODO: Paths

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
    LevelD(const LevelD::Metadata &meta, const LevelD::Mesh &mesh, const Things &things)
		: metadata(meta), mesh(mesh), things(things) {}
};