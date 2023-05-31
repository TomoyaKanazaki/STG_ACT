//==========================================
//
//  オブジェクトクラス(object.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_OBJECT (2048) //オブジェクトの最大数

//==========================================
//  オブジェクトクラス生成
//==========================================
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0, //不使用
		TYPE_PLAYER, //プレイヤー
		TYPE_ENEMY, //敵
		TYPE_BULLET, //弾
		TYPE_MAX
	}TYPE;

	CObject();
	virtual ~CObject();

	//メンバ関数
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	CObject *GetObject(int nID) { return m_apObject[nID]; }
	int GetID(void) { return m_nID; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	void SetType(TYPE type) { m_type = type; }
	TYPE GetTypre(void) { return m_type; }

	//静的メンバ関数
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

protected:

	//メンバ関数
	void Release(void);

	//メンバ変数
	D3DXVECTOR3 m_pos; //オブジェクトの中心座標
	D3DXVECTOR3 m_rot; //オブジェクトの向き
	D3DXVECTOR3 m_size; //オブジェクトのサイズ

private:

	//静的メンバ変数
	static CObject *m_apObject[MAX_OBJECT]; //オブジェクトのポインタ
	static int m_nNumObject; //オブジェクトの総数

	//メンバ変数
	int m_nID; //自分自身のインデックス
	TYPE m_type; //種類

};

#endif
