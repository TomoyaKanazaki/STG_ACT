//==========================================
//
//  ���͏���(input.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//==========================================
//  �}�N����`
//==========================================
#define NUM_KEY_MAX	(256) //�L�[�̍ő�l

//==========================================
//  �C���v�b�g�N���X
//==========================================
class CInput
{
public:
	CInput(); //�R���X�g���N�^
	virtual ~CInput(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
	
protected:

	//�����o�ϐ�
	LPDIRECTINPUTDEVICE8 m_pDevice;

	//�ÓI�����o�ϐ�
	static LPDIRECTINPUT8 m_pInput;
};

//==========================================
//  �L�[�{�[�h�N���X
//==========================================
class CKeyboard : public CInput
{
public:
	CKeyboard(); //�R���X�g���N�^
	~CKeyboard(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR3 GetWASD(void); //WASD���͂̃x�N�g���擾
	bool GetPress(int nKey); //�v���X���̎擾
	bool GetTrigger(int nKey); //�g���K�[���̎擾

private:

	//�����o�ϐ�
	BYTE m_aKeyState[NUM_KEY_MAX]; //�S���͏��̕ۊ�
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //�g���K�[���
};

//==========================================
//  �}�E�X�N���X
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

	CMouse(); //�R���X�g���N�^
	~CMouse(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey); //�v���X���̎擾
	bool GetTrigger(int nKey); //�g���K�[���̎擾
	D3DXVECTOR3 GetMouseMove(void); //�}�E�X�ړ��ʂ̎擾
	bool GetMouseControll(void); //�}�E�X����̗L�����擾

private:

	//�����o�ϐ�
	DIMOUSESTATE2 m_MouseState; //�S���͏��̕ۊ�
	DIMOUSESTATE2 m_MouseStateTrigger; //�g���K�[���
	bool m_bMouseMove; //�}�E�X����̗L��
};

//==========================================
//  �W���C�p�b�h�N���X
//==========================================
class CJoyPad : public CInput
{
public:
	//�{�^��
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

	//�\���L�[
	typedef enum
	{
		CROSS_UP = 0, //�����
		CROSS_RIGHT = 9000, //�E����
		CROSS_DOWN = 18000, //������
		CROSS_LEFT = 27000, //������
		CROSS_NONE = -1 //���͂��Ȃ���Ԃ̏��
	}CROSS;

	//�X�e�B�b�N����
	typedef enum
	{
		STICK_UP = 180, //�����
		STICK_DOWN = 0, //������
		STICK_RIGHT = 90, //�E����
		STICK_LEFT = -90 //������
	}STICK;

	CJoyPad(); //�R���X�g���N�^
	~CJoyPad(); //�f�X�g���N�^

	//�����o�֐�
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

	//�����o�֐�
	bool KnockStickL(DIJOYSTATE JoyKey, int nDead); //���X�e�B�b�N�̓��͔���
	bool KnockStickR(DIJOYSTATE JoyKey, int nDead); //�E�X�e�B�b�N�̓��͔���

	//�ÓI
	static BOOL CALLBACK EnumJoySticksCallBack(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidInstance, VOID *pContext);

	//�����o�ϐ�
	DIJOYSTATE m_aKeyState; //�S���͏��̕ۊ�
	DIJOYSTATE m_aKeyStateTrigger; //�g���K�[���
	DIJOYSTATE m_aKeyStateRerease; //�����[�X���
	DIJOYSTATE m_aKeyStateRepeat; //���s�[�g���
	DWORD m_CrossTrigger; //�\���L�[��p�̃g���K�[���
	int m_nStickAngleL; //���X�e�B�b�N�̊p�x
	int m_nStickAngleR; //�E�X�e�B�b�N�̊p�x
	int m_nStickTriggerL; //���X�e�B�b�N�̃g���K�[���
	int m_nStickTriggerR; //�E�X�e�B�b�N�̃g���K�[���
};

#endif