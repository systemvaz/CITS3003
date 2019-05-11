attribute vec3 vPosition;
attribute vec2 vTexCoord;
attribute vec3 vNormal;

uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform mat4 Projection;

varying vec2 texCoord;
varying vec3 pos, Lvec, N;

void main()
{
    vec4 vpos = vec4(vPosition, 1.0);

    // Transform vertex position into eye coordinates
    pos = (ModelView * vpos).xyz;

    // The vector to the light from the vertex
    Lvec = LightPosition.xyz - pos;

    // Transform vertex normal into eye coordinates (assumes scaling
    // is uniform across dimensions)
    N = normalize( (ModelView*vec4(vNormal, 0.0)).xyz );

    gl_Position = Projection * ModelView * vpos;
    texCoord = vTexCoord;
}
