/*-------------------------------------
* CITS3003 Project 2019
* Alexander Varano della Vergiliana.
* Student ID: 22268701
* ------------------------------------*/

varying vec3 pos, N;
varying vec2 texCoord;  // The third coordinate is always 0.0 and is discarded

uniform vec3 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform vec4 LightPosition;
uniform vec4 LightPosition2;
uniform float Shininess;
uniform sampler2D texture;
uniform float texScale;

vec4 color;
vec3 specular, ambient, diffuse;

void main()
{
  int i;

  // The vector to the light from the vertex
  vec3 Lvec[2];
  Lvec[0] = LightPosition.xyz - pos;
  Lvec[1] = LightPosition2.xyz - (0.0, 0.0, 0.0) ;  //Directional light 2

  color = gl_FrontLightModelProduct.sceneColor;
  for(i = 0; i < 2; i++)
  {
    // Unit direction vectors for Blinn-Phong shading calculation
    vec3 L = normalize(Lvec[i]);   // Direction to the light source
    vec3 E = normalize( -pos );   // Direction to the eye/camera
    vec3 H = normalize( L + E );  // Halfway vector

    // Compute terms in the illumination equation
    ambient = AmbientProduct;

    //float Kd = max( dot(L, N), 0.0 );
    float Kd = max( dot(-L, N), 0.0 );
    diffuse = Kd*DiffuseProduct;

    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    specular = Ks * SpecularProduct;

    if (dot(L, N) < 0.0 )
    {
      specular = vec3(0.0, 0.0, 0.0);
    }

    color.rgb += ambient + diffuse + specular;
  }

  color.a = 1.0;

  // globalAmbient is independent of distance from the light source
  vec3 globalAmbient = vec3(0.01, 0.01, 0.01);

  gl_FragColor = color * texture2D( texture, texCoord * texScale );
}
