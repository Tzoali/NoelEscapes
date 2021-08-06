/* Omar Arturo Ruiz Bernal
   Daniel Tzoali Arroyo Valdivia*/

#include "Records.h"
//Actualiza la informacion
void Records::actualizar(char * nombre, int puntuacion)
{
	strcpy(actual.nombre,nombre);
	actual.puntuacion = puntuacion;
}
//Crea un id para actual
void Records::crearID()
{
	bool crear = true;
	bool igual = true;
	while (crear)
	{
		igual = false;
		int n = 1+rand()%(50-1+1);
		for (int i = 0; i<5; i++)
		{
			if (info[i].id == n)
			{
				igual = true;
				break;
			}
		}
		if (!igual)
		{
			actual.id = n;
			break;
		}
	}
}
//Constructor
Records::Records()
{
    actual.id = 0;
    strcpy(actual.nombre,"");
    actual.puntuacion = -1;

	entrada.open("res/records/entrada.dat",ios::in|ios::binary);
	entrada.seekg(0,ios::beg);
	entrada.clear();

	for (int i = 0; i<5; i++)
	{
		entrada.read((char *)&info[i],sizeof(informacion));
	}

	salida.open("res/records/temp.dat",ios::out|ios::binary);

	crearID();

	ordenar();
}
//Destructor
Records::~Records()
{
	cerrar();
}
//Establece el id
void Records::setID(int id)
{
	actual.id = id;
}
//Reemplaza renglones
void Records::reemplazar()
{
	int minimo = 100000;
	int j;
	for (int i = 0; i<5; i++)
	{
		if (info[i].puntuacion <= minimo)
		{
			j = i;
			minimo = info[i].puntuacion;
		}
	}
	if (actual.puntuacion >= info[j].puntuacion)
	{
		info[j].puntuacion = actual.puntuacion;
		info[j].id = actual.id;
		strcpy(info[j].nombre,actual.nombre);
	}
}
//Ordena los records
void Records::ordenar()
{
	int minimo;
    for (int i = 0; i<4; i++)
    {
        minimo = i;
        for (int j = i+1; j<5; j++)
        {
            if (info[j].puntuacion > info[minimo].puntuacion)
            {
                minimo = j;
            }
        }
        informacion aux;
        aux = info[minimo];
        info[minimo] = info[i];
        info[i] = aux;
    }
}
//Cierra todo lo necesario
void Records::cerrar()
{
	reemplazar();
	ordenar();

	salida.seekp(0,ios::beg);
	salida.clear();
	for (int i = 0; i<5; i++)
	{
		salida.write((char *)&info[i],sizeof(informacion));
	}

	entrada.close();
	salida.close();

	remove("res/records/entrada.dat");
	rename("res/records/temp.dat","res/records/entrada.dat");
}
//Regressa la informacion en el renglon especificado
informacion Records::getInformacion(int x)
{
    return info[x];
}
