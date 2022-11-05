#include "windows.h"
#include <stdlib.h>
#include <stdio.h>
#include <shlobj.h>

LRESULT CALLBACK WindowFunc(HWND, UINT, WPARAM, LPARAM);

char *szWinName = "ATPackClass";

HWND hMainWnd, FHandle,
	hButton1, hButton2, hButton21, hButton22, hButton23, hButton24, hButton25, hButton26, hButton27, hButton3, hButton4,
	hEdit1, hEdit2,
	list1, list2, hStatic;
MSG msg;
WNDCLASS wcl;
int c1, lenPath;
HDC hdc;
static HANDLE hImage1;
char mainPath[260] = "", exPath[260] = "";
FILE *in, *out;
char ch;
char b[260];
long int count, acount[32000];
int listCount, i, ii, n, EX = 0;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int nCmdShow)
{
	wcl.hInstance = hInstance;
    wcl.lpszClassName = szWinName;
    wcl.lpfnWndProc = WindowFunc;
    wcl.style = 0;
    wcl.hCursor = LoadCursor(NULL,IDC_ARROW);
    wcl.lpszMenuName = NULL;
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    wcl.hbrBackground = (HBRUSH)COLOR_WINDOW;

	if(!RegisterClass (&wcl))
		return (FALSE);

//создаем главное окно и элементы управления
    hMainWnd = CreateWindow(szWinName, "Установка ПО РНТ.", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
                                            600, 400, HWND_DESKTOP, NULL, hInstance, NULL);
    if((in = fopen("autorun.ico", "rb")) == NULL) {
    	hButton1 = CreateWindow("button", "Запаковать", WS_CHILD, 370, 335, 100, 25, hMainWnd, NULL, hInstance, NULL);
        hButton21 = CreateWindow("button", "Добавить ...", WS_CHILD | WS_VISIBLE, 20, 100, 100, 25, hMainWnd, NULL, hInstance, NULL);
        hButton22 = CreateWindow("button", "Сформировать", WS_CHILD, 130, 100, 110, 25, hMainWnd, NULL, hInstance, NULL);
    } else {
    	hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 100, 150, 25, hMainWnd, NULL, hInstance, NULL);
        hButton2 = CreateWindow("button", "Распаковать", WS_CHILD | WS_VISIBLE, 260, 335, 100, 25, hMainWnd, NULL, hInstance, NULL);
        hButton23 = CreateWindow("button", "Службы", WS_CHILD | WS_VISIBLE, 180, 100, 65, 25, hMainWnd, NULL, hInstance, NULL);
        hButton24 = CreateWindow("button", "Блокнот", WS_CHILD | BS_AUTORADIOBUTTON, 250, 100, 75, 25, hMainWnd, NULL, hInstance, NULL);
        hButton25 = CreateWindow("button", "-install", WS_CHILD | BS_AUTORADIOBUTTON, 340, 100, 65, 25, hMainWnd, NULL, hInstance, NULL);
        hButton26 = CreateWindow("button", "InstallUtil", WS_CHILD | BS_AUTORADIOBUTTON, 410, 100, 100, 25, hMainWnd, NULL, hInstance, NULL);
        hButton27 = CreateWindow("button", "Запуск", WS_CHILD | BS_AUTORADIOBUTTON , 510, 100, 70, 25, hMainWnd, NULL, hInstance, NULL);
        hButton4 = CreateWindow("button", "Установить", WS_CHILD | WS_VISIBLE, 370, 335, 100, 25, hMainWnd, NULL, hInstance, NULL);
        fclose(in);
    }
    FHandle = CreateWindowEx(0,"msctls_progress32", 0, WS_CHILD , 20, 65, 560, 25, hMainWnd, 0, 0, 0);
    ShowWindow(FHandle, SW_SHOW);
    hButton3 = CreateWindow("button", "Выход", WS_CHILD | WS_VISIBLE, 480, 335, 100, 25, hMainWnd, NULL, hInstance, NULL);
    hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", NULL, WS_CHILD | WS_BORDER | ES_READONLY, 20, 100, 150, 25, hMainWnd, NULL, hInstance, NULL);
//	list1 = CreateWindow("ListBox",NULL, LBS_NOTIFY | WS_CHILD | WS_VSCROLL|WS_BORDER ,20,130,180,200,hMainWnd,NULL, hInstance, NULL);
	list2 = CreateWindow("ListBox",NULL, LBS_NOTIFY | WS_CHILD | WS_VSCROLL|WS_BORDER ,220,130,180,200,hMainWnd,NULL, hInstance, NULL);
	list1 = CreateWindow("ListBox",NULL, LBS_NOTIFY | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | WS_HSCROLL, 20,130,560,200,hMainWnd,NULL, hInstance, NULL);
//	list1 = CreateWindow("ListBox",NULL, LBS_NOTIFY | WS_CHILD | WS_VISIBLE | WS_VSCROLL|WS_BORDER ,20,130,560,200,hMainWnd,NULL, hInstance, NULL);
//	list2 = CreateWindow("ListBox",NULL, LBS_NOTIFY | WS_CHILD | WS_VISIBLE | WS_VSCROLL|WS_BORDER ,220,130,180,200,hMainWnd,NULL, hInstance, NULL);
//        hStatic = CreateWindow("static", "Введите путь и нажмите кнопку \"Установить\".",
//								WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 130, 150, 70, hMainWnd, NULL, hInstance, NULL);
	SetWindowText(hEdit1, "C:\\AutoTracker\\");
	SetWindowText(hEdit2, "\\toCD\\");
	GetModuleFileName( NULL, exPath, 260 );
	strcat(mainPath, exPath);
	lenPath = strlen(mainPath);
	for(c1=lenPath; mainPath[c1]!='\\'; c1--)mainPath[c1]='\0';
    if((in = fopen("autorun.ico", "rb")) == NULL)
            SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)exPath);
    else {
            fclose(in);
    }
// отображаем и обновляем окно
	ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);
// цикл обработки сообщений
    while(GetMessage(&msg, NULL, 0, 0)) {
    	TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

//Распаковка картинок
bool createImage(const char *newFile, const int begin, const int count)
{
	char whereFile[260] = "";
	GetModuleFileName( NULL, whereFile, 260 );
	int nnn = 0;
	if((in = fopen(whereFile, "rb")) == NULL) {
		return FALSE;
	}
	else {
		if(!fseek( in, begin, SEEK_SET ))
		{
			if((out = fopen(newFile, "wb")) == NULL) {
				return FALSE;
			}
	        while (!feof(in) && (nnn++ < count)){
	        	ch = fgetc(in);
	            if(!feof(in))
	        	   	fputc((int)ch, out);
	        }
			fclose(out);
		}
		fclose(in);
	}
	return TRUE;
}

//Поиск всех файлов для упаковки
int findAllFiles(const char Path[MAX_PATH], const int lenForCdPath)
{
	WIN32_FIND_DATA winFileData;
	HANDLE hFile;
	char szPath[MAX_PATH];
	strcpy(szPath, Path);
	if(SetCurrentDirectory(szPath))
	{
		strcat(szPath,"\\*.*");
		hFile = FindFirstFile(szPath,&winFileData);
		if (hFile!=INVALID_HANDLE_VALUE)
		{
			do
			{
				if ((winFileData.cFileName[1] !='.' && winFileData.cFileName[0] != '.') || (winFileData.cFileName[0] != '.')){
					char folderName[MAX_PATH];
					strcpy(folderName, Path);
					strcat(folderName, "\\");
					strcat(folderName, winFileData.cFileName);
					if(winFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
						findAllFiles(folderName, lenForCdPath);
					else {
						char tmpSzFile[260];
						int indexLetter, tmpIndex=0;
						for(indexLetter = lenForCdPath; folderName[indexLetter]; indexLetter++)
							tmpSzFile[tmpIndex++] = folderName[indexLetter];
						tmpSzFile [tmpIndex] = '\0';
						SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) tmpSzFile);
						SendMessage(list1,LB_SETCARETINDEX,(int)SendMessage(list1,LB_GETCOUNT,0,0),FALSE);
					}
				}
			}
			while (FindNextFile(hFile,&winFileData)!=0);
			FindClose(hFile);
		}
	}
	return 0;
}

// Создание последовательности директорий и поддиректорий
bool CreateDirectoryPath(char sPathTo[260])
{
        while(CreateDirectory(sPathTo, NULL) == FALSE) {
                char sTemp[260];
                int k = strlen(sPathTo);
                strcpy(sTemp, sPathTo);
                while(CreateDirectory(sTemp, NULL) != TRUE) {
                        while(sTemp[--k] != '\\') {
                                if(k<=1)
                                return FALSE;
                                sTemp[k] = 0;
                        }
                }
        }
        return TRUE;
}

//создаем autorun.inf
bool createInf(const char toPath[260], int i)
{
	int ii,iL;
	char to[260];
	strcpy(to, toPath);
	strcat(to, "autorun.inf");
	if((out = fopen(to, "wb")) == NULL) {
		SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"Error write:");
		return FALSE;
	}
	fprintf(out,"%s\r\n%s\r\n%s\r\n", "[autorun] ", "Open = setup.exe ", "Icon = autorun.ico ");
	for(ii=0; ii<i+1; ii++) {
		fprintf(out,"%lld\r\n",acount[ii]);
		char bbb1[260];
		SendMessage(list1,LB_GETTEXT, ii, (LPARAM)(LPCSTR)bbb1);
		for(iL = 0; bbb1[iL]; iL++)
			if(bbb1[iL]==' ')bbb1[iL]='_';
		if(i>ii)fprintf(out,"%s\r\n", bbb1);
	}
	fclose(out);
	return TRUE;
}

// Копирование installutil  и другое
bool CopyFile(const char FileName[260], const char fromPath[260], const char toPath[260], int i)
{
	int ii,iL;
	char from[260], to[260];
	strcpy(from, fromPath);
	strcat(from, FileName);
	strcpy(to, toPath);
	strcat(to, FileName);
	if((in = fopen(from, "rb")) == NULL) {
		SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"Error read:");
		return FALSE;
	}
	if((out = fopen(to, "wb")) == NULL) {
		SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"Error write:");
		return FALSE;
	}
	while(!feof(in)) {
		ch = fgetc(in);
		if(!feof(in))
		fputc((int)ch, out);
    }
	fclose(in);
	fclose(out);
	return TRUE;
}

// оконная функция
LRESULT CALLBACK WindowFunc(HWND hMainWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    char toCdPath[260] = "";
	char forCdPath[260] = "";
	char setupPath[260] = "";
	char infPath[260] = "";
	char icoFullName[260] = "";
	strcat(toCdPath, mainPath);
	strcat(toCdPath, "toCD\\");
	strcat(forCdPath, mainPath);
	strcat(forCdPath, "forCD\\");
	strcpy(icoFullName, toCdPath);
	strcat(icoFullName, "autorun.ico");
    int lenForCdPath = strlen(forCdPath);

	switch(iMsg)
    {
//подгружаем картинку
	case WM_CREATE:	{
			char imageFullName[260]="";
			GetTempPath(255, imageFullName);
			strcat(imageFullName, "at.bmp");
			if(createImage(imageFullName, 44942, 108054))
				hImage1=LoadImage(NULL, imageFullName, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			return 0;
		}
//рисуем картинку
	case WM_PAINT: {
			PAINTSTRUCT ps;
			BITMAP bm;
			hdc = BeginPaint(hMainWnd,&ps);
			HDC hdcMem = CreateCompatibleDC(ps.hdc);
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hImage1);
			GetObject(hImage1, sizeof(bm), &bm);
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hbmOld);
			DeleteDC(hdcMem);
			EndPaint(hMainWnd,&ps);
			return 0;
		}

    case WM_DESTROY: {
	        DeleteObject((HGDIOBJ)hImage1);
            	PostQuitMessage(0);
            	break;
		}

    case WM_COMMAND: {
//	Close
        	if(((HWND)lParam == hButton3) && (HIWORD(wParam) == BN_CLICKED))
        		PostQuitMessage(0);
//	OpenDialog
			if(((HWND)lParam == hButton21) && (HIWORD(wParam) == BN_CLICKED)) {
				BROWSEINFO    info;
				char          szDir[MAX_PATH];
				char          szDisplayName[MAX_PATH];
				LPITEMIDLIST  pidl;
				LPMALLOC      pShellMalloc;

				if(SHGetMalloc(&pShellMalloc) == NO_ERROR)
				{
					memset(&info, 0x00,sizeof(info));
					info.hwndOwner = hMainWnd;                 // Owner window
					info.pidlRoot  = 0;                      // root folder
					info.pszDisplayName = szDisplayName;     // return display name
					info.lpszTitle = "Выбор каталога для упаковки ...";         // label caption
					info.ulFlags   = BIF_RETURNONLYFSDIRS;   // config flags
					info.lpfn = 0;                           // callback function

					pidl = SHBrowseForFolder(&info);

					if(pidl)
					{
						if(SHGetPathFromIDList(pidl, szDir))
						{
							STARTUPINFO cif;
							ZeroMemory(&cif,sizeof(STARTUPINFO));
							PROCESS_INFORMATION pi;
							cif.wShowWindow = SW_HIDE;
							CreateProcess(0 , "attrib -R -A -S -H /S /D",0,0,FALSE,0,0, szDir,&cif,&pi);
							strcat(szDir, "\\");
							SetWindowText(hEdit2, szDir);
							ShowWindow(hButton21, SW_HIDE);
							ShowWindow(hButton22, SW_SHOW);
						}

						pShellMalloc->Free(pidl);
					}
					pShellMalloc->Release();
				}
	        }

//	Pack
			if(((HWND)lParam == hButton1) && (HIWORD(wParam) == BN_CLICKED)) {
				count = 0;
				acount[0] = 0;
				CreateDirectoryPath(toCdPath);
				strcpy(setupPath, toCdPath);
				strcat(setupPath, "setup.exe");
				if((out = fopen(setupPath, "wb")) == NULL) {
					SendMessage(list2,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"Error write out.");
					return 1;
				}

				listCount = (int)SendMessage(list1,LB_GETCOUNT,0,0);
				SendMessage(FHandle, PBM_SETRANGE, 0, MAKELPARAM(0, listCount));
				SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) "---------------------------");
                SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) " ");
                SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) "Запакован(ы):");
				if(listCount>0)
					for(i = 0; i<listCount; i++){
						char bbb1[260];
                        char tmpFullPath[260] = "";
                        SendMessage(list1,LB_GETTEXT, i, (LPARAM)(LPCSTR)bbb1);
                        GetWindowText(hEdit2, tmpFullPath, 260);
                        //strcat(tmpFullPath, forCdPath);
                        strcat(tmpFullPath, bbb1);
                        //                        SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)tmpFullPath );
                        if(i==0)
                        	GetModuleFileName( NULL, tmpFullPath, 260 );
						if((in = fopen(tmpFullPath, "rb")) == NULL) {
							SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"Error:");
							SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)tmpFullPath);
							return 1;
						}
						while(!feof(in)) {
							ch = fgetc(in);
						    if(!feof(in)) {
						    	fputc((int)ch, out);
							    count++;
						    }//if
					    }//while
                        SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) tmpFullPath);
                		SendMessage(list1,LB_SETCARETINDEX,(int)SendMessage(list1,LB_GETCOUNT,0,0),FALSE);
                        fclose(in);
		        		acount[i+1] = count;

			            SendMessage(FHandle, PBM_SETPOS, i+1, 0);
			            //UpdateWindow(FHandle);
                        UpdateWindow(hMainWnd);//обновили окно и список list1, отобразили добавление нового файла
			        }
        			fclose(out);
        		acount[0]=i+1;
// Создаем autorun.inf
                if(!createInf(toCdPath, i)) {
                	SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"autorun.inf");
                    return 1;
                }
// Создаем autorun.ico
                if(!createImage(icoFullName, 44942 + 108054, 766)){
                	SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"autorun.ico");
                	return 1;
                }
                SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) "-----------------------------------");
                SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) "--   Процесс упаковки завершен ----");
                SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) "-----------------------------------");
                SendMessage(list1,LB_SETCARETINDEX,(int)SendMessage(list1,LB_GETCOUNT,0,0),FALSE);
                ShowWindow(hButton1, SW_HIDE);
				STARTUPINFO cif;
				ZeroMemory(&cif,sizeof(STARTUPINFO));
				PROCESS_INFORMATION pi;
				cif.wShowWindow = SW_HIDE;
				char openExplorer[260] = "";
				strcpy(openExplorer, "explorer ");
				strcat(openExplorer, toCdPath);
				CreateProcess(0 , openExplorer,0,0,FALSE,0,0, toCdPath,&cif,&pi);
			}//if Pack

//UnPack
			if(((HWND)lParam == hButton2) && (HIWORD(wParam) == BN_CLICKED)) {
				char chp;
				char APath[260] = "";
                char CPath[260] = "";
                strcat(APath, "autorun.inf");
				int iname = 0;
                int itmpNamef = 0;
                int tmpN = 0;
				if((in = fopen(APath, "r")) == NULL) {
					SendMessage(list2,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"Error read autorun.inf");
					return 1;
				}
                fgets(APath, 260, in);
                fgets(APath, 260, in);
                fgets(APath, 260, in);
                fscanf(in, "%lld", &count);
                SendMessage(FHandle, PBM_SETRANGE, 0, MAKELPARAM(0,count));

				while(!feof(in)) {
					if(!feof(in)){
                                fscanf(in, "%s", &APath);
				                fscanf(in, "%lld", &count);

				                iname++;
				                acount[iname] = count;
                                SendMessage(list2,LB_ADDSTRING,255,(LPARAM)(LPCSTR)APath);
                    }
                }
				fclose(in);

				count = 0;
				if((in = fopen("setup.exe", "rb")) == NULL) {
					SendMessage(list2,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"Error: not read file.");
					return 1;
				}

                char fullTmpNamef[260] = "";
                GetWindowText(hEdit1, fullTmpNamef, 260);
                if(fullTmpNamef[strlen(fullTmpNamef)-1]!='\\') {
                	fullTmpNamef[strlen(fullTmpNamef)]='\\';
                    fullTmpNamef[strlen(fullTmpNamef)+1]='\0';
                    SetWindowText(hEdit1, fullTmpNamef);
                }

                for(ii = 1; ii<iname; ii++){
                	char namef[260] = "";
                    char tmpNamef[260] = "";
                    GetWindowText(hEdit1, fullTmpNamef, 260);
                    SendMessage(list2,LB_GETTEXT, ii-1, (LPARAM)(LPCSTR)tmpNamef);
                    for(itmpNamef = strlen(tmpNamef); ((tmpNamef[itmpNamef-1]!='\\') && (itmpNamef !=0)); itmpNamef--);
						tmpNamef[itmpNamef]='\0';
                    for(tmpN = itmpNamef; tmpN <= strlen(tmpNamef); tmpN++)
                    	namef[tmpN-itmpNamef] = tmpNamef[tmpN];
                    namef[tmpN-itmpNamef]='\0';
                    strcat(fullTmpNamef, tmpNamef);
                    strcpy(tmpNamef, fullTmpNamef);
                    if(itmpNamef!=0)
                    	CreateDirectoryPath(tmpNamef);
                    SendMessage(list2,LB_GETTEXT, ii-1, (LPARAM)(LPCSTR)namef);
                    GetWindowText(hEdit1, fullTmpNamef, 260);
                    strcat(fullTmpNamef, namef);
                    strcpy(namef, fullTmpNamef);
                    int ttt=strlen(fullTmpNamef);
    				if(
            			(fullTmpNamef[ttt-4]=='.') &&
            			(fullTmpNamef[ttt-3]=='e') &&
            			(fullTmpNamef[ttt-2]=='x') &&
            			(fullTmpNamef[ttt-1]=='e')
    					) if(ii>1)SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)fullTmpNamef);
                    fseek( in, count, SEEK_SET );
                    if(ii>1){
					        if((out = fopen(namef, "wb")) == NULL) {
							SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"Error write out: new file");
							return 1;
						}
                    }
                    for(n=0; n<acount[ii]-acount[ii-1]; n++){
                        ch = fgetc(in);
                        if(!feof(in)) {
                        	if(ii>1)fputc((int)ch, out);
                        	count++;
                        }
                    }
                    if(ii>1)fclose(out);
                    if(
            			(fullTmpNamef[ttt-4]=='.') &&
            			(fullTmpNamef[ttt-3]=='i') &&
            			(fullTmpNamef[ttt-2]=='n') &&
            			(fullTmpNamef[ttt-1]=='i')
    					) if(ii>1)SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)fullTmpNamef);
                    if(
                    	(fullTmpNamef[ttt-7]=='.') &&
                    	(fullTmpNamef[ttt-6]=='c') &&
                		(fullTmpNamef[ttt-5]=='o') &&
            			(fullTmpNamef[ttt-4]=='n') &&
            			(fullTmpNamef[ttt-3]=='f') &&
            			(fullTmpNamef[ttt-2]=='i') &&
            			(fullTmpNamef[ttt-1]=='g')
    					) if(ii>1)SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)fullTmpNamef);
            		SendMessage(list1,LB_SETCARETINDEX,(int)SendMessage(list1,LB_GETCOUNT,0,0),FALSE);
            		SendMessage(FHandle, PBM_SETPOS, ii+1, 0);
                    UpdateWindow(hMainWnd);//обновили окно и список list1, отобразили создание нового файла
                }
				fclose(in);
                ShowWindow(hButton2, SW_HIDE);
				ShowWindow(hButton24, SW_SHOW);
                ShowWindow(hButton25, SW_SHOW);
				ShowWindow(hButton26, SW_SHOW);
				ShowWindow(hButton27, SW_SHOW);
                SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) "-----------------------------------");
                SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) "--   Процесс распаковки завершен --");
                SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR) "-----------------------------------");
                SendMessage(list1,LB_SETCARETINDEX,(int)SendMessage(list1,LB_GETCOUNT,0,0),FALSE);
				STARTUPINFO cif;
				ZeroMemory(&cif,sizeof(STARTUPINFO));
				PROCESS_INFORMATION pi;
				cif.wShowWindow = SW_HIDE;
				char openExplorer[260] = "";
				char openFolder[260] = "";
                GetWindowText(hEdit1, openFolder, 260);
				strcpy(openExplorer, "explorer ");
				strcat(openExplorer, openFolder);
				CreateProcess(0 , openExplorer,0,0,FALSE,0,0, 0,&cif,&pi);
	        }//if UnPack

//Services
			if(((HWND)lParam == hButton23) && (HIWORD(wParam) == BN_CLICKED)) {
				STARTUPINFO cif;
	            ZeroMemory(&cif,sizeof(STARTUPINFO));
	            PROCESS_INFORMATION pi;
				cif.wShowWindow = SW_SHOW;
				char buf[260]="";
				char tempBuf[260]="";
				GetSystemDirectory(buf, 255);
				strcat(tempBuf, buf);
				strcat(tempBuf, "\\mmc.exe ");
				strcat(tempBuf, buf);
				strcat(tempBuf, "\\services.msc /s");
				CreateProcess(0, tempBuf,0,0,FALSE,0,0,0,&cif,&pi);
			}

//Change EX
			if(((HWND)lParam == hButton22) && (HIWORD(wParam) == BN_CLICKED)) {
				char szDir[MAX_PATH];
				GetWindowText(hEdit2, szDir, 260);
				findAllFiles(szDir, strlen(szDir)+1);
				ShowWindow(hButton22, SW_HIDE);
	            ShowWindow(hButton1, SW_SHOW);
			}
			if(((HWND)lParam == hButton24) && (HIWORD(wParam) == BN_CLICKED)) {
				EX=1;
			}
			if(((HWND)lParam == hButton25) && (HIWORD(wParam) == BN_CLICKED)) {
				EX=2;
			}
			if(((HWND)lParam == hButton26) && (HIWORD(wParam) == BN_CLICKED)) {
				EX=3;
			}
			if(((HWND)lParam == hButton27) && (HIWORD(wParam) == BN_CLICKED)) {
				EX=4;
			}
//Install
			if(((HWND)lParam == hButton4) && (HIWORD(wParam) == BN_CLICKED)) {
			    int i, tmpN;
				STARTUPINFO cif;
	            ZeroMemory(&cif,sizeof(STARTUPINFO));
	            PROCESS_INFORMATION pi;
	            char fullName[260] = "";
	            char Name[260] = "";
	            char folderName[260] = "";
	            char fileName[260] = "";
	            int nSel = SendMessage(list1, LB_GETCURSEL, 0, 0);
	            SendMessage(list1, LB_GETTEXT, nSel, (LPARAM)(LPCSTR) fullName);
	            char winFolder[260] = "";
	            char frameworkFolder[260]="";
	            GetWindowsDirectory(winFolder, 260);
	            strcpy(frameworkFolder, winFolder);
	            strcat(frameworkFolder, "\\Microsoft.NET\\Framework\\v2.0.50727\\");
                strcpy(folderName, fullName);
	            int ttt=strlen(fullName);
                for(i = strlen(fullName); ((fullName[i-1]!='\\') && (i !=0)); i--);
				folderName[i]='\0';
                for(tmpN = i; tmpN <= strlen(fullName); tmpN++)
                	fileName[tmpN-i] = fullName[tmpN];
{
					char tempFolder[260] = "";
					char tempName[260] = "";
					strcpy(tempFolder, folderName);
					strcpy(tempName, tempFolder);
					if(EX==1){
						strcpy(tempName, winFolder);
						strcat(tempName, "\\notepad.exe ");
						strcat(tempName, fullName);
					}
					if(EX==2){
						strcpy(tempName, fullName);
						strcat(tempName, " -install");
					}
					if(EX==3){
						if(!CopyFile("InstallUtil.exe", frameworkFolder, folderName, 0)) {
							MessageBox(hMainWnd, "Пожалуйста, установите FrameWork 2.0", "Ошибка", MB_OK);
							return 1;
						}
						strcat(tempName, "InstallUtil.exe ");
						strcat(tempName, fullName);
					}
					if(EX==4){
						strcpy(tempName, fullName);//переделать на добавления файла без пути, а не копирование полного пути
					}
					if(EX==0){
						MessageBox(hMainWnd, "Пожалуйста, выберите способ установки.", "Ошибка", MB_OK);
						return 1;
					}
					cif.wShowWindow = SW_SHOW;
					CreateProcess(0 , tempName,0,0,FALSE,0,0, tempFolder,&cif,&pi);
					MessageBox(hMainWnd, tempName, "Установлен/Запущен", MB_OK);
				}
			}
        }//case

        default:
                return DefWindowProc(hMainWnd, iMsg, wParam, lParam);
        }//switch
        return 0;
}
