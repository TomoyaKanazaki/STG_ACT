//==========================================
//
//  パーティクルクラス(particle.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"
#include "object.h"

//==========================================
//  パーティクルクラス定義
//==========================================
class CParticle : public CObject
{
public:
	CParticle(); //コンストラクタ
	~CParticle(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 range, D3DXCOLOR col, int nEffectNum, int nEffectLife, int nMove, int nLife);

private:

	//メンバ変数
	D3DXVECTOR3 m_range; //発生したエフェクトの移動量基準
	D3DXCOLOR m_col; //発生するエフェクトの色
	int m_nEffectNum; //1fに発生するエフェクトの数
	int m_nEffectLife; //発生するエフェクトの寿命
	int m_nMove; //移動量
	int m_nLife; //パーティクル本体の寿命

};

#endif
