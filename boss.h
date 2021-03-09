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

static void handleInput_move_boss();
static void handleInput_level_boss(int PLAYER_DAMAGE_A,int PLAYER_DAMAGE_B);
static void config_scroll_level_boss();
static void enemys_level_boss(int ADD_SCORE,int ENEMY_DAMAGE);



void boss()
{
  //Local variables
  u16 ind;
  int timer1=0;
  int timer2=0;
  TBOOL DO;

  int ENERGY_PLAYER;
  int ENERGY_ENEMY1;


  int COMPLETED;

  int ENEMY_DAMAGE;
  int PLAYER_DAMAGE_A;
  int PLAYER_DAMAGE_B;

  int ADD_SCORE;

  Characters = MEM_alloc(2 * sizeof(TCHARACTER));

  //Initialize level objects-----------------------------------------------------
	  ENERGY_PLAYER   =  0x0003E8;
	  ENERGY_ENEMY1   =  0x000FA0;
	  COMPLETED       =  0x000064;
	  ENEMY_DAMAGE    =  0x000001;
	  PLAYER_DAMAGE_A =  0x00000A;
	  PLAYER_DAMAGE_B =  0x000005;
	  ADD_SCORE       =  0x00000A;
  //----------------------------------------------------------------------------

  System16->game_over = FALSE;
  System16->winner = FALSE;

  Gamer->energy=ENERGY_PLAYER;
  Gamer->score=0;

  //Leono
  Characters[0].x      = 0x00000A;
  Characters[0].y      = 0x000064;
  Characters[0].speed  = 0x000003;
  Characters[0].energy = 0x000000;
  Characters[0].dead   = 0x000000;
  Characters[0].graph  = 0x000000;

  //Mumm-Ra
  Characters[1].x      =-0x0000C8;
  Characters[1].y      = 0x000064;
  Characters[1].speed  = 0x000003;
  Characters[1].energy = ENERGY_ENEMY1;
  Characters[1].dead   = 0x000000;
  Characters[1].graph  = 0x000000;


  CanvasA.offset_H = 0x000000;
  CanvasA.offset_V = 0x000000;
  CanvasA.speed    = 0x000002;

  DO=TRUE;

  //Tv background
	  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x0000000));
	  VDP_setBackgroundColor(2);

	  VDP_setPalette(PAL1,OBJ_RESOURCE_LEVEL_01_A.palette->data);
	  VDP_setPalette(PAL2,OBJ_RESOURCE_LEVEL_01_B.palette->data);

	  ind = TILE_USERINDEX;
	  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_LEVEL_01_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 0, 0, 0, CPU);
	  ind += OBJ_RESOURCE_LEVEL_01_A.tileset->numTile;

	  VDP_drawImageEx(BG_B, &OBJ_RESOURCE_LEVEL_01_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, ind), 0, 0, 0, CPU);
	  ind += OBJ_RESOURCE_LEVEL_01_B.tileset->numTile;

	  VDP_setPalette(PAL3, OBJ_RESOURCE_CHARACTER_BOSS.palette->data);

	  SND_startPlay_2ADPCM(OBJ_MUSIC_TRACK06, sizeof(OBJ_MUSIC_TRACK06), SOUND_PCM_CH1,1);
  //-----------------------------------------------------------------------------------------------

  //Initial markers
  updateGameInfo();

  //initialize sprite engine
  SPR_init(0, 0, 0);



  Characters[0].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_BOSS,
                                       Characters[0].x,
                                       Characters[0].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[1].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_BOSS,
                                       Characters[1].x,
                                       Characters[1].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  //-----------------------------------------------------------------------------------------------


  SPR_setAnim(Characters[0].graph, LEONO_ANIMATION);
  SPR_setAnim(Characters[1].graph, MUMMRA_ANIMATION);



  //Set Level Scroll
  config_scroll_level_boss();


  while(DO)
  {

	//Enemy IA procedures execution
    timer1++;

    if(timer1 > 3)
    {
    	enemys_level_boss(ADD_SCORE,ENEMY_DAMAGE);
    	timer1=0;
    }

    //Game rules
    if(Gamer->energy <= 0)
    {
    	if(Gamer->lives > 0)
    	{
    		Gamer->lives-=1;
    		Gamer->energy = ENERGY_PLAYER;
    	}
    }

    if(Gamer->energy < 0 && Gamer->lives == 0)
    {
    	System16->game_over = TRUE;
    	DO=FALSE;
    }

    if(Gamer->score >= COMPLETED)
    {
    	System16->winner = TRUE;
    	DO=FALSE;
    }


    //Player Controller update
    handleInput_move_boss();

    timer2++;
    if(timer2 > 6)
    {
    	timer2=0;
    	handleInput_level_boss(PLAYER_DAMAGE_A,PLAYER_DAMAGE_B);
    }


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

  SPR_releaseSprite(Characters[0].graph);
  SPR_releaseSprite(Characters[1].graph);

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
	  Gamer->level=7;
	  stages();
  }


}

static void config_scroll_level_boss()
{
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    CanvasA.offset_H=0;
    CanvasA.offset_V=0;
}

static void handleInput_move_boss()
{
    u16 value = JOY_readJoypad(JOY_1);

    if (value & BUTTON_START)
        {
    		pause();
        }

    else if (value & BUTTON_LEFT)
        {
        	CanvasA.offset_H += 2;
        	Characters[0].x--; if(Characters[0].x <= LEFT_LIMIT_PLAYER) Characters[0].x = LEFT_LIMIT_PLAYER;
        	SPR_setAnim(Characters[0].graph, LEONO_ANIMATION_RUN); SPR_setHFlip(Characters[0].graph, TRUE);
        	SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);
        }
    else if (value & BUTTON_RIGHT)
        {
        	CanvasA.offset_H -= 2;
        	Characters[0].x++; if(Characters[0].x >= RIGHT_LIMIT_PLAYER) Characters[0].x = RIGHT_LIMIT_PLAYER;
        	SPR_setAnim(Characters[0].graph, LEONO_ANIMATION_RUN); SPR_setHFlip(Characters[0].graph, FALSE);
        	SPR_setPosition(Characters[0].graph,Characters[0].x,Characters[0].y);
        }


    if ((!(value & BUTTON_RIGHT)) && (!(value & BUTTON_LEFT))
    		                      && (!(value & BUTTON_A))
    		                      && (!(value & BUTTON_B))
       )
    {
    	SPR_setAnim(Characters[0].graph, LEONO_ANIMATION);
    }


}

static void handleInput_level_boss(int PLAYER_DAMAGE_A,int PLAYER_DAMAGE_B)
{
    u16 value = JOY_readJoypad(JOY_1);

    static TBOOL event_button_A_press = FALSE;
    static TBOOL event_button_A_free  = FALSE;
    static TBOOL event_button_B_press = FALSE;
    static TBOOL event_button_B_free  = FALSE;

    if (value & BUTTON_A)
        {
    	event_button_A_press = TRUE;
        }

    else if (value & BUTTON_B)
        {
    	event_button_B_press = TRUE;
        }

    if ((!(value & BUTTON_A)) && (!(value & BUTTON_B)))
    {
    	event_button_A_free = TRUE;
    	event_button_B_free = TRUE;
    }


    if(event_button_A_press && event_button_A_free)
    {
    		//clear events
    		event_button_A_press = FALSE;
    		event_button_A_free  = FALSE;

    		SPR_setAnim(Characters[0].graph, LEONO_ANIMATION_SLASH);

        	if(fcollisionEx(Characters[0].x,Characters[0].y,
        			  Characters[1].x,Characters[1].y,30))
        	{
        		Characters[1].energy-=PLAYER_DAMAGE_A;
        		Gamer->score+=1;
        		updateGameInfo();
        	}

        	SND_startPlay_2ADPCM(OBJ_MUSIC_BLOW1, sizeof(OBJ_MUSIC_BLOW1), SOUND_PCM_CH2,0);
    }


    if(event_button_B_press && event_button_B_free)
    {
		//clear events
		event_button_B_press = FALSE;
		event_button_B_free  = FALSE;

        SPR_setAnim(Characters[0].graph, LEONO_ANIMATION_KICK);

        	if(fcollision(Characters[0].x,Characters[0].y,
        			  Characters[1].x,Characters[1].y))
        	{
        		Characters[1].energy-=PLAYER_DAMAGE_B;
        		Gamer->score+=1;
        		updateGameInfo();
        	}

        SND_startPlay_2ADPCM(OBJ_MUSIC_BLOW2, sizeof(OBJ_MUSIC_BLOW2), SOUND_PCM_CH2,0);

    }


}

static void enemys_level_boss(int ADD_SCORE,int ENEMY_DAMAGE)
{
	static int direction=0; //0= RIGHT, 1= LEFT

	if(direction == 0)
	{
		if(Characters[1].x < RIGHT_LIMIT_ENEMY){
			SPR_setHFlip(Characters[1].graph,FALSE);
			Characters[1].x+=1;}
		else
			direction=1;
	}

	if(direction == 1)
	{
		if(Characters[1].x > LEFT_LIMIT_ENEMY){
			 SPR_setHFlip(Characters[1].graph, TRUE);
			Characters[1].x-=1;}
		else
			direction=0;
	}


    SPR_setPosition(Characters[1].graph,Characters[1].x,Characters[1].y);

    //Management collisions of enemys
    if(fcollision(Characters[0].x,Characters[0].y,
    			  Characters[1].x,Characters[1].y))
    		{
    			Gamer->energy-=ENEMY_DAMAGE;
    			updateGameInfo();
    		}


}


