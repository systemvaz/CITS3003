#version 150

//in  vec3 vColor;
//uniform float time;
//uniform float sinAngle;
//uniform float cosAngle;

in  vec2 vPosition;
out vec4 mycolor;
uniform mat2 multipliers;
uniform float random;

void
main()
{
    gl_Position = vec4(vPosition.x * multipliers[0][0] + vPosition.y * multipliers[0][1],
                   vPosition.x * multipliers[1][0] + vPosition.y * multipliers[1][1],
                    0.0, 1.0);

    mycolor = vec4(gl_Position.x, gl_Position.y, gl_Position.z, 1.0 );

    //gl_Position = vec4(vPosition, 1.0);

    //float angle = 0.01 * time;

    //gl_Position = vec4(vPosition.x * cos(angle) - vPosition.y * sin(angle),
    //                  vPosition.x * sin(angle) + vPosition.y * cos(angle),
    //                  0.0, 1.0);
}
