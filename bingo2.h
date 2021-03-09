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


void bingo2()
{
  u16 ind;
  TBOOL timer1_enabled=FALSE;
  int timer1=0;
  int timer2=0;
  TBOOL DO = TRUE;
  int Ace=0;

  Characters = MEM_alloc(3 * sizeof(TCHARACTER));

  Characters[0].x      = 0x000014;
  Characters[0].y      = 0x00006E;
  Characters[0].speed  = 0x000000;
  Characters[0].energy = 0x000000;
  Characters[0].dead   = 0x000000;
  Characters[0].graph  = 0x000000;

  Characters[1].x      = 0x000078;
  Characters[1].y      = 0x00006E;
  Characters[1].speed  = 0x000000;
  Characters[1].energy = 0x000000;
  Characters[1].dead   = 0x000000;
  Characters[1].graph  = 0x000000;

  Characters[2].x      = 0x0000D2;
  Characters[2].y      = 0x00006E;
  Characters[2].speed  = 0x000000;
  Characters[2].energy = 0x000000;
  Characters[2].dead   = 0x000000;
  Characters[2].graph  = 0x000000;


  //Tv background
  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x0000000));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL1, OBJ_RESOURCE_BINGO_A.palette->data);
  VDP_setPalette(PAL2, OBJ_RESOURCE_BINGO_B.palette->data);

  ind = TILE_USERINDEX;
  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_BINGO_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 29, 1, 0, CPU);
  ind += OBJ_RESOURCE_BINGO_A.tileset->numTile;

  VDP_drawImageEx(BG_B, &OBJ_RESOURCE_BINGO_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, ind), 0, 0, 0, CPU);
  ind += OBJ_RESOURCE_BINGO_B.tileset->numTile;

  VDP_setPalette(PAL3, OBJ_RESOURCE_CHARACTER_BINGO.palette->data);

  //initialize sprite engine
  SPR_init(0, 0, 0);


  Characters[0].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_BINGO,
                                       Characters[0].x,
                                       Characters[0].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[1].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_BINGO,
                                       Characters[1].x,
                                       Characters[1].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  Characters[2].graph = SPR_addSprite(&OBJ_RESOURCE_CHARACTER_BINGO,
                                       Characters[2].x,
                                       Characters[2].y,
                                       TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

  SPR_setAnim(Characters[0].graph, 0);
  SPR_setAnim(Characters[1].graph, 0);
  SPR_setAnim(Characters[2].graph, 0);


  VDP_drawText("where is the ace?",11,3);

  VDP_drawText("1",2,14);
  VDP_drawText("2",15,14);
  VDP_drawText("3",26,14);

  VDP_drawText("(A) First card",1,23);
  VDP_drawText("(B) Second card",1,24);
  VDP_drawText("(C) Third card    [START]=Do not play",1,25);


  SND_startPlay_2ADPCM(OBJ_MUSIC_TRACK05, sizeof(OBJ_MUSIC_TRACK05), SOUND_PCM_CH1,1);

  //Seed for dice roll
  setRandomSeed((int)getTick());

  Ace = random() %3; //0-2

  while(DO)
  {

	//Roll lucky dice
	timer2++;
	if(timer2 > 50)
	{
		timer2=0;
		Ace = random() %3; //0-2
		//print_int(Ace,30,10,'A');
	}


	if(!timer1_enabled)
		timer1_enabled = handleInputBingo(Ace);

    if(timer1_enabled)
    {
    	timer1++;
    	if(timer1 > 1200)
    	{
    		timer1=0;
    		DO=FALSE;
    	}
    }

    SPR_update();
    SYS_doVBlankProcess();
  }

  SPR_releaseSprite(Characters[0].graph);
  SPR_releaseSprite(Characters[1].graph);
  SPR_releaseSprite(Characters[2].graph);

  MEM_free(Characters);
  Characters=NULL;

  //Free VDP tile resources
  VDP_resetScreen();
  SPR_reset();

  SND_stopPlay_2ADPCM(SOUND_PCM_CH1);
  SND_stopPlay_2ADPCM(SOUND_PCM_CH2);

  Gamer->level=12;
  stages();

}


