/////////////////////////////////////////////////// Bagas ///////////////////////////////////////////////////////////////

#include <GL/glut.h>
#include <cmath>

// Variabel kamera
float posisi_kamera_x = 0.0f, posisi_kamera_y = 2.0f, posisi_kamera_z = 10.0f; // Posisi kamera
float sudut_kamera_yaw = 9.0f, sudut_kamera_pitch = 0.5f; // Sudut kamera

// Variabel transformasi makanan
float skala_makanan = 1.0f;

// Variabel animasi api
float ukuran_api = 0.5f;
bool api_membesar = true;

// Variabel mouse
bool mouse_aktif = false;
int posisi_mouse_terakhir_x, posisi_mouse_terakhir_y;

// Variabel untuk mengatur tampilan garis kartesius
bool gambar_sumbu_kartesius = true;

void batasiPosisiKamera() {
    if (posisi_kamera_x > 14.0f) posisi_kamera_x = 14.0f;
    if (posisi_kamera_x < -14.0f) posisi_kamera_x = -14.0f;
    if (posisi_kamera_z > 14.0f) posisi_kamera_z = 14.0f;
    if (posisi_kamera_z < -14.0f) posisi_kamera_z = -14.0f;
}

void gambarTulisan(const char* teks, float x, float y, float z) {
    glRasterPos3f(x, y, z);
    while (*teks) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *teks);
        teks++;
    }
}

void gambarRuangan() {
    glBegin(GL_QUADS);

    // Lantai 
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-15.0, -2.0, -15.0);
    glVertex3f(15.0, -2.0, -15.0);
    glVertex3f(15.0, -2.0, 15.0);
    glVertex3f(-15.0, -2.0, 15.0);

    // Atap 
    glColor3f(0.3, 0.2, 0.3);
    glVertex3f(-15.0, 10.0, -15.0);
    glVertex3f(15.0, 10.0, -15.0);
    glVertex3f(15.0, 10.0, 15.0);
    glVertex3f(-15.0, 10.0, 15.0);

    // belakang 
    glColor3f(0.6, 0.9, 0.6);
    glVertex3f(-15.0, -2.0, -15.0);
    glVertex3f(15.0, -2.0, -15.0);
    glVertex3f(15.0, 10.0, -15.0);
    glVertex3f(-15.0, 10.0, -15.0);

    // kiri 
    glColor3f(0.6, 0.9, 0.6);
    glVertex3f(-15.0, -2.0, -15.0);
    glVertex3f(-15.0, -2.0, 15.0);
    glVertex3f(-15.0, 10.0, 15.0);
    glVertex3f(-15.0, 10.0, -15.0);

    // kanan
    glColor3f(0.6, 0.9, 0.6);
    glVertex3f(15.0, -2.0, -15.0);
    glVertex3f(15.0, -2.0, 15.0);
    glVertex3f(15.0, 10.0, 15.0);
    glVertex3f(15.0, 10.0, -15.0);

    glEnd();
   
    glColor3f(1.0, 1.0, 1.0);  
    gambarTulisan("<<<< RESTORAN KELOMPOK 10 >>>>", 6.0f, 5.0f, 15.0f);  
}

void gambarMeja(float x, float y, float z, float panjang, float lebar, float tinggi, float rotasi) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotasi, 0.0f, 9.0f, 0.0f);
    glScalef(panjang, tinggi, lebar);

    glColor3f(0.5, 0.35, 0.05); // Warna kayu
    glutSolidCube(1.5);

    glPopMatrix();
}

void gambarApi(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3f(1.0, 0.5, 0.0);
    glutSolidSphere(ukuran_api, 20, 20);

    glPopMatrix();
}

void gambarKompor(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    // Badan kompor
    glColor3f(0.2, 0.2, 0.2);
    glScalef(2.0, 0.5, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();
    // Api
    gambarApi(x, y + 0.5, z);
}

void gambarMakananDiMeja(float posisi_meja_x, float posisi_meja_y, float posisi_meja_z) {
    glPushMatrix();
    glTranslatef(posisi_meja_x, posisi_meja_y + 0.5, posisi_meja_z);
    glScalef(skala_makanan, skala_makanan, skala_makanan);

    // Piring pertama
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); 
    glTranslatef(0.0f, -0.3f, -6.0f);
    glScalef(1.5f, 0.1f, 1.5f);
    glutSolidSphere(0.8, 50, 50); 
    glPopMatrix();
    // Apel 
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); 
    glTranslatef(0.0f, 0.2f, -6.0f); 
    glutSolidSphere(0.4, 30, 30);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glTranslatef(0.0f, 0.4f, 0.0f);
    glutSolidCone(0.1, 0.2, 30, 30);
    glPopMatrix();

    // Piring kedua
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); 
    glTranslatef(0.0f, -0.3f, -2.0f);
    glScalef(1.5f, 0.1f, 1.5f);
    glutSolidSphere(0.8, 50, 50); 
    glPopMatrix();
    // Pizza 
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.6f); 
    glTranslatef(0.0f, 0.2f, -2.0f); 
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidSphere(0.6, 30, 30);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glTranslatef(0.0f, 0.1f, 0.0f);
    glutSolidSphere(0.5, 30, 30);
    glColor3f(1.0f, 1.0f, 0.0f); 
    glTranslatef(0.0f, 0.1f, 0.0f);
    glutSolidSphere(0.4, 30, 30);
    glPopMatrix();

    // Piring ketiga
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); 
    glTranslatef(0.0f, -0.3f, 2.0f);
    glScalef(1.5f, 0.1f, 1.5f);
    glutSolidSphere(0.8, 50, 50); 
    glPopMatrix();
    // kueh
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.6f); 
    glTranslatef(0.0f, 0.2f, 2.0f); 
    glScalef(0.8f, 0.5f, 0.8f);
    glutSolidCube(0.6);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glTranslatef(0.0f, 0.4f, 0.0f);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();

    // Piring keempat
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); 
    glTranslatef(0.0f, -0.3f, 6.0f);
    glScalef(1.5f, 0.1f, 1.5f);
    glutSolidSphere(0.8, 50, 50); 
    glPopMatrix();
    // Burger 
    glPushMatrix();
    glColor3f(0.8f, 0.5f, 0.2f); 
    glTranslatef(0.0f, 0.2f, 6.0f); 
    glutSolidSphere(0.4, 30, 30);
    glColor3f(0.5f, 0.25f, 0.1f); 
    glTranslatef(0.0f, 0.2f, 0.0f);
    glutSolidSphere(0.35, 30, 30);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glTranslatef(0.0f, 0.2f, 0.0f);
    glutSolidSphere(0.4, 30, 30);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glTranslatef(0.0f, 0.2f, 0.0f);
    glutSolidSphere(0.35, 30, 30);
    glColor3f(0.8f, 0.5f, 0.2f); 
    glTranslatef(0.0f, 0.2f, 0.0f);
    glutSolidSphere(0.4, 30, 30);
    glPopMatrix();

    // Piring kelima
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); 
    glTranslatef(0.0f, -0.3f, 10.0f);
    glScalef(1.5f, 0.1f, 1.5f);
    glutSolidSphere(0.8, 50, 50); 
    glPopMatrix();
    // Minuman 
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); 
    glTranslatef(0.0f, 0.5f, 10.0f); 
    glScalef(0.5f, 0.8f, 0.5f);
    glutSolidCube(0.6); 
    glColor3f(1.0f, 1.0f, 0.0f); 
    glTranslatef(0.0f, 0.5f, 0.0f);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.05, 0.2, 30, 30);
    glPopMatrix();

    glPopMatrix();
}
//=========================================================================================================================//

/////////////////////////////////////////////////// Romy ///////////////////////////////////////////////////////////////

void aturKamera() {
    float arah_kamera_x = sin(sudut_kamera_yaw);
    float arah_kamera_y = sin(sudut_kamera_pitch);
    float arah_kamera_z = -cos(sudut_kamera_yaw);

    gluLookAt(posisi_kamera_x, posisi_kamera_y, posisi_kamera_z,
              posisi_kamera_x + arah_kamera_x, posisi_kamera_y + arah_kamera_y, posisi_kamera_z + arah_kamera_z,
              0.0, 10.0, 0.0);
}

void gerakanMouse(int x, int y) {
    if (mouse_aktif) {
        float sensitivitas = 0.003f;

        sudut_kamera_yaw += (x - posisi_mouse_terakhir_x) * sensitivitas;
        sudut_kamera_pitch += (y - posisi_mouse_terakhir_y) * sensitivitas;

        if (sudut_kamera_pitch > 1.5f) sudut_kamera_pitch = 1.5f;
        if (sudut_kamera_pitch < -1.5f) sudut_kamera_pitch = -1.5f;

        posisi_mouse_terakhir_x = x;
        posisi_mouse_terakhir_y = y;

        glutPostRedisplay();
    }
}

void klikMouse(int tombol, int state, int x, int y) {
    if (tombol == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouse_aktif = true;
        posisi_mouse_terakhir_x = x;
        posisi_mouse_terakhir_y = y;
    } else if (tombol == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mouse_aktif = false;
    }
}
//=========================================================================================================================//

/////////////////////////////////////////////////// FIRMAN ///////////////////////////////////////////////////////////////
void gambarSumbu() {//jadi ini teh buat menggambar sumbu kordinat
    glBegin(GL_LINES);
    // Sumbu X 
    glColor3f(1.0, 0.0, 0.0); //merah
    glVertex3f(-15.0, 0.0, 0.0); 
    glVertex3f(15.0, 0.0, 0.0);/
    // Sumbu Y 
    glColor3f(0.0, 1.0, 0.0); //hejo
    glVertex3f(0.0, -10.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    // Sumbu Z 
    glColor3f(0.0, 0.0, 1.0); //biru
    glVertex3f(0.0, 0.0, -15.0);// titik
    glVertex3f(0.0, 0.0, 15.0);
    glEnd();
}
//=========================================================================================================================//


/////////////////////////////////////////////////// Romy ///////////////////////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y) {
    float kecepatan_gerak = 0.5f;
    float arah_x = sin(sudut_kamera_yaw);
    float arah_z = -cos(sudut_kamera_yaw);
    switch (key) {
        case 'w':
            posisi_kamera_x += arah_x * kecepatan_gerak;
            posisi_kamera_z += arah_z * kecepatan_gerak;
            break;
        case 's':
            posisi_kamera_x -= arah_x * kecepatan_gerak;
            posisi_kamera_z -= arah_z * kecepatan_gerak;
            break;
        case '+':
            skala_makanan += 0.1f;
            break;
        case '-':
            if (skala_makanan > 0.2f) skala_makanan -= 0.1f;
            break;
        case 'c': 
            gambar_sumbu_kartesius = !gambar_sumbu_kartesius;
            break;
        case 27: // ESC
            exit(0);
    }

    batasiPosisiKamera();
    glutPostRedisplay();
}
//=========================================================================================================================//

/////////////////////////////////////////////////// Bagas ///////////////////////////////////////////////////////////////
void animasiApi(int value) {
    if (api_membesar) {
        ukuran_api += 0.05f;
        if (ukuran_api >= 0.8f) api_membesar = false;
    } else {
        ukuran_api -= 0.05f;
        if (ukuran_api <= 0.5f) api_membesar = true;
    }
    glutPostRedisplay();
    glutTimerFunc(100, animasiApi, 0); //mengatur animasi atau tindakan berulang
}
//=========================================================================================================================//


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gambarKarpet(float x, float z, float panjang, float lebar) {
    glPushMatrix();
    glTranslatef(x, -2.0f, z);

    glColor3f(5.0, 0.0, 0.0); //warna
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); 
    glScalef(panjang, 0.05f, lebar); 
    glutSolidCube(1.0);// warna bawah 
    glPopMatrix();
}
// rendering
void tampilan() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    aturKamera();
    gambarRuangan();
    if (gambar_sumbu_kartesius) {
        gambarSumbu();
    }
    // Meja kanan
    gambarMeja(10.0f, -1.5f, -5.0f, 15.0f, 2.5f, 0.5f, 90.0f);
    gambarMakananDiMeja(10.0f, -1.0f, -5.0f);    
    gambarKarpet(10.0f, -5.0f, 22.0f, 10.5f); 
    // Meja kiri
    gambarMeja(-10.0f, -1.5f, -5.0f, 15.0f, 2.5f, 0.5f, 90.0f);
    gambarMakananDiMeja(-10.0f, -1.0f, -5.0f);
    gambarKarpet(-10.0f, -5.0f, 22.0f, 10.5f); 
    // Meja belakang 
    gambarMeja(0.0f, -1.5f, -13.0f, 3.0f, 3.0f, 0.5f, 0.0f);
    gambarKompor(0.0f, -1.0f, -13.0f);
    
    glutSwapBuffers();
}
//=========================================================================================================================//


/////////////////////////////////////////////////// Firman ///////////////////////////////////////////////////////////////
void inisialisasi() {
    glEnable(GL_DEPTH_TEST);//
    glEnable(GL_LIGHTING);// 
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);// Kanggo ngasih warna.
    glClearColor(0.2, 0.2, 0.2, 1.0);// Menentukan warna latar belakang 

    // posisi cahaya
    GLfloat posisi_cahaya[] = {0.0f, 0.0f, -14.0f, 1.0f};
    GLfloat cahaya_diffuse[] = {1.0f, 0.5f, 0.0f, 1.0f};	
    GLfloat cahaya_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};//	cahaya ruangan
    GLfloat cahaya_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};//	(highlight) yang dipantulkan dari permukaan mengkilap.

    glLightfv(GL_LIGHT0, GL_POSITION, posisi_cahaya);// posisi cahaya
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cahaya_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, cahaya_ambient);//menentukan warna cahaya
    glLightfv(GL_LIGHT0, GL_SPECULAR, cahaya_specular); 
}

// mengatur proyeksi
void reshape(int w, int h) {
    glViewport(0, 0, w, h);//Ini memastikan bahwa viewport mencakup seluruh jendela
    glMatrixMode(GL_PROJECTION);//memberi tahu OpenGL bahwa perubahan berikutnya akan diterapkan pada matriks proyeksi.
    glLoadIdentity();//Mengatur matriks aktif menjadi matriks identitas (default).
    gluPerspective(45.0, (float)w / h, 1.0, 100.0);//objek yang lebih jauh dari kamera terlihat lebih kecil
    glMatrixMode(GL_MODELVIEW);//Mengembalikan matriks aktif ke mode Model-View.
}
//=========================================================================================================================//


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Restoran Kelompok - 10");

    glutDisplayFunc(tampilan);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(klikMouse);
    glutMotionFunc(gerakanMouse);

    inisialisasi();
    animasiApi(0);

    glutMainLoop();
    return 0;
}
