#include <Glad/glad.c>
#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <OpenGL/Shader.h>
#include <OpenGL/Texture.h>
#include <OpenGL/Camera.h>

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


//Input variables
float mixValue = 0.2f;
float lastX = 400, lastY = 300;
bool firstMouse = true;
float Zoom = 45.0f;

//camera variables 

glm::vec3 cameraPos = glm::vec3(0, 0, 3);
glm::vec3 direction = (cameraPos - glm::vec3(0, 0, 0));
glm::vec3 cameraFront = glm::vec3(0, 0, -1);
glm::vec3 right = (glm::cross(direction, glm::vec3(0, 1, 0)));
glm::vec3 cameraUp = glm::vec3(0, 1, 0);

float yaw = -90.0f;
float pitch = 0;

//deltatime variables
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	else if (Zoom > 45.0f)
		Zoom = 45.0f;


}

//
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += xoffset;
	pitch += yoffset;
	pitch = glm::clamp(pitch, -89.0f, 89.0f);
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

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

	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) *
		cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) *
		cameraSpeed;
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);
	
	//Load GLAD, ensure it's working
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}


	//set GL to work properly and dynamically with the window (stretchy stuff)
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

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
	

	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		perspective = glm::perspective(glm::radians(Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
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
		


		
		//std::cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
		

		view = glm::lookAt(cameraPos, cameraFront + cameraPos,
			cameraUp);

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
