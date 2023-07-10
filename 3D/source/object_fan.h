//==========================================
//
//  オブジェクトファンクラス(object_fan.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_FAN_H_
#define _OBJECT_FAN_H_
#include "main.h"
#include "object.h"

//==========================================
//  オブジェクトファンクラス定義
//==========================================
class CObject_Fan : public CObject
{
public:
	CObject_Fan(int nPriority = 1); //コンストラクタ
	~CObject_Fan(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool OnMesh(const D3DXVECTOR3 pos);
	bool OnMesh(const D3DXVECTOR3 pos, const D3DXVECTOR3 oldpos, D3DXVECTOR3 *pVecLine, D3DXVECTOR3 *pVecToPos);

	//静的メンバ関数
	static CObject_Fan *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumPrimitive, float fRadius);

private:

	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファ
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャ情報
	D3DXCOLOR m_Color; //頂点カラー
	float m_fRadius; //中心座標から各頂点への距離
	int m_nNumPrimitive; //プリミティブ数
	int m_nNumVtx; //頂点数

	//メンバ関数
	void SetVtx(void);
	bool CheckOnMesh(const D3DXVECTOR3 &posJudge, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &posEnd) const;

};

#endif
