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

void game_over()
{
  u16 ind;
  int timer1=0;
  int timer2=0;
  TBOOL DO = TRUE;

  //Tv Background

  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x0000000));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL1, OBJ_RESOURCE_GAMEOVER.palette->data);

  ind = TILE_USERINDEX;
  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_GAMEOVER, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 12, 6, 0, CPU);
  ind += OBJ_RESOURCE_GAMEOVER.tileset->numTile;

  VDP_drawText("Thundercat you have failed, you are",2,2);
  VDP_drawText("dead HA, HA, HA!",2,3);

  char str[80]="";
  sprintf(str,"YOUR FINAL SCORE: %d",Gamer->total_score);
  VDP_drawText(str,11,23);

  SND_startPlay_PCM(OBJ_MUSIC_GAMEOVER, sizeof(OBJ_MUSIC_GAMEOVER), SOUND_RATE_11025,SOUND_PAN_CENTER,0);

  while(DO)
  {
    timer1++;

    if(timer1 > 3)
    {
        timer1=0;
        VDP_drawText("G A M E    O V E R",11,18);
    }
    else
    	VDP_drawText("                  ",11,18);


    timer2++;
    if(timer2 > 2300)
    {
    	timer2=0;
    	DO=FALSE;
    }

    SYS_doVBlankProcess();
  }

  //Free VDP tile resources
  VDP_resetScreen();
  SYS_hardReset();

}





