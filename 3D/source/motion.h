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
		MOTION_NONE = 0, //なし
		PLAYER_SHOT, //弾を撃つ
		MOTION_MAX
	}CHARA;

	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		D3DXVECTOR3 rot; //角度
	}KEY;

	typedef struct
	{
		int nframe; //フレーム数
		KEY *pKey; //キー情報
	}KEY_INFO;

	typedef struct
	{
		bool bLoop; //ループの有無
		int nNumKey; //キー数
		KEY_INFO *pKeyInfo; //キー情報
	}INFO;

	CMotion(); //コンストラクタ
	~CMotion(); //デストラクタ

	//メンバ関数
	void Update(void);
	void SetModel(CModel **ppModel, int nNum, CHARA type);
	void Set(int type);
	
	//静的メンバ関数
	static void Load(void);
	static void UnLoad(void);

private:

	//メンバ変数
	CModel **m_ppModel;
	CHARA m_Chara;
	INFO m_Info;
	int m_nNumModel;

	//静的メンバ変数
	static INFO *m_pInfo;
	static int m_nNumMotion;

};

#endif
