#version 150

//in  vec3 vColor;
//uniform float time;
//uniform float sinAngle;
//uniform float cosAngle;

in  vec3 vPosition;
out vec4 mycolor;
uniform mat3 multipliers;
uniform float random;

void
main()
{
    gl_Position = vec4(vPosition.x * multipliers[0][0] + vPosition.y * multipliers[0][1] + vPosition.z * multipliers[0][2],
                   vPosition.x * multipliers[1][0] + vPosition.y * multipliers[1][1] + vPosition.z * multipliers[1][2],
                   vPosition.x * multipliers[2][0] + vPosition.y * multipliers[2][1] + ((vPosition.z * multipliers[2][2])+1),
                   1.0);

    mycolor = vec4(gl_Position.x, gl_Position.y, gl_Position.z - 0.2, 1.0 );

}
