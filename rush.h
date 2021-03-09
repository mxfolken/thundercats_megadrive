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

static void handleInput_rush();
static void items_rush(int ADD_SCORE);


void rush()
{
  //Local variables
  u16 ind;
  int timer1=0;
  int C;
  TBOOL DO;
  int timer2=0;
  int TIME_LIMIT;

  int COMPLETED;
  int ADD_SCORE;

  Characters = MEM_alloc(7 * sizeof(TCHARACTER));

  //Initialize level objects----------------------------------------------------
	  COMPLETED   = 0x0003E8;
	  ADD_SCORE   = 0x00000A;
	  TIME_LIMIT  = 0x000078;
  //----------------------------------------------------------------------------

  System16->game_over = FALSE;
  System16->winner = FALSE;

  Gamer->energy=500;
  Gamer->score=0;

  //Cheetara
  Characters[0].x      = 0x00000A;
  Characters[0].y      = 0x00009E;
  Characters[0].speed  = 0x000003;
  Characters[0].energy = 0x000000;
  Characters[0].dead   = 0x000000;
  Characters[0].graph  = 0x000000;

  Characters[1].x      = POSITION_INIT1_RUSH;
  Characters[1].y      = 0x00001E;
  Characters[1].speed  = 0x000003;
  Characters[1].energy = 0x000000;
  Characters[1].dead   = 0x000000;
  Characters[1].graph  = 0x000000;

  Characters[2].x      = POSITION_INIT2_RUSH;
  Characters[2].y      = 0x0000A0;
  Characters[2].speed  = 0x000003;
  Characters[2].energy = 0x000000;
  Characters[2].dead   = 0x000000;
  Characters[2].graph  = 0x000000;

  Characters[3].x      = POSITION_INIT3_RUSH;
  Characters[3].y      = 0x000064;
  Characters[3].speed  = 0x000003;
  Characters[3].energy = 0x000000;
  Characters[3].dead   = 0x000000;
  Characters[3].graph  = 0x000000;

  Characters[4].x      = POSITION_INIT4_RUSH;
  Characters[4].y      = 0x00005A;
  Characters[4].speed  = 0x000003;
  Characters[4].energy = 0x000000;
  Characters[4].dead   = 0x000000;
  Characters[4].graph  = 0x000000;

  Characters[5].x      = POSITION_INIT5_RUSH;
  Characters[5].y      = 0x00008C;
  Characters[5].speed  = 0x000003;
  Characters[5].energy = 0x000000;
  Characters[5].dead   = 0x000000;
  Characters[5].graph  = 0x000000;

  Characters[6].x      = POSITION_INIT6_RUSH;
  Characters[6].y      = 0x0000C8;
  Characters[6].speed  = 0x000003;
  Characters[6].energy = 0x000000;
  Characters[6].dead   = 0x000000;
  Characters[6].graph  = 0x000000;


  DO=TRUE;


  //Tv Background

  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x0000000));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL2,OBJ_RESOURCE_LEVEL_03_B.palette->data);

  ind = TILE_USERINDEX;
  VDP_drawImageEx(BG_B, &OBJ_RESOURCE_LEVEL_03_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, ind), 0, 0, 0, CPU);
  ind += OBJ_RESOURCE_LEVEL_03_B.tileset->numTile;

  SND_startPlay_2ADPCM(OBJ_MUSIC_TRACK03, sizeof(OBJ_MUSIC_TRACK03), SOUND_PCM_CH1,1);
  //-----------------------------------------------------------------------------------------------

  //Initial markers
  updateGameInfo();

  //initialize sprite engine
  SPR_init(0, 0, 0);


  VDP_setPalette(PAL3, OBJ_RESOURCE_CHARACTER_LEVEL_03.palette->data);



  Characters[0].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_03,
                                       Characters[0].x,
                                       Characters[0].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[1].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_03,
                                       Characters[1].x,
                                       Characters[1].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[2].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_03,
                                       Characters[2].x,
                                       Characters[2].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[3].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_03,
                                       Characters[3].x,
                                       Characters[3].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[4].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_03,
                                       Characters[4].x,
                                       Characters[4].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[5].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_03,
                                       Characters[5].x,
                                       Characters[5].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[6].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_03,
                                       Characters[6].x,
                                       Characters[6].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
  //-----------------------------------------------------------------------------------------------

  SPR_setAnim(Characters[1].graph, 6);
  SPR_setAnim(Characters[2].graph, 6);
  SPR_setAnim(Characters[3].graph, 6);

  SPR_setAnim(Characters[4].graph, 6);
  SPR_setAnim(Characters[5].graph, 6);
  SPR_setAnim(Characters[6].graph, 6);

  SPR_setHFlip(Characters[1].graph, TRUE);
  SPR_setHFlip(Characters[2].graph, TRUE);
  SPR_setHFlip(Characters[3].graph, TRUE);


  while(DO)
  {

	//Enemy IA procedures execution
    timer1++;

    if(timer1 > 1)
    {
    	items_rush(ADD_SCORE);
    	timer1=0;
    }

    timer2++;
    if(timer2 > 100)
    {
    	timer2 = 0;
    	TIME_LIMIT = TIME_LIMIT - 1;
    	updateTimerInfo(TIME_LIMIT,'B');
    }

    //Game rules

    if(TIME_LIMIT == 0)
    {
    	if(Gamer->score >= COMPLETED)
    		System16->winner = TRUE;
    	else
    		System16->game_over = TRUE;


    	DO=FALSE;

    }

    //Player Controller update
    handleInput_rush();


    //FRAME
    VDP_setHorizontalScroll(BG_A,CanvasA.offset_H);
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

  Gamer->total_score = Gamer->total_score + Gamer->score;

  if(System16->game_over) game_over();

  if(System16->winner)
  {
	  Gamer->level=4;
	  stages();
  }





}


static void handleInput_rush()
{
    u16 value = JOY_readJoypad(JOY_1);

    if (value & BUTTON_UP)
        {
            if(Characters[0].y > TOP_LIMIT_RUSH) Characters[0].y-=3;
            SPR_setAnim(Characters[0].graph, 5);
            SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);
        }

    if (value & BUTTON_DOWN)
        {
            if(Characters[0].y < DOWN_LIMIT_RUSH) Characters[0].y+=3;
            SPR_setAnim(Characters[0].graph, 5);
            SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);
        }

    if (value & BUTTON_START)
        {
    		pause();
        }

    if (value & BUTTON_LEFT)
        {
            if(Characters[0].x >= LEFT_LIMIT_PLAYER) Characters[0].x-=3;
            SPR_setAnim(Characters[0].graph, 5);
            SPR_setHFlip(Characters[0].graph, TRUE);
            SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);

        }
    else if (value & BUTTON_RIGHT)
        {
            if(Characters[0].x <= RIGHT_LIMIT_PLAYER) Characters[0].x+=3;
            SPR_setAnim(Characters[0].graph, 5);
            SPR_setHFlip(Characters[0].graph, FALSE);
            SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);
        }


    if ( (!(value & BUTTON_RIGHT)) && (!(value & BUTTON_LEFT))
								   && (!(value & BUTTON_UP))
								   && (!(value & BUTTON_DOWN))
       )
        SPR_setAnim(Characters[0].graph, 4);

}

void items_rush(int ADD_SCORE)
{

	int C;

	//---------------------------------------[1]
	if(Characters[1].x > LEFT_LIMIT_ENEMY)
		Characters[1].x-=3;
	else
		Characters[1].x=POSITION_INIT1_RUSH;
	//---------------------------------------[2]
	if(Characters[2].x > LEFT_LIMIT_ENEMY)
		Characters[2].x-=3;
	else
		Characters[2].x=POSITION_INIT2_RUSH;
	//---------------------------------------[3]
	if(Characters[3].x > LEFT_LIMIT_ENEMY)
		Characters[3].x-=1;
	else
		Characters[3].x=POSITION_INIT3_RUSH;
	//---------------------------------------[4]
	if(Characters[4].x < RIGHT_LIMIT_ENEMY)
		Characters[4].x+=1;
	else
		Characters[4].x=POSITION_INIT4_RUSH;
	//---------------------------------------[5]
	if(Characters[5].x < RIGHT_LIMIT_ENEMY)
		Characters[5].x+=1;
	else
		Characters[5].x=POSITION_INIT5_RUSH;
	//---------------------------------------[6]
	if(Characters[6].x < RIGHT_LIMIT_ENEMY)
		Characters[6].x+=2;
	else
		Characters[6].x=POSITION_INIT6_RUSH;
	//---------------------------------------


    for(C=1;C<=6;C++)
    {
    	if(!Characters[C].dead)
    		SPR_setPosition(Characters[C].graph,Characters[C].x,Characters[C].y);
    }


	//Thundercats items

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[1].x,Characters[1].y))
	{
		Gamer->score+=ADD_SCORE;
		Characters[1].x = POSITION_INIT1_RUSH;
		SPR_setPosition(Characters[1].graph,Characters[1].x,Characters[1].y);
		updateGameInfo();
		SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[2].x,Characters[2].y))
	{
		Gamer->score+=ADD_SCORE;
		Characters[2].x = POSITION_INIT2_RUSH;
		SPR_setPosition(Characters[2].graph,Characters[2].x,Characters[2].y);
		updateGameInfo();
		SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[3].x,Characters[3].y))
	{
		Gamer->score+=ADD_SCORE;
		Characters[3].x = POSITION_INIT3_RUSH;
		SPR_setPosition(Characters[3].graph,Characters[3].x,Characters[3].y);
		updateGameInfo();
		SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[4].x,Characters[4].y))
	{
		Gamer->score+=ADD_SCORE;
		Characters[4].x = POSITION_INIT4_RUSH;
		SPR_setPosition(Characters[4].graph,Characters[4].x,Characters[4].y);
		updateGameInfo();
		SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[5].x,Characters[5].y))
	{
		Gamer->score+=ADD_SCORE;
		Characters[5].x = POSITION_INIT5_RUSH;
		SPR_setPosition(Characters[5].graph,Characters[5].x,Characters[5].y);
		updateGameInfo();
		SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
	}

	if(fcollision(Characters[0].x,Characters[0].y,
			  Characters[6].x,Characters[6].y))
	{
		Gamer->score+=ADD_SCORE;
		Characters[6].x = POSITION_INIT6_RUSH;
		SPR_setPosition(Characters[6].graph,Characters[6].x,Characters[6].y);
		updateGameInfo();
		SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
	}



}


