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
#include <string.h>
#include "KDebug.h"
#include "tools.h"
#include "timer.h"
#include "sys.h"


//#define DEBUG_GAME
#define RELEASE_GAME

//#define THUNDERCATS_NTSC
//#define THUNDERCATS_PAL

#include "pictures.h"
#include "music.h"
#include "sprites.h"

#include "global.h"
#include "sega.h"

#include "game_over.h"
#include "game_menu.h"
#include "fight.h"
#include "fight2.h"
#include "feline_tank.h"
#include "feline_tank2.h"
#include "rush.h"
#include "rush2.h"
#include "evade.h"
#include "evade2.h"
#include "evade3.h"
#include "stages.h"
#include "boss.h"
#include "boss2.h"
#include "quiz.h"
#include "quiz2.h"
#include "bingo.h"
#include "bingo2.h"
#include "end_boss.h"
#include "winner.h"
#include "password.h"

int main()
{

#ifdef DEBUG_GAME
  KDebug_Alert("Init VDP chipset...");
  KDebug_Alert("Init 320x224 size of screen.");
#endif


  VDP_init();
  VDP_setScreenWidth320();

#ifdef THUNDERCATS_NTSC
  if(!SYS_isNTSC())
  {
	  VDP_drawText("      THIS GAME IS FOR NTSC TV.",1,10);
	  while(TRUE){}
  }
#endif

#ifdef THUNDERCATS_PAL
  if(!SYS_isPAL())
  {
	  VDP_drawText("       THIS GAME IS FOR PAL TV.",1,10);
	  while(TRUE){}
  }
#endif


  Characters = NULL;

  SEGA();
  game_menu();

 return 0;
}


