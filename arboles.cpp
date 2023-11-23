#include <iostream>
#include <limits>
#include <climits> 
#include <string>
#include <algorithm>

using namespace std;
#define INF INT_MAX
struct TNodo {
   int info;
   int FE;
   string informacion;
   TNodo *izq, *der;
};

void menuAVL();
TNodo* crea(int dato);
TNodo* crea(string dato);
TNodo* CreaArbol(bool FamiliaCarlos);
void prefijo(TNodo* raiz);
void infijo(TNodo* raiz, bool FamiliaCarlos);
void posfijo(TNodo* raiz);
void buscar(TNodo *raiz,int dato);
int contarNodos(TNodo* raiz);
int contarNodosInternos(TNodo* raiz);
int encontrarMaximo(TNodo* raiz);
int calcularSuma(TNodo* raiz);
void imprimirHojas(TNodo* raiz, bool esRaizPrincipal = true);
void imprimirNodosInternos(TNodo* raiz, bool esRaizPrincipal = true);
void Inserta_balanceado(TNodo* &NODO, bool &BO, int INFOR);
void Reestructura_izq(TNodo* &NODO, bool &BO);
void Reestructura_der(TNodo* &NODO, bool &BO);
void Elimina_balanceado(TNodo* &NODO, bool &BO, int INFOR);
//grafos
void grafos();
void imprimirMatriz(int** matriz, int n);
void dijkstra(int** grafo, int n, int inicio);
void floyd(int** grafo, int n);
void warshall(int** grafo, int n);
void liberarArbol(TNodo* nodo);



//Luis Ernesto Lopez Cardenas ISC 3A

int main() {
    TNodo* raiz = NULL;
    int op,dato;
    do {
        cout << endl << "1...Cargar el arbol a memoria";
        cout << endl << "2...Recorrido prefijo";
        cout << endl << "3...Recorrido infijo";
        cout << endl << "4...Recorrido posfijo";
        cout << endl << "5...Buscar dato dentro del arbol";
        cout << endl << "6...Contar nodos del arbol binario";
        cout << endl << "7...Contar nodos internos del arbol";
        cout << endl << "8...Maximo valor del arbol y promedio";
        cout << endl << "9...Imprimir informacion de las hojas";
        cout << endl << "10..Imprimir informacion de los Internos";
        cout << endl << "11..Agregar familia de carlos";
        cout << endl << "12. Arboles AVL";
        cout << endl << "13. Grafos";
        cout << endl << "0...Salir";
        cout << endl << "Selecciona tu opcion: ";
        cin >> op;
        switch (op) {
            case 1:
                raiz = CreaArbol(false);
                break;
            case 2:
                prefijo(raiz);
                cout << endl;
                break;
            case 3:
                infijo(raiz,false);
                cout << endl;
                break;
            case 4:
                posfijo(raiz);
                cout << endl;
                break;
            case 5:
                cout << "Dame el dato que deseas buscar dentro del arbol: " << endl;
                cin >> dato;
                buscar(raiz,dato);
                break;
            case 6: 
                cout << "El arbol tiene " << contarNodos(raiz) << " nodos." << endl;
                break;
            case 7: 
                cout << "El arbol tiene " << contarNodosInternos(raiz) << " nodos internos." << endl;
                break;
            case 8: 
                if (raiz != NULL) {
                    int maximo = encontrarMaximo(raiz);
                    int suma = calcularSuma(raiz);
                    int cantidadNodos = contarNodos(raiz);
                    double promedio = cantidadNodos == 0 ? 0 : suma / (1.0 * cantidadNodos);

                    cout << "Maximo valor en el arbol: " << maximo << endl;
                    cout << "Promedio de los valores en el arbol: " << promedio << endl;
                } else {
                    cout << "El arbol esta vacio." << endl;
                }
                break;
            case 9:
                cout << "Informacion de las hojas:" << endl;
                imprimirHojas(raiz, true);
                break;
            case 10:
                cout << "Informacion de los nodos internos:" << endl;
                imprimirNodosInternos(raiz, true);
                break;
            case 11: 
                cout << "Agregando la familia de carlos: " << endl;
                raiz = CreaArbol(true);
                infijo(raiz,true);
            case 12: 
                menuAVL();
                break;
            case 13:
                grafos();
                break;
                
            case 0:
                cout << endl << "Hasta luego!!" << endl;
                break;
        }
    } while (op != 0);

    liberarArbol(raiz);
   
    
    return 0;
}

void liberarArbol(TNodo* nodo) {
    if (nodo == NULL) {
        return;
    }

    liberarArbol(nodo->izq);
    liberarArbol(nodo->der);
    delete nodo;
}

TNodo* crea(int dato) {
    TNodo* nuevo = new TNodo;
    nuevo->info = dato;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}
TNodo* crea(string dato) {
    TNodo* nuevo = new TNodo;
    nuevo->informacion = dato;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

TNodo* CreaArbol(bool FamiliaCarlos) {
    TNodo* raiz;
    int dato;
    string nombre;
    cout << "Dato para el arbol (0 para terminar): ";
    if(FamiliaCarlos ==false){
        cin >> dato;
    }
    else{
        fflush(stdin);
         getline(cin, nombre);
         fflush(stdin);
    }
    if (dato == 0 || nombre == "0") {
        return NULL;
    }
    if(FamiliaCarlos == false){
         raiz = crea(dato);
    }
    else{
         raiz = crea(nombre);
    }
    
    if(FamiliaCarlos== false){
        cout << "Existe Nodo por la IZQUIERDA 1=si: ";
    }
    else{
        cout << "Continua familia de parte de la Madre 1=si";
    }
    int resp;
    cin >> resp;
    if (resp == 1) {
        if(FamiliaCarlos == false){
            raiz->izq = CreaArbol(false);
        }
        else{
            raiz->izq = CreaArbol(true);
        }
        
    }
    if(FamiliaCarlos == false){
         cout << "Existe Nodo por la DERECHA 1=si: ";
    }
    else{
        cout << "Continua Familia por parte del Padre 1=si: ";
    }
    cin >> resp;
    if (resp == 1) {
        if(FamiliaCarlos == false){
             raiz->der = CreaArbol(false);
        }
        else{
             raiz->der = CreaArbol(true);
        }
    }
    return raiz;
}

void prefijo(TNodo* raiz) {

    int cont;
    if (raiz != NULL) {
        cout << raiz->info << "-";
        prefijo(raiz->izq);
        prefijo(raiz->der);
    }

}

void infijo(TNodo* raiz, bool FamiliaCarlos) {
    if (raiz != NULL) {
        if(FamiliaCarlos == false){
             infijo(raiz->izq, false);
             cout << raiz->info << "-";
        }
        else{
              infijo(raiz->izq, true);
              cout << raiz->informacion << "-";
        }
        if(FamiliaCarlos == false){
            infijo(raiz->der, false);
        }
        else{
            infijo(raiz->der, true);
        }
       
    }
}

void posfijo(TNodo* raiz) {
    if (raiz != NULL) {
        posfijo(raiz->izq);
        posfijo(raiz->der);
        cout << raiz->info << "-";
    }
}

void buscar(TNodo *raiz,int dato){
    if(raiz!=NULL){
        if(dato<raiz->info){
            buscar(raiz->der,dato);
        }else{
            if(dato > raiz->info){
                buscar(raiz->izq,dato);
            }
            else{
                cout << "Dato encontrado en el arbol" << endl;
            }
        }

    }
    else{
        cout << endl << "Dato no encontrado" << endl;
    }
}
int contarNodos(TNodo* raiz) {
  
    if (raiz == NULL) {
        return 0;
    }

    int contadorRaiz = 1;
    int contadorIzquierda = contarNodos(raiz->izq);
    int contadorDerecha = contarNodos(raiz->der);
    return contadorRaiz + contadorIzquierda + contadorDerecha;
}

/*int contarNodos(TNodo* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
    
}*/

int contarNodosInternos(TNodo* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    
    if (raiz->izq == NULL && raiz->der == NULL) {
        return 0;
    }

    return 1 + contarNodosInternos(raiz->izq) + contarNodosInternos(raiz->der);
}

int encontrarMaximo(TNodo* raiz) {
    if (raiz == NULL) {
        
        return -1; 
    }

    int maximo = raiz->info;

    int maxIzq = encontrarMaximo(raiz->izq);
    int maxDer = encontrarMaximo(raiz->der);

    if (maxIzq > maximo) {
        maximo = maxIzq;
    }

    if (maxDer > maximo) {
        maximo = maxDer;
    }

    return maximo;
}

// Función para calcular la suma de los valores en el árbol

int calcularSuma(TNodo* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    int sumaRaiz = raiz->info;
    int sumaIzquierda = calcularSuma(raiz->izq);
    int sumaDerecha = calcularSuma(raiz->der);
    return sumaRaiz + sumaIzquierda + sumaDerecha;
}

/*int calcularSuma(TNodo* raiz) {
    if (raiz == NULL) {
        return 0;
    }

    return raiz->info + calcularSuma(raiz->izq) + calcularSuma(raiz->der);
}*/

void imprimirHojas(TNodo* raiz, bool esRaizPrincipal) {
    if (raiz != NULL) {
        if (raiz->izq == NULL && raiz->der == NULL && !esRaizPrincipal) {
            cout << "Hoja: " << raiz->info << endl;
        } else {
            imprimirHojas(raiz->izq, false);
            imprimirHojas(raiz->der, false);
        }
    }
}


void imprimirNodosInternos(TNodo* raiz, bool esRaizPrincipal) {
    if (raiz != NULL) {
        if (raiz->izq != NULL || raiz->der != NULL) {
            if (!esRaizPrincipal) {
                cout << "Nodo interno: " << raiz->info << endl;
            }
        }

        imprimirNodosInternos(raiz->izq, false);
        imprimirNodosInternos(raiz->der, false);
    }
}

void Inserta_balanceado(TNodo* &NODO, bool &BO, int INFOR) {
    TNodo *OTRO, *NODO1, *NODO2;
    
    if (NODO == NULL) {
        NODO = new TNodo;
        NODO->info = INFOR;
        NODO->FE = 0;
        NODO->izq = NODO->der = NULL;
        BO = true;
    } else {
        if (INFOR < NODO->info) {
            Inserta_balanceado(NODO->izq, BO, INFOR);
            
            if (BO == true) {
                switch (NODO->FE) {
                    case 1:
                        NODO->FE = 0;
                        BO = false;
                        break;
                    case 0:
                        NODO->FE = -1;
                        break;
                    case -1:
                        NODO1 = NODO->izq;
                        if (NODO1->FE == -1) {
                            NODO->izq = NODO1->der;
                            NODO1->der = NODO;
                            NODO->FE = 0;
                            NODO = NODO1;
                        } else {
                            NODO2 = NODO1->der;
                            NODO1->der = NODO2->izq;
                            NODO2->izq = NODO1;
                            NODO->izq = NODO2->der;
                            NODO2->der = NODO;
                            if (NODO2->FE == -1) {
                                NODO->FE = 1;
                            } else {
                                NODO->FE = 0;
                            }
                            if (NODO2->FE == 1) {
                                NODO1->FE = -1;
                            } else {
                                NODO1->FE = 0;
                            }
                            NODO = NODO2;
                        }
                        NODO->FE = 0;
                        BO = false;
                        break;
                }
            }
        } else if (INFOR > NODO->info) {
            Inserta_balanceado(NODO->der, BO, INFOR);
            
            if (BO == true) {
                switch (NODO->FE) {
                    case -1:
                        NODO->FE = 0;
                        BO = false;
                        break;
                    case 0:
                        NODO->FE = 1;
                        break;
                    case 1:
                        NODO1 = NODO->der;
                        if (NODO1->FE == 1) {
                            NODO->der = NODO1->izq;
                            NODO1->izq = NODO;
                            NODO->FE = 0;
                            NODO = NODO1;
                        } else {
                            NODO2 = NODO1->izq;
                            NODO1->izq = NODO2->der;
                            NODO2->der = NODO1;
                            NODO->der = NODO2->izq;
                            NODO2->izq = NODO;
                            if (NODO2->FE == 1) {
                                NODO->FE = -1;
                            } else {
                                NODO->FE = 0;
                            }
                            if (NODO2->FE == -1) {
                                NODO1->FE = 1;
                            } else {
                                NODO1->FE = 0;
                            }
                            NODO = NODO2;
                        }
                        NODO->FE = 0;
                        BO = false;
                        break;
                }
            }
        } else {
            cout << "La informacion ya se encuentra en el arbol" << endl;
            BO = false;
        }
    }
}

void Reestructura_izq(TNodo* &NODO, bool &BO) {
    TNodo *NODO1, *NODO2;
    
    if (BO == true) {
        switch (NODO->FE) {
            case -1:
                NODO->FE = 0;
                break;
            case 0:
                NODO->FE = 1;
                BO = false;
                break;
            case 1: // Reestructuración del árbol
                NODO1 = NODO->der;
                if (NODO1->FE == 0) { // Rotación DD
                    NODO->der = NODO1->izq;
                    NODO1->izq = NODO;
                    NODO->FE = 1;
                    NODO1->FE = -1;
                    BO = false;
                } else if (NODO1->FE == 1) {
                    NODO->FE = 0;
                    NODO1->FE = 0;
                    BO = false;
                } else { // Rotación DI
                    NODO2 = NODO1->izq;
                    NODO->der = NODO2->izq;
                    NODO2->izq = NODO;
                    NODO1->izq = NODO2->der;
                    NODO2->der = NODO1;
                    if (NODO2->FE == 1) {
                        NODO->FE = -1;
                    } else {
                        NODO->FE = 0;
                    }
                    if (NODO2->FE == -1) {
                        NODO1->FE = 1;
                    } else {
                        NODO1->FE = 0;
                    }
                    NODO = NODO2;
                    NODO->FE = 0;
                    BO = false;
                }
                break;
        }
    }
}

void Reestructura_der(TNodo* &NODO, bool &BO) {
    TNodo *NODO1, *NODO2;

    if (BO == true) {
        switch (NODO->FE) {
            case 1:
                NODO->FE = 0;
                break;
            case 0:
                NODO->FE = -1;
                BO = false;
                break;
            case -1: // Reestructuración del árbol
                NODO1 = NODO->izq;
                if (NODO1->FE == 0) { // Rotación II
                    NODO->izq = NODO1->der;
                    NODO1->der = NODO;
                    NODO->FE = -1;
                    NODO1->FE = 1;
                    BO = false;
                } else if (NODO1->FE == -1) {
                    NODO->FE = 0;
                    NODO1->FE = 0;
                    BO = false;
                } else { // Rotación ID
                    NODO2 = NODO1->der;
                    NODO->izq = NODO2->der;
                    NODO2->der = NODO;
                    NODO1->der = NODO2->izq;
                    NODO2->izq = NODO1;
                    if (NODO2->FE == -1) {
                        NODO->FE = 1;
                    } else {
                        NODO->FE = 0;
                    }
                    if (NODO2->FE == 1) {
                        NODO1->FE = -1;
                    } else {
                        NODO1->FE = 0;
                    }
                    NODO = NODO2;
                    NODO->FE = 0;
                    BO = false;
                }
                break;
        }
    }
}
void Elimina_balanceado(TNodo* &NODO, bool &BO, int INFOR) {
    TNodo *OTRO, *AUX, *AUX1;
    bool BOOL = false;

    if (NODO != NULL) {
        if (INFOR < NODO->info) {
            Elimina_balanceado(NODO->izq, BO, INFOR);
            Reestructura_izq(NODO, BO);
        } else if (INFOR > NODO->info) {
            Elimina_balanceado(NODO->der, BO, INFOR);
            Reestructura_der(NODO, BO);
        } else {
            OTRO = NODO;
            BO = true;

            if (OTRO->der == NULL) {
                NODO = OTRO->izq;
            } else if (OTRO->izq == NULL) {
                NODO = OTRO->der;
            } else {
                AUX = OTRO->izq;
                BOOL = false;

                while (AUX->der != NULL) {
                    AUX1 = AUX;
                    AUX = AUX->der;
                    BOOL = true;
                }

                NODO->info = AUX->info;
                OTRO = AUX;

                if (BOOL == true) {
                    AUX1->der = AUX->izq;
                } else {
                    NODO->izq = AUX->izq;
                }
                Reestructura_der(NODO->izq, BO);
            }
            delete OTRO;
        }
    } else {
        cout << "La informacion no se encuentra en el arbol" << endl;
    }
}





void menuAVL(){
    TNodo* raiz = NULL;
    bool altura_crecida = false;
    bool altura_disminuida = false;
    int op, dato;

    do {
        cout << endl << "1...Insertar elemento en el arbol balanceado";
        cout << endl << "2...Eliminar elemento en el arbol balanceado";
        cout << endl << "3...Imprimir arbol AVL";
        cout << endl << "0...Salir...";
        cout << endl << "Selecciona tu opcion: ";
        cin >> op;

        switch (op) {
            case 1:
                cout << "Ingresa el dato a insertar: ";
                cin >> dato;
                Inserta_balanceado(raiz, altura_crecida, dato);
                break;
            case 2:
                cout << "Ingresa el dato a eliminar: ";
                cin >> dato;
                Elimina_balanceado(raiz, altura_disminuida, dato);
                break;
            case 3:
                cout << "Imprimir arbol en infijo" << endl;
                infijo(raiz,false);
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                main();
                break;
            case 0:
                cout << "Adios" << endl;
                break;
        }
    } while (op != 0);
    liberarArbol(raiz);

}


void grafos() {
    int n;
    cout << "Ingrese la cantidad de nodos en el grafo: ";
    cin >> n;

    int** grafo = new int*[n];
    for (int i = 0; i < n; ++i) {
        grafo[i] = new int[n];
    }

    cout << "Ingrese la matriz de adyacencia para el grafo (coloque INF para representar infinito): " << endl;
    string valor;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> valor;

            transform(valor.begin(), valor.end(), valor.begin(), ::tolower); // Convertir a minúsculas

            if (valor == "inf") {
                grafo[i][j] = INF;
            } else {
                try {
                    grafo[i][j] = stoi(valor);
                } catch (invalid_argument const& e) {
                    cout << "Entrada invalida. Intente de nuevo." << endl;
                    j--;  // Retrocede un paso para volver a ingresar el valor
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            }
        }
    }


    int opcion;
    do {
        cout << "\nSeleccione una opcion:" << endl
             << "1. Algoritmo de Dijkstra" << endl
             << "2. Algoritmo de Floyd" << endl
             << "3. Algoritmo de Warshall" << endl
             << "0. Salir" << endl;

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intente de nuevo." << endl;
            continue;
        }

        switch (opcion) {
            case 1:
                int nodoInicio;
                cout << "Ingrese el nodo de inicio para el algoritmo de Dijkstra (0 a " << n - 1 << "): ";
                if (!(cin >> nodoInicio)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Entrada invalida. Intente de nuevo." << endl;
                    break;
                }
                dijkstra(grafo, n, nodoInicio);
                break;
            case 2:
                floyd(grafo, n);
                break;
            case 3:
                warshall(grafo, n);
                break;
            case 0:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
        }

        if (opcion < 0 || opcion > 3) {
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    // Liberar memoria
    for (int i = 0; i < n; ++i) {
        delete[] grafo[i];
    }
    delete[] grafo;
}

void imprimirMatriz(int** matriz, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << matriz[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

void dijkstra(int** grafo, int n, int inicio) {
    int* distancias = new int[n];
    bool* visitado = new bool[n];

    for (int i = 0; i < n; ++i) {
        distancias[i] = INF;
        visitado[i] = false;
    }

    distancias[inicio] = 0;

    for (int contador = 0; contador < n - 1; ++contador) {
        int distanciaMin = INF, indiceMin;

        for (int v = 0; v < n; ++v) {
            if (!visitado[v] && distancias[v] <= distanciaMin) {
                distanciaMin = distancias[v];
                indiceMin = v;
            }
        }

        int u = indiceMin;
        visitado[u] = true;

        for (int v = 0; v < n; ++v) {
            if (!visitado[v] && grafo[u][v] && distancias[u] != INF && distancias[u] + grafo[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + grafo[u][v];
            }
        }
    }

    cout << "Distancias mas cortas desde el nodo " << inicio << " usando el algoritmo de Dijkstra: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Nodo " << i << ": " << distancias[i] << endl;
    }

    delete[] distancias;
    delete[] visitado;
}

void floyd(int** grafo, int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grafo[i][k] != INF && grafo[k][j] != INF && grafo[i][k] + grafo[k][j] < grafo[i][j]) {
                    grafo[i][j] = grafo[i][k] + grafo[k][j];
                }
            }
        }
    }

    cout << "Distancias mas cortas usando el algoritmo de Floyd: " << endl;
    imprimirMatriz(grafo, n);
}

void warshall(int** grafo, int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grafo[i][k] != INF && grafo[k][j] != INF && (grafo[i][k] + grafo[k][j] < grafo[i][j])) {
                    grafo[i][j] = grafo[i][k] + grafo[k][j];
                }
            }
        }
    }

    cout << "Cierre transitivo usando el algoritmo de Warshall: " << endl;
    imprimirMatriz(grafo, n);
}
