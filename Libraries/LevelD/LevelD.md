# LevelD File Format Documentation

This file contains comprehensive documentation of LevelD file format and how is the LevelD C++ structure (de)serialized. This file should be considered as the definitive specification and any implementation of LevelD file reader should conform to this file.

## Table of Contents

 * [Introduction](#introduction)
 * [META block](#meta-block)
 * [MESH block](#mesh-block)
 * [THNG block](#thng-block)
 * [TRIG block](#trig-block)
 * [PATH block](#path-block)

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

## Semantics

Semantics of individual fields are not set in stone, but their supposed usage is reflected by the comments and as such is implemented in LevelD Editor. The semantics also somehow match the way Doom Builder editor does things with Doom levels. Couple examples:

* id - this supposed to identify particular type of thing (like enemy Imp) or action to execute in triggers (like Open Door)
* tag - this is supposed to tie together entities (for example if action says Kill Enemy, it will have the same tag as thing that is supposed to die)
* flags - modify default behaviour of a given entity
* metadata - way to label entity or can be used to add additional flags or scripts

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

## THNG block

This block replaced Players/Npcs/Items block from previous versions and added more properties.

This block is supposed to store spawns for all physical entities in the level. See Triggers block if you need to represent general purpose areas supposed to invoke functions in certain events.

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 4             | Block ID    | ID of this block. Value is fixed to 'THNG' |
| 4             | count | Total number of things |

Following sub-block follows `count` number of times.

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 4             | id | Id of the thing (identifies general type, like "player spawn") |
| 4             | tag | Tag used to identify groups of things, regardless of id |
| 4             | x  | X coordinate of thing spawn |
| 4             | y  | Y coordinate of thing spawn |
| 2             | flags  | Flags given to thing |
| string		| metadata | General purpose |

## TRIG block

Used to store general purpose areas (rectangular/circular) that are supposed to invoke callback when triggered.

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 4             | Block ID    | ID of this block. Value is fixed to 'THNG' |
| 4             | count | Total number of triggers |

Following sub-block follows `count` number of times.

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 4             | x  | X coordinate of thing spawn |
| 4             | y  | Y coordinate of thing spawn |
| 2             | type  | 0 - Rectangle, 1 - Circle |
| 2				| width | Only present if type is 0 |
| 2				| height | Only present if type is 0 |
| 2				| radius | Only present if type is 1 |
| 4             | id | Id of the thing (identifies callback function) |
| 4             | tag | Tag used to identify groups of triggers, regardless of id |
| 2				| type | Used to enumerate how the trigger is triggered |
| 4             | a1 | First argument for callback |
| 4             | a2 | Second argument for callback |
| 4             | a3 | Third argument for callback |
| 4             | a4 | Fourth argument for callback |
| 4             | a5 | Fifth argument for callback |
| string		| metadata | General purpose |

## PATH block

Used to store navigation information for NPCs.

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 4             | Block ID | ID of this block. Value is fixed to 'PATH' |
| 4             | count | Total number of paths |

Following sub-block follows `count` number of times.

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 1             | looping | Boolean value indicating whether path loops |
| 4             | tag | Tag used to identify groups of entities, regardless of their IDs |
| 4             | count2 | Total number of points in path |

Following subsub-flock follows `count2` number of times

| Width (bytes) | Usage | Note |
| :-----------: | :---- | :--- |
| 4             | x     | World X coordinate of a point |
| 4             | y     | World Y coordinate of a point |
| 4             | value | Auxiliary value |
