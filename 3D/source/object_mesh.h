//==========================================
//
//  メッシュオブジェクトクラス(object_mesh.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_MESH_H_
#define _OBJECT_MESH_H_
#include "main.h"
#include "object.h"

//==========================================
//  メッシュオブジェクトクラス定義
//==========================================
class CObject_Mesh : public CObject
{
public:
	typedef struct
	{
		int nNumMesh; //総分割数(プリミティブ数)
		int nNumMesh_U; //横の分割数
		int nNumMesh_V; //縦の分割数
		int nNumVtx; //総頂点数
		int nNumVtx_U; //横の頂点数
		int nNumVtx_V; //縦の頂点数
		int nNumIdx; //総インデックス数
	}MeshData; //頂点情報系の構造体

	CObject_Mesh(int nPriority = 3); //コンストラクタ
	~CObject_Mesh(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool OnMesh(const D3DXVECTOR3 pos);

	//静的メンバ関数
	static CObject_Mesh *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv);

private:

	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; //インデックスバッファ
	MeshData m_Mesh; //メッシュ情報
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス

	//メンバ関数
	void SetVtx(void);
	void SetIdx(void);
	void CalcData(void);

};

#endif
