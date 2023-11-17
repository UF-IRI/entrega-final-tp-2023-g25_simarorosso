#include <catch2/catch.hpp>
#include <funcAux.h>
/*
TESTCASE("Identificar menores "){

    string cumple = "23-06-2005";

    identificar_menores(cumple);

    CHECK(identificar_menores(cumple) == true);
}
TESTCASE("Chequear letras blimblimblamblam"){

    string nombre = "H0la";

    bool result = chequear_letras_nombres(nombre);

    CHECK(result == false);
}
*/

TEST_CASE("Existencia de la clase"){
    int nclases=3;
    Clases arrayClases[nclases];


    //falta el cupo q lo vamos a hacer con lo de el generaor de clientes

    SECTION("Existe la clase"){
        arrayClases[0]={1, "Spinning", 8.00};
        arrayClases[1]={25, "Zumba", 10.00};
        arrayClases[2]={51, "Musculacion", 15.3};
        //inicializo mis clases
        bool respuesta;
        respuesta=existencia_clase( 25, nclases);
        CHECK(respuesta == true);
    };

    SECTION("No existe la clase"){
        arrayClases[0]={1, "Spinning", 8.00};
        arrayClases[1]={25, "Zumba", 10.00};
        arrayClases[2]={51, "Musculacion", 15.3};
        //inicializo mis clases
        bool respuesta;
        respuesta=existencia_clase( 0, nclases);
        CHECK(respuesta == false);
    };
}
/*

bool existencia_clase(unsigned int ID, int nclases)
{
    if(ID > 0 && ID < nclases)
        return true;
    else
        return false;
}
*/

TEST_CASE("Existencia de la persona"){

    int nclientes=3;
    Clientes arrayclientes[3];
    bool resp;
    //REQUIRE(nclientes>0);?????????

    arrayclientes[0] = {1, "Agustín", "Guerra", "AgustínGuerra@bolandia.iri" ,"462-185-1730", "10-12-1966",	0};
                                                                                                             arrayclientes[1] = {21, "Valentina", "Santos", "ValentinaSantos@bolandia.iri", "267-761-2323", "20-10-2002", -14049};
    arrayclientes[2] = {49, "Brenda", "Cabrera", "BrendaCabrera@bolandia.iri", "520-861-4363", "05-07-1971", 12326};
    //inizializo una lista de clientes
    SECTION("Existe"){
        resp=ExistenciaPersona(arrayclientes, nclientes, 21);//ingreso los datos a la func y le doy un ID existente
        CHECK(resp == true);
    }
    SECTION("No existe"){
        resp=ExistenciaPersona(arrayclientes, nclientes, 745);//ingreso los datos a la func y le doy un ID existente
        CHECK(resp == false);
    }
}
/*
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
 */


TEST_CASE("Identificar menores"){

    int nclientes=3;
    Clientes arrayclientes[3];
    bool resp;
    //REQUIRE(nclientes>0);?????????

    arrayclientes[0] = {1, "Agustín", "Guerra", "AgustínGuerra@bolandia.iri" ,"462-185-1730", "10-12-1966",	0};
                                                                                                             arrayclientes[1] = {21, "Valentina", "Santos", "ValentinaSantos@bolandia.iri", "267-761-2323", "20-10-2002", -14049};
    arrayclientes[2] = {140, "Alejandro", "Quintero", "AlejandroQuintero@bolandia.iri", "244-461-0321", "03-09-2010", -9736};
    int i;
    int contmenores = 0;
    for(i = 0; i < nclientes; i++ ){
        resp=identificar_menores(arrayclientes[i].fechaNac);
        if(resp==false)
            contmenores++;
    }
    CHECK(contmenores==1);
}//REVISAR SI ESTA BIEN

TEST_CASE("Filtro para letras de nombres"){
    int nclientes=3;
    Clientes arrayclientes[3];
    //REQUIRE(nclientes>0);?????????
    SECTION("Hay un caracter mal en el [1]"){

        arrayclientes[0] = {131, "Maximiliano", "Tovar", "MaximilianoTovar@bolandia.iri","624-201-9885", "25-09-1993", -914};
        arrayclientes[1] = {104, "Abr9l", "Tovar", "AbrilTovar@bolandia.iri", "944-827-3204", "16-03-2000", 0};
        arrayclientes[2] = {140, "Alejandro", "Quintero", "AlejandroQuintero@bolandia.iri", "244-461-0321", "03-09-2010", -9736};
        int i;
        int conterrnombres = 0;
        for(i = 0 ; i < nclientes ; i++){
            if(chequear_letras_nombres (arrayclientes[i].nombre))
                conterrnombres++;
        }

        CHECK(conterrnombres == 1);
    }
    SECTION("Todos Bien"){

        arrayclientes[0] = {131, "Maximiliano", "Tovar", "MaximilianoTovar@bolandia.iri","624-201-9885", "25-09-1993", -914};
        arrayclientes[1] = {104, "Abril", "Tovar", "AbrilTovar@bolandia.iri", "944-827-3204", "16-03-2000", 0};
        arrayclientes[2] = {140, "Alejandro", "Quintero", "AlejandroQuintero@bolandia.iri", "244-461-0321", "03-09-2010", -9736};
        int i;
        int conterrnombres = 0;
        for(i = 0 ; i < nclientes ; i++){
            if(chequear_letras_nombres (arrayclientes[i].nombre))
                conterrnombres++;
        }

        CHECK(conterrnombres == 0);
    }
}

TEST_CASE("Busqueda de IDclases repetidas"){

    SECTION("Hay repetidos"){
        Asistencia AsistenciaCliente;
        Inscripcion array_inscripciones[4];
        array_inscripciones[0]={ 3 , 4215165168 };//este es el que quiero encontrar para luego comparar con el otro
        array_inscripciones[1]={ 3 , 2348752390 };
        array_inscripciones[2]={ 5 , 7813401343 };
        array_inscripciones[3]={ 8 , 1348951434 };
        Inscripcion *puntero=&array_inscripciones[4];

        AsistenciaCliente={ 7 , 4, puntero };
        int resp=buscar_idclases_repetidos( puntero, 4 );

        REQUIRE(resp==0);
    }

    SECTION("No hay repetidos"){
        Asistencia AsistenciaCliente;
        Inscripcion array_inscripciones[4];
        array_inscripciones[0]={ 3 , 4215165168 };
        array_inscripciones[1]={ 7 , 2348752390 };
        array_inscripciones[2]={ 5 , 7813401343 };
        array_inscripciones[3]={ 8 , 1348951434 };
        Inscripcion *puntero=&array_inscripciones[4];

        AsistenciaCliente={ 7 , 4, puntero };
        int resp=buscar_idclases_repetidos( puntero, 4 );

        REQUIRE(resp==-1);
    }
}

TEST_CASE("Bucar los repetidos para eliminar repetidos"){
    SECTION("Hay repetidos"){
        Asistencia AsistenciaCliente;
        Inscripcion array_inscripciones[4];
        array_inscripciones[0]={ 3 , 4215165168 };
        array_inscripciones[1]={ 3 , 2348752390 };//este es el que quiero encontrar para luego eliminarlo
        array_inscripciones[2]={ 5 , 7813401343 };
        array_inscripciones[3]={ 8 , 1348951434 };
        Inscripcion *puntero=&array_inscripciones[4];

        AsistenciaCliente={ 7 , 4, puntero };
        int resp=buscar_repetidos_eliminar( puntero, 4 );

        REQUIRE(resp==1);
    }

    SECTION("No hay repetidos"){
        Asistencia AsistenciaCliente;
        Inscripcion array_inscripciones[4];
        array_inscripciones[0]={ 3 , 4215165168 };
        array_inscripciones[1]={ 7 , 2348752390 };
        array_inscripciones[2]={ 5 , 7813401343 };
        array_inscripciones[3]={ 8 , 1348951434 };
        Inscripcion *puntero=&array_inscripciones[4];

        AsistenciaCliente={ 7 , 4, puntero };
        int resp=buscar_repetidos_eliminar( puntero, 4 );

        REQUIRE(resp==-1);
    }
}

TEST_CASE("Eliminar el repetido que me envían"){

SECTION("Esta en la segunda posicion"){
    unsigned int cantinscriptos=4;
    Inscripcion *array_inscripciones= new Inscripcion[cantinscriptos];
    array_inscripciones[0]={ 3 , 4215165168 };
    array_inscripciones[1]={ 3 , 2348752390 };//este es el que quiero eliminar
    array_inscripciones[2]={ 5 , 7813401343 };
    array_inscripciones[3]={ 8 , 1348951434 };
    Inscripcion *puntero=&array_inscripciones[cantinscriptos];
    int posaeliminar=1;
    eliminar(puntero, cantinscriptos, posaeliminar);
    CHECK(cantinscriptos == cantinscriptos-1);
    for (unsigned int i = 0; i < cantinscriptos; ++i){
        cout<<array_inscripciones->idCurso<<endl;
    }
    delete[] array_inscripciones;
}
SECTION("Esta en la ultima posicion"){
    unsigned int cantinscriptos=4;
    Inscripcion *array_inscripciones= new Inscripcion[cantinscriptos];
    array_inscripciones[0]={ 3 , 4215165168 };
    array_inscripciones[1]={ 6 , 2348752390 };
    array_inscripciones[2]={ 5 , 7813401343 };
    array_inscripciones[3]={ 5 , 1348951434 };//este es el que quiero eliminar
    Inscripcion *puntero=&array_inscripciones[cantinscriptos];
    int posaeliminar=1;
    eliminar(puntero, cantinscriptos, posaeliminar);
    CHECK(cantinscriptos == cantinscriptos-1);
    for (unsigned int i = 0; i < cantinscriptos; ++i){
        cout<<array_inscripciones->idCurso<<endl;
    }//preguntar si esta bien
    delete[] array_inscripciones;
}
}

/*

typedef struct {

    unsigned int idCliente, cantInscriptos;
    Inscripcion* CursosInscriptos;

} Asistencia;

typedef struct {

    unsigned int idCurso;
    time_t fechaInscripcion;

} Inscripcion;

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
*/

TEST_CASE("Estado del cliente"){
    SECTION("No debe"){
        Clientes Cliente;
        bool respuesta;
        Cliente = {104, "Abril", "Tovar", "AbrilTovar@bolandia.iri", "944-827-3204", "16-03-2000", 0};
        respuesta= EstadoPos( Cliente.estado);
        CHECK(respuesta == true);
    }

    SECTION("Debe"){
        Clientes Cliente;
        bool respuesta;
        Cliente = {104, "Abril", "Tovar", "AbrilTovar@bolandia.iri", "944-827-3204", "16-03-2000", -5647};
        respuesta= EstadoPos( Cliente.estado);
        CHECK(respuesta == false);
    }
}
/*
bool EstadoPos(int estado)
{
    if( estado < 0)
        return false;
    else
        return true;
}
*/

