#include <libreria.h>
#include <manejoArchivos.cpp>
#include <funcAux.cpp>

#define CSV_CLASES "iriClasesGYM.csv"// :(
#define CSV_CLIENTES "iriClientesGYM.csv"//:(
#define BINARIO "asistencias_1697673600000.dat"

/*ES DE ESPERAR QUE SALGA "SEGMENTATION FAULT". SI NUNCA PUEDE LEER EL ARCHIVO Y VER QUÉ TAN LARGO ES PARA GENERAR LOS ARRAYS DINÁMICOS, A LA HORA DE LLENAR ESOS ARRAYS VA A APARECER EL ERROR*/

int main() {
    
            /*-------- DECLARACIÓN Y APERTURA DE ARCHIVOS --------*/

    ofstream generar_binario_buenardo;
    generar_binario_buenardo.open(BINARIO, ios::binary | ios::app); // IOS::APP PARA MANDAR EL CURSOR AL FINAL

    ifstream archivo_clases;
    archivo_clases.open(CSV_CLASES);

    ifstream infile_b;
    infile_b.open(BINARIO, ios::binary);

    ifstream archivo_datos_clientes;
    archivo_datos_clientes.open(CSV_CLIENTES);

    unsigned int n_asistencias = sizeof(infile_b)/sizeof(Asistencia);
    unsigned int nclientes = largo_archivo(archivo_datos_clientes);
    unsigned int nclases = largo_archivo(archivo_clases);
    unsigned int i,j;

    Clientes *array_clientes = new Clientes [nclientes];
    Clases *array_clases = new Clases [nclases];
    Asistencia *array_asistencia = new Asistencia [nclientes];
    Cupo *control_cupos = new Cupo [nclases]; //VARIABLE QUE TIENE IGUAL ESPACIO QUE LAS CLASES EN LA QUE SE VA CONTROLANDO LA CANTIDAD DE RESERVAS
    Asistencia *datos_archivo_asistencia = new Asistencia [n_asistencias];



    /*VACIO E INICIALIZO LOS ARRAYS DE ASISTENCIAS E INSCRIPCIONES CON LOS QUE VOY A TRABAJAR*/
    for(i=0; i<nclientes; i++){
        array_asistencia[i].cantInscriptos = 0;
        array_asistencia[i].CursosInscriptos = nullptr;
    }
    for(i=0; i<n_asistencias; i++){
        datos_archivo_asistencia[i].cantInscriptos = 0;
        datos_archivo_asistencia[i].CursosInscriptos = nullptr;
    }

    leer_archivo_clientes(archivo_datos_clientes,array_clientes);
    leer_archivo_clases(archivo_clases,array_clases);
    leer_archivo_binario(infile_b,datos_archivo_asistencia,n_asistencias);


            /*-------- SE INICIALIZAN LOS CUPOS DE CADA CLASE --------*/

    unsigned int max_spinning = 45;
    unsigned int max_yoga = 25;
    unsigned int max_pilates = 15;
    unsigned int max_stretching = 40;
    unsigned int max_zumba = 50;
    unsigned int max_boxeo = 30;
    unsigned int max_musculacion = 30;


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

    /*VARIABLES AUXILIARES*/
    unsigned int aux1;
    unsigned int aux2;
    time_t aux3;
    bool rta;

    for( i = 0; i<nclientes; i++)
    {

        //VOY CARGANDO LOS DATOS EN EL ARRAY DE ASISTENCIAS

        //cantInscriptos_aux = rand()% (4-1+1)+1;//ACOTADO ENTRE 1 Y 4 PARA PROBAR SIMPLEMENTE
        aux1 = 1+ rand()%4;

        array_asistencia[i].idCliente = array_clientes[i].idCliente;
        array_asistencia[i].cantInscriptos = aux1;   //ACOTADO ENTRE 1 Y 4 PARA PROBAR SIMPLEMENTE
    }

    asignar_espacios_inscripciones(array_asistencia,nclientes);

    for(i=0; i<nclientes; i++){
        for( j=0; j<array_asistencia[i].cantInscriptos; j++)
        {

            aux2 = 1 +  rand()%120;
            aux3 = 1000000000 + (rand() * 700);

            array_asistencia[i].CursosInscriptos[j].idCurso = aux2;

            array_asistencia[i].CursosInscriptos[j].fechaInscripcion = aux3;
        }
    }

    /*---------* SEGUNDA PARTE --> CORROBORAR DATOS Y QUE NO ESTEN REPETIDOS *---------*/

    for(i=0; i<nclientes; i++)
    {
        for(j=0; j<array_asistencia[i].cantInscriptos;)
        {
            rta = existencia_clase(array_asistencia[i].CursosInscriptos[j].idCurso, nclases);

            if( rta == false ) //SI ALGUNA DE LAS CLASES QUE RESERVÓ EL CLIENTE NO ESTA ENTRE LOS RANGOS VÁLIDO LA SACAMOS
            {
                eliminar(array_asistencia[i].CursosInscriptos, array_asistencia[i].cantInscriptos,j);
            }
            else
                j++; //COMO AL ELIMINAR UN ELEMENTO TENGO QUE RECORRER UNO MENOS, SOLO INCREMENTO LA 'j' SI NO ELIMINÉ UNO
        }
    }
    int pos, pos_repetido;
    double segundos;

    for(i=0; i<nclientes; i++)
    {

        pos = buscar_idclases_repetidos(array_asistencia[i].CursosInscriptos, array_asistencia[i].cantInscriptos);

        if(pos != -1){ //Si encontró 2 id de clase repetidos

            pos_repetido = buscar_repetidos_eliminar(array_asistencia[i].CursosInscriptos, array_asistencia[i].cantInscriptos);
            segundos = difftime(array_asistencia[i].CursosInscriptos[pos].fechaInscripcion , array_asistencia[i].CursosInscriptos[pos_repetido].fechaInscripcion);

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

            int pos_repetido = buscar_mismo_horario_clase_repetido(array_asistencia[i].CursosInscriptos,array_asistencia[i].cantInscriptos,array_clases,nclases); //BUSCO EL OTRO QUE TIENE MISMO HORARIO
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

    /*SE ACTUALIZA EL CUPO DE LAS RESERVAS ANTERIORES*/
    for(i=0; i<n_asistencias; i++)
    {
        for(j=0; j<array_asistencia[i].cantInscriptos; j++)
        {
            actualizar_cupo(control_cupos,nclases,datos_archivo_asistencia[i].CursosInscriptos[j].idCurso);
        }
    }

    /*SE ACTUALIZA EL CUPO DE LAS NUEVAS RESERVAS*/
    for(i=0; i<nclientes; i++)
    {
        for(j=0; j<array_asistencia[i].cantInscriptos; j++)
        {
            actualizar_cupo(control_cupos,nclases,array_asistencia[i].CursosInscriptos[j].idCurso);
        }
    }

    for( i=0; i<nclientes;i++) //SI EL CLIENTE NO TIENE LA CUOTA AL DÍA LO DAMOS DE BAJA DE TODOS LOS CURSOS EN LOS QUE ESTÉ
    {
        if( EstadoPos(array_clientes, array_asistencia[i].idCliente,nclientes) == false)
        {
            for(j=0; j<array_asistencia[i].cantInscriptos; j++)
            {
                actualizar_cupo_restar(control_cupos,nclases,array_asistencia[i].CursosInscriptos[j].idCurso);
            }
        }
    }
    for( i=0; i<n_asistencias; i++) //SI EL CLIENTE NO TIENE LA CUOTA AL DÍA LO DAMOS DE BAJA DE TODOS LOS CURSOS EN LOS QUE ESTÉ
    {
        if( EstadoPos(array_clientes, datos_archivo_asistencia[i].idCliente,n_asistencias) == false)
        {
            for(j=0; j<datos_archivo_asistencia[i].cantInscriptos; j++)
            {
                actualizar_cupo_restar(control_cupos,nclases,datos_archivo_asistencia[i].CursosInscriptos[j].idCurso);
            }
        }
    }

    /*UNA VEZ PROCESADAS Y FILTRADAS TODAS LAS RESERVAS, GENERAMOS EL ARCHIVO BINARIO*/

    escribir_bin(generar_binario_buenardo,array_asistencia,nclientes);


/*-------------------------------------------------------------------------------------------------------- --------------------------------------------------------------------------------------------------------*/

        /*-------- SE LIBERA LA MEMORIA RESERVADA Y SE CIERRAN LOS ARCHIVOS --------*/
    for(i=0; i<nclientes;i++)
    {
        delete [] array_asistencia[i].CursosInscriptos;
    }

    for(i=0;i<n_asistencias;i++)
    {
        delete [] datos_archivo_asistencia[i].CursosInscriptos;
    }

    delete [] datos_archivo_asistencia;
    delete [] array_asistencia;
    delete [] control_cupos;
    delete [] array_clases;
    delete [] array_clientes;

    archivo_datos_clientes.close();
    archivo_clases.close();
    infile_b.close();
    generar_binario_buenardo.close();

/*-------------------------------------------------------------------------------------------------------- --------------------------------------------------------------------------------------------------------*/

    cout<<"Exito!!!"<<endl;

    return 0;
}
