#include <SDL.h>
#include <iostream>
#include <string>
#include <iomanip>
#include "Mouse.h"
#include "Shape.h"
#include "DLL.h"
#include "DisplayMenu.h"

const int WIN_HEIGHT = 800;
const int WIN_WIDTH = 500;
int main(int arc, char *argv[])
{
	
	bool quit = false;
	bool secondQuit = false;
	LButton select;

	//window handle
	SDL_Window *window = NULL;

	//use the surface to draw on
	SDL_Surface *screenSurface = NULL;

	//Render
	SDL_Renderer *render = NULL;

	//Event object, to process keyboard, mouse, etc.


	//Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << " SDL Could not initialize! Error" << std::endl;
	}
	/* Create
	1) a graphics window renderer
	2) a surface for the renderer to render on
	*/

	if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, 
		SDL_WINDOW_RESIZABLE, &window, &render))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
			"Could not create window and renderer: %s", SDL_GetError());
		return 3;

	}
	int inArray = 0;
	SDL_Event event;
	int xMouse, yMouse;
	xMouse = yMouse = -1;
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	Point a, b, c;
	int *xPointArray;
	int *yPointArray;
	int triItr = 0;
	int quadItr = 0;
	int moveItr1 = 0;
	int moveItr2 = 0;
	bool check = false;

	DisplayMenu(render);

	dLL<Shape*> shape_list; 

	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_SetRenderDrawColor(render, 194, 255, 245, 255);
				SDL_GetMouseState(&xMouse, &yMouse);
				if ((triButton.getAX() < xMouse  && xMouse 
					< triButton.getBX()) && (triButton.getAY() 
						< yMouse && yMouse < triButton.getBY()))
				{//if inside first button
					xPointArray = new int[3];
					yPointArray = new int[3];
					triItr = 0;
					secondQuit = false;
					while (!secondQuit && !quit)
					{
						while ((SDL_WaitEvent(&event)) && (triItr < 3)) {
							//waits for user to click three times
							xMouse = yMouse = -1;
							switch (event.type)
							{
							case SDL_MOUSEBUTTONDOWN:
								
								SDL_GetMouseState(&xMouse, &yMouse);
								SDL_RenderDrawPoint(render, xMouse, yMouse);
								if (xMouse != -1)
								{
									xPointArray[triItr] = xMouse;
									yPointArray[triItr] = yMouse;
								}
								triItr++;
								break;
							case SDL_QUIT:
								quit = true;
								break;
								SDL_RenderPresent(render);
							}//end of triangle switch
							SDL_RenderPresent(render);
						}
						//add new triangle, draw
						shape_list.insert(new Triangle(xPointArray[0],
							yPointArray[0], xPointArray[1], yPointArray[1],
							xPointArray[2], yPointArray[2]));

						inArray++;

						shape_list.get(1)->Draw(render); 
					//	shape_list.Draw(inArray, render);
						SDL_RenderPresent(render);
						delete[] yPointArray;
						delete[] xPointArray;
						yPointArray = nullptr;
						xPointArray = nullptr;
						xMouse = yMouse = -1;
						secondQuit = true;
					} //end of quit loop 
				} //endif
				else if (quadButton.getAX() < xMouse && xMouse
					< quadButton.getBX() && quadButton.getAY() 
					< yMouse  && yMouse < quadButton.getBY())
				{//if insides second button
					SDL_SetRenderDrawColor(render, 194, 255, 245, 255);

					xPointArray = new int[2];
					yPointArray = new int[2];
					quadItr = 0;
					secondQuit = false;
					while (!secondQuit && !quit)
					{
						while ((SDL_WaitEvent(&event)) && (quadItr < 2)) {
							xMouse = yMouse = -1;
							switch (event.type)
							{
							case SDL_MOUSEBUTTONDOWN:
								SDL_GetMouseState(&xMouse, &yMouse);
								SDL_RenderDrawPoint(render, xMouse, yMouse);
								if (xMouse != -1)
								{
									xPointArray[quadItr] = xMouse;
									yPointArray[quadItr] = yMouse;
								}
								quadItr++;
								break;
							case SDL_QUIT:
								quit = true;
								break;
								SDL_RenderPresent(render);
							}//end of rectangle switch
							SDL_RenderPresent(render);
						}
						//draw and add new quad
						SDL_RenderDrawLine(render, xPointArray[0], yPointArray[0], 
							xPointArray[1], yPointArray[0]);
						SDL_RenderDrawLine(render, xPointArray[1], yPointArray[1], 
							xPointArray[0], yPointArray[1]);
						SDL_RenderDrawLine(render, xPointArray[0], yPointArray[1], 
							xPointArray[0], yPointArray[0]);
						SDL_RenderDrawLine(render, xPointArray[1], yPointArray[0], 
							xPointArray[1], yPointArray[1]);
						SDL_RenderPresent(render);
						shape_list.insert(new Quad(xPointArray[0], yPointArray[0], 
							xPointArray[1], yPointArray[1]));

						inArray++;
						shape_list.get(1)->Draw(render);

						//clean up 
						delete[] yPointArray;
						delete[] xPointArray;
						yPointArray = nullptr;
						xPointArray = nullptr;
						xMouse = yMouse = -1;
						secondQuit = true;
					} //end of quit loop 
				}//end if
				else if (moveButton.getAX() < xMouse && xMouse 
					< moveButton.getBX() && moveButton.getAY() 
					< yMouse  && yMouse < moveButton.getBY())
				{//if inside third button
					SDL_SetRenderDrawColor(render, 194, 255, 245, 255);
					xPointArray = new int[2];
					yPointArray = new int[2];
					moveItr1 = 0;
					moveItr2 = 0;
					secondQuit = false;

					while (!secondQuit && !quit)
					{
						while ((SDL_WaitEvent(&event)) && (moveItr1 < 2)) {
							//waits for user to click twice
							xMouse = yMouse = -1;
							switch (event.type)
							{
							case SDL_MOUSEBUTTONDOWN:
								SDL_GetMouseState(&xMouse, &yMouse);
								SDL_RenderDrawPoint(render, xMouse, yMouse);
								if (xMouse != -1)
								{
									xPointArray[moveItr1] = xMouse;
									yPointArray[moveItr1] = yMouse;
								}
								moveItr1++;
								break;
							case SDL_QUIT:
								quit = true;	
								break;
							}//end of rectangle switch
							SDL_RenderPresent(render);
						}
						//draws area selected
						SDL_SetRenderDrawColor(render, 229, 225, 225, 255);
						SDL_RenderDrawLine(render, xPointArray[0], yPointArray[0], 
							xPointArray[1], yPointArray[0]);
						SDL_RenderDrawLine(render, xPointArray[1], yPointArray[1],
							xPointArray[0], yPointArray[1]);
						SDL_RenderDrawLine(render, xPointArray[0], yPointArray[1],
							xPointArray[0], yPointArray[0]);
						SDL_RenderDrawLine(render, xPointArray[1], yPointArray[0],
							xPointArray[1], yPointArray[1]);
						Quad searchArea(xPointArray[0], yPointArray[0],
							xPointArray[1], yPointArray[1]);
						//creates new points for moving
						Point xy1(xPointArray[0], yPointArray[0]);
						Point xy2(xPointArray[1], yPointArray[1]);
						SDL_RenderPresent(render);
						for (int i = 1; i <= inArray; i++)
						{

							check = shape_list.get(i)->inBounds(xy1, xy2);

							if (check)
							{
								secondQuit = false;
								while (!secondQuit && !quit)
								{
									while ((SDL_WaitEvent(&event)) && (moveItr2 < 1)) {
										//waits for user to click once
										xMouse = yMouse = -1;
										switch (event.type)
										{ 
										case SDL_MOUSEBUTTONDOWN:
											SDL_GetMouseState(&xMouse, &yMouse);
											SDL_RenderDrawPoint(render, xMouse, yMouse);
											if (xMouse != -1)
											{
												xPointArray[moveItr2] = xMouse;
												yPointArray[moveItr2] = yMouse;
											}
											moveItr2++;
											break;
										case SDL_QUIT:
											quit = true;
											break;
											SDL_RenderPresent(render);
										}//end of rectangle switch
										SDL_RenderPresent(render);
									}
									//creates new points to move object by
									Point xy3(xPointArray[0], yPointArray[0]);
									Point xy4((xy3.getX() + (xy2.getX() - xy1.getX())), 
										(xy3.getY() + (xy2.getY() - xy1.getY())));
									SDL_SetRenderDrawColor(render, 229, 225, 225, 255);
									SDL_RenderDrawLine(render, xy3.getX(),
										xy3.getY(), xy3.getX(), xy4.getY());
									SDL_RenderDrawLine(render, xy3.getX(),
										xy3.getY(), xy4.getX(), xy3.getY());
									SDL_RenderDrawLine(render, xy4.getX(), 
										xy4.getY(), xy3.getX(), xy4.getY());
									SDL_RenderDrawLine(render, xy4.getX(), 
										xy4.getY(), xy4.getX(), xy3.getY());
									
									Quad moveArea(xy3.getX(), xy3.getY(), xy4.getX(), xy4.getY());
									searchArea.erase(render);
									moveArea.erase(render);
									//gets difference between original and new position
									int newX1 = xy3.getX() - xy1.getX();
									int newY1 = xy3.getY() - xy1.getY();
									int newX2 = xy4.getX() - xy2.getX();
									int newY2 = xy4.getY() - xy2.getY();
									//creates new points to move object by
									Point move1(newX1, newY1);
									Point move2(newX2, newY2);
									//erases old, draws new
									shape_list.get(i)->erase(render);
									shape_list.get(i)->moveBy(move1, move2);
									shape_list.get(i)->Draw(render);
									SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
									break;
								}
								SDL_RenderPresent;
							}
							else if(!check)
							{
								//if not all points are inside selection area
								SDL_Delay(300);
								searchArea.erase(render);
							}
						}//end of for checking inbounds
						delete[] yPointArray;
						delete[] xPointArray;
						yPointArray = nullptr;
						xPointArray = nullptr;
						xMouse = yMouse = -1;
						secondQuit = true;
					} //end of quit loop 
				}//endif

				else if (clearButton.getAX() < xMouse && xMouse 
					< clearButton.getBX() && clearButton.getAY() 
					< yMouse  && yMouse < clearButton.getBY())
				{//inside fourth button
					SDL_SetRenderDrawColor(render, 194, 255, 245, 255);
					xPointArray = new int[2];
					yPointArray = new int[2];
					moveItr1 = 0;
					secondQuit = false;

					while (!secondQuit && !quit)
					{
						while ((SDL_WaitEvent(&event)) && (moveItr1 < 2)) {
							//waits for user to click twice
							//similar to move button function
							xMouse = yMouse = -1;
							switch (event.type)
							{
							case SDL_MOUSEBUTTONDOWN:
								SDL_GetMouseState(&xMouse, &yMouse);
								SDL_RenderDrawPoint(render, xMouse, yMouse);
								if (xMouse != -1)
								{
									xPointArray[moveItr1] = xMouse;
									yPointArray[moveItr1] = yMouse;
								}
								moveItr1++;
								break;
							case SDL_QUIT:
								quit = true;
									break;
							}//end of rectangle switch
							SDL_RenderPresent(render);
						}//wait end 
						//draws selection area
						SDL_SetRenderDrawColor(render, 229, 225, 225, 255);
						SDL_RenderDrawLine(render, xPointArray[0], yPointArray[0], xPointArray[1], yPointArray[0]);
						SDL_RenderDrawLine(render, xPointArray[1], yPointArray[1], xPointArray[0], yPointArray[1]);
						SDL_RenderDrawLine(render, xPointArray[0], yPointArray[1], xPointArray[0], yPointArray[0]);
						SDL_RenderDrawLine(render, xPointArray[1], yPointArray[0], xPointArray[1], yPointArray[1]);
						Quad searchArea(xPointArray[0], yPointArray[0], xPointArray[1], yPointArray[1]);

						Point xy1(xPointArray[0], yPointArray[0]);
						Point xy2(xPointArray[1], yPointArray[1]);
						SDL_RenderPresent(render);
						for (int i = 1; i <= inArray; i++)
						{	
							check = shape_list.get(i)->inBounds(xy1, xy2);

							if (check)
							{
								shape_list.get(i)->erase(render);
								shape_list.remove(i); 
								//erases object in bounds
								searchArea.erase(render);
								inArray--;

							}//check if
							else if (!check)
							{
								SDL_Delay(300);
								searchArea.erase(render);
							}
						}//end of for checking inbounds
						//clean up
						delete[] yPointArray;
						delete[] xPointArray;
						yPointArray = nullptr;
						xPointArray = nullptr;
						xMouse = yMouse = -1;
						secondQuit = true;
					} //end of quit loop
				}//end if
				else if (quitButton.getAX() < xMouse && xMouse < quitButton.getBX() && quitButton.getAY() < yMouse  && yMouse < quitButton.getBY())
				{//if inside last button
					secondQuit = true;
					quit = true;
					break;
				}//end if
				break;
			}// end of final switch
			SDL_RenderPresent(render);
		} //end of poll event
		SDL_RenderPresent(render);
	} //end of quit
	
	
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}