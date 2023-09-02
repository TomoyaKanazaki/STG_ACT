//==========================================
//
//  UI�N���X(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
char CUi::m_sPass[256] = {};

//==========================================
//  �R���X�g���N�^
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
//  �f�X�g���N�^
//==========================================
CUi::~CUi()
{

}

//==========================================
//  ����������
//==========================================
void CUi::Init(HWND hWnd)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_hWnd = hWnd;

	//ImGui���̐ݒ�
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//�g�p����t�H���g
	const char* FontPath = "data/font/GenShinGothic-Bold.ttf";

	//�t�H���g�T�C�Y
	const float FontSize = 15.0f;

	//�����̐ݒ�
	ImGuiIO &io = ImGui::GetIO();

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	//ImGui�X�^�C���̐ݒ�
	ImGui::StyleColorsLight();

	//�v���b�g�t�H�[��/�����_���[�ƃo�b�N�G���h�̐ݒ�
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);
}

//==========================================
//  �I������
//==========================================
void CUi::Uninit(void)
{
	//ImGui���I��
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//==========================================
//  �X�V����
//==========================================
void CUi::Update(void)
{
	//ImGui�̎��s
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//�E�B���h�E�̐���
	ImGui::Begin(u8"EnemyManager");

	//�\������G�̔ԍ������߂�
	if (ImGui::ArrowButton("##0", 0))
	{
		if (m_nID > 0)
		{
			m_nID--;
		}
	} ImGui::SameLine();
	ImGui::Text(u8"�G���ԍ� : %d", m_nID); ImGui::SameLine();
	if (ImGui::ArrowButton("##1", 1))
	{
		if (m_nID < 255)
		{
			m_nID++;
		}
	}

	// �����o��
	Save();

	//�E�B���h�E�̏I��
	ImGui::End();

	//�X�V�̏I��
	ImGui::EndFrame();

}

//==========================================
//  �`�揈��
//==========================================
void CUi::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`����e
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	//���C�e�B���O���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CUi *CUi::Create(HWND hWnd)
{
	//�C���X�^���X����
	CUi *pUI = NULL;

	//NULL�`�F�b�N
	if (pUI == NULL)
	{
		//���������m��
		pUI = new CUi;
	}

	//������
	if (pUI != NULL)
	{
		pUI->Init(hWnd);
	}

	//�|�C���^��Ԃ�
	return pUI;
}

//==========================================
//  �����o������
//==========================================
void CUi::Save(void)
{
	if (ImGui::Button(u8"�Z�[�u"))
	{
		OPENFILENAMEA filename = {};

		// �t�@�C���I���_�C�A���O�̐ݒ�
		filename.lStructSize = sizeof(OPENFILENAMEA);
		filename.hwndOwner = NULL;
		filename.lpstrFilter = 
			"�o�C�i���t�@�C��\0*.bin\0";
		filename.lpstrFile = m_sPass;
		filename.nMaxFile = MAX_PATH;
		filename.Flags = OFN_FILEMUSTEXIST;

		// �t�@�C���I���_�C�A���O��\��
		if (GetOpenFileNameA(&filename))
		{
			// �I�����ꂽ�t�@�C���̃p�X��\��
			printf("Selected file: %s\n", m_sPass);
		}

		//�Z�[�u
		if (strcmp(&m_sPass[0], "") != 0)
		{
			//���[�J���ϐ��錾
			FILE *pFile; //�t�@�C����
		
			//�t�@�C�����������ݐ�p�ŊJ��
			pFile = fopen(m_sPass, "wb");
		
			if (pFile != NULL)
			{
				//�ۑ�����Ă���f�[�^�����擾����
				int nNumData = 0;
				for (int nCnt = 0; nCnt < 256; nCnt++)
				{
					if (m_EnemyData[nCnt].bUse)
					{
						nNumData++;
					}
				}
		
				//�f�[�^����ۑ�����
				fwrite(&nNumData, sizeof(int), 1, pFile);
		
				//�g�p���Ă���f�[�^��ۑ�����
				for (int nCnt = 0; nCnt < 256; nCnt++)
				{
					if (m_EnemyData[nCnt].bUse)
					{
						fwrite(&m_EnemyData[nCnt], sizeof(EnemyData), 1, pFile);
					}
				}
		
				//�t�@�C�������
				fclose(pFile);
			}
		}
		else
		{
			MessageBox(m_hWnd, "Failed to save", "Failed to save", MB_OK);
		}
	}
}
