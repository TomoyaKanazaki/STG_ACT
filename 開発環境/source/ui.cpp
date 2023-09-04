//==========================================
//
//  UIクラス(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "gamemanager.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
char CUi::m_sPass[256] = {};

//==========================================
//  コンストラクタ
//==========================================
CUi::CUi()
{
	m_hWnd = NULL;
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		m_EnemyData[nCnt].CreateData.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_EnemyData[nCnt].CreateData.fase = 0;
		m_EnemyData[nCnt].CreateData.type = 0;
		m_EnemyData[nCnt].CreateData.nCount = 0;
		m_EnemyData[nCnt].CreateData.nInterval = 0;
		m_EnemyData[nCnt].bUse = false;
	}
	m_nID = 0;
	m_state = CGameManager::NONE;
}

//==========================================
//  デストラクタ
//==========================================
CUi::~CUi()
{

}

//==========================================
//  初期化処理
//==========================================
void CUi::Init(HWND hWnd)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_hWnd = hWnd;

	//ImGui環境の設定
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//使用するフォント
	const char* FontPath = "data/font/GenShinGothic-Bold.ttf";

	//フォントサイズ
	const float FontSize = 15.0f;

	//文字の設定
	ImGuiIO &io = ImGui::GetIO();

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	//ImGuiスタイルの設定
	ImGui::StyleColorsLight();

	//プラットフォーム/レンダラーとバックエンドの設定
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);
}

//==========================================
//  終了処理
//==========================================
void CUi::Uninit(void)
{
	//ImGuiを終了
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//==========================================
//  更新処理
//==========================================
void CUi::Update(void)
{
	//ImGuiの実行
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//ウィンドウの生成
	ImGui::Begin(u8"EnemyManager");

	//表示する敵の番号を決める
	if (ImGui::ArrowButton("##0", 0))
	{
		if (m_nID > 0)
		{
			m_nID--;
		}
	} ImGui::SameLine();
	ImGui::Text(u8"敵情報番号 : %d", m_nID); ImGui::SameLine();
	if (ImGui::ArrowButton("##1", 1))
	{
		if (m_nID < 255)
		{
			m_nID++;
		}
	}

	//ライン
	ImGui::NewLine();

	//敵情報の使用状態を設定
	ImGui::Checkbox(u8"使用状態", &m_EnemyData[m_nID].bUse);

	//敵情報のパラメータ設定
	if (m_EnemyData[m_nID].bUse)
	{
		//敵タイプの設定
		ImGui::SliderInt (u8"敵タイプ", &m_EnemyData[m_nID].CreateData.type, 0, CEnemy::TYPE_MAX - 1);

		//初期位置の設定
		ImGui::DragFloat3(u8"初期位置", m_EnemyData[m_nID].CreateData.pos);

		//生成されるフェーズの設定
		ImGui::SliderInt(u8"生成フェーズ", &m_EnemyData[m_nID].CreateData.fase, 0, CGameManager::FAZE_MAX - 1);

		//生成回数の設定
		ImGui::Text(u8"[ -1 ]で無限生成");
		ImGui::DragInt(u8"生成回数", &m_EnemyData[m_nID].CreateData.nCount, 0.05f, -1);

		//生成間隔の設定
		ImGui::DragInt(u8"生成間隔", &m_EnemyData[m_nID].CreateData.nInterval, 0.05f, 0);
	}

	//ライン
	ImGui::NewLine();

	//フェーズ設定
	ImGui::Text(u8"現在のフェーズ : %d", CGameManager::GetState());
	if (ImGui::ArrowButton("##2", 0))
	{
		if (m_state > 0)
		{
			m_state = (CGameManager::STATE)((int)m_state - 1);
		}
	} ImGui::SameLine();
	ImGui::Text(u8"フェーズ : %d", m_state); ImGui::SameLine();
	if (ImGui::ArrowButton("##3", 1))
	{
		if (m_state < CGameManager::FAZE_MAX - 1)
		{
			m_state = (CGameManager::STATE)((int)m_state + 1);
		}
	} ImGui::SameLine();
	if (ImGui::Button(u8"再設定"))
	{
		ReLoad();
		CGameManager::SetState(m_state);
		CEnemyManager::ResetDeth();
	}

	//入出力
	Save(); ImGui::SameLine(); Load();

	//ウィンドウの終了
	ImGui::End();

	//更新の終了
	ImGui::EndFrame();

}

//==========================================
//  描画処理
//==========================================
void CUi::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画内容
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	//ライティングをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CUi *CUi::Create(HWND hWnd)
{
	//インスタンス生成
	CUi *pUI = NULL;

	//NULLチェック
	if (pUI == NULL)
	{
		//メモリを確保
		pUI = new CUi;
	}

	//初期化
	if (pUI != NULL)
	{
		pUI->Init(hWnd);
	}

	//ポインタを返す
	return pUI;
}

//==========================================
//  書き出し処理
//==========================================
void CUi::Save(void)
{
	if (ImGui::Button(u8"セーブ"))
	{
		OPENFILENAMEA filename = {};

		// ファイル選択ダイアログの設定
		filename.lStructSize = sizeof(OPENFILENAMEA);
		filename.hwndOwner = NULL;
		filename.lpstrFilter = 
			"バイナリファイル\0*.bin\0";
		filename.lpstrFile = m_sPass;
		filename.nMaxFile = MAX_PATH;
		filename.Flags = OFN_FILEMUSTEXIST;

		// ファイル選択ダイアログを表示
		if (GetOpenFileNameA(&filename))
		{
			// 選択されたファイルのパスを表示
			printf("Selected file: %s\n", m_sPass);
		}

		//セーブ
		if (strcmp(&m_sPass[0], "") != 0)
		{
			//ローカル変数宣言
			FILE *pFile; //ファイル名
		
			//ファイルを書き込み専用で開く
			pFile = fopen(m_sPass, "wb");
		
			if (pFile != NULL)
			{
				//保存されているデータ数を取得する
				int nNumData = 0;
				for (int nCnt = 0; nCnt < 256; nCnt++)
				{
					if (m_EnemyData[nCnt].bUse)
					{
						nNumData++;
					}
				}
		
				//データ数を保存する
				fwrite(&nNumData, sizeof(int), 1, pFile);
		
				//使用しているデータを保存する
				for (int nCnt = 0; nCnt < 256; nCnt++)
				{
					if (m_EnemyData[nCnt].bUse)
					{
						//0割り防止
						if (m_EnemyData[nCnt].CreateData.nInterval <= 0)
						{
							m_EnemyData[nCnt].CreateData.nInterval = 1;
						}

						//書き出し
						fwrite(&m_EnemyData[nCnt].CreateData, sizeof(CEnemyManager::CreateData), 1, pFile);
					}
				}
		
				//ファイルを閉じる
				fclose(pFile);
			}
		}
		else
		{
			MessageBox(m_hWnd, "Failed to save", "Failed to save", MB_OK);
		}
	}
}

//==========================================
//  読み込み処理
//==========================================
void CUi::Load(void)
{
	if (ImGui::Button(u8"ロード"))
	{
		OPENFILENAMEA filename = {};

		// ファイル選択ダイアログの設定
		filename.lStructSize = sizeof(OPENFILENAMEA);
		filename.hwndOwner = NULL;
		filename.lpstrFilter =
			"バイナリファイル\0*.bin\0";
		filename.lpstrFile = m_sPass;
		filename.nMaxFile = MAX_PATH;
		filename.Flags = OFN_FILEMUSTEXIST;

		// ファイル選択ダイアログを表示
		if (GetOpenFileNameA(&filename))
		{
			// 選択されたファイルのパスを表示
			printf("Selected file: %s\n", m_sPass);
		}

		//セーブ
		if (strcmp(&m_sPass[0], "") != 0)
		{
			//ローカル変数宣言
			FILE *pFile; //ファイル名

			//ファイルを書き込み専用で開く
			pFile = fopen(m_sPass, "rb");

			if (pFile != NULL)
			{
				//保存されているデータ数を取得する
				int nNumData = 0;
				fread(&nNumData, sizeof(int), 1, pFile);

				//保存されているデータを全て読み込む
				for (int nCnt = 0; nCnt < nNumData; nCnt++)
				{
					fread(&m_EnemyData[nCnt].CreateData, sizeof(CEnemyManager::CreateData), 1, pFile);
					m_EnemyData[nCnt].bUse = true;
				}

				//ファイルを閉じる
				fclose(pFile);

				//エネミーマネージャに保存されたデータを更新
				CEnemyManager::Unload();
				CEnemyManager::Load(&m_sPass[0]);
			}
		}
		else
		{
			MessageBox(m_hWnd, "Failed to load", "Failed to load", MB_OK);
		}
	}
}

//==========================================
//  再読み込み
//==========================================
void CUi::ReLoad(void)
{
	//ローカル変数宣言
	FILE *pFile; //ファイル名

	//ファイルを書き込み専用で開く
	pFile = fopen(m_sPass, "rb");

	if (pFile != NULL)
	{
		//保存されているデータ数を取得する
		int nNumData = 0;
		fread(&nNumData, sizeof(int), 1, pFile);

		//保存されているデータを全て読み込む
		for (int nCnt = 0; nCnt < nNumData; nCnt++)
		{
			fread(&m_EnemyData[nCnt].CreateData, sizeof(CEnemyManager::CreateData), 1, pFile);
			m_EnemyData[nCnt].bUse = true;
		}

		//エネミーマネージャの更新
		CEnemyManager::Unload();
		CEnemyManager::Load(&m_sPass[0]);

		//ファイルを閉じる
		fclose(pFile);
	}
}
