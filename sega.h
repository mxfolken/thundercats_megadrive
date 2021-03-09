/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Nova32 Animation Studios
	Rolando Fernandez Benavidez, February 18 2021.

	Thundercats the game!
	for SEGA Genesis/MegaDrive systems.

	Compatible with NTSC & PAL TV.
*/


#include <genesis.h>

void SEGA()
{
  u16 ind;
  int  timer1=0;
  char bplay=FALSE;

  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x000000));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL1, OBJ_RESOURCE_SEGA.palette->data);

  ind = TILE_USERINDEX;

  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_SEGA, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 13, 10, 0, CPU);
  ind += OBJ_RESOURCE_SEGA.tileset->numTile;

  while(TRUE)
  {

   timer1++;

   if(timer1 > 70)
   {
        if(bplay == FALSE)
        {
            SND_startPlay_PCM(OBJ_MUSIC_SEGA, sizeof(OBJ_MUSIC_SEGA), SOUND_RATE_11025,SOUND_PAN_CENTER,0);
            bplay=TRUE;
        }
   }

   if(timer1 > 200) break;

    VDP_waitVSync();
  }

  //Free VDP tile resources
  VDP_resetScreen();

}

