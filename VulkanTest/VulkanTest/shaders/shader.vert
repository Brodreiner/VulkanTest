#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;


//layout(location = 0) in vec3 inPosition;
//layout(location = 1) in vec3 inColor;

//layout(location = 0) out vec3 fragColor;

//out gl_PerVertex {
//    vec4 gl_Position;
//};

//vec3 positions[8] = vec3[](
//	vec3(-0.5f,-0.5f, 0.5f),
//	vec3( 0.5f,-0.5f, 0.5f),
//	vec3( 0.5f, 0.5f, 0.5f),
//	vec3(-0.5f, 0.5f, 0.5f),
//	vec3(-0.5f,-0.5f,-0.5f),
//	vec3( 0.5f,-0.5f,-0.5f),
//	vec3( 0.5f, 0.5f,-0.5f),
//	vec3(-0.5f, 0.5f,-0.5f)
//);

//int index[36] = int[](
//	0, 1, 2, 2, 3, 0,
//	4, 5, 6, 6, 7, 4,
//	0, 4, 1, 1, 4, 5,
//	1, 5, 2, 2, 5, 6,
//	2, 6, 3, 3, 6, 7,
//	3, 7, 0, 0, 7, 4
//);



//void main() {
//	//const int rowSize = 100;
//	//int cubeIndex = gl_VertexIndex/36;
//	//int x = cubeIndex % rowSize;
//	//int y = (cubeIndex % (rowSize * rowSize)) / rowSize;
//	//int z = cubeIndex / (rowSize * rowSize);
//	//vec3 relativePosition = positions[index[gl_VertexIndex % 36]];	
//	//float realPositionX = (x + relativePosition.x - rowSize/2)  / rowSize;
//	//float realPositionY = (y + relativePosition.y -rowSize/2)  / rowSize;
//	//float realPositionZ = (z + relativePosition.z - rowSize/2)  / rowSize;
//	//vec3 position = vec3(realPositionX, realPositionY, realPositionZ);

//    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
//    fragColor = vec3(gl_VertexIndex/4%2,gl_VertexIndex/2%2,gl_VertexIndex%2);
//}



layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
}