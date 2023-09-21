//==========================================
//
//  煙のクラス(smoke.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SMOKE_H_
#define _SMOKE_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CSmoke : public CObject3D
{
public:
	CSmoke(int nPriority = 7); //コンストラクタ
	~CSmoke(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CSmoke *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col, int nLife);

private:

	//メンバ変数
	D3DXVECTOR3 m_vecDeffSize; //デフォルトサイズ
	int m_nLife;
	float m_fLifeRatio; //寿命の最大値における１単位

};

#endif
