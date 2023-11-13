#include <iostream>
using namespace std;

struct TNodo {
   int info;
   TNodo *izq, *der;
};

TNodo* crea(int dato) {
    TNodo* nuevo = new TNodo;
    nuevo->info = dato;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

TNodo* CreaArbol() {
    int dato;
    cout << "Dato para el arbol (0 para terminar): ";
    cin >> dato;
    if (dato == 0) {
        return NULL;
    }
    TNodo* raiz = crea(dato);
    cout << "Existe Nodo por la IZQUIERDA 1=si: ";
    int resp;
    cin >> resp;
    if (resp == 1) {
        raiz->izq = CreaArbol();
    }
    cout << "Existe Nodo por la DERECHA 1=si: ";
    cin >> resp;
    if (resp == 1) {
        raiz->der = CreaArbol();
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

void infijo(TNodo* raiz) {
    if (raiz != NULL) {
        infijo(raiz->izq);
        cout << raiz->info << "-";
        infijo(raiz->der);
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
        cout << endl << "0...Salir";
        cout << endl << "Selecciona tu opcion: ";
        cin >> op;
        switch (op) {
            case 1:
                raiz = CreaArbol();
                break;
            case 2:
                prefijo(raiz);
                cout << endl;
                break;
            case 3:
                infijo(raiz);
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
            case 0:
                cout << endl << "Hasta luego!!" << endl;
                break;
        }
    } while (op != 0);

    // Limpieza de memoria: se debe liberar la memoria utilizada por el árbol.
    // Puedes agregar la lógica para hacerlo aquí.
    
    return 0;
}
