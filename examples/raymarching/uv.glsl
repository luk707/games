#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

varying vec4 vColor;

void main()
{
   gl_Position = position;
   vColor = vec4((position.x + 1) / 2, (position.y + 1) / 2, 0, 0);
}

#shader fragment
#version 330 core

#define ITERATIONS 1000
#define MIN_D 0.0001
#define MAX_D 30.

layout(location = 0) out vec4 color;

uniform vec4 u_Data;

uniform vec3 u_CameraPosition;
uniform vec3 u_CameraTarget;
uniform vec3 u_CameraUp;

varying vec4 vColor;

// signed distance to a sphere
float sdSphere( vec3 p, float r) {
 	return length(p) -r;   
}

// signed distance to the plan y=0
float sdPlan(vec3 p) {
    return abs(p.y);
}

// signed distance to a cube of dimension b
float sdBox( vec3 p, vec3 b )
{
  vec3 d = abs(p) - b;
  return length(max(d,0.0));
}

// adapted from http://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
vec3 rotation(vec3 point, vec3 axis, float angle){
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    mat4 rot= mat4(oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,0.0,0.0,1.0);
    return (rot*vec4(point,1.)).xyz;
}

float distS[10];
// compute distance to each object and returns the minimum (aka the distance to each object)
float sdScene(vec3 pos, float iTime) {
    vec3 cubePos = rotation(pos - vec3(0.,1.,-3.5), vec3(0.,.5,0.5), iTime);
    distS[0] = sdSphere(pos-vec3(.5,.5,-5.), 1.);
    distS[1] = sdPlan(pos);
    distS[2] = sdBox(cubePos, vec3(.5,.5,.5));
    distS[3] = sdBox(pos - vec3(2.,0.,-3.), vec3(.5,.6,.5));
    int oid = 0;
    float d = distS[0];
    for(int i=1;i<=3;i++) {
        if(distS[i] < d) {
          oid = i;
          d = distS[i];
        }
    }
	return d;
}

// raymarch algorithm
float rayMarch(vec3 ro, vec3 rd, float iTime) {
	vec3 pos = ro;
    float inc = 0.;
    float d = 0.;
    for(int i=0;i<ITERATIONS;i++) {
    	pos = ro + d*rd;
        inc = sdScene(pos, iTime);
        d += inc;
        if(inc < MIN_D || d > MAX_D) break;
    }
    return d;
}

void main()
{
    vec2 uv = vColor.xy;
    uv -=0.5;
    uv.x *= u_Data.z/u_Data.w;

    vec3 camPos = vec3(sin(u_Data.x) * 2,1.,cos(u_Data.x) * 2);
    vec3 ro = camPos + vec3(0.,0.,1.);
    float offset = .0003;
    vec3 rd0 = normalize(camPos + vec3(uv + vec2(-offset, offset), 0) - ro);
    vec3 rd1 = normalize(camPos + vec3(uv + vec2(-offset, -offset), 0) - ro);
    vec3 rd2 = normalize(camPos + vec3(uv + vec2(offset, -offset), 0) - ro);
    vec3 rd3 = normalize(camPos + vec3(uv + vec2(offset, offset), 0) - ro);

    float d0 = rayMarch(ro, rd0, u_Data.x);
    float d1 = rayMarch(ro, rd1, u_Data.x);
    float d2 = rayMarch(ro, rd2, u_Data.x);
    float d3 = rayMarch(ro, rd3, u_Data.x);

    vec3 col0 = vec3(smoothstep(MAX_D, 0, pow(d0-1, 2)));
    vec3 col1 = vec3(smoothstep(MAX_D, 0, pow(d1-1, 2)));
    vec3 col2 = vec3(smoothstep(MAX_D, 0, pow(d2-1, 2)));
    vec3 col3 = vec3(smoothstep(MAX_D, 0, pow(d3-1, 2)));

    color = vec4(.25 * (col0 + col1 + col2 + col3), 1);
}
