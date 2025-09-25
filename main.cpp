#include <iostream>
#include <string>
#include <cstdio>
#include <limits>

// Constante global que indicara el tamaño maximo de los arreglos
const int maximos_Productos = 100;

// Inicializacion de los arreglos paralelos
int codigo_Productos[maximos_Productos];
std::string nombres_Productos[maximos_Productos];
int cantidad_Stock[maximos_Productos];
float precio_Unitario[maximos_Productos];
std::string codigo_Ubicacion[maximos_Productos];

// Contador de cuantos productos se llevan
int contador_Productos = 0;

int stock_Bajo = 10;

void cargarArchivo();

// Prototipos de funciones
void agregarProducto();
void consultarProducto();
void actualizarInventario();
void generarReporte();
void generarReporteStockBajo();
void buscarProductoMasCaro();
void buscarProductoMasBarato();
void modificarArchivo();

int main()
{
    // Inicializar los datos pŕincipales
    cargarArchivo();

    int opcion;
    do
    {
        std::cout << "--- SISTEMA DE INVENTARIO DE LA FERRETERIA EL MARTILLO --- \n";
        std::cout << "Seleccione una opción: \n";
        std::cout << "1. Agregar un Producto \n";
        std::cout << "2. Consultar un Producto \n";
        std::cout << "3. Actualizar el Inventario de un Producto \n";
        std::cout << "4. Generar Reporte de Productos \n";
        std::cout << "5. Generar Reporte de Productos de Bajo Stock \n";
        std::cout << "6. Buscar el Producto mas Caro \n";
        std::cout << "7. Buscar el Producto mas Barato \n";
        std::cout << "8. Salir \n";
        std::cout << "Opción Seleccionada: ";

        if (!(std::cin >> opcion))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nEntrada inválida. Debe ingresar un número.\n\n";
            continue;
        }

        switch (opcion)
        {
        case 1:
            agregarProducto();
            break;
        case 2:
            consultarProducto();
            break;
        case 3:
            actualizarInventario();
            break;
        case 4:
            generarReporte();
            break;
        case 5:
            generarReporteStockBajo();
            break;
        case 6:
            buscarProductoMasCaro();
            break;
        case 7:
            buscarProductoMasBarato();
            break;
        case 8:
            std::cout << "Bye bye\n";
            modificarArchivo();
            break;

        default:
            std::cout << "\nOpcion incorrecta. Intente de nuevo.\n";
            break;
        }
    } while (opcion != 8);

    return 0;
}

void agregarProducto()
{
    std::cout << "\n--- Agregar Nuevo Producto ---\n";

    if (contador_Productos >= maximos_Productos)
    {
        std::cout << "Error: El inventario está lleno. No se pueden agregar más productos.\n";
        return;
    }

    int codigo_Nuevo;
    std::cout << "Ingrese el código del nuevo producto: ";

    if (!(std::cin >> codigo_Nuevo))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n Ingresa un número\n\n";
    }

    for (int i = 0; i < contador_Productos; i++)
    {
        if (codigo_Productos[i] == codigo_Nuevo)
        {
            std::cout << "El código " << codigo_Nuevo << " ya existe en el inventario.\n\n";
            return;
        }
    }

    codigo_Productos[contador_Productos] = codigo_Nuevo;

    std::cout << "Ingrese el nombre del producto: ";
    std::cin.ignore();
    std::getline(std::cin, nombres_Productos[contador_Productos]);

    std::cout << "Ingrese la cantidad en stock: ";
    std::cin >> cantidad_Stock[contador_Productos];

    std::cout << "Ingrese el precio unitario: ";
    std::cin >> precio_Unitario[contador_Productos];

    std::cout << "Ingrese la ubicacion del producto (De preferencia que sea A-Numero): ";
    std::cin >> codigo_Ubicacion[contador_Productos];

    contador_Productos++;

    std::cout << "\n Se ha agregado el producto \n\n";
}

// Funcion para hacer la consulta de un producto
void consultarProducto()
{
    std::string ubicacion_Buscada;

    std::cout << "Ingrese la ubicacion del producto a buscar: ";
    std::cin >> ubicacion_Buscada;

    // Variable bandera para saber si se ha encontrado el producto
    bool producto_Encontrado = false;

    for (int i = 0; i < contador_Productos; i++)
    {
        if (codigo_Ubicacion[i] == ubicacion_Buscada)
        {
            std::cout << "\n ----- Información del Producto ----- \n";
            std::cout << "Código: " << codigo_Productos[i] << "\n";
            std::cout << "Nombre: " << nombres_Productos[i] << "\n";
            std::cout << "Cantidad en stock: " << cantidad_Stock[i] << "\n";
            std::cout << "Precio unitario: $" << precio_Unitario[i] << "\n\n";
            std::cout << "Ubicacion del producto: " << codigo_Ubicacion[i] << "\n\n";

            producto_Encontrado = true;
            break;
        }
    }

    if (!producto_Encontrado)
    {
        std::cout << "La ubicacion de producto " << ubicacion_Buscada << " no existe \n\n";
    }
}

// Funcion para actualizar el inventario de un producto
void actualizarInventario()
{
    std::string ubicacion_Buscada;

    std::cout << "Ingrese la ubicacion del producto a buscar: ";
    std::cin >> ubicacion_Buscada;

    bool producto_Encontrado = false;

    for (int i = 0; i < contador_Productos; i++)
    {
        if (codigo_Ubicacion[i] == ubicacion_Buscada)
        {
            int cantidad_Actualizar;
            std::cout << "El producto a actualizar es: " << nombres_Productos[i] << " \n";
            std::cout << "¿Cuál es la cantidad a sumar o restar (para restar poner un (-) antes del numero): ";
            std::cin >> cantidad_Actualizar;

            int nuevo_Stock = cantidad_Stock[i] + cantidad_Actualizar;

            if (nuevo_Stock >= 0)
            {
                cantidad_Stock[i] = nuevo_Stock;
                std::cout << "Inventario actualizado, el nuevo stock es: " << cantidad_Stock[i] << " \n\n";
            }
            else
            {
                std::cout << "Hay un error, el stock quedaria en negativo " << nuevo_Stock << " , no se realizó el cambio \n";
            }

            producto_Encontrado = true;
            break;
        }
    }

    if (!producto_Encontrado)
    {
        std::cout << "La ubicacion del producto " << ubicacion_Buscada << " no existe \n\n";
    }
}

// Funcion para generar el reporte de inventario
void generarReporte()
{
    std::cout << "\n ----- Reporte de Inventario ----- \n";
    std::cout << "| Código | " << "Nombre | " << "Stock | " << "Precio | " << "Ubicacion |" << " \n";

    for (int i = 0; i < contador_Productos; i++)
    {
        std::cout << "| " << codigo_Productos[i] << " | " << nombres_Productos[i] << " | " << cantidad_Stock[i] << " | $" << precio_Unitario[i] << " | " << codigo_Ubicacion[i] << " | \n\n";
    }
}

void generarReporteStockBajo()
{
    bool encontrado_Producto = false;

    std::cout << "\n ----- Reporte de Inventario de Stock Bajo ----- \n";
    std::cout << "| Código | " << "Nombre | " << "Stock | " << "Precio | " << "Ubicacion |" << " \n";

    for (int i = 0; i < contador_Productos; i++)
    {
        if (cantidad_Stock[i] <= stock_Bajo)
        {
            std::cout << "| " << codigo_Productos[i] << " | " << nombres_Productos[i] << " | " << cantidad_Stock[i] << " | $" << precio_Unitario[i] << " | " << codigo_Ubicacion[i] << " | \n";
            encontrado_Producto = true;
        }
    }

    if (!encontrado_Producto)
    {
        std::cout << "No hay productos con bajo stock \n";
    }

    std::cout << "\n";
}

void buscarProductoMasCaro()
{
    float precio_MasCaro = precio_Unitario[0];
    int indice_DelMasCaro = 0;

    for (int i = 1; i < contador_Productos; i++)
    {
        if (precio_Unitario[i] > precio_MasCaro)
        {
            precio_MasCaro = precio_Unitario[i];
            indice_DelMasCaro = i;
        }
    }

    std::cout << "\nEl producto más caro es: " << nombres_Productos[indice_DelMasCaro]
              << " y su precio es $" << precio_MasCaro << " \n\n";
}

void buscarProductoMasBarato()
{
    float precio_MasBarato = precio_Unitario[0];
    int indice_DelMasBarato = 0;

    for (int i = 1; i < contador_Productos; i++)
    {
        if (precio_Unitario[i] < precio_MasBarato)
        {
            precio_MasBarato = precio_Unitario[i];
            indice_DelMasBarato = i;
        }
    }

    std::cout << "\nEl producto más barato es: " << nombres_Productos[indice_DelMasBarato]
              << " y su precio es $" << precio_MasBarato << " \n\n";
}

void cargarArchivo()
{
    FILE *archivo_Cargado = fopen("data/inventario.txt", "r");

    if (archivo_Cargado == NULL)
    {
        std::cout << "Error al exportar al txt \n\n";

        return;
    }

    char buffer[512];

    fgets(buffer, sizeof(buffer), archivo_Cargado);

    while (contador_Productos < maximos_Productos && fgets(buffer, sizeof(buffer), archivo_Cargado))
    {
        int codigo, cantidad;
        float precio;
        char nombre[200], ubicacion[50];

        int yaLeido = sscanf(buffer, "%d, %[^,], %d, %f, %s", &codigo, nombre, &cantidad, &precio, ubicacion);

        if (yaLeido == 5)
        {
            codigo_Productos[contador_Productos] = codigo;
            nombres_Productos[contador_Productos] = nombre;
            cantidad_Stock[contador_Productos] = cantidad;
            precio_Unitario[contador_Productos] = precio;
            codigo_Ubicacion[contador_Productos] = ubicacion;
            contador_Productos++;
        }
    }

    fclose(archivo_Cargado);

    std::cout << "Se cargaron correctamente los productos desde el archivo inventario.txt \n\n";
}

void modificarArchivo()
{
    FILE *archivo_guardado = fopen("data/inventario.txt", "w");

    if (archivo_guardado == NULL)
    {
        std::cout << "No se pudo abrir el archivo para guardar los cambios.\n\n";

        return;
    }

    fprintf(archivo_guardado, "Codigo,Nombre,Cantidad,Precio,Ubicacion\n");

    for (int i = 0; i < contador_Productos; i++)
    {
        fprintf(archivo_guardado, "%d,%s,%d,%.2f,%s\n",
                codigo_Productos[i],
                nombres_Productos[i].c_str(),
                cantidad_Stock[i],
                precio_Unitario[i],
                codigo_Ubicacion[i].c_str());
    }

    fclose(archivo_guardado);

    std::cout << "Cambios guardados exitosamente en 'inventario.txt'.\n\n";
}
