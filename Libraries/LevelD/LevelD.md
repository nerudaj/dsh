# LevelD File Format Documentation

This file contains comprehensive documentation of LevelD file format and how is the LevelD C++ structure (de)serialized. This file should be considered as the definitive specification and any implementation of LevelD file reader should conform to this file.

## Table of Contents

 * [Introduction](#introduction)
 * [META block](#meta-block)
 * [MESH block](#mesh-block)
 * [PLAS block](#plas-block)
 * [NPCS block](#npcs-block)
 * [ITEM block](#item-block)

## Introduction

The LevelD file format is an universal storage for game level data. It provides conversion layer between C++ data structure and file on a computer disk. It can store many different kinds of information in a fairly effective manner.

The LevelD file format (.lvd for short) is build around the idea of modules or blocks of data that can be provided independently on each other. LevelD structure is meant to be serialized as a binary file, as effectively as possible.

### Endianess

Every number is stored in **big-endian** format.

### File structure

Every .lvd file consists of a simple header and a number of blocks. While header is fixed, blocks are not ordered in any way and parser should not make any assumptions about their order. For exporters, it is _recommended_ to export metadata block first.

### File <-> Software mapping

Each attribute of LevelD object is directly mapped to one block in .lvd file. List of supported blocks and their contents is dependent on used version of LevelD exporter.

 > **NOTE:** If a particular attribute of LevelD object is not initialized, it is recommended for exporters to not write it to output file for efficiency reasons.

Available blocks:

 * metadata
 * mesh (changed in version 2)
 * players
 * npcs
 * items

### Versioning

Each change to LevelD file format will bump the version number by 1. Every parser **must** be able to parse files with lower versions and **must** throw exception when version number is higher.

### Blocks

Every block starts with 4B string identifier. When parsing, one can first read these four bytes, then decide which block parser to use and then apply it to parse the given block.

### Strings

When this specification states something is stored as a string, that this is stored first as a 1B number stating how many characters that string has (string cannot be longer than 255 characters, ignoring null terminating character) and then that many characters follow.

### Vectors

When this specification states something is stored as a vector of XB numbers, it means first there are 4B of data specifiying *length* of the vector and then X * *length* bytes of data containing the desired vector.

## File header

| Width (bytes) | Usage   | Note |
| :-----------: | :----   | :--- |
| 2             | Version | Interpret as unsigned 2B integer |

## META block

This block represents metadata of the level. It has following structure:

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 4             | Block ID    | ID of this block. Value is fixed to 'META' |
| 8             | timestamp | User defined |
| string        | id    | ID of the level |
| string        | name  | Name of the level |
| string        | author | Author of the level |
| string        | description | Brief description of the level |

## MESH block

Mesh block represents the level mesh - how it looks and where the collisions are. This block only supports tile based maps with only simple (on/off) collisions:

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 4             | Block ID    | ID of this block. Value is fixed to 'MESH' |
| 2             | tileWidth | Width of tile in pixels (since version 2) |
| 2             | tileHeight | Height of tile in pixels (since version 2) |
| 4             | width | Width of map |
| vector        | data | Data for all tiles |

Each cell in `data` vector represents single tile. Tile with coordinates [x, y] lies in the cell with index `x * width + y`. Every cell represents two information - if the block is impassable (single top bit of the value, `true` if impassable) and id of the tile (bottom 15 bits). LevelD object has these two stored in separate vectors: `blocks` (collision data) and `tiles` (ids). Height of the map is compute as size of `data` divided by `width`.

## PLAS block

Players block is for storing spawn positions of players in level:

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 4             | Block ID    | ID of this block. Value is fixed to 'PLAS' |
| 4             | count | Total number of players |

Following sub-block follows `count` number of times.

| Width (bytes) | Usage | Note |
| 4             | id | Id of the player |
| 4             | x  | X coordinate of player spawn |
| 4             | y  | Y coordinate of player spawn |
| 2             | flags  | Flags given to player spawn |

## NPCS block

NPCs block is for storing spawn positions of non-players in level.

Parsing is identical to parsing of PLAS block, just the Block ID is set to 'NPCS'.

## ITEM block

Item block is for storing spawn positions of items in level.

Parsing is identical to parsing of PLAS and NPCS block, just the Block ID is set to 'ITEM'.