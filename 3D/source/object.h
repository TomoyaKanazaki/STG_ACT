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
#define PRIORITY_NUM (8) //優先順位の最大数
#define MAX_OBJECT (4096) //オブジェクトの最大数

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
		TYPE_EXPLOSION, //爆発
		TYPE_BG, //背景
		TYPE_EFFECT, //エフェクト
		TYPE_NUMBER, //数字
		TYPE_TIMER, //タイマー
		TYPE_SCORE, //スコア
		TYPE_FIELD, //床
		TYPE_WALL, //壁
		TYPE_SHADOW, //影
		METHOD_MAX
	}TYPE;

	CObject(int nPriority = 3); //コンストラクタ
	virtual ~CObject(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	CObject *GetObject(int nPriority, int nID) { return m_apObject[nPriority][nID]; }
	int GetID(void) { return m_nID; }
	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }

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
	static CObject *m_apObject[PRIORITY_NUM][MAX_OBJECT]; //オブジェクトのポインタ
	static int m_nNumObject; //オブジェクトの総数

	//メンバ変数
	int m_nID; //自分自身のインデックス
	int m_nPriority; //描画優先順位
	TYPE m_type; //種類

};

#endif
