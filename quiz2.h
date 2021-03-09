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

static TBOOL handleInputQuiz2();

void quiz2()
{
  u16 ind;
  TBOOL timer1_enabled=FALSE;
  int timer1=0;
  TBOOL DO = TRUE;

  //Tv Background

  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x0000000));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL1, OBJ_RESOURCE_QUIZ_A.palette->data);
  VDP_setPalette(PAL2, OBJ_RESOURCE_QUIZ_B.palette->data);

  ind = TILE_USERINDEX;
  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_QUIZ_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 12, 5, 0, CPU);
  ind += OBJ_RESOURCE_QUIZ_A.tileset->numTile;

  VDP_drawImageEx(BG_B, &OBJ_RESOURCE_QUIZ_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, ind), 0, 0, 0, CPU);
  ind += OBJ_RESOURCE_QUIZ_A.tileset->numTile;


	  VDP_drawText("Where is the eye of Thundera?",2,3);

	  VDP_drawText("(A) On a stone",2,21);
	  VDP_drawText("(B) In the feline castle",2,22);
	  VDP_drawText("(C) On Leono's sword",2,23);


	  SND_startPlay_2ADPCM(OBJ_MUSIC_TRACK04, sizeof(OBJ_MUSIC_TRACK04), SOUND_PCM_CH1,1);

  while(DO)
  {

	if(!timer1_enabled)
		timer1_enabled = handleInputQuiz2();

    if(timer1_enabled)
    {
    	timer1++;
    	if(timer1 > 800)
    	{
    		timer1=0;
    		DO=FALSE;
    	}
    }

    SYS_doVBlankProcess();
  }

  //Free VDP tile resources
  VDP_resetScreen();

  SND_stopPlay_2ADPCM(SOUND_PCM_CH1);
  SND_stopPlay_2ADPCM(SOUND_PCM_CH2);

  Gamer->level=15;
  stages();



}

static TBOOL handleInputQuiz2()
{
    TBOOL RC=FALSE;
    u16 value = JOY_readJoypad(JOY_1);

    	if(value & BUTTON_A)
    	{
    		VDP_drawText("I'm sorry, your answer is wrong            ",2,21);
    		VDP_drawText("I can't gift you points!                   ",2,22);
    		VDP_drawText("See you another time.                      ",2,23);
    		RC=TRUE;
    		SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
    	}

    	if(value & BUTTON_B)
    	{
    		VDP_drawText("I'm sorry, your answer is wrong            ",2,21);
    		VDP_drawText("I can't gift you points!                   ",2,22);
    		VDP_drawText("See you another time.                      ",2,23);
    		RC=TRUE;
    		SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
    	}


    	if(value & BUTTON_C)
    	{
    		VDP_drawText("Excellent answer!                          ",2,21);
    		VDP_drawText("You earned the following points: 400       ",2,22);
    		VDP_drawText(" * * * Congratulations! * * *              ",2,23);
    		Gamer->total_score+=400;
    		RC=TRUE;
    		SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
    	}


return RC;
}





