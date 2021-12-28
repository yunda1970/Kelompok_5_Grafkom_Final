// File Header
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PI 3.14

// Fungsi Init (Untuk Membuat Tempat Menggambar)
void init(void)
{
	glEnable (GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	IDquadric=gluNewQuadric(); // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(IDquadric, GLU_SMOOTH); // Create Smooth Normals ( NEW )
	gluQuadricTexture(IDquadric, GL_TRUE); // Create Texture Coords ( NEW )
}

// Variabel Kamera (Menentukan Posisi Awal Kamera)
float angle=0.0, deltaAngle = 0.0, ratio;
float x=-0.0f,y=1.75f,z=15.0f; // posisi awal kamera
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
// Fungsi moveMeFlat (Pergerakkan Kamera Maju/Mundur)
// Fungsi Keyboard
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
	// Fungsi mengaktifkan pencahayaan
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
// Membentuk Sayap Dan Ekor 3D
// Mengatur Posisi Sayap Kiri
// Mengatur Posisi Sayap Kanan
// Mengatur Posisi Ekor
// Animasi Pesawat
// Fungsi Display (Menampilkan Output Program)
// Memanggil Fungsi Untuk Manampilkan Objek Di Layar
