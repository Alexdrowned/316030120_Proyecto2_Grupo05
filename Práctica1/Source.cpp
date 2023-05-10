/*---------------------------------------------------------*/
/* ----------------   Práctica 1 (Continuación)--------------------------*/
/*-----------------    2023-2   ---------------------------*/
/*------------- Bautista Beltrán Axel Arturo 316030120 ---------------*/
#include <glew.h>
#include <glfw3.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow* window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor* monitors;
GLuint VBO[2], VAO[2], EBO[2];
GLuint shaderProgramYellow, shaderProgramColor;

static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);							\n\
}"; //Vertex shader

static const char* myVertexShaderColor = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
	ourColor = aColor;														\n\
}";

// Fragment Shader
static const char* myFragmentShaderYellow = "									\n\
#version 330																\n\
																			\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(0.0f, 0.0f, 1.0f);									\n\
}";

static const char* myFragmentShaderColor = "								\n\
#version 330 core															\n\
out vec4 FragColor;															\n\
in vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
	FragColor = vec4(ourColor, 1.0f);										\n\
}";

void myData(void);
void setupShaders(void);
void display(void);
void getResolution(void);


void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	float vertices[] =
	{
		// positions         //color
		0.0f,  0.00f, 0.0f, 1.0f,  1.0f, 1.0f, //1
		//Puntos centrales
		0.0f,  0.55f, 0.0f, 1.0f,  0.0f, 0.0f, //1
		0.0f,  0.25f, 0.0f, 0.0f,  1.0f, 0.0f, //2
		0.0f,  -0.70f, 0.0f, 0.0f,  0.0f, 1.0f, //3
		0.0f,  -0.75f, 0.0f, 1.0f,  1.0f, 0.0f, //4
		0.0f,  -0.80f, 0.0f, 0.0f,  1.0f, 1.0f, //5

		//Puntos derecha
		0.08f,  -0.70f, 0.0f, 1.0f,  0.0f, 1.0f, //6
		0.22f,  -0.775f, 0.0f, 1.0f,  0.75f, 0.80f, //7
		0.25f,  -0.7125f, 0.0f, 0.43f,  0.30f, 0.210f, //8
		0.36f,  -0.55f, 0.0f, 0.584f,  0.513f, 0.713f, //9
		0.16f,  -0.1f, 0.0f, 1.0f,  0.647f, 0.0f, //10
		0.27f,  -0.08f, 0.0f, 0.549f,  0.8074f, 0.9216f, //11
		0.47f,  -0.12f, 0.0f, 0.9f,  0.1f, 0.3f, //12
		0.18f,  -0.05f, 0.0f, 0.71f,  0.40f, 0.12f, //13
		0.325f,  0.0f, 0.0f, 0.50f,  0.50f, 0.50f, //14
		0.22f,  0.23f, 0.0f, 0.56f,  0.94f, 0.56f, //15
		0.44f,  0.21f, 0.0f, 0.0f,  0.0f, 0.0f, //16
		0.35f,  0.30f, 0.0f, 1.0f,  0.840f, 0.0f, //17
		0.20f,  0.55f, 0.0f, 0.0f,  0.20f, 0.13f, //18
		0.30f,  0.55f, 0.0f, 1.0f,  1.0f, 1.0f, //19
		0.39f,  0.52f, 0.0f, 0.125f,  0.450f, 0.20f, //20
		0.42f,  0.50f, 0.0f, 0.25f,  0.5f, 1.0f, //21
		0.37f,  0.65f, 0.0f, 0.3f,  0.3f, 0.3f, //22
		0.40f,  0.75f, 0.0f, 0.0f,  0.0f, 0.0f, //23
		0.10f,  -0.725f, 0.0f, 1.0f,  1.0f, 1.0f, //24

		-0.08f,  -0.70f, 0.0f, 1.0f,  0.0f, 1.0f, //25
		-0.22f,  -0.775f, 0.0f, 1.0f,  0.75f, 0.80f, //26
		-0.25f,  -0.7125f, 0.0f, 0.43f,  0.30f, 0.210f, //27
		-0.36f,  -0.55f, 0.0f, 0.584f,  0.513f, 0.713f, //28
		-0.16f,  -0.1f, 0.0f, 1.0f,  0.647f, 0.0f, //29
		-0.27f,  -0.08f, 0.0f, 0.549f,  0.8074f, 0.9216f, //30
		-0.47f,  -0.12f, 0.0f, 0.9f,  0.1f, 0.3f, //31
		-0.18f,  -0.05f, 0.0f, 0.71f,  0.40f, 0.12f, //32
		-0.325f,  0.0f, 0.0f, 0.50f,  0.50f, 0.50f, //33
		-0.22f,  0.23f, 0.0f, 0.56f,  0.94f, 0.56f, //34
		-0.44f,  0.21f, 0.0f, 0.0f,  0.0f, 0.0f, //34
		-0.35f,  0.30f, 0.0f, 1.0f,  0.840f, 0.0f, //35
		-0.20f,  0.55f, 0.0f, 0.0f,  0.20f, 0.13f, //36
		-0.30f,  0.55f, 0.0f, 1.0f,  1.0f, 1.0f, //37
		-0.39f,  0.52f, 0.0f, 0.125f,  0.450f, 0.20f, //38
		-0.42f,  0.50f, 0.0f, 0.25f,  0.5f, 1.0f, //39
		-0.37f,  0.65f, 0.0f, 0.3f,  0.3f, 0.3f, //40
		-0.40f,  0.75f, 0.0f, 0.0f,  0.0f, 0.0f, //41
		-0.10f,  -0.725f, 0.0f, 1.0f,  1.0f, 1.0f, //42
	};

	unsigned int indices[] =
	{
		1,2,15,17,19, //0 ->5 -listo
		23,18,19,22, //5 -> 4 -listo
		22,19,17,20, //9 -> 4 -listo
		23,22,20,21, // 13 -> 4 -listo	
		21,16,17,20, //17 -> 4 -listo
		15,13,14,16,17, // 21 -> 5 -listo
		14,11,9,12,16, // 26 -> 5 -listo
		11,10,8,9, // 31 -> 4
		7,8,6,24,4,5, // 35 -> 6
		24,6,3,4, //41 -> 4

		//Parte izquierda
		1,2,34,36,38, //45 -> 5
		42,37,38,41, //50 -> 4
		42,41,39,40, //54 -> 4
		41,38,36,39, //58 -> 4
		40,39,36,35, //62 -> 4
		34,36,35,33,32, //66 -> 5
		33,35,31,28,30, //71 -> 5
		30,28,27,29, //76 -> 4
		26,27,25,43,4,5, //80 ->6
		43,25,3,4, // 86 -> 4

		//Parte central
		2,15,13,10,29,32,34, // 90 -> 7
		3,25,29,10,6, // 97 -> 5

		//
		6,8,10, //102 -> 3
		25,27,29, // 105 -> 3

	};

	glGenVertexArrays(2, VAO); //Pasamos de la memoria ram a la memoria de video
	glGenBuffers(2, VBO); //Crear dos buffers para enviar información
	glGenBuffers(2, EBO); //Buffer para indices o elementos



	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //Pasa los datos al buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Busca el numero de vertices
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Aqui decimos la posición de como estan los atributos
	glEnableVertexAttribArray(0); //Void * 0 indica la posición cero dentro del arreglo
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1); //Toma desde la posición 3 para color / 6 * sizeof (float) indica que hara 6 lecturas para cada parte

	//Para trabajar con indices (Element Buffer Object)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void setupShaders()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &myVertexShader, NULL);
	glCompileShader(vertexShader);

	unsigned int vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderColor, 1, &myVertexShaderColor, NULL);
	glCompileShader(vertexShaderColor);

	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &myFragmentShaderYellow, NULL);
	glCompileShader(fragmentShaderYellow);

	unsigned int fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderColor, 1, &myFragmentShaderColor, NULL);
	glCompileShader(fragmentShaderColor);


	//Crear el Programa que combina Geometría con Color
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	shaderProgramColor = glCreateProgram();
	glAttachShader(shaderProgramColor, vertexShaderColor);
	glAttachShader(shaderProgramColor, fragmentShaderColor);
	glLinkProgram(shaderProgramColor);
	//Check for errors 

	//ya con el Programa, el Shader no es necesario
	glDeleteShader(vertexShader);
	glDeleteShader(vertexShaderColor);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderColor);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Axel", NULL, NULL); //Especifica el tamaño y nombre de la ventana
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);//Posición de la ventana
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize); //Se trabajan con muchos buffers

	glewInit();


	//My Functions
	//Setup Data to use
	myData();
	//To Setup Shaders
	setupShaders();

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Background color
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Display Section
		glUseProgram(shaderProgramColor);

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
		glPointSize(10.0);
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(5 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(9 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(13 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(17 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(21 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(26 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(31 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(35 * sizeof(float)));
		//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(41 * sizeof(float)));
		//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(46 * sizeof(float)));
		//Parte izquierda
	
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(45 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(50 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(54 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(58 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(62 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(66 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(71 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(76 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(80 * sizeof(float)));
		//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(86 * sizeof(float)));

		//Parte central
		glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, (void*)(90 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(97 * sizeof(float)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(102 * sizeof(float)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(105 * sizeof(float)));
		

		glBindVertexArray(0);
		glUseProgram(0);


		//End of Display Section

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}