#include <libreria.h>
#include <manejoArchivos.h>
#include <funcAux.h>

#define CSV_CLASES "../iriClasesGYM.csv"
#define CSV_CLIENTES "../iriClientesGYM.csv"
#define BINARIO "asistencias_1697673600000.dat"

int main() {
    
            /*-------- DECLARACIÓN Y APERTURA DE ARCHIVOS --------*/
    ifstream archivo_clases;
    archivo_clases.open(CSV_CLASES);

    ifstream infile_b;
    infile_b.open(BINARIO, ios::binary);

    ifstream archivo_datos_clientes;
    archivo_datos_clientes.open(CSV_CLIENTES);

    unsigned int nclientes = largo_archivo(archivo_datos_clientes);
    unsigned int nclases = largo_archivo(archivo_clases);

    Clientes *array_clientes = new Clientes [nclientes];
    Clases *array_clases = new Clases [nclases];
    Asistencia *array_asistencia = new Asistencia [nclientes];
    Cupo *control_cupos = new Cupo [nclases]; //VARIABLE QUE TIENE IGUAL ESPACIO QUE LAS CLASES EN LA QUE SE VA CONTROLANDO LA CANTIDAD DE RESERVAS
    //unsigned int n_asistencias = sizeof(infile_b)/sizeof(Asistencia);

    leer_archivo_clases(archivo_clases,array_clases);
    leer_archivo_clientes(archivo_datos_clientes,array_clientes);


            /*-------- SE INICIALIZAN LOS CUPOS DE CADA CLASE --------*/

    unsigned int max_spinning = 45;
    unsigned int max_yoga = 25;
    unsigned int max_pilates = 15;
    unsigned int max_stretching = 40;
    unsigned int max_zumba = 50;
    unsigned int max_boxeo = 30;
    unsigned int max_musculacion = 30;

    unsigned int i,j;

    for(i=0; i<nclases;i++)
    {
        if( (array_clases+i)->nombre_clase == "Spinning")
        {
            control_cupos[i].Id_clase = array_clases[i].idClase;
            control_cupos[i].cupo_max = max_spinning;
            control_cupos[i].ocupados = 0;
        }
        else if( (array_clases+i)->nombre_clase == "Yoga")
        {
            control_cupos[i].Id_clase = array_clases[i].idClase;
            control_cupos[i].cupo_max = max_yoga;
            control_cupos[i].ocupados = 0;
        }
        else if( (array_clases+i)->nombre_clase == "Pilates")
        {
            control_cupos[i].Id_clase = array_clases[i].idClase;
            control_cupos[i].cupo_max = max_pilates;
            control_cupos[i].ocupados = 0;
        }
        else if( (array_clases+i)->nombre_clase == "Stretching")
        {
            control_cupos[i].Id_clase = array_clases[i].idClase;
            control_cupos[i].cupo_max = max_stretching;
            control_cupos[i].ocupados = 0;
        }
        else if( (array_clases+i)->nombre_clase == "Zumba")
        {
            control_cupos[i].Id_clase = array_clases[i].idClase;
            control_cupos[i].cupo_max = max_zumba;
            control_cupos[i].ocupados = 0;
        }
        else if( (array_clases+i)->nombre_clase == "Boxeo")
        {
            control_cupos[i].Id_clase = array_clases[i].idClase;
            control_cupos[i].cupo_max = max_boxeo;
            control_cupos[i].ocupados = 0;
        }
        else if( (array_clases+i)->nombre_clase == "Musculacion")
        {
            control_cupos[i].Id_clase = array_clases[i].idClase;
            control_cupos[i].cupo_max = max_musculacion;
            control_cupos[i].ocupados = 0;
        }
    }

                        /*-------- SIMULACION --------*/



          /* ---------* PRIMERA PARTE --> LLENAR ARRAYS *---------*/

    srand (time(NULL));

    for( i = 0; i<nclientes; i++)
    {

        //VOY CARGANDO LOS DATOS EN EL ARRAY DE ASISTENCIAS

        int cantInscriptos_aux = rand() %4 + 1;//ACOTADO ENTRE 1 Y 4 PARA PROBAR SIMPLEMENTE

        array_asistencia[i].idCliente = array_clientes[i].idCliente;
        array_asistencia[i].cantInscriptos = cantInscriptos_aux;  //ACOTADO ENTRE 1 Y 4 PARA PROBAR SIMPLEMENTE

        asignar_espacios_inscripciones_individual(array_asistencia[i]);

        for( j=0; j< array_asistencia[i].cantInscriptos; j++)
        {
            int id_aux = rand() %251 + 1;
            time_t hora_inscrip_aux = rand() %100000000000 + 1000000000;

            Inscripcion auxiliar;
            auxiliar.idCurso = id_aux;
            auxiliar.fechaInscripcion = hora_inscrip_aux;

            array_asistencia[i].CursosInscriptos[j] = auxiliar;
        }
    }

    /*---------* SEGUNDA PARTE --> CORROBORAR DATOS Y QUE NO ESTEN REPETIDOS *---------*/




    for( i=0; i<nclientes;i++){

        int pos = buscar_idclases_repetidos(array_asistencia[i].CursosInscriptos, array_asistencia[i].cantInscriptos);

        if(pos != -1){ //Si encontró 2 id de clase repetidos

            int pos_repetido = buscar_repetidos_eliminar(array_asistencia[i].CursosInscriptos, array_asistencia[i].cantInscriptos);
            double segundos = difftime(array_asistencia[i].CursosInscriptos[pos].fechaInscripcion , array_asistencia[i].CursosInscriptos[pos_repetido].fechaInscripcion);

            if(segundos<0.0)//el que tengo que borrar es el segundo, la reserva se realizo despues
            {
                eliminar(array_asistencia[i].CursosInscriptos,array_asistencia[i].cantInscriptos,pos_repetido);
            }
            else
            {
                eliminar(array_asistencia[i].CursosInscriptos,array_asistencia[i].cantInscriptos,pos);
            }
        }
    }

    /* ---------* TERCERA PARTE --> CORROBORAR QUE NO TENGA 2 CLASES DISTINTAS EN EL MISMO HORARIO *---------*/

    for( i=0;i<nclientes;i++){

        int pos = buscar_mismo_horario_clase (array_asistencia[i].CursosInscriptos,array_asistencia[i].cantInscriptos,array_clases,nclases);

        if(pos != -1){ //POS != -1 SIGNIFICA QUE ENCONTRÓ 2 REPETIDOS

            int pos_repetido = buscar_mismo_horario_clase_repetido(array_asistencia[i].CursosInscriptos,array_asistencia[i].cantInscriptos,array_clases,nclases);
            double segundos = difftime(array_asistencia[i].CursosInscriptos[pos].fechaInscripcion , array_asistencia[i].CursosInscriptos[pos_repetido].fechaInscripcion);

            if(segundos<0.0) //el que tengo que borrar es el segundo, la reserva se realizo despues
            {
                eliminar(array_asistencia[i].CursosInscriptos,array_asistencia[i].cantInscriptos,pos_repetido);
            }
            else
            {
                eliminar(array_asistencia[i].CursosInscriptos,array_asistencia[i].cantInscriptos,pos);
            }

        }
    }

/*-------------------------------------------------------------------------------------------------------- --------------------------------------------------------------------------------------------------------*/

        /*-------- SE LIBERA LA MEMORIA RESERVADA Y SE CIERRAN LOS ARCHIVOS --------*/
    for(i=0; i<nclientes;i++)
    {
        delete [] array_asistencia[i].CursosInscriptos;
    }

    delete [] array_asistencia;
    delete [] control_cupos;
    delete [] array_clases;
    delete [] array_clientes;

    archivo_datos_clientes.close();
    archivo_clases.close();
    infile_b.close();
/*-------------------------------------------------------------------------------------------------------- --------------------------------------------------------------------------------------------------------*/

    cout<<"Exito!!!"<<endl;
    return 0;
}
