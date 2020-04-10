#include "XController.h"
#include <Xinput.h>
#pragma comment(lib,"Xinput.lib") /* Don't erase that line, it might fuck up erraything */


XController::XController()
{
	/* Initialize value for buttons and joystick*/
	player =
	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
}
XController:: ~XController()
{

} 

void XController::readController()
{
	A_ButtonPressed();
	B_ButtonPressed();
	X_ButtonPressed();
	Y_ButtonPressed();
	START_ButtonPressed();
	leftTrigger();
	rightTrigger();
	rJoyStick();
	lJoyStick();
}
/* this method will be called in the timer callback*/
void XController::updateController()
{
	readController();
	system("cls");
	isUpdated = true;
	std::cout << player << std::endl;
}

Controller XController::getPlayer()
{
	return player;
}

void XController::getUserInput()
{

	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
		{
			controllerId = i;
			std::cout << "Controller is connected in port : " << i << std::endl;
		}
	}
}

XINPUT_STATE XController::GetState()
{
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	XInputGetState(controllerId, &state);
	return state;
}

void XController::A_ButtonPressed()
{
	player.BTN_A = ((GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
}

void XController::B_ButtonPressed()
{
	player.BTN_B = ((GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
}
void XController::X_ButtonPressed()
{
	player.BTN_X = ((GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
}
void XController::Y_ButtonPressed()
{
	player.BTN_Y = ((GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
}

void XController::START_ButtonPressed()
{
	player.BTN_START = ((GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
}

void XController::leftTrigger()
{
	player.left_Trigger = (int)(GetState().Gamepad.bLeftTrigger / 255);
}

void XController::rightTrigger()
{
	player.right_Trigger = (int)(GetState().Gamepad.bRightTrigger / 255);
}

void XController::rJoyStick()
{
	player.RThumbStickX = (int)fmaxf(-1, (float)GetState().Gamepad.sThumbRX / 32767);
	player.RThumbStickY = (int)fmaxf(-1, (float)GetState().Gamepad.sThumbRY / 32767);
}

void XController::lJoyStick()
{
	player.LThumbStickX = (int)fmaxf(-1, (float)GetState().Gamepad.sThumbLX / 32767);
	player.LThumbStickY = (int)fmaxf(-1, (float)GetState().Gamepad.sThumbLY / 32767);
}

std::ostream& operator<<(std::ostream &os, const struct Controller& player)
{
	os << "Bouton A: " << player.BTN_A <<std::endl;
	os << "Bouton B: " << player.BTN_B << std::endl;
	os << "Bouton X: " << player.BTN_X << std::endl;
	os << "Bouton Y: " << player.BTN_Y << std::endl;
	os << "George stick Gauche X: " << player.LThumbStickX << std::endl;
	os << "George stick Gauche Y: " << player.LThumbStickY << std::endl;
	os << "George stick Droite X: " << player.RThumbStickX << std::endl;
	os << "George stick Droite Y: " << player.RThumbStickY << std::endl;
	os << "Gachette gauche: " << player.left_Trigger << std::endl;
	os << "Gachette droite: " << player.right_Trigger << std::endl;
	return os;
}

