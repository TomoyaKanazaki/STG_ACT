//==========================================
//
//  入力処理(input.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//==========================================
//  マクロ定義
//==========================================
#define NUM_KEY_MAX	(256) //キーの最大値

//==========================================
//  インプットクラス
//==========================================
class CInput
{
public:
	CInput(); //コンストラクタ
	virtual ~CInput(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
	
protected:

	//メンバ変数
	LPDIRECTINPUTDEVICE8 m_pDevice;

	//静的メンバ変数
	static LPDIRECTINPUT8 m_pInput;
};

//==========================================
//  キーボードクラス
//==========================================
class CKeyboard : public CInput
{
public:
	CKeyboard(); //コンストラクタ
	~CKeyboard(); //デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR3 GetWASD(void); //WASD入力のベクトル取得
	bool GetPress(int nKey); //プレス情報の取得
	bool GetTrigger(int nKey); //トリガー情報の取得

private:

	//メンバ変数
	BYTE m_aKeyState[NUM_KEY_MAX]; //全入力情報の保管
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //トリガー情報
};

//==========================================
//  マウスクラス
//==========================================
class CMouse : public CInput
{
public:
	typedef enum
	{
		BUTTON_LEFT = 0,
		BUTTON_RIGHT,
		BUTTON_WHEEL,
		BUTTON_SIDE1,
		BUTTON_SIDE2,
		BUTTON_MAX
	}BUTTON;

	CMouse(); //コンストラクタ
	~CMouse(); //デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey); //プレス情報の取得
	bool GetTrigger(int nKey); //トリガー情報の取得
	D3DXVECTOR3 GetMouseMove(void); //マウス移動量の取得
	bool GetMouseControll(void); //マウス操作の有無を取得

private:

	//メンバ変数
	DIMOUSESTATE2 m_MouseState; //全入力情報の保管
	DIMOUSESTATE2 m_MouseStateTrigger; //トリガー情報
	bool m_bMouseMove; //マウス操作の有無
};

//==========================================
//  ジョイパッドクラス
//==========================================
class CJoyPad : public CInput
{
public:
	//ボタン
	typedef enum
	{
		KEY_X = 0,
		KEY_Y,
		KEY_A,
		KEY_B,
		KEY_LB,
		KEY_RB,
		KEY_LT,
		KEY_RT,
		KEY_L3,
		KEY_R3,
		KEY_BACK,
		KEY_START,
		KEY_MAX
	}BUTTON;

	//十字キー
	typedef enum
	{
		CROSS_UP = 0, //上方向
		CROSS_RIGHT = 9000, //右方向
		CROSS_DOWN = 18000, //下方向
		CROSS_LEFT = 27000, //左方向
		CROSS_NONE = -1 //入力がない状態の情報
	}CROSS;

	//スティック方向
	typedef enum
	{
		STICK_UP = 180, //上方向
		STICK_DOWN = 0, //下方向
		STICK_RIGHT = 90, //右方向
		STICK_LEFT = -90 //左方向
	}STICK;

	CJoyPad(); //コンストラクタ
	~CJoyPad(); //デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetJoyPadButtonPress(BUTTON nKey);
	bool GetJoyPadButtonTrigger(BUTTON nKey);
	bool GetJoyPadCrossPress(int nDirection);
	bool GetJoyPadCrossTrigger(int nDirection);
	bool GetJoyPadCrossNone(void);
	D3DXVECTOR3 GetStickL(void);
	D3DXVECTOR3 GetStickR(void);
	bool GetStickTriggerL(int nDirection);
	bool GetStickTriggerR(int nDirection);

private:

	//メンバ関数
	bool KnockStickL(DIJOYSTATE JoyKey, int nDead); //左スティックの入力判定
	bool KnockStickR(DIJOYSTATE JoyKey, int nDead); //右スティックの入力判定

	//静的
	static BOOL CALLBACK EnumJoySticksCallBack(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidInstance, VOID *pContext);

	//メンバ変数
	DIJOYSTATE m_aKeyState; //全入力情報の保管
	DIJOYSTATE m_aKeyStateTrigger; //トリガー情報
	DIJOYSTATE m_aKeyStateRerease; //リリース情報
	DIJOYSTATE m_aKeyStateRepeat; //リピート情報
	DWORD m_CrossTrigger; //十字キー専用のトリガー情報
	int m_nStickAngleL; //左スティックの角度
	int m_nStickAngleR; //右スティックの角度
	int m_nStickTriggerL; //左スティックのトリガー情報
	int m_nStickTriggerR; //右スティックのトリガー情報
};

#endif