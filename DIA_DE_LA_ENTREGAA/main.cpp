#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define CSV_CLASES "iriClasesGYM.csv"
#define CSV_CLIENTES "iriClientesGYM.csv"
#define BINARIO "asistencias_1697673600000.dat"
#define NUEVO_BINARIO "ProbandoProbando.dat"

using namespace std;

struct Cupo{
    unsigned int Id_clase;
    unsigned int cupo_max;
    unsigned int ocupados;
};

typedef struct {
    unsigned int idCurso;
    time_t fechaInscripcion;
} Inscripcion;

typedef struct {
    unsigned int idCliente, cantInscriptos;
    Inscripcion* CursosInscriptos;
} Asistencia;

struct Clientes{

    unsigned int idCliente;
    string nombre;
    string apellido;
    string email;
    string telefono;
    string fechaNac;
    int estado;

};
struct Clases{

    unsigned int idClase;
    string nombre_clase;
    float horario;

};

using namespace std;

//DAIOWNDOINWODINAWOD
void asignar_espacios_inscripciones (Asistencia *array_asistencia, unsigned int n_asistencias);

/*FUNCIONES PARA MANEJO DE ARCHIVOS*/
unsigned int largo_archivo(ifstream &archivo);
void leer_archivo_clases (ifstream &archivo, Clases *array_clases);
void leer_archivo_binario (ifstream &archivo, Asistencia *array_asistencia, unsigned int n_asistencias);
void leer_archivo_clientes (ifstream &archivo, Clientes*);

/*FUNCIONES QUE REVISAN QUE NO TENGA 2 CLASES EN EL MISMO HORARIO*/
float buscar_horario_clase(Clases *array_clases, unsigned int idClase,unsigned int nclases); //LE DOY UN ID DE CLASE, ME DEVUELVE SU HORARIO ----> FUNCIONA BIEN
int buscar_mismo_horario_clase (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos, Clases *array_clases, unsigned int nclases);// ----> FUNCIONA BIEN
int buscar_mismo_horario_clase_repetido (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos, Clases *array_clases, unsigned int nclases);//----> FUNCIONA BIEN

/*FUNCIONES QUE REVISAN QUE NO TENGA EL MISMO ID DE CLASES EN MI ARRAY DE INSCRIPCIONES*/
int buscar_idclases_repetidos (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos);//LE PASO UN ARRAY DE INCRIPCIONES, BUSCA SI HAY REPETIDOS, SI ENCUENTRA, //---->FUNCIONA BIEN
int buscar_repetidos_eliminar (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos); //ESTE IGUAL, SOLO QUE RETORNA 'j' //---->FUNCIONA BIEN

/*FUNCIONES DE CONTROL Y ORGANIZACION*/
void eliminar(Inscripcion *array_inscripcion, unsigned int &cantInscriptos, unsigned int eliminar);//----> FUNCIONA LOCOOOOOOO
bool actualizar_cupo (Cupo *control_cupos, unsigned int nclases ,unsigned int Id_clase); //INFORMA SI SE PUDO REALIZAR LA RESERVA Y SI HAY CUPOS DISPONIBLES ( NO HAY CUPOS -->  false  || SE PUDO RESERVAS --> true )
void asignar_espacios_inscripciones_individual (Asistencia asistencia, unsigned int cantInscriptos);
bool actualizar_cupo_restar (Cupo *control_cupos, unsigned int nclases, unsigned int Id_clase);
bool EstadoPos(Clientes *array_clientes, unsigned int Id_cliente, unsigned int nclientes);
bool existencia_clase(unsigned int ID, unsigned int nclases);



void escribir_bin(ofstream &archivo, Asistencia *array_datos, unsigned int nclientes);

using namespace std;



int main()
{

    ofstream generar_binario_buenardo;
    generar_binario_buenardo.open(NUEVO_BINARIO, ios::binary | ios::app); // IOS::APP PARA MANDAR EL CURSOR AL FINAL

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




    Cupo *control_cupos = new Cupo [nclases]; //VARIABLE QUE TIENE IGUAL ESPACIO QUE LAS CLASES EN LA QUE SE VA CONTROLANDO LA CANTIDAD DE RESERVAS

    unsigned int max_spinning = 45;
    unsigned int max_yoga = 25;
    unsigned int max_pilates = 15;
    unsigned int max_stretching = 40;
    unsigned int max_zumba = 50;
    unsigned int max_boxeo = 30;
    unsigned int max_musculacion = 30;

    /*SE INICIALIZAN LOS CUPOS DE CADA CLASE*/
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

       /* ---------* PRIMERA PARTE --> LLENAR ARRAYS *---------*/

    srand (time(NULL));
    bool rta;

    /*VARIABLES AUXILIARES*/
    unsigned int aux1;
    unsigned int aux2;
    time_t aux3;

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
   // ---------* SEGUNDA PARTE --> CORROBORAR DATOS Y QUE NO ESTEN REPETIDOS *---------


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
   // ---------* TERCERA PARTE --> CORROBORAR QUE NO TENGA 2 CLASES DISTINTAS EN EL MISMO HORARIO *---------

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

//////////////////////////

        /*for(i=0;i<10;i++)
        {
            cout<<"Cliente numero: "<<i+1<<endl;
            cout<<array_asistencia[i].idCliente<<endl;
            cout<<array_asistencia[i].cantInscriptos<<endl;
            for(j=0;j<array_asistencia[i].cantInscriptos;j++)
            {
                cout<<"Clase numero: "<<j+1<<endl;
                cout<<array_asistencia[i].CursosInscriptos[j].idCurso<<endl;
                cout<<array_asistencia[i].CursosInscriptos[j].fechaInscripcion<<endl;
                cout<<endl;

            }
        }*/

    escribir_bin(generar_binario_buenardo,array_asistencia,nclientes);


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



    cout<<" Exito !!!"<<endl;

    return 0;
}
/**/unsigned int largo_archivo(ifstream &archivo){

    unsigned int cont = 0;

    string linea, header;

    getline(archivo, header);

    while (!archivo.eof() && getline (archivo,linea)){

        cont++;

    }

    archivo.clear();
    archivo.seekg(0,ios::beg);

    return cont;

}
/**/void leer_archivo_clases (ifstream &archivo, Clases *array_clases)
{

    string header;
    int i = 0;

    char delimiter = ',';

    string idClase_aux;
    string nombre_aux;
    string horario_aux;

    string linea;
    stringstream s;

    if(!archivo.is_open()) //Chequeo que se haya abierto bien el archivo
    {
        cout<<"Hubo un error al abrir el archivo"<<endl;
        return;
    }

    getline(archivo,header);//Me copio el header para descartarlo

    while( !archivo.eof() && (getline(archivo,linea))){

        s.clear();
        s<<linea;

        getline(s,idClase_aux,delimiter);
        getline(s,nombre_aux,delimiter);
        getline(s,horario_aux,delimiter);


        int StoI_id = stoi(idClase_aux);

        (array_clases+i)->idClase = StoI_id;
        (array_clases+i)->nombre_clase = nombre_aux;
        (array_clases+i)->horario = StoI_id;

        i++;
    }
    archivo.clear();
    archivo.seekg(0,ios::beg);
    return;
}
/**/void leer_archivo_binario (ifstream &archivo, Asistencia *array_asistencia, unsigned int n_asistencias)
{

    unsigned int i,j;

    //VARIABLES AUXILIARES
    unsigned int idCliente_aux = 0;
    unsigned int cantInscriptos_aux = 0; //RARO PERO ME LO PIDE QT, "VARIABLES MAY NOT BE INITIALIZED"

    Inscripcion inscripcion_aux;



    if(!archivo.is_open()){
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }

    for(i=0; i<n_asistencias; i++)
    {
        archivo.read((char*)&idCliente_aux,sizeof(unsigned int));
        archivo.read((char*)&cantInscriptos_aux,sizeof(unsigned int));

        (array_asistencia + i) ->cantInscriptos = cantInscriptos_aux;
        (array_asistencia + i) ->idCliente = idCliente_aux;

        (array_asistencia+i)->CursosInscriptos = new Inscripcion [cantInscriptos_aux];

        for(j=0; j<cantInscriptos_aux;j++)
        {
                archivo.read((char*)&inscripcion_aux,sizeof(Inscripcion));
                array_asistencia[i].CursosInscriptos[j] = inscripcion_aux;
        }

    }

    archivo.clear();
    archivo.seekg(0,ios::beg);

    return;

}
void asignar_espacios_inscripciones (Asistencia *array_asistencia, unsigned int nclientes)
{
    unsigned int i = 0;
    while(i<nclientes){

        unsigned int reservas_cliente = array_asistencia[i].cantInscriptos;
        (array_asistencia+i)->CursosInscriptos = new Inscripcion [reservas_cliente];
        i++;
    }
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
void escribir_bin(ofstream &archivo, Asistencia *array_datos, unsigned int nclientes)
{
    unsigned int i,j;

    if(archivo.is_open())
    {
        for(i=0; i<nclientes; i++)
        {
            archivo.write((char*)&array_datos[i].idCliente,sizeof(unsigned int));
            archivo.write((char*)&array_datos[i].cantInscriptos,sizeof(unsigned int));

            for(j=0; j<array_datos[i].cantInscriptos; j++)
            {
            archivo.write((char*)&array_datos[i].CursosInscriptos[j],sizeof(Inscripcion));
            }
        }
    }
    return;
}
/**/bool identificar_menores(string fecha)
{
    string aux;

    aux = fecha.substr(6,10);

    if(aux.compare("2008") == -1)
        return true;
    else
        return false;

}

/**/bool existencia_clase(unsigned int ID, unsigned int nclases)
{
    if(ID <= nclases)
    {
        return true;
    }

    return false;

}

/**/bool chequear_letras_nombres (string nombre_cliente)
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

/**/bool ExistenciaPersona(Clientes *array_clientes, int nclientes, unsigned int IDBuscado){
    Clientes *aux= array_clientes;// para no perder el punt de la cabeza del array
    Clientes *ultimo= (array_clientes + nclientes -1);//busco la ultima posicion del array de clases
    while(aux != ultimo)
    {
        if(aux->idCliente  ==  IDBuscado)
            return true;//existe ese ID

        aux++;//aumento el puntero para avanzar
    }
        return false;//no existe
}
/**/float buscar_horario_clase(Clases *array_clases, unsigned int idClase, unsigned int nclases) //LE DOY UN ID DE CLASE, ME DEVUELVE SU HORARIO
{
    unsigned int i=0;

    for(i=0; i<nclases;i++)
    {
        if ( array_clases[i].idClase == idClase )
            return array_clases[i].horario;
    }
        return -1.0;

}
/**/int buscar_mismo_horario_clase (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos, Clases *array_clases, unsigned int nclases )
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
        return -1;
}
/**/int buscar_mismo_horario_clase_repetido (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos, Clases *array_clases, unsigned int nclases)
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
        return -1;

}
/**/int buscar_idclases_repetidos (Inscripcion *inscripciones_cliente, unsigned int cantInscriptos)
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
/**/void eliminar(Inscripcion *array_inscripcion, unsigned int &cantInscriptos, unsigned int eliminar)
{
    unsigned int i = 0;

    if (eliminar == cantInscriptos - 1)
    {
        cantInscriptos--;//si es el último, resto uno a n y listo!
        return;
    }
    //muevo las inscripciones debajo del que quiero eliminar un lugar hacia arriba tapando los datosd e l que quiero eliminar
    for (i = eliminar; i < cantInscriptos-1; i++)
    {
        array_inscripcion[i] = array_inscripcion[i+1];
    }

    cantInscriptos--;
    return;
}


/**/bool EstadoPos(Clientes *array_clientes, unsigned int Id_cliente, unsigned int nclientes)
{
    unsigned int i;

    for(i=0; i<nclientes; i++)
    {
        if(array_clientes[i].idCliente == Id_cliente)
        {
            if(array_clientes[i].estado >= 0)
            {
                return true;
            }
        }
    }

    return false;
}
void leer_archivo_clientes(ifstream &archivo, Clientes *array_clientes)
{

    string header,linea;
    int i = 0;

    string id_aux;
    string nombre_aux;
    string apellido_aux;
    string email_aux;
    string telefono_aux;
    string fechaNac_aux;
    string estado_aux;
    stringstream s;

    char delimiter = ',';


    if(!archivo.is_open()) //Chequeo que se haya abierto bien el archivo
    {
        cout<<"Hubo un error al abrir el archivo"<<endl;
        return;
    }

    getline(archivo,header);

    while(!(archivo.eof()) && (getline(archivo,linea))){

        s.clear();
        s<<linea;

        getline(s,id_aux,delimiter);
        getline(s,nombre_aux,delimiter);
        getline(s,apellido_aux,delimiter);
        getline(s,email_aux,delimiter);
        getline(s,telefono_aux,delimiter);
        getline(s,fechaNac_aux,delimiter);
        getline(s,estado_aux,delimiter);

        /*       FILTROS PARA VERIFICAR SI LOS DATOS ESTAN CORRECTOS       */

        unsigned int StoI = stoi(id_aux);
        int EstadotoI = stoi(estado_aux);

        (array_clientes+i)->idCliente = StoI;
        (array_clientes+i)->nombre = nombre_aux;
        (array_clientes+i)->apellido = apellido_aux;
        (array_clientes+i)->email = email_aux;
        (array_clientes+i)->telefono = telefono_aux;
        (array_clientes+i)->fechaNac = fechaNac_aux;
        (array_clientes+i)->estado = EstadotoI;

        i++;
    }

    archivo.clear();
    archivo.seekg(0,ios::beg);
}
bool actualizar_cupo_restar (Cupo *control_cupos, unsigned int nclases, unsigned int Id_clase)
{
    unsigned int i;

    for(i=0; i<nclases;i++)
    {
        if( (control_cupos[i].Id_clase == Id_clase) && (control_cupos[i].ocupados > 0) )
        {// PARA REDUCIR EN UNO LA CANTIDAD DE CUPOS OCUPADOS TENGO QUE VER QUE SEAN MAYORES A CERO PORQUE NO LE VOY A RESTAR A UNA CLASE QUE YA TENGA CERO
            control_cupos[i].ocupados--;
            return true;
        }
    }
    return false;
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
