#version 150

in  vec3 vPosition;
out vec4 mycolor;
uniform mat3 multipliers;

void
main()
{
    gl_Position = vec4(multipliers * vPosition, 1.0);

    mycolor = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0 );
    //mycolor = vec4(gl_Position.x, gl_Position.y, gl_Position.z + 0.3, 1.0 );
}
