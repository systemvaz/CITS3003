// Two-Dimensional Sierpinski Gasket
// Generated using randomly selected vertices and bisection

#include "Angel.h"

const int NumPoints = 30000;
GLint timeParam, cosParam, sinParam;

//----------------------------------------------------------------------------

void
init( void )
{
    vec2 points[NumPoints];

    // Specifiy the vertices of a triangle
    vec2 vertices[3] =
    {
        vec2( -1.0, -1.0 ), vec2( 0.0, 1.0 ), vec2( 1.0, -1.0 )
    };

    // Select an arbitrary initial point inside of the triangle
    points[0] = vec2( 0.25, 0.50 );

    // compute and store N-1 new points
    for ( int i = 1; i < NumPoints; ++i )
    {
        int j = rand() % 3;   // pick a vertex at random

        // Compute the point halfway between the selected vertex
        //   and the previous point
        points[i] = ( points[i - 1] + vertices[j] ) / 2.0;

        // if (length(points[i]) > 1)
        // {
        //   i--;
        // }
    }

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vrotate2dq2.glsl", "fshader21.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    //GLuint timeParam = glGetUniformLocation(program, "time");
    cosParam = glGetUniformLocation(program, "cosAngle");
    sinParam = glGetUniformLocation(program, "sinAngle");

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}


void idle(void)
{
  glutPostRedisplay();
}
//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    //glUniform1f(timeParam, glutGet(GLUT_ELAPSED_TIME));
    glUniform1f(cosParam, cos(glutGet(GLUT_ELAPSED_TIME) * 0.01));
    glUniform1f(sinParam, sin(glutGet(GLUT_ELAPSED_TIME) * 0.01));
    glDrawArrays( GL_POINTS, 0, NumPoints );    // draw the points
    //glFlush();
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );

    // If you are using freeglut, the next two lines will check if
    // the code is truly 3.2. Otherwise, comment them out

    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "Sierpinski Gasket" );

    //glewInit();

    init();

    glutDisplayFunc( display );
    glutIdleFunc(idle);
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
