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

#define TBOOL char
#define TBYTE unsigned char

#define   TOLERANCE                 0x00000A
#define   LEFT_LIMIT_PLAYER         0x00000A
#define   RIGHT_LIMIT_PLAYER        0x000104
#define   RIGHT_LIMIT_ENEMY         0x00012C
#define   LEFT_LIMIT_ENEMY          0x000000


//FIGHT ENGINE-------------------------------------

#define   POSITION_INIT1_FIGHT      0x000168
#define   POSITION_INIT2_FIGHT      0x000190
#define   POSITION_INIT3_FIGHT      0x0001CC
#define   POSITION_INIT4_FIGHT     -0x00001E
#define   POSITION_INIT5_FIGHT     -0x00005A
#define   POSITION_INIT6_FIGHT     -0x000078

#define   ANIM_STAND_PLAYER_FIGHT   0x000000
#define   ANIM_RUN_PLAYER_FIGHT     0x000001
#define   ANIM_KICK_PLAYER_FIGHT    0x000002
#define   ANIM_SLASH_PLAYER_FIGHT   0x000003
#define   ANIM_CHACALO_FIGHT        0x000007
#define   ANIM_MANDRILO_FIGHT       0x000004

//FELINE TANK ENGINE-------------------------------

#define   TOP_LIMIT_FTANK           0x000064
#define   DOWN_LIMIT_FTANK          0x0000C8

#define   POSITION_INIT1_FTANK      0x000168
#define   POSITION_INIT2_FTANK      0x000190
#define   POSITION_INIT3_FTANK      0x0001CC
#define   POSITION_INIT4_FTANK     -0x00001E
#define   POSITION_INIT5_FTANK     -0x00005A
#define   POSITION_INIT6_FTANK     -0x000078

#define   ANIM_STAND_PLAYER_FTANK   0x000000
#define   ANIM_RUN_PLAYER_FTANK     0x000001


//RUSH ENGINE----------------------------------------

#define   TOP_LIMIT_RUSH            0x00000A
#define   DOWN_LIMIT_RUSH           0x0000C8

#define   POSITION_INIT1_RUSH       0x000172
#define   POSITION_INIT2_RUSH       0x000190
#define   POSITION_INIT3_RUSH       0x0001CC
#define   POSITION_INIT4_RUSH      -0x000082
#define   POSITION_INIT5_RUSH      -0x0000BE
#define   POSITION_INIT6_RUSH      -0x000078

//BOSS ENGINE-----------------------------------------
#define   LEONO_ANIMATION           0x000001
#define   LEONO_ANIMATION_RUN       0x000004
#define   LEONO_ANIMATION_SLASH     0x000003
#define   LEONO_ANIMATION_KICK      0x000002
#define   MUMMRA_ANIMATION          0x000000

//EVADE ENGINE----------------------------------------

#define   TOP_LIMIT_EVADE           0x000014
#define   DOWN_LIMIT_EVADE          0x00008C

//END_BOSS ENGINE-------------------------------------

#define   LEONO_UP_ENDBOSS          0x00000A
#define   LEONO_DOWN_ENDBOSS        0x00008C
#define   LEONO_LEFT_ENDBOSS        0x000001
#define   LEONO_RIGHT_ENDBOSS       0x000104
#define   LEONO_ANIM_STAND_ENDBOSS  0x000000
#define   LEONO_ANIM_RUN_ENDBOSS    0x000001
#define   MUMMRA_ANIM_POWER_ENDBOSS 0x000005
#define   MUMMRA_HEIGHT             0x00001E


struct __stCharacter
{
    s16    x;
    s16    y;
    Sprite *graph;
    int    energy;
    int    speed;
    TBOOL  dead;
};

typedef struct __stCharacter TCHARACTER;

struct __st_system16
{
	TBOOL game_over;
	TBOOL winner;
}GLSYSTEM16;

typedef struct __st_system16 TSYSTEM16;

struct __stCanvasA
{
    s16 offset_H;
    s16 offset_V;
    int speed;
}CanvasA;

struct __stGamer
{
    int lives;
    int score;
    int bonus;
    int total_score;
    int level;
    int stage;
    int energy;
}GLGAMER;

typedef struct __stGamer TGAMER;

TSYSTEM16 *System16 = NULL;
TGAMER *Gamer = NULL;
TCHARACTER *Characters = NULL;

void updateGameInfo()
{
  char msg[60]="";

  VDP_setTextPlane(BG_B);
  //VDP_setTextPalette(2);


  sprintf(msg," LEVEL:%d  LIVES:%d  ENERGY:%d",
          Gamer->level,
          Gamer->lives,
          Gamer->energy);

  VDP_clearTextLine(1);
  VDP_drawText(msg,0,1);

  sprintf(msg," SCORE:%d",Gamer->score);

  VDP_clearTextLine(2);
  VDP_drawText(msg,0,2);

#ifdef DEBUG_GAME
  sprintf(msg,"RAM:%d FREE BYTES.",MEM_getFree());
  VDP_clearTextLine(22);
  VDP_drawText(msg,0,22);
#endif

}

void updateGameInfoEx()
{
  char msg[60]="";

  VDP_setTextPlane(BG_A);
  //VDP_setTextPalette(2);


  sprintf(msg," LEVEL:%d  LIVES:%d  ENERGY:%d",
          Gamer->level,
          Gamer->lives,
          Gamer->energy);

  VDP_drawText("                                                                                           ",0,1);
  VDP_drawText(msg,0,1);

  sprintf(msg," SCORE:%d",Gamer->score);

  VDP_drawText("                                               ",0,2);
  VDP_drawText(msg,0,2);

#ifdef DEBUG_GAME
  sprintf(msg,"RAM: %d BYTES FREE.",MEM_getFree()); //getTick()    MEM_getFree()
  VDP_drawText("                                 ",0,22);
  VDP_drawText(msg,0,22);
#endif

}

void updateGameInfoEx2(int *ee)
{
  char msg[60]="";

  VDP_setTextPlane(BG_B);
  //VDP_setTextPalette(2);

  sprintf(msg," SCORE:%d  LIVES:%d  ENERGY:%d",
          Gamer->score,
          Gamer->lives,
          Gamer->energy);

  VDP_clearTextLine(25);
  VDP_drawText(msg,0,25);

  if(ee != NULL)
  {
	  sprintf(msg," MUMM-RA ENERGY:%d",*ee);
	  VDP_clearTextLine(26);
	  VDP_drawText(msg,0,26);
  }

#ifdef DEBUG_GAME
  sprintf(msg,"RAM:%d FREE BYTES.",MEM_getFree());
  VDP_drawText("                                    ",0,18);
  VDP_drawText(msg,0,18);
#endif

}

void pause()
{
	VDP_clearTextLine(1);
	VDP_clearTextLine(2);
	VDP_drawText("        * * *  P A U S E  * * *     ",0,1);
	VDP_drawText("      Push button (C) to continue...",0,2);
	JOY_waitPress (JOY_1,BUTTON_C);
	updateGameInfo();
}

void pauseEx()
{
	VDP_setTextPlane(BG_A);
	VDP_clearTextLine(1);
	VDP_clearTextLine(2);
	VDP_drawText("        * * *  P A U S E  * * *     ",0,1);
	VDP_drawText("      Push button (C) to continue...",0,2);
	JOY_waitPress (JOY_1,BUTTON_C);
	updateGameInfoEx();
}

void pauseEx2()
{
	VDP_setTextPlane(BG_B);
	VDP_clearTextLine(25);
	VDP_drawText("        * * *  P A U S E  * * *     ",0,25);
	JOY_waitPress (JOY_1,BUTTON_C);
	updateGameInfoEx2(NULL);
}

void print_int(int value,int x, int y,char Bg)
{
  char msg[60]="";

  if(Bg == 'A')
	  VDP_setTextPlane(BG_A);
  else
	  VDP_setTextPlane(BG_B);

  //VDP_setTextPalette(2);

  sprintf(msg,"VALUE: %d",value);
  VDP_drawText("                                   ",x,y);
  VDP_drawText(msg,x,y);

}


void updateTimerInfo(int ptimer,char Bg)
{
  char msg[60]="";

  if(Bg == 'A')
	  VDP_setTextPlane(BG_A);
  else
	  VDP_setTextPlane(BG_B);

  //VDP_setTextPalette(2);

  sprintf(msg," TIME: %d",ptimer);
  VDP_drawText("            ",0,25);
  VDP_drawText(msg,0,25);

}



TBOOL fcollision(u16 x1,u16 y1,u16 x2,u16 y2)
{
	TBOOL rc=0;

	if(abs(x1-x2)<TOLERANCE && abs(y1-y2)<TOLERANCE)
		rc=1;

return rc;
}

TBOOL fcollisionEx(u16 x1,u16 y1,u16 x2,u16 y2,TBYTE Tolerance)
{
	TBOOL rc=0;

	if(abs(x1-x2)<Tolerance && abs(y1-y2)<Tolerance)
		rc=1;

return rc;
}

static void game_over();
static void game_menu();
static void password();

static void fight();
static void feline_tank();
static void rush();
static void evade();
static void stages();
static void boss();
static void quiz();
static void bingo();
static void end_boss();
static void winner();

static void fight2();
static void evade2();
static void feline_tank2();
static void rush2();
static void bingo2();
static void boss2();
static void quiz2();

static void evade3();






