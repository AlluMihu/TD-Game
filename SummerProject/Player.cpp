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

Player::Player()
{
	x = 3;
	y = heightSquare / 2 - 2;
	boundx = 2;
	boundy = 4;
	speed = 0.1;
	lives = 5;
}

Player::Player(ALLEGRO_BITMAP *playerBitmap){
	x = 3;
	y = heightSquare / 2 - 2;
	boundx = 2;
	boundy = 4;
	speed = 0.1;
	lives = 5;

	image = playerBitmap;
}


Player::~Player()
{
}

void Player::MoveUp(){
	y -= speed;

	if (y < 0){
		y = 0;
	}
}
void Player::MoveDown(){
	y += speed;

	if (y > heightSquare - boundy){
		y = heightSquare - boundy;
	}
}
void Player::DrawPlayer(){
	//al_draw_filled_rectangle(x * square_l, y * square_l, square_l * (x + boundx), square_l * (y + boundy), al_map_rgb(137, 85, 56));
	al_draw_bitmap(image, x * square_l, y * square_l, 0);
}
void Player::Shoot(){

}
void Player::SetLive(int x){
	lives = x;
}
void Player::SetScore(int x){
	score = x;
}

float Player::getX(){
	return x;
}
float Player::getY(){
	return y;
}
int Player::getLives(){
	return lives;
}
int Player::getScore(){
	return score;
}