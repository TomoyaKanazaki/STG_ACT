//==========================================
//
//  プレイヤークラス(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "object.h"
#include "layer.h"

//==========================================
//  前方宣言
//==========================================
class CModel;
class CShadow;

//==========================================
//  プレイヤークラスの定義
//==========================================
class CPlayer : public CObject
{
public:
	CPlayer(int nPriority = 4); //コンストラクタ
	~CPlayer(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }

	//静的メンバ変数
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//メンバ関数
	void Move(void);
	void Rotate(void);

	//メンバ変数
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_oldPos;
	int m_nLife;
	int m_nNumModel;
	int m_nDeadCounter;
	float m_fSpeed;
	float m_fAngle;
	bool m_bRand;
	bool m_bDead;

	//モデル情報
	CModel *m_apModel[5]; //モデル情報
	CLayer::LAYERDATA *m_pLayer; //階層構造情報
	CShadow *m_pShadow; //影の情報

};

#endif
