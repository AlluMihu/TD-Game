#include <allegro5\allegro.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include <cmath>
#include <iostream>
#include <fstream>

#include "Player.h"
#include "globals.h"
#include "Background.h"
#include "Bullets.h"
#include "Enemy.h"
#include "Terrorist.h"
#include "Obstacle.h"

Background::Background(){
}

Background::Background(float x1, float y1,float width1, float height1, ALLEGRO_BITMAP *image1){	
	x = x1;
	y = y1;
	width = width1;
	height = height1;
	image = image1;
}


Background::~Background(){
}

void Background::DrawBackground(){
	al_draw_bitmap(image, x, y, 0);
}