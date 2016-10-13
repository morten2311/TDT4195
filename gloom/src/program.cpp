// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
GLuint createVAO(GLfloat* vertices, int size,GLuint* indices) {
	GLuint array;
	GLuint VBO;
	GLuint IB;

	//Create VAO
	glGenVertexArrays(1, &array);
	glBindVertexArray(array);
	//Create buffer
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable the vertex attribute
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 15, indices, GL_STATIC_DRAW);
	return(array);

}

void runProgram(GLFWwindow* window)
{

	Gloom::Shader shader;shader.makeBasicShader("../gloom/shaders/simple.vert","../gloom/shaders/simple.frag");
	GLfloat vertices1[] = { -0.6, -0.6, 0, -0.3, -0.6, 0, -0.3, 0,0,
							0.6, 0.6, 0, 0, 0.6, 0, 0, 0, 0 ,
							-0.8, 0.3, 0, -0.2, 0.3, 0, -0.8, 0.8, 0,  
							-0.6, 0, 0, -0.6, -0.3, 0, -0.5, 0,0,
		-0.9, 0, 0, -0.9, -0.3, 0, -0.7, 0,0 };

	GLfloat vertices[] = {	
							-0.3, 0, 0,
							-0.6, -0.6, 0,
							-0.3, -0.6, 0
		 };
	GLfloat vertice2[] = {
		0.6, -0.8, -1.2,
		0, 0.4, 0,
		-0.8, -0.2, 1.2
	};

	GLuint indices[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	//GLuint indices[] = { 0,1,2};

	GLuint vao = createVAO(vertices, 9*5,indices);
	printGLError();

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

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here
		// Activate shader program
		shader.activate();
		glBindVertexArray(vao);
        // Draw your scene here
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
	

		glBindVertexArray(0);
	

		// Deactivate shader program
		shader.deactivate();

        // Handle other events
        glfwPollEvents();

        // Flip buffers
        glfwSwapBuffers(window);
    }
	shader.destroy();
}


void keyboardCallback(GLFWwindow* window, int key, int scancode,
                      int action, int mods)
{
    // Use escape key for terminating the GLFW window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
