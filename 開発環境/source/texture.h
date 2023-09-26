//==========================================
//
//  テクスチャ管理クラス(texture.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_TEXTURE (256) //使用するテクスチャの最大数

//==========================================
//  テクスチャ管理クラス
//==========================================
class CTexture
{
public:
	//テクスチャの種類の列挙型定義
	enum TEXTURE
	{
		EFFECT = 0, //エフェクト
		NUMBER, //数字
		FIELD, //床
		TITLE, //タイトル
		RESULT, //リザルト
		TARGET, //的
		EXPLOSION, //爆発
		SMOKE, //煙
		RANKING, //ランキング
		ENTER, //エンター
		RANK, //今回の順位
		SCORE, //スコア
		TEXTURE_MAX
	};

	CTexture(); //コンストラクタ
	~CTexture(); //デストラクタ

	//メンバ関数
	HRESULT Load(void); //テクスチャのロード
	void UnLoad(void); //テクスチャの破棄
	int Regist(const char *pFilName); //テクスチャの登録
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx) { return m_apTexture[nIdx]; } //テクスチャの取得
	int GetNum(void) { return m_nNumAll; }

	//静的メンバ関数
	static bool GetLoadState(void) { return m_bLoad; }; //テクスチャの読み込み状態を取得

private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE]; //テクスチャ情報
	char m_sFilePass[MAX_TEXTURE][256]; //既に読み込まれているテクスチャのパス
	int m_nNumAll; //テクスチャの総数

	//静的メンバ変数
	static bool m_bLoad;

};

#endif
