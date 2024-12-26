#include <GL/glut.h>
#include <cmath>

// Variabel untuk kontrol kamera
float cameraAngleX = 5.0f; 
float cameraAngleY = 1.0f;
float cameraDistance = 70.0f; 

// Variabel untuk kontrol pencahayaan
float lightPosX = 10.0f;
float lightPosY = 10.0f;
float lightPosZ = 10.0f;
bool showLightCube = true; // Status untuk menampilkan kubus penanda cahaya

// posisi awan pertama
float cloud1PosX = 20.0f;
float cloud1PosY = 24.0f;
float cloud1PosZ = -29.0f;

// posisi awan kedua
float cloud2PosX = -20.0f;
float cloud2PosY = 24.0f;
float cloud2PosZ = -29.0f;

int lastMouseX, lastMouseY; // Posisi terakhir kursor mouse
bool isDragging = false; // Status apakah mouse sedang digunakan
bool showAxes = false; // Status untuk menampilkan garis kartesius

void init() {
    glClearColor(0.5, 0.5, 0.5, 1.0); // Warna latar belakang abu-abu
    glEnable(GL_DEPTH_TEST);          // Mengaktifkan depth testing
    glEnable(GL_LIGHTING);            // Aktifkan pencahayaan
    glEnable(GL_LIGHT0);              // Aktifkan sumber cahaya 0
    glEnable(GL_NORMALIZE);           // Normalisasi norma permukaan

    // Atur sumber cahaya
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
}

void drawAxes() {
    glDisable(GL_LIGHTING); // Matikan pencahayaan untuk sumbu
    glBegin(GL_LINES);

    // Sumbu X (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    // Sumbu Y (hijau)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    // Sumbu Z (biru)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();
    glEnable(GL_LIGHTING); // Aktifkan kembali pencahayaan
}

void drawLight() { 
    glDisable(GL_LIGHTING); // Matikan pencahayaan untuk bola matahari
    glPushMatrix();

    // Posisikan bola matahari di lokasi cahaya
    glTranslatef(lightPosX, lightPosY, lightPosZ);

    // Membuat efek warna gradasi dari oranye ke kuning
    int slices = 50; // Jumlah potongan bola
    int stacks = 50; // Jumlah tumpukan bola
    float step = 1.0f / stacks; // Langkah gradasi warna berdasarkan tumpukan

    for (int i = 0; i < stacks; i++) {
        float t = i * step;        // Fraksi warna dari 0.0 ke 1.0
        float nextT = (i + 1) * step;

        float r = 1.0f;           // Komponen merah (selalu penuh untuk oranye dan kuning)
        float g = 0.5f + 0.5f * t; // Komponen hijau (bertambah untuk gradasi ke kuning)
        float b = 0.0f;           // Komponen biru (nol untuk oranye ke kuning)

        glColor3f(r, g, b);       // Atur warna untuk tumpukan saat ini
        glBegin(GL_QUAD_STRIP);   // Mulai menggambar strip quad

        for (int j = 0; j <= slices; j++) {
            float angle = 2.0f * M_PI * j / slices; // Sudut untuk lingkaran horizontal
            float x = cos(angle);
            float y = sin(angle);

            // Posisi untuk tumpukan saat ini dan berikutnya
            float z1 = cos(M_PI * t);
            float z2 = cos(M_PI * nextT);

            glVertex3f(5.0f * x * sin(M_PI * t), 5.0f * y * sin(M_PI * t), 5.0f * z1);
            glVertex3f(5.0f * x * sin(M_PI * nextT), 5.0f * y * sin(M_PI * nextT), 5.0f * z2);
        }
        glEnd(); // Selesai menggambar strip quad
    }

    glPopMatrix();
    glEnable(GL_LIGHTING); // Aktifkan kembali pencahayaan
}

void drawAwan1() {//by naufal
 	glDisable(GL_LIGHTING); 
    glPushMatrix();

    // Posisikan awan
    glTranslatef(cloud1PosX, cloud1PosY, cloud1PosZ);

    // Gambar tiga sphere untuk membentuk awan
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih untuk awan
    glutSolidSphere(4.0, 20, 20); // Sphere pertama

    glPushMatrix();
    glTranslatef(5.0f, 0.0f, 0.0f);
    glutSolidSphere(3.0, 20, 20); // Sphere kedua
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 0.0f);
    glutSolidSphere(3.0f, 20, 20); // Sphere ketiga
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
    
    glPopMatrix();

}

void drawAwan2() {//by naufal
	glDisable(GL_LIGHTING); 
    glPushMatrix();

    // Posisikan awan
    glTranslatef(cloud2PosX, cloud2PosY, cloud2PosZ);
    

    // Gambar tiga sphere untuk membentuk awan
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih untuk awan
    glutSolidSphere(4.0, 20, 20); // Sphere pertama

    glPushMatrix();
    glTranslatef(5.0f, 0.0f, 0.0f);
    glutSolidSphere(3.0, 20, 20); // Sphere kedua
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 0.0f);
    glutSolidSphere(3.0f, 20, 20); // Sphere ketiga
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
    
    glPopMatrix();

}

void drawCube() {  //by naufal
    glPushMatrix();
    glTranslatef(0.0f, -15.0f, 0.0f); // Posisikan kubus di bawah oktahedron
    glScalef(-70.0f, 30.0f, 80.0f);    // Sesuaikan ukuran kubus
    glColor3f(0.0f, 0.0f, 1.0f);     // Warna biru untuk kubus
    glutSolidCube(1.0f);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Atur kamera
    float cameraPosX = cameraDistance * sinf(cameraAngleX) * cosf(cameraAngleY);
    float cameraPosY = cameraDistance * sinf(cameraAngleY);
    float cameraPosZ = cameraDistance * cosf(cameraAngleX) * cosf(cameraAngleY);
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ,  // Posisi kamera
              0.0, 0.0, 0.0,                      // Titik fokus
              0.0, 1.0, 0.0);                     // Arah atas

    // Atur posisi pencahayaan
    GLfloat lightPosition[] = { lightPosX, lightPosY, lightPosZ, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Tambahkan material
    GLfloat materialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Warna putih
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

    glPushMatrix();
    glScalef(20.0f, 20.0f, 20.0f); // Perbesar oktahedron
    glColor3f(1.0f, 1.0f, 1.0f);   // Warna putih untuk oktahedron
    glutSolidOctahedron();
    glPopMatrix();

    drawCube(); // pemanggilan function cube

    drawAwan1(); // Panggil fungsi untuk menggambar awan
	drawAwan2();

    if (showAxes) {
        drawAxes();
    }

    if (showLightCube) {
        drawLight();
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi untuk menangani pergerakan mouse
void mouseMotion(int x, int y) {
    if (isDragging) {
        // Hitung perubahan posisi mouse
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;

        // Perbarui sudut kamera berdasarkan perubahan mouse
        cameraAngleX += dx * 0.005f;
        cameraAngleY += dy * 0.005f;

        // Batasi sudut kamera agar tidak melebihi batas
        if (cameraAngleY > M_PI / 2.0f) cameraAngleY = M_PI / 2.0f;
        if (cameraAngleY < -M_PI / 2.0f) cameraAngleY = -M_PI / 2.0f;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay(); // Render ulang
    }
}

// Fungsi untuk menangani klik mouse
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        } else if (state == GLUT_UP) {
            isDragging = false;
        }
    }
}

// Fungsi untuk menangani input keyboard
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC
        exit(0);
    } else if (key == 'c' || key == 'C') { // Tombol untuk menampilkan garis kartesius
        showAxes = !showAxes;
        glutPostRedisplay();
    } else if (key == 'w' || key == 'W') { // Gerakkan cahaya ke atas
        lightPosY += 1.0f;
        glutPostRedisplay();
    } else if (key == 's' || key == 'S') { // Gerakkan cahaya ke bawah
        lightPosY -= 1.0f;
        glutPostRedisplay();
    } else if (key == 'a' || key == 'A') { // Gerakkan cahaya ke kiri
        lightPosX -= 1.0f;
        glutPostRedisplay();
    } else if (key == 'd' || key == 'D') { // Gerakkan cahaya ke kanan
        lightPosX += 1.0f;
        glutPostRedisplay();
    } else if (key == 'q' || key == 'Q') { // Gerakkan cahaya ke depan
        lightPosZ += 1.0f;
        glutPostRedisplay();
    } else if (key == 'e' || key == 'E') { // Gerakkan cahaya ke belakang
        lightPosZ -= 1.0f;
        glutPostRedisplay();
    } else if (key == 'l' || key == 'L') { // Tombol untuk menampilkan kubus penanda cahaya
        showLightCube = !showLightCube;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("PYRAMID");
    glutFullScreen();	
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
