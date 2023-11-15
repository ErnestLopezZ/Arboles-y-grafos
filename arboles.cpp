#include <iostream>
using namespace std;

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

                    cout << "Máximo valor en el árbol: " << maximo << endl;
                    cout << "Promedio de los valores en el árbol: " << promedio << endl;
                } else {
                    cout << "El árbol está vacío." << endl;
                }
                break;
            case 9:
                cout << "Información de las hojas:" << endl;
                imprimirHojas(raiz, true);
                break;
            case 10:
                cout << "Información de los nodos internos:" << endl;
                imprimirNodosInternos(raiz, true);
                break;
            case 11: 
                cout << "Agregando la familia de carlos: " << endl;
                raiz = CreaArbol(true);
                infijo(raiz,true);
            case 12: 
                menuAVL();
                break;
                
            case 0:
                cout << endl << "Hasta luego!!" << endl;
                break;
        }
    } while (op != 0);

    // Limpieza de memoria: se debe liberar la memoria utilizada por el árbol.
    // Puedes agregar la lógica para hacerlo aquí.
    
    return 0;
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
        // Si el árbol está vacío, puedes devolver un valor que indique que no hay máximo
        // En este caso, devolvemos un valor que no debería ser alcanzado por los valores reales del árbol
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
            cout << "La información ya se encuentra en el árbol" << endl;
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
        cout << "La información no se encuentra en el árbol" << endl;
    }
}





void menuAVL(){
    TNodo* raiz = NULL;
    bool altura_crecida = false;
    bool altura_disminuida = false;
    int op, dato;

    do {
        cout << endl << "1...Insertar elemento en el árbol balanceado";
        cout << endl << "2...Eliminar elemento en el árbol balanceado";
        cout << endl << "3...Imprimir arbol AVL";
        cout << endl << "Selecciona tu opción: ";
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
            default:
                cout << "Opción no válida. Inténtalo de nuevo." << endl;
                break;
        }
    } while (op != 0);

}


