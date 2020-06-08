//克雷那语输入法计划
//克雷那语，女性化的写作克蕾娜语，意味“天空的语言”
//拉丁字母写法为Klanahawu mwurahaiyapyu

//因为并不存在任何一种编码体系支持这套语言，并暂时无任何计划将其与Unicode字符集进行对应
//我们认为那将可能是对Unicode字符集的一种污染
//因此想要在电脑上输入克雷那语，就需要使用图形化的输入方法，因此您只能在这个编辑程序中输入
//那这就不仅仅是一个输入法，也是一个克雷那语的可视化字处理软件了，它将兼有所见即所得的Word的特点，也有命令式的远古WPS的特点

//在此向中文输入和字处理的先辈们致敬~！王选先生将永远铭记！求伯君先生将永远铭记！

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

int UpperCase[14][9] = {0};
int LowerCase[14][9] = {0};
//得想法从一个文件中读取这个映射表

//TCHAR2char   
void TcharToChar(const TCHAR * tchar, char * _char)
{
	int iLength;
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);//获取字节长度 
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);//将tchar值赋给_char    
}

//char2TCHAR
void CharToTchar(const char * _char, TCHAR * tchar)
{
	int iLength;
	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

int PutCharacter(char *KlanahawuString,int mode)
{
	//mode==1为大写，否则为小写
	//开始进行从前往后的单字解析
	//目前仅支持单字
	//其实要支持多字也行，每次做完一个字符以后就从Buffer里面修剪掉刚刚处理完成的这一个字符
	//应添加对不合法的字符的屏蔽，并给出提示，如有性辅音与后元音的结合中不符合阳阳阴阴的
	int row = -1;
	int column = -1;
	if (KlanahawuString[0] == 'm')
	{
		//是m行-第1行
		row = 0;
		if (KlanahawuString[1] == 'a')
		{
			if (KlanahawuString[2] != 'i')
			{
				//是a列-第1列
				column = 0;
			}
			if (KlanahawuString[2] == 'i')
			{
				//是ai列-第7列
				column = 6;
			}
		}
		if (KlanahawuString[1] == 'y')
		{
			if (KlanahawuString[2] == 'i')
			{
				//是yi列-第2列
				column = 1;
			}
			if (KlanahawuString[2] == 'u')
			{
				//是yu列-第5列
				column = 4;
			}
		}
		if (KlanahawuString[1] == 'l')
		{
			//是la列-第3列
			column = 2;
		}
		if (KlanahawuString[1] == 'w')
		{
			//是wu列-第4列
			column = 3;
		}
		if (KlanahawuString[1] == 'e')
		{
			//是ei列-第6列
			column = 5;
		}
		if (KlanahawuString[1] == 'o')
		{
			//是ou列-第8列
			column = 7;
		}
		if (KlanahawuString[1] == 'r')
		{
			//是ru列-第9列
			column = 8;
		}
	}
	if (KlanahawuString[0] == 'n')
	{
		//是n行-第2行
		row = 1;
	}
	if (KlanahawuString[0] == 'p')
	{
		//是p行-第3行
		row = 2;
	}
	if (KlanahawuString[0] == 't')
	{
		//是t行-第4行
		row = 3;
	}
	if (KlanahawuString[0] == 'k')
	{
		//是k行-第6行
		row = 5;
	}
	if (KlanahawuString[0] == 'f')
	{
		//是fa行-第11行
		row = 10;
	}
	if (KlanahawuString[0] == 'v')
	{
		//是va行-第12行
		row = 11;
	}
	if (KlanahawuString[0] == 'y')
	{
		//是ya行-第13行
		row = 12;
	}
	if (KlanahawuString[0] == 'r')
	{
		//是r行-第14行
		row = 13;
	}
	if (KlanahawuString[0] == 's')
	{
		//是sh/sa/sah行
		if (KlanahawuString[1] == 'h')
		{
			//是sh行-第5行
			row = 4;
		}
		if (KlanahawuString[1] == 'a'&&KlanahawuString[2] != 'h')
		{
			//是sa-第7行
			row = 6;
		}
		if (KlanahawuString[1] == 'a'&&KlanahawuString[2] == 'h')
		{
			//是sah行-第8行
			row = 7;
		}
	}
	if (KlanahawuString[0] == 'h')
	{
		//是h/ha行
		//if (KlanahawuString[1] ！= 'a')
		//{
		//	//是sh行-第5行
		//row=4;
		//}
		//if (KlanahawuString[1] == 'a')
		//{
		//	//是ha-第7行
		//row=6;
		//}

		//这两行很乱我还没想好怎么写
	}
	//在上面判断清楚r和c之后，就可以去根据大小写来申请输入了
	if (mode == 1)
	{
		//大写
		if (CurrentW >= W_Limit)
		{
			CurrentW = 0;
			CurrentPixelW = 0;
			CurrentH += 1;
			CurrentPixelH += KLANAHAWU_H;
		}
		CurrentW += 1;
		CurrentPixelW += KLANAHAWU_W;
		int CharNum = UpperCase[row][column];
		char filename[50] = { '0' };
		char filenameExtend[] = { ".jpg" };
		itoa(CharNum, filename,10);
		strcat(filename, filenameExtend);
		printf("你的文件名是%s\n", filename);
	}
	else
	{
		//小写
	}
	return 0;
}

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

	//未来早晚换成百分比定义的，实现响应式设计（笑）

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
		InteractiveAction = GetMouseMsg();
		switch (InteractiveAction.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			if (InteractiveAction.x >= ExitButtonL && InteractiveAction.x <= ExitButtonR && InteractiveAction.y >= ExitButtonU && InteractiveAction.y <= ExitButtonD)
			{
				printf("\n%s\n", Buffer);
				closegraph();
				printf("您可选中文本后右键点击以复制\n");
				system("PAUSE");
				exit(0);
			}
			else if (InteractiveAction.x >= InputWordButtonL && InteractiveAction.x <= InputWordButtonR && InteractiveAction.y >= InputWordButtonU && InteractiveAction.y <= InputWordButtonD)
			{
				TCHAR TempInput_TCHAR[20 + 1];
				char TempInput_CHAR[20 + 1];
				if (InteractiveAction.mkShift == 1 || InteractiveAction.mkCtrl == 1)
				{
					InputBox(TempInput_TCHAR, 20 + 1, TEXT("请输入拉丁写法，纯小写"));
					TcharToChar(TempInput_TCHAR, TempInput_CHAR);
					//printf("%s", TempInput_CHAR);
					strcat(Buffer, TempInput_CHAR);
					PutCharacter(TempInput_CHAR,1);
					//outtext(UPPERCASE);
					//输出大写
				}
				else
				{
					InputBox(TempInput_TCHAR, 20 + 1, TEXT("请输入拉丁写法，纯小写"));
					TcharToChar(TempInput_TCHAR, TempInput_CHAR);
					//printf("%s", TempInput_CHAR);
					strcat(Buffer, TempInput_CHAR);
					PutCharacter(TempInput_CHAR,0);
					//outtext(LOWERCASE);
					//输出小写
				}
			}
			else if (InteractiveAction.x >= PasteTextButtonL && InteractiveAction.x <= PasteTextButtonR && InteractiveAction.y >= PasteTextButtonU && InteractiveAction.y <= PasteTextButtonD)
			{
				printf("%s\n", Buffer);
			}
		}
		}
	}
	return 0;
}