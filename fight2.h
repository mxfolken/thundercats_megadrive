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

void fight2()
{
  //Local variables
  u16 ind;
  int timer1=0;
  int timer2=0;
  int C;
  TBOOL DO;

  int ENERGY_PLAYER;
  int ENERGY_ENEMY1;
  int ENERGY_ENEMY2;
  int ENERGY_ENEMY3;
  int ENERGY_ENEMY4;
  int ENERGY_ENEMY5;
  int ENERGY_ENEMY6;

  int COMPLETED;

  int ENEMY_DAMAGE;
  int PLAYER_DAMAGE_A;
  int PLAYER_DAMAGE_B;

  int ADD_SCORE;

  Characters = MEM_alloc(7 * sizeof(TCHARACTER));

  //Initialize level objects----------------------------------------------------
	  ENERGY_PLAYER   =   0x00012C;
	  ENERGY_ENEMY1   =   0x00000A;
	  ENERGY_ENEMY2   =   0x00000A;
	  ENERGY_ENEMY3   =   0x00000A;
	  ENERGY_ENEMY4   =   0x00000A;
	  ENERGY_ENEMY5   =   0x00000A;
	  ENERGY_ENEMY6   =   0x00000A;
	  COMPLETED       =   0x000064;
	  ENEMY_DAMAGE    =   0x000019;
	  PLAYER_DAMAGE_A =   0x000001;
	  PLAYER_DAMAGE_B =   0x000005;
	  ADD_SCORE       =   0x00000A;
  //----------------------------------------------------------------------------

  System16->game_over = FALSE;
  System16->winner = FALSE;

  Gamer->energy=ENERGY_PLAYER;
  Gamer->score=0;

  //Lion-O
  Characters[0].x      = 0x0000A0;
  Characters[0].y      = 0x00009E;
  Characters[0].speed  = 0x000003;
  Characters[0].energy = 0x000000;
  Characters[0].dead   = 0x000000;
  Characters[0].graph  = 0x000000;

  //Jackalman
  Characters[1].x      = POSITION_INIT1_FIGHT;
  Characters[1].y      = 0x00009E;
  Characters[1].speed  = 0x000003;
  Characters[1].energy = ENERGY_ENEMY1;
  Characters[1].dead   = 0x000000;
  Characters[1].graph  = 0x000000;

  //Monkian
  Characters[2].x      = POSITION_INIT2_FIGHT;
  Characters[2].y      = 0x00009E;
  Characters[2].speed  = 0x000003;
  Characters[2].energy = ENERGY_ENEMY2;
  Characters[2].dead   = 0x000000;
  Characters[2].graph  = 0x000000;

  //Mutant
  Characters[3].x      = POSITION_INIT3_FIGHT;
  Characters[3].y      = 0x00009E;
  Characters[3].speed  = 0x000003;
  Characters[3].energy = ENERGY_ENEMY3;
  Characters[3].dead   = 0x000000;
  Characters[3].graph  = 0x000000;

  //Mutant
  Characters[4].x      = POSITION_INIT4_FIGHT;
  Characters[4].y      = 0x00009E;
  Characters[4].speed  = 0x000003;
  Characters[4].energy = ENERGY_ENEMY4;
  Characters[4].dead   = 0x000000;
  Characters[4].graph  = 0x000000;

  //Mutant
  Characters[5].x      = POSITION_INIT5_FIGHT;
  Characters[5].y      = 0x00009E;
  Characters[5].speed  = 0x000003;
  Characters[5].energy = ENERGY_ENEMY5;
  Characters[5].dead   = 0x000000;
  Characters[5].graph  = 0x000000;

  //Mutant
  Characters[6].x      = POSITION_INIT6_FIGHT;
  Characters[6].y      = 0x00009E;
  Characters[6].speed  = 0x000003;
  Characters[6].energy = ENERGY_ENEMY6;
  Characters[6].dead   = 0x000000;
  Characters[6].graph  = 0x000000;


  CanvasA.offset_H     = 0x000000;
  CanvasA.offset_V     = 0x000000;
  CanvasA.speed        = 0x000002;

  DO=TRUE;


  //Tv Background

	  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x0000000));
	  VDP_setBackgroundColor(2);

	  VDP_setPalette(PAL1,OBJ_RESOURCE_LEVEL_08_A.palette->data);
	  VDP_setPalette(PAL2,OBJ_RESOURCE_LEVEL_08_B.palette->data);

	  ind = TILE_USERINDEX;
	  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_LEVEL_08_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 0, 0, 0, CPU);
	  ind += OBJ_RESOURCE_LEVEL_08_A.tileset->numTile;

	  VDP_drawImageEx(BG_B, &OBJ_RESOURCE_LEVEL_08_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, ind), 0, 0, 0, CPU);
	  ind += OBJ_RESOURCE_LEVEL_08_B.tileset->numTile;

	  VDP_setPalette(PAL3, OBJ_RESOURCE_CHARACTER_LEVEL_08.palette->data);

	  SND_startPlay_2ADPCM(OBJ_MUSIC_TRACK01, sizeof(OBJ_MUSIC_TRACK01), SOUND_PCM_CH1,1);
  //-----------------------------------------------------------------------------------------------

  //Initial markers
  updateGameInfo();

  //initialize sprite engine
  SPR_init(0, 0, 0);


  Characters[0].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_08,
                                       Characters[0].x,
                                       Characters[0].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[1].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_08,
                                       Characters[1].x,
                                       Characters[1].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[2].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_08,
                                       Characters[2].x,
                                       Characters[2].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[3].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_08,
                                       Characters[3].x,
                                       Characters[3].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[4].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_08,
                                       Characters[4].x,
                                       Characters[4].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[5].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_08,
                                       Characters[5].x,
                                       Characters[5].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[6].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_LEVEL_08,
                                       Characters[6].x,
                                       Characters[6].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
  //-----------------------------------------------------------------------------------------------

  SPR_setAnim(Characters[1].graph, ANIM_CHACALO_FIGHT);
  SPR_setAnim(Characters[2].graph, ANIM_MANDRILO_FIGHT);
  SPR_setAnim(Characters[3].graph, ANIM_CHACALO_FIGHT);

  SPR_setAnim(Characters[4].graph, ANIM_CHACALO_FIGHT);
  SPR_setAnim(Characters[5].graph, ANIM_MANDRILO_FIGHT);
  SPR_setAnim(Characters[6].graph, ANIM_CHACALO_FIGHT);

  SPR_setHFlip(Characters[1].graph, TRUE);
  SPR_setHFlip(Characters[2].graph, TRUE);
  SPR_setHFlip(Characters[3].graph, TRUE);

  //Set Level Scroll
  config_scroll_level_fight();


  while(DO)
  {

	//Enemy IA procedures execution
    timer1++;

    if(timer1 > 2)
    {
    	enemys_level_fight(ADD_SCORE,ENEMY_DAMAGE);
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
    handleInput_move_fight();

    timer2++;
    if(timer2 > 6)
    {
    	timer2=0;
    	handleInput_level_fight(PLAYER_DAMAGE_A,PLAYER_DAMAGE_B);
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
	  Gamer->level = 9;
	  stages();
  }


}


