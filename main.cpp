#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 800
#define H 450
#define MAXLEN 200
#define KLANAHAWU_PIXEL 25
#define KLANAHAWU_W 2*KLANAHAWU_PIXEL
#define KLANAHAWU_H KLANAHAWU_PIXEL+2*KLANAHAWU_PIXEL+KLANAHAWU_PIXEL
int CurrentW = 0;
int CurrentH = 0;
int CurrentPixelW = 0;
int CurrentPixelH = 0;
int W_Limit = W / KLANAHAWU_W;
int H_Limit = 350 / KLANAHAWU_H;

int main(int argc, char *argv[])
{
	TCHAR Klanahawu_mwurahaiyapyu[] = { TEXT("Klanahawu_mwurahaiyapyu") };
	TCHAR UPPERCASE[] = { TEXT("UPPERCASE") };
	TCHAR UPPERCASE_Notice[] = { TEXT("按住shift或ctrl点击可输入大写") };
	TCHAR Buffer_Notice[] = { TEXT("还没法读取剪贴板所以就直接printf") };
	TCHAR LOWERCASE[] = { TEXT("LOWERCASE") };
	TCHAR InputWord_Notice[] = { TEXT("输入") };
	TCHAR PasteText_Notice[] = { TEXT("复制") };
	initgraph(W, H, SHOWCONSOLE);
	char Buffer[MAXLEN] = { "klanahawu:\n" };

	//输入按钮
	int InputWordButtonL = 50;
	int InputWordButtonU = 370;
	int InputWordButtonR = InputWordButtonL + 325;
	int InputWordButtonD = InputWordButtonU + 40;
	rectangle(InputWordButtonL, InputWordButtonU, InputWordButtonR, InputWordButtonD);
	//复制按钮
	int PasteTextButtonL = 425;
	int PasteTextButtonU = 370;
	int PasteTextButtonR = PasteTextButtonL + 325;
	int PasteTextButtonD = PasteTextButtonU + 40;
	rectangle(PasteTextButtonL, PasteTextButtonU, PasteTextButtonR, PasteTextButtonD);
	//退出按钮
	int ExitButtonL = 50;
	int ExitButtonU = 420;
	int ExitButtonR = ExitButtonL + 700;
	int ExitButtonD = ExitButtonU + 20;
	rectangle(ExitButtonL, ExitButtonU, ExitButtonR, ExitButtonD);

	setfillcolor(RED);
	solidrectangle(ExitButtonL + 1, ExitButtonU + 1, ExitButtonR - 1, ExitButtonD - 1);

	outtextxy(InputWordButtonL + 150, InputWordButtonU + 2, InputWord_Notice);
	outtextxy(PasteTextButtonL + 150, PasteTextButtonU + 2, PasteText_Notice);
	outtextxy(InputWordButtonL + 65, InputWordButtonU + 20, UPPERCASE_Notice);
	outtextxy(PasteTextButtonL + 50, PasteTextButtonU + 20, Buffer_Notice);
	MOUSEMSG InteractiveAction;
	while (true)
	{
	}
	return 0;
}