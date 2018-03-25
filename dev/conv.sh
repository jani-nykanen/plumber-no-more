#!/bin/sh
cd "$(dirname "$0")"

# Tilemaps
../tools/tmx2bin maps/1.tmx ../ASSETS/MAPS/1.BIN
../tools/tmx2bin maps/2.tmx ../ASSETS/MAPS/2.BIN
../tools/tmx2bin maps/3.tmx ../ASSETS/MAPS/3.BIN
../tools/tmx2bin maps/4.tmx ../ASSETS/MAPS/4.BIN
../tools/tmx2bin maps/5.tmx ../ASSETS/MAPS/5.BIN
../tools/tmx2bin maps/6.tmx ../ASSETS/MAPS/6.BIN

# Bitmaps
../tools/png2bin bitmaps/player.png ../ASSETS/BITMAPS/PLAYER.BIN
../tools/png2bin bitmaps/tiles.png ../ASSETS/BITMAPS/TILES.BIN
../tools/png2bin bitmaps/font.png ../ASSETS/BITMAPS/FONT.BIN