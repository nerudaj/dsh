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

### LevelD C++ Structure

Declaration of this structure is particulary messy, due to many sub-structures being introduced, but when using it, you only need to care about following members:

 * metadata
 * mesh
 * players
 * npcs
 * items

Each of these members is represented by a single block in the .lvd file. If a member is not initialized, it's block won't be serialized into .lvd file and vice versa.

### Parsing

Every .lvd file **must** start with 4B big endian number denoting version of LevelD specification. This number denotes which blocks are supported. This specification will clearly denote which version of LevelD parser each block requires.

After these initial parsing must proceed in following steps:
 1. Read next 4 bytes of data. This is the block *ID*
 2. Then proceed with parser specific for that block based on *ID*

#### Strings

When this specification states something is stored as a string, that this is stored first as a 1B number stating how many characters that string has (string cannot be longer than 255 characters, ignoring null terminating character) and then that many characters follow.

#### Vectors

When this specification states something is stored as a vector of XB numbers, it means first there are 4B of data specifiying *length* of the vector and then X * *length* bytes of data containing the desired vector.

## META block

This block represents metadata of the level.

Meta block parsing follows these steps:

 1. Read 8B of data - *timestamp*
 2. Read a string of data - *id* of the level
 3. Read a string of data - *name* of the level
 4. Read a string of data - *author* of the level
 5. Read a string of data - brief *description* of the level

## MESH block

Mesh block represents the level mesh - how it looks and where the collisions are. This block only supports tile based maps with only simple (on/off) collisions.

Parsing follows these steps:

 1. Read 2B of data - *width* of tile
 2. Read 2B of data - *height* of tile
 3. Read 4B of data - *width* of map
 4. Read vector of 2B data - *data* of map
 5. *height* of the map is computed as |*data*| / *width*
 6. Split *data* into two vectors - *tiles* and *blocks*
 7. You obtain *tiles* by taking bottom 15bits from each field of *data*
 8. You obtain *blocks* by taking top 1bit from each field of *data*

The *blocks* vector basically says whether a tile at index [x, y] is impassable or not. You can index into blocks using this formula: `y * width + x`

The *tiles* vector says what type of a tile is at index [x, y]. Indexing formula is the same as for *blocks*.

## PLAS block

Players block is for storing spawn positions of players in level.

Parsing follows these steps:

 1. Read 4B of data - *count* of player spawns
 2. N times do this:
    a. Read 4B of data - *id* of the actor (from LevelD version 1)
    b. Read 4B of data - *x* coordinate of current player spawn
    c. Read 4B of data - *y* coordinate of current player spawn
    d. Read 2B of data - *flags* affecting current player spawn

## NPCS block

NPCs block is for storing spawn positions of non-players in level.

Parsing is identical to parsing of PLAS block.

## ITEM block

Item block is for storing spawn positions of items in level.

Parsing is identical to parsing of PLAS and NPCS block.