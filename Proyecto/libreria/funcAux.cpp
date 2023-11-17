#include <funcAux.h>

bool identificar_menores(string fecha)
{
    string aux;

    aux = fecha.substr(6,10);

    if(aux.compare("2008") == -1)
        return true;
    else
        return false;

}

bool existencia_clase(unsigned int ID, int nclases)
{
    if(ID > 0 && ID < nclases)
        return true;
    else
        return false;
}

bool chequear_letras_nombres (string nombre_cliente)
{
    int largo_nombre = nombre_cliente.length();

    int i;

    for(i=0;i<largo_nombre;i++)
    {
        /*if(cliente_aux[i] == 'á' || cliente_aux[i]== 'é'|| cliente_aux[i]== 'í' || cliente_aux[i]== 'ó' || cliente_aux[i]== 'ú') //NO ME DETECTA LAS LETRAS CON ACENTO A PESAR Q SE LO INDICO
        {
            continue;
        }*/
        if( !(nombre_cliente[i] >= 'a' && nombre_cliente[i] <= 'z') && !(nombre_cliente[i] >= 'A' && nombre_cliente[i] <= 'Z'))
        {
            return false;
        }
    }
    return true;
}

bool ExistenciaPersona(Clientes *array_clientes, int nclientes, unsigned int IDBuscado){
    Clientes *aux= array_clientes;// para no perder el punt de la cabeza del array
    Clientes *ultimo= (array_clientes + nclientes -1);//busco la ultima posicion del array de clases
    while(aux != ultimo){//hasta que llegue al final
        if(aux->idCliente  ==  IDBuscado)//comparo que los ID sean iguales
            return true;//existe ese ID

        aux++;//aumento el puntero para avanzar
    }
    if( aux == ultimo)
        return false;//no existe
}//preguntar porque la alerta

/*
void resize_clientes (Clientes *&array_clientes, int &nclientes)
{
    nclientes++;

    Clientes *array_clientes_aux = new Clientes [nclientes];

    if(array_clientes_aux == nullptr) //Veo si tengo memoria
        return;


    for(int i = 0; i<(nclientes-1);i++)
    {
        array_clientes_aux[i] = array_clientes[i];
    }

    delete [] array_clientes;
    array_clientes = array_clientes_aux;

    return;
}
*/

float buscar_horario_clase(Clases *array_clases, unsigned int idClase, unsigned int nclases) //LE DOY UN ID DE CLASE, ME DEVUELVE SU HORARIO
{
    unsigned int i=0;

    for(i=0; i<nclases;i++)
    {
        if ( array_clases[i].idClase == idClase )
            return array_clases[i].horario;
    }

    if(i == nclases)
        return -1.0;
}
int buscar_mismo_horario_clase (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos, Clases *array_clases, unsigned int nclases )
{
    unsigned int i,j;

    for(i=0;i<cantInscriptos;i++)
    {
        for(j = (i+1); j < cantInscriptos; j++)
        {
            float h1,h2;
            h1 = buscar_horario_clase(array_clases,inscripciones_cliente[i].idCurso,nclases);
            h2 = buscar_horario_clase(array_clases,inscripciones_cliente[j].idCurso,nclases);

            if (h1 == h2)
                return i;// Tengo dos iguales, devuelvo 'i'

        }
    }
    if(i == cantInscriptos)
        return -1;
}
int buscar_mismo_horario_clase_repetido (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos, Clases *array_clases, unsigned int nclases)
{
    unsigned int i,j;
    for(i=0;i<cantInscriptos;i++)
    {
        for(j = (i+1); j < cantInscriptos; j++)
        {
            float h1,h2;
            h1 = buscar_horario_clase(array_clases,inscripciones_cliente[i].idCurso,nclases);
            h2 = buscar_horario_clase(array_clases,inscripciones_cliente[j].idCurso,nclases);

            if (h1 == h2)
                return j;// Igual que la funcion anterior, devuelvo 'j'

        }
    }
    if(i == cantInscriptos)
        return -1;
}
int buscar_idclases_repetidos (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos)
{
    unsigned int i,j;
    for(i = 0; i<cantInscriptos; i++)
    {
        for(j = (i+1); j < cantInscriptos; j++)
        {
            if (inscripciones_cliente[i].idCurso == inscripciones_cliente[j].idCurso)
            {
                return i;
            }

        }
    }
    return -1;
}
int buscar_repetidos_eliminar (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos)
{
    unsigned int i,j;
    for(i = 0; i<cantInscriptos; i++)
    {
        for(j = (i+1); j < cantInscriptos; j++)
        {
            if (inscripciones_cliente[i].idCurso == inscripciones_cliente[j].idCurso)
            {
                return j;
            }

        }
    }
    return -1;
}
void eliminar(Inscripcion *array_inscripcion, unsigned int &cantInscriptos, unsigned int eliminar)
{
    unsigned int i;

    if (eliminar == cantInscriptos - 1)
    {
        cantInscriptos--;//si es el último, resto uno a n y listo!
        return;
    }
    //muevo las inscripciones debajo del que quiero eliminar un lugar hacia arriba tapando los datosd e l que quiero eliminar
    for (i = eliminar; i < cantInscriptos-1; i++)
    {
        array_inscripcion[i] = array_inscripcion[i + 1];
    }

    cantInscriptos--;
    return;
}

void asignar_espacios_inscripciones (Asistencia *array_asistencia, unsigned int n_asistencias)
{
    unsigned int i;
    for( i=0; i<n_asistencias; i++)
    {
        array_asistencia[i].CursosInscriptos = new Inscripcion [array_asistencia[i].cantInscriptos];
    }
}
void asignar_espacios_inscripciones_individual (Asistencia asistencia)
{
    asistencia.CursosInscriptos = new Inscripcion [asistencia.cantInscriptos];
    return;
}
void terminar_de_leer_archivo_binario (ifstream &archivo, Asistencia *array_asistencia, unsigned int n_asistencias)
{

    unsigned int i,j;

    //VARIABLES AUXILIARES
    Inscripcion inscripcion_aux;
    unsigned int idCliente_aux = 0;
    unsigned int cantInscriptos_aux = 0;

    if(!archivo.is_open()){
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }

    for(i=0; i<n_asistencias; i++)
    {
        archivo.read((char*)&idCliente_aux,sizeof(unsigned int));
        archivo.read((char*)&cantInscriptos_aux,sizeof(unsigned int));

        for(j=0; j<cantInscriptos_aux;j++)
        {
            archivo.read((char*)&inscripcion_aux,sizeof(Inscripcion));
            array_asistencia[i].CursosInscriptos[j]=inscripcion_aux;
        }

    }

    archivo.clear();
    archivo.seekg(0,ios::beg);

    return;

}
bool actualizar_cupo (Cupo *control_cupos, unsigned int nclases, unsigned int Id_clase)
{
    unsigned int i;

    for(i=0; i<nclases;i++)
    {
        if( (control_cupos[i].Id_clase == Id_clase) && (control_cupos[i].ocupados < control_cupos[i].cupo_max))
        {
            control_cupos[i].ocupados++;
            return true;
        }
    }
    return false;
}

bool EstadoPos(int estado)
{
    if( estado < 0)
        return false;
    else
        return true;
}
