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
		TYPE_NORMAL_ENEMY, //敵
		TYPE_BLOCK_ENEMY, //止める敵
		TYPE_PUSH_ENEMY, //弾く敵
		TYPE_BULLET_ENEMY, //弾の敵
		TYPE_EXPLOSION, //爆発
		TYPE_BG, //背景
		TYPE_EFFECT, //エフェクト
		TYPE_NUMBER, //数字
		TYPE_TIMER, //タイマー
		TYPE_SCORE, //スコア
		TYPE_FIELD, //床
		TYPE_SHADOW, //影
		TYPE_TARGET, //目標
		TYPE_FADE, //フェード
		TYPE_ROCKON, //ロックオン
		TYPE_DEBRIS, //スペースデブリ
		METHOD_MAX
	}TYPE;

	CObject(int nPriority = 3); //コンストラクタ
	virtual ~CObject(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	CObject *GetNext(void) { return m_pNext; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }
	D3DXVECTOR3 GetOldRot(void) { return m_oldRot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_type; }
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }
	void SetSize(const D3DXVECTOR3 size) { m_size = size; }
	void SetType(TYPE type) { m_type = type; }

	virtual int GetCombo() { return NULL; } //敵のコンボ数の取得

	//静的メンバ関数
	static CObject *GetTop(int nPriority) { return m_apTop[nPriority]; }
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int GetNum(void) { return m_nNumObject; }

protected:

	//メンバ関数
	void Release(void);

	//メンバ変数
	D3DXVECTOR3 m_pos; //オブジェクトの中心座標
	D3DXVECTOR3 m_rot; //オブジェクトの向き
	D3DXVECTOR3 m_move; //オブジェクトの移動量
	D3DXVECTOR3 m_size; //オブジェクトのサイズ
	D3DXVECTOR3 m_oldPos; //オブジェクトの前回座標
	D3DXVECTOR3 m_oldRot; //オブジェクトの前回角度

private:

	//メンバ変数
	CObject *m_pNext; //次のオブジェクトのポインタ
	CObject *m_pPrev; //前のオブジェクトのポインタ
	int m_nPriority; //描画優先順位
	TYPE m_type; //種類
	bool m_bDeath; //死亡フラグ

	//静的メンバ変数
	static int m_nNumObject; //オブジェクトの総数
	static CObject *m_apTop[PRIORITY_NUM]; //先頭オブジェクトのポインタ配列
	static CObject *m_apCur[PRIORITY_NUM]; //最後尾オブジェクトのポインタ配列

};

#endif
