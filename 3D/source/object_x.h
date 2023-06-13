//==========================================
//
//  xオブジェクトクラス(object_x.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_X_H_
#define _OBJECT_X_H_
#include "main.h"
#include "object.h"

//==========================================
//  xオブジェクトクラスの定義
//==========================================
class CObject_X : public CObject
{
public:
	CObject_X(int nPriority = 2); //コンストラクタ
	~CObject_X(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CObject_X *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 *m_pTexture;
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;
	D3DXMATRIX m_mtxWorld;

};

#endif
