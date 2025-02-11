//Librerias Usadas
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Estructuras
struct Usuario {
    int cedula;
    char nombre[50];
};

struct Vehiculo {
    char placa[10];
    char modelo[30];
    char marca[20];
    int anio;
    char chofer[50];
    int idSector;
    bool disponible;
};

struct Sector {
    int id;
    char nombre[30];
};

// Clase principal
class SpeedCar 
{
private:
    Usuario colasEspera[10][100]; 
    int tamColas[10]; 
    Vehiculo listasVehiculos[10][100]; 
    int tamListas[10]; 

    Usuario usuarios[100];
    int numUsuarios;

    Vehiculo vehiculos[100];
    int numVehiculos;

    Sector sectores[10];
    int numSectores;

    fstream archivoUsuarios;
    fstream archivoVehiculos;
    fstream archivoSectores;

public:
    SpeedCar() 
	{
        numUsuarios = 0;
        numVehiculos = 0;
        numSectores = 0;
        for (int i = 0; i < 10; i++) {
            tamColas[i] = 0;
            tamListas[i] = 0;
        }
        cargarDatos();
    }
    
    //Funcion para cargar los datos del menu de gestión
    void cargarDatos() 
    {
        cargarUsuarios();
        cargarVehiculos();
        cargarSectores();
    }
    
    //Funcion para cargar los usuarios del menu de gestión
    void cargarUsuarios() 
	{
        ifstream archivoUsuarios("usuarios.txt");
        
        if (!archivoUsuarios) 
		{
            cout << "Archivo usuarios.txt no encontrado. Creando archivo vacio.\n";
            ofstream("usuarios.txt").close();
            return;
        }

        numUsuarios = 0; // Reiniciar lista de usuarios
        Usuario usuario;
        
        while (archivoUsuarios >> usuario.cedula) 
		{
        
		   archivoUsuarios.ignore();
           archivoUsuarios.getline(usuario.nombre, 50);
        
		   if (numUsuarios < 100) 
		   {
                usuarios[numUsuarios++] = usuario;
           }
       }
       
        archivoUsuarios.close();
   }
   
    //Funcion para cargar los vehiculos del menu de gestión
    void cargarVehiculos() 
	{
        ifstream archivoVehiculos("vehiculos.txt");
        
        if (!archivoVehiculos) 
		{
            cout << "Archivo vehiculos.txt no encontrado. Creando archivo vacio.\n";
            ofstream("vehiculos.txt").close();
            return;
        }

        numVehiculos = 0; // Reiniciar lista de vehículos
        Vehiculo vehiculo;
        
        while (archivoVehiculos >> vehiculo.placa >> vehiculo.modelo >> vehiculo.marca
           >> vehiculo.anio >> vehiculo.chofer >> vehiculo.idSector >> vehiculo.disponible) 
		{
        
		    if (numVehiculos < 100) 
			{
            vehiculos[numVehiculos++] = vehiculo;

            // Solo agregar el vehículo al sector si no está ya en la lista
            bool vehiculoExistente = false;
                for (int i = 0; i < tamListas[vehiculo.idSector]; i++) 
			    {
                    if (strcmp(listasVehiculos[vehiculo.idSector][i].placa, vehiculo.placa) == 0) 
				    {
                        vehiculoExistente = true;
                        break;
                    }
               }
                if (!vehiculoExistente) 
			    {
                agregarVehiculoALista(vehiculo.idSector, vehiculo);
                }
           }
       }
       
        archivoVehiculos.close();
   }

    //Funcion para cargar los sectores del menu de gestión
    void cargarSectores() 
	{
        ifstream archivoSectores("sectores.txt");
        
        if (!archivoSectores) 
		{
            cout << "Archivo sectores.txt no encontrado. Creando archivo vacio.\n";
            ofstream("sectores.txt").close();
            return;
        }

        numSectores = 0; // Reiniciar lista de sectores
        Sector sector;
        
        while (archivoSectores >> sector.id) 
		{
            archivoSectores.ignore();
            archivoSectores.getline(sector.nombre, 30);
            
            if (numSectores < 10) 
			{
            sectores[numSectores++] = sector;
            }
       }
       
        archivoSectores.close();
   }


    //Funcion para guardar los usuarios del menu de gestión
    void guardarUsuarios() 
	{
        ofstream archivoUsuarios("usuarios.txt");
        
        if (!archivoUsuarios) 
		{
            cout << "Error al abrir usuarios.txt para guardar.\n";
            return;
        }
        
        for (int i = 0; i < numUsuarios; i++) 
		{
            archivoUsuarios << usuarios[i].cedula << " " << usuarios[i].nombre << "\n";
        }
        
        archivoUsuarios.close();
    }
    //Funcion para guardar los vehiculos del menu de gestión
    void guardarVehiculos() 
	{
        ofstream archivoVehiculos("vehiculos.txt");
        
        if (!archivoVehiculos) 
		{
            cout << "Error al abrir vehiculos.txt para guardar.\n";
            return;
        }
        
		for (int i = 0; i < numVehiculos; i++) 
		{
            archivoVehiculos << vehiculos[i].placa << " " << vehiculos[i].modelo << " "
                         << vehiculos[i].marca << " " << vehiculos[i].anio << " "
                         << vehiculos[i].chofer << " " << vehiculos[i].idSector << " "
                         << vehiculos[i].disponible << "\n";
       }
       
        archivoVehiculos.close();
    }
     
	//Funcion para guardar los sectores del menu de gestión
    void guardarSectores() 
	{
        ofstream archivoSectores("sectores.txt");
        if (!archivoSectores) 
		{
            cout << "Error al abrir sectores.txt para guardar.\n";
            return;
        }
        
        for (int i = 0; i < numSectores; i++) 
		{
            archivoSectores << sectores[i].id << " " << sectores[i].nombre << "\n";
        }
        
        archivoSectores.close();
   }

    //Funcion para verificar la cola de espera del menu de servicio diario
    void verificarColaEspera(int idSector) 
	{
        if (tamColas[idSector] == 0) 
		{
            cout << "No hay usuarios en la cola de espera para el sector " << idSector << ".\n";
            return;
        }

        Usuario usuario = colasEspera[idSector][0];
        cout << "Usuario en cola: " << usuario.nombre << " (Cedula: " << usuario.cedula << ").\n";
        char respuesta;
        cout << "\xbf Aun necesita el traslado? (S/N): ";
        cin >> respuesta;

        if (toupper(respuesta) == 'S') 
		{
            if (tamListas[idSector] > 0) 
			{
                Vehiculo vehiculo = listasVehiculos[idSector][0];
                cout << "Vehiculo asignado: " << vehiculo.placa << " (" << vehiculo.modelo << ").\n";
                eliminarPrimeroCola(idSector);
                eliminarPrimeroLista(idSector);
                
            } else {
                cout << "No hay vehiculos disponibles en el sector.\n";
            }
            
        } else {
            eliminarPrimeroCola(idSector);
            cout << "Usuario retirado de la cola.\n";
        }
    }
    
    //Funcion para agregar vehiculos a la lista de vehiculos por sectores del menu de servicio diario
    void agregarVehiculoALista(int idSector, Vehiculo vehiculo) 
	{
        if (tamListas[idSector] < 100) 
		{
            listasVehiculos[idSector][tamListas[idSector]] = vehiculo;
            tamListas[idSector]++;
            ordenarListaPorAnio(idSector);
            
        } else {
            cout << "La lista de vehiculos del sector " << idSector << " esta llena.\n";
        }
    }
    
	//Funcion para cambiar de sector los vehiculos del menu de servicio diario
    void cambiarSectorVehiculo() 
	{
        char placa[10];
        int nuevoSector;
        cout << "Ingrese la placa del vehiculo: ";
        cin >> placa;
        cout << "Ingrese el ID del nuevo sector(Sectores del 1 al 9): ";
        cin >> nuevoSector;

        bool vehiculoEncontrado = false;
        for (int i = 0; i < numVehiculos; i++) 
		{
            if (strcmp(vehiculos[i].placa, placa) == 0) 
			{
                int sectorActual = vehiculos[i].idSector;
                vehiculos[i].idSector = nuevoSector;
                agregarVehiculoALista(nuevoSector, vehiculos[i]);
                eliminarPrimeroLista(sectorActual);
                vehiculoEncontrado = true;
                cout << "Vehiculo movido al sector " << nuevoSector << ".\n";

                if (tamColas[nuevoSector] > 0) 
				{
                    cout << "Hay usuarios en la cola de espera del sector " << nuevoSector << ".\n";
                    verificarColaEspera(nuevoSector);
                }
                break;
            }
        }

        if (!vehiculoEncontrado) 
		{
            cout << "Vehiculo no encontrado.\n";
        }
    }
    
    //Funcion para ordenar los sectores de la lista de vehiculos por año del vehiculo en el menu de servicios diario
    void ordenarListaPorAnio(int idSector) 
	{
        for (int i = 0; i < tamListas[idSector] - 1; i++) 
		{
            for (int j = i + 1; j < tamListas[idSector]; j++) 
			{
                if (listasVehiculos[idSector][i].anio < listasVehiculos[idSector][j].anio) 
				{
                    Vehiculo temp = listasVehiculos[idSector][i];
                    listasVehiculos[idSector][i] = listasVehiculos[idSector][j];
                    listasVehiculos[idSector][j] = temp;
                }
            }
        }
    }
    
    //Funcion ahora si para listar vehiculos jsjsjsj en el menu de servicios diario
    void listarVehiculos(int idSector) 
	{
        if (tamListas[idSector] == 0) 
		{
            cout << "No hay vehiculos disponibles en el sector " << idSector << ".\n";
            return;
        }
        
        cout << "Vehiculos disponibles en el sector " << idSector << ":\n";
        
        for (int i = 0; i < tamListas[idSector]; i++) 
		{
            Vehiculo vehiculo = listasVehiculos[idSector][i];
            cout << "Placa: " << vehiculo.placa << " | Modelo: " << vehiculo.modelo << " | Marca: " << vehiculo.marca << " | Anio: " << vehiculo.anio << "\n";
        }
    }
    
    //Funcion para eliminar usuarios de la cola de espera del sector en el menu de servicio diario
    void eliminarPrimeroCola(int idSector) 
	{
        for (int i = 1; i < tamColas[idSector]; i++) 
		{
            colasEspera[idSector][i - 1] = colasEspera[idSector][i];
        }
        
        tamColas[idSector]--;
    }
    
    //Funcion para eliminar vehiculos del sector en el que estaban en el menu de servicio diario
    void eliminarPrimeroLista(int idSector) 
	{
        for (int i = 1; i < tamListas[idSector]; i++) 
		{
            listasVehiculos[idSector][i - 1] = listasVehiculos[idSector][i];
        }
        
        tamListas[idSector]--;
    }

    template <typename T>
    
    T solicitarEntrada(const string& mensaje) 
	{
        T valor;
        while (true) 
		{
            cout << mensaje;
            cin >> valor;
            
            if (cin.fail()) 
			{
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida. Intente de nuevo.\n";
            } else {
                break;
            }
        }
        
        return valor;
    }
    
    //funcion para rectificar que del lado de cliente en la consola de comandos no dejen vacias respuestas 
    void solicitarCadena(const string& mensaje, char* destino, size_t longitud) 
    {
        cin.ignore();
        while (true) 
		{
            cout << mensaje;
            cin.getline(destino, longitud);
            
            if (strlen(destino) > 0) 
			{
                break;
            } else {
                cout << "La entrada no puede estar vacia. Intente de nuevo.\n";
            }
       }
   }
    
    //funcion para agregar usuarios a la cola de espera en el menu de servicio diario
    void agregarUsuarioACola(int idSector, Usuario usuario) 
	{
        if (idSector < 0 || idSector >= 10) 
		{
           cout << "ID de sector invalido. Intente nuevamente.\n";
           return;
        }

        if (tamColas[idSector] < 100)
		{
            colasEspera[idSector][tamColas[idSector]] = usuario;
            tamColas[idSector]++;
            cout << "Usuario agregado a la cola de espera del sector " << idSector << ".\n";
            
        } else {
            cout << "La cola de espera del sector " << idSector << " esta llena.\n";
        }
    }
    
    //Funcion para distribuir los vehiculos en los diferentes sectores del 1 al 9, en el menu se servicio diario
    void distribuirVehiculos() 
	{
        srand(time(0)); // Semilla para la aleatoriedad
        for (int i = 0; i < numVehiculos; i++) 
		{
            if (vehiculos[i].disponible) 
			{
               int sectorAleatorio = rand() % numSectores;
            
               // Solo asignar si el vehículo no está ya en el sector
               bool vehiculoExistente = false;
                for (int j = 0; j < tamListas[sectorAleatorio]; j++) 
				{
                    if (strcmp(listasVehiculos[sectorAleatorio][j].placa, vehiculos[i].placa) == 0) 
					{
                        vehiculoExistente = true;
                        break;
                    }
               }

               if (!vehiculoExistente) 
			   {
                vehiculos[i].idSector = sectores[sectorAleatorio].id;
                agregarVehiculoALista(sectorAleatorio, vehiculos[i]);
               }
           }
       }
       
    cout << "Vehiculos distribuidos aleatoriamente entre los sectores.\n";
   }

   //funcion para solicitar traslados de usuarios en los vehiculos en el menu de servicio diario
    void solicitarTraslado() {
        Usuario usuario;
        int sectorOrigen, sectorDestino;

        cout << "Ingrese cedula del usuario: ";
        cin >> usuario.cedula;
        cin.ignore(); // Ignorar salto de línea residual
        cout << "Ingrese nombre del usuario: ";
        cin.getline(usuario.nombre, 50);

        cout << "Ingrese ID del sector de origen(Sectores del 1 al 9): ";
        cin >> sectorOrigen;
        cout << "Ingrese ID del sector de destino(Sectores del 1 al 9): ";
        cin >> sectorDestino;

        // Validar sectores
        if (sectorOrigen < 0 || sectorOrigen >= 10 || sectorDestino < 0 || sectorDestino >= 10) 
		{
            cout << "Sector invalido. Por favor verifique los datos.\n";
            return;
        }

        // Si no hay vehículos en el sector de origen
        if (tamListas[sectorOrigen] == 0) 
		{
           cout << "No hay vehiculos disponibles en el sector de origen. El usuario sera aniadido a la cola de espera.\n";
           agregarUsuarioACola(sectorOrigen, usuario);
           return;
       }

       // Mostrar vehículos disponibles
       cout << "Vehiculos disponibles en el sector " << sectorOrigen << ":\n";
       
	   for (int i = 0; i < tamListas[sectorOrigen]; i++) 
	   {
            Vehiculo vehiculo = listasVehiculos[sectorOrigen][i];
            cout << i + 1 << ". Placa: " << vehiculo.placa
                 << " | Modelo: " << vehiculo.modelo
                 << " | Anio: " << vehiculo.anio << "\n";
       }

       // Seleccionar vehículo
       int seleccion;
       cout << "Seleccione un vehiculo (1 a " << tamListas[sectorOrigen] << "): ";
       cin >> seleccion;

       if (seleccion < 1 || seleccion > tamListas[sectorOrigen]) 
	   {
           cout << "Seleccion invalida.\n";
           return;
        }

        // Realizar el traslado
        Vehiculo& vehiculo = listasVehiculos[sectorOrigen][seleccion - 1];
        vehiculo.disponible = false;
        vehiculo.idSector = sectorDestino;

        agregarVehiculoALista(sectorDestino, vehiculo);
        eliminarVehiculoDeLista(sectorOrigen, seleccion - 1);

        cout << "Traslado realizado exitosamente. Vehiculo " << vehiculo.placa << " asignado.\n";
   }
    
    //funcion para eliminar vehiculos de la lista por repación, se que no estaba en lo que se pedia pero me gusto el proyecto y lo añadi para que agarrase forma en el menu de servicio diario
    void eliminarVehiculoDeLista(int sector, int indice) 
	{
        // Mueve los vehículos a la izquierda para eliminar el seleccionado
        for (int i = indice; i < tamListas[sector] - 1; i++)  
	    {
            listasVehiculos[sector][i] = listasVehiculos[sector][i + 1];
        }
        
        tamListas[sector]--;
   }
    
    //funcion para finalizar los traslados y dejar vehiculos disponibles en el menu se servicio diarios
	void finalizarTraslado() 
	{
        char placa[10];
        
        cout << "Ingrese la placa del vehiculo para finalizar el traslado: ";
        cin >> placa;

        for (int i = 0; i < numVehiculos; i++) 
		{
            if (strcmp(vehiculos[i].placa, placa) == 0) 
			{
                vehiculos[i].disponible = true;
                cout << "Traslado finalizado. Vehiculo ahora esta disponible nuevamente.\n";
                return;
           }
       }
       
    cout << "Vehiculo no encontrado.\n";
   }

   //funcion para eliminar vehiculos de los sectores en dado caso de una averia o reparación, esto es para el menu de servicio diario  
   void eliminarVehiculoDeSector() {
        char placa[10];
        int idSector;

        cout << "Ingrese el ID del sector del cual desea eliminar el vehiculo(Sectores del 1 al 9): ";
        cin >> idSector;

        if (idSector < 0 || idSector >= 10) 
		{
            cout << "Sector invalido. Intente nuevamente.\n";
            return;
        }

        // Buscar placa del vehículo
        cout << "Ingrese la placa del vehiculo a eliminar: ";
        cin >> placa;

        // Buscar el vehículo en la lista del sector
        bool vehiculoEncontrado = false;
       for (int i = 0; i < tamListas[idSector]; i++) 
	   {
          if (strcmp(listasVehiculos[idSector][i].placa, placa) == 0) 
		  {
            // Vehículo encontrado, eliminarlo
            for (int j = i; j < tamListas[idSector] - 1; j++) 
			{
                listasVehiculos[idSector][j] = listasVehiculos[idSector][j + 1]; // Mover vehículos a la izquierda
            }
            
            tamListas[idSector]--; // Reducir el tamaño de la lista
            vehiculoEncontrado = true;
            cout << "Vehiculo con placa " << placa << " eliminado correctamente del sector " << idSector << ".\n";
            break;
          }
       }

       if (!vehiculoEncontrado) 
	   {
        cout << "Vehiculo no encontrado en el sector " << idSector << ".\n";
       }
   }
    
    //funcion para generar un reporte para verificar que se este cumpliendo con los objetivos propuestos y demas funcionalidades del programa, reviselo profe es importante att: Kevin Zambrano, menu de servicio diario
    void generarReporteDiario() 
	{
        ofstream reporte("reporte_diario.txt");
        if (!reporte) 
		{
        cout << "Error al crear el archivo de reporte.\n";
        return;
        }

        reporte << "**** Reporte Diario ****\n";

        // Estadísticas de vehículos
        reporte << "\nVehículos más usados:\n";
        for (int i = 0; i < numVehiculos; i++) 
	    {
            reporte << "Placa: " << vehiculos[i].placa
                    << " | Modelo: " << vehiculos[i].modelo
                    << " | Marca: " << vehiculos[i].marca
                    << " | Disponible: " << (vehiculos[i].disponible ? "Sí" : "No") << "\n";
       }

        // Estadísticas de usuarios
        reporte << "\nUsuarios frecuentes:\n";
        for (int i = 0; i < numUsuarios; i++) 
		{
            reporte << "Cédula: " << usuarios[i].cedula
                 << " | Nombre: " << usuarios[i].nombre << "\n";
        }   

        reporte << "\nResumen de operaciones:\n";
        reporte << "Total de usuarios: " << numUsuarios << "\n";
        reporte << "Total de vehículos: " << numVehiculos << "\n";
        reporte << "Total de sectores: " << numSectores << "\n";

        reporte.close();
        cout << "Reporte diario generado en 'reporte_diario.txt'.\n";
   }

    //Funcion para que el programa sea mas bonito
    void limpiarConsola() {
        #ifdef _WIN32
        system("cls"); // Comando para limpiar la consola en Windows
        #else
        system("clear"); // Comando para limpiar la consola en Unix/Linux/Mac
        #endif
    }
    
    //Funcion para que el programa sea mas bonito
    void pausarConsola() {
        cout << "\nPresione Enter para continuar...";
        cin.ignore(); // Limpia cualquier entrada previa
        cin.get();    // Espera a que el usuario presione Enter
    }
    
    //Funcion para que se inicialize el menu de gestion
    void menuGestion() {
        int opcion;
        do {
            limpiarConsola();
            cout << "\n--- Menu de Gestion ---\n";
            cout << "1. Agregar Usuario\n";
            cout << "2. Agregar Vehiculo\n";
            cout << "3. Agregar Sector\n";
            cout << "4. Salir\n";
            opcion = solicitarEntrada<int>("Seleccione una opcion: ");

            limpiarConsola();

            switch (opcion) {
                case 1: {
                    Usuario usuario;
                    usuario.cedula = solicitarEntrada<int>("Ingrese cedula del usuario: ");
                    solicitarCadena("Ingrese nombre del usuario: ", usuario.nombre, 50);
                    usuarios[numUsuarios++] = usuario;
                    guardarUsuarios();
                    break;
                }
                case 2: {
                    Vehiculo vehiculo;
                    solicitarCadena("Ingrese placa del vehiculo: ", vehiculo.placa, 10);
                    solicitarCadena("Ingrese modelo del vehiculo: ", vehiculo.modelo, 30);
                    solicitarCadena("Ingrese marca del vehiculo: ", vehiculo.marca, 20);
                    vehiculo.anio = solicitarEntrada<int>("Ingrese anio del vehiculo: ");
                    solicitarCadena("Ingrese nombre del chofer: ", vehiculo.chofer, 50);
                    vehiculo.idSector = -1;
                    vehiculo.disponible = true;
                    vehiculos[numVehiculos++] = vehiculo;
                    guardarVehiculos();
                    break;
                }
                case 3: {
                    Sector sector;
                    sector.id = solicitarEntrada<int>("Ingrese ID del sector: ");
                    solicitarCadena("Ingrese nombre del sector: ", sector.nombre, 30);
                    sectores[numSectores++] = sector;
                    guardarSectores();
                    break;
                }
                case 4:
                    cout << "Saliendo del menu de gestion...\n";
                    break;
                default:
                    cout << "Opcion invalida. Intente de nuevo.\n";
                    break;
            }

            pausarConsola();

        } while (opcion != 4);
    }
    
    //Funcion para que se inicialize el menu de servicio diario
    void menuServicioDiario() {
	    cargarDatos();
	
        int opcion;
        do {
    	limpiarConsola();
        cout << "\n--- Menu de Servicio Diario ---\n";
        cout << "1. Distribuir Vehiculos\n";
        cout << "2. Solicitar Traslado\n";
        cout << "3. Finalizar Traslado\n";
        cout << "4. Verificar Cola de espera\n";
        cout << "5. Lista de Vehiculos\n";
        cout << "6. Eliminar Vehiculo de un Sector(Reparacion)\n";
        cout << "7. Cambiar Sector de Vehiculo\n";
        cout << "8. Generar Reporte Diario\n";
        cout << "9. Salir\n";
        opcion = solicitarEntrada<int>("Seleccione una opcion: ");
        
        limpiarConsola();

              switch (opcion) 
			  {
                case 1:
                    distribuirVehiculos();
                    break;
                case 2:
                    solicitarTraslado();
                    break;
                case 3:
                    finalizarTraslado();
                    break;
                case 4:
            	     {
            	        int idSector = solicitarEntrada<int>("Ingrese ID del Sector(Sectores del 1 al 9): ");
                        verificarColaEspera(idSector);
                        break;
                    }
                case 5:
            	    {
            	        int idSector = solicitarEntrada<int>("Ingrese ID del Sector(Sectores del 1 al 9): ");
                        listarVehiculos(idSector);
                        break;
                    }
			    case 6:
                    eliminarVehiculoDeSector();
                    break;
			    case 7:
                    cambiarSectorVehiculo();
                    break;		    
                case 8:
                    generarReporteDiario();
                    break;
                case 9:
                    cout << "Saliendo del menu de servicio diario...\n";
                    break;
                default:
                    cout << "Opcion invalida. Intente nuevamente.\n";
                    break;
               }
            
        pausarConsola();
        
       } while (opcion != 9);
   }

   //Funcion para que se inicialize el menu principal
    void menuPrincipal() {
        int opcion;
        do {
            limpiarConsola();
            cout << "\n--- Menu Principal ---\n";
            cout << "1. Menu de Gestion\n";
            cout << "2. Menu de Servicio Diario\n";
            cout << "3. Salir\n";
            opcion = solicitarEntrada<int>("Seleccione una opcion: ");

            limpiarConsola();

            switch (opcion) {
                case 1:
                    menuGestion();
                    break;
                case 2:
                    menuServicioDiario();
                    break;
                case 3:
                    cout << "Saliendo del programa...\n";
                    break;
                default:
                    cout << "Opcion invalida. Intente de nuevo.\n";
                    break;
            }

            pausarConsola();

        } while (opcion != 3);
    }
};

//Obviamente aqui se ejecuta todo jsjsjsj, eso es todo profe disfrute el programa att: Kevin Zambrano
int main() {
    SpeedCar app;
    app.menuPrincipal();
    return 0;
}

