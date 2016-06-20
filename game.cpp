/****************************************
 * The game of moonlander
 ****************************************/

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "velocity.h"
#include "lander.h"

#define GRAVITY     .05    // the moon's gravity
#define MIN_SPEED   3.0    // minimal landing speed
#define FALL_HEIGHT 4.0    // greatest height we can fall from

#define X_SIZE       600
#define Y_SIZE       400

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   // create the game
   Game() : dead(false), landed(false), fuel(FUEL),
    isLeft(false), isRight(false), isUp(false),
    platform(ground.getPlatformPosition()),
    lander(random(-(X_SIZE/2)+10, (X_SIZE/2)-10), random(40, Y_SIZE /2) -10){}
   
    // handle user input
   void input(const Interface & ui);

   // advance the game
   void advance();
         
   // draw stuff
   void draw(const Interface & ui) const;
   
private:
    bool justLanded() const;
    bool isLeft;
    bool isRight;
    bool isUp;
    
   
   int  fuel;
   bool dead;
   bool landed;
   Ground ground;
    Point platform;

    Lander lander;
};

/******************************************
 * GAME :: LANDED
 * Did we land successfully?
 ******************************************/
bool Game :: justLanded() const
{
     
   // TODO: indicate if the lander has landed
    if(platform.getX() -(PLATFORM / 2.0) <= lander.getX() &&
       platform.getX() +(PLATFORM / 2.0) >= lander.getX() &&
       platform.getY() <= lander.getY() &&
       platform.getY() +4.0 >= lander.getY() &&
       lander.getDy() <= 0.3 &&
       lander.getDx() <= 0.3)
    {
        return true;
    }
    else
        return false;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   // TODO: move lander and check for crashed
    landed = justLanded();
    if (landed)
    {
        lander.setPoint(platform);
        lander.setDx(0);
        lander.setDy(0);
        
        if (ui.isSpace())
        {
            
        }
    }
    else
    {
    if(ground.crashed(lander.getPoint()))
    {
        dead = true;
    }
    if(!dead)
    {
        lander.advance(isLeft, isRight, isUp);
        fuel = lander.getFuel();
    }
    }
}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: input(const Interface & ui)
{
   // TODO: handle user input
    if(ui.isUp())
        isUp = true;
    else
        isUp = false;
    if(ui.isLeft())
        isLeft = true;
    else
        isLeft = false;
    if(ui.isRight())
        isRight = true;
    else
        isRight = false;
    
   // Note that you can discover keys that were pressed by checking
   // methods such as ui.isUp(), ui.isLeft(), etc.
   // see Pong for an example

}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui) const
{
   // TODO: draw the lander or a status message
    lander.draw();
    if(dead)
        drawText(Point( -60, 100), "You failed America.");
    if(landed)
    {
        drawText(Point(-150, 100), "That’s one small step for man,\n one giant leap for mankind");
    }
   // TODO: draw the fuel
    drawText(Point(-(X_SIZE / 2) + 10, (Y_SIZE / 2) - 20), "Fuel: ");
    drawNumber(Point(-(X_SIZE / 2) + 50, (Y_SIZE / 2) - 10), fuel);
    
    // draw xSpeed and ySpeed
    if (lander.getDx() >= 0)
    {
       drawText(Point((X_SIZE / 2) - 100, (Y_SIZE / 2) - 20), "xSpeed: ");
       drawNumber(Point((X_SIZE / 2) - 40, (Y_SIZE / 2) - 10), lander.getDx()*10);
    }
    else
    {
       drawText(Point((X_SIZE / 2) - 100, (Y_SIZE / 2) - 20), "xSpeed:-");
       drawNumber(Point((X_SIZE / 2) - 40, (Y_SIZE / 2) - 10), (-(lander.getDx()))*10);
    }
    if (lander.getDy() >= 0)
    {
       drawText(Point((X_SIZE / 2) - 100, (Y_SIZE / 2) - 50), "ySpeed: ");
       drawNumber(Point((X_SIZE / 2) - 40, (Y_SIZE / 2) - 40), lander.getDy()*10);
    }
    else
    {
       drawText(Point((X_SIZE / 2) - 100, (Y_SIZE / 2) - 50), "ySpeed:-");
       drawNumber(Point((X_SIZE / 2) - 40, (Y_SIZE / 2) - 40), (-(lander.getDy()))*10);
    }
    
   // draw ground
   ground.draw();
}


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p;
   
   pGame->advance();
   
   pGame->input(*pUI);
   
   pGame->draw(*pUI);
}

// set the bounds of the drawing rectangle
float Point::xMin = -(X_SIZE / 2.0);
float Point::xMax =  (X_SIZE / 2.0);
float Point::yMin = -(Y_SIZE / 2.0);
float Point::yMax =  (Y_SIZE / 2.0);

/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Moon Lander");
   Game game;
   ui.run(callBack, &game);
   
   return 0;
}
