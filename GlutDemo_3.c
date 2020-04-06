#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

// vertex array object (declared global for simplicity)
GLuint vao;

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw something using modern OpenGL
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 24);

    glutSwapBuffers();
}

static void keyboard(unsigned char key, int x, int y) {
    printf("Pressed %c key\n", key);

    if(key == 'q') {
        exit(0);
    }
}

// Compile a shader
GLuint compile_shader(const char *shader_src, GLenum shaderType) {
    // Compile the shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shader_src, NULL);
    glCompileShader(shader);
    // Check the result of the compilation
    GLint test;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
    if(!test) {
        printf("Shader compilation failed with this message:\n");
        char compilation_log[512];
        glGetShaderInfoLog(shader, 512, NULL, &compilation_log[0]);
        printf("%s\n", compilation_log);
        exit(-1);
    }
    return shader;
}


// Create a program from two shaders
GLuint create_program(const char *src_vert_shader, const char *src_frag_shader) {
    // Compile the vertex and fragment shaders
    GLuint vertexShader = compile_shader(src_vert_shader, GL_VERTEX_SHADER);
    GLuint fragmentShader = compile_shader(src_frag_shader, GL_FRAGMENT_SHADER);

    // Attach the above shader to a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Flag the shaders for deletion
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Link and use the program
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    return shaderProgram;
}

void initialize(void) {
    // Use a Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // 8 triangles to be rendered
    GLfloat vertices_position[48] = {
        0.0, 0.0,
        0.5, 0.0,
        0.5, 0.5,

        0.0, 0.0,
        0.5, 0.5,
        0.0, 0.5,

        0.0, 0.0,
        0.0, 0.5,
        -0.5, 0.5,

        0.0, 0.0,
        -0.5, 0.5,
        -0.5, 0.0,

        0.0, 0.0,
        -0.5, 0.0,
        -0.5, -0.5,

        0.0, 0.0,
        -0.5, -0.5,
        0.0, -0.5,

        0.0, 0.0,
        0.0, -0.5,
        0.5, -0.5,

        0.0, 0.0,
        0.5, -0.5,
        0.5, 0.0
    };

    // Create a Vector Buffer Object that will store the vertices on video memory
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Allocate space and upload the data from CPU to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);

    // Hard coded (for simplicity) vertex shader source
    const char *src_vert_shader = " \
        #version 150\n \
        in vec4 position; \
        void main() { \
            gl_Position = position; \
        } \
    ";

    // Hard coded (for simplicity) fragment shader source
    const char *src_frag_shader = " \
        #version 150\n \
        out vec4 out_color; \
        void main() { \
            out_color = vec4(1.0, 1.0, 1.0, 1.0); \
        } \
    ";

    GLuint shaderProgram = create_program(src_vert_shader, src_frag_shader);

    // Get the location of the attributes that enters in the vertex shader
    GLint position_attribute = glGetAttribLocation(shaderProgram, "position");

    // Specify how the data for position can be accessed
    glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Enable the attribute
    glEnableVertexAttribArray(position_attribute);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Request a modern OpenGL profile
    glutInitContextVersion(3,3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    // Create a window with an OpenGL context
    glutCreateWindow("Glut Demo");

    // Print the default OpenGL version
    printf("OpenGL version = %s\n", glGetString(GL_VERSION));

    // Initialize GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        printf("Error in GLEW initialization = %s\n", glewGetErrorString(err));
    }

    // Initialize the data to be rendered
    initialize();

    // Register GLUT callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // Clear the screen with red
    glClearColor(1.0, 0.0, 0.0, 1.0);

    glutMainLoop();
}
