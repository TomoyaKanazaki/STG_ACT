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
	static COrbit *Create(CModel *pParent, D3DXCOLOR col, float fLength, int nLife);

private:

	//メンバ変数
	CModel *m_parent; //追従するモデル
	D3DXVECTOR3 m_Pos; //位置
	D3DXVECTOR3 m_VtxPos; //頂点位置
	D3DXCOLOR m_Col; //色
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファ
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	float m_fLength; //軌跡の長さ
	int m_nLife; //存在時間
	int m_nNumVtx; //頂点数

};

#endif
