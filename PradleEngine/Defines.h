#pragma once

namespace PradleEngine
{
#define CONSOLE_WIDHT 80
#define CONSOLE_HEIGHT 25

#define RGB(text, bg) ( (WORD)(text|(bg<<4)) )
#define COLOR_ALL    16

#define BLACK		  0 //°ËÁ¤
#define BLUE		  1 //ÆÄ¶û
#define GREEN		  2 //ÃÊ·Ï
#define CYAN		  3 //½Ã¾È
#define RED			  4 //»¡°­
#define MAGENTA		  5 //¸¶Á¨Å¸
#define BROWN		  6 //°¥»ö
#define LIGHTGRAY	  7 //Èò»ö
#define DARKGRAY	  8 //È¸»ö 
#define LIGHTBLUE	  9 //¹àÀº ÆÄ¶û
#define LIGHTGREEN	 10 //¹àÀº ³ì»ö
#define LIGHTCYAN	 11 //¹àÀº ½Ã¾È
#define LIGHTRED	 12 //¹àÀº »¡°­
#define LIGHTMAGENTA 13 //¹àÀº ¸¶Á¨Å¸
#define YELLOW		 14 //¹àÀº ³ë¶û
#define WHITE		 15 //¹àÀº ÇÏ¾á»ö

	enum class CODE_PAGE
	{
		KOREAN,
		ENGLISH,
	};
}