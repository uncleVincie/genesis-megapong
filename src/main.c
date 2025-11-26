#include <genesis.h>
#include <resources.h>

int main() {

    VDP_loadTileSet(bgtile.tileset,1,DMA); //load the tileset into position 1 in VRAM, use Direct Memory Access
    PAL_setPalette(PAL1, bgtile.palette->data,DMA); //get pallete data from the asset, load into pallet 1, using DMA
    //VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,1),2,2); //draw on Plane B, draw the tile that's in position 1 in VRAM with pallete 1, no flipping, x position in tiles, y position in tiles
    VDP_fillTileMapRect(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),0,0,40,30);
    while(1) {
        SYS_doVBlankProcess();
    }
    return(0);
}