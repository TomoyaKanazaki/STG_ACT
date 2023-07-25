//==========================================
//
//  軌跡クラス(orbit.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ORBIT_H_
#define _ORBIT_H_
#include "main.h"
#include "object.h"

//==========================================
//  前方宣言
//==========================================
class CModel;

//==========================================
//  軌跡クラス定義
//==========================================
class COrbit : public CObject
{
public:
	COrbit(); //コンストラクタ
	~COrbit(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static COrbit *Create(CModel *pParent, D3DXCOLOR col, D3DXVECTOR3 offset0, D3DXVECTOR3 offset1, int nLife);

private:

	struct OFFSET
	{
		D3DXVECTOR3 pos;
		D3DXCOLOR col;
		D3DXMATRIX mtxWorld;
	};

	//メンバ変数
	CModel *m_parent; //追従するモデル
	OFFSET m_offset[2]; //オフセット情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファ
	D3DXCOLOR m_colDef; //初期カラー
	int m_nLife; //存在時間
	int m_nNumVtx; //頂点数
	D3DXMATRIX m_mtxWorld; //軌跡本体のマトリックス

};

#endif
