#include <stdio.h>
#include <stdlib.h>

#include <GL/freeglut.h>

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw a rectangle using the fixed pipeline functionality
    // THIS WILL NOT WORK WITH THE CORE OPENGL PROFILE
    glColor3f(0.5f, 1.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    glutSwapBuffers();
}

static void keyboard(unsigned char key, int x, int y) {
    printf("Pressed %c key\n", key);
    if(key == 'q') {
        exit(0);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Create a window with an OpenGL context
    glutCreateWindow("Glut Demo");

    // Check the default OpenGL version
    printf("OpenGL version = %s\n", glGetString(GL_VERSION));

    // Register GLUT callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glClearColor(1.0, 0.0, 0.0, 1.0);

    glutMainLoop();
}
