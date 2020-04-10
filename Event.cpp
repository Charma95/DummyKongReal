#include "Event.h"


Event::Event( QGraphicsView *parent)
	:QGraphicsView(parent)
{

}
Event::~Event()
{
	
}
void Event::push_eventController()
{
	XController controler;
	Controller player;
	if (controler.isUpdated)
	{
		if (player.BTN_A)
		{
			emit marioJump();
		}
		if(player.BTN_X)
		{
			emit hitBarrel();
		}
		if (player.LThumbStickX < 0)
		{
			emit marioRun(LEFT);
		}
		else
		{
			emit marioRun(RIGHT);
		}
		if (player.LThumbStickY < 0)
		{
			emit goDown();
		}
		else
		{
			emit climb();
		}
	}
	else
	{
		return;
	}
}

//void Event::push_eventKeyboard(QKeyEvent *event)
//{
//		qDebug("allo");
//		// move the player left and right
//		if (event->key() == Qt::Key_A)
//		{
//			qDebug("gauche\n");
//			if (m_game.getMario()->pos().x() > 0)
//				gameWindow.marioRunLeft();
//		}
//		else if (event->key() == Qt::Key_A)
//		{
//			qDebug("Droite\n");
//			if (m_game.getMario()->pos().x() + 48 < PIX_WIDTH * MAX_WIDTH);
//			gameWindow.marioRunRight();
//		}
//		else if (event->key() == Qt::Key_Escape)
//		{
//			//emit escPressed();
//		}
//		else if (event->key() == Qt::Key_Space)
//		{
//			marioJump();
//		}
//	
//}

