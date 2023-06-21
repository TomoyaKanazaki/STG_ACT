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
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetMove(void) { return m_move; }

	//静的メンバ変数
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//メンバ関数
	void Move(void);
	void Rotate(void);

	//メンバ変数
	D3DXVECTOR3 m_move;
	float m_fSpeed;
	float m_fAngle;
	bool m_bJunp;

	//モデル情報
	CModel *m_apModel[2];
	CShadow *m_pShadow;

};

#endif
