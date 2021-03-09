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

static TBOOL handleInputPWD(int *a,int *b,int *c);

void password()
{
  u16 ind;
  int timer1=0;
  TBOOL DO = TRUE;

  int A=9;
  int B=9;
  int C=9;

  //Tv Background

  VDP_setPaletteColor(2,RGB24_TO_VDPCOLOR(0x009066B));
  VDP_setBackgroundColor(2);

  VDP_setPalette(PAL1, OBJ_RESOURCE_PASSWORD.palette->data);

  ind = TILE_USERINDEX;
  VDP_drawImageEx(BG_A, &OBJ_RESOURCE_PASSWORD, TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), 0, 0, 0, CPU);
  ind += OBJ_RESOURCE_PASSWORD.tileset->numTile;


  VDP_drawText("9",3,10); VDP_drawText("9",8,10); VDP_drawText("9",12,10);

  VDP_drawText("(A)",2,13); VDP_drawText("(B)",7,13); VDP_drawText("(C)",11,13);

  VDP_drawText("B U T T O N S",2,14);

  VDP_drawText("Select code and",1,17);
  VDP_drawText("press start.",1,18);

  SND_startPlay_2ADPCM(OBJ_MUSIC_TRACK03, sizeof(OBJ_MUSIC_TRACK03), SOUND_PCM_CH1,1);

  while(DO)
  {

	  timer1++;

	  if(timer1 > 7){
		  timer1=0;
		  DO = handleInputPWD(&A,&B,&C);
	  }

    SYS_doVBlankProcess();
  }

  //Free VDP tile resources
  VDP_resetScreen();

  SND_stopPlay_2ADPCM(SOUND_PCM_CH1);
  SND_stopPlay_2ADPCM(SOUND_PCM_CH2);


  Gamer->lives=3;
  Gamer->bonus=0;
  Gamer->total_score=0;
  Gamer->stage = 0;

  if(A==2 && B==2 && C==2) { Gamer->level= 2; stages(); }
  if(A==1 && B==9 && C==0) { Gamer->level= 3; stages(); }
  if(A==0 && B==5 && C==4) { Gamer->level= 4; stages(); }
  if(A==5 && B==9 && C==1) { Gamer->level= 5; stages(); }
  if(A==2 && B==6 && C==2) { Gamer->level= 6; stages(); }
  if(A==1 && B==3 && C==7) { Gamer->level= 7; stages(); }
  if(A==8 && B==4 && C==2) { Gamer->level= 8; stages(); }
  if(A==9 && B==0 && C==3) { Gamer->level= 9; stages(); }
  if(A==1 && B==0 && C==6) { Gamer->level=10; stages(); }
  if(A==2 && B==1 && C==5) { Gamer->level=11; stages(); }
  if(A==6 && B==0 && C==9) { Gamer->level=12; stages(); }
  if(A==1 && B==3 && C==3) { Gamer->level=13; stages(); }
  if(A==0 && B==4 && C==1) { Gamer->level=14; stages(); }
  if(A==0 && B==7 && C==7) { Gamer->level=15; stages(); }

  SYS_hardReset();

}

static TBOOL handleInputPWD(int *a,int *b,int *c)
{
    TBOOL RC=TRUE;

    static TBOOL event_button_A_press = FALSE;
    static TBOOL event_button_A_free  = FALSE;
    static TBOOL event_button_B_press = FALSE;
    static TBOOL event_button_B_free  = FALSE;
    static TBOOL event_button_C_press = FALSE;
    static TBOOL event_button_C_free  = FALSE;

    u16 value = JOY_readJoypad(JOY_1);

    if (value & BUTTON_START)
        {
    		RC = FALSE;
        }

    if (value & BUTTON_A)
        {
    	event_button_A_press = TRUE;
        }

    else if (value & BUTTON_B)
        {
    	event_button_B_press = TRUE;
        }

    else if (value & BUTTON_C)
        {
    	event_button_C_press = TRUE;
        }


    if ( (!(value & BUTTON_START)) && (!(value & BUTTON_A))
                                   && (!(value & BUTTON_B))
                                   && (!(value & BUTTON_C))
       )
    {
    	event_button_A_free = TRUE;
    	event_button_B_free = TRUE;
    	event_button_C_free = TRUE;
    }

    if(event_button_A_press && event_button_A_free)
    {
		if(*a < 9) *a=*a+1;
			else if (*a == 9) *a=0;

		char value[5]="";
		sprintf(value,"%d",*a);
		VDP_drawText(value,3,10);

	    event_button_A_press = FALSE;
	    event_button_A_free  = FALSE;

	    SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);

    }

    if(event_button_B_press && event_button_B_free)
    {
		if(*b < 9) *b=*b+1;
			else if (*b == 9) *b=0;

		char value[5]="";
		sprintf(value,"%d",*b);
		VDP_drawText(value,8,10);

	    event_button_B_press = FALSE;
	    event_button_B_free  = FALSE;

	    SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
    }

    if(event_button_C_press && event_button_C_free)
    {
		if(*c < 9) *c=*c+1;
			else if (*c == 9) *c=0;

		char value[5]="";
		sprintf(value,"%d",*c);
		VDP_drawText(value,12,10);

	    event_button_C_press = FALSE;
	    event_button_C_free  = FALSE;

	    SND_startPlay_2ADPCM(OBJ_MUSIC_ITEMS, sizeof(OBJ_MUSIC_ITEMS), SOUND_PCM_CH2,0);
    }


return RC;
}





