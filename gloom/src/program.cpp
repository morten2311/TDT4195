// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include <glm/glm.hpp>
#include "sceneGraph.hpp"
#include "sphere.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
std::stack<glm::mat4>* stack;
//Colors
GLfloat red[] = { 1,0,0,1 };
GLfloat brown[] = {0.8,0.4,0,1 };
GLfloat white[] = { 1,1,1,1 };
GLfloat yellow[] = { 1,1,0,1 };
GLfloat blue[] = { 0,0,1,1 };

//Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -15.0f);
GLfloat rotationY = 0;
GLfloat rotationX = 0;
const int slices = 10, layers = 10;

SceneNode* sun;
SceneNode* earth;
SceneNode* moon;
SceneNode* mars;
SceneNode* jupiter;

GLuint vao;

glm::mat4 calcModel(SceneNode* node) {
	//glm::mat4 rotateVert = glm::rotate(glm::radians(node->rotationY), glm::vec3(1, 0, 0));
	//glm::mat4 rotateHor = glm::rotate(glm::radians(node->rotationX), glm::vec3(0, 1, 0));

	glm::mat4 rotateVert = glm::rotate(glm::radians(node->rotationY),node->);
	glm::mat4 rotateHor = glm::rotate(glm::radians(node->rotationX), glm::vec3(0, 1, 0));

	glm::mat4 translate = glm::translate(glm::vec3(node->x, node->y, node->z));
	glm::mat4 scale = glm::scale(glm::vec3(node->scaleFactor, node->scaleFactor, node->scaleFactor));
	glm::mat4 transformModel = rotateHor*rotateVert*translate*scale;
	return transformModel;

}

void update(SceneNode* node) {
	node->rotationX += (node->rotationSpeedRadians)*getTimeDeltaSeconds();
	node->rotationY += (node->rotationSpeedRadians)*getTimeDeltaSeconds();

}
void iterate_node(SceneNode* node, SceneNode* parent)
{
	update(node);
	if (parent) {
		node->currentTransformationMatrix = calcModel(node)*peekMatrix(stack);
	}
	else {
		node->currentTransformationMatrix = calcModel(node);
	}
	pushMatrix(stack,node->currentTransformationMatrix);
	//matrices
	glm::mat4x4 rotateVert;
	glm::mat4x4 rotateHor;
	glm::mat4x4 translate;
	glm::mat4x4 persp;

	rotateVert = glm::rotate(glm::radians(rotationY), glm::vec3(1, 0, 0));
	rotateHor = glm::rotate(glm::radians(rotationX), glm::vec3(0, 1, 0));
	translate = glm::translate(glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z));
	//projection
	persp = glm::perspective(glm::radians(45.0f), GLfloat(windowWidth) / GLfloat(windowHeight), 1.0f, 100.0f);

	glm::mat4x4 trans;
	trans = persp*rotateVert*rotateHor*translate*(node->currentTransformationMatrix);
	vao = node->vertexArrayObjectID;

	glBindVertexArray(vao);
	//draw
	glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, slices*layers * 2 * 3, GL_UNSIGNED_INT, 0);
	//unbind
	glBindVertexArray(0);

	for each (SceneNode* child in node->children) {
		iterate_node(child,node);
	}
	popMatrix(stack);
}
SceneNode* createSolarSystem() {
	//Create nodes
	sun = createSceneNode();
	earth = createSceneNode();
	moon = createSceneNode();
	mars = createSceneNode();
	jupiter = createSceneNode();

	//Set parameters
	sun->vertexArrayObjectID = createCircleVAO(slices, layers, yellow);
	sun->rotationSpeedRadians = (toRadians(360));
	sun->rotationDirection = glm::vec3(0, 1, 0);
	sun->scaleFactor = 1;
	sun->x = 0;
	sun->y = 0;
	sun->z = 0;

	earth->vertexArrayObjectID = createCircleVAO(slices, layers, blue);
	earth->rotationSpeedRadians = (toRadians(40));
	earth->rotationDirection = glm::vec3(0, 1, 0);
	earth->scaleFactor = 0.5;
	earth->x = 2;
	earth->y = 0;
	earth->z = 0;

	moon->vertexArrayObjectID = createCircleVAO(slices, layers, white);
	moon->rotationSpeedRadians = (toRadians(20));
	moon->rotationDirection = glm::vec3(1, 0, 0);
	moon->scaleFactor = 0.2;
	moon->x = 3;
	moon->y = 0;
	moon->z = 0;

	mars->vertexArrayObjectID = createCircleVAO(slices, layers, red);
	mars->rotationSpeedRadians = (toRadians(20));
	mars->rotationDirection = glm::vec3(1, 0, 0);
	mars->scaleFactor = 0.3;
	mars->x = 5;
	mars->y = 0;
	mars->z = 0;

	jupiter->vertexArrayObjectID = createCircleVAO(slices, layers, brown);
	jupiter->rotationSpeedRadians = (toRadians(20));
	jupiter->rotationDirection = glm::vec3(1, 0, 0);
	jupiter->scaleFactor = 0.7;
	jupiter->x = 7;
	jupiter->y = 0;
	jupiter->z = 0;

	//Create subgraph
	addChild(sun, mars);
	addChild(sun, jupiter);
	addChild(earth, moon);
	addChild(sun, earth);

	return sun;
}


void runProgram(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

    // Set GLFW callback mechanism(s)
    glfwSetKeyCallback(window, keyboardCallback);

    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc.)

	Gloom::Shader shader; shader.makeBasicShader("../gloom/shaders/simple.vert", "../gloom/shaders/simple.frag");

	//Creat the VAO with vertices and RGBA values, sizes for both the buffers and the indices.  
	SceneNode* root = createSolarSystem();
	stack = createEmptyMatrixStack();

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Draw your scene here
		// Activate shader program
		shader.activate();

		iterate_node(root,0);

		// Deactivate shader program
		shader.deactivate();

        // Handle other events
        glfwPollEvents();

        // Flip buffers
        glfwSwapBuffers(window);
    }
	shader.destroy();
}



GLuint createVAO(GLfloat* vertices, GLfloat* RGBA, int size_vertices, int size_index, int size_RGB, GLuint* indices) {
	GLuint array;
	GLuint VBO_vertices;
	GLuint VBO_RGBA;

	GLuint IB;

	//Create VAO
	glGenVertexArrays(1, &array);
	glBindVertexArray(array);
	//Create vertice buffer
	glGenBuffers(1, &VBO_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size_vertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable the vertex attribute
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size_index, indices, GL_STATIC_DRAW);

	//Create RGBA buffer
	glGenBuffers(1, &VBO_RGBA);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_RGBA);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size_RGB, RGBA, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	return(array);

}


//Move camera
void keyboardCallback(GLFWwindow* window, int key, int scancode,
	int action, int mods)	
{
	
    // Use escape key for terminating the GLFW window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

	//Move left
	if (key == GLFW_KEY_LEFT)
	{
		cameraPos.x += 0.05;
	}   
	//Move right
	if (key == GLFW_KEY_RIGHT )
	{
		cameraPos.x -= 0.05;

	}  
	//Move up
	if (key == GLFW_KEY_UP )
	{
		cameraPos.y -= 0.05;

	}   
	//Move down
	if (key == GLFW_KEY_DOWN )
	{
		cameraPos.y += 0.05;


	}

	//Move forward
	if (key == GLFW_KEY_W )
	{
		cameraPos.z += 0.05;
	}   
	//Move backward
	if ( key == GLFW_KEY_S)
	{
		cameraPos.z -= 0.05;

	}   

	//Rotate horizontally
	if (key == GLFW_KEY_H )
	{
		rotationX += 10;
	}
	//Rotate horizontally
	if (key == GLFW_KEY_N )
	{
		rotationX -= 10;
	}

	//Rotate vertically
	if (key == GLFW_KEY_V )
	{
		rotationY += 10;

	}
	//Rotate vertically
	if (key == GLFW_KEY_F )
	{
		rotationY -= 10;

	}
}
