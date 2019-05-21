attribute vec3 vPosition;
attribute vec2 vTexCoord;
attribute vec3 vNormal;

uniform mat4 ModelView;
uniform mat4 Projection;

varying vec2 texCoord;
varying vec3 pos, N;
varying vec3 Lvec[2];

attribute vec4 boneIDs;
attribute vec4 boneWeights;
uniform mat4 boneTransforms[64];

void main()
{
    // bones
    ivec4 bone = ivec4(boneIDs); // convert boneIDs to ivec4
    mat4 boneTransform = boneWeights[0] * boneTransforms[bone[0]] +
                         boneWeights[1] * boneTransforms[bone[1]] +
                         boneWeights[2] * boneTransforms[bone[2]] +
                         boneWeights[3] * boneTransforms[bone[3]];

    //vec4 vpos = vec4(vPosition, 1.0);
    vec4 vpos = vec4(vPosition, 1.0);

    // Transform vertex position into eye coordinates
    pos = (ModelView * boneTransform * vpos).xyz;

    // Transform vertex normal into eye coordinates (assumes scaling
    // is uniform across dimensions)

    //N = normalize( (ModelView * vec4(vNormal, 0.0)).xyz);
    N = normalize( (ModelView * boneTransform * vec4(vNormal, 0.0)).xyz);

    gl_Position = Projection * ModelView * boneTransform * vpos;
    texCoord = vTexCoord;
}
