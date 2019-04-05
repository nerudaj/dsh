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
    level.players = {
        {10, 20, 0}, {20, 30, 10}
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

    log.info("Main", "mesh.tiles comparison done");

    if (level.mesh.blocks.size() == in.mesh.blocks.size()) {
        for (unsigned i = 0; i < level.mesh.blocks.size(); i++) {
            if (level.mesh.blocks[i] != in.mesh.blocks[i]) {
                log.error("Main", "mesh.blocks[" + std::to_string(i) + "] mismatch!");
                log.debug("Main", "ref: " + std::to_string(level.mesh.blocks[i]) + ", out: " + std::to_string(in.mesh.blocks[i]));
            }
        }
    }
    else {
        log.error("Main", "mesh.blocks.size mismatch!");
    }

    log.info("Main", "mesh.blocks comparison done");

    if (level.players.size() == in.players.size()) {
        for (unsigned i = 0; i < level.players.size(); i++) {
            if (level.players[i].x != in.players[i].x) {
                log.error("Main", "players[" + std::to_string(i) + "].x mismatch!");
                log.debug("Main", "ref: " + std::to_string(level.players[i].x) + ", out: " + std::to_string(in.players[i].x));
            }
            if (level.players[i].y != in.players[i].y) {
                log.error("Main", "players[" + std::to_string(i) + "].y mismatch!");
                log.debug("Main", "ref: " + std::to_string(level.players[i].y) + ", out: " + std::to_string(in.players[i].y));
            }
            if (level.players[i].flags != in.players[i].flags) {
                log.error("Main", "players[" + std::to_string(i) + "].flags mismatch!");
                log.debug("Main", "ref: " + std::to_string(level.players[i].flags) + ", out: " + std::to_string(in.players[i].flags));
            }
        }
    }
    else {
        log.error("Main", "players.size mismatch!");
        log.debug("Main", "ref: " + std::to_string(level.players.size()) + ", out: " + std::to_string(in.players.size()));
    }

    log.info("Main", "players comparison done");
}