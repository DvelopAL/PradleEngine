#pragma once

namespace PradleEngine
{
#define CONSOLE_WIDHT 80
#define CONSOLE_HEIGHT 25

#define RGB(text, bg) ( (WORD)(text|(bg<<4)) )
#define COLOR_ALL    16

#define BLACK		  0 //����
#define BLUE		  1 //�Ķ�
#define GREEN		  2 //�ʷ�
#define CYAN		  3 //�þ�
#define RED			  4 //����
#define MAGENTA		  5 //����Ÿ
#define BROWN		  6 //����
#define LIGHTGRAY	  7 //���
#define DARKGRAY	  8 //ȸ�� 
#define LIGHTBLUE	  9 //���� �Ķ�
#define LIGHTGREEN	 10 //���� ���
#define LIGHTCYAN	 11 //���� �þ�
#define LIGHTRED	 12 //���� ����
#define LIGHTMAGENTA 13 //���� ����Ÿ
#define YELLOW		 14 //���� ���
#define WHITE		 15 //���� �Ͼ��

	enum class CODE_PAGE
	{
		KOREAN,
		ENGLISH,
	};
}