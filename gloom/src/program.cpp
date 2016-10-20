// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLuint createVAO(GLfloat* vertices, GLfloat* RGBA, int size_vertices,int size_index,int size_RGB,GLuint* indices) {
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

void runProgram(GLFWwindow* window)
{


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
	GLfloat RGBA[] = {
		1,0,0,1,
		0,1,0,1,
		0,0,1,1,

		1,0,0,1,
		0,1,0,1,
		0,0,1,1,

		1,0,0,1,
		0,1,0,1,
		0,0,1,1,

		1,0,0,1,
		0,1,0,1,
		0,0,1,1,

		1,0,0,1,
		0,1,0,1,
		0,0,1,1,

	};
	//All 5 triangles
	GLfloat vertices1[] = { -0.6, -0.6, 0, -0.3, -0.6, 0, -0.3, 0,0,
		0.6, 0.6, 0, 0, 0.6, 0, 0, 0, 0 ,
		-0.8, 0.3, 0, -0.2, 0.3, 0, -0.8, 0.8, 0,
		-0.6, 0, 0, -0.6, -0.3, 0, -0.5, 0,0,
		-0.9, 0, 0, -0.9, -0.3, 0, -0.7, 0,0 };

	//1 Triangle for task 1c and 2d)
	GLfloat vertices[] = {
		-0.3, 0, 0,
		-0.6, -0.6, 0,
		-0.3, -0.6, 0
	};
	//Triangle for task 1d)
	GLfloat vertice2[] = {
		0.6, -0.8, -1.2,
		0, 0.4, 0,
		-0.8, -0.2, 1.2
	};
	//indices for all 5 triangles
	GLuint indices1[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	//Indices for task 1c , 2d,c)
	GLuint indices[] = { 0,1,2 };
	//Creat the VAO with vertices and with the sizes for both the buffers and the indices. Here sizes are given to make 5 triangles. 
	GLuint vao = createVAO(vertices, RGBA, 9 * 5, 15, 4 * 15, indices);
	printGLError();





    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Draw your scene here


		glBindVertexArray(vao);
		// Activate shader program
		shader.activate();

		//Uniform Transformation
		glm::mat4x4 IDmatrix(1.0);
		glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(IDmatrix));


		//Transform to camera coordinate system
		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);



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


	//Move left
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);

	}   
	//Move right
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}  
	//Move up
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}   
	//Move down
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//Move forward
	if (key == GLFW_KEY_LEFT_SHIFT && key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}   
	//Move backward
	if (key == GLFW_KEY_LEFT_SHIFT && key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}   

	//Rotate horizontally
	if ((key == GLFW_KEY_LEFT_SHIFT && (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT)) && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//Rotate vertically
	if ((key == GLFW_KEY_LEFT_SHIFT && (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN)) && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
