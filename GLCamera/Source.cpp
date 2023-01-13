#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <OpenGL/Shader.h>
#include <OpenGL/Texture.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VAO, VBO, EBO;
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
	glGenBuffers(1, &EBO);


	//Bind all the buffers and buffer data to them
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	//enable vertex attrib arrays
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// unbind buffer (everything has been registered in Vertex Attribute Pointer)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//texture stuff
	glGenTextures(1, &texture);
	glGenTextures(1, &texture2);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "texture success!" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "texture success!" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	stbi_image_free(data2);
	
	ourShader.use();
	ourShader.setFloat(offval, 0.0f);

	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // manually
	ourShader.setInt("texture2", 1); // or with shader class

	//MATHS
	
	glm::mat4 model = glm::mat4(1.0f);
	

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

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
		glm::mat4 trans = glm::mat4(1.0f);
		
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 trans = glm::mat4(1.0);
			trans = glm::translate(trans, cubePositions[i]);
			trans = glm::rotate(trans, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.3f));
			

			//if (i % 3 == 0)
			{
				trans = glm::rotate(trans, glm::radians(10.0f * (float)glfwGetTime()), glm::vec3(1.0f, 0.3f, 0.3f));
			}

			ourShader.setMat4("model", trans);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//put the transform in our shader
		model = glm::rotate(model, 0.0005f * (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));


		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		ourShader.setMat4("view", view);
		ourShader.setMat4("perspective", perspective);



		//draw triangle
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		


		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate(); //terminate program


	return 0;
}
