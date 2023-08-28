//==========================================
//
//  ���͏���(input.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <stdio.h>
#include "input.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;
int CJoyPad::m_nNum = 0;

//==========================================
//  �}�N����`
//==========================================
#define STICK_DEADLINE (50) //�X�e�B�b�N���͂̃f�b�h���C��
#define STICK_DEADZONE (50) //�X�e�B�b�N���͂̃f�b�h�]�[��
#define MOUSE_MOVE (0.001f) //�}�E�X�̔{��

//==========================================
//  �R���X�g���N�^
//==========================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CInput::~CInput()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND /*hWnd*/)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create
		(
			hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_pInput,
			NULL
		)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CInput::Uninit(void)
{
	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	//���̓f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//==========================================
//  �L�[�{�[�h
//==========================================
//  �R���X�g���N�^
//==========================================
CKeyboard::CKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = NULL;
		m_aKeyStateTrigger[nCnt] = NULL;
	}
}

//==========================================
//  �f�X�g���N�^
//==========================================
CKeyboard::~CKeyboard()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�I�u�W�F�N�g����
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�̐ݒ�
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CKeyboard::Update(void)
{
	//���[�J���ϐ��錾
	BYTE aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�L�[�{�[�h�̃g���K�[���̕ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h�̃v���X���̕ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire(); //�L�[�{�[�h�̃A�N�Z�X��
	}
}

//==========================================
//  WASD����
//==========================================
D3DXVECTOR3 CKeyboard::GetWASD(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//W
	if (GetPress(DIK_W))
	{
		move.z += -1.0f;
	}

	//A
	if (GetPress(DIK_A))
	{
		move.x += 1.0f;
	}

	//S
	if (GetPress(DIK_S))
	{
		move.z += 1.0f;
	}

	//D
	if (GetPress(DIK_D))
	{
		move.x += -1.0f;
	}

	//�x�N�g���̐��K��
	D3DXVec3Normalize(&move, &move);

	return move;
}

//==========================================
//  �v���X���̎擾
//==========================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//==========================================
//  �g���K�[���̎擾
//==========================================
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//==========================================
//  �}�E�X
//==========================================
//  �R���X�g���N�^
//==========================================
CMouse::CMouse()
{
	m_MouseState = {};
	m_MouseStateTrigger = {};
}

//==========================================
//  �f�X�g���N�^
//==========================================
CMouse::~CMouse()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�ϐ���ۑ�
	m_hWnd = hWnd;

	//�I�u�W�F�N�g����
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�̐ݒ�
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel
	(
		hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
	)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; //���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X�����擾
	m_pDevice->Acquire();

	//�}�E�X�J�[�\���̏���
	//ShowCursor(false);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CMouse::Update(void)
{
	//���[�J���ϐ��錾
	DIMOUSESTATE2 mouse;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(mouse), &mouse)))
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			//�g���K�[���̕ۑ�
			m_MouseStateTrigger.rgbButtons[nCnt] = (m_MouseState.rgbButtons[nCnt] ^ mouse.rgbButtons[nCnt]) & mouse.rgbButtons[nCnt];

			//�����[�X���̕ۑ�
			m_MouseStateRelease.rgbButtons[nCnt] = (mouse.rgbButtons[nCnt] ^ m_MouseState.rgbButtons[nCnt]) & m_MouseState.rgbButtons[nCnt];
		}

		if (m_MouseState.lX != mouse.lX || m_MouseState.lY != mouse.lY)
		{
			m_bMouseMove = true;
		}
		else
		{
			m_bMouseMove = false;
		}

		//���͏��̕ۑ�
		m_MouseState = mouse;
	}
	else
	{
		m_pDevice->Acquire(); //�}�E�X�ւ̃A�N�Z�X��
	}
}

//==========================================
//  �X�N���[����ɂ�����}�E�X�̎擾
//==========================================
D3DXVECTOR2 CMouse::GetCursor(void)
{
	//�J�[�\���ʒu�̎擾
	POINT CursorPos;
	if (GetCursorPos(&CursorPos))
	{
		//��l���X�N���[���̒��S�ɐݒ肷��
		CursorPos.x -= GetSystemMetrics(SM_CXSCREEN) / 2;
		CursorPos.y -= GetSystemMetrics(SM_CYSCREEN) / 2;

		//�X�N���[�����W���E�B���h�E���W�ɕϊ�����
		ScreenToClient(m_hWnd, &CursorPos);
	}

	//�l��Ԃ�
	return D3DXVECTOR2((float)CursorPos.x, (float)CursorPos.y);
}

//==========================================
//  �v���X���
//==========================================
bool CMouse::GetPress(int nKey)
{
	return (m_MouseState.rgbButtons[nKey] & 0x80) != 0;
}

//==========================================
//  �g���K�[���
//==========================================
bool CMouse::GetTrigger(int nKey)
{
	return (m_MouseStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================
//  �����[�X���
//==========================================
bool CMouse::GetRelease(int nKey)
{
	return (m_MouseStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================
//  �}�E�X�̈ړ��ʎ擾
//==========================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	return D3DXVECTOR3(((float)m_MouseState.lX) * -MOUSE_MOVE, 0.0f, ((float)m_MouseState.lY) * -MOUSE_MOVE);
}

//==========================================
//  �}�E�X����̗L�����擾
//==========================================
bool CMouse::GetMouseControll(void)
{
	return m_bMouseMove;
}

//==========================================
//  �W���C�p�b�h
//==========================================
//  �R���X�g���N�^
//==========================================
CJoyPad::CJoyPad()
{
	//XINPUT_STATE m_JoyKeyState = {};
	//XINPUT_STATE m_JoyKeyTrigger = {};
	//XINPUT_VIBRATION m_Vibration = {};
	//VIBRATION m_VibrationState = VIBRATIONSTATE_NONE;
	//int m_VibrationTimer = 0;
	//int m_nIdx = m_nNum;

	//�g�p�������Z����
	m_nNum++;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CJoyPad::~CJoyPad()
{
	//�g�p�������Z����
	m_nNum--;
}

//==========================================
//  ����������
//==========================================
HRESULT CJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//XInput�̃X�e�[�g��ݒ�(�L����)
	XInputEnable(true);

	//�������N���A
	memset(&m_JoyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_JoyKeyTrigger, 0, sizeof(XINPUT_STATE));
	memset(&m_Vibration, 0, sizeof(XINPUT_VIBRATION));

	if (XInputGetState(m_nIdx, &m_JoyKeyState) == ERROR_SUCCESS)
	{
		return S_OK;
	}

	return E_FAIL;
}

//==========================================
//  �I������
//==========================================
void CJoyPad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�(������)
	XInputEnable(false);

	CInput::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CJoyPad::Update(void)
{
	//���[�J���ϐ��錾
	XINPUT_STATE JoyKeyState; //�W���C�p�b�h���͏��

	//�W���C�p�b�h�̏�Ԃ̎擾
	if (XInputGetState(m_nIdx, &JoyKeyState) == ERROR_SUCCESS)
	{
		//�g���K�[����ۑ�
		m_JoyKeyTrigger.Gamepad.wButtons
			= ~m_JoyKeyState.Gamepad.wButtons
			& JoyKeyState.Gamepad.wButtons;

		//�v���X����
		m_JoyKeyState = JoyKeyState;

		//�o�C�u����
		if (m_VibrationState != VIBRATIONSTATE_NONE)
		{
			//�o�C�u��Ԃ̍X�V
			switch (m_VibrationState)
			{
			case VIBRATIONSTATE_PLAYER_EXPLOSION:
				m_Vibration.wLeftMotorSpeed -= (short)(USHRT_MAX * 0.01f);
				m_Vibration.wRightMotorSpeed -= (short)(USHRT_MAX * 0.01f);
				break;
			case VIBRATIONSTATE_ENEMY_EXPLOSION:
				m_Vibration.wLeftMotorSpeed = (m_Vibration.wLeftMotorSpeed == USHRT_MAX / 2) ? USHRT_MAX : USHRT_MAX / 2;
				m_Vibration.wRightMotorSpeed = (m_Vibration.wRightMotorSpeed == USHRT_MAX / 2) ? USHRT_MAX : USHRT_MAX / 2;
				break;
			default:
				break;
			}

			//�o�C�u���̒l��␳����
			if (m_Vibration.wLeftMotorSpeed < 0)
			{
				m_Vibration.wLeftMotorSpeed = 0;
			}
			if (m_Vibration.wRightMotorSpeed < 0)
			{
				m_Vibration.wRightMotorSpeed = 0;
			}

			//�o�C�u���Ԃ̍X�V
			m_VibrationTimer--;

			//�o�C�u��Ԃ̃��Z�b�g
			if (m_VibrationTimer == 0)
			{
				m_VibrationState = VIBRATIONSTATE_NONE;
			}
		}
		else
		{
			memset(&m_Vibration, 0, sizeof(XINPUT_VIBRATION));
		}

		//�o�C�u�����W���C�p�b�h�ɑ��M
		XInputSetState(m_nIdx, &m_Vibration);
	}
}

//==========================================
//  �W���C�p�b�h�̃v���X���̎擾
//==========================================
bool CJoyPad::GetPress(JOYKEY Key)
{
	return (m_JoyKeyState.Gamepad.wButtons & (0x01 << Key)) != 0;
}

//==========================================
//  �W���C�p�b�h�̃g���K�[���̎擾
//==========================================
bool CJoyPad::GetTrigger(JOYKEY Key)
{
	return (m_JoyKeyTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//==========================================
//  �W���C�p�b�h��LT/RT�̃v���X
//==========================================
bool CJoyPad::GetLTRT(JOYKEY key, int Pedal)
{
	//���[�J���ϐ�
	int nKeep = 0;

	switch (key)
	{
	case BUTTON_LT:
		nKeep = (int)m_JoyKeyState.Gamepad.bLeftTrigger;
		break;
	case BUTTON_RT:
		nKeep = (int)m_JoyKeyState.Gamepad.bRightTrigger;
		break;
	default:
		break;
	}

	//�ϐ���Ԃ�
	if (nKeep >= Pedal)
	{
		return true;
	}
	return false;
}

//==========================================
//  �W���C�p�b�h��L�X�e�B�b�N���(D3DXVECTOR3)
//==========================================
D3DXVECTOR3 CJoyPad::GetStickL(float Dead)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)m_JoyKeyState.Gamepad.sThumbLX / SHRT_MAX;
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.y = (float)m_JoyKeyState.Gamepad.sThumbLY / SHRT_MAX;
	if (fabsf(Stick.y) < Dead)
	{
		Stick.y = 0.0f;
	}
	Stick.y *= -1;

	return Stick;
}
//==========================================
//  �W���C�p�b�h��R�X�e�B�b�N���(D3DXVECTOR3)
//==========================================
D3DXVECTOR3 CJoyPad::GetStickR(float Dead)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)m_JoyKeyState.Gamepad.sThumbRX / SHRT_MAX;
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.y = (float)m_JoyKeyState.Gamepad.sThumbRY / SHRT_MAX;
	if (fabsf(Stick.y) < Dead)
	{
		Stick.y = 0.0f;
	}
	Stick.y *= -1;

	return Stick;
}

//==========================================
//  �o�C�u���[�V�����@�\
//==========================================
void CJoyPad::VibrationJoyPad(VIBRATION VibrationState)
{
	//�o�C�u��Ԃ̐ݒ�
	m_VibrationState = VibrationState;

	//�o�C�u���[�V�����̐ݒ�
	switch (m_VibrationState)
	{
	case VIBRATIONSTATE_PLAYER_EXPLOSION:
		m_Vibration.wLeftMotorSpeed = USHRT_MAX;
		m_Vibration.wRightMotorSpeed = USHRT_MAX;
		m_VibrationTimer = 100;
		break;
	case VIBRATIONSTATE_ENEMY_EXPLOSION:
		m_Vibration.wLeftMotorSpeed = USHRT_MAX / 2;
		m_Vibration.wRightMotorSpeed = USHRT_MAX / 2;
		m_VibrationTimer = 100;
		break;
	default:
		assert(false);
		break;
	}

	//�o�C�u�����W���C�p�b�h�ɑ��M
	XInputSetState(m_nIdx, &m_Vibration);
}
