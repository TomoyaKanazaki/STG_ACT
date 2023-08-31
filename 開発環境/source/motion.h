//==========================================
//
//  モーションクラス(motion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"

//==========================================
//  前方宣言
//==========================================
class CModel;

//==========================================
//  モーションクラス定義
//==========================================
class CMotion
{
public:
	typedef enum
	{
		PLAYER_SHOT = 0, //弾を撃つ
		MOTION_NONE
	}CHARA;

	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		D3DXVECTOR3 rot; //角度
	}KEY;

	typedef struct
	{
		int nFrame; //フレーム数
		KEY *pKey; //キー情報
	}KEY_INFO;

	typedef struct
	{
		bool bLoop; //ループの有無
		int nNumKey; //キー数
		int nNumModel; //モデル数
		KEY_INFO *pKeyInfo; //キー情報
	}INFO;

	CMotion(); //コンストラクタ
	~CMotion(); //デストラクタ

	//メンバ関数
	void Update(void);
	void SetModel(CModel **ppModel, int nNum, CHARA type);
	void Set(CHARA type);
	
	//静的メンバ関数
	static void Load(void);
	static void UnLoad(void);

private:

	//メンバ変数
	CModel **m_ppModel;
	int m_nMotion;
	INFO m_Info;
	KEY m_oldKey;
	int m_nNumModel;
	int m_nCntFrame;
	int m_nCntKey;

	//静的メンバ変数
	static INFO *m_pInfo;
	static int m_nNumMotion;

};

#endif
