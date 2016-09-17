#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

Quad triButton(0, 1, 100, 50);
Quad quadButton(100, 1, 200, 50);
Quad moveButton(200, 1, 300, 50);
Quad clearButton(300, 1, 400, 50);
Quad quitButton(400, 1, 499, 50);
void DisplayMenu(SDL_Renderer *rdr)
{
	triButton.Draw(rdr);
	quadButton.Draw(rdr);
	moveButton.Draw(rdr);
	clearButton.Draw(rdr);
	quitButton.Draw(rdr);

	Triangle triDec(50, 15, 45, 35, 55, 35);
	triDec.Draw(rdr);
	Quad quadDec(143, 15, 158, 35);
	quadDec.Draw(rdr);

	Quad moveDec(243, 15, 258, 35);
	moveDec.Draw(rdr);
	SDL_SetRenderDrawColor(rdr, 0, 0, 0, 255);
	SDL_RenderDrawLine(rdr, 243, 15, 258, 15);
	SDL_RenderDrawLine(rdr, 243, 35, 258, 35);
	SDL_SetRenderDrawColor(rdr, 194, 255, 245, 255);
	SDL_RenderDrawLine(rdr, 243, 15, 251, 25);
	SDL_RenderDrawLine(rdr, 258, 15, 251, 25);

	Quad clearDec(343, 15, 358, 35);
	clearDec.Draw(rdr);
	SDL_SetRenderDrawColor(rdr, 0, 0, 0, 255);
	SDL_RenderDrawLine(rdr, 358, 15, 358, 35);
	Quad quitDec(443, 15, 458, 35);
	quitDec.Draw(rdr);
	SDL_RenderDrawLine(rdr, 451, 25, 460, 34);
}
#endif // !DISPLAYMENU_H
