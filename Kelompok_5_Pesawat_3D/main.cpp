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
// Variabel Pencahayaan (Inisialisasi Awal)
// Fungsi Reshape (Mempertahankan Bentuk Gambar)
// Fungsi OrientMe (Pergerakkan Kamera Kanan/Kiri)
// Fungsi moveMeFlat (Pergerakkan Kamera Maju/Mundur)
// Fungsi Keyboard
// Fungsi Press Key
// Release Key
// Fungsi Lightning (Mengaktifkan Pencahayaan)
// Badan Pesawat
// Membentuk Sayap Dan Ekor 3D
// Mengatur Posisi Sayap Kiri
// Mengatur Posisi Sayap Kanan
// Mengatur Posisi Ekor
// Animasi Pesawat
// Fungsi Display (Menampilkan Output Program)
// Memanggil Fungsi Untuk Manampilkan Objek Di Layar
