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

static TBOOL handleInputMenu();

void game_menu()
{
  u16 ind;
  int timer1=0;
  TBOOL DO = 1;

  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x000000));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL1, OBJ_RESOURCE_MENU.palette->data);

  ind = TILE_USERINDEX;
  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_MENU, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 0, 0, 0, CPU);
  ind += OBJ_RESOURCE_MENU.tileset->numTile;

  VDP_drawText("        Nova32 Animation Studios",1,1);
  VDP_drawText("   Rolando Fernandez Benavidez,2021.",1,2);

  SND_startPlay_2ADPCM(OBJ_MUSIC_MENU, sizeof(OBJ_MUSIC_MENU), SOUND_PCM_CH1,1);

  while(DO==1)
  {
    timer1++;

    if(timer1 > 3)
    {
        timer1=0;
        VDP_drawText("PUSH START",16,56);
        VDP_drawText("(C)PASSWORD",15,58);
    }
    else
    {
        VDP_drawText("          ",16,56);
        VDP_drawText("           ",15,58);
    }

    DO = handleInputMenu();

    SYS_doVBlankProcess();
  }

  //Free VDP tile resources
  VDP_resetScreen();

  SND_stopPlay_2ADPCM(SOUND_PCM_CH1);
  SND_stopPlay_2ADPCM(SOUND_PCM_CH2);

  System16 = &GLSYSTEM16;
  Gamer = &GLGAMER;

  if(DO==0)
  {
	  Gamer->lives=3;
	  Gamer->bonus=0;
	  Gamer->total_score=0;
	  Gamer->level = 1;
	  Gamer->stage = 0;

	  //DEBUG----------------
	  Gamer->level = 1;
	  //---------------------

	  stages();
  }
  else
	  password();

}

static TBOOL handleInputMenu()
{
    TBOOL RC=1;
    u16 value = JOY_readJoypad(JOY_1);

    if(value & BUTTON_START) RC=0;
    if(value & BUTTON_C) RC=2;

    SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);

return RC;
}





