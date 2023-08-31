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
class CMotion;
class COrbit;

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
	void SetDead(const bool bDead) { m_bDead = bDead; }

	//静的メンバ関数
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//メンバ関数
	void Move(void);
	void Slop(void);
	void Shot(void);
	void Explosion(void);
	void Swing(void);
	void Aiming(void);

	//メンバ変数
	int m_nLife;
	int m_nNumModel;
	int m_nDeadCounter;
	int m_nBladeLife;
	float m_fSpeed;
	float m_fAngle;
	float m_fSwing;
	bool m_bRand;
	bool m_bDead;
	D3DXMATERIAL *m_pDefMat;

	//静的メンバ変数
	const static float mc_fExplosion; //殲滅範囲

	//モデル情報
	CModel **m_ppModel; //モデル情報
	CLayer::LAYERDATA *m_pLayer; //階層構造情報
	CShadow *m_pShadow; //影の情報
	CMotion *m_pMotion;
	COrbit *m_orbit;

};

#endif
