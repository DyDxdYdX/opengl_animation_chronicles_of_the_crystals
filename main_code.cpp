#include <windows.h>
#include <stdlib.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>
#include <math.h>
#include <stdio.h>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720
#define FPS 30
#define PI 3.1415926535897932384626433832795

//global variable
int X = 0;
int Y = 0;
int dx = 1;
int dy = 1;
int color = 0;
int updown = 0;
int update_updown = 1;
int leftright = 0;
int update_leftright = 1;
double cloudPos1 = 100;
double cloudPos2 = 500;
double cloudPos3 = 900;
double cloudMove = 1;
int birdVar = 1;
int birdVar_update = 1;
int birdPos1 = 320;
int birdPos2 = 960;
int birdMove = 2;

int next_scene = 0;
int scene_update = 0;

//circle (coor x, coor y, radius, number of corner)
void circle(int x, int y, int r, int n) {
	double inc = (2 * PI) / (double)n;
	glBegin(GL_POLYGON);
	for (double theta = 0.0; theta <= 2 * PI; theta += inc) {
		glVertex2d(x + r * cos(theta), y + r * sin(theta));
	}
	glEnd();
}

//body for all type of character
void character_body(int x, int y) {
	glLineWidth(10);
	glBegin(GL_LINES);

	//body
	glVertex2f(x, y);
	glVertex2f(x, y - 100);

	//right feet
	glVertex2f(x, y - 100);
	glVertex2f(x + 20, y - 150);

	//left feet
	glVertex2f(x, y - 100);
	glVertex2f(x - 20, y - 150);

	//left hand
	glVertex2f(x - 20, y - 80);
	glVertex2f(x , y - 40);

	//right hand
	glVertex2f(x + 20, y - 80);
	glVertex2f(x, y - 40);
	glEnd();
}

//rectangle (coor x, coor y, width, height)
void rectangle(int x, int y, double w, double h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}

//triangle (coor x, coor y, width, height)
void triangle(int x, int y, double w, double h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w/2, y + h);
	glEnd();
}

//crystal shape hexagon
//hexagon (coor x, coor y, width, height)
void hexagon(int x, int y, double w, double h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x - w / 2, y + h / 5);
	glVertex2f(x - w / 2, y + h * 4 / 5);
	glVertex2f(x, y + h);
	glVertex2f(x + w / 2, y + h * 4 / 5);
	glVertex2f(x + w / 2, y + h / 5);
	glEnd();
}

//crystal shape half-hexagon
//hexagon (coor x, coor y, width, height)
void Halfhexagon(int x, int y, double w, double h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x - w / 2, y + h / 5);
	glVertex2f(x - w / 2, y + h * 4 / 5);
	glVertex2f(x, y + h);
	glEnd();
}

//weapon axe
void axe(int x, int y) {
	glBegin(GL_POLYGON);
	glColor3ub(189, 189, 189);
	glVertex2d(x - 15, y + 45);
	glVertex2d(x - 35, y + 33);
	glVertex2d(x - 28, y + 23);
	glVertex2d(x - 15, y + 23);
	glEnd();
	glBegin(GL_LINES);
	glColor3ub(84, 62, 27);
	glVertex2d(x, y);
	glVertex2d(x - 20, y + 45);
	glEnd();
}

//weapon magic rod
void rod(int x, int y) {
	glBegin(GL_LINES);
	glColor3ub(84, 62, 27);
	glVertex2d(x-8, y+29);
	glVertex2d(x-8, y-70);
	glEnd();
	glColor3ub(227, 99, 7);
	circle(x-8, y+30, 7, 1000);
}

//sun (coor x, coor y, size)
void sun(int x, int y, int r, int n) {
	glColor3ub(237, 153, 9);
	circle(x, y, r, n);
	glColor3ub(227, 99, 7);
	circle(x, y, r-10, n);
}

//tree (coor x, coor y, size)
void tree(int x, int y, double w, double h) {
	glColor3ub(87, 63, 47);
	rectangle(x + w / 2 - w / 5 / 2, y, w / 5, h / 5);

	glColor3ub(34, 107, 39);
	triangle(x , y + h / 5, w , h / 5);

	glColor3ub(44, 145, 51);
	triangle(x, y + h / 5 + 20, w, h / 5);
	
	glColor3ub(55, 204, 65);
	triangle(x, y + h / 5 + 40, w, h / 5);

}

//king_chair (coor x, coor y, width, height)
void king_chair(int x, int y, int w, int h) {
	glColor3ub(153, 85, 50);
	rectangle(x + w - w / 3, y, w / 3, 2 * h);
	glColor3ub(153, 85, 50);
	rectangle(x, y, w, h);
	glColor3ub(122, 68, 40);
	rectangle(x + w - w / 3 + 10, y + 10, w / 3 - 20, 2 * h - 20);
	glColor3ub(122, 68, 40);
	rectangle(x + 10, y + 10, w - 20, h - 20);
}


//magic attack effect
void magic_attack(int x, int y) {
	glColor3ub(80, 9, 128);
	circle(x, y, 20, 1000);
	glColor3ub(0, 0, 0);
	circle(x, y, 15, 1000);
}

//crystal color var1
void crystal(int x, int y, double w, double h) {
	glColor3ub(78, 194, 252);
	hexagon(x, y, w, h);
	glColor3ub(47, 105, 186);
	Halfhexagon(x, y, w, h);
	glColor3ub(47, 105, 186);
	hexagon(x, y, w / 2, h);
	glColor3ub(78, 194, 252);
	Halfhexagon(x, y, w / 2, h);
}

//crystal color var2
void crystal2(int x, int y, double w, double h) {
	glColor3ub(47, 105, 186);
	hexagon(x, y, w, h);
	glColor3ub(78, 194, 252);
	Halfhexagon(x, y, w, h);
	glColor3ub(78, 194, 252);
	hexagon(x, y, w / 2, h);
	glColor3ub(47, 105, 186);
	Halfhexagon(x, y, w / 2, h);
}

//crystal spinning effect
void crystal_spin(int x, int y, double w, double h) {
	glColor3ub(200, 0, 0);

	if (color <= 50) {
		crystal(x, y, w, h);
	}
	else {
		crystal2(x, y, w, h);
	}
}

//mountain
void mountain() {
	glColor3ub(102, 102, 102);
	triangle(200, 240, 600, 400);
	glColor3ub(171, 171, 171);
	triangle(100, 240, 400, 250);
	glColor3ub(171, 171, 171);
	triangle(700, 240, 350, 200);
}

//cloud
void cloud(int x, int y) {
	glColor3ub(240, 240, 240);
	circle(x, y, 30, 1000);
	circle(x + 35, y + 20, 30, 1000);
	circle(x + 35, y - 20, 30, 1000);
	circle(x + 70, y + 20, 30, 1000);
	circle(x + 70, y - 20, 30, 1000);
	circle(x + 105, y, 30, 1000);
}

//bird
void bird(int x, int y, int var) {
	glColor3ub(0, 0, 0);
	glLineWidth(4.0);
	glBegin(GL_LINES);

	//body
	glVertex2f(x - 25, y);
	glVertex2f(x + 25, y);
	glVertex2f(x, y);
	glVertex2f(x - 30, y + 30);
	glVertex2f(x, y);
	glVertex2f(x + 30, y + 30);

	//wing variation
	if (var <= 5) {
		glVertex2f(x - 30, y + 30);
		glVertex2f(x - 60, y);
		glVertex2f(x + 30, y + 30);
		glVertex2f(x + 60, y);
	}
	else if (var <= 15) {
		glVertex2f(x - 30, y + 30);
		glVertex2f(x - 60, y + 30);
		glVertex2f(x + 30, y + 30);
		glVertex2f(x + 60, y + 30);
	}
	else {
		glVertex2f(x - 30, y + 30);
		glVertex2f(x - 60, y + 60);
		glVertex2f(x + 30, y + 30);
		glVertex2f(x + 60, y + 60);
	}
	glEnd();
}

//main character
void ayano(int x, int y) {
	glColor3ub(0, 0, 0);
	circle(x, y, 25, 100);
	character_body(x, y);
}

//king
void bartz(int x, int y) {
	glColor3ub(7, 42, 219);
	circle(x, y, 25, 100);
	character_body(x, y);

}

//queen
void leena(int x, int y) {
	glColor3ub(245, 139, 17);
	circle(x, y, 25, 100);
	character_body(x, y);

}

//princess
void leila(int x, int y) {
	glColor3ub(252, 77, 255);
	circle(x, y, 25, 100);
	character_body(x, y);

}

//goblin with axe
void goblin_axe(int x, int y) {
	glColor3ub(0, 102, 2);
	circle(x, y, 25, 100);
	character_body(x, y);
	axe(x - 15, y - 80);
}

//goblin with magic rod
void goblin_rod(int x, int y) {
	glColor3ub(0, 102, 2);
	circle(x, y, 25, 100);
	character_body(x, y);
	rod(x - 15, y - 80);
}

//balluk
void balluk(int x, int y) {
	glColor3ub(115, 73, 62);
	circle(x, y, 25, 100);
	character_body(x, y);
	axe(x - 15, y - 80);
}

//warlock
void warlock(int x, int y) {
	glColor3ub(88, 122, 49);
	circle(x, y, 25, 100);
	character_body(x, y);
	rod(x - 15, y - 80);
}

//demon king
void cthulhu(int x, int y) {
	glColor3ub(255, 25, 0);
	circle(x, y, 25, 100);
	character_body(x, y);
	rod(x - 15, y - 80);
}

//outside
void grassland(int world) {
	glColor3ub(42, 181, 51);
	rectangle(0, 0, SCREENWIDTH, SCREENHEIGHT / 3);

	if (world == 2) mountain();
	tree(10, SCREENHEIGHT / 3 - 30, 90, 300);
	tree(138, SCREENHEIGHT / 3 - 30, 90, 300);
	tree(266, SCREENHEIGHT / 3 - 30, 90, 300);
	tree(SCREENWIDTH - 110 - 256, SCREENHEIGHT / 3 - 30, 90, 300);
	tree(SCREENWIDTH - 110 - 128, SCREENHEIGHT / 3 - 30, 90, 300);
	tree(SCREENWIDTH - 110, SCREENHEIGHT / 3 - 30, 90, 300);
	sun(SCREENWIDTH - SCREENWIDTH / 10, SCREENHEIGHT - SCREENHEIGHT / 7, 100, 1000);
	cloud(cloudPos1, 600);
	cloud(cloudPos2, 500);
	cloud(cloudPos3, 550);
	bird(birdPos1, 600, birdVar);
	bird(birdPos2, 500, birdVar);
}

//brick effect
//brick (coor x, coor y, width, height)
void brick(int x, int y, double w, double h) {
	int j = 0;
	int start_i = 0;
	for (int k = y; k < h; k += 50) {
		if (j % 2 == 0) {
			start_i = 0;
		}
		else {
			start_i = -50;
		}
		for (int i = x + start_i; i < w; i += 100) {
			glColor3ub(199, 196, 195);
			rectangle(i, k, 100, 50);
			glColor3ub(86, 86, 86);
			rectangle(i, k, 90, 40);
		}
		j++;
	}
}

//inside king castle
void castle1() {
	brick(0, 0, SCREENWIDTH, SCREENHEIGHT);

	glColor3ub(199, 196, 195);
	rectangle(SCREENWIDTH/2 - 200/2, SCREENHEIGHT / 2 - 20, 210, 150);
	glColor3ub(154, 243, 252);
	rectangle(SCREENWIDTH / 2 - 180 / 2, SCREENHEIGHT / 2 - 10, 190, 140);
	glColor3ub(100, 100, 100);
	rectangle(0, 0, SCREENWIDTH, SCREENHEIGHT / 3);
	bartz(SCREENWIDTH - SCREENWIDTH / 7 + 30, SCREENHEIGHT / 5 + 190);
	king_chair(SCREENWIDTH - SCREENWIDTH / 7, SCREENHEIGHT / 5, 100, 100);
	leena(SCREENWIDTH - SCREENWIDTH / 6.1, SCREENHEIGHT / 2);
	leila(SCREENWIDTH - SCREENWIDTH / 5.7, SCREENHEIGHT / 3);
}

//inside demon castle
void castle2() {
	brick(0, 0, SCREENWIDTH, SCREENHEIGHT);

	glColor3ub(199, 196, 195);
	rectangle(SCREENWIDTH / 2 - 200 / 2, SCREENHEIGHT / 2 - 20, 210, 150);
	glColor3ub(154, 243, 252);
	rectangle(SCREENWIDTH / 2 - 180 / 2, SCREENHEIGHT / 2 - 10, 190, 140);
	glColor3ub(100, 100, 100);
	rectangle(0, 0, SCREENWIDTH, SCREENHEIGHT / 3);
	cthulhu(SCREENWIDTH - SCREENWIDTH / 7 + 30, SCREENHEIGHT / 5 + 190);
	king_chair(SCREENWIDTH - SCREENWIDTH / 7, SCREENHEIGHT / 5, 100, 100);
}

//mart (coor x, coor y, width, height)
void mart(int x, int y, double w, double h) {
	
	//main shape
	glColor3ub(2, 84, 35);
	rectangle(x, y, w, h);

	//roof
	glColor3ub(232, 210, 16);
	rectangle(x, y + h, w, h / 3);

	//door
	glColor3ub(163, 189, 204);
	rectangle(x + w / 2 - w / 8, y, w / 4, h / 3);
	glColor3ub(42, 164, 235);
	rectangle(x + w / 2 - w / 8 + 5, y , w / 4 - 10, h / 3 - 5);

	//windows 1
	glColor3ub(163, 189, 204);
	rectangle(x + w / 8, y + h / 1.85, w / 5, h / 5);
	glColor3ub(42, 164, 235);
	rectangle(x + w / 8 + 5, y + h / 1.85 + 5, w / 5 - 10, h / 5 - 10);

	//windows 2
	glColor3ub(163, 189, 204);
	rectangle(x + w - w / 8 - w / 5, y + h / 1.85, w / 5, h / 5);
	glColor3ub(42, 164, 235);
	rectangle(x + w - w / 8 - w / 5 + 5, y + h / 1.85 + 5, w / 5 - 10, h / 5 - 10);
}

//kingCastle (coor x, coor y, width, height)
void kingCastle(int x, int y, double w, double h) {
	//main shape
	glColor3ub(107, 113, 117);
	rectangle(x, y, w / 2, h / 2);
	rectangle(x + w / 2, y, w, h);
	rectangle(x + w / 2 + w, y, w / 2, h / 2);
	rectangle(x + w / 2 - w / 7 / 2, y + h, w + w / 7, h / 5);
	glColor3ub(163, 189, 204);
	rectangle(x + w / 2 + w / 7 / 2, y, w - w / 7, h);

	//roof
	glColor3ub(133, 69, 40);
	triangle(x, y + h / 2, w / 2, h / 2);
	triangle(x + w / 2 + w, y + h / 2, w / 2, h / 2);
	triangle(x + w / 2, y + h + h / 5, w, h / 1.5);

	//door
	glColor3ub(54, 54, 54);
	rectangle(x + w - w / 2 / 2, y, w / 2, h / 2.5);

	//window 
	glColor3ub(99, 114, 122);
	rectangle(x + w - w / 3 / 2, y + h / 1.5, w / 3, h / 5);
	glColor3ub(42, 164, 235);
	rectangle(x + w - (w / 3 - 10) / 2, y + h / 1.5 + 5, w / 3 - 10, h / 5 - 10);
	glColor3ub(42, 164, 235);
	rectangle(x + w / 2 / 2 - w / 3 / 2, y + h / 2 / 1.5 - h / 5 / 2 , w / 3, h / 5);
	rectangle(x + w + 3 * w / 4 - w / 3 / 2, y + h / 2 / 1.5 - h / 5 / 2, w / 3, h / 5);
}

//demon king castle
//demonCastle (coor x, coor y, width, height)
void demonCastle(int x, int y, double w, double h) {
	//main shape
	glColor3ub(79, 9, 2);
	rectangle(x, y, w / 3, h);
	rectangle(x + w, y, w / 3, h);
	glColor3ub(140, 16, 3);
	triangle(x + w / 3 / 2, y , w, h);

	//door
	glColor3ub(38, 38, 38);
	rectangle(x + w / 3 / 2 + w / 2 - w / 4 / 2, y, w / 4, h / 3);

	//window
	glColor3ub(42, 164, 235);
	rectangle(x + w / 3 / 2 - w / 5 / 2, y + h / 1.5, w / 5, h / 5);
	rectangle(x + w + w / 3 / 2 - w / 5 / 2, y + h / 1.5, w / 5, h / 5);
}

//function to print dialog
void dialog(char* text) {
	char* p = text;
	glColor4ub(255, 255, 255, 155);
	rectangle(0, 10, SCREENWIDTH, 100);
	glPushMatrix();
	glTranslatef(50, 50, 0);
	glScaled(0.2, 0.2, 0);
	glColor3ub(0, 0, 0);
	glLineWidth(1.4);
	for (p = text; *p; p++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	glPopMatrix();
}

//for opening screen and ending screen
void op_ed(char* text) {
	char* p = text;
	glPushMatrix();
	glTranslatef(50, 360, 0);
	glScaled(0.5, 0.5, 0);
	glColor3ub(0, 0, 0);
	glLineWidth(2.0);
	for (p = text; *p; p++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	glPopMatrix();
}

void white_screen(){
	glColor3ub(230, 230, 230);
	rectangle(0, 0, SCREENWIDTH, SCREENHEIGHT);
}

//reset some the globlal variable that will be use for update scene
void reset_scene(int x) {
	if (scene_update == x) {
		next_scene++;
		scene_update = 0;
		updown = 0;
		leftright = 0;
		if (update_updown < 0) update_updown *= -1;
	}
}

//scene 1
void scene1(int x) {
	grassland(1);
	mart(700, 100, 230, 200);

	//ayano start moving toward the mart
	if (x < 100) ayano(300+leftright*2, 200+updown);
	else {

		//ayano stop and a portal summon at him
		ayano(500, 200);
		glColor3ub(104, 136, 156);
		if (x % 3 == 0 && x >= 135) rectangle(460, 47, 80, 180);
		if (x >= 175) rectangle(460, 47, 80, 180);

		//white screen indicate ayano has been teleported
		if (x >= 190 && x < 205) white_screen();
		else if(x >= 205) {
			grassland(1);
			mart(700, 100, 230, 200);
		}
	}

	//text 
	if (x > 140 && x<190) dialog((char*)"Ayano: What is happening!?!");
}

void scene2(int x) {
	castle1();

	//ayano arrived at another world
	ayano(300, 334);
	glColor3ub(104, 136, 156);
	if (x <= 20) rectangle(260, 182, 80, 180);
	else if (x <= 50 ) if (x % 3 == 0) rectangle(260, 182, 80, 180);

	//crystal blinking before become into smaller piece
	if (x <= 75) crystal_spin(640, 130, 90, 200);
	else if (x <= 95 && x % 3 == 0) crystal_spin(640, 130, 90, 200);
	if (x > 95 && x < 130) crystal_spin(640, 200, 30, 60);

	//crystal move to ayano
	else if (x >= 130 && x <= 150) crystal_spin(640 - leftright*15, 200 + updown*3, 30, 60);

	//text
	if (x > 50 && x < 110) dialog((char*)"King: The crystal answer our prayer!!");
	if (x > 160 && x < 220) dialog((char*)"King: Warrior from another world, please save our world.");
	if (x > 220 && x < 280) dialog((char*)"Queen: The crystal sacrifice its power to summon you.");
	if (x > 280 && x < 340) dialog((char*)"Queen: Defeat the Demon Lord Cthulhu and its army, the crystal will aid you.");
	if (x > 340 && x < 400) dialog((char*)"Princess: Please be careful, the Demon Lord is very strong.");
	if (x > 400 && x < 460) dialog((char*)"Princess: Be careful for Demon General Balluk and Demon Wizard Warlock as well.");
	if (x > 460 && x < 520) dialog((char*)"Ayano: Don't worry, they are nothing in front of me!");
}

void scene3(int x) {
	grassland(2);

	//ayano started his journey
	if (x <= 30) {
		kingCastle(-140, 70, 400, 450);
		ayano(250, 220);
	}
	else if (x > 30 && x <= 170) {
		kingCastle(-140 - 5*leftright, 70, 400, 450);
		ayano(250, 220 + updown * 2);
	}

	//ayano meet demon general balluk and his army
	if (x > 100 && x <= 170) {
		balluk(1800-5*leftright, 220);
		goblin_axe(1700 - 5 * leftright, 220);
	}

	else if (x > 170 && x <= 340) {
		balluk(1090, 220);
		goblin_axe(990, 220);
		ayano(250, 220);

		//ayano start attack
		if (x > 300 && x <= 317) {
			magic_attack(300 + 40 * leftright, 150);
		}
		if (x > 320 && x <= 339) {
			magic_attack(300 + 40 * leftright, 150);
		}
	}

	//demon general balluk and his army died
	if (x > 340 && x <=400) {
		ayano(250, 220);
		if (x % 3 == 0 && x < 380) {
			balluk(1090, 220);
			goblin_axe(990, 220);
		}
	}

	//demon general warlock and his army come to meet ayano
	if (x >= 400 && x <= 770) {
		ayano(250, 220);

		//demon general warlock and his army moving toward ayano
		if (x < 470) {
			warlock(1420 - 4 * leftright, 220 + updown);
			goblin_rod(1320 - 4 * leftright, 220 + updown);
		}
		if (x >= 470 && x < 650) {
			goblin_rod(1040, 220);
			warlock(1140, 220);
		}

		//demon general warlock and his army attack ayano
		if (x > 610 && x < 638) {
			magic_attack(995 - 40 * leftright, 150);
			magic_attack(1095 - 40 * leftright, 150);
		}

		//the attack got deflected
		if (x > 613 && x < 640) {
			glColor3ub(200,200,200);
			rectangle(400, 70, 30, 175);
		}

		//demon general warlock and his army died
		if (x > 650 && x < 705) {
			if (x % 3 == 0) {
				goblin_rod(1040, 220);
				warlock(1140, 220);
			}
		}
	}

	//the position of crytal which ayano use
	if (x >= 205 && x < 740) crystal_spin(280, 120, 30, 60);

	//on the way to demon castle
	if (x >= 770 && x < 860) {
		demonCastle(1280 - 4 * leftright, 70, 500, 550);
		ayano(250, 220 + updown * 2);
	}
	if (x >= 860 && x <= 970) {
		demonCastle(572, 70, 500, 550);
		if (x < 940) ayano(250 + 4 * leftright, 220 + updown * 2);
	}

	//text
	if (x > 175 && x < 235) dialog((char*)"Balluk: Hero, defeat me if you want to pass me!");
	if (x > 235 && x < 295) dialog((char*)"Ayano: You are no match for me.");
	if (x > 480 && x < 540) dialog((char*)"Warlock: You may have defeated Balluk, but not me.");
	if (x > 540 && x < 600) dialog((char*)"Ayano: Crystal protect me!");
	if (x > 645 && x < 705) dialog((char*)"Warlock: Impossible!");
	if (x > 705 && x < 765) dialog((char*)"Ayano: Easy as A B C!");
}

void scene4(int x) {
	castle2();

	//ayano arrived inside the demon castle
	if (x <= 80) ayano(-20 + 4 * leftright, 334 + 2 * updown);
	if (x > 80 && x < 745) {
		ayano(300, 334);
	}

	//demon lord start attacking 2 times
	if (x > 440 && x < 453) {
		magic_attack(1044 - 50 * leftright, 220);
		magic_attack(1044 - 50 * leftright, 264);
		magic_attack(1044 - 50 * leftright, 310);
	}
	if (x > 453 && x < 466) {
		magic_attack(1044 - 50 * leftright, 220);
		magic_attack(1044 - 50 * leftright, 264);
		magic_attack(1044 - 50 * leftright, 310);
	}

	//crystal losses its power
	if (x > 80 && x < 1000) {
		if (x < 475) crystal_spin(330, 234 , 30, 60);
		else if (x % 3 == 0 && x <= 530) crystal_spin(330, 234, 30, 60);
		if (x > 442 && x <= 530) {
			glColor3ub(200, 200, 200);
			rectangle(380, 184, 30, 175);
		}
	}

	//ayano get banish
	if (x > 680 && x < 730 && x % 3 == 0) {
		glColor3ub(150, 150, 150);
		rectangle(250, 184, 100, 175);
	}
	else if (x > 730 && x < 750) {
		glColor3ub(150, 150, 150);
		rectangle(250, 184, 100, 175);
	}

	//text
	if (x > 90 && x < 150) dialog((char*)"Demon Lord: Hero, I welcome you to my castle.");
	if (x > 150 && x < 210) dialog((char*)"Demon Lord: I am Demon Lord Cthulhu.");
	if (x > 210 && x < 235) dialog((char*)"Demon Lord: I applaud you for standing in this room-");
	if (x > 235 && x < 295) dialog((char*)"Ayano: You talk too much for a Demon Lord.");
	if (x > 315 && x < 375) dialog((char*)"Demon Lord: Arrogant human, YOU DARE TO STAND UP AGAINST ME!");
	if (x > 375 && x < 435) dialog((char*)"Demon Lord: TASTE MY POWER!");
	if (x > 475 && x < 535) dialog((char*)"Ayano: Only this?- WHAT? THE CRYSTAL!!");
	if (x > 540 && x < 600) dialog((char*)"Demon Lord: Pathetic! The Crystal broke because you use too much of its power.");
	if (x > 600 && x < 660) dialog((char*)"Demon Lord: NOW BANISH FROM THIS WORLD!! MUAHAHAHAHA!!");
	if (x > 660 && x < 720) dialog((char*)"Ayano: WHAT??!! NOOOOO!!!!");
}

void opening() {
	white_screen();
	op_ed((char*)"Chronicle of The Crystal");
	dialog((char*)"By: Broski Co.");
	crystal_spin(1000, 160, 200, 400);
}

void ending() {
	white_screen();
	op_ed((char*)"To Be Continue...?");
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

	//to determine and show the current scene
	if (next_scene == 0) opening();
	else if (next_scene == 1) scene1(scene_update);
	else if (next_scene == 2) scene2(scene_update);
	else if (next_scene == 3) scene3(scene_update);
	else if (next_scene == 4) scene4(scene_update);
	else if (next_scene == 5) ending();

	glFlush();
	glutSwapBuffers();
}

void idle() {
	DWORD start = GetTickCount64();
	while (GetTickCount64() - start < 1000 / FPS);

	// useful code to make the chatacter look "walking"
	// if (updown > 3 || updown <= 0) update_updown *= -1;

	//update the frame
	scene_update += 1;

	//could position update
	cloudPos1 += cloudMove;
	cloudPos2 += cloudMove;
	cloudPos3 += cloudMove;
	if (cloudPos1 > SCREENWIDTH) cloudPos1 = -105;
	if (cloudPos2 > SCREENWIDTH) cloudPos2 = -105;
	if (cloudPos3 > SCREENWIDTH) cloudPos3 = -105;

	//bird varriant and position update
	birdPos1 += birdMove;
	birdPos2 += birdMove;
	birdVar += birdVar_update;
	if (birdPos1 > SCREENWIDTH) birdPos1 = -60;
	if (birdPos2 > SCREENWIDTH) birdPos2 = -60;
	if (birdVar >= 20 || birdVar < 0) birdVar_update *= -1;

	//use for the crystal "spinning" animation
	color += 3;
	if (color > 100) color = 0;
	X += dx;
	Y += dy;

	//opening
	if (next_scene == 0) {
		reset_scene(100);
	}

	//counter for scene 1
	if (next_scene == 1) {
		leftright += update_leftright;
		updown += update_updown;
		if (updown > 3 || updown <= 0) update_updown *= -1;
		reset_scene(230);
	}
	
	//counter for scene 2
	if (next_scene == 2) {
		if (scene_update >= 130) {
			leftright += update_leftright;
			updown += update_updown;
		}
		reset_scene(530);
	}

	//counter for scene 3
	if (next_scene == 3) {

		//initialize the updown and leftright value, usefull for magic_attack animation
		if (scene_update == 171 || scene_update == 320 || scene_update == 400 || scene_update == 610 || scene_update == 770 || scene_update == 860) {
			updown = 0;
			leftright = 0;
			if (update_updown < 0) update_updown *= -1;
		}

		//counter for ayano start his journey
		if (scene_update >= 30 && scene_update <170) {
			leftright += update_leftright;
			updown += update_updown;
			if (updown > 3 || updown <= 0) update_updown *= -1;
		}

		//counter for ayano start attacking
		if (scene_update > 300 && scene_update <400) {
			leftright += update_leftright;
			if (updown > 3 || updown <= 0) update_updown *= -1;
		}

		//counter for demon general warlock and his army come to meet ayano
		if (scene_update > 400 && scene_update < 470) {
			leftright += update_leftright;
			updown += update_updown;
			if (updown > 3 || updown <= 0) update_updown *= -1;
		}

		//counter for demon general warlock and his army attack ayano
		if (scene_update > 610) {
			leftright += update_leftright;
		}

		//counter for ayano moving after defeating demon general warlock and his army
		if (scene_update > 770) {
			leftright += update_leftright;
			updown += update_updown;
			if (updown > 3 || updown <= 0) update_updown *= -1;
		}

		//update the value for increment value for leftright when demon general warlock and his army magic was deflected
		//update the same value when from before as value before for movement of demon castle and ayano
		if (scene_update == 624 || scene_update == 770) {
			update_leftright *= -1;
		}
		reset_scene(970);
	}

	//counter for scene 4
	if (next_scene == 4) {
		//reinitialize the leftright value
		if (scene_update == 440 || scene_update == 453 || scene_update == 680) leftright = 0;

		leftright += update_leftright;
		updown += update_updown;
		if (updown > 3 || updown <= 0) update_updown *= -1;
		reset_scene(760);
	}

	glutPostRedisplay();
}

void initGL() {
	glClearColor(154.0 / 255.0, 243.0 / 255.0, 252.0 / 255.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREENWIDTH, 0, SCREENHEIGHT);
}

int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInit(&argc, argv);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutCreateWindow("Chronicle of The Crystal");
	glutDisplayFunc(display);
	glutIdleFunc(idle);


	initGL();

	glutMainLoop();
}
