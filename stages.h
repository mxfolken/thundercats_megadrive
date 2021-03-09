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

void stages()
{
  u16 ind;
  int timer2=0;
  TBOOL DO = TRUE;

  //Tv Background

  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x0000000));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL1, OBJ_RESOURCE_STAGE.palette->data);

  ind = TILE_USERINDEX;
  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_STAGE, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 12, 6, 0, CPU);
  ind += OBJ_RESOURCE_STAGE.tileset->numTile;

  SND_startPlay_PCM(OBJ_MUSIC_STAGES, sizeof(OBJ_MUSIC_STAGES), SOUND_RATE_11025,SOUND_PAN_CENTER,0);

  char str[80]="";
  sprintf(str,"     LEVEL: %d",Gamer->level);
  VDP_drawText(str,11,21);

  switch(Gamer->level)
  {
  	  case  2: {VDP_drawText("PASSWORD: 2-2-2",11,23); break;}
  	  case  3: {VDP_drawText("PASSWORD: 1-9-0",11,23); break;}
  	  case  4: {VDP_drawText("PASSWORD: 0-5-4",11,23); break;}
  	  case  5: {VDP_drawText("PASSWORD: 5-9-1",11,23); break;}
  	  case  6: {VDP_drawText("PASSWORD: 2-6-2",11,23); break;}
  	  case  7: {VDP_drawText("PASSWORD: 1-3-7",11,23); break;}
  	  case  8: {VDP_drawText("PASSWORD: 8-4-2",11,23); break;}
  	  case  9: {VDP_drawText("PASSWORD: 9-0-3",11,23); break;}
  	  case 10: {VDP_drawText("PASSWORD: 1-0-6",11,23); break;}
  	  case 11: {VDP_drawText("PASSWORD: 2-1-5",11,23); break;}
  	  case 12: {VDP_drawText("PASSWORD: 6-0-9",11,23); break;}
  	  case 13: {VDP_drawText("PASSWORD: 1-3-3",11,23); break;}
  	  case 14: {VDP_drawText("PASSWORD: 0-4-1",11,23); break;}
  	  case 15: {VDP_drawText("PASSWORD: 0-7-7",11,23); break;}
  }


  while(DO)
  {

    timer2++;
    if(timer2 > 600)
    {
    	timer2=0;
    	DO=FALSE;
    }

    SYS_doVBlankProcess();
  }

  //Free VDP tile resources
  VDP_resetScreen();

  switch(Gamer->level)
  {
	  case  1: { fight();        break; }
	  case  2: { feline_tank();  break; }
	  case  3: { rush();         break; }
	  case  4: { bingo();        break; }
	  case  5: { evade();        break; }
	  case  6: { boss();         break; }
	  case  7: { quiz();         break; }

	  case  8: { fight2();       break; }
	  case  9: { feline_tank2(); break; }
	  case 10: { rush2();        break; }
	  case 11: { bingo2();       break; }
	  case 12: { evade2();       break; }
	  case 13: { boss2();        break; }
	  case 14: { quiz2();        break; }
	  case 15: { evade3();       break; }

	  case 16: { end_boss();     break; }
  }

  game_menu();

}





