//==========================================
//
//  入力処理(input.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <stdio.h>
#include "input.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//==========================================
//  マクロ定義
//==========================================
#define STICK_DEADLINE (50) //スティック入力のデッドライン
#define STICK_DEADZONE (50) //スティック入力のデッドゾーン

//==========================================
//  コンストラクタ
//==========================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//==========================================
//  デストラクタ
//==========================================
CInput::~CInput()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
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
//  終了処理
//==========================================
void CInput::Uninit(void)
{
	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	//入力デバイスの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//==========================================
//  キーボード
//==========================================
//  コンストラクタ
//==========================================
CKeyboard::CKeyboard()
{

}

//==========================================
//  デストラクタ
//==========================================
CKeyboard::~CKeyboard()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//オブジェクト生成
	CInput::Init(hInstance, hWnd);

	//入力デバイスの設定
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CKeyboard::Update(void)
{
	//ローカル変数宣言
	BYTE aKeyState[NUM_KEY_MAX]; //キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //キーボードのトリガー情報の保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報の保存
		}
	}
	else
	{
		m_pDevice->Acquire(); //キーボードのアクセス権
	}
}

//==========================================
//  WASD入力
//==========================================
D3DXVECTOR3 CKeyboard::GetWASD(void)
{
	//ローカル変数宣言
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

	//正規化
	D3DXVec3Normalize(&move, &move);

	return move;
}

//==========================================
//  プレス情報の取得
//==========================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//==========================================
//  トリガー情報の取得
//==========================================
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//==========================================
//  マウス
//==========================================
//  コンストラクタ
//==========================================
CMouse::CMouse()
{

}

//==========================================
//  デストラクタ
//==========================================
CMouse::~CMouse()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//入力デバイスの設定
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel
	(
		hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
	)))
	{
		return E_FAIL;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; //相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return E_FAIL;
	}

	//マウスへのアクセス権を取得
	m_pDevice->Acquire();

	//マウスカーソルの消去
	//ShowCursor(false);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CMouse::Update(void)
{
	//ローカル変数宣言
	DIMOUSESTATE2 mouse;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(mouse), &mouse)))
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			//トリガー情報の保存
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

		//入力情報の保存
		m_MouseState = mouse;
	}
	else
	{
		m_pDevice->Acquire(); //マウスへのアクセス権
	}
}

//==========================================
//  プレス情報
//==========================================
bool CMouse::GetPress(int nKey)
{
	return (m_MouseState.rgbButtons[nKey] & 0x80) != 0;
}

//==========================================
//  トリガー情報
//==========================================
bool CMouse::GetTrigger(int nKey)
{
	return (m_MouseStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================
//  マウスの移動量取得
//==========================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	return D3DXVECTOR3(((float)m_MouseState.lX), ((float)m_MouseState.lY), ((float)m_MouseState.lZ));
}

//==========================================
//  マウス操作の有無を取得
//==========================================
bool CMouse::GetMouseControll(void)
{
	return m_bMouseMove;
}

////==========================================
////  ジョイパッド
////==========================================
////  コンストラクタ
////==========================================
//CJoyPad::CJoyPad()
//{
//
//}
//
////==========================================
////  デストラクタ
////==========================================
//CJoyPad::~CJoyPad()
//{
//}
//
////==========================================
////  デバイスを列挙してデバイスを生成するコールバック関数
////==========================================
//BOOL CALLBACK CJoyPad::EnumJoySticksCallBack(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
//{
//	//ローカル変数宣言
//	HRESULT hr;
//	LPDIRECTINPUTDEVICE8 pDevJoypad = m_pDevice;
//
//	//NULLチェック
//	if (pDevJoypad != nullptr)
//	{
//		return E_FAIL;
//	}
//
//	//デバイスの生成
//	hr = m_pInput->CreateDevice(pdidInstance->guidInstance, &pDevJoypad, NULL);
//	if (FAILED(hr))
//	{
//		return E_FAIL;
//	}
//
//	//生成した変数を代入
//	m_pDevice = pDevJoypad;
//
//	//次のデバイスを調べるときはDIENUM_CONTINUE、最初の一回のみの場合はDIENUM_STOP
//	return DIENUM_CONTINUE;
//}
//
////==========================================
////  十字キーの範囲選択を行うコールバック関数
////==========================================
//BOOL CALLBACK CJoyPad::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidInstance, VOID *pContext)
//{
//	//ローカル変数宣言(引数をキャストして代入)
//	LPDIRECTINPUTDEVICE8 pDevJoypad = (LPDIRECTINPUTDEVICE8)pContext;
//
//	//入力範囲のセット
//	DIPROPRANGE diprg;
//	diprg.diph.dwSize = sizeof(diprg);
//	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
//	diprg.diph.dwHow = DIPH_BYOFFSET;
//	diprg.lMax = 1000;
//	diprg.lMin = -1000;
//
//	//X軸
//	diprg.diph.dwObj = DIJOFS_X;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//Y軸
//	diprg.diph.dwObj = DIJOFS_Y;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//Z軸
//	diprg.diph.dwObj = DIJOFS_Z;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//RX軸
//	diprg.diph.dwObj = DIJOFS_RX;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//RY軸
//	diprg.diph.dwObj = DIJOFS_RY;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//RZ軸
//	diprg.diph.dwObj = DIJOFS_RZ;
//	pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//	//次のデバイスを調べるときはDIENUM_CONTINUE、最初の一回のみの場合はDIENUM_STOP
//	return DIENUM_CONTINUE;
//}
//
////==========================================
////  初期化処理
////==========================================
//HRESULT CJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
//{
//	//デバイスの列挙
//	HRESULT hr = m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoySticksCallBack, nullptr, DIEDFL_ATTACHEDONLY);
//	if (FAILED(hr))
//	{
//		return E_FAIL;
//	}
//
//	//入力デバイスの設定
//	if (m_pDevice == NULL)
//	{
//		//デバイスのフォーマットの設定
//		hr = m_pDevice->SetDataFormat(&c_dfDIJoystick);
//		if (FAILED(hr))
//		{
//			return E_FAIL;
//		}
//
//		//協調モードの設定
//		hr = m_pDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
//		if (FAILED(hr))
//		{
//			return E_FAIL;
//		}
//
//		//デバイスに対しての十字キーの範囲等を指定
//		hr = m_pDevice->EnumObjects(EnumAxesCallback, m_pDevice, DIDFT_AXIS);
//		if (FAILED(hr))
//		{
//			return E_FAIL;
//		}
//	}
//
//	//変数を返す
//	return S_OK;
//}
//
////==========================================
////  終了処理
////==========================================
//void CJoyPad::Uninit(void)
//{
//	CInput::Uninit();
//}
//
////==========================================
////  更新処理
////==========================================
//void CJoyPad::Update(void)
//{
//	//NULLチェック
//	if (m_pDevice == NULL)
//	{
//		m_CrossTrigger = -1;
//		m_nStickTriggerL = 1000;
//		m_nStickTriggerR = 1000;
//	}
//
//	//デバイスからデータを取得できることを確認し、できなかった場合はアクセス権が取得
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
//	//一時保管場所
//	DIJOYSTATE JoyKey;
//
//	//コントローラの状態を取得
//	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(JoyKey), &JoyKey)))
//	{
//		//各ボタンの情報整理
//		for (int nCntKey = 0; nCntKey < 32; nCntKey++)
//		{
//			//トリガー情報の保存
//			m_aKeyStateTrigger.rgbButtons[nCntKey]
//				= (m_aKeyState.rgbButtons[nCntKey] ^ JoyKey.rgbButtons[nCntKey]) & JoyKey.rgbButtons[nCntKey];
//
//			//プレス情報の保存
//			m_aKeyState.rgbButtons[nCntKey] = JoyKey.rgbButtons[nCntKey];
//		}
//
//		//十字ボタンのトリガー情報を保存
//		if (m_aKeyState.rgdwPOV[0] != JoyKey.rgdwPOV[0])
//		{
//			m_CrossTrigger = JoyKey.rgdwPOV[0];
//		}
//		else
//		{
//			m_CrossTrigger = -1;
//		}
//
//		//スティックの角度を保存
//		m_nStickAngleL = (int)D3DXToDegree(atan2f((float)JoyKey.lX, (float)JoyKey.lY));
//		m_nStickAngleR = (int)D3DXToDegree(atan2f((float)JoyKey.lZ, (float)JoyKey.lRz));
//
//		//スティックのトリガー情報をリセット
//		m_nStickTriggerL = 1000;
//		m_nStickTriggerR = 1000;
//
//		//スティックのトリガー情報を保存
//		if (KnockStickL(JoyKey, STICK_DEADLINE)) //左
//		{
//			m_nStickTriggerL = m_nStickAngleL;
//		}
//		if (KnockStickR(JoyKey, STICK_DEADLINE)) //右
//		{
//			m_nStickTriggerR = m_nStickAngleR;
//		}
//
//		//入力情報の保存
//		m_aKeyState = JoyKey;
//	}
//}
//
////==========================================
////  ボタンのプレス情報の取得
////==========================================
//bool CJoyPad::GetJoyPadButtonPress(BUTTON nKey)
//{
//	return (m_aKeyState.rgbButtons[nKey] & 0x80) ? true : false;
//}
//
////==========================================
////  ボタンのトリガー情報の取得
////==========================================
//bool CJoyPad::GetJoyPadButtonTrigger(BUTTON nKey)
//{
//	return (m_aKeyStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
//}
//
////==========================================
////  十字キーのプレス情報の取得
////==========================================
//bool CJoyPad::GetJoyPadCrossPress(int nDirection)
//{
//	return ((m_aKeyState.rgdwPOV[0] - nDirection) == 0) ? true : false;
//}
//
////==========================================
////  十字キーのトリガー情報の取得
////==========================================
//bool CJoyPad::GetJoyPadCrossTrigger(int nDirection)
//{
//	return ((m_CrossTrigger - nDirection) == 0) ? true : false;
//}
//
////==========================================
////  十字キーの入力判定
////==========================================
//bool CJoyPad::GetJoyPadCrossNone(void)
//{
//	return (m_CrossTrigger == -1) ? true : false;
//}
//
////==========================================
////  スティックの判定
////==========================================
//D3DXVECTOR3 CJoyPad::GetStickL(void) //左
//{
//	//ローカル変数宣言
//	D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	//返り値の設定
//	stick.x = (float)m_aKeyState.lX / 1000.0f;
//	stick.y = (float)m_aKeyState.lY / 1000.0f;
//
//	//変数を返す
//	return stick;
//}
//
//D3DXVECTOR3 CJoyPad::GetStickR(void) //右
//{
//	//ローカル変数宣言
//	D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	//返り値の設定
//	stick.x = (float)m_aKeyState.lZ / 1000.0f;
//	stick.y = (float)m_aKeyState.lRz / 1000.0f;
//
//	//変数を返す
//	return stick;
//}
//
////==========================================
////  スティックのトリガー取得
////==========================================
//bool CJoyPad::GetStickTriggerL(int nDirection) //左
//{
//	return abs(m_nStickTriggerL - nDirection) < 45 ? true : false;
//}
//
//bool CJoyPad::GetStickTriggerR(int nDirection) //右
//{
//	return abs(m_nStickTriggerR - nDirection) < 45 ? true : false;
//}
//
////==========================================
////  スティックの入力判定
////==========================================
//bool CJoyPad::KnockStickL(DIJOYSTATE JoyKey, int nDead) //左
//{
//	//ローカル変数宣言
//	bool bJudg = false;
//
//	//前回入力の判定
//	if (abs(m_aKeyState.lX) <= nDead && abs(m_aKeyState.lY) <= nDead)
//	{
//		//今回入力の判定
//		if (abs(JoyKey.lX) >= nDead + STICK_DEADZONE || abs(JoyKey.lY) >= nDead + STICK_DEADZONE)
//		{
//			bJudg = true;
//		}
//	}
//
//	//変数を返す
//	return bJudg;
//}
//
//bool CJoyPad::KnockStickR(DIJOYSTATE JoyKey, int nDead) //右
//{
//	//ローカル変数宣言
//	bool bJudg = false;
//
//	//前回入力の判定
//	if (abs(m_aKeyState.lZ) <= nDead && abs(m_aKeyState.lRz) <= nDead)
//	{
//		//今回入力の判定
//		if (abs(JoyKey.lZ) >= nDead + STICK_DEADZONE || abs(JoyKey.lRz) >= nDead + STICK_DEADZONE)
//		{
//			bJudg = true;
//		}
//	}
//
//	//変数を返す
//	return bJudg;
//}
