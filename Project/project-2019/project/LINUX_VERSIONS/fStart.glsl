varying vec3 pos;
varying vec3 Lvec;
varying vec3 N;
varying vec2 texCoord;  // The third coordinate is always 0.0 and is discarded

uniform vec3 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;
uniform float Shininess;
uniform sampler2D texture;

vec4 color;

void main()
{
    // Unit direction vectors for Blinn-Phong shading calculation
    vec3 L = normalize( Lvec );   // Direction to the light source
    vec3 E = normalize( -pos );   // Direction to the eye/camera
    vec3 H = normalize( L + E );  // Halfway vector

    // Compute terms in the illumination equation
    vec3 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 );
    vec3  diffuse = Kd*DiffuseProduct;

    vec3 white = vec3(1.0, 1.0, 1.0);
    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec3  specular = Ks * white * SpecularProduct;

    if (dot(L, N) < 0.0 )
    {
      specular = vec3(0.0, 0.0, 0.0);
    }

    // globalAmbient is independent of distance from the light source
    vec3 globalAmbient = vec3(0.1, 0.1, 0.1);

    color.rgb = ambient + diffuse + specular;
    color.a = 1.0;

    gl_FragColor = color * texture2D( texture, texCoord * 2.0 );
}
