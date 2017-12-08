#pragma once

#include <irrklang/irrKlang.h>

#include "zc_debug.h"
#include "zc_resource_manager.h"


void selectTile();

int tilesSimulSelectNr = 0;
int firstSelectionNr = -1;

void playSoundEffect(std::string soundPath, bool loop = false)
{
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	if (!engine)
	{
		std::cout << "ERROR TO INITIALIZE SOUND ENGINE" << std::endl;
		return;
	}
	if (loop)
		engine->play2D(soundPath.c_str(), true);
	else
		engine->play2D(soundPath.c_str());

	
}

void upMoveOnBoard(){
	
	if (tileSelection > 7)		tileSelection -= 8;
	//debug(tileData[tileSelection].tileContent);
	playSoundEffect("./sounds/beepSound.wav");

}

void leftMoveOnBoard(){
	if (tileSelection > 0)		tileSelection -= 1;
	playSoundEffect("./sounds/beepSound.wav");
	//debug(tileData[tileSelection].tileContent);
}

void downMoveOnBoard(){
	if (tileSelection < 56)		tileSelection += 8;
	playSoundEffect("./sounds/beepSound.wav");
	//debug(tileData[tileSelection].tileContent);
}

void rightMoveOnBoard() {
	if (tileSelection < 63)		tileSelection += 1;
	playSoundEffect("./sounds/beepSound.wav");
	//debug(tileData[tileSelection].tileContent);
}


void selectTile()
{
	tilesSimulSelectNr += 1;

	if (tilesSimulSelectNr == 1)
	{
		firstSelectionNr = tileSelection;
		tileData[firstSelectionNr].holdStatus = true;
	}
	
	if (tilesSimulSelectNr == 2)
	{
		if (tileSelection != firstSelectionNr && tileData[tileSelection].tileContent == tileData[firstSelectionNr].tileContent)
		{
			//tileData[firstSelectionNr].drawEnabled = false;
			//tileData[tileSelection].drawEnabled = false;
			tileData[firstSelectionNr].explosionStatus = true;
			tileData[tileSelection].explosionStatus = true;
			
			tileData[tileSelection].exploStartTimeAllowed = true;
			tileData[firstSelectionNr].exploStartTimeAllowed = true;

			playSoundEffect("sounds/explosionSound.wav");

		}
		else
		{
			playSoundEffect("sounds/wrongSound.mp3");
		}

		tileData[firstSelectionNr].holdStatus = false;

	
		tilesSimulSelectNr = 0;
		firstSelectionNr = -1;

		tileData[firstSelectionNr].holdStatus = false;
		tileData[tileSelection].holdStatus = false;

		
	}

	debug(tilesSimulSelectNr);
}

static bool diamond_enabled = true;