//==========================================
//
//  モデルクラス(model.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "object.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_MODEL (32) //モデルの最大数

//==========================================
//  モデルクラス定義
//==========================================
class CModel : public CObject
{
public:
	//モデル構造体定義
	typedef struct
	{
		LPDIRECT3DTEXTURE9 *pTexture; //マテリアルに使用するテクスチャ
		LPD3DXMESH pMesh; //頂点情報
		LPD3DXBUFFER pBuffMat; //マテリアルバッファ
		DWORD dwNumMat; //マテリアル数
		D3DXMATRIX mtxWorld; //ワールドマトリックス
	}MODEL;

	CModel(int nPriority = 7); //コンストラクタ
	~CModel(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetTransform(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot) { m_pos = pos; m_rot = rot; }
	static int GetNum(void) { return m_nNum; }

	//静的メンバ関数
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nModelID, CModel *m_pParent = NULL);
	static HRESULT Load(void);
	static void UnLoad(void);
	static bool GetLoadState(void) { return m_bLoad; }
	static int m_nNum;



private:

	//メンバ変数
	MODEL m_Info;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	CModel *m_pParent; //親モデルへのポインタ
	int m_nSelfID;

	//静的メンバ変数
	static int m_nNumAll; 
	static MODEL *m_pModel;
	static char m_sFilePass[MAX_MODEL][128];
	static bool m_bLoad;

};

#endif
