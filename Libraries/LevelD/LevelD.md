# LevelD File Format Documentation

This file contains comprehensive documentation of LevelD file format and how is the LevelD C++ structure (de)serialized. This file should be considered as the definitive specification and any implementation of LevelD file reader should conform to this file.

## Table of Contents

 * [Introduction](#introduction)
 * [MESH block](#mesh-block)

## Introduction

The LevelD file format is an universal storage for game level data. It provides conversion layer between C++ data structure and file on a computer disk. It can store many different kinds of information in a fairly effective manner.

The LevelD file format (.lvd for short) is build around the idea of modules or blocks of data that can be provided independently on each other. LevelD structure is meant to be serialized as a binary file, as effectively as possible.

Every .lvd file **must** start with 4B big endian number denoting version of LevelD specification. This number denotes which blocks are supported. This specification will clearly denote which version of LevelD parser each block requires.

After these initial parsing must proceed in following steps:
 1. Read next 4 bytes of data. This is the block *ID*
 2. Read next 4 bytes of data. This is the block *size*
 3. Read next *size* bytes of data. This is the block *contents*
 4. Parse *contents* using appropriate block parser based on *ID*

## META block

TODO

## MESH block

TODO

## PLAS block

TODO

## NPCS block

TODO

## ITEM block

TODO