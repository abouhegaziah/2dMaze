//  Includes
#include<iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <random>
#include <time.h>
#include <glut.h>
#include<Windows.h>
#include<MMSystem.h>

using namespace std;
int Wwidth = 650;
int Whieght = 650;
bool flage = false;

int counter = -20;

bool done = false;

int border = 25;
int lanes = 5;
int loc = (Whieght-(border*2)) / lanes;

float* paths = new float[lanes - 1];

int coins = rand() % 6 +4;
int takenCoin;
bool coinsdrawn = false;
float* coinsX = new float[coins];
float* coinsY = new float[coins];

int objY= 50;
int objX = 300;

float* powerUpsX = new float[2];
float* powerUpsY = new float[2];


int score = 0;

float rotAngle = 0.0;

void drawRect(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}
void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

void Timer(int value) {
	PlaySound(TEXT("bleep.wav"), NULL, SND_ASYNC | SND_FILENAME);
	//cout << "score: " << score << endl;
	for (int i = 1; i < lanes ;i++) {
		//cout << "objY - 15: " << objY - 15 << "   loc * i   " << loc * i << endl;
		if (!(((loc * i) <= (objY + 14)) && (((loc * i)) >= (objY - 25)))) {
			paths[i - 1] = rand() % 525 + 25;
		}
	}

	for (int i = 0; i < 2;i++) {
		if (powerUpsX[i] < 1000) {
			int x = rand() % 525 + 25;
			int y = rand() % 525 + 25;
			if (x < 1000)
				if (((y + 10) % loc >= 0 && (y + 10) % loc <= 15) || (((y) % loc >= 0 && (y) % loc <= 15))) {
					i--;
				}
				else {
					powerUpsX[i] = x;
					powerUpsY[i] = y;
				}
		}
	
	}
	counter += 20;
	glutPostRedisplay();
	glutTimerFunc(20 * 1000, Timer, 0);

}


void Key(unsigned char key, int x, int y) {
	bool between = false;
	int current = 0;
	bool move = true;
	switch (key) {
	case 'w':
		if (objY + 15 == Whieght - 25) {
			PlaySound(TEXT("solid.wav"), NULL, SND_ASYNC | SND_FILENAME);
			break;
		}
		for (int i = 1;i < lanes ;i++) {
		/*	cout << "loc: " << loc * i << endl;
			cout << "objY : " << objY << endl;*/
			if ((loc * i)  <= objY + 15 && ((loc * i) )  >= objY - 15) {
				current = i;
				move = false;
			}
			
		}
		if (move == true) {
			objY++;
			break;		
		}
		else {
			if (objX -15>= paths[current - 1]  && objX +15 <= (paths[current - 1] ) + 50) {
				objY++;
				break;}
			else {
				PlaySound(TEXT("solid.wav"), NULL, SND_ASYNC | SND_FILENAME);
				break;
			}
				
		}
	case 's':
		//flage = true;
		if (objY - 17 == border) {
			PlaySound(TEXT("solid.wav"), NULL, SND_ASYNC | SND_FILENAME);
			break;
		}
			
		for (int i = 1;i < lanes;i++) {
			if ((loc * i)+15 == objY-17) {
				current = i;
				move = false;
			}

		}
		if (move == true) {
			objY--;
			break;
		}
		else {
			if (objX - 15 >= paths[current - 1] && objX + 15 <= (paths[current - 1]) + 50) {
				objY--;
				break;
			}
			else {
				PlaySound(TEXT("solid.wav"), NULL, SND_ASYNC | SND_FILENAME);
				break;
			}
				
		};
		
	case 'd':
		if (objX + 15 == Wwidth - 25) {
			PlaySound(TEXT("solid.wav"), NULL, SND_ASYNC | SND_FILENAME);
			break;
		}
		for (int i = 1;i < lanes;i++) {
			
			if ((loc * i) <= objY && (loc * i) + 15 >= objY || (loc * i) < objY -17 && (loc * i) + 15 > objY-17 || (loc * i) < objY + 15 && (loc * i) + 15 > objY +15) {
				between = true;
				current = i;
			}
		}
		if (between == false) {
			objX++;
			break;
		}
		else {
			if (objX - 15 >= paths[current - 1] && objX + 15 >= (paths[current - 1] + 50)) {
				PlaySound(TEXT("solid.wav"), NULL, SND_ASYNC | SND_FILENAME);
				break;
			}

			else {
				objX++;
				break;
			}
		};
	case 'a':
		if (objX - 15 == border) {
			PlaySound(TEXT("solid.wav"), NULL, SND_ASYNC | SND_FILENAME);
			break;
		}
		
		for (int i = 1;i < lanes +1;i++) {
		/*	cout << "loc: " << loc * i << endl;
			cout << "objY : " << objY << endl;*/
			if ((loc * i) <= objY && (loc * i) + 15 >= objY || (loc * i) < objY - 17 && (loc * i) + 15 > objY - 17 || (loc * i) < objY + 15 && (loc * i) + 15 > objY + 15) {
			/*	cout << "loc: " << loc * i << endl;
				cout << "objY : " << objY << endl;*/
				between = true;
				current = i;
			}
		}
		if (between == false) {
			objX--;
			break;
		}
		else {
			/*cout << "loc: " << paths[current-1] << endl;
			cout << "objX : " << objX << endl;*/
			if (objX - 15 <= paths[current - 1] && objX + 15 <= (paths[current - 1] + 50)) {
				PlaySound(TEXT("solid.wav"), NULL, SND_ASYNC | SND_FILENAME);
				break;
			}
			else {
				objX--;
				break;
			}
		};
		
	
	}

	glutPostRedisplay();
}

void cointaken() {
	for (int i = 0;i < coins;i++) {
		if (objY+10 >= coinsY[i] && objY - 10 <= coinsY[i] && objX + 10 >= coinsX[i] && objX - 10 <= coinsX[i]) {
			PlaySound(TEXT("cons.wav"), NULL, SND_ASYNC | SND_FILENAME);

			coinsY[i] = 1000000000000;
			coinsX[i] = 100000000000000;
			if(flage)
			score += 5;
			score += 5;
			break;
		}
	}
}
void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void goalTaken()
{
	if (objY + 10 >= 590 && objY - 10 <= 590 && objX + 10 >= 322 && objX - 10 <= 322) {
		done = true;
	}
	if (done) {
		PlaySound(TEXT("Ta Da.wav"), NULL, SND_ASYNC | SND_FILENAME);
		glColor3f(0, 0, 0);
		drawRect(0, 0, 650, 650);
		glColor3f(1, 1, 1);
		char* p0s[15];
		sprintf((char*)p0s, "Game Over  Score: %d", score);
		print(250, 325, (char*)p0s);
	}
	}
void powerUpTaken() {
	if (objY +15  >= powerUpsY[0] && objY -20 <= powerUpsY[0] && objX + 15 >= powerUpsX[0] && objX - 15 <= powerUpsX[0]) {
		PlaySound(TEXT("powerup.wav"), NULL, SND_ASYNC | SND_FILENAME);
		bool found = false;
		powerUpsX[0] = 1000000000000;
		powerUpsY[0] = 1000000000000;	
		for (int i = 1; i < lanes;i++)
			if (objY < loc * i) {
				if (!found) {
					paths[i - 1] = objX - 25;
					found = true;
				}
				else break;
			}
	}
	else if (objY + 15 >= powerUpsY[1] && objY - 15 <= powerUpsY[1] && objX + 15 >= powerUpsX[1] && objX - 15 <= powerUpsX[1]) {
		PlaySound(TEXT("powerup.wav"), NULL, SND_ASYNC | SND_FILENAME);
		powerUpsX[1] = 1000000000000;
		powerUpsY[1] = 1000000000000;
		flage = true;
	}
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	cointaken();
	powerUpTaken();
	glColor3f(0, 113, 167);
	drawRect(0, 0, 650, 650);
	//--------------------------------
	glColor3f(0, 0, 0);
	char* p0s[15];
	sprintf((char*)p0s, "Score: %d", score);
	print(30, 600, (char*)p0s);
	//borders
	glColor3f(0.196078, 0.196078, 0.8);
	drawRect(0, 0, Wwidth, 15);
	drawRect(0, Whieght, Wwidth, -15);
	drawRect(Wwidth, 0, -15, Whieght);
	drawRect(0, 0, 15,Whieght );
//lane Border
	for (int i = 1;i < lanes;i++) {

		int y = loc * i;
		glColor3f(0.556863, 0.137255, 0.137255);
		drawRect(15, y, Wwidth - border-5, 15);
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(15, y+7, 0.0f);
		glVertex3f(625, y+7, 0.0f);
		glEnd();

	}
//Border window
	for (int i = 0;i < 31;i++) {
		glBegin(GL_TRIANGLES);
		glColor3f(0.196078, 0.196078, 0.8);
		glVertex3f((15+(20*i)), 15, 0);
		glColor3f(0.196078, 0.196078, 0.8);
		glVertex3f((35 + (20 * i)), 15, 0);
		glColor3f(0.556863, 0.137255, 0.137255);
		glVertex3f((25 + (20 * i)), 25, 0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glColor3f(0.196078, 0.196078, 0.8);
		glVertex3f((15 + (20 * i)), 635, 0);
		glColor3f(0.196078, 0.196078, 0.8);
		glVertex3f((35 + (20 * i)), 635, 0);
		glColor3f(0.556863, 0.137255, 0.137255);
		glVertex3f((25 + (20 * i)), 625, 0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glColor3f(0.196078, 0.196078, 0.8);
		glVertex3f(15, (35 + (20 * i)), 0);
		glColor3f(0.556863, 0.137255, 0.137255);
		glVertex3f(25, (25 + (20 * i)), 0);
		glColor3f(0.196078, 0.196078, 0.8);
		glVertex3f(15, (15 + (20 * i)), 0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glColor3f(0.196078, 0.196078, 0.8);
		glVertex3f(635, (15 + (20 * i)), 0);
		glColor3f(0.556863, 0.137255, 0.137255);
		glVertex3f(625, (25 + (20 * i)), 0);
		glColor3f(0.196078, 0.196078, 0.8);
		glVertex3f(635, (35 + (20 * i)), 0);
		glEnd();

	}

// coins 
	if (!coinsdrawn) {
		for (int i = 0;i < coins;i++) {
			int z = 0;
			int x = rand() % (650-70) + 35;
			int y = rand() % (610-35) + 35;
			//cout << "y: " << y << "  y % loc:   " << y % loc << endl;
			if ((y % loc >= 0 && y % loc <= 30) || (y % loc >= loc-20 && y % loc <= loc-1)) {
				i--;
			}
			else
			{
				coinsX[i] = x;
				coinsY[i] = y;
				glPushMatrix();
				glColor3f(0, 0, 0);
				drawCircle(coinsX[i], coinsY[i], 8);
				glPopMatrix();
			}
		}
		coinsdrawn = true;
	}
	else {
		for (int i = 0;i < coins;i++) {
			glPushMatrix();
			glTranslatef(coinsX[i], coinsY[i], 0);
			glRotatef(rotAngle, 0, 0, 1);
			glTranslatef(-coinsX[i], -coinsY[i], 0);
			glColor3f(1.00, 0.43, 0.78);
			drawCircle(coinsX[i], coinsY[i], 8);
			glBegin(GL_POINTS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(coinsX[i]-4, coinsY[i]+4, 0);
			glVertex3f(coinsX[i]-4, coinsY[i]-4, 0);
			glEnd();
			glBegin(GL_TRIANGLES);
			glColor3f(1.00, 0.43, 0.78);
			glVertex3f(coinsX[i], coinsY[i], 0);
			//glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(coinsX[i]+12, coinsY[i]+8, 0);
			//glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(coinsX[i] + 12, coinsY[i] - 8, 0);
			glEnd();
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(coinsX[i]-8, coinsY[i] , 0.0f);
			glVertex3f(coinsX[i]-6 , coinsY[i], 0.0f);
			glEnd();
			/*glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(coinsX[i], coinsY[i] - 8, 0.0f);
			glVertex3f(coinsX[i], coinsY[i] + 8, 0.0f);
			glEnd();*/
			glPopMatrix();
		}
	}
//Bridge
	for (int i = 1; i < lanes ;i++) {
		int y = loc * i;
		glColor3f(0, 113, 167);
		drawRect(paths[i-1], y, 50, 15);
	}

//Goal-------------
	glPushMatrix();
	glColor3f(0.85, 0.85, 0.10);
	drawRect(307, 575, 34, 15);
	drawRect(313 +6, 590+5, 12, 5);
	drawCircle(313+3, 590, 10);
	drawCircle(313+19, 590, 10);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(309, 585, 0.0f);
	glVertex3f(340, 585, 0.0f);
	glEnd();
	drawRect(322, 590, 3, 3);
	glPopMatrix();

//object
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	drawCircle(objX,objY, 15);
	glBegin(GL_TRIANGLES);
	//glColor3f(0.2, 0.2, 0.2f);
	glVertex3f(objX , objY, 0);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(objX +15, objY -18, 0);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(objX - 15, objY -18, 0);
	glEnd();
	glColor3f(1.0, 1.0f, 1.0f);
	drawCircle(objX+7, objY+6, 4);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0f, 0.0f);
	glVertex3f(objX + 7, objY + 6, 0.0f);
	glEnd();
	glColor3f(1.0, 1.0f, 1.0f);
	drawRect(objX-4, objY, 4, 15);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.0f, 0.0f);
	glVertex3f(objX, objY + 15, 0);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(objX, objY + 9, 0);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(objX - 4, objY +12, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.0f, 0.0f);
	glVertex3f(objX-4, objY +8, 0);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(objX, objY + 5, 0);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(objX-4 , objY + 2, 0);
	glEnd();
	glPopMatrix();
//PowerUps-----------------
	for (int i = 0; i < 2;i++) {
		glColor3f(0, 0, 0);
		drawRect(powerUpsX[i], powerUpsY[i], 12, 12);
		glColor3f(1, 1, 1);
		drawCircle(powerUpsX[i]+6, powerUpsY[i]+6, 5);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(powerUpsX[i], powerUpsY[i]+6, 0.0f);
		glVertex3f(powerUpsX[i]+12, powerUpsY[i]+6, 0.0f);
		glEnd();
		
	}
	if (counter == 120) {
		glColor3f(0, 0, 0);
		drawRect(0, 0, 650, 650);
		glColor3f(1, 1, 1);
		char* p0s[15];
		sprintf((char*)p0s, "Game Over  Score: %d", score);
		print(250, 325, (char*)p0s);
	}
	

//---------------------------
	goalTaken();
	glFlush();

}
void Anim() {
	rotAngle+=0.1;
	glutPostRedisplay();
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(Wwidth, Whieght);
	glutInitWindowPosition(200, 150);

	glutCreateWindow("OpenGL - 2D Template");
	glutDisplayFunc(Display);
	
	glutIdleFunc(Anim);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	gluOrtho2D(0.0, Wwidth, 0.0, Whieght);
	glutTimerFunc(0, Timer, 0); // sets the Timer handler function; which runs every `Threshold` milliseconds (1st argument)
	glutKeyboardFunc(Key);      // sets the Keyboard handler function; called when a key is pressed
	srand(time(NULL));

	glutMainLoop();
}
