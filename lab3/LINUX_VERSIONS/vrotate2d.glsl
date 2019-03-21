#version 150

in  vec3 vPosition;
in  vec3 vColor;
out vec4 color;
uniform float time;

void
main()
{
    //gl_Position = vec4(vPosition, 1.0);

    float angle = 0.01 * time;
    gl_Position = vec4(vPosition.x * cos(angle) - vPosition.y * sin(angle),
                      vPosition.x * sin(angle) + vPosition.y * cos(angle),
                      0.0, 1.0);
    color = vec4( vColor, 1.0 );
}
