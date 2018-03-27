#!/bin/sh
cd "$(dirname "$0")"

# Tilemaps
../tools/tmx2bin maps/1.tmx ../ASSETS/MAPS/1.BIN
../tools/tmx2bin maps/2.tmx ../ASSETS/MAPS/2.BIN
../tools/tmx2bin maps/3.tmx ../ASSETS/MAPS/3.BIN
../tools/tmx2bin maps/4.tmx ../ASSETS/MAPS/4.BIN
../tools/tmx2bin maps/5.tmx ../ASSETS/MAPS/5.BIN
../tools/tmx2bin maps/6.tmx ../ASSETS/MAPS/6.BIN
../tools/tmx2bin maps/7.tmx ../ASSETS/MAPS/7.BIN
../tools/tmx2bin maps/8.tmx ../ASSETS/MAPS/8.BIN
../tools/tmx2bin maps/9.tmx ../ASSETS/MAPS/9.BIN
../tools/tmx2bin maps/10.tmx ../ASSETS/MAPS/10.BIN
../tools/tmx2bin maps/11.tmx ../ASSETS/MAPS/11.BIN
../tools/tmx2bin maps/12.tmx ../ASSETS/MAPS/12.BIN
../tools/tmx2bin maps/13.tmx ../ASSETS/MAPS/13.BIN
../tools/tmx2bin maps/14.tmx ../ASSETS/MAPS/14.BIN

# Bitmaps
../tools/png2bin bitmaps/player.png ../ASSETS/BITMAPS/PLAYER.BIN
../tools/png2bin bitmaps/tiles.png ../ASSETS/BITMAPS/TILES.BIN
../tools/png2bin bitmaps/font.png ../ASSETS/BITMAPS/FONT.BIN
../tools/png2bin bitmaps/coin.png ../ASSETS/BITMAPS/COIN.BIN
../tools/png2bin bitmaps/monsters.png ../ASSETS/BITMAPS/ENEMIES.BIN
../tools/png2bin bitmaps/rocket.png ../ASSETS/BITMAPS/ROCKET.BIN