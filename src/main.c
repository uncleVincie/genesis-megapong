#include <genesis.h>
#include <resources.h>

int main() {

    VDP_loadTileSet(bgtile.tileset,1,DMA); //load the tileset into position 1 in VRAM, use Direct Memory Access
    VDP_setTileMapXY(BG_B,1,2,2); //draw on Plane B, draw the tile that's in position 1 in VRAM, x position in tiles, y position in tiles
    while(1) {
        SYS_doVBlankProcess();
    }
    return(0);
}