#include "gerstner.h"


Gerstner::Gerstner()
{
	ShaderGenerator shaderProgram;
	shaderProgram.AddShader("v_ocean.glsl", GL_VERTEX_SHADER);
	shaderProgram.AddShader("f_ambient_diffuse_specular.glsl", GL_FRAGMENT_SHADER);
	GLuint shaderProgramID = shaderProgram.LinkProgram();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	Ocean oceanObj(128, 128, .25, 5, 5, 1, vec2(-1, -1), 9, 0.8, 5);
	RenderObject oceanObjBuffer;
	oceanObjBuffer.SetVertex(oceanObj.GetVertices());
	oceanObjBuffer.SetUVs(oceanObj.GetUVs());
	oceanObjBuffer.SetIndices(oceanObj.GetIndices());


	GLuint mvp_uniform_block;
	glGenBuffers(1, &mvp_uniform_block);
	glBindBuffer(GL_UNIFORM_BUFFER, mvp_uniform_block);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) * 3, NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, mvp_uniform_block);

	GLuint wave_uniform_block;
	glGenBuffers(1, &wave_uniform_block);
	glBindBuffer(GL_UNIFORM_BUFFER, wave_uniform_block);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(int) + sizeof(float) * 4 + sizeof(vec2), NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, wave_uniform_block);

	GLuint timeID = glGetUniformLocation(shaderProgramID, "time");
	GLuint waveNumberID = glGetUniformLocation(shaderProgramID, "WaveNumber");
	GLuint globalSteepnessID = glGetUniformLocation(shaderProgramID, "GlobalSteepness");
	GLuint LightPosition_worldspaceID = glGetUniformLocation(shaderProgramID, "LightPosition_worldspace");
	GLuint EyePositionID = glGetUniformLocation(shaderProgramID, "EyePosition");
	GLuint DirectionalLight_direction_worldspaceID = glGetUniformLocation(shaderProgramID, "DirectionalLight_direction_worldspace");
	GLuint instance_offsetID = glGetUniformLocation(shaderProgramID, "instance_offset");

	vector<vec3> instance_offset_vec3 = oceanObj.GetInstance_offset();

	glfwSetTime(0);
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgramID);
		glUniform1f(timeID, glfwGetTime());
		glUniform1i(waveNumberID, oceanObj.WaveNumber);
		glUniform1f(globalSteepnessID, oceanObj.GlobalSteepness);

		glUniform3f(LightPosition_worldspaceID, 128 * .25 / 2, 7, 128 * .25 / 2);
		vec3 eyePos = getEyePos();
		glUniform3f(EyePositionID, eyePos.x, eyePos.y, eyePos.z);
		glUniform3f(DirectionalLight_direction_worldspaceID, -1, -1, -1);
		glUniform3fv(instance_offsetID, instance_offset_vec3.size(), &instance_offset_vec3[0].x);

		glBindBuffer(GL_UNIFORM_BUFFER, mvp_uniform_block);
		SendUniformMVP();
		glBindBuffer(GL_UNIFORM_BUFFER, wave_uniform_block);
		SendUniformWaveParameters(oceanObj);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, oceanObjBuffer.vertices_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oceanObjBuffer.indices_buffer);
		glDrawElementsInstanced(GL_TRIANGLES, oceanObj.GetIndices().size(), GL_UNSIGNED_INT, (void*) 0, instance_offset_vec3.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0);


	glDeleteProgram(shaderProgramID);
	glfwTerminate();
	return 0;
}

Gerstner::~Gerstner()
{

}
