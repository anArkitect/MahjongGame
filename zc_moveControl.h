#pragma once

#include "zc_debug.h"
#include "zc_resource_manager.h"


void selectTile();

int tilesSimulSelectNr = 0;
int firstSelectionNr = -1;

void upMoveOnBoard(){
	
	if (tileSelection > 7)		tileSelection -= 8;
	debug(tileData[tileSelection].tileContent);
}

void leftMoveOnBoard(){
	if (tileSelection > 0)		tileSelection -= 1;
	debug(tileData[tileSelection].tileContent);
}

void downMoveOnBoard(){
	if (tileSelection < 56)		tileSelection += 8;
	debug(tileData[tileSelection].tileContent);
}

void rightMoveOnBoard() {
	if (tileSelection < 63)		tileSelection += 1;
	debug(tileData[tileSelection].tileContent);
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

		}

	
		tilesSimulSelectNr = 0;
		firstSelectionNr = -1;

		tileData[firstSelectionNr].holdStatus = false;
		tileData[tileSelection].holdStatus = false;
	}

	debug(tilesSimulSelectNr);
}