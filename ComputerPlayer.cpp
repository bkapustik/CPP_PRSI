#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(Vector2f positionOfFirstCard, shared_ptr<GraphicsHelper> graphics) : Player(positionOfFirstCard, graphics)
{

}

bool ComputerPlayer::wantsCustomTurn()
{
	return false;
}