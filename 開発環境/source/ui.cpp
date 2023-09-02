//==========================================
//
//  UIクラス(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "manager.h"
#include "renderer.h"

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

	// 書き出し
	Save();

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
						fwrite(&m_EnemyData[nCnt], sizeof(EnemyData), 1, pFile);
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
