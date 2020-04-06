#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw something using modern OpenGL
    // ...

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

    // Use a modern OpenGL profile
    glutInitContextVersion(3,3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    // Create a window with an OpenGL context
    glutCreateWindow("Glut Demo");

    // Check the default OpenGL version
    printf("OpenGL version = %s\n", glGetString(GL_VERSION));

    // Initialize GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        printf("Error in GLEW initialization = %s\n", glewGetErrorString(err));
    }

    // Register GLUT callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glClearColor(1.0, 0.0, 0.0, 1.0);

    glutMainLoop();
}
