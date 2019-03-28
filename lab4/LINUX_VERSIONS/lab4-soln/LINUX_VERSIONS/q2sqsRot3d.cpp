#include "Angel.h"

using namespace std;

const int NumTriangles = 2;
const int NumVertices  = 3 * NumTriangles;

vec3 points[NumVertices] = {
    vec3( -0.5, -0.5, 0.0 ), vec3(  0.5, -0.5, 0.0 ), vec3( -0.5, 0.5, 0.0 ),
    vec3(  0.5,  0.5, 0.0 ), vec3( -0.5,  0.5, 0.0 ), vec3( 0.5, -0.5, 0.0 )
}; 

vec3 colors[NumVertices] = {
    vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 1.0, 0.0),
    vec3(0.0, 1.0, 1.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0), 
};

GLuint xyzMultipliers; 

//----------------------------------------------------------------------------

void init( void )
{
    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // First, we create an empty buffer of the size we need by passing
    //   a NULL pointer for the data values
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
                  NULL, GL_STATIC_DRAW );

    // Next, we load the real data in parts.  We need to specify the
    //   correct byte offset for placing the color data after the point
    //   data in the buffer.  Conveniently, the byte offset we need is
    //   the same as the size (in bytes) of the points array, which is
    //   returned from "sizeof(points)".
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "v-xyz.glsl", "fpassthru.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader    
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    xyzMultipliers = glGetUniformLocation(program, "xyzMultipliers");

    //glEnable( GL_DEPTH_TEST );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* white background */
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
 
    float angle = 0.001 * glutGet(GLUT_ELAPSED_TIME);
        
    mat3 xzRotateMultipliers = mat3( vec3(cos(angle),  0.0, sin(angle)),
                                     vec3(0.0,         1.0,        0.0),
                                     vec3(-sin(angle), 0.0, cos(angle)) );
    glUniformMatrix3fv( xyzMultipliers, 1, GL_TRUE, xzRotateMultipliers );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    mat3 xyRotateMultipliers = mat3( vec3(cos(angle), -sin(angle), 0.0),
                                     vec3(sin(angle),  cos(angle), 0.0),
                                     vec3(0.0,        0.0,         1.0) );
    glUniformMatrix3fv( xyzMultipliers, 1, GL_TRUE, xyRotateMultipliers );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    mat3 yzRotateMultipliers = mat3( vec3(1.0,        0.0,         0.0),
                                     vec3(0.0, cos(angle), -sin(angle)),
                                     vec3(0.0, sin(angle),  cos(angle)) );
    glUniformMatrix3fv( xyzMultipliers, 1, GL_TRUE, yzRotateMultipliers );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

void idle( void )
{
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

int main( int argc, char **argv )
{
    glutInit( &argc, argv );

    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );

    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Simple GLSL example" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );

    glutMainLoop();
    return 0;
}
