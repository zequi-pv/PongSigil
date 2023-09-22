#include "sl.h"

int main()
{
	const int width = 400;
	const int height = 400;

	slWindow(width, height, "Simple SIGIL Example", false);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slSetBackColor(0.0, 0.600, 0.0);

		slSetForeColor(0, 0, 1, 1);
		slSetFont(slLoadFont("fonts/arial.ttf"), 20);
		slSetTextAlign(SL_ALIGN_CENTER);
		slSetFontSize(20);
		slText(200,200,"Hola");
		//slSetForeColor(1, 1, 1, 1);
		//slRectangleFill(width * 0.5, height * 0.5, 100, 100);

		slRender();
	}

	slClose();

	return 0;
}