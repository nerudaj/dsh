#include "LevelD.hpp"
#include <Logger.hpp>
#include <Config.hpp>

int main(int argc, char *argv[]) {
    Logger log(1);

    cfg::Args args("v:");
    if (!args.parse(argc, argv)) {
        log.error("Main", "Argument parsing error!");
        return 1;
    }

    if (args.isSet('v')) {
        log.setLoggingLevel(args.getArgumentValue('v').asInt());
    }

    log.debug("Main", "Starting...");
    
    LevelD level;
    level.mesh = {
        3, 2, { 0, 1, 2, 3, 4, 5 }, { 0, 0, 1, 1, 0, 0 }
    };

    log.debug("Main", "LevelD object created");

    level.saveToFile("map.lvd");
    log.info("Main", "Level was exported");

    LevelD in;
    in.loadFromFile("map.lvd");
    log.info("Main", "Level was loaded");

    if (level.mesh.width != in.mesh.width) {
        log.error("Main", "mesh.width mismatch!");
    }
    if (level.mesh.height != in.mesh.height) {
        log.error("Main", "mesh.height mismatch!");
    }

    log.info("Main", "Dimension check pass");
    
    if (level.mesh.tiles.size() == in.mesh.tiles.size()) {
        for (unsigned i = 0; i < level.mesh.tiles.size(); i++) {
            if (level.mesh.tiles[i] != in.mesh.tiles[i]) {
                log.error("Main", "mesh.tiles[" + std::to_string(i) + "] mismatch!");
                log.debug("Main", "ref: " + std::to_string(level.mesh.tiles[i]) + ", out: " + std::to_string(in.mesh.tiles[i]));
            }
        }
    }
    else {
        log.error("Main", "mesh.tiles.size mismatch!");
    }

    if (level.mesh.collisions.size() == in.mesh.collisions.size()) {
        for (unsigned i = 0; i < level.mesh.collisions.size(); i++) {
            if (level.mesh.collisions[i] != in.mesh.collisions[i]) {
                log.error("Main", "mesh.collisions[" + std::to_string(i) + "] mismatch!");
                log.debug("Main", "ref: " + std::to_string(level.mesh.collisions[i]) + ", out: " + std::to_string(in.mesh.collisions[i]));
            }
        }
    }
    else {
        log.error("Main", "mesh.collisions.size mismatch!");
    }
}