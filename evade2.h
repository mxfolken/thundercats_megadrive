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

void evade2()
{
  //Local variables
  u16 ind;
  int C;
  TBOOL DO;
  int timer=0;
  int timer2=0;

  int ENERGY_PLAYER;
  int ENEMY_DAMAGE;
  int ADD_SCORE;
  int TIME_LIMIT;

  Characters = MEM_alloc(7 * sizeof(TCHARACTER));

  //Initialize level objects----------------------------------------------------
	  ENERGY_PLAYER   =  0x000014;
	  ENEMY_DAMAGE    =  0x000001;
	  ADD_SCORE       =  0x000037;
	  TIME_LIMIT      =  0x000078;
  //----------------------------------------------------------------------------

  System16->game_over = FALSE;
  System16->winner = FALSE;

  Gamer->energy=ENERGY_PLAYER;
  Gamer->score=0;

  //Leono
  Characters[0].x      = 0x000064;
  Characters[0].y      = 0x000064;
  Characters[0].speed  = 0x000003;
  Characters[0].energy = 0x000000;
  Characters[0].dead   = 0x000000;
  Characters[0].graph  = 0x000000;

  Characters[1].x      = POSITION_INIT1_FTANK;
  Characters[1].y      = 0x000014;
  Characters[1].energy = 0x000000;
  Characters[1].dead   = 0x000000;
  Characters[1].graph  = 0x000000;

  Characters[2].x      = POSITION_INIT2_FTANK;
  Characters[2].y      = 0x00008C;
  Characters[2].energy = 0x000000;
  Characters[2].dead   = 0x000000;
  Characters[2].graph  = 0x000000;

  Characters[3].x      = POSITION_INIT3_FTANK;
  Characters[3].y      = 0x00003C;
  Characters[3].energy = 0x000000;
  Characters[3].dead   = 0x000000;
  Characters[3].graph  = 0x000000;

  Characters[4].x      = POSITION_INIT4_FTANK;
  Characters[4].y      = 0x000064;
  Characters[4].energy = 0x000000;
  Characters[4].dead   = 0x000000;
  Characters[4].graph  = 0x000000;

  Characters[5].x      = POSITION_INIT5_FTANK;
  Characters[5].y      = 0x000028;
  Characters[5].energy = 0x000000;
  Characters[5].dead   = 0x000000;
  Characters[5].graph  = 0x000000;

  Characters[6].x      = POSITION_INIT6_FTANK;
  Characters[6].y      = 0x000046;
  Characters[6].energy = 0x000000;
  Characters[6].dead   = 0x000000;
  Characters[6].graph  = 0x000000;

  CanvasA.offset_H     = 0x000000;
  CanvasA.offset_V     = 0x000000;
  CanvasA.speed        = 0x000002;

  DO=TRUE;

  Characters[1].speed  = 0x000003;
  Characters[2].speed  = 0x000004;
  Characters[3].speed  = 0x000003;
  Characters[4].speed  = 0x000002;
  Characters[5].speed  = 0x000003;
  Characters[6].speed  = 0x000004;

  //Tv Background

  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x0000000));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL1,OBJ_RESOURCE_LEVEL_12_A.palette->data);
  VDP_setPalette(PAL2,OBJ_RESOURCE_LEVEL_12_B.palette->data);


  ind = TILE_USERINDEX;
  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_LEVEL_12_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 0, 0, 0, CPU);
  ind += OBJ_RESOURCE_LEVEL_12_A.tileset->numTile;

  VDP_drawImageEx(BG_B, &OBJ_RESOURCE_LEVEL_12_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, ind), 0, 0, 0, CPU);
  ind += OBJ_RESOURCE_LEVEL_12_B.tileset->numTile;

  SND_startPlay_2ADPCM(OBJ_MUSIC_TRACK01, sizeof(OBJ_MUSIC_TRACK01), SOUND_PCM_CH1,1);

  //-----------------------------------------------------------------------------------------------

  //Initial markers
  updateGameInfoEx();

  //initialize sprite engine
  SPR_init(0, 0, 0);

  VDP_setPalette(PAL3, OBJ_RESOURCE_CHARACTER_LEVEL_12.palette->data);


  Characters[0].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_12,
                                       Characters[0].x,
                                       Characters[0].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[1].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_12,
                                       Characters[1].x,
                                       Characters[1].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[2].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_12,
                                       Characters[2].x,
                                       Characters[2].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[3].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_12,
                                       Characters[3].x,
                                       Characters[3].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[4].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_12,
                                       Characters[4].x,
                                       Characters[4].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[5].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_12,
                                       Characters[5].x,
                                       Characters[5].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[6].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_12,
                                       Characters[6].x,
                                       Characters[6].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  //-----------------------------------------------------------------------------------------------

  SPR_setAnim(Characters[1].graph, 2);
  SPR_setAnim(Characters[2].graph, 2);
  SPR_setAnim(Characters[3].graph, 2);

  SPR_setAnim(Characters[4].graph, 2);
  SPR_setAnim(Characters[5].graph, 2);
  SPR_setAnim(Characters[6].graph, 2);


  //Set Level Scroll
  config_scroll_evade();

  //Seed for dice roll
  setRandomSeed((int)getTick());
  int r=0;

  while(DO)
  {

	//Enemy IA procedures execution
    items_evade(ENEMY_DAMAGE);



    //Score random
    timer2++;

    if(timer2 > 4)
    {
    	timer2=0;

		r = random() %20; //0-19
		if(r == 3)
		{
			Gamer->score+=1;
			updateGameInfoEx();
		}

    }

    timer++;
    if(timer > 100)
    {
        timer = 0;
        TIME_LIMIT = TIME_LIMIT - 1;
        updateTimerInfo(TIME_LIMIT,'A');
    }


    if(Gamer->energy == 0)
    {
    	if(Gamer->lives > 0)
    	{
    		Gamer->lives-=1;
    		Gamer->energy = ENERGY_PLAYER;
    	}
    	else TIME_LIMIT = 0;
    }

    //Game rules
    if(TIME_LIMIT == 0)
    {
    	if(Gamer->energy <= 0)
    		System16->game_over = TRUE;
    	else
    		{
    			System16->winner = TRUE;
    			Gamer->score+=ADD_SCORE;
    		}

    	DO=FALSE;
    }


    CanvasA.offset_H-= 2;

    //Player Controller update
    handleInput_evade();


    //FRAME
    VDP_setHorizontalScroll(BG_B,CanvasA.offset_H);
    SPR_update();
    SYS_doVBlankProcess();

  }

  //Level success-----------------------------------------------------------------------------
  VDP_clearTextLine(1);
  VDP_clearTextLine(2);
  if(System16->winner)
	  VDP_drawText("      * * * LEVEL COMPLETED * * *",0,10);
  else
	  VDP_drawText("        * * * LEVEL FAILED * * *",0,10);
  SND_startPlay_2ADPCM(OBJ_MUSIC_TRACK04, sizeof(OBJ_MUSIC_TRACK04), SOUND_PCM_CH1,1);
  int s=500;
  while(s>0){SYS_doVBlankProcess(); s--;}
  //------------------------------------------------------------------------------------------



  for(C=0;C<=6;C++)
	  SPR_releaseSprite(Characters[C].graph);

  MEM_free(Characters);
  Characters=NULL;

  //Free VDP tile resources
  VDP_resetScreen();
  SPR_reset();

  SND_stopPlay_2ADPCM(SOUND_PCM_CH1);
  SND_stopPlay_2ADPCM(SOUND_PCM_CH2);

  if(System16->game_over) game_over();

  if(System16->winner)
  {
	  Gamer->level=13;
	  stages();
  }

}



