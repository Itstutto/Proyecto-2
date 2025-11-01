#include "ListaClientes1.h"
#include "ListaSolicitudesContratos.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"

ListaClientes1::ListaClientes1() : ListaPersonas() {}
ListaClientes1::~ListaClientes1() {}

void ListaClientes1::eliminarColaboradorHistorial(string id)
{
	NodoP* actual = primero;
	while (actual) {
		Persona* p = actual->getDato();
		if (p) {
			ListaSolicitudesContratos* historial = p->getHistorial();
			if (historial) {
				historial->clienteEliminado(id);
			}
		}
		actual = actual->getSig();
	}
}

string ListaClientes1::mostrarPersonas(int ver) {
	stringstream ss;
	int opcion = 1;

	ss << endl << "Clientes" << endl;
	NodoP* actual = primero;
	while (actual) {
		ss << "---------------------------------------------------------" << endl
            << opcion<<"). " << actual->getDato()->infoMenu() << endl;
		actual = actual->getSig();
		opcion++;
	}
	if (ver == 0) {
		ss << "---------------------------------------------------------" << endl
            <<opcion++<<"). Reporte de clientes" << endl
			<< "----------------------------------------------------------" << endl;
		ss << opcion++ << "). Agregar nuevo cliente" << endl
			<< "----------------------------------------------------------" << endl;
		ss << opcion++ << "). Eliminar cliente" << endl
			<< "----------------------------------------------------------" << endl;
	}
		ss << opcion << "). Salir" << endl
            << "----------------------------------------------------------" << endl
            << "Seleccione una opcion: ";

	return ss.str();
}

string ListaClientes1::generarReporteClientes() {
    stringstream ss;
    ss << "Reporte de Clientes por Cantidad de Contratos (Orden Descendente)" << endl;
    ss << "-----------------------------------------------------------------" << endl << endl;

    if (!primero) {
        ss << "No hay clientes registrados." << endl;
        return ss.str();
    }

    // --- PASO 1: ORDENAMIENTO POR BURBUJA CON PUNTERO ANTERIOR ---

    NodoP* anterior = nullptr;
    NodoP* actual;
    bool intercambioRealizado;

    // Bucle externo para las pasadas
    for (int i = 0; i < tam; i++) {
        anterior = nullptr; // Reinicia el puntero anterior para cada pasada
        actual = primero;
        intercambioRealizado = false;

        // Bucle interno para cada pasada, compara pares adyacentes
        while (actual != nullptr && actual->getSig() != nullptr) {

            NodoP* n1 = actual;          // Primer nodo del par
            NodoP* n2 = actual->getSig();  // Segundo nodo del par

            // Obtener el conteo de contratos para N1 y N2
            Cliente* cli1 = dynamic_cast<Cliente*>(n1->getDato());
            Cliente* cli2 = dynamic_cast<Cliente*>(n2->getDato());

            int count1 = 0;
            int count2 = 0;

            if (cli1 && cli1->getHistorial()) {
                cli1->getHistorial()->obtenerReporteContratosCliente(cli1->getId(), count1);
            }
            if (cli2 && cli2->getHistorial()) {
                cli2->getHistorial()->obtenerReporteContratosCliente(cli2->getId(), count2);
            }

            // Comparación para Orden Descendente (de mayor a menor)
            if (count1 < count2) { // Intercambio: n2 (mayor) se mueve antes que n1 (menor)

                // 1. Reenlazar n1 al sucesor de n2
                n1->setSig(n2->getSig());
                // 2. Reenlazar n2 a n1
                n2->setSig(n1);

                // 3. Actualizar el puntero que apuntaba a n1 (anterior) o la cabeza (primero)
                if (anterior == nullptr) {
                    primero = n2;
                }
                else {
                    anterior->setSig(n2);
                }

                // 4. Actualizar punteros para el avance (la nueva pareja a revisar)
                //    - El nuevo 'anterior' (predecesor del par intercambiado) es n2.
                //    - El nuevo 'actual' (inicio del siguiente par) es n1->getSig() (el nodo que seguía a n2)
                anterior = n2;
                actual = n1->getSig();

                intercambioRealizado = true;

            }
            else {
                // NO intercambio: Avanzamos los punteros normalmente
                anterior = n1;
                actual = n2; // Avanza al siguiente nodo
            }
        }

        // Optimización: si no hubo intercambios en una pasada, la lista está ordenada
        if (!intercambioRealizado) break;
    }


    // --- PASO 2: GENERACIÓN DEL REPORTE FINAL (SOBRE LA LISTA ORDENADA) ---
    NodoP* actualReporte = primero;
    int rank = 1;

    while (actualReporte) {
        Persona* p = actualReporte->getDato();
        if (p) {
            Cliente* c = dynamic_cast<Cliente*>(p);
            if (c) {
                int contratosCount = 0;
                string contratosCodes = "";
                if (c->getHistorial()) {
                    contratosCodes = c->getHistorial()->obtenerReporteContratosCliente(c->getId(), contratosCount);
                }

                ss << rank++ << "). Cliente: " << c->getNombre() << endl;
                ss << "   -> ID: " << c->getId() << endl;
                ss << "   -> Cantidad de Contratos (Estado 2): " << contratosCount << endl;
                ss << "   -> Códigos de Contratos: [" << (contratosCodes.empty() ? "Ninguno" : contratosCodes) << "]" << endl;
                ss << "-----------------------------------------------------------------" << endl;
            }
        }
        actualReporte = actualReporte->getSig();
    }

    return ss.str();
}
