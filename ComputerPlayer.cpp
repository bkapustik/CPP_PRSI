#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(const Vector2f positionOfFirstCard,const shared_ptr<GraphicsHelper> graphics) : Player(positionOfFirstCard, graphics)
{

}

bool ComputerPlayer::wantsCustomTurn() const
{
	return false;
}