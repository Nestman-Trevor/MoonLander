//
//  lander.cpp
//  Project2
//
//  Created by Trevor on 2/23/15.
//  Copyright (c) 2015 Trevor. All rights reserved.
//

#include "lander.h"
#include "uiDraw.h"


void Lander :: draw()const
{
    drawLander(getPoint());
}

void Lander::advance(bool bLeft, bool bRight, bool bUp)
{
    if (fuel > 0)
    {
    if (bLeft)
    {
        velocity.setDx(velocity.getDx() +.03);
        fuel -= 1;
    }
    if (bRight)
    {
        velocity.setDx(velocity.getDx() -.03);
        fuel -= 1;
    }
    if (bUp)
    {
        velocity.setDy(velocity.getDy() +.1);
        fuel -= 1;
    }
    
    drawLanderFlames(getPoint(), bUp, bLeft, bRight);
    }
    velocity.setDy(velocity.getDy() - GRAVITY);
    velocity.addX(velocity.getDx());
    velocity.addY(velocity.getDy());
}
