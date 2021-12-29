// File Header
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PI 3.14

// Variabel Kamera (Menentukan Posisi Awal Kamera)
float angle=0.0, deltaAngle = 0.0, ratio;
float x=-10.0f,y=25.0f,z=160.0f; // posisi awal kamera
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;

// Variabel Pesawat (Inisialisasi Awal)
float posY = 0, posX = 0, posZ = 0, wingDownY=0, wingDownX=0, bodyDownX=0,bodyDownY=0, angleWing=0;
static int rotAngleX =0, rotAngleY =0, rotAngleZ =0;
int planeMove = 0, planeBankLeft = 1, planeIdle=1;
float angleZ = 0, angleX = 0, buildingAngle = 0,buildDown=0;
GLUquadricObj *IDquadric;

// Variabel Pencahayaan (Inisialisasi Awal)
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

// Fungsi Init (Untuk Membuat Tempat Menggambar)
void init(void)
{
	glEnable (GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	IDquadric=gluNewQuadric(); // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(IDquadric, GLU_SMOOTH); // Create Smooth Normals ( NEW )
	gluQuadricTexture(IDquadric, GL_TRUE); // Create Texture Coords ( NEW )
}

// Fungsi Reshape (Mempertahankan Bentuk Gambar)
void Reshape(int w1, int h1)
{
	// Fungsi reshape (Menggerakkan kamera)
	if(h1 == 0) h1 = 1;
	w = w1;
	h = h1;
	ratio = 1.0f * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

// Fungsi OrientMe (Pergerakkan Kamera Kanan/Kiri)
void orientMe(float ang)
{
	lx = sin(ang/10);
	lz = -cos(ang/10);
	glLoadIdentity();
	gluLookAt(x, y, z,x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

// Fungsi moveMeFlat (Pergerakkan Kamera Maju/Mundur)
void moveMeFlat(int i)
{
	x = x + i*(lx)*0.1;
	z = z + i*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

// Fungsi Keyboard
void keyboard(unsigned char key, int x, int y)
{
	 switch (key)
	{
		case 'w': rotAngleX += 2; break;
		case 's': rotAngleX -= 2; break;
		case 'a': rotAngleY += 2; break;
		case 'd': rotAngleY -= 2; break;
		case 'q': rotAngleZ += 2; break;
		case 'e': rotAngleZ -= 2; break;
		case 'i': posX -= 1; break;
		case 'k': posX += 1; break;
		case 32 : rotAngleX=rotAngleY=rotAngleZ=0;posY = 0, posX = 0, posZ = 0; break;
		case 'z' : exit(0);
		default:
		break;
	}glutPostRedisplay();
}

// Fungsi Press Key
void pressKey(int k, int x, int y)
{
	// Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas
 	// Selama tombol ditekan, variabel angle dan move diubah => kamera  bergerak
	switch (k)
	{
		case GLUT_KEY_UP : deltaMove = 1;break;
		case GLUT_KEY_DOWN : deltaMove = -1;break;
		case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
	 }
}

// Release Key
void releaseKey(int key, int x, int y)
{
	// Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
	// Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti
	switch (key)
	{
		case GLUT_KEY_UP : if (deltaMove > 0)
		deltaMove = 0;
		break;

		case GLUT_KEY_DOWN : if (deltaMove < 0)
		deltaMove = 0;
		break;

		case GLUT_KEY_LEFT : if (deltaAngle < 0.0f)
		deltaAngle = 0.0f;
		break;

		case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
		deltaAngle = 0.0f;
		break;

 	}
}

// Fungsi Lightning (Mengaktifkan Pencahayaan)
void lighting(){
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

// Badan Pesawat
void badanP()
{	glColor3f(0.5,0.5,0.5);
    glPushMatrix();
	glTranslatef(-7.0f,12.0f,0.0f);
	glRotated(90, 0, 1, 0);
	gluCylinder(IDquadric, 2.5f, 2.5f, 17.5f, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10.0f,12.0f,0.0f);
	glRotated(53, 0, 1, 0);
	glRotated(55, 0, 1, 1);
	gluCylinder(IDquadric, 2.55f, 1.0f, 8.0f, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-11.8f,10.8f,0.0f);
	glRotated(53, 0, 1, 0);
	glRotated(55, 0, 1, 1);
	gluCylinder(IDquadric, 1.0f, 2.6f, 5.5f, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-11.5f,10.9f,0.0f);
	gluSphere(IDquadric, 1.0f, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(17.5f,13.7f,0.0f);
	gluSphere(IDquadric, 1.0f, 32, 32);
	glPopMatrix();

}

// Membentuk Sayap Dan Ekor 3D
void triangularPrism()
{
    glBegin(GL_QUADS);
        glColor3f(0.1,0.0,0.0);
        glVertex3f(0.5, 0, 0.5);
        glVertex3f(0.5, 0, -0.5);
        glVertex3f(-0.5, 0, -0.5);
        glVertex3f(-0.5, 0, 0.5);
        glVertex3f(0.5,0,-0.5);
        glVertex3f(0.5,1,-0.5);
        glVertex3f(-0.5,1,-0.5);
        glVertex3f(-0.5,0,-0.5);
        glVertex3f(0.5,1,-0.5);
        glVertex3f(-0.5,1,-0.5);
        glVertex3f(-0.5,0,0.5);
        glVertex3f(0.5,0,0.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.4,0.0,0.0);
        glVertex3f(0.5,0,0.5);
        glVertex3f(0.5,1,-0.5);
        glVertex3f(0.5,0,-0.5);
        glVertex3f(-0.5,0,0.5);
        glVertex3f(-0.5,1,-0.5);
        glVertex3f(-0.5,0,-0.5);
    glEnd();
}

// Mengatur Posisi Sayap Kiri
void wingL(){
	glColor3f(0.0,0.2,0.0);
	glPushMatrix();
	glTranslatef(1.0,11.0,0.0);
	glRotated(-90,0,1,0);
	glRotated(-90,0,0,1);
	glScalef(0.5,25.5,5.0);
	triangularPrism();
	glPopMatrix();
}

// Mengatur Posisi Sayap Kanan
void wingR(){
	glColor3f(0.0,0.2,0.0);
	glPushMatrix();
	glTranslatef(1.0,11.0,0.0);
	glRotated(-90,0,1,0);
	glRotated(90,0,0,1);
	glScalef(0.5,25.5,5.0);
	triangularPrism();
	glPopMatrix();
}

// Mengatur Posisi Ekor
void tailP(){
	glPushMatrix();
	glTranslatef(15.0,13.0,0.0);
	glRotated(-90,0,1,0);
	glScalef(0.5,8.0,5.0);
	triangularPrism();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(15.0,13.0,0.0);
	glRotated(-90,0,1,0);
	glRotated(-90,0,0,1);
	glScalef(0.5,8.0,5.0);
	triangularPrism();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(15.0,13.0,0.0);
	glRotated(-90,0,1,0);
	glRotated(90,0,0,1);
	glScalef(0.5,8.0,5.0);
	triangularPrism();
	glPopMatrix();
}

void Grid ()
{
    // Membuat Laut
    glColor3f(0.0f,0.0f,0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-1000,-0.1,1000);
    glVertex3f(-1000,-0.1,-1004);
    glVertex3f(1000,-0.1,-1004);
    glVertex3f(1000,-0.1,1000);
    glEnd();

    // Membuat Matahari

}

// Animasi Pesawat

// Fungsi Display (Menampilkan Output Program)
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (deltaMove)
		moveMeFlat(deltaMove);
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
	}
	glPushMatrix();
		glRotated(rotAngleX+10, 1, 0, 0);
		glRotated(rotAngleY, 0, 1, 0);
		glRotated(rotAngleZ, 0, 0, 1);
		glRotated(-90,0,1,0);
		glPushMatrix();
			int tinggi = 50;
			glTranslatef(0,tinggi/2,-10);
			glPushMatrix();
				glTranslatef(0,buildDown,0);
				glRotated( buildingAngle,1,0,0);
				glTranslatef(0,tinggi/2,0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,buildDown,0);
				glRotated( buildingAngle,0,0,1);
				glTranslatef(0,tinggi/2,20);
			glPopMatrix();
			glTranslatef(0,0,20);
		glPopMatrix();
		Grid();
		glTranslatef(50,15,0);
		glTranslated(posX, posY, posZ);
        glRotated(angleX, 1, 0, 0);
		glPushMatrix();
			glTranslatef(bodyDownX,bodyDownY,0);
			badanP();
			tailP();
		glPopMatrix();
		glTranslatef(wingDownX,wingDownY,0);
		glRotated(-angleWing,0,1,0);
		wingL();
		glRotated(angleWing*2,0,1,0);
		wingR();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

// Memanggil Fungsi Untuk Manampilkan Objek Di Layar
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Pesawat 3D");
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutReshapeFunc(Reshape);
//    glutTimerFunc(50, update, 0);
	lighting();
	init();
	glClearColor(0.0f,0.7f,1.0f,1.0f); //Warna biru muda
	glutMainLoop();
	return(0);
}

