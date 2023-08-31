//==========================================
//
//  �Q�[���S�ʂ̐���(main.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <time.h>
#include "main.h"
#include "manager.h"
#include "input.h"

//==========================================
//  �v���g�^�C�v�錾
//==========================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//==========================================
//  ���C���֐�
//==========================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hInstancePrev*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	//�f�o�b�O
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC, //�E�B���h�E�̃X�^�C��
		WindowsProc, //�E�B���h�E�v���V�[�W��
		0, //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0, //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance, //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW), //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1), //�N���C�A���g�̔w�i�F
		NULL, //���j���[�o�[
		CLASS_NAME, //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION), //�t�@�C���̃A�C�R��
	};
	HWND hWnd; //�E�B���h�E�n���h��
	MSG msg; //���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime; //���ݎ���
	DWORD dwExecLastTime; //�Ō�ɏ�����������
	DWORD dwFrameCount; //�t���[���J�E���g
	DWORD dwFPSLastTime; //�Ō��FPS���v����������

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx
	(
		0, //�g���E�B���h�E�X�^�C��
		CLASS_NAME, //�E�B���h�E�N���X�̖��O
		WINDOW_NAME, //�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW, //�E�B���h�E�X�^�C��
		CW_USEDEFAULT, //�E�B���h�E�̍���X���W
		CW_USEDEFAULT, //�E�B���h�E�̍���Y���W
		(rect.right - rect.left), //�E�B���h�E�̕�
		(rect.bottom - rect.top), //�E�B���h�E�̍���
		NULL, //�V�K�E�B���h�E�̃n���h��
		NULL, //���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance, //�C���X�^���X�n���h��
		NULL
	);

	//�C���X�^���X����
	CManager *pManager = NULL;

	//�������̊m��
	if (pManager == NULL)
	{
		pManager = new CManager;
	}

	//����������
	if (pManager != NULL)
	{
#ifdef _DEBUG
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{
			//�����������Ɏ��s�����ꍇ
			return -1;
		}
#else
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{
			//�����������Ɏ��s�����ꍇ
			return -1;
		}
#endif
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0; //������
	dwExecLastTime = timeGetTime(); //���ݎ������擾

	//�f�o�b�O�\���p�̐��l�̐ݒ�
	dwFrameCount = 0; //������
	dwFPSLastTime = timeGetTime(); //���ݎ������擾

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow); //�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd); //�N���C�A���g�̈�

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			//windows�̏���
			if (msg.message == WM_QUIT)
			{
				//WM_QUIT���b�Z�[�W���󂯎�����ꍇ
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg); //���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg); //�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{
			//DirectX�̏���
			dwCurrentTime = timeGetTime(); //���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//0.5�b�o��
				int nFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				CManager::SetFPS(nFPS);
				dwFPSLastTime = dwCurrentTime; //FPS�𑪒肵������
				dwFrameCount = 0; //�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				//60����1�b�o��
				dwExecLastTime = dwCurrentTime;
				dwFrameCount++;

				if (pManager != NULL)
				{
					//�X�V����
					pManager->Update();

					//�`�揈��
					pManager->Draw();

#if _DEBUG
					if (pManager->GetKeyboard()->GetTrigger(DIK_F2))
					{
						pManager->Uninit();
						delete pManager;
						pManager = NULL;
					}
#endif
				}
				else
				{
					pManager = new CManager;
					pManager->Init(hInstance, hWnd, TRUE);
				}
			}
		}
	}

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�̃N���X�̉���
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//�C���X�^���X�̔j��
	if (pManager != NULL)
	{
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	return (int)msg.wParam;
}

//==========================================
//  �E�B���h�E�v���[�W��
//==========================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//imgui��p�}�E�X����
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}

	switch (uMsg)
	{
	case WM_DESTROY: //�E�B���h�E�j���̃��b�Z�[�W
					 //WM_DUIT�̃��b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�������b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:
			//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_CLOSE: //�L�[�������b�Z�[�W
				   //�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
		DestroyWindow(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //����̏�����Ԃ�
}
