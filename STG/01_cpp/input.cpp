//==========================================
//
//  ���͏���(input.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <stdio.h>
#include "input.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//==========================================
//  �}�N����`
//==========================================
#define STICK_DEADLINE (50) //�X�e�B�b�N���͂̃f�b�h���C��
#define STICK_DEADZONE (50) //�X�e�B�b�N���͂̃f�b�h�]�[��

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
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
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
		move.y += -1.0f;
	}

	//A
	if (GetPress(DIK_A))
	{
		move.x += -1.0f;
	}

	//S
	if (GetPress(DIK_S))
	{
		move.y += 1.0f;
	}

	//D
	if (GetPress(DIK_D))
	{
		move.x += 1.0f;
	}

	//���K��
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
//  �}�E�X�̈ړ��ʎ擾
//==========================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	return D3DXVECTOR3(((float)m_MouseState.lX), ((float)m_MouseState.lY), ((float)m_MouseState.lZ));
}

//==========================================
//  �}�E�X����̗L�����擾
//==========================================
bool CMouse::GetMouseControll(void)
{
	return m_bMouseMove;
}

////==========================================
////  �W���C�p�b�h
////==========================================
////  �R���X�g���N�^
////==========================================
//CJoyPad::CJoyPad()
//{
//
//}
//
////==========================================
////  �f�X�g���N�^
////==========================================
//CJoyPad::~CJoyPad()
//{
//}
//
////==========================================
////  �f�o�C�X��񋓂��ăf�o�C�X�𐶐�����R�[���o�b�N�֐�
////==========================================
//BOOL CALLBACK CJoyPad::EnumJoySticksCallBack(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
//{
//	//���[�J���ϐ��錾
//	HRESULT hr;
//	LPDIRECTINPUTDEVICE8 pDevJoypad = m_pDevice;
//
//	//NULL�`�F�b�N
//	if (pDevJoypad != nullptr)
//	{
//		return E_FAIL;
//	}
//
//	//�f�o�C�X�̐���
//	hr = m_pInput->CreateDevice(pdidInstance->guidInstance, &pDevJoypad, NULL);
//	if (FAILED(hr))
//	{
//		return E_FAIL;
//	}
//
//	//���������ϐ�����
//	m_pDevice = pDevJoypad;
//
//	//���̃f�o�C�X�𒲂ׂ�Ƃ���DIENUM_CONTINUE�A�ŏ��̈��݂̂̏ꍇ��DIENUM_STOP
//	return DIENUM_CONTINUE;
//}
//
////==========================================
////  �\���L�[�͈̔͑I�����s���R�[���o�b�N�֐�
////==========================================
//BOOL CALLBACK CJoyPad::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidInstance, VOID *pContext)
//{
//	//���[�J���ϐ��錾(�������L���X�g���đ��)
//	LPDIRECTINPUTDEVICE8 pDevJoypad = (LPDIRECTINPUTDEVICE8)pContext;
//
//	//���͔͈͂̃Z�b�g
//	DIPROPRANGE diprg;
//	diprg.diph.dwSize = sizeof(diprg);
//	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
//	diprg.diph.dwHow = DIPH_BYOFFSET;
//	diprg.lMax = 1000;
//	diprg.lMin = -1000;
//
//	//X��
//	diprg.diph.dwObj = DIJOFS_X;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//Y��
//	diprg.diph.dwObj = DIJOFS_Y;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//Z��
//	diprg.diph.dwObj = DIJOFS_Z;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//RX��
//	diprg.diph.dwObj = DIJOFS_RX;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//RY��
//	diprg.diph.dwObj = DIJOFS_RY;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//RZ��
//	diprg.diph.dwObj = DIJOFS_RZ;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//���̃f�o�C�X�𒲂ׂ�Ƃ���DIENUM_CONTINUE�A�ŏ��̈��݂̂̏ꍇ��DIENUM_STOP
//	return DIENUM_CONTINUE;
//}
//
////==========================================
////  ����������
////==========================================
//HRESULT CJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
//{
//	//�f�o�C�X�̗�
//	HRESULT hr = m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoySticksCallBack, nullptr, DIEDFL_ATTACHEDONLY);
//	if (FAILED(hr))
//	{
//		return E_FAIL;
//	}
//
//	//���̓f�o�C�X�̐ݒ�
//	if (m_pDevice == NULL)
//	{
//		//�f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
//		hr = m_pDevice->SetDataFormat(&c_dfDIJoystick);
//		if (FAILED(hr))
//		{
//			return E_FAIL;
//		}
//
//		//�������[�h�̐ݒ�
//		hr = m_pDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
//		if (FAILED(hr))
//		{
//			return E_FAIL;
//		}
//
//		//�f�o�C�X�ɑ΂��Ă̏\���L�[�͈͓̔����w��
//		hr = m_pDevice->EnumObjects(EnumAxesCallback, m_pDevice, DIDFT_AXIS);
//		if (FAILED(hr))
//		{
//			return E_FAIL;
//		}
//	}
//
//	//�ϐ���Ԃ�
//	return S_OK;
//}
//
////==========================================
////  �I������
////==========================================
//void CJoyPad::Uninit(void)
//{
//	CInput::Uninit();
//}
//
////==========================================
////  �X�V����
////==========================================
//void CJoyPad::Update(void)
//{
//	//NULL�`�F�b�N
//	if (m_pDevice == NULL)
//	{
//		m_CrossTrigger = -1;
//		m_nStickTriggerL = 1000;
//		m_nStickTriggerR = 1000;
//	}
//
//	//�f�o�C�X����f�[�^���擾�ł��邱�Ƃ��m�F���A�ł��Ȃ������ꍇ�̓A�N�Z�X�����擾
//	HRESULT hr = m_pDevice->Poll();
//
//	if (FAILED(hr))
//	{
//		hr = m_pDevice->Acquire();
//		while (hr == DIERR_INPUTLOST)
//		{
//			hr = m_pDevice->Acquire();
//		}
//	}
//
//	//�ꎞ�ۊǏꏊ
//	DIJOYSTATE JoyKey;
//
//	//�R���g���[���̏�Ԃ��擾
//	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(JoyKey), &JoyKey)))
//	{
//		//�e�{�^���̏�񐮗�
//		for (int nCntKey = 0; nCntKey < 32; nCntKey++)
//		{
//			//�g���K�[���̕ۑ�
//			m_aKeyStateTrigger.rgbButtons[nCntKey]
//				= (m_aKeyState.rgbButtons[nCntKey] ^ JoyKey.rgbButtons[nCntKey]) & JoyKey.rgbButtons[nCntKey];
//
//			//�v���X���̕ۑ�
//			m_aKeyState.rgbButtons[nCntKey] = JoyKey.rgbButtons[nCntKey];
//		}
//
//		//�\���{�^���̃g���K�[����ۑ�
//		if (m_aKeyState.rgdwPOV[0] != JoyKey.rgdwPOV[0])
//		{
//			m_CrossTrigger = JoyKey.rgdwPOV[0];
//		}
//		else
//		{
//			m_CrossTrigger = -1;
//		}
//
//		//�X�e�B�b�N�̊p�x��ۑ�
//		m_nStickAngleL = (int)D3DXToDegree(atan2f((float)JoyKey.lX, (float)JoyKey.lY));
//		m_nStickAngleR = (int)D3DXToDegree(atan2f((float)JoyKey.lZ, (float)JoyKey.lRz));
//
//		//�X�e�B�b�N�̃g���K�[�������Z�b�g
//		m_nStickTriggerL = 1000;
//		m_nStickTriggerR = 1000;
//
//		//�X�e�B�b�N�̃g���K�[����ۑ�
//		if (KnockStickL(JoyKey, STICK_DEADLINE)) //��
//		{
//			m_nStickTriggerL = m_nStickAngleL;
//		}
//		if (KnockStickR(JoyKey, STICK_DEADLINE)) //�E
//		{
//			m_nStickTriggerR = m_nStickAngleR;
//		}
//
//		//���͏��̕ۑ�
//		m_aKeyState = JoyKey;
//	}
//}
//
////==========================================
////  �{�^���̃v���X���̎擾
////==========================================
//bool CJoyPad::GetJoyPadButtonPress(BUTTON nKey)
//{
//	return (m_aKeyState.rgbButtons[nKey] & 0x80) ? true : false;
//}
//
////==========================================
////  �{�^���̃g���K�[���̎擾
////==========================================
//bool CJoyPad::GetJoyPadButtonTrigger(BUTTON nKey)
//{
//	return (m_aKeyStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
//}
//
////==========================================
////  �\���L�[�̃v���X���̎擾
////==========================================
//bool CJoyPad::GetJoyPadCrossPress(int nDirection)
//{
//	return ((m_aKeyState.rgdwPOV[0] - nDirection) == 0) ? true : false;
//}
//
////==========================================
////  �\���L�[�̃g���K�[���̎擾
////==========================================
//bool CJoyPad::GetJoyPadCrossTrigger(int nDirection)
//{
//	return ((m_CrossTrigger - nDirection) == 0) ? true : false;
//}
//
////==========================================
////  �\���L�[�̓��͔���
////==========================================
//bool CJoyPad::GetJoyPadCrossNone(void)
//{
//	return (m_CrossTrigger == -1) ? true : false;
//}
//
////==========================================
////  �X�e�B�b�N�̔���
////==========================================
//D3DXVECTOR3 CJoyPad::GetStickL(void) //��
//{
//	//���[�J���ϐ��錾
//	D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	//�Ԃ�l�̐ݒ�
//	stick.x = (float)m_aKeyState.lX / 1000.0f;
//	stick.y = (float)m_aKeyState.lY / 1000.0f;
//
//	//�ϐ���Ԃ�
//	return stick;
//}
//
//D3DXVECTOR3 CJoyPad::GetStickR(void) //�E
//{
//	//���[�J���ϐ��錾
//	D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	//�Ԃ�l�̐ݒ�
//	stick.x = (float)m_aKeyState.lZ / 1000.0f;
//	stick.y = (float)m_aKeyState.lRz / 1000.0f;
//
//	//�ϐ���Ԃ�
//	return stick;
//}
//
////==========================================
////  �X�e�B�b�N�̃g���K�[�擾
////==========================================
//bool CJoyPad::GetStickTriggerL(int nDirection) //��
//{
//	return abs(m_nStickTriggerL - nDirection) < 45 ? true : false;
//}
//
//bool CJoyPad::GetStickTriggerR(int nDirection) //�E
//{
//	return abs(m_nStickTriggerR - nDirection) < 45 ? true : false;
//}
//
////==========================================
////  �X�e�B�b�N�̓��͔���
////==========================================
//bool CJoyPad::KnockStickL(DIJOYSTATE JoyKey, int nDead) //��
//{
//	//���[�J���ϐ��錾
//	bool bJudg = false;
//
//	//�O����͂̔���
//	if (abs(m_aKeyState.lX) <= nDead && abs(m_aKeyState.lY) <= nDead)
//	{
//		//������͂̔���
//		if (abs(JoyKey.lX) >= nDead + STICK_DEADZONE || abs(JoyKey.lY) >= nDead + STICK_DEADZONE)
//		{
//			bJudg = true;
//		}
//	}
//
//	//�ϐ���Ԃ�
//	return bJudg;
//}
//
//bool CJoyPad::KnockStickR(DIJOYSTATE JoyKey, int nDead) //�E
//{
//	//���[�J���ϐ��錾
//	bool bJudg = false;
//
//	//�O����͂̔���
//	if (abs(m_aKeyState.lZ) <= nDead && abs(m_aKeyState.lRz) <= nDead)
//	{
//		//������͂̔���
//		if (abs(JoyKey.lZ) >= nDead + STICK_DEADZONE || abs(JoyKey.lRz) >= nDead + STICK_DEADZONE)
//		{
//			bJudg = true;
//		}
//	}
//
//	//�ϐ���Ԃ�
//	return bJudg;
//}
