#pragma once

#include "Shader.h"

Shader::Shader(const char* name, const char* vertexShader, const char* fragmentShader) {
	// La funzione successiva crea un programma shader completo a partire da due shader individuali: 
	// uno per la gestione dei vertici e uno per la gestione dei pixel. 
	// Il programma shader risultante viene identificato da un numero univoco (il programId) che verr  utilizzato in seguito per associarlo ad un oggetto grafico e per renderizzarlo.
	//All'interno della funzione ShaderMaker::createProgram
	//Compilazione degli shader : La funzione compila i due shader individuali, verificando che non ci siano errori di sintassi.
	//Linkaggio : Una volta compilati, i due shader vengono collegati insieme per formare un programma shader completo.
	// Creazione dell'identificativo: Viene generato un identificativo univoco per il programma shader e viene restituito alla funzione chiamante.
	char vS[100], fS[100];
	strcpy_s(vS, SHADER_FOLDER);
	strcat_s(vS, vertexShader);
	strcpy_s(fS, SHADER_FOLDER);
	strcat_s(fS, fragmentShader);
	
	this->programId = ShaderMaker::createProgram(vS, fS);
	this->name = std::string(name);
}

std::string Shader::getName() {
	return name;
}

GLuint Shader::getProgramId() {
	return programId;
}