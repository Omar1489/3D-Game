#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <stdio.h>
#include <math.h>
#include <glut.h>
using namespace std;
#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

Model_3DS model_house;
Model_3DS ship_model;
Model_3DS model_tree;
GLuint tex;
GLuint sand;

// Textures
GLTexture tex_ground;
GLTexture tex_ground2;
GLTexture tex_ground3;
GLTexture tex_sea;

double lightmove = 1; 
int lightup = 0;
int lightstate = 1;

double playerX = 0;
double playerY = 0;
double playerZ = 4.47;
double playerAngle = 0;
//double playerZ = 0;
int playerState = 0;

int firstTime = 1; 


int level1Timer = 0;
 
int Score = 0;
double GoalX = 0;
double GoalZ = 0;



double PlayerR = 0;
double PlayerG = 0;
double PlayerB = 0;

double ballR= 0;
double ballG = 0;
double ballB = 0;

double mainBallR = 0;
double mainBallG = 0;
double mainBallB = 1;

int mainBall = 0;

double X=0;
double Z=0;

int gameState = 0;

double lightC = 0.7;
double lightCD = 0;

int Balls1 = {};
double Balls1Xs[8]= {};
double Balls1Zs [8]= {};
int Balls2 = {};
double Balls2Xs[8] = {};
double Balls2Zs[8] = {};
int Balls3 = {};
double Balls3Xs[8] = {};
double Balls3Zs[8] = {};
int Balls4 = {};
double Balls4Xs[8] = {};
double Balls4Zs[8] = {};

double holesX[7] = {};
double holesZ[7] = {};

double ballsY = -0.5;
double upOrdown = 1;

double ball1X = -0.2;
double LOR1 = 1;

double ball2X = 0.2;
double LOR2 = 0;

double ball3X = 0.4;
double LOR3 = 1;

double ball4X = -0.4;
double LOR4 = 0;


double holeLOR1 = 0;
double holeLOR2 = 0;
double holeLOR3 = 0;
double holeLOR4 = 0;
double holeLOR5 = 0;
double holeLOR6 = 0;
double holeLOR7 = 0;

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

void Timer(int value) {
	
	mainBall = rand() % (3) + (0);
	if (mainBall == 0) {
		//Blue
		mainBallR = 0;
		mainBallG = 0;
		 mainBallB = 1;

	}else if (mainBall == 1) {
		//Green
		mainBallR = 0;
		mainBallG = 1;
		mainBallB = 0;
	}
	else if (mainBall == 2) {
		//Pink
		mainBallR = 0.9;
		mainBallG = 0;
		mainBallB = 0.5;

	}
	else if (mainBall == 3) {
		//Green
		mainBallR = 1;
		mainBallG = 0;
		mainBallB = 0;
	}

	if (gameState == 6) {
		gameState = 10;
		firstTime = 1;
	}

	if (gameState == 7) {
		gameState = 5;
		firstTime = 1;
	}
	/*cout << "hi";
	cout << "\n";*/
	if (gameState == 1 && level1Timer < 12) {
		
		level1Timer++;
	}
	else if (gameState == 1 && level1Timer == 12) {
		gameState = 2;
		firstTime = 1;
		level1Timer = 0;
	}

	if (gameState == 3 && level1Timer < 18) {
		/*cout << level1Timer;
		cout << "\n";*/
		level1Timer++;
		

	}
	else if (gameState == 3 && level1Timer == 18) {
		if (Score >=10) {
			gameState = 8;
			firstTime = 1;
			level1Timer = 0;
		}
		else {

			gameState = 5;
			firstTime = 1;
			level1Timer = 0;
		}
	}

	glutTimerFunc(5 * 1000, Timer, 0);


}

void Anim() { 

	if (gameState == 1) {
		lightstate = 1;
	}else if (gameState == 3) {
		lightstate = 0;
	}

	if (gameState == 1 || gameState == 3) {
		if (lightmove > -1 && lightup == 0) {
			lightmove = lightmove - 0.01;
		}
		else if (lightmove <= -1 && lightup == 0) {
			lightup = 1;
		}else if (lightmove < 3 && lightup == 1) {
			lightmove = lightmove + 0.01;
		}
		else if (lightmove >= 3 && lightup == 1) {
			lightup = 0;
		}
	}
	else {
		lightmove = 1;
	}

	if (gameState == 1 || gameState == 3) {
		if (lightC > 0.5 && lightCD == 0) {
			lightC = lightC - 0.1;
		}
		else if (lightC <= 0.5 && lightCD == 0) {
			lightCD = 1;
		}
		else if (lightC < 1 && lightCD == 1) {
			lightC = lightC + 0.1;
		}
		else if (lightC >= 1 && lightCD == 1) {
			lightCD = 0;
		}
	}
	

	if (gameState == 6) {
		playerY = playerY - 0.0001;
		
	}

	if (gameState == 7) {
		playerY = playerY - 0.01;

	}
	if (gameState == 0|| gameState == 10|| gameState == 2|| gameState == 5) {
		if (ballsY > -0.9 && upOrdown == 1) {
			ballsY = ballsY - 0.0003;
		}
		else if (ballsY <= -0.9 && upOrdown == 1) {
			upOrdown = 0;
			ballsY = ballsY + 0.0003;
		}
		else if (ballsY < -0.5 && upOrdown == 0) {
			ballsY = ballsY + 0.0003;
		}
		else if (ballsY >= -0.5 && upOrdown == 0) {
			upOrdown = 1;
			ballsY = ballsY - 0.0003;
		}

		/*double ball1X = -0.5;
		double LOR1 = 1;*/
		//1
		if (ball1X > -0.68 && LOR1 == 1) {
			ball1X = ball1X - 0.0003;
		}
		else if (ball1X <= -0.68 && LOR1 == 1) {
			LOR1 = 0;
			ball1X = ball1X + 0.0003;
		}
		else if (ball1X < 0.68 && LOR1 == 0) {
			ball1X = ball1X + 0.0003;
		}
		else if (ball1X >= 0.68 && LOR1 == 0) {
			LOR1 = 1;
			ball1X = ball1X - 0.0003;
		}
		//2
		if (ball2X > -0.68 && LOR2 == 1) {
			ball2X = ball2X - 0.0003;
		}
		else if (ball2X <= -0.68 && LOR2 == 1) {
			LOR2 = 0;
			ball2X = ball2X + 0.0003;
		}
		else if (ball2X < 0.68 && LOR2 == 0) {
			ball2X = ball2X + 0.0003;
		}
		else if (ball2X >= 0.68 && LOR2 == 0) {
			LOR2 = 1;
			ball2X = ball2X - 0.0003;
		}
		//3
		if (ball3X > -0.68 && LOR3 == 1) {
			ball3X = ball3X - 0.0003;
		}
		else if (ball3X <= -0.68 && LOR3 == 1) {
			LOR3 = 0;
			ball3X = ball3X + 0.0003;
		}
		else if (ball3X < 0.68 && LOR3 == 0) {
			ball3X = ball3X + 0.0003;
		}
		else if (ball3X >= 0.68 && LOR3 == 0) {
			LOR3 = 1;
			ball3X = ball3X - 0.0003;
		}
		//4
		if (ball4X > -0.68 && LOR4 == 1) {
			ball4X = ball4X - 0.0003;
		}
		else if (ball4X <= -0.68 && LOR4 == 1) {
			LOR4 = 0;
			ball4X = ball4X + 0.0003;
		}
		else if (ball4X < 0.68 && LOR4 == 0) {
			ball4X = ball4X + 0.0003;
		}
		else if (ball4X >= 0.68 && LOR4 == 0) {
			LOR4 = 1;
			ball4X = ball4X - 0.0003;
		}
	}

	//holes
	if (gameState == 3) {
		if (holesX[0] > -0.15 && holeLOR1 == 1) {
			holesX[0] = holesX[0] - 0.01;
		}
		else if (holesX[0] <= -0.15 && holeLOR1 == 1) {
			holeLOR1 = 0;
			holesX[0] = holesX[0] + 0.01;
		}
		else if (holesX[0] < 0.15 && holeLOR1 == 0) {
			holesX[0] = holesX[0] + 0.01;
		}
		else if (holesX[0] >= 0.15 && holeLOR1 == 0) {
			holeLOR1 = 1;
			holesX[0] = holesX[0] - 0.01;
		}
	}
	if (gameState == 3) {
		if (holesX[1] > -0.15 && holeLOR2 == 1) {
			holesX[1] = holesX[1] - 0.01;
		}
		else if (holesX[1] <= -0.15 && holeLOR2 == 1) {
			holeLOR2 = 0;
			holesX[1] = holesX[1] + 0.01;
		}
		else if (holesX[1] < 0.15 && holeLOR2 == 0) {
			holesX[1] = holesX[1] + 0.01;
		}
		else if (holesX[1] >= 0.15 && holeLOR2 == 0) {
			holeLOR2 = 1;
			holesX[1] = holesX[1] - 0.01;
		}
	}

	if (gameState == 3) {
		if (holesX[2] > -0.15 && holeLOR3 == 1) {
			holesX[2] = holesX[1] - 0.01;
		}
		else if (holesX[2] <= -0.15 && holeLOR3 == 1) {
			holeLOR3 = 0;
			holesX[2] = holesX[2] + 0.01;
		}
		else if (holesX[2] < 0.15 && holeLOR3 == 0) {
			holesX[2] = holesX[2] + 0.01;
		}
		else if (holesX[2] >= 0.15 && holeLOR3 == 0) {
			holeLOR3 = 1;
			holesX[2] = holesX[2] - 0.01;
		}
	}

	if (gameState == 3) {
		if (holesX[3] > -0.15 && holeLOR4 == 1) {
			holesX[3] = holesX[3] - 0.01;
		}
		else if (holesX[3] <= -0.15 && holeLOR4 == 1) {
			holeLOR4 = 0;
			holesX[3] = holesX[3] + 0.01;
		}
		else if (holesX[3] < 0.15 && holeLOR4 == 0) {
			holesX[3] = holesX[3] + 0.01;
		}
		else if (holesX[3] >= 0.15 && holeLOR4 == 0) {
			holeLOR4 = 1;
			holesX[3] = holesX[3] - 0.01;
		}
	}

	if (gameState == 3) {
		if (holesX[4] > -0.15 && holeLOR5 == 1) {
			holesX[4] = holesX[4] - 0.01;
		}
		else if (holesX[4] <= -0.15 && holeLOR5 == 1) {
			holeLOR5 = 0;
			holesX[4] = holesX[4] + 0.01;
		}
		else if (holesX[4] < 0.15 && holeLOR5 == 0) {
			holesX[4] = holesX[4] + 0.01;
		}
		else if (holesX[4] >= 0.15 && holeLOR5 == 0) {
			holeLOR5 = 1;
			holesX[4] = holesX[4] - 0.01;
		}
	}

	if (gameState == 3) {
		if (holesX[5] > -0.15 && holeLOR6 == 1) {
			holesX[5] = holesX[5] - 0.01;
		}
		else if (holesX[5] <= -0.15 && holeLOR6 == 1) {
			holeLOR6 = 0;
			holesX[5] = holesX[5] + 0.01;
		}
		else if (holesX[5] < 0.15 && holeLOR6 == 0) {
			holesX[5] = holesX[5] + 0.01;
		}
		else if (holesX[5] >= 0.15 && holeLOR6 == 0) {
			holeLOR6 = 1;
			holesX[5] = holesX[5] - 0.01;
		}
	}

	if (gameState == 3) {
		if (holesX[6] > -0.15 && holeLOR7 == 1) {
			holesX[6] = holesX[6] - 0.01;
		}
		else if (holesX[6] <= -0.15 && holeLOR7== 1) {
			holeLOR7 = 0;
			holesX[6] = holesX[6] + 0.01;
		}
		else if (holesX[6] < 0.15 && holeLOR7 == 0) {
			holesX[6] = holesX[6] + 0.01;
		}
		else if (holesX[6] >= 0.15 && holeLOR7 == 0) {
			holeLOR7 = 1;
			holesX[6] = holesX[6] - 0.01;
		}
	}


	glutPostRedisplay();

}
void drawGround(double thickness) {

	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glScaled(0.25, thickness, 5.0);
	glutSolidCube(2);
	glPopMatrix();
	
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glTranslated(0, 0.021, 0);
	glBegin(GL_QUADS);
	
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-0.25, 0, -5);
	glTexCoord2f(5, 0);
	glVertex3f(0.25, 0, -5);
	glTexCoord2f(5, 5);
	glVertex3f(0.25, 0, 5);
	glTexCoord2f(0, 5);
	glVertex3f(-0.25, 0, 5);

	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void drawGround2(double thickness) {
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_sea.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glTranslated(0, -0.5, 0);
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-5, 0, -8);
	glTexCoord2f(5, 0);
	glVertex3f(5, 0, -8);
	glTexCoord2f(5, 5);
	glVertex3f(5, 0, 8);
	glTexCoord2f(0, 5);
	glVertex3f(-5, 0, 8);

	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
void drawGround3(double thickness) {

	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glScaled(0.25, thickness, 5.0);
	glutSolidCube(2);
	glPopMatrix();

	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground2.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glTranslated(0, 0.021, 0);
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-0.25, 0, -5);
	glTexCoord2f(5, 0);
	glVertex3f(0.25, 0, -5);
	glTexCoord2f(5, 5);
	glVertex3f(0.25, 0, 5);
	glTexCoord2f(0, 5);
	glVertex3f(-0.25, 0, 5);

	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.



    double zTemp = -6;
	double xTemp = -0.5;
	for (int j = 0; j < 2; j++) {
		zTemp = -6;
		for (int i = 0; i < 25; i++) {
			glPushMatrix();
			glRotated(45, 0, 1, 0);
			glTranslatef(xTemp, -0.5, zTemp);
			glScalef(0.25, 0.5, 0.25);
			model_tree.Draw();
			glPopMatrix();
			zTemp = zTemp + 0.5;
		}
		xTemp = xTemp + 1;
	}
	
}

void drawGround4(double thickness) {
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground3.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glTranslated(0, -0.5, 0);
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-5, 0, -8);
	glTexCoord2f(5, 0);
	glVertex3f(5, 0, -8);
	glTexCoord2f(5, 5);
	glVertex3f(5, 0, 8);
	glTexCoord2f(0, 5);
	glVertex3f(-5, 0, 8);

	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void drawBall() {
	glPushMatrix();
	glColor3f(ballR, ballG, ballB);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(0, 0.045, 0.4); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();
}

void drawHole() {
	glPushMatrix();
	glColor3f(0,0, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(0, 0.01, 0.4); // sphere at (1,1,0)  
	glScaled(1, 0.25, 1);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();
}
void drawBackground() {
	glPushMatrix();
	
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	//glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();


}

void drawPlayer() {
	//ball
	glPushMatrix();
	glColor3f(mainBallR, mainBallG, mainBallB);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(0, 0.17, 0.46); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();
	//shoes
	glPushMatrix();
	glColor3f(0.5529411765f, 0.5215686275f, 0.5019607843f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.011, 0.03, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.02, 0.02, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5529411765f, 0.5215686275f, 0.5019607843f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.011, 0.03, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.02, 0.02, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//legs
	glPushMatrix();
	glColor3f(0.3254901961f, 0.2470588235f, 0.733333333f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.011, 0.075, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.02, 0.07, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3254901961f, 0.2470588235f, 0.733333333f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.011, 0.075, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.02, 0.07, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//body 
	glPushMatrix();
	glColor3f(PlayerR, PlayerG, PlayerB);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.14, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.042, 0.06, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//head
	glPushMatrix();
	glColor3f(0.7960784314f, 0.5607843137f, 0.431372549f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.19, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.04, 0.04, 0.04);
	glutSolidCube(1.0);
	glPopMatrix();

	//arms 
	glPushMatrix();
	glColor3f(0.7960784314f, 0.5607843137f, 0.431372549f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.0285, 0.163, 0.43); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.04, 0.015);
	
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7960784314f, 0.5607843137f, 0.431372549f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.0285, 0.163, 0.43); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.04, 0.015);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(PlayerR, PlayerG, PlayerB);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.0285, 0.162, 0.4); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.015, 0.015);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(PlayerR, PlayerG, PlayerB);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.0285, 0.162, 0.4); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.015, 0.015);
	glutSolidCube(1.0);
	glPopMatrix();
	// face 
   //hair 

	glPushMatrix();
	glColor3f(0.2117647059f, 0.133333333f, 0.05098039216f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.21, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.041, 0.01, 0.041);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.2117647059f, 0.133333333f, 0.05098039216f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.19, 0.3895); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.041, 0.04, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//eyes
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.009, 0.195, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.0075, 0.1945, 0.4111); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.003, 0.003, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.009, 0.195, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.0075, 0.1945, 0.4111); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.003, 0.003, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//nose
	glPushMatrix();
	glColor3f(0.66666666667f, 0.4549019608f, 0.3568627451f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.189, 0.41101); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.003, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//eyebrows
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.009, 0.2, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.001, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.009, 0.2, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.001, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//mouth 

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.183, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.008, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.183, 0.4111); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.008, 0.001, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawPlayer1() {
	//ball
	glPushMatrix();
	glColor3f(mainBallR, mainBallG, mainBallB);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(0, 0.17, 0.46); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();
	//shoes
	glPushMatrix();
	glColor3f(0.5529411765f, 0.5215686275f, 0.5019607843f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.011, 0.035, 0.375); // big cube at (0.5, 0.5, 0.5)
	glRotated(20.0, 1, 0, 0);
	glScaled(0.02, 0.02, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5529411765f, 0.5215686275f, 0.5019607843f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.011, 0.035, 0.425); // big cube at (0.5, 0.5, 0.5)
	glRotated(-20.0, 1, 0, 0);
	glScaled(0.02, 0.02, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//legs
	glPushMatrix();
	glColor3f(0.3254901961f, 0.2470588235f, 0.733333333f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.011, 0.075, 0.39); // big cube at (0.5, 0.5, 0.5)
	glRotated(20.0, 1, 0, 0);
	glScaled(0.02, 0.07, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3254901961f, 0.2470588235f, 0.733333333f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.011, 0.075, 0.41); // big cube at (0.5, 0.5, 0.5)
	glRotated(-20.0, 1, 0, 0);
	glScaled(0.02, 0.07, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//body 
	glPushMatrix();
	glColor3f(PlayerR, PlayerG, PlayerB);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.14, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.042, 0.06, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//head
	glPushMatrix();
	glColor3f(0.7960784314f, 0.5607843137f, 0.431372549f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.19, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.04, 0.04, 0.04);
	glutSolidCube(1.0);
	glPopMatrix();

	//arms 
	glPushMatrix();
	glColor3f(0.7960784314f, 0.5607843137f, 0.431372549f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.0285, 0.163, 0.43); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.04, 0.015);

	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7960784314f, 0.5607843137f, 0.431372549f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.0285, 0.163, 0.43); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.04, 0.015);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(PlayerR, PlayerG, PlayerB);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.0285, 0.162, 0.4); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.015, 0.015);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(PlayerR, PlayerG, PlayerB);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.0285, 0.162, 0.4); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.015, 0.015);
	glutSolidCube(1.0);
	glPopMatrix();
	// face 
   //hair 

	glPushMatrix();
	glColor3f(0.2117647059f, 0.133333333f, 0.05098039216f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.21, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.041, 0.01, 0.041);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.2117647059f, 0.133333333f, 0.05098039216f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.19, 0.3895); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.041, 0.04, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//eyes
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.009, 0.195, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.0075, 0.1945, 0.4111); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.003, 0.003, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.009, 0.195, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.0075, 0.1945, 0.4111); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.003, 0.003, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//nose
	glPushMatrix();
	glColor3f(0.66666666667f, 0.4549019608f, 0.3568627451f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.189, 0.41101); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.003, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//eyebrows
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.009, 0.2, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.001, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.009, 0.2, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.001, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//mouth 

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.183, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.008, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.183, 0.4111); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.008, 0.001, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawPlayer2() {
	//ball
	glPushMatrix();
	glColor3f(mainBallR, mainBallG, mainBallB);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(0, 0.17, 0.46); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();
	//shoes
	glPushMatrix();
	glColor3f(0.5529411765f, 0.5215686275f, 0.5019607843f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.011, 0.035, 0.425); // big cube at (0.5, 0.5, 0.5)
	glRotated(-20.0, 1, 0, 0);
	glScaled(0.02, 0.02, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5529411765f, 0.5215686275f, 0.5019607843f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.011, 0.035, 0.375); // big cube at (0.5, 0.5, 0.5)
	glRotated(20.0, 1, 0, 0);
	glScaled(0.02, 0.02, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//legs
	glPushMatrix();
	glColor3f(0.3254901961f, 0.2470588235f, 0.733333333f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.011, 0.075, 0.41); // big cube at (0.5, 0.5, 0.5)
	glRotated(-20.0, 1, 0, 0);
	glScaled(0.02, 0.07, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3254901961f, 0.2470588235f, 0.733333333f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.011, 0.075, 0.39); // big cube at (0.5, 0.5, 0.5)
	glRotated(20.0, 1, 0, 0);
	glScaled(0.02, 0.07, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//body 
	glPushMatrix();
	glColor3f(PlayerR, PlayerG, PlayerB);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.14, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.042, 0.06, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//head
	glPushMatrix();
	glColor3f(0.7960784314f, 0.5607843137f, 0.431372549f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.19, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.04, 0.04, 0.04);
	glutSolidCube(1.0);
	glPopMatrix();

	//arms 

	glPushMatrix();
	glColor3f(0.7960784314f, 0.5607843137f, 0.431372549f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.0285, 0.163, 0.43); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.04, 0.015);

	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7960784314f, 0.5607843137f, 0.431372549f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.0285, 0.163, 0.43); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.04, 0.015);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(PlayerR, PlayerG, PlayerB);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.0285, 0.162, 0.4); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.015, 0.015);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(PlayerR, PlayerG, PlayerB);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.0285, 0.162, 0.4); // big cube at (0.5, 0.5, 0.5)
	glRotated(90.0, 1, 0, 0);
	glScaled(0.015, 0.015, 0.015);
	glutSolidCube(1.0);
	glPopMatrix();
	// face 
   //hair 

	glPushMatrix();
	glColor3f(0.2117647059f, 0.133333333f, 0.05098039216f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.21, 0.4); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.041, 0.01, 0.041);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.2117647059f, 0.133333333f, 0.05098039216f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.19, 0.3895); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.041, 0.04, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//eyes
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.009, 0.195, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.0075, 0.1945, 0.4111); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.003, 0.003, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.009, 0.195, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.0075, 0.1945, 0.4111); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.003, 0.003, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//nose
	glPushMatrix();
	glColor3f(0.66666666667f, 0.4549019608f, 0.3568627451f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.189, 0.41101); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.003, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//eyebrows
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0.009, 0.2, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.001, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(-0.009, 0.2, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.006, 0.001, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	//mouth 

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.183, 0.411); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.008, 0.004, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0.183, 0.4111); // big cube at (0.5, 0.5, 0.5)
	glScaled(0.008, 0.001, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawPlayerRight() {
	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glTranslated(-0.4, 0, 0.4);

	glRotated(45, 0, 1, 0);
	drawPlayer();
	glPopMatrix();
}
void drawPlayerRight1() {
	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glTranslated(-0.4, 0, 0.4);

	glRotated(45, 0, 1, 0);
	drawPlayer1();
	glPopMatrix();
}
void drawPlayerRight2() {
	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glTranslated(-0.4, 0, 0.4);

	glRotated(45, 0, 1, 0);
	drawPlayer2();
	glPopMatrix();
}

void drawPlayerBack() {
	glPushMatrix();
	glRotated(135, 0, 1, 0);
	glTranslated(-0.8, 0, 0);

	glRotated(45, 0, 1, 0);
	drawPlayer();
	glPopMatrix();
}
void drawPlayerBack1() {
	glPushMatrix();
	glRotated(135, 0, 1, 0);
	glTranslated(-0.8, 0, 0);

	glRotated(45, 0, 1, 0);
	drawPlayer1();
	glPopMatrix();
}
void drawPlayerBack2() {
	glPushMatrix();
	glRotated(135, 0, 1, 0);
	glTranslated(-0.8, 0, 0);

	glRotated(45, 0, 1, 0);
	drawPlayer2();
	glPopMatrix();
}
void drawPlayerLeft() {
	glPushMatrix();
	glRotated(-45, 0, 1, 0);
	glTranslated(0.4, 0, -0.4);

	glRotated(-45, 0, 1, 0);
	drawPlayer();
	glPopMatrix();
}
void drawPlayerLeft1() {
	glPushMatrix();
	glRotated(-45, 0, 1, 0);
	glTranslated(0.4, 0, -0.4);

	glRotated(-45, 0, 1, 0);
	drawPlayer1();
	glPopMatrix();
}
void drawPlayerLeft2() {
	glPushMatrix();
	glRotated(-45, 0, 1, 0);
	glTranslated(0.4, 0, -0.4);

	glRotated(-45, 0, 1, 0);
	drawPlayer2();
	glPopMatrix();
}
/*
void drawbackground() {
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	//glTranslated(50, 0, 0);
	//glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 10, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();
}*/

void setupLights() {
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient[] = { 0.7f, 0.7, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, lightstate,lightmove, 0.0 };
	GLfloat lightIntensity[] = { lightC, 1, lightC, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

//=======================================================================
// Lighting Configuration Function
//=======================================================================
/*
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}
*/
//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	//InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	camera.look();
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

void score() {
	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	char* p0s[50];
	glTranslated(-0.01, 0.3, 4.88);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Score: %d", Score);
	print(0, 0, (char*)p0s);
	glPopMatrix();
}
void drawIntro() {
	
	
	glPushMatrix();
	glColor3f(0.203921568627f, 0.68235294117f, 0.9215686274509f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0, -1); // big cube at (0.5, 0.5, 0.5)
	//glScaled(0.006, 0.001, 0.02);
	glutSolidCube(5.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball1X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball2X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball3X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0, 0.5);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball4X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	char* p0s[50];
	glTranslated(-0.23, 0.2, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Level one (Island)");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.5, 0.1, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	sprintf((char*)p0s, "-Try to collect any number of balls with the same");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.22, 0.0, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	sprintf((char*)p0s, " color you have");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.5, -0.1, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "-Try to avoid the holes and the balls with  ");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.22, -0.2, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	sprintf((char*)p0s, "  different colors");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.23, -0.3, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "-You have 1 min ");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.23, -0.4, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Press (P) to start ");
	print(0, 0, (char*)p0s);
	glPopMatrix();
}
void drawIntro2() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glPushMatrix();
	glColor3f(0.203921568627f, 0.68235294117f, 0.9215686274509f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0, -1); // big cube at (0.5, 0.5, 0.5)
	//glScaled(0.006, 0.001, 0.02);
	glutSolidCube(5.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball1X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball2X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball3X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0, 0.5);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball4X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	char* p0s[50];
	glTranslated(-0.23, 0.2, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Level one (Island)");
	print(0, 0, (char*)p0s);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.22, 0.0, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	sprintf((char*)p0s, " You lost");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	level1Timer = 0;
	
	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.23, -0.4, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Press (P) to play again");
	print(0, 0, (char*)p0s);
	glPopMatrix();
}
void drawIntro3() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glPushMatrix();
	glColor3f(0.203921568627f, 0.68235294117f, 0.9215686274509f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0, -1); // big cube at (0.5, 0.5, 0.5)
	//glScaled(0.006, 0.001, 0.02);
	glutSolidCube(5.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball1X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball2X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball3X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0, 0.5);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball4X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	char* p0s[50];
	glTranslated(-0.23, 0.4, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Score: %d", Score);
	print(0, 0, (char*)p0s);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.23, 0.2, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Level two (Forest)");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.5, 0.1, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	sprintf((char*)p0s, "-Try to collect atleast 10 balls with the same ");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.22, 0.0, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	sprintf((char*)p0s, " color you have to win");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.5, -0.1, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "-Try to avoid the holes and the balls with  ");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.22, -0.2, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	sprintf((char*)p0s, "  different colors");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.23, -0.3, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "-You have 1.5 min ");
	print(0, 0, (char*)p0s);
	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.23, -0.4, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Press (P) to start ");
	print(0, 0, (char*)p0s);
	glPopMatrix();
}
void drawIntro4() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glPushMatrix();
	glColor3f(0.203921568627f, 0.68235294117f, 0.9215686274509f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0, -1); // big cube at (0.5, 0.5, 0.5)
	//glScaled(0.006, 0.001, 0.02);
	glutSolidCube(5.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball1X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball2X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball3X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0, 0.5);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball4X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	char* p0s[50];
	glTranslated(-0.23, 0.2, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Level two (Forest)");
	print(0, 0, (char*)p0s);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.22, 0.0, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	sprintf((char*)p0s, " You lost");
	print(0, 0, (char*)p0s);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.23, -0.4, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Press (P) to play again");
	print(0, 0, (char*)p0s);
	glPopMatrix();
}
void drawIntro5() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glPushMatrix();
	glColor3f(0.203921568627f, 0.68235294117f, 0.9215686274509f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glRotated(45.0, 0, 1, 0);
	glTranslated(0, 0, -1); // big cube at (0.5, 0.5, 0.5)
	//glScaled(0.006, 0.001, 0.02);
	glutSolidCube(5.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball1X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball2X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball3X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0, 0.5);
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(ball4X, ballsY, 2.5); // sphere at (1,1,0)  
	glutSolidSphere(0.03, 10, 10);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	char* p0s[50];
	glTranslated(-0.23, 0.2, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Level two (Forest)");
	print(0, 0, (char*)p0s);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.22, 0.0, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	sprintf((char*)p0s, " You won");
	print(0, 0, (char*)p0s);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0.0, 1.0, 0.0);
	glTranslated(-0.23, -0.4, 2.5);
	glRotated(-45, 0.0, 1.0, 0.0);
	sprintf((char*)p0s, "Score: %d", Score);
	print(0, 0, (char*)p0s);
	glPopMatrix();
}
void Display() {
	if (gameState == 0) {
		setupCamera();
		setupLights();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (firstTime == 1) {

		
		camera.eye = Vector3f(2.6571f, -0.259243f, 2.65719f);
		camera.up = Vector3f(0.0191321f, 0.999634f, 0.0191321f);
		camera.center = Vector3f(1.95034f, -0.232186f, 1.95034f);
		firstTime =0;
		}

		drawIntro();

	}
	if (gameState == 2) {
		setupCamera();
		setupLights();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (firstTime == 1) {


			camera.eye = Vector3f(2.6571f, -0.259243f, 2.65719f);
			camera.up = Vector3f(0.0191321f, 0.999634f, 0.0191321f);
			camera.center = Vector3f(1.95034f, -0.232186f, 1.95034f);
			firstTime = 0;
		}

		drawIntro3();

	}
	if (gameState == 10) {
		setupCamera();
		setupLights();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (firstTime == 1) {


			camera.eye = Vector3f(2.6571f, -0.259243f, 2.65719f);
			camera.up = Vector3f(0.0191321f, 0.999634f, 0.0191321f);
			camera.center = Vector3f(1.95034f, -0.232186f, 1.95034f);
			firstTime = 0;
		}

		drawIntro2();

	}
	if (gameState == 1 || gameState == 6) {
		setupCamera();
		setupLights();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
		glPushMatrix();
		drawbackground();
		glPopMatrix();
		*/
		glPushMatrix();

		
		glRotatef(90.f, 0, 0, 0);
		//glColor3f(0.9, 0, 0.5);
		glScaled(0.1, 0.1, 0.1);
		ship_model.Draw();
		glPopMatrix();

		glPushMatrix();
		drawGround(0.02);
		glPopMatrix();

		glPushMatrix();
		drawGround2(0.02);
		glPopMatrix();


		double TextZ = 0;
		for (int i = 0; i < 10; i++) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(0, 0, TextZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			score();
			glPopMatrix();
			TextZ = TextZ - 1.2;
		}




		if (firstTime == 1) {
			
			double zDis = 1.2;
			double Z = 4.2;
			for (int i = 0; i < 8; i++) {

				double temp = rand() % (44) + (-22);
				double X = temp / 100;

				ballR = 0;
				ballG = 0;
				ballB = 1;


				Balls1Xs[i] = X;
				Balls1Zs[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawBall();
				glPopMatrix();
				Z = Z - zDis;
				//zDis = zDis - 0.3;
			}

			Z = 4;
			for (int i = 0; i < 8; i++) {

				double temp = rand() % (44) + (-22);
				X = temp / 100;



				ballR = 0;
				ballG = 1;
				ballB = 0;

				Balls2Xs[i] = X;
				Balls2Zs[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawBall();
				glPopMatrix();
				Z = Z - zDis;
				//	zDis = zDis + 0.3;
			}

			Z = 3.8;
			for (int i = 0; i < 8; i++) {

				double temp = rand() % (44) + (-22);
				X = temp / 100;



				ballR = 0.9;
				ballG = 0;
				ballB = 0.5;

				Balls3Xs[i] = X;
				Balls3Zs[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawBall();
				glPopMatrix();
				Z = Z - zDis;
				//	zDis = zDis + 0.3;
			}

			Z = 3.6;
			for (int i = 0; i < 8; i++) {

				double temp = rand() % (44) + (-22);
				X = temp / 100;



				ballR = 1;
				ballG = 0;
				ballB = 0;

				Balls4Xs[i] = X;
				Balls4Zs[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawBall();
				glPopMatrix();
				Z = Z - zDis;
				//	zDis = zDis + 0.3;
			}



		}
		else {

			for (int i = 0; i < 8; i++) {
				ballR = 0;
				ballG = 0;
				ballB = 1;
				X = Balls1Xs[i];
				Z = Balls1Zs[i];

				if (X != 500 && Z != 500) {
					glPushMatrix();
					glRotated(45, 0.0, 1.0, 0.0);
					glTranslated(X, 0, Z);
					glRotated(-45, 0.0, 1.0, 0.0);
					drawBall();
					glPopMatrix();
				}
			}
			for (int i = 0; i < 8; i++) {




				ballR = 0;
				ballG = 1;
				ballB = 0;

				X = Balls2Xs[i];
				Z = Balls2Zs[i];
				if (X != 500 && Z != 500) {
					glPushMatrix();
					glRotated(45, 0.0, 1.0, 0.0);
					glTranslated(X, 0, Z);
					glRotated(-45, 0.0, 1.0, 0.0);
					drawBall();
					glPopMatrix();
				}
			}
			for (int i = 0; i < 8; i++) {


				ballR = 0.9;
				ballG = 0;
				ballB = 0.5;

				X = Balls3Xs[i];
				Z = Balls3Zs[i];
				if (X != 500 && Z != 500) {
					glPushMatrix();
					glRotated(45, 0.0, 1.0, 0.0);
					glTranslated(X, 0, Z);
					glRotated(-45, 0.0, 1.0, 0.0);
					drawBall();
					glPopMatrix();
				}
			}
			for (int i = 0; i < 8; i++) {



				ballR = 1;
				ballG = 0;
				ballB = 0;

				X = Balls4Xs[i];
				Z = Balls4Zs[i];
				if (X != 500 && Z != 500) {
					glPushMatrix();
					glRotated(45, 0.0, 1.0, 0.0);
					glTranslated(X, 0, Z);
					glRotated(-45, 0.0, 1.0, 0.0);
					drawBall();
					glPopMatrix();
				}
			}

		}

		if (firstTime == 1) {
			double zDis = 1.2;
			double Z = 3.3;
			for (int i = 0; i < 7; i++) {

				double temp = rand() % (30) + (-15);
				double X = temp / 100;


				holesX[i] = X;
				holesZ[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawHole();
				glPopMatrix();
				Z = Z - zDis;
			}
			firstTime = 0;
		}
		else {
			for (int i = 0; i < 7; i++) {
				X = holesX[i];
				Z = holesZ[i];
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawHole();
				glPopMatrix();
			}
		}


		//glRotated(playerAngle, 0.0, 1.0, 0.0);
		//Player
		if (playerState == 0) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			glTranslated(-playerX, 0, -playerZ);
			glRotated(playerAngle, 0.0, 1.0, 0.0);
			glTranslated(playerX, 0, playerZ);

			drawPlayer();
			glPopMatrix();




		}
		else if (playerState == 1) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			drawPlayer1();
			glPopMatrix();

		}
		else if (playerState == 2) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayer();
			glPopMatrix();


		}
		else if (playerState == 3) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayer2();
			glPopMatrix();


		}
		else if (playerState == 4) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			drawPlayerRight();
			glPopMatrix();

		}
		else if (playerState == 5) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerRight1();
			glPopMatrix();

		}
		else if (playerState == 6) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerRight();
			glPopMatrix();


		}
		else if (playerState == 7) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerRight2();
			glPopMatrix();


		}
		else if (playerState == 8) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			drawPlayerBack();
			glPopMatrix();

		}
		else if (playerState == 9) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerBack1();
			glPopMatrix();

		}
		else if (playerState == 10) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerBack();
			glPopMatrix();


		}
		else if (playerState == 11) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerBack2();
			glPopMatrix();


		}
		else if (playerState == 12) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			drawPlayerLeft();
			glPopMatrix();

		}
		else if (playerState == 13) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerLeft1();
			glPopMatrix();

		}
		else if (playerState == 14) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerLeft();
			glPopMatrix();


		}
		else if (playerState == 15) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerLeft2();
			glPopMatrix();


		}
	}
else if (gameState == 3 || gameState == 7) {
		setupCamera();
		setupLights();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
		glPushMatrix();
		drawbackground();
		glPopMatrix();
		*/

		glPushMatrix();
		drawGround3(0.02);
		glPopMatrix();

		glPushMatrix();
		drawGround4(0.02);
		glPopMatrix();


		double TextZ = 0;
		for (int i = 0; i < 10; i++) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(0, 0, TextZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			score();
			glPopMatrix();
			TextZ = TextZ - 1.2;
		}




		if (firstTime == 1) {
			double zDis = 1.2;
			double Z = 4.2;
			for (int i = 0; i < 8; i++) {

				double temp = rand() % (44) + (-22);
				double X = temp / 100;

				ballR = 0;
				ballG = 0;
				ballB = 1;


				Balls1Xs[i] = X;
				Balls1Zs[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawBall();
				glPopMatrix();
				Z = Z - zDis;
				//zDis = zDis - 0.3;
			}

			Z = 4;
			for (int i = 0; i < 8; i++) {

				double temp = rand() % (44) + (-22);
				X = temp / 100;



				ballR = 0;
				ballG = 1;
				ballB = 0;

				Balls2Xs[i] = X;
				Balls2Zs[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawBall();
				glPopMatrix();
				Z = Z - zDis;
				//	zDis = zDis + 0.3;
			}

			Z = 3.8;
			for (int i = 0; i < 8; i++) {

				double temp = rand() % (44) + (-22);
				X = temp / 100;



				ballR = 0.9;
				ballG = 0;
				ballB = 0.5;

				Balls3Xs[i] = X;
				Balls3Zs[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawBall();
				glPopMatrix();
				Z = Z - zDis;
				//	zDis = zDis + 0.3;
			}

			Z = 3.6;
			for (int i = 0; i < 8; i++) {

				double temp = rand() % (44) + (-22);
				X = temp / 100;



				ballR = 1;
				ballG = 0;
				ballB = 0;

				Balls4Xs[i] = X;
				Balls4Zs[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawBall();
				glPopMatrix();
				Z = Z - zDis;
				//	zDis = zDis + 0.3;
			}



		}
		else {

			for (int i = 0; i < 8; i++) {
				ballR = 0;
				ballG = 0;
				ballB = 1;
				X = Balls1Xs[i];
				Z = Balls1Zs[i];

				if (X != 500 && Z != 500) {
					glPushMatrix();
					glRotated(45, 0.0, 1.0, 0.0);
					glTranslated(X, 0, Z);
					glRotated(-45, 0.0, 1.0, 0.0);
					drawBall();
					glPopMatrix();
				}
			}
			for (int i = 0; i < 8; i++) {




				ballR = 0;
				ballG = 1;
				ballB = 0;

				X = Balls2Xs[i];
				Z = Balls2Zs[i];
				if (X != 500 && Z != 500) {
					glPushMatrix();
					glRotated(45, 0.0, 1.0, 0.0);
					glTranslated(X, 0, Z);
					glRotated(-45, 0.0, 1.0, 0.0);
					drawBall();
					glPopMatrix();
				}
			}
			for (int i = 0; i < 8; i++) {


				ballR = 0.9;
				ballG = 0;
				ballB = 0.5;

				X = Balls3Xs[i];
				Z = Balls3Zs[i];
				if (X != 500 && Z != 500) {
					glPushMatrix();
					glRotated(45, 0.0, 1.0, 0.0);
					glTranslated(X, 0, Z);
					glRotated(-45, 0.0, 1.0, 0.0);
					drawBall();
					glPopMatrix();
				}
			}
			for (int i = 0; i < 8; i++) {



				ballR = 1;
				ballG = 0;
				ballB = 0;

				X = Balls4Xs[i];
				Z = Balls4Zs[i];
				if (X != 500 && Z != 500) {
					glPushMatrix();
					glRotated(45, 0.0, 1.0, 0.0);
					glTranslated(X, 0, Z);
					glRotated(-45, 0.0, 1.0, 0.0);
					drawBall();
					glPopMatrix();
				}
			}

		}

		if (firstTime == 1) {
			double zDis = 1.2;
			double Z = 3.3;
			for (int i = 0; i < 7; i++) {

				double temp = rand() % (44) + (-22);
				double X = temp / 100;


				holesX[i] = X;
				holesZ[i] = Z;
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawHole();
				glPopMatrix();
				Z = Z - zDis;
			}
			firstTime = 0;
		}
		else {
			for (int i = 0; i < 7; i++) {
				X = holesX[i];
				Z = holesZ[i];
				glPushMatrix();
				glRotated(45, 0.0, 1.0, 0.0);
				glTranslated(X, 0, Z);
				glRotated(-45, 0.0, 1.0, 0.0);
				drawHole();
				glPopMatrix();
			}
		}


		//glRotated(playerAngle, 0.0, 1.0, 0.0);
		//Player
		if (playerState == 0) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			glTranslated(-playerX, 0, -playerZ);
			glRotated(playerAngle, 0.0, 1.0, 0.0);
			glTranslated(playerX, 0, playerZ);

			drawPlayer();
			glPopMatrix();




		}
		else if (playerState == 1) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			drawPlayer1();
			glPopMatrix();

		}
		else if (playerState == 2) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayer();
			glPopMatrix();


		}
		else if (playerState == 3) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayer2();
			glPopMatrix();


		}
		else if (playerState == 4) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			drawPlayerRight();
			glPopMatrix();

		}
		else if (playerState == 5) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerRight1();
			glPopMatrix();

		}
		else if (playerState == 6) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerRight();
			glPopMatrix();


		}
		else if (playerState == 7) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerRight2();
			glPopMatrix();


		}
		else if (playerState == 8) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			drawPlayerBack();
			glPopMatrix();

		}
		else if (playerState == 9) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerBack1();
			glPopMatrix();

		}
		else if (playerState == 10) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerBack();
			glPopMatrix();


		}
		else if (playerState == 11) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerBack2();
			glPopMatrix();


		}
		else if (playerState == 12) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);

			drawPlayerLeft();
			glPopMatrix();

		}
		else if (playerState == 13) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerLeft1();
			glPopMatrix();

		}
		else if (playerState == 14) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerLeft();
			glPopMatrix();


		}
		else if (playerState == 15) {
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(playerX, playerY, playerZ);
			glRotated(-45, 0.0, 1.0, 0.0);
			drawPlayerLeft2();
			glPopMatrix();


		}
	} 
else if(gameState == 4) {

	}
else if (gameState == 5) {
		setupCamera();
		setupLights();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (firstTime == 1) {


			camera.eye = Vector3f(2.6571f, -0.259243f, 2.65719f);
			camera.up = Vector3f(0.0191321f, 0.999634f, 0.0191321f);
			camera.center = Vector3f(1.95034f, -0.232186f, 1.95034f);
			firstTime = 0;
		}

		drawIntro4();
	}
	glFlush();
}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;
	float a = 0.01;
	/*cout << " game State = ";
	cout << gameState;
	cout << "\n";*/
	if (gameState == 0) {
		switch (key) {
		case 'p':
			gameState = 1;
			playerX = 0;
			playerY = 0;
			playerZ = 4.47;
			playerState = 0;
			firstTime = 1;
			Score = 0;

			ballR = 0;
			ballG = 0;
			ballB = 0;

			mainBallR = 0;
			mainBallG = 0;
			mainBallB = 1;

			mainBall = 0;

			X = 0;
			Z = 0;
			camera.eye = Vector3f(3.6694f, 0.600514f, 3.66341f);
			camera.up = Vector3f(-0.411004f, 0.805294f, -0.427291f);
			camera.center = Vector3f(3.0993f, 0.00771928f, 3.09457f);
			
			break;
		}
	}
	if ( gameState == 1) {
		switch (key) {
		/*case 'w':
			camera.moveY(d);
			break;
		case 's':
			camera.moveY(-d);
			break;
		case 'a':
			camera.moveX(d);
			break;
		case 'd':
			camera.moveX(-d);
			break;
		case 'q':
			camera.moveZ(a);
			break;
		case 'e':
			camera.moveZ(-a);
			break;*/

		case'4':
			if (playerX > -0.22) {
				playerX = playerX - 0.01;
			}
			if (playerState == 0 || playerState == 1 || playerState == 2 || playerState == 3 || playerState == 4 || playerState == 5 || playerState == 6 || playerState == 7 || playerState == 8 || playerState == 9 || playerState == 10 || playerState == 11 || playerState == 15) {
				playerState = 12;
			}
			else if (playerState == 12) {
				playerState = 13;
			}
			else if (playerState == 13) {
				playerState = 14;
			}
			else if (playerState == 14) {
				playerState = 15;
			}


			if (mainBall == 0) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						Score++;
						Balls1Xs[i] = 500;
						Balls1Zs[i] = 500;
						cout << "here";
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
				}
			}
			else if (mainBall == 1) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						Score++;
						Balls2Xs[i] = 500;
						Balls2Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 2) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						Score++;
						Balls3Xs[i] = 500;
						Balls3Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 3) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						Score++;
						Balls4Xs[i] = 500;
						Balls4Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				if (playerX + 0.05 > holesX[i] && playerX - 0.05 < holesX[i] && playerZ + 0.05 > holesZ[i] && playerZ - 0.05 < holesZ[i]) {
					gameState = 6;
				
				}
			}
			break;
		case'8':
			if (playerZ > -5.31) {
				camera.moveZ(0.0079);
				camera.moveY(0.00549);
				playerZ = playerZ - 0.0096;


			}
			if (playerState == 0 || playerState == 1 || playerState == 2 || playerState == 3 || playerState == 4 || playerState == 5 || playerState == 6 || playerState == 7 || playerState == 11 || playerState == 12 || playerState == 13 || playerState == 14 || playerState == 15) {
				playerState = 8;
			}
			else if (playerState == 8) {
				playerState = 9;
			}
			else if (playerState == 9) {
				playerState = 10;
			}
			else if (playerState == 10) {
				playerState = 11;
			}
			if (mainBall == 0) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						Score++;
						Balls1Xs[i] = 500;
						Balls1Zs[i] = 500;
						cout << "here";
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
				}
			}
			else if (mainBall == 1) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						Score++;
						Balls2Xs[i] = 500;
						Balls2Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 2) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						Score++;
						Balls3Xs[i] = 500;
						Balls3Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 3) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						Score++;
						Balls4Xs[i] = 500;
						Balls4Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				if (playerX + 0.05 > holesX[i] && playerX - 0.05 < holesX[i] && playerZ + 0.05 > holesZ[i] && playerZ - 0.05 < holesZ[i]) {
					gameState = 6;
					
				}
			}

			break;
		case'6':
			if (playerX < 0.22) {
				playerX = playerX + 0.01;
			}
			if (playerState == 0 || playerState == 1 || playerState == 2 || playerState == 3 || playerState == 7 || playerState == 8 || playerState == 9 || playerState == 10 || playerState == 11 || playerState == 12 || playerState == 13 || playerState == 14 || playerState == 15) {
				playerState = 4;
			}
			else if (playerState == 4) {
				playerState = 5;
			}
			else if (playerState == 6) {
				playerState = 7;
			}
			else if (playerState == 5) {
				playerState = 6;
			}

			if (mainBall == 0) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						Score++;
						Balls1Xs[i] = 500;
						Balls1Zs[i] = 500;
						cout << "here";
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
				}
			}
			else if (mainBall == 1) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						Score++;
						Balls2Xs[i] = 500;
						Balls2Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 2) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						Score++;
						Balls3Xs[i] = 500;
						Balls3Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 3) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						Score++;
						Balls4Xs[i] = 500;
						Balls4Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				if (playerX + 0.05 > holesX[i] && playerX - 0.05 < holesX[i] && playerZ + 0.05 > holesZ[i] && playerZ - 0.05 < holesZ[i]) {
					gameState = 6;
					
				}
			}
			break;
		case'5':
			if (playerZ < 4.57) {

				camera.moveZ(-0.008);
				camera.moveY(-0.0055);
				playerZ = playerZ + 0.0096;

			}
			if (playerState == 0 || playerState == 4 || playerState == 5 || playerState == 6 || playerState == 7 || playerState == 8 || playerState == 9 || playerState == 10 || playerState == 11 || playerState == 12 || playerState == 13 || playerState == 14 || playerState == 15) {
				playerState = 1;
			}
			else if (playerState == 1) {
				playerState = 2;
			}
			else if (playerState == 2) {
				playerState = 3;
			}
			else if (playerState == 3) {
				playerState = 0;
			}
			if (mainBall == 0) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						Score++;
						Balls1Xs[i] = 500;
						Balls1Zs[i] = 500;
						cout << "here";
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
							gameState = 10;
							firstTime = 1;
						}
					}
				}
			}
			else if (mainBall == 1) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						Score++;
						Balls2Xs[i] = 500;
						Balls2Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState =10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 2) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						Score++;
						Balls3Xs[i] = 500;
						Balls3Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 3) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						Score++;
						Balls4Xs[i] = 500;
						Balls4Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 10;
						firstTime = 1;
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				if (playerX + 0.05 > holesX[i] && playerX - 0.05 < holesX[i] && playerZ + 0.05 > holesZ[i] && playerZ - 0.05 < holesZ[i]) {
					gameState = 6;
					
				}
			}
			break;
		case'p':
			cout << "  eyeX =   ";
			cout << camera.eye.x;
			cout << "  eyeY =   ";
			cout << camera.eye.y;
			cout << "  eyeZ =   ";
			cout << camera.eye.z;
			cout << "\n";
			cout << "  upX =   ";
			cout << camera.up.x;
			cout << "  upY =   ";
			cout << camera.up.y;
			cout << "  upZ =   ";
			cout << camera.up.z;
			cout << "\n";
			cout << "  centerX =   ";
			cout << camera.center.x;
			cout << "  centerY =   ";
			cout << camera.center.y;
			cout << "  centerZ =   ";
			cout << camera.center.z;
			cout << "\n";
			cout << "  playerX =   ";
			cout << playerX;
			cout << "  playerZ =   ";
			cout << playerZ;
			cout << "\n";
			break;



		case GLUT_KEY_ESCAPE:
			exit(EXIT_SUCCESS);
		}
	}
	if (gameState == 3 ) {
		switch (key) {
		/*case 'w':
			camera.moveY(d);
			break;
		case 's':
			camera.moveY(-d);
			break;
		case 'a':
			camera.moveX(d);
			break;
		case 'd':
			camera.moveX(-d);
			break;
		case 'q':
			camera.moveZ(a);
			break;
		case 'e':
			camera.moveZ(-a);
			break;*/

		case'4':
			if (playerX > -0.22) {
				playerX = playerX - 0.01;
			}
			if (playerState == 0 || playerState == 1 || playerState == 2 || playerState == 3 || playerState == 4 || playerState == 5 || playerState == 6 || playerState == 7 || playerState == 8 || playerState == 9 || playerState == 10 || playerState == 11 || playerState == 15) {
				playerState = 12;
			}
			else if (playerState == 12) {
				playerState = 13;
			}
			else if (playerState == 13) {
				playerState = 14;
			}
			else if (playerState == 14) {
				playerState = 15;
			}


			if (mainBall == 0) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						Score++;
						Balls1Xs[i] = 500;
						Balls1Zs[i] = 500;
						cout << "here";
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
				}
			}
			else if (mainBall == 1) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						Score++;
						Balls2Xs[i] = 500;
						Balls2Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 2) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						Score++;
						Balls3Xs[i] = 500;
						Balls3Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 3) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						Score++;
						Balls4Xs[i] = 500;
						Balls4Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				if (playerX + 0.05 > holesX[i] && playerX - 0.05 < holesX[i] && playerZ + 0.05 > holesZ[i] && playerZ - 0.05 < holesZ[i]) {
					gameState = 7;
					
				}
			}
			break;
		case'8':
			if (playerZ > -5.31) {
				camera.moveZ(0.0079);
				camera.moveY(0.00549);
				playerZ = playerZ - 0.0096;


			}
			if (playerState == 0 || playerState == 1 || playerState == 2 || playerState == 3 || playerState == 4 || playerState == 5 || playerState == 6 || playerState == 7 || playerState == 11 || playerState == 12 || playerState == 13 || playerState == 14 || playerState == 15) {
				playerState = 8;
			}
			else if (playerState == 8) {
				playerState = 9;
			}
			else if (playerState == 9) {
				playerState = 10;
			}
			else if (playerState == 10) {
				playerState = 11;
			}
			if (mainBall == 0) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						Score++;
						Balls1Xs[i] = 500;
						Balls1Zs[i] = 500;
						cout << "here";
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
				}
			}
			else if (mainBall == 1) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						Score++;
						Balls2Xs[i] = 500;
						Balls2Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 2) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						Score++;
						Balls3Xs[i] = 500;
						Balls3Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 3) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						Score++;
						Balls4Xs[i] = 500;
						Balls4Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				if (playerX + 0.05 > holesX[i] && playerX - 0.05 < holesX[i] && playerZ + 0.05 > holesZ[i] && playerZ - 0.05 < holesZ[i]) {
					gameState = 7;
					

				}
			}

			break;
		case'6':
			if (playerX < 0.22) {
				playerX = playerX + 0.01;
			}
			if (playerState == 0 || playerState == 1 || playerState == 2 || playerState == 3 || playerState == 7 || playerState == 8 || playerState == 9 || playerState == 10 || playerState == 11 || playerState == 12 || playerState == 13 || playerState == 14 || playerState == 15) {
				playerState = 4;
			}
			else if (playerState == 4) {
				playerState = 5;
			}
			else if (playerState == 6) {
				playerState = 7;
			}
			else if (playerState == 5) {
				playerState = 6;
			}

			if (mainBall == 0) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						Score++;
						Balls1Xs[i] = 500;
						Balls1Zs[i] = 500;
						cout << "here";
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
				}
			}
			else if (mainBall == 1) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						Score++;
						Balls2Xs[i] = 500;
						Balls2Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 2) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						Score++;
						Balls3Xs[i] = 500;
						Balls3Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 3) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						Score++;
						Balls4Xs[i] = 500;
						Balls4Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				if (playerX + 0.05 > holesX[i] && playerX - 0.05 < holesX[i] && playerZ + 0.05 > holesZ[i] && playerZ - 0.05 < holesZ[i]) {
					gameState = 7;
					
				}
			}
			break;
		case'5':
			if (playerZ < 4.57) {

				camera.moveZ(-0.008);
				camera.moveY(-0.0055);
				playerZ = playerZ + 0.0096;

			}
			if (playerState == 0 || playerState == 4 || playerState == 5 || playerState == 6 || playerState == 7 || playerState == 8 || playerState == 9 || playerState == 10 || playerState == 11 || playerState == 12 || playerState == 13 || playerState == 14 || playerState == 15) {
				playerState = 1;
			}
			else if (playerState == 1) {
				playerState = 2;
			}
			else if (playerState == 2) {
				playerState = 3;
			}
			else if (playerState == 3) {
				playerState = 0;
			}
			if (mainBall == 0) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						Score++;
						Balls1Xs[i] = 500;
						Balls1Zs[i] = 500;
						cout << "here";
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
					for (int i = 0; i < 8; i++) {
						if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
							gameState = 5;
							firstTime = 1;
						}
					}
				}
			}
			else if (mainBall == 1) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						Score++;
						Balls2Xs[i] = 500;
						Balls2Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 2) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						Score++;
						Balls3Xs[i] = 500;
						Balls3Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			else if (mainBall == 3) {
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls4Xs[i] && playerX - 0.03 < Balls4Xs[i] && playerZ + 0.03 > Balls4Zs[i] && playerZ - 0.03 < Balls4Zs[i]) {
						Score++;
						Balls4Xs[i] = 500;
						Balls4Zs[i] = 500;
						cout << "here";
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls1Xs[i] && playerX - 0.03 < Balls1Xs[i] && playerZ + 0.03 > Balls1Zs[i] && playerZ - 0.03 < Balls1Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls2Xs[i] && playerX - 0.03 < Balls2Xs[i] && playerZ + 0.03 > Balls2Zs[i] && playerZ - 0.03 < Balls2Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
				for (int i = 0; i < 8; i++) {
					if (playerX + 0.03 > Balls3Xs[i] && playerX - 0.03 < Balls3Xs[i] && playerZ + 0.03 > Balls3Zs[i] && playerZ - 0.03 < Balls3Zs[i]) {
						gameState = 5;
						firstTime = 1;
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				if (playerX + 0.05> holesX[i] && playerX - 0.05 < holesX[i] && playerZ + 0.05 > holesZ[i] && playerZ - 0.05 < holesZ[i]) {
					gameState = 7;
					
				}
			}
			break;
		/*case'p':
			cout << "  eyeX =   ";
			cout << camera.eye.x;
			cout << "  eyeY =   ";
			cout << camera.eye.y;
			cout << "  eyeZ =   ";
			cout << camera.eye.z;
			cout << "\n";
			cout << "  upX =   ";
			cout << camera.up.x;
			cout << "  upY =   ";
			cout << camera.up.y;
			cout << "  upZ =   ";
			cout << camera.up.z;
			cout << "\n";
			cout << "  centerX =   ";
			cout << camera.center.x;
			cout << "  centerY =   ";
			cout << camera.center.y;
			cout << "  centerZ =   ";
			cout << camera.center.z;
			cout << "\n";
			cout << "  playerX =   ";
			cout << playerX;
			cout << "  playerZ =   ";
			cout << playerZ;
			cout << "\n";
			break;*/



		case GLUT_KEY_ESCAPE:
			exit(EXIT_SUCCESS);
		}
	}	else if (gameState == 5) {
		switch (key) {
		case 'p':
			gameState = 3;
			playerX = 0;
			playerY = 0;
			playerZ = 4.47;
			playerState = 0;
			firstTime = 1;
			Score = 0;
			
			ballR = 0;
			ballG = 0;
			ballB = 0;

			mainBallR = 0;
			mainBallG = 0;
			mainBallB = 1;

			mainBall = 0;

			X = 0;
			Z = 0;
			
			camera.eye = Vector3f(3.6694f, 0.600514f, 3.66341f);
			camera.up = Vector3f(-0.411004f, 0.805294f, -0.427291f);
			camera.center = Vector3f(3.0993f, 0.00771928f, 3.09457f);
			break;
				}
			}
	else if (gameState == 10) {
	switch (key) {
	case 'p':
		gameState = 1;
		playerX = 0;
		playerY = 0;
		playerZ = 4.47;
		playerState = 0;
		firstTime = 1;
		Score = 0;

		ballR = 0;
		ballG = 0;
		ballB = 0;

		mainBallR = 0;
		mainBallG = 0;
		mainBallB = 1;

		mainBall = 0;

		X = 0;
		Z = 0;

		camera.eye = Vector3f(3.6694f, 0.600514f, 3.66341f);
		camera.up = Vector3f(-0.411004f, 0.805294f, -0.427291f);
		camera.center = Vector3f(3.0993f, 0.00771928f, 3.09457f);
		break;
	}

			}else if (gameState == 2) {
				switch (key) {
				case 'p':
					gameState = 3;
					playerX = 0;
					playerY = 0;
					playerZ = 4.47;
					playerState = 0;
					firstTime = 1;
					Score = 0;

					ballR = 0;
					ballG = 0;
					ballB = 0;

					mainBallR = 0;
					mainBallG = 0;
					mainBallB = 1;

					mainBall = 0;

					X = 0;
					Z = 0;

					camera.eye = Vector3f(3.6694f, 0.600514f, 3.66341f);
					camera.up = Vector3f(-0.411004f, 0.805294f, -0.427291f);
					camera.center = Vector3f(3.0993f, 0.00771928f, 3.09457f);
					break;
				}

			}
			
	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	ship_model.Load("Models/ship/Toy Ship N050312.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");

	// Loading texture files
	tex_ground.Load("Textures/Untitled2.bmp");
	tex_ground2.Load("Textures/ground2.bmp");
	tex_sea.Load("Textures/sea.bmp");
	tex_ground3.Load("Textures/ground.bmp");


	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	loadBMP(&sand, "Textures/Untitled2.bmp", true);
}
int main(int argc, char** argv) {
	srand(time(0));
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	//PlaySound("sounds/Blazer Rail 2.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	camera.eye = Vector3f(3.6694f, 0.600514f, 3.66341f);
	camera.up = Vector3f(-0.411004f, 0.805294f, -0.427291f);
	camera.center = Vector3f(3.0993f, 0.00771928f, 3.09457f);
	
	glutCreateWindow("Lab 5");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	myInit();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	LoadAssets();
	glutTimerFunc(0, Timer, 0);
	glutIdleFunc(Anim);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
	return 0; 
}
