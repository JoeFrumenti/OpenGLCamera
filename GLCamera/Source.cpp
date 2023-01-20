#include <Glad/glad.c>
#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <OpenGL/Shader.h>
#include <OpenGL/Texture.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VAO, VBO;
unsigned int texture;
unsigned int texture2;

int width, height, nrChannels;
unsigned char* data = stbi_load("container.jpg", &width, &height,
	&nrChannels, 0);

int width2, height2, nrChannels2;

float mixValue = 0.2f;



//vertices to make a rectangle hopefully
float vertices[] = { // positions           // texture coords
					   -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
						0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
						0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
						0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
					   -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
					   -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

					   -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
						0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
						0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
						0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
					   -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
					   -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
					   
					   -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
					   -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
					   -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
					   -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
					   -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
					   -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
						
					    0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
						0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
						0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
						0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
						0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
						0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
					   
					   -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
						0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
						0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
						0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
					   -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
					   -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
					   
					   -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
						0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
						0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
						0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
					   -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
					   -0.5f,  0.5f, -0.5f, 0.0f, 1.0f
};


//CUBES
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};


//resize window function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//input function
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		mixValue += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		mixValue -= 0.01f;
}

int main()
{

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data2 = stbi_load("awesomeface.png", &width2, &height2,
		&nrChannels2, 0);


	//initialize and configure window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	//set window to be the one we are working on
	glfwMakeContextCurrent(window);

	
	//Load GLAD, ensure it's working
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}


	//set GL to work properly and dynamically with the window (stretchy stuff)
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//tell OpenGL how to use textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//set up texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	
	Shader ourShader("vertexshader.vs", "fragmentshader.fs");
	
	std::string offval = "offsetvalue";


	//set up Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	//Bind all the buffers and buffer data to them
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	//enable vertex attrib arrays
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// unbind buffer (everything has been registered in Vertex Attribute Pointer)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//texture stuff
	Texture face = Texture("awesomeface.png", GL_TEXTURE0);
	Texture box = Texture("container.jpg", GL_TEXTURE1);

	ourShader.use();
	ourShader.setFloat(offval, 0.0f);


	ourShader.setInt("texture2", 0); //with shader class
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 1); // or manually
	

	//MATHS
	
	//local/world space
	glm::mat4 model = glm::mat4(1.0f);


	

	glm::mat4 view;

	//pre clip space (set perspective vs ortho)
	glm::mat4 perspective = glm::mat4(1.0f);
	perspective = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//clear depth test
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rendering commands
		ourShader.setFloat("mixValue", mixValue);

		//background color
		glClearColor(.27f, 0.38f, 0.92f, 1.0f); //set glclearcolor
		glClear(GL_COLOR_BUFFER_BIT);	//apply glclearcolor

		//Cool transform stuff
		
		//world space
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.3f));

			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//view space
		const float radius = 10.0f;
		float camX = (cos(glfwGetTime()) * radius);
		float camZ = (sin(glfwGetTime()) * radius);
		glm::vec3 cameraPos = glm::vec3(camX, 0, camZ);

		glm::vec3 cameraFront = glm::vec3(0, 0, -1);

		glm::vec3 up = glm::vec3(0, 1, 0);

		
		//std::cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
		

		view = glm::lookAt(cameraPos, cameraPos + cameraFront,
			up);

		//put the transform in our shader

		
		ourShader.setMat4("view", view);
		ourShader.setMat4("perspective", perspective);



		//draw triangle
		glBindVertexArray(VAO);

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate(); //terminate program

	return 0;
}
