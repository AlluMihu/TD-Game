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

const int square_l = 20;
const int widthSquare = 55;
const int heightSquare = 35;
const int GAME_PIXEL_WIDTH = 1100;
const int GAME_PIXEL_HEIGHT = 700;
const int FPS = 60;
const int maxBullets = 1;
const int maxEnemy = 500;

//GameStates
bool MainMenu = true;
bool LevelMenu = false;
bool GameLoop = false;
bool GameOver = false;
bool Win = true;

bool done = false;
bool redraw = false;
bool reload = false;

enum KEYS{UP, DOWN};
bool keys[2] = { false, false };

struct teroSettings{
	int timeFPS;
	float y;
};

void SelectLevel(int x);

int main(void){
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *imageBG = NULL;
	ALLEGRO_BITMAP *imageLevel = NULL;
	ALLEGRO_FONT *font24 = NULL;

	if (!al_init())
		return -1;

	display = al_create_display(GAME_PIXEL_WIDTH, GAME_PIXEL_HEIGHT);

	if (!display)
		return -1;

	//installs and inits
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_install_keyboard();
	al_install_mouse();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();

	imageBG = al_load_bitmap("sandBG.png");
	Background BG(0, 0, GAME_PIXEL_WIDTH, GAME_PIXEL_HEIGHT, imageBG);

	imageLevel = al_load_bitmap("LevelSelect.png");


	ALLEGRO_BITMAP *playerBitmap = NULL;
	playerBitmap = al_load_bitmap("player.png");
	Player player(playerBitmap);

	Bullets bullets[maxBullets];
	Bullets bulletsUsed[maxBullets];
	font24 = al_load_font("Montserrat-Regular.ttf", 24, 0);
	
	ALLEGRO_BITMAP *obstacleBitmap = NULL;
	obstacleBitmap = al_load_bitmap("stone.png");
	Obstacle obstacle1(30, 5, obstacleBitmap);
	Obstacle obstacle2(23, 15, obstacleBitmap);
	Obstacle obstacle3(40, 24, obstacleBitmap);

	ALLEGRO_BITMAP *teroBitmap1 = NULL;
	teroBitmap1 = al_load_bitmap("Rept1.png");
	ALLEGRO_BITMAP *teroBitmap2 = NULL;
	teroBitmap2 = al_load_bitmap("Rept2.png");
	ALLEGRO_BITMAP *teroBitmap3 = NULL;
	teroBitmap3 = al_load_bitmap("Rept3.png");
	Terrorist tero[maxEnemy];
	teroSettings teroSet[maxEnemy];

	int time = 0;

	//register events
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);

	std::ifstream f;

	while (!done){

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


// MAIN MENU 
		if (MainMenu){
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				done = true;
				break;
			}
			if (ev.type == ALLEGRO_EVENT_TIMER){
				redraw = true;

			}
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
				switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				default:
					MainMenu = false;
					LevelMenu = true;
					GameLoop = false;
					GameOver = false;
					player.Player::Player(playerBitmap);
					break;
				}
			}else
			if (ev.type == ALLEGRO_EVENT_KEY_UP){

			}
			if (redraw == true && al_event_queue_is_empty(event_queue)){
				redraw = false;

				al_draw_textf(font24, al_map_rgb(100, 0, 30), widthSquare / 2 * square_l, heightSquare / 1.3 * square_l,
					ALLEGRO_ALIGN_CENTER, "PRESS ANY KEY TO CONTINUE");
				
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
// LEVEL MENU
		if (LevelMenu){
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				done = true;
				break;
			}
			if (ev.type == ALLEGRO_EVENT_TIMER){
				redraw = true;

			}
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if (ev.mouse.button & 1 && ev.mouse.x < widthSquare * square_l / 2){
					
				}	
			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
				switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_1:
					MainMenu = false;
					LevelMenu = false;
					GameLoop = true;
					GameOver = false;

					for (int i = 0; i < maxEnemy; i++){
						teroSet[i].timeFPS = 0;
						teroSet[i].y = 0;
						tero[i].setLive(false);
					}

					f.open("Levels/level1.txt");
					for (int i = 0; i < maxEnemy; i++){
						f >> teroSet[i].timeFPS >> teroSet[i].y;
					}
					player.Player::Player();

					f.close();
					break;
				case ALLEGRO_KEY_2:
					MainMenu = false;
					LevelMenu = false;
					GameLoop = true;
					GameOver = false;
					 
					for (int i = 0; i < maxEnemy; i++){
						teroSet[i].timeFPS = 0;
						teroSet[i].y = 0;
						tero[i].setLive(false);
					}

					f.open("Levels/level2.txt");
					for (int i = 0; i < maxEnemy; i++){
						f >> teroSet[i].timeFPS >> teroSet[i].y;
					}
					player.Player::Player();

					f.close();
					break;
				case ALLEGRO_KEY_3:
					MainMenu = false;
					LevelMenu = false;
					GameLoop = true;
					GameOver = false;

					for (int i = 0; i < maxEnemy; i++){
						teroSet[i].timeFPS = 0;
						teroSet[i].y = 0;
						tero[i].setLive(false);
					}

					f.open("Levels/level3.txt");
					for (int i = 0; i < maxEnemy; i++){
						f >> teroSet[i].timeFPS >> teroSet[i].y;
					}
					player.Player::Player();

					f.close();
					break;
				case ALLEGRO_KEY_4:
					MainMenu = false;
					LevelMenu = false;
					GameLoop = true;
					GameOver = false;

					for (int i = 0; i < maxEnemy; i++){
						teroSet[i].timeFPS = 0;
						teroSet[i].y = 0;
						tero[i].setLive(false);
					}

					f.open("Levels/level4.txt");
					for (int i = 0; i < maxEnemy; i++){
						f >> teroSet[i].timeFPS >> teroSet[i].y;
					}
					player.Player::Player();

					f.close();
					break;
				case ALLEGRO_KEY_5:
					MainMenu = false;
					LevelMenu = false;
					GameLoop = true;
					GameOver = false;

					for (int i = 0; i < maxEnemy; i++){
						teroSet[i].timeFPS = 0;
						teroSet[i].y = 0;
						tero[i].setLive(false);
					}

					f.open("Levels/level5.txt");
					for (int i = 0; i < maxEnemy; i++){
						f >> teroSet[i].timeFPS >> teroSet[i].y;
					}
					player.Player::Player();

					f.close();
					break;
				case ALLEGRO_KEY_6:
					MainMenu = false;
					LevelMenu = false;
					GameLoop = true;
					GameOver = false;

					for (int i = 0; i < maxEnemy; i++){
						teroSet[i].timeFPS = 0;
						teroSet[i].y = 0;
						tero[i].setLive(false);
					}

					f.open("Levels/level6.txt");
					for (int i = 0; i < maxEnemy; i++){
						f >> teroSet[i].timeFPS >> teroSet[i].y;
					}
					player.Player::Player();

					f.close();
					break;
				}
			}
			else
			if (ev.type == ALLEGRO_EVENT_KEY_UP){

			}
			if (redraw == true && al_event_queue_is_empty(event_queue)){
				redraw = false;

				al_draw_bitmap(imageLevel, 0, 0, 0);

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
// GAME LOOP 
		if (GameLoop){
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				done = true;
				break;
			}
			if (ev.type == ALLEGRO_EVENT_TIMER){
				redraw = true;
				
				Win = false;

				if (time > 3760){
					MainMenu = false;
					LevelMenu = false;
					GameLoop = false;
					GameOver = true;
					Win = true;
				}
				
				if (player.getLives() <= 0){
					MainMenu = false;
					LevelMenu = false;
					GameLoop = false;
					GameOver = true;
					Win = false;
				}
				time++;

				//LEVEL
				for (int i = 0; i < maxEnemy; i++){
					if (!teroSet[i].timeFPS)
						break;
					if (teroSet[i].timeFPS == time){
						tero[i].Terrorist::Terrorist(55, teroSet[i].y, teroBitmap1, teroBitmap2, teroBitmap3);
						tero[i].setLive(true);
					}
				}
				//Atat

				if (keys[UP])
					player.MoveUp();
				if (keys[DOWN])
					player.MoveDown();

				for (int i = 0; i < maxBullets; i++){
					if (bullets[i].isLive()){
						bullets[i].UpdateBullet();
						obstacle1.Collide(bullets[i]);
						obstacle2.Collide(bullets[i]);
						obstacle3.Collide(bullets[i]);
					}
				}

				for (int i = 0; i < maxEnemy; i++){
					if (!teroSet[i].timeFPS)
						break;
					if (tero[i].isLive()){
						if (tero[i].endOfTheRoad())
							player.SetLive(player.getLives() - 1);
						for (int j = 0; j < maxBullets; j++)
							if (bullets[j].isLive())
								tero[i].Die(bullets[j]);
						tero[i].UpdateEnemy();
					}
				}
			}
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if (ev.mouse.button & 1 && time){
					for (int i = 0; i < maxBullets; i++){
						if (!bullets[i].isLive()){

							bullets[i].setLive(true);
							bullets[i].setX(player.getX() + 2);
							bullets[i].setY(player.getY() + 2);
							float tg = (ev.mouse.y - (player.getY() + 2) * square_l) / (ev.mouse.x - (player.getX() + 2) * square_l);
							bullets[i].setSpeedX(sqrt(bullets[i].getSpeed() * bullets[i].getSpeed() / (tg * tg + 1)));
							if (tg < 0)
								bullets[i].setSpeedY(-sqrt(bullets[i].getSpeed() * bullets[i].getSpeed() - bullets[i].getSpeedX() * bullets[i].getSpeedX()));
							else
								bullets[i].setSpeedY(sqrt(bullets[i].getSpeed() * bullets[i].getSpeed() - bullets[i].getSpeedX() * bullets[i].getSpeedX()));
							if (ev.mouse.x < (player.getX() + 3) * square_l)
								bullets[i].setLive(false);
							break;
						}
					}
				}
			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
				switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_W:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_S:
					keys[DOWN] = true;
					break;
				}
			}
			else
			if (ev.type == ALLEGRO_EVENT_KEY_UP){
				switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_W:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_S:
					keys[DOWN] = false;
					break;
				}
			}
			if (redraw && al_event_queue_is_empty(event_queue)){
				redraw = false;

				BG.DrawBackground();
				player.DrawPlayer();
				for (int i = 0; i < maxBullets; i++){
					if (bullets[i].isLive()){
						bullets[i].DrawBullet();
					}
				}
				for (int i = 0; i < maxEnemy; i++){
					if (!teroSet[i].timeFPS)
						break;
					if (tero[i].isLive()){
						tero[i].DrawEnemy(time);
					}
				}

				obstacle1.DrawObstacle();
				obstacle2.DrawObstacle();
				obstacle3.DrawObstacle();
				al_draw_textf(font24, al_map_rgb(0, 0, 100), GAME_PIXEL_WIDTH - 144, GAME_PIXEL_HEIGHT - 44, 0, "LIVES:%d",player.getLives());

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
//GAME OVER
		if (GameOver){
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				done = true;
				break;
			}
			if (ev.type == ALLEGRO_EVENT_TIMER){
				redraw = true;
				
			}
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
				switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				default:
					MainMenu = false;
					LevelMenu = true;
					GameLoop = false;
					GameOver = false;

					time = 0;
					player.Player::Player(playerBitmap);
					break;
				}
			}
			else
			if (ev.type == ALLEGRO_EVENT_KEY_UP){

			}
			if (redraw == true && al_event_queue_is_empty(event_queue)){
				redraw = false;

				if (Win == true){
					al_draw_textf(font24, al_map_rgb(100, 100, 30), widthSquare / 2 * square_l, heightSquare / 2 * square_l,
						ALLEGRO_ALIGN_CENTER, "LEVEL COMPLETED");
				}
				else{
					al_draw_textf(font24, al_map_rgb(100, 100, 30), widthSquare / 2 * square_l, heightSquare / 2 * square_l,
						ALLEGRO_ALIGN_CENTER, "GAME OVER");
				}
				al_draw_textf(font24, al_map_rgb(100, 0, 30), widthSquare / 2 * square_l, heightSquare / 1.3 * square_l,
					ALLEGRO_ALIGN_CENTER, "PRESS ANY KEY TO CONTINUE");

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
	}
	
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font24);
	al_destroy_bitmap(imageBG);
}