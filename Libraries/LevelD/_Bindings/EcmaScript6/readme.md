# Readme

This project is a binding of LevelD file format (de)parser for Javascript (more precisely EcmaScript 6).

## How to use

First you have to link the `leveld.js` file to your application. From this point, you can use class `LevelD` which has following members:

 * metadata
 * mesh
 * players
 * npcs
 * items

These members have the same structure and byte precision as in the main LevelD project. Please see the documentation for main C++ implementation.

You can build `LevelD` object by hand or you can initialize them from `.lvd` files. You will need to fetch those files from the backend as `Uint8Array` and then initialize the `LevelD` object using it:

```js
// variable rawData contains Uint8Array with file contents fetched from backend

let lvd = new LevelD();
lvd.LoadFromUint8Array(rawData);
// lvd is now properly initialized
```

You can also export initialized LevelD object back into Uint8Array using method `GetSerializedToUint8Array()`.

## Known limitations/Bugs

The timestamp property of metadata is currently not loaded/exported at all, it will be always zero.