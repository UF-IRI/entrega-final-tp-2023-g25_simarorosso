#ifndef MANEJOARCHIVOS_H
#define MANEJOARCHIVOS_H


#include <libreria.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/*FUNCIONES PARA MANEJO DE ARCHIVOS*/
unsigned int largo_archivo(ifstream &archivo);
void leer_archivo_clases (ifstream &archivo, Clases *array_clases);
void leer_archivo_binario (ifstream &archivo, Asistencia *array_asistencia, unsigned int n_asistencias);
void leer_archivo_clientes (ifstream &archivo, Clientes*);
void escribir_bin(ofstream &archivo, Asistencia *array_datos, unsigned int nclientes);




#endif // MANEJOARCHIVOS_H
