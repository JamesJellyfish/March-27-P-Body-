#include "Game.h"
#include <Windows.h>
#include <mmsystem.h>
#undef main
int main()
{
	
	//Create the Game
	Game theGame;

	//Initialize the game
	theGame.InitGame();

	//Sound, put the sound file in 
	//PlaySound(TEXT("OPening_SOng.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	//PlaySound(TEXT("SoundTrack.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	//PlaySound(TEXT("Cool_song.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	//Runs the game until it returns :)
	return theGame.Run();
}