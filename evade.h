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

static void handleInput_evade();
static void config_scroll_evade();
static void items_evade(int ENEMY_DAMAGE);


void evade()
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
	  ENERGY_PLAYER   =  0x00001E;
	  ENEMY_DAMAGE    =  0x000001;
	  ADD_SCORE       =  0x000037;
	  TIME_LIMIT      =  0x00004E;
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

  Characters[1].speed  = 0x000002;
  Characters[2].speed  = 0x000003;
  Characters[3].speed  = 0x000002;
  Characters[4].speed  = 0x000001;
  Characters[5].speed  = 0x000002;
  Characters[6].speed  = 0x000003;

  //Tv Background

  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x0000000));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL1,OBJ_RESOURCE_LEVEL_05_A.palette->data);
  VDP_setPalette(PAL2,OBJ_RESOURCE_LEVEL_05_B.palette->data);


  ind = TILE_USERINDEX;
  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_LEVEL_05_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 0, 0, 0, CPU);
  ind += OBJ_RESOURCE_LEVEL_05_A.tileset->numTile;

  VDP_drawImageEx(BG_B, &OBJ_RESOURCE_LEVEL_05_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, ind), 0, 0, 0, CPU);
  ind += OBJ_RESOURCE_LEVEL_05_B.tileset->numTile;

  SND_startPlay_2ADPCM(OBJ_MUSIC_TRACK01, sizeof(OBJ_MUSIC_TRACK01), SOUND_PCM_CH1,1);

  //-----------------------------------------------------------------------------------------------

  //Initial markers
  updateGameInfoEx();

  //initialize sprite engine
  SPR_init(0, 0, 0);

  VDP_setPalette(PAL3, OBJ_RESOURCE_CHARACTER_LEVEL_05.palette->data);


  Characters[0].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_05,
                                       Characters[0].x,
                                       Characters[0].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[1].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_05,
                                       Characters[1].x,
                                       Characters[1].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[2].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_05,
                                       Characters[2].x,
                                       Characters[2].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[3].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_05,
                                       Characters[3].x,
                                       Characters[3].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[4].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_05,
                                       Characters[4].x,
                                       Characters[4].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[5].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_05,
                                       Characters[5].x,
                                       Characters[5].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[6].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_05,
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
	  Gamer->level=6;
	  stages();
  }

}



static void config_scroll_evade()
{
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    CanvasA.offset_H=0;
    CanvasA.offset_V=0;
}


static void handleInput_evade()
{
    u16 value = JOY_readJoypad(JOY_1);

    if (value & BUTTON_START)
        {
    		pauseEx();
        }


    if (value & BUTTON_UP)
        {
            if(Characters[0].y > TOP_LIMIT_EVADE) Characters[0].y--;
            SPR_setAnim(Characters[0].graph, 1);
            SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);
        }

    if (value & BUTTON_DOWN)
        {
            if(Characters[0].y < DOWN_LIMIT_EVADE) Characters[0].y++;
            SPR_setAnim(Characters[0].graph, 1);
            SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);
        }


    if (value & BUTTON_LEFT)
        {
            if(Characters[0].x >= LEFT_LIMIT_PLAYER) Characters[0].x--;
            SPR_setAnim(Characters[0].graph, 1);
            SPR_setHFlip(Characters[0].graph, TRUE);
            SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);

        }
    else if (value & BUTTON_RIGHT)
        {
            if(Characters[0].x <= RIGHT_LIMIT_PLAYER) Characters[0].x++;
            SPR_setAnim(Characters[0].graph, 1);
            SPR_setHFlip(Characters[0].graph, FALSE);
            SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);
        }


    if ( (!(value & BUTTON_RIGHT)) && (!(value & BUTTON_LEFT))
								   && (!(value & BUTTON_UP))
								   && (!(value & BUTTON_DOWN))
       )
        SPR_setAnim(Characters[0].graph, 0);

}

void items_evade(int ENEMY_DAMAGE)
{

	int C;

	//---------------------------------------[1]
	if(Characters[1].x > LEFT_LIMIT_ENEMY)
		Characters[1].x-=Characters[1].speed;
	else
		Characters[1].x=POSITION_INIT1_FTANK;
	//---------------------------------------[2]
	if(Characters[2].x > LEFT_LIMIT_ENEMY)
		Characters[2].x-=Characters[2].speed;
	else
		Characters[2].x=POSITION_INIT2_FTANK;
	//---------------------------------------[3]
	if(Characters[3].x > LEFT_LIMIT_ENEMY)
		Characters[3].x-=Characters[3].speed;
	else
		Characters[3].x=POSITION_INIT3_FTANK;
	//---------------------------------------[4]
	if(Characters[4].x < RIGHT_LIMIT_ENEMY)
		Characters[4].x+=Characters[4].speed;
	else
		Characters[4].x=POSITION_INIT4_FTANK;
	//---------------------------------------[5]
	if(Characters[5].x < RIGHT_LIMIT_ENEMY)
		Characters[5].x+=Characters[5].speed;
	else
		Characters[5].x=POSITION_INIT5_FTANK;
	//---------------------------------------[6]
	if(Characters[6].x < RIGHT_LIMIT_ENEMY)
		Characters[6].x+=Characters[6].speed;
	else
		Characters[6].x=POSITION_INIT6_FTANK;
	//---------------------------------------


    for(C=1;C<=6;C++)
    {
    	if(!Characters[C].dead)
    		SPR_setPosition(Characters[C].graph,Characters[C].x,Characters[C].y);
    }


	//danger items

    if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[1].x,Characters[1].y))
	{
    	if(Gamer->energy > 0) Gamer->energy-=ENEMY_DAMAGE;
		updateGameInfoEx();
		SND_startPlay_2ADPCM(OBJ_MUSIC_DAMAG, sizeof(OBJ_MUSIC_DAMAG), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[2].x,Characters[2].y))
	{
		if(Gamer->energy > 0) Gamer->energy-=ENEMY_DAMAGE;
		updateGameInfoEx();
		SND_startPlay_2ADPCM(OBJ_MUSIC_DAMAG, sizeof(OBJ_MUSIC_DAMAG), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[3].x,Characters[3].y))
	{
		if(Gamer->energy > 0) Gamer->energy-=ENEMY_DAMAGE;
		updateGameInfoEx();
		SND_startPlay_2ADPCM(OBJ_MUSIC_DAMAG, sizeof(OBJ_MUSIC_DAMAG), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[4].x,Characters[4].y))
	{
		if(Gamer->energy > 0) Gamer->energy-=ENEMY_DAMAGE;
		updateGameInfoEx();
		SND_startPlay_2ADPCM(OBJ_MUSIC_DAMAG, sizeof(OBJ_MUSIC_DAMAG), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[5].x,Characters[5].y))
	{
		if(Gamer->energy > 0) Gamer->energy-=ENEMY_DAMAGE;
		updateGameInfoEx();
		SND_startPlay_2ADPCM(OBJ_MUSIC_DAMAG, sizeof(OBJ_MUSIC_DAMAG), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[6].x,Characters[6].y))
	{
		if(Gamer->energy > 0) Gamer->energy-=ENEMY_DAMAGE;
		updateGameInfoEx();
		SND_startPlay_2ADPCM(OBJ_MUSIC_DAMAG, sizeof(OBJ_MUSIC_DAMAG), SOUND_PCM_CH2,0);
	}


}


