#include <bits/stdc++.h>
using namespace std;

//Crear una variable para ir registrando los movimientos que ocurrenen el cubo
int pasos[1000];
//Una variable contador para poder luego saber cuantos movimientos ocurrieron
int counter=0;
//Un arreglo de mutex para luego trabajar con concurrencia
std::mutex mymutex[6];

//Declaracion de las distintas funciones
void displayMenu(int color);
void ptrPasosSinNotacion();
void ptrPasosConNotacion();
void wrtFace(int *arr);
void ptrFace(int *arr);
int pasosRepetidos(int pasosResumidos[]);
bool isValidInt(string valid_numeroEnCadena);
void change_num(int *arr);
void searchNums(int arr[], int &w, int &b, int &y, int &g, int &r, int &o);

/**
* Estructura con la que se podra trabajar con el cubo
* Aqui se encuentran todas las funcionones que permiten manipular los datos
* dados como si fuera un cubo real.
* @author Equipo 1
*/
struct Cube
{
    int *white, *yellow, *orange, *green, *red, *blue;
    /**
    * Contructor de la clase
    * Al declarar una variable de este tipo de contructor empezara con reservar
    * la memoria necesaria para 6 arreglos de 9 datos cada uno y se hara que los
    * apuntadores de la clase apunten a esa memoria, cada uno de los apuntadores
    * simbolizaran la cara del cubo del nombre que se les dio y su indice
    * correspondera a la posicion de los colores de esa cara.
    * @author Equipo 1
    * @throw bad_alloc si la memoria no se pudo reserar correctamente
    */
	Cube(){
		try{
			white= new int[9];
	    	yellow= new int[9];
	    	orange= new int[9];
	    	green= new int[9];
	    	red= new int[9];
	    	blue= new int[9];
		}catch(bad_alloc& e){
			cout<<"No se pudo reservar memoria";
			exit(-1);
		}
	}
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara derecha
     * hacia abajo, esto viendose de frente la cara blaca del cubo con la
     * cara azúl por debajo, o bien mirando la cara naranja de frente y rotarla
     * hacia la izquierda, esto se logra cambiando los datos de los arreglos
     * siguiendo la aritmetica del cubo.
     * @author Equipo 1
     */
	void rotRightDown()
    {
        //Simulando el movimiento de los colores adyacentes de la cara naranja
        int aux = white[2];
        white[2]=green[6];
        green[6]=yellow[2];
        yellow[2]=blue[2];
        blue[2]=aux;

        aux = white[5];
        white[5]=green[3];
        green[3]=yellow[5];
        yellow[5]=blue[5];
        blue[5]=aux;

        aux = white[8];
        white[8]=green[0];
        green[0]=yellow[8];
        yellow[8]=blue[8];
        blue[8]=aux;

        //Simulando el rote de los colores en la cara naranja
        int auxi[9] = {orange[0], orange[1], orange[2], orange[3], orange[4], orange[5], orange[6], orange[7], orange[8]};
        orange[0]=auxi[2];
        orange[1]=auxi[5];
        orange[2]=auxi[8];
        orange[3]=auxi[1];
        orange[5]=auxi[7];
        orange[6]=auxi[0];
        orange[7]=auxi[3];
        orange[8]=auxi[6];

        //Asignarle al arreglo un numero que simbolizara que movimiento realizo
        pasos[counter]=1;
        counter+=1;
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara derecha
     * hacia arriba, esto viendose de frente la cara blaca del cubo con la cara 
     * azúl por debajo, o bien mirando la cara naranja de frente y rotarla 
     * hacia la derecha, se aprobecha el echo de que al hacer el mismo 
     * movimiento 3 veces es como si se hiciera el movimiento contrario 1 vez.
     * @author Equipo 1
     */
    void rotRightUp()
    {
        rotRightDown();
        rotRightDown();
        rotRightDown();
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara izquierda
     * hacia abajo, esto viendose de frente la cara blaca del cubo con la
     * cara azúl por debajo, o bien mirando la cara roja de frente y rotarla
     * hacia la derecha, esto se logra cambiando los datos de los arreglos
     * siguiendo la aritmetica del cubo.
     * @author Equipo 1
     */
    void rotLeftDown()
    {
        //Simulando el movimiento de los colores adyacentes de la cara roja
        int aux = white[0];
        white[0]=green[8];
        green[8]=yellow[0];
        yellow[0]=blue[0];
        blue[0]=aux;

        aux = white[3];
        white[3]=green[5];
        green[5]=yellow[3];
        yellow[3]=blue[3];
        blue[3]=aux;

        aux = white[6];
        white[6]=green[2];
        green[2]=yellow[6];
        yellow[6]=blue[6];
        blue[6]=aux;

        //Simulando el rote de los colores en la cara roja
        int auxi[9] = {red[0], red[1], red[2], red[3], red[4], red[5], red[6], red[7], red[8]};
        red[0]=auxi[6];
        red[1]=auxi[3];
        red[2]=auxi[0];
        red[3]=auxi[7];
        red[5]=auxi[1];
        red[6]=auxi[8];
        red[7]=auxi[5];
        red[8]=auxi[2];

        //Asignarle al arreglo un numero que simbolizara que movimiento realizo
        pasos[counter]=3;
        counter+=1;
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara izquierda
     * hacia abajo, esto viendose de frente la cara blaca del cubo con la cara 
     * azúl por debajo, o bien mirando la cara roja de frente y rotarla 
     * hacia la izquierda, se aprobecha el echo de que al hacer el mismo 
     * movimiento 3 veces es como si se hiciera el movimiento contrario 1 vez.
     * @author Equipo 1
     */
    void rotLeftUp()
    {
        rotLeftDown();
        rotLeftDown();
        rotLeftDown();
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara superior
     * hacia la derecha, esto viendose de frente la cara blaca del cubo con la
     * cara azúl por debajo, o bien mirando la cara verde de frente y rotarla
     * hacia la izquierda, esto se logra cambiando los datos de los arreglos
     * siguiendo la aritmetica del cubo.
     * @author Equipo 1
     */
    void rotUpRight()
    {
        //Simulando el movimiento de los colores adyacentes de la cara verde
        int aux = white[0];
        white[0]=red[6];
        red[6]=yellow[8];
        yellow[8]=orange[2];
        orange[2]=aux;

        aux = white[1];
        white[1]=red[3];
        red[3]=yellow[7];
        yellow[7]=orange[5];
        orange[5]=aux;

        aux = white[2];
        white[2]=red[0];
        red[0]=yellow[6];
        yellow[6]=orange[8];
        orange[8]=aux;

        //Simulando el rote de los colores en la cara verde
        int auxi[9] = {green[0], green[1], green[2], green[3], green[4], green[5], green[6], green[7], green[8]};
        green[0]=auxi[2];
        green[1]=auxi[5];
        green[2]=auxi[8];
        green[3]=auxi[1];
        green[5]=auxi[7];
        green[6]=auxi[0];
        green[7]=auxi[3];
        green[8]=auxi[6];

        //Asignarle al arreglo un numero que simbolizara que movimiento realizo
        pasos[counter]=4;
        counter+=1;
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara superior
     * hacia la izquierda, esto viendose de frente la cara blaca del cubo con la cara 
     * azúl por debajo, o bien mirando la cara verde de frente y rotarla 
     * hacia la derecha, se aprobecha el echo de que al hacer el mismo 
     * movimiento 3 veces es como si se hiciera el movimiento contrario 1 vez.
     * @author Equipo 1
     */
    void rotUpLeft()
    {
        rotUpRight();
        rotUpRight();
        rotUpRight();
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara inferior
     * hacia la derecha, esto viendose de frente la cara blaca del cubo con la
     * cara azúl por debajo, o bien mirando la cara azúl de frente y rotarla
     * hacia la derecha, esto se logra cambiando los datos de los arreglos
     * siguiendo la aritmetica del cubo.
     * @author Equipo 1
     */
    void rotDownRight()
    {
        //Simulando el movimiento de los colores adyacentes de la cara azúl
        int aux = white[6];
        white[6]=red[8];
        red[8]=yellow[2];
        yellow[2]=orange[0];
        orange[0]=aux;

        aux = white[7];
        white[7]=red[5];
        red[5]=yellow[1];
        yellow[1]=orange[3];
        orange[3]=aux;

        aux = white[8];
        white[8]=red[2];
        red[2]=yellow[0];
        yellow[0]=orange[6];
        orange[6]=aux;

        //Simulando el rote de los colores en la cara azúl
        int auxi[9] = {blue[0], blue[1], blue[2], blue[3], blue[4], blue[5], blue[6], blue[7], blue[8]};
        blue[0]=auxi[6];
        blue[1]=auxi[3];
        blue[2]=auxi[0];
        blue[3]=auxi[7];
        blue[5]=auxi[1];
        blue[6]=auxi[8];
        blue[7]=auxi[5];
        blue[8]=auxi[2];

        //Asignarle al arreglo un numero que simbolizara que movimiento realizo
        pasos[counter]=2;
        counter+=1;
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara inferior
     * hacia la izquierda, esto viendose de frente la cara blaca del cubo con la cara 
     * azúl por debajo, o bien mirando la cara azúl de frente y rotarla 
     * hacia la izquierda, se aprobecha el echo de que al hacer el mismo 
     * movimiento 3 veces es como si se hiciera el movimiento contrario 1 vez.
     * @author Equipo 1
     */
    void rotDownLeft()
    {
        rotDownRight();
        rotDownRight();
        rotDownRight();
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara frontal
     * hacia la derecha teniendo la cara blanca de frente, esto se logra 
     * cambiando los datos de los arreglos siguiendo la aritmetica del cubo.
     * @author Equipo 1
     */
    void rotFaceForwRight()
    {
        //Simulando el movimiento de los colores adyacentes de la cara blanca
        int aux = blue[0];
        blue[0]=orange[0];
        orange[0]=green[0];
        green[0]=red[0];
        red[0]=aux;

        aux = blue[1];
        blue[1]=orange[1];
        orange[1]=green[1];
        green[1]=red[1];
        red[1]=aux;

        aux = blue[2];
        blue[2]=orange[2];
        orange[2]=green[2];
        green[2]=red[2];
        red[2]=aux;

        //Simulando el rote de los colores en la cara blanca
        int auxi[9] = {white[0], white[1], white[2], white[3], white[4], white[5], white[6], white[7], white[8]};
        white[0]=auxi[6];
        white[1]=auxi[3];
        white[2]=auxi[0];
        white[3]=auxi[7];
        white[5]=auxi[1];
        white[6]=auxi[8];
        white[7]=auxi[5];
        white[8]=auxi[2];

        //Asignarle al arreglo un numero que simbolizara que movimiento realizo
        pasos[counter]=5;
        counter+=1;
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara frontal
     * hacia la izquierda, esto viendose de frente la cara blaca del cubo, 
     * se aprobecha el echo de que al hacer el mismo movimiento 3 veces es 
     * como si se hiciera el movimiento contrario 1 vez.
     * @author Equipo 1
     */
    void rotFaceForwLeft()
    {
        rotFaceForwRight();
        rotFaceForwRight();
        rotFaceForwRight();
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara trasera
     * hacia la derecha, esto viendose de frente la cara blaca del cubo con la
     * cara azúl por debajo, o bien mirando la cara amarilla de frente y rotarla
     * hacia la izquierda, esto se logra cambiando los datos de los arreglos
     * siguiendo la aritmetica del cubo.
     * @author Equipo 1
     */
    void rotFaceBackRight()
    {
        //Simulando el movimiento de los colores adyacentes de la cara amarilla
        int aux = blue[6];
        blue[6]=orange[6];
        orange[6]=green[6];
        green[6]=red[6];
        red[6]=aux;

        aux = blue[7];
        blue[7]=orange[7];
        orange[7]=green[7];
        green[7]=red[7];
        red[7]=aux;

        aux = blue[8];
        blue[8]=orange[8];
        orange[8]=green[8];
        green[8]=red[8];
        red[8]=aux;

        //Simulando el rote de los colores en la cara amarilla
        int auxi[9] = {yellow[0], yellow[1], yellow[2], yellow[3], yellow[4], yellow[5], yellow[6], yellow[7], yellow[8]};
        yellow[0]=auxi[2];
        yellow[1]=auxi[5];
        yellow[2]=auxi[8];
        yellow[3]=auxi[1];
        yellow[5]=auxi[7];
        yellow[6]=auxi[0];
        yellow[7]=auxi[3];
        yellow[8]=auxi[6];

        //Asignarle al arreglo un numero que simbolizara que movimiento realizo
        pasos[counter]=6;
        counter+=1;
    }
    /**
     * Funcion de la clase
     * En esta funcion se simulara el movimiento de girar la cara tarsera
     * hacia la izquierda, esto viendose de frente la cara blaca del cubo con la cara 
     * azúl por debajo, o bien mirando la cara amarilla de frente y rotarla 
     * hacia la derecha, se aprobecha el echo de que al hacer el mismo 
     * movimiento 3 veces es como si se hiciera el movimiento contrario 1 vez.
     * @author Equipo 1
     */
    void rotFaceBackLeft()
    {
        rotFaceBackRight();
        rotFaceBackRight();
        rotFaceBackRight();
    }
    /**
     * Funcion de la clase
     * Hacer la cruz superior, busca llegar a tener una cruz blanca para poder 
     * empezar a trabajar en el cubocon algoritmos, no es necesario que este 
     * alineada puesto que una funcion se encargara de eso despues de tener 
     * la cruz echa.
     * @author Equipo 1
     */
    void makeSupCross()
    {
        int i=0, j=0;
        //El proceso se repetira hasta que las posiciones que correspondena  la cruz tenga color blanco
        while(white[1]!=1 || white[3]!=1 || white[5]!=1 || white[7]!=1)
        {
            for(j=0; j<4; j++)
            {
                for(i=0; i<4; i++)
                {
                    if(white[5]==1)
                        i=4;
                    else
                        rotRightDown();
                }
                for(i=0; i<4; i++)
                {
                    if(white[7]==1)
                        i=4;
                    else
                        rotDownRight();
                }
                for(i=0; i<4; i++)
                {
                    if(white[3]==1)
                        i=4;
                    else
                        rotLeftDown();
                }
                for(i=0; i<4; i++)
                {
                    if(white[1]==1)
                        i=4;
                    else
                        rotUpRight();
                }
                if(white[1]==1 && white[3]==1 && white[5]==1 && white[7]==1)
                    j=4;
                else
                    rotFaceForwRight();
            }
            if(white[5]!=1)
            {
                rotRightDown();
                rotFaceForwRight();
            }
            else
            {
                if(white[7]!=1)
                {
                    rotDownRight();
                    rotFaceForwRight();
                }
                else
                {
                    if(white[3]!=1)
                    {
                        rotLeftDown();
                        rotFaceForwRight();
                    }
                    else
                    {
                        if(white[1]!=1)
                        {
                            rotUpRight();
                            rotFaceForwRight();
                        }
                    }
                }
            }
        }
        permutateSupCross();
    }
    /**
     * Funcion de la clase
     * Permutar la cruz superior, una vez se tenga la cruz blanca echa esta funcion
     * se asegura de que esa cruz este alineada con sus respectivos colores
     * en caso de no ser asi sigue un algoritmo que depende de la posicion 
     * de ciertos colores y utiliza los movimientos anteriormente programados
     * para realizarlos.
     * @author Equipo 1
     */
    void permutateSupCross()
    {
        //El proceso se repetira hasta que todas las posiciones dichas tengan el color esperado
        while(orange[1]!=3 || green[1]!=4 || blue[1]!=5 || red[1]!=6)
        {
            for(int i=0; i<4; i++)
            {
                if(blue[1]==5 && orange[1]==3)
                {
                    //Algoritmo para permutar
                    rotRightDown();
                    rotFaceForwLeft();
                    rotRightUp();
                    rotFaceForwLeft();
                    rotRightDown();
                    rotFaceForwRight();
                    rotFaceForwRight();
                    rotRightUp();
                    rotFaceForwLeft();
                    break;
                }
                if(orange[1]==3 && green[1]==4)
                {
                    rotUpRight();
                    rotFaceForwLeft();
                    rotUpLeft();
                    rotFaceForwLeft();
                    rotUpRight();
                    rotFaceForwRight();
                    rotFaceForwRight();
                    rotUpLeft();
                    rotFaceForwLeft();
                    break;
                }
                if(green[1]==4 && red[1]==6)
                {
                    rotLeftUp();
                    rotFaceForwLeft();
                    rotLeftDown();
                    rotFaceForwLeft();
                    rotLeftUp();
                    rotFaceForwRight();
                    rotFaceForwRight();
                    rotLeftDown();
                    rotFaceForwLeft();
                    break;
                }
                if(red[1]==6 && blue[1]==5)
                {
                    rotDownLeft();
                    rotFaceForwLeft();
                    rotDownRight();
                    rotFaceForwLeft();
                    rotDownLeft();
                    rotFaceForwRight();
                    rotFaceForwRight();
                    rotDownRight();
                    rotFaceForwLeft();
                    break;
                }
                rotFaceForwRight();
            }
            if(orange[1]!=3 || green[1]!=4 || blue[1]!=5 || red[1]!=6)
            {
                for(int i=0; i<4; i++)
                {
                    if(orange[1]==3 && red[1]==6)
                    {
                            rotUpRight();
                            rotFaceForwLeft();
                            rotUpLeft();
                            rotFaceForwLeft();
                            rotUpRight();
                            rotFaceForwRight();
                            rotFaceForwRight();
                            rotUpLeft();
                            rotFaceForwLeft();
                            break;
                    }
                    else
                    {
                        if(blue[1]==5 && green[1]==4)
                        {
                            rotRightDown();
                            rotFaceForwLeft();
                            rotRightUp();
                            rotFaceForwLeft();
                            rotRightDown();
                            rotFaceForwRight();
                            rotFaceForwRight();
                            rotRightUp();
                            rotFaceForwLeft();
                            break;
                        }
                    }
                    rotFaceForwRight();
                }
            }
        }
    }
    /**
     * Funcion de la clase
     * Hacer la cara superior, una vez se tenga la cruz blanca echa esta 
     * funcion buscara llegar a tener la cara blanca armada y alineada 
     * con sus respectivos colores siguiendo algoritmos usando los
     * movimientos anteriormente programados.
     * @author Equipo 1
     */
    void makeSupFace()
    {
        bool rt = true;
        while(white[0]!=1 || white[2]!=1 || white[6]!=1 || white[8]!=1)
        {
            rt = true;
            for(int i=0; i<4; i++)
            {
                if(blue[8]==1 && orange[6]==3)
                {
                    rotDownRight();
                    rotFaceBackLeft();
                    rotDownLeft();
                    i=0;
                }
                if(orange[8]==1 && green[6]==4)
                {
                    rotRightUp();
                    rotFaceBackLeft();
                    rotRightDown();
                    i=0;
                }
                if(green[8]==1 && red[6]==6)
                {
                    rotUpLeft();
                    rotFaceBackLeft();
                    rotUpRight();
                    i=0;
                }
                if(red[8]==1 && blue[6]==5)
                {
                    rotLeftDown();
                    rotFaceBackLeft();
                    rotLeftUp();
                    i=0;
                }
                if(blue[6]==1 && red[8]==6)
                {
                    rotDownLeft();
                    rotFaceBackRight();
                    rotDownRight();
                    i=0;
                }
                if(red[6]==1 && green[8]==4)
                {
                    rotLeftUp();
                    rotFaceBackRight();
                    rotLeftDown();
                    i=0;
                }
                if(green[6]==1 && orange[8]==3)
                {
                    rotUpRight();
                    rotFaceBackRight();
                    rotUpLeft();
                    i=0;
                }
                if(orange[6]==1 && blue[8]==5)
                {
                    rotRightDown();
                    rotFaceBackRight();
                    rotRightUp();
                    i=0;
                }
                if(white[0]!=1 || white[2]!=1 || white[6]!=1 || white[8]!=1)
                    rotFaceBackRight();
                else
                    i=4;
            }
            if(white[0]!=1 || white[2]!=1 || white[6]!=1 || white[8]!=1)
            {
                if(blue[0]==1 || red[2]==1 || (white[6]==1 && blue[0]!=5 && red[2]!=6))
                {
                    rotLeftDown();
                    rotFaceBackRight();
                    rotLeftUp();
                    rt = false;
                }
                else
                {
                    if(red[0]==1 || green[2]==1 || (white[0]==1 && red[0]!=6 && green[2]!=4))
                    {
                        rotUpLeft();
                        rotFaceBackRight();
                        rotUpRight();
                        rt = false;
                    }
                    else
                    {
                        if(green[0]==1 || orange[2]==1 || (white[2]==1 && green[0]!=4 && orange[2]!=3))
                        {
                            rotRightUp();
                            rotFaceBackRight();
                            rotRightDown();
                            rt = false;
                        }
                        else
                        {
                            if(orange[0]==1 || blue[2]==1 || (white[8]==1 && orange[0]!=3 && blue[2]!=5))
                            {
                                rotRightDown();
                                rotFaceBackRight();
                                rotRightUp();
                                rt = false;
                            }
                        }
                    }
                }
            }
            if(rt)
            {
                if(white[0]!=1)
                {
                    while(yellow[6]!=1)
                        rotFaceBackRight();
                    rotLeftUp();
                    rotFaceBackRight();
                    rotLeftDown();
                }
                else
                {
                    if(white[2]!=1)
                    {
                        while(yellow[8]!=1)
                            rotFaceBackRight();
                        rotRightUp();
                        rotFaceBackRight();
                        rotRightDown();
                    }
                    else
                    {
                        if(white[6]!=1)
                        {
                            while(yellow[0]!=1)
                                rotFaceBackRight();
                            rotLeftDown();
                            rotFaceBackRight();
                            rotLeftUp();
                        }
                        else
                        {
                            if(white[8]!=1)
                            {
                                while(yellow[2]!=1)
                                    rotFaceBackRight();
                                rotRightDown();
                                rotFaceBackRight();
                                rotRightUp();
                            }
                        }
                    }
                }
            }
        }
    }
    /**
     * Funcion de la clase
     * Hacer las aristas medias laterales, una vez la cara blanca este armada
     * esta funcion buscara alinear las aristas que corresponden a la parte
     * media de los colores laterales del cubo sin alterar la cara armada, 
     * esto se consigue con algoritmos echos en base a la posiciones de los 
     * colores con los movimientos anteriormente programados
     * @author Equipo 1
     */
    void makeLatEdge()
    {
        //Mientras que no este el color buscado en la posicion necesaria
        while(blue[3]!=5 || blue[5]!=5 || green[3]!=4 || green[5]!=4)
        {
            for(int i=0; i<4; i++)
            {
                if(blue[7]==5 && yellow[1]==3)
                {
                    rotFaceBackRight();
                    rotRightDown();
                    rotFaceBackLeft();
                    rotRightUp();
                    rotFaceBackLeft();
                    rotDownRight();
                    rotFaceBackRight();
                    rotDownLeft();
                    i=0;
                }
                if(orange[7]==3 && yellow[5]==4)
                {
                    rotFaceBackRight();
                    rotUpRight();
                    rotFaceBackLeft();
                    rotUpLeft();
                    rotFaceBackLeft();
                    rotRightUp();
                    rotFaceBackRight();
                    rotRightDown();
                    i=0;
                }
                if(green[7]==4 && yellow[7]==6)
                {
                    rotFaceBackRight();
                    rotLeftUp();
                    rotFaceBackLeft();
                    rotLeftDown();
                    rotFaceBackLeft();
                    rotUpLeft();
                    rotFaceBackRight();
                    rotUpRight();
                    i=0;
                }
                if(red[7]==6 && yellow[3]==5)
                {
                    rotFaceBackRight();
                    rotDownLeft();
                    rotFaceBackLeft();
                    rotDownRight();
                    rotFaceBackLeft();
                    rotLeftDown();
                    rotFaceBackRight();
                    rotLeftUp();
                    i=0;
                }
                if(blue[7]==5 && yellow[1]==6)
                {
                    rotFaceBackLeft();
                    rotLeftDown();
                    rotFaceBackRight();
                    rotLeftUp();
                    rotFaceBackRight();
                    rotDownLeft();
                    rotFaceBackLeft();
                    rotDownRight();
                    i=0;
                }
                if(red[7]==6 && yellow[3]==4)
                {
                    rotFaceBackLeft();
                    rotUpLeft();
                    rotFaceBackRight();
                    rotUpRight();
                    rotFaceBackRight();
                    rotLeftUp();
                    rotFaceBackLeft();
                    rotLeftDown();
                    i=0;
                }
                if(green[7]==4 && yellow[7]==3)
                {
                    rotFaceBackLeft();
                    rotRightUp();
                    rotFaceBackRight();
                    rotRightDown();
                    rotFaceBackRight();
                    rotUpRight();
                    rotFaceBackLeft();
                    rotUpLeft();
                    i=0;
                }
                if(orange[7]==3 && yellow[5]==5)
                {
                    rotFaceBackLeft();
                    rotDownRight();
                    rotFaceBackRight();
                    rotDownLeft();
                    rotFaceBackRight();
                    rotRightDown();
                    rotFaceBackLeft();
                    rotRightUp();
                    i=0;
                }
                if(blue[3]==5 && blue[5]==5 && green[3]==4 && green[5]==4)
                    i=4;
                else
                    rotFaceBackRight();
            }
            if(blue[5]!=5)
            {
                rotFaceBackRight();
                rotRightDown();
                rotFaceBackLeft();
                rotRightUp();
                rotFaceBackLeft();
                rotDownRight();
                rotFaceBackRight();
                rotDownLeft();
            }
            else
            {
                if(orange[5]!=3)
                {
                    rotFaceBackRight();
                    rotUpRight();
                    rotFaceBackLeft();
                    rotUpLeft();
                    rotFaceBackLeft();
                    rotRightUp();
                    rotFaceBackRight();
                    rotRightDown();
                }
                else
                {
                    if(green[5]!=4)
                    {
                        rotFaceBackRight();
                        rotLeftUp();
                        rotFaceBackLeft();
                        rotLeftDown();
                        rotFaceBackLeft();
                        rotUpLeft();
                        rotFaceBackRight();
                        rotUpRight();
                    }
                    else
                    {
                        if(red[5]!=6)
                        {
                            rotFaceBackRight();
                            rotDownLeft();
                            rotFaceBackLeft();
                            rotDownRight();
                            rotFaceBackLeft();
                            rotLeftDown();
                            rotFaceBackRight();
                            rotLeftUp();
                        }
                    }
                }
            }
        }
    }
    /**
     * Funcion de la clase
     * Hacer la cruz inferior, una vez armada la cara blanca y las aristas 
     * medias busca llegar a tener una cruz amarilla sin alterar lo que
     * ya se tiene armado, siguiendo algoritmos que dependen de la posicion
     * de los colores usando lo movimientos anteriormente programados.
     * @author Equipo 1
     */
    void makeInfCross()
    {
        //Mientras que no este el color buscado en la posicion necesaria
        while(yellow[1]!=2 || yellow[3]!=2 || yellow[5]!=2 || yellow[7]!=2)
        {
            if(yellow[1]==2 && yellow[7]==2)
            {
                rotLeftDown();
                rotUpLeft();
                rotFaceBackLeft();
                rotUpRight();
                rotFaceBackRight();
                rotLeftUp();
            }
            else
            {
                if(yellow[5]==2 && yellow[3]==2)
                {
                    rotUpLeft();
                    rotRightUp();
                    rotFaceBackLeft();
                    rotRightDown();
                    rotFaceBackRight();
                    rotUpRight();
                }
                else
                {
                    if(yellow[1]==2 && yellow[5]==2)
                    {
                        rotLeftDown();
                        rotUpLeft();
                        rotFaceBackLeft();
                        rotUpRight();
                        rotFaceBackRight();
                        rotLeftUp();
                    }
                    else
                    {
                        if(yellow[5]==2 && yellow[7]==2)
                        {
                            rotDownRight();
                            rotLeftDown();
                            rotFaceBackLeft();
                            rotLeftUp();
                            rotFaceBackRight();
                            rotDownLeft();
                        }
                        else
                        {
                            if(yellow[7]==2 && yellow[3]==2)
                            {
                                rotRightUp();
                                rotDownRight();
                                rotFaceBackLeft();
                                rotDownLeft();
                                rotFaceBackRight();
                                rotRightDown();
                            }
                            else
                            {
                                rotUpLeft();
                                rotRightUp();
                                rotFaceBackLeft();
                                rotRightDown();
                                rotFaceBackRight();
                                rotUpRight();
                            }
                        }
                    }
                }
            }
        }
        permutateInfCross();
    }
    /**
     * Funcion de la clase
     * Permutar la cruz inferior, una vez se tenga la cara blanca armada, 
     * las aristas medias y la cruz amarilla echa esta funcion se asegura de 
     * que esa cruz este alineada con sus respectivos colores en caso de no 
     * ser asi sigue un algoritmo que depende de la posicion de ciertos colores, 
     * estos no alteran las partes ya armadas del cubo y utiliza los 
     * movimientos anteriormente programados para realizarlos.
     * @author Equipo 1
     */
    void permutateInfCross()
    {
        //Mientras que no este el color buscado en la posicion necesaria
        while(orange[7]!=3 || green[7]!=4 || blue[7]!=5 || red[7]!=6)
        {
            for(int i=0; i<4; i++)
            {
                if(blue[7]==5 && orange[7]==3)
                {
                    rotDownLeft();
                    rotFaceBackRight();
                    rotDownRight();
                    rotFaceBackRight();
                    rotDownLeft();
                    rotFaceBackRight();
                    rotFaceBackRight();
                    rotDownRight();
                    rotFaceBackRight();
                    break;
                }
                if(orange[7]==3 && green[7]==4)
                {
                    rotRightDown();
                    rotFaceBackRight();
                    rotRightUp();
                    rotFaceBackRight();
                    rotRightDown();
                    rotFaceBackRight();
                    rotFaceBackRight();
                    rotRightUp();
                    rotFaceBackRight();
                    break;
                }
                if(green[7]==4 && red[7]==6)
                {
                    rotUpRight();
                    rotFaceBackRight();
                    rotUpLeft();
                    rotFaceBackRight();
                    rotUpRight();
                    rotFaceBackRight();
                    rotFaceBackRight();
                    rotUpLeft();
                    rotFaceBackRight();
                    break;
                }
                if(red[7]==6 && blue[7]==5)
                {
                    rotLeftUp();
                    rotFaceBackRight();
                    rotLeftDown();
                    rotFaceBackRight();
                    rotLeftUp();
                    rotFaceBackRight();
                    rotFaceBackRight();
                    rotLeftDown();
                    rotFaceBackRight();
                    break;
                }
                rotFaceBackRight();
            }
            if(orange[7]!=3 || green[7]!=4 || blue[7]!=5 || red[7]!=6)
            {
                for(int i=0; i<4; i++)
                {
                    if(orange[7]==3 && red[7]==6)
                    {
                        rotDownLeft();
                        rotFaceBackRight();
                        rotDownRight();
                        rotFaceBackRight();
                        rotDownLeft();
                        rotFaceBackRight();
                        rotFaceBackRight();
                        rotDownRight();
                        rotFaceBackRight();
                        break;
                    }
                    else
                    {
                        if(blue[7]==5 && green[7]==4)
                        {
                            rotLeftUp();
                            rotFaceBackRight();
                            rotLeftDown();
                            rotFaceBackRight();
                            rotLeftUp();
                            rotFaceBackRight();
                            rotFaceBackRight();
                            rotLeftDown();
                            rotFaceBackRight();
                            break;
                        }
                    }
                    rotFaceBackRight();
                }
            }
        }
    }
    /**
     * Funcion de la clase
     * Hacer la cara inferior, una vez se tenga armado la cara blanca, las
     * aristas medias y la cruz amarilla alineada con los colores laterales
     * esta funcion busca armar la cara amarilla alineando todo con sus
     * repsectivos colores.
     * @author Equipo 1
     */
    void makeInfFace()
    {
        //Mientras que no este el color buscado en la posicion necesaria
        while(!(((blue[8]==5 || blue[8]==3 || blue[8]==2)&&(orange[6]==3 || orange[6]==5 || orange[6]==2)&&(yellow[2]==2 || yellow[2]==3 || yellow[2]==5)) && ((orange[8]==3 || orange[8]==4 || orange[8]==2)&&(green[6]==4 || green[6]==3 || green[6]==2)&&(yellow[8]==2 || yellow[8]==3 || yellow[8]==4)) && ((green[8]==4 || green[8]==6 || green[8]==2)&&(red[6]==6 || red[6]==4 || red[6]==2)&&(yellow[6]==4 || yellow[6]==6 || yellow[6]==2)) && ((red[8]==6 || red[8]==5 || red[8]==2)&&(blue[6]==5 || blue[6]==6 || blue[6]==2)&&(yellow[0]==2 || yellow[0]==5 || yellow[0]==6))))
        {
            if((blue[8]==5 || blue[8]==3 || blue[8]==2)&&(orange[6]==3 || orange[6]==5 || orange[6]==2)&&(yellow[2]==2 || yellow[2]==3 || yellow[2]==5))
            {
                while(!(((blue[8]==5 || blue[8]==3 || blue[8]==2)&&(orange[6]==3 || orange[6]==5 || orange[6]==2)&&(yellow[2]==2 || yellow[2]==3 || yellow[2]==5)) && ((orange[8]==3 || orange[8]==4 || orange[8]==2)&&(green[6]==4 || green[6]==3 || green[6]==2)&&(yellow[8]==2 || yellow[8]==3 || yellow[8]==4)) && ((green[8]==4 || green[8]==6 || green[8]==2)&&(red[6]==6 || red[6]==4 || red[6]==2)&&(yellow[6]==4 || yellow[6]==6 || yellow[6]==2)) && ((red[8]==6 || red[8]==5 || red[8]==2)&&(blue[6]==5 || blue[6]==6 || blue[6]==2)&&(yellow[0]==2 || yellow[0]==5 || yellow[0]==6))))
                {
                    rotFaceBackLeft();
                    rotDownRight();
                    rotFaceBackRight();
                    rotUpRight();
                    rotFaceBackLeft();
                    rotDownLeft();
                    rotFaceBackRight();
                    rotUpLeft();
                }
            }
            else
            {
                if((orange[8]==3 || orange[8]==4 || orange[8]==2)&&(green[6]==4 || green[6]==3 || green[6]==2)&&(yellow[8]==2 || yellow[8]==3 || yellow[8]==4))
                {
                    while(!(((blue[8]==5 || blue[8]==3 || blue[8]==2)&&(orange[6]==3 || orange[6]==5 || orange[6]==2)&&(yellow[2]==2 || yellow[2]==3 || yellow[2]==5)) && ((orange[8]==3 || orange[8]==4 || orange[8]==2)&&(green[6]==4 || green[6]==3 || green[6]==2)&&(yellow[8]==2 || yellow[8]==3 || yellow[8]==4)) && ((green[8]==4 || green[8]==6 || green[8]==2)&&(red[6]==6 || red[6]==4 || red[6]==2)&&(yellow[6]==4 || yellow[6]==6 || yellow[6]==2)) && ((red[8]==6 || red[8]==5 || red[8]==2)&&(blue[6]==5 || blue[6]==6 || blue[6]==2)&&(yellow[0]==2 || yellow[0]==5 || yellow[0]==6))))
                    {
                        rotFaceBackLeft();
                        rotRightUp();
                        rotFaceBackRight();
                        rotLeftUp();
                        rotFaceBackLeft();
                        rotRightDown();
                        rotFaceBackRight();
                        rotLeftDown();
                    }
                }
                else
                {
                    if((green[8]==4 || green[8]==6 || green[8]==2)&&(red[6]==6 || red[6]==4 || red[6]==2)&&(yellow[6]==4 || yellow[6]==6 || yellow[6]==2))
                    {
                        while(!(((blue[8]==5 || blue[8]==3 || blue[8]==2)&&(orange[6]==3 || orange[6]==5 || orange[6]==2)&&(yellow[2]==2 || yellow[2]==3 || yellow[2]==5)) && ((orange[8]==3 || orange[8]==4 || orange[8]==2)&&(green[6]==4 || green[6]==3 || green[6]==2)&&(yellow[8]==2 || yellow[8]==3 || yellow[8]==4)) && ((green[8]==4 || green[8]==6 || green[8]==2)&&(red[6]==6 || red[6]==4 || red[6]==2)&&(yellow[6]==4 || yellow[6]==6 || yellow[6]==2)) && ((red[8]==6 || red[8]==5 || red[8]==2)&&(blue[6]==5 || blue[6]==6 || blue[6]==2)&&(yellow[0]==2 || yellow[0]==5 || yellow[0]==6))))
                        {
                            rotFaceBackLeft();
                            rotUpLeft();
                            rotFaceBackRight();
                            rotDownLeft();
                            rotFaceBackLeft();
                            rotUpRight();
                            rotFaceBackRight();
                            rotDownRight();
                        }
                    }
                    else
                    {
                        if((red[8]==6 || red[8]==5 || red[8]==2)&&(blue[6]==5 || blue[6]==6 || blue[6]==2)&&(yellow[0]==2 || yellow[0]==5 || yellow[0]==6))
                        {
                            while(!(((blue[8]==5 || blue[8]==3 || blue[8]==2)&&(orange[6]==3 || orange[6]==5 || orange[6]==2)&&(yellow[2]==2 || yellow[2]==3 || yellow[2]==5)) && ((orange[8]==3 || orange[8]==4 || orange[8]==2)&&(green[6]==4 || green[6]==3 || green[6]==2)&&(yellow[8]==2 || yellow[8]==3 || yellow[8]==4)) && ((green[8]==4 || green[8]==6 || green[8]==2)&&(red[6]==6 || red[6]==4 || red[6]==2)&&(yellow[6]==4 || yellow[6]==6 || yellow[6]==2)) && ((red[8]==6 || red[8]==5 || red[8]==2)&&(blue[6]==5 || blue[6]==6 || blue[6]==2)&&(yellow[0]==2 || yellow[0]==5 || yellow[0]==6))))
                            {
                                rotFaceBackLeft();
                                rotLeftDown();
                                rotFaceBackRight();
                                rotRightDown();
                                rotFaceBackLeft();
                                rotLeftUp();
                                rotFaceBackRight();
                                rotRightUp();
                            }
                        }
                        else
                        {
                            rotFaceBackLeft();
                            rotLeftDown();
                            rotFaceBackRight();
                            rotRightDown();
                            rotFaceBackLeft();
                            rotLeftUp();
                            rotFaceBackRight();
                            rotRightUp();
                        }
                    }
                }
            }
        }
        while(!((blue[8]==5 && orange[6]==3 && yellow[2]==2) && (orange[8]==3 && green[6]==4 && yellow[8]==2) && (green[8]==4 && red[6]==6 && yellow[6]==2) && (red[8]==6 && blue[6]==5 && yellow[0]==2)))
        {
            if(blue[8]==5 && orange[6]==3 && yellow[2]==2)
            {
                rotFaceBackRight();
                while(!(blue[8]==3 && orange[6]==4 && yellow[2]==2))
                {
                    rotDownLeft();
                    rotFaceForwRight();
                    rotDownRight();
                    rotFaceForwLeft();
                }
                rotFaceBackRight();
                while(!(blue[8]==4 && orange[6]==6 && yellow[2]==2))
                {
                    rotDownLeft();
                    rotFaceForwRight();
                    rotDownRight();
                    rotFaceForwLeft();
                }
                rotFaceBackRight();
                while(!(blue[8]==6 && orange[6]==5 && yellow[2]==2))
                {
                    rotDownLeft();
                    rotFaceForwRight();
                    rotDownRight();
                    rotFaceForwLeft();
                }
                rotFaceBackRight();
            }
            else
            {
                rotDownLeft();
                rotFaceForwRight();
                rotDownRight();
                rotFaceForwLeft();
            }
        }
    }
    /**
     * Funcion de la clase
     * Esta funcion ejecuta en orden las funciones para
     * armar el cubo Rubik.
     * @author Equipo 1
     */
    void solveCube()
    {
        makeSupCross();
        makeSupFace();
        makeLatEdge();
        makeInfCross();
        makeInfFace();
    }
    /**
     * Funcion de la clase
     * Funcion creada para randomizar un cubo, fue usado
     * para crear casos de prueba para el programa.
     * @author Equipo 1
     */
    void randCube()
    {
        int j;
        for(int i=0; i<25; i++)
        {
            j= rand()%(6-1);
            switch(j)
            {
                case 1:
                    rotRightDown();
                    break;
                case 2:
                    rotDownRight();
                    break;
                case 3:
                    rotLeftDown();
                    break;
                case 4:
                    rotUpRight();
                    break;
                case 5:
                    rotFaceForwRight();
                    break;
                case 6:
                    rotFaceBackRight();
                    break;
            }
        }
    }
    /**
     * Funcion de la clase
     * Esta funcion permite alterar valores de cualquier cara del cubo
     * @author Equipo 1
     */
    void changeFace()
    {
        //Strings para registrar distintas opciones y calificar si el valor introducido el valido
        string option1 = "", option2 = "", option3 = "";
        do{
            system("cls");
            cout<<"¿Que cara quieres cambiar?"<<endl
            <<"1: Cara Blanca   2: Cara Amarilla    3: Cara Naranja"<<endl
            <<"4: Cara Verde    5: Cara Azul        6: Cara Roja"<<endl
            <<"7: No quiero cambiar una cara"<<endl;
            try{
                //Verificar opcion valida
                cin>>option1;
                if(!isValidInt(option1)) throw option1;
                if(stoi(option1)>7 || stoi(option1)<1)    throw option1;
                switch(stoi(option1)){
                    case 1:
                        do{
                            system("cls");
                            displayMenu(0);
                            ptrFace(white);
                            change_num(white);
                            system("cls");
                            ptrFace(white);
                            cout<<"¿Quieres cambiar otro numero de esta cara?"<<endl
                                <<"1: Si 2: No"<<endl;
                            do{
                                //Verificar opcion valida
                                try{
                                    cin>>option2;
                                    if(!isValidInt(option2)) throw option2;
                                    if(stoi(option2)>2 || stoi(option2)<1)  throw option2;
                                }catch(string &e){
                                    cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
                                    option2 = "";
                                }
                            }while(!isValidInt(option2));
                        }while(option2!="2");
                        break;
                    case 2:
                        do{
                            system("cls");
                            displayMenu(5);
                            ptrFace(yellow);
                            change_num(yellow);
                            system("cls");
                            ptrFace(yellow);
                            cout<<"¿Quieres cambiar otro numero de esta cara?"<<endl
                                <<"1: Si 2: No"<<endl;
                            do{
                                //Verificar opcion valida
                                try{
                                    cin>>option2;
                                    if(!isValidInt(option2)) throw option2;
                                    if(stoi(option2)>2 || stoi(option2)<1)  throw option2;
                                }catch(string &e){
                                    cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
                                    option2 = "";
                                }
                            }while(!isValidInt(option2));
                        }while(option2!="2");
                        break;
                    case 3:
                        do{
                            system("cls");
                            displayMenu(2);
                            ptrFace(orange);
                            change_num(orange);
                            system("cls");
                            ptrFace(orange);
                            cout<<"¿Quieres cambiar otro numero de esta cara?"<<endl
                                <<"1: Si 2: No"<<endl;
                            do{
                                //Verificar opcion valida
                                try{
                                    cin>>option2;
                                    if(!isValidInt(option2)) throw option2;
                                    if(stoi(option2)>2 || stoi(option2)<1)  throw option2;
                                }catch(string &e){
                                    cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
                                    option2 = "";
                                }
                            }while(!isValidInt(option2));
                        }while(option2!="2");
                        break;
                    case 4:
                        do{
                            system("cls");
                            displayMenu(3);
                            ptrFace(green);
                            change_num(green);
                            system("cls");
                            ptrFace(green);
                            cout<<"¿Quieres cambiar otro numero de esta cara?"<<endl
                                <<"1: Si 2: No"<<endl;
                            do{
                                //Verificar opcion valida
                                try{
                                    cin>>option2;
                                    if(!isValidInt(option2)) throw option2;
                                    if(stoi(option2)>2 || stoi(option2)<1)  throw option2;
                                }catch(string &e){
                                    cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
                                    option2 = "";
                                }
                            }while(!isValidInt(option2));
                        }while(option2!="2");
                        break;
                    case 5:
                        do{
                            system("cls");
                            displayMenu(stoi(option1)-1);
                            ptrFace(blue);
                            change_num(blue);
                            system("cls");
                            ptrFace(blue);
                            cout<<"¿Quieres cambiar otro numero de esta cara?"<<endl
                                <<"1: Si 2: No"<<endl;
                            do{
                                //Verificar opcion valida
                                try{
                                    cin>>option2;
                                    if(!isValidInt(option2)) throw option2;
                                    if(stoi(option2)>2 || stoi(option2)<1)  throw option2;
                                }catch(string &e){
                                    cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
                                    option2 = "";
                                }
                            }while(!isValidInt(option2));
                        }while(option2!="2");
                        break;
                    case 6:
                        do{
                            system("cls");
                            displayMenu(stoi(option1)-1);
                            ptrFace(red);
                            change_num(red);
                            system("cls");
                            ptrFace(red);
                            cout<<"¿Quieres cambiar otro numero de esta cara?"<<endl
                                <<"1: Si 2: No"<<endl;
                            do{
                                //Verificar opcion valida
                                try{
                                    cin>>option2;
                                    if(!isValidInt(option2)) throw option2;
                                    if(stoi(option2)>2 || stoi(option2)<1)  throw option2;
                                }catch(string &e){
                                    cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
                                    option2 = "";
                                }
                            }while(!isValidInt(option2));
                        }while(option2!="2");
                        break;
                    case 7:
                        option3 = "2";
                        break;
                    default:
                        cout<<"Numero invalido"<<endl;
                        continue;
                }
            }catch(string &e){
                cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
            }
            system("cls");
            if(option3 == "2")  break;
            prtCube();
            cout<<"¿Quieres cambiar otra cara?"<<endl
                <<"1: Si 2: No"<<endl;
            do{
                //Verificar opcion valida
                 try{
                    cin>>option3;
                    if(!isValidInt(option3)) throw option3;
                    if(stoi(option3)>2 || stoi(option3)<1)  throw option3;
                }catch(string &e){
                    cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
                    option3 = "";
                }
            }while(!isValidInt(option3));
        }while(option3!="2");
        system("cls");
    }
    /**
     * Funcion de la clase
     * Aqui se verificara si los datos introducidos para el cubo corresponden a un cubo verdadero
     * @author  Equipo 1
     * @throw   invalid_argument    En caso de que se detecatra que el nuemero de colores no corresponde a un cubo real
     */
    void checkcube()
    {
        thread t[6];
        int w=0, b=0, y=0, g=0, r=0, o=0;
        t[0] = thread(&searchNums, white, ref(w), ref(b), ref(y), ref(g), ref(r), ref(o));
        t[1] = thread(&searchNums, blue, ref(w), ref(b), ref(y), ref(g), ref(r), ref(o));
        t[2] = thread(&searchNums, yellow, ref(w), ref(b), ref(y), ref(g), ref(r), ref(o));
        t[3] = thread(&searchNums, green, ref(w), ref(b), ref(y), ref(g), ref(r), ref(o));
        t[4] = thread(&searchNums, red, ref(w), ref(b), ref(y), ref(g), ref(r), ref(o));
        t[5] = thread(&searchNums, orange, ref(w), ref(b), ref(y), ref(g), ref(r), ref(o));

        for(int i=0; i<6;i++)
            t[i].join();
        if(w!=8||b!=8||y!=8||g!=8||r!=8||o!=8)  throw invalid_argument("Los datos introducidos no correspondan a un cubo real");
    }
    /**
     * Funcion de la clase
     * Imprime todas la caras de cubo indicando que cara es y sus valores
     * @author Equipo 1
     */
    void prtCube()
    {
        cout<<endl<<"Asi se ve tu cubo:"<<endl;
        cout<<"Cara Blanca:"<<endl;
        ptrFace(white);
        cout<<"Cara Azul:"<<endl;
        ptrFace(blue);
        cout<<"Cara Amarilla:"<<endl;
        ptrFace(yellow);
        cout<<"Cara Verde:"<<endl;
        ptrFace(green);
        cout<<"Cara Roja:"<<endl;
        ptrFace(red);
        cout<<"Cara Naranja:"<<endl;
        ptrFace(orange);
    }
    /**
     * Sobrecarga de la clase
     * Sobrecarga del operador cin para registrar todos los datos de los
     * aputadores a las caras del cubo
     * @author  Equipo 1
     * @param   is          Acronimo de imput
     * @param   c           Corresponde a la variable de la clase
     */
    friend istream& operator >> (istream &is, Cube &c)
    {
        wrtFace(c.white);
		wrtFace(c.blue);
		wrtFace(c.orange);
		wrtFace(c.green);
		wrtFace(c.red);
		wrtFace(c.yellow);
        return is;
    }
    /**
     * Sobrecarga de la clase
     * Sobrecarga del operador cout para imprimir todos los datos de
     * las caras de los arreglos en orden.
     * @author  Equipo 1
     * @param   os          Acronimo de output
     * @param   c           Corresponde a la variable de la clase
     */
    friend ostream& operator << (ostream &os, Cube &c)
    {
        os<<endl<<"Asi se ve tu cubo:"<<endl;
        os<<"Cara Blanca:"<<endl;
        ptrFace(c.white);
        os<<"Cara Azul:"<<endl;
        ptrFace(c.blue);
        os<<"Cara Amarilla:"<<endl;
        ptrFace(c.yellow);
        os<<"Cara Verde:"<<endl;
        ptrFace(c.green);
        os<<"Cara Roja:"<<endl;
        ptrFace(c.red);
        os<<"Cara Naranja:"<<endl;
        ptrFace(c.orange);
        return os;
    }
};
int main()
{
    //Creo un string para poder verificar luego si la opcion es correcta
    string option = "";
    bool bandera = true;
    cout<<"Bienvenido a SYC un programa que te indica como resolver tu cubo Rubik paso por paso mediante el metodo de principiantes\n"<<endl
        <<"Para resolver tu cubo necesitas indicarme la posicion de los colores en las caras, recuerda que el color de la cara es indicado por el color del centro de la misma, a continuacion,veras una rubrica de como debes representar los colores:\n"<<endl;
    Cube micubo;
    while(true)
    {
        try
        {
            if(!bandera)
            {
                while(true)
                {
                    //Verificar valor valido
                    try
                    {
                        cin>>option;
                        if(!isValidInt(option)) throw invalid_argument("Opcion invalida");
                        if(stoi(option)>2||stoi(option)<1) throw invalid_argument("Opcion invalida");
                        if(stoi(option)==2){
                            bandera=true;
                        }
                        break;
                    }catch(invalid_argument &e)
                    {
                        cout<<e.what()<<" reintroducela"<<endl;
                    }
                }
            }
            if(bandera)
            {
                cin>>micubo;
                bandera = false;
            }
            micubo.prtCube();
            cout<<"Quieres cambiar algun valor de alguna cara?"<<endl
                <<"1: Si 2: No"<<endl;
            while(true)
            {
                try
                {
                    cin>>option;
                    if(!isValidInt(option)) throw invalid_argument("Opcion invalida");
                    if(stoi(option)>2||stoi(option)<1) throw invalid_argument("Opcion invalida");
                    break;
                }catch(invalid_argument &e)
                {
                    cout<<e.what()<<" reintroducela"<<endl;
                }
            }
            if(option == "1"){
                micubo.changeFace();
                option = "";
            }
            micubo.checkcube();
            break;
        }catch(invalid_argument &e)
        {
            cout<<e.what()<<endl
                <<"Cambiar una cara de este cubo (1) o volver a introducir todo el cubo(2)"<<endl;
        }
    }
    micubo.solveCube();
    cout<<"Quieres ver las instruccion con notacion o texto (si elijes notacion se te dara una rubrica para que la entiendas)"<<endl
        <<"1. Notacion"<<endl
        <<"2. Texto"<<endl;
    do{
        //Verificar valor valido
        try{
            cin>>option;
            if(!isValidInt(option)) throw option;
            if(stoi(option)>2 || stoi(option)<1)  throw option;
        }catch(string &e){
            cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
            option = "";
        }
    }while(!isValidInt(option));
    switch(stoi(option))
    {
        case 1:
            ptrPasosConNotacion();
            break;
        case 2:
            ptrPasosSinNotacion();
            break;
    }
    return 0;
}
/**
* Imprime el menu para conocer la rubrica de colores y en que cara de color te encuentras
* @author   Equipo 1    
* @param    color        Una variable que permite nos permite imprimir en que cara nos encontramos dentro de un orden
*/
void displayMenu(int color)
{
    cout<<"El orden de los colores se representa de arriba hacia abajo de izquierda a derecha como se indica a continuacion"<<endl
        <<" -------"<<endl
        <<" |1|2|3|"<<endl
        <<" |4|5|6|"<<endl
        <<" |7|8|9|"<<endl
        <<"Rubrica de colores"<<endl
        <<"1 = Blanco   2 = Amarillo    3 = Naranja"<<endl
        <<"4 = Verde    5 = Azul        6 = Rojo"<<endl
        <<"7 = Reintroducir una posicion\n"<<endl;
    switch(color)
    {
        case 0:
            cout<<"Cara Blanca (se mira poniendo la cara azul debajo):"<<endl;
            break;
        case 1:
            cout<<"Cara Azul (Teniendo la cara blanca arriba):"<<endl;
            break;
        case 2:
            cout<<"Cara Naranja (Teniendo la cara blanca arriba):"<<endl;
            break;
        case 3:
            cout<<"Cara Verde (Teniendo la cara blanca arriba):"<<endl;
            break;
        case 4:
            cout<<"Cara Rojo (Teniendo la cara blanca arriba):"<<endl;
            break;
        case 5:
            cout<<"Cara Amarilla (Teniendo la cara azul arriba):"<<endl;
            break;
    }
}
/**
 * Registra los datos de un arreglo, que en este caso seran las caras
 * de el cubo.
 * @author  Equipo 1
 * @param   arr         corresponde a el apuntador de una cara del cubo
 */
void wrtFace(int *arr)
{
    string color_num = "";
    int static color = 0;
    for(int i=0; i<9; i++)
    {
        arr[i] = 0;
    }
    switch(color%6)
    {
        case 0:
            arr[4] = 1;
            break;
        case 1:
            arr[4] = 5;
            break;
        case 2:
            arr[4] = 3;
            break;
        case 3:
            arr[4] = 4;
            break;
        case 4:
            arr[4] = 6;
            break;
        case 5:
            arr[4] = 2;
            break;
    }
    for(int i=0; i<9; i++)
    {
        if(i==4)    continue;
        displayMenu(color);
        ptrFace(arr);   
        try{
            cin>>color_num;
            if(!isValidInt(color_num))    throw color_num;
            if(stoi(color_num)<1 || stoi(color_num)>7)  throw color_num;
            if(color_num=="7"){
                change_num(arr);
                i--;
            }
            else{
	            arr[i]=stoi(color_num);
            }
	    }catch(string &e){
	    	cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
	    	i--;
            system("pause");
		}
        system("cls" );
    }
    color++;
}
/**
 * Permite cambiar un valor del arreglo en el que se encuentra
 * @author  Equipo 1
 * @param   arr         corresponde a el apuntador de una cara del cubo
 */
void change_num(int *arr)
{
    string pos = "", color_num = "";
    cout<<"Que posicion? ";
    do{
        try{
            cin>>pos;
            if(!isValidInt(pos))    throw pos;
            if(stoi(pos)<1 || stoi(pos)>9 || pos=="5")  throw pos;
            cout<<"Introduce el nuevo numero:"<<endl;
            do{
                try{
                    cin>>color_num;
                    if(!isValidInt(color_num))    throw color_num;
                    if(stoi(color_num)<1 || stoi(color_num)>6)  throw color_num;
                    arr[stoi(pos)-1] = stoi(color_num);
                }catch(string &e){
                    cout<<"El valor \""<<e<<"\" es invalido"<<endl;
                }
            }while(!isValidInt(color_num));
        }catch(string &e){
            cout<<"El valor \""<<e<<"\" es invalido"<<endl;
        }
    }while(!isValidInt(pos));
}
/**
 * Imprimir el arreglo de una cara viendose como una cara del cubo.
 * @author  Equipo 1
 * @param   arr         corresponde a el apuntador de una cara del cubo
 */
void ptrFace(int *arr)
{
    for(int i=0;i<9;i++){
        if(i!=0 && i%3==0)  cout<<" |"<<endl<<" -------------"<<endl;
        if(i==0)  cout<<" -------------"<<endl;
        if(arr[i]==0)   cout<<" |  ";
		else    cout<<" | "<<arr[i];
	}
    cout<<" |"<<endl<<" -------------"<<endl;
}
/**
 * Analiza si el string es un numero entero valido
 * @author  Equipo 1
 * @param   arr         corresponde a el apuntador de una cara del cubo
 * @return  <code>true</code> si es un entero valido
*           <code>false</code> si es otra cosa
 */
bool isValidInt(string valid_numeroEnCadena)
{
    bool valido = true;
    int tamanioDeCadena = valid_numeroEnCadena.size();
    if(tamanioDeCadena == 0)    valido = false;
    for(int i=0; valido && i<tamanioDeCadena; i++)
    {
        if(!isdigit(valid_numeroEnCadena.at(i)))
        valido = false;
    }
    return valido;
}
/**
 * Busca y contabiliza la cantidad de numeros del 1-6 que hay, dentro de el arreglo
 * que corresponde a una cara del cubo.
 * @author  Equipo 1
 * @param   arr         corresponde a el apuntador de una cara del cubo
 * @param   w           contara la cantidad de caras blancas
 * @param   b           contara la cantidad de caras azules
 * @param   y           contara la cantidad de caras amarillas
 * @param   g           contara la cantidad de caras verdes
 * @param   r           contara la cantidad de caras rojas
 * @param   o           contara la cantidad de caras naranjas
 */
void searchNums(int arr[], int &w, int &b, int &y, int &g, int &r, int &o)
{
    for(int i=0; i<9; i++)
    {
        if(i==4)    i++;
        switch(arr[i])
        {
            case 1:
                mymutex[0].lock();
                w++;
                mymutex[0].unlock();
                break;
            case 2:
                mymutex[1].lock();
                y++;
                mymutex[1].unlock();
                break;
            case 3:
                mymutex[2].lock();
                o++;
                mymutex[2].unlock();
                break;
            case 4:
                mymutex[3].lock();
                g++;
                mymutex[3].unlock();
                break;
            case 5:
                mymutex[4].lock();
                b++;
                mymutex[4].unlock();
                break;
            case 6:
                mymutex[5].lock();
                r++;
                mymutex[5].unlock();
                break;
        }
    }
}
/**
 * Imprimira los pasos se siguo mientras se armaba el cubo con intrucciones
 * escritas de manera de que cualquiera lo pueda entender.
 * @author  Equipo 1
 */
void ptrPasosSinNotacion()
{
    int j=0, pasosResumidos[500], aux=0;
    string numPasos = "";
    int k = pasosRepetidos(pasosResumidos);

    cout<<"¿Cuantos pasos quieres que se desplieguen a la vez? (Cuando termines de hacerlos presiona cualqueir boton)"<<endl;
    do{
        try{
            cin>>numPasos;
            if(!isValidInt(numPasos)) throw numPasos;
            if(stoi(numPasos)<1)  throw numPasos;
        }catch(string &e){
            cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
            numPasos = "";
        }
    }while(!isValidInt(numPasos));
    aux = stoi(numPasos);
    cout<<"\nTodos los pasos se hacen mirando la cara BLANCA teniendo la cara AZUL debajo"<<endl;
    for(int i=0; i<k; i++)
    {
        if(pasosResumidos[i]==pasosResumidos[i+1]&&pasosResumidos[i+1]==pasosResumidos[i+2])
        {
            cout<<"["<<j+1<<"] ";
            switch(pasosResumidos[i])
            {
                case 1:
                    cout<<"Parte derecha hacia arriba"<<endl;
                    break;
                case 2:
                    cout<<"Parte inferior a la izquierda"<<endl;
                    break;
                case 3:
                    cout<<"Parte izquierda hacia arriba"<<endl;
                    break;
                case 4:
                    cout<<"Parte superior a la izquierda"<<endl;
                    break;
                case 5:
                    cout<<"Cara frontal a la izquierda"<<endl;
                    break;
                case 6:
                    cout<<"Cara trasera a la izquierda"<<endl;
                    break;
            }
            i+=2;
            j++;
        }
        else
        {
            cout<<"["<<j+1<<"] ";
            if(pasosResumidos[i]==pasosResumidos[i+1])
            {
                cout<<"x2 ";
                i++;
            }
            switch(pasosResumidos[i])
            {
                case 1:
                    cout<<"Parte derecha hacia abajo"<<endl;
                    break;
                case 2:
                    cout<<"Parte inferior hacia la derecha"<<endl;
                    break;
                case 3:
                    cout<<"Parte izquierda hacia abajo"<<endl;
                    break;
                case 4:
                    cout<<"Parte superior hacia la derecha"<<endl;
                    break;
                case 5:
                    cout<<"Cara frontal a la derecha"<<endl;
                    break;
                case 6:
                    cout<<"Cara trasera a la derecha"<<endl;
                    break;
            }
            j++;
        }
        if(j==aux)
        {
            system("pause");
            aux+=stoi(numPasos);
        }
    }
}
/**
 * Imprimira los pasos se siguo mientras se armaba el cubo con intrucciones
 * escritas con la notacion utilizada comunmente para pasos en el cubo rubik.
 * @author  Equipo 1
 */
void ptrPasosConNotacion()
{
    setlocale(LC_CTYPE, "Spanish");
    int j=0, l=0, pasosResumidos[500], aux;
    string numPasos = "";
    int k = pasosRepetidos(pasosResumidos);

    cout<<"Todos los pasos se hacen teniendo la cara BLANCA como superior, la AMARILLA como inferior y se mira de frente la cara AZUL"<<endl
        <<"------------------------------------------------------------------------------------------------------|"<<endl
        <<"|     U = Up     |    D = Down    |    R = Right   |    L = Left    |    F = Front   |    B = Back    |"<<endl
        <<"|----------------|----------------|----------------|----------------|----------------|----------------|"<<endl
        <<"|   Es girar la  |   Es girar la  |   Es girar la  |   Es girar la  |   Es girar la  |   Es girar la  |"<<endl
        <<"|  cara superior |  cara inferior |  parte derecha | parte izquierda|  cara frontal  |  cara tracera  |"<<endl
        <<"|   en sentido   |    en sentido  |   en sentido   |   en sentido   |   en sentido   |   en sentido   |"<<endl
        <<"|    horario     |     horario    |     horario    |    horario     |    horario     |    horario     |"<<endl
        <<"|  <-|X|X|X|     |     | | | |    |     | | |X| ^  |     |X| | |    |    |X|X|X|     |    | | | |     |"<<endl
        <<"|    | | | |     |     | | | |    |     | | |X| |  |   | |X| | |    |    |X|X|X| ->  | <- | | | |     |"<<endl
        <<"|    | | | |     |     |X|X|X|->  |     | | |X|    |   V |X| | |    |    |X|X|X|     |    | | | |     |"<<endl
        <<"------------------------------------------------------------------------------------------------------|"<<endl
        <<"Cuando se dice en sentido horario se refiere a como si vieras la cara que estas girando de frente.\nSi la letra esta acompanada por el simbolo \' (prima) significa que va en direccion anti-horaria\n"<<endl;

    cout<<"En cuantos pasos quieres ir avanzando? (Cuando termines de hacerlos presiona cualquier boton)"<<endl;

    do{
        //Verificar valor valido
        try{
            cin>>numPasos;
            if(!isValidInt(numPasos)) throw numPasos;
            if(stoi(numPasos)<1)  throw numPasos;
        }catch(string &e){
            cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
            numPasos = "";
        }
    }while(!isValidInt(numPasos));
    aux = stoi(numPasos);
    for(int i=0; i<k; i++)
    {
        if(pasosResumidos[i]==pasosResumidos[i+1]&&pasosResumidos[i+1]==pasosResumidos[i+2])
        {
            cout<<"["<<j+1<<"] ";
            switch(pasosResumidos[i])
            {
                case 1:
                    cout<<"R"<<endl;
                    break;
                case 2:
                    cout<<"F\'"<<endl;
                    break;
                case 3:
                    cout<<"L\'"<<endl;
                    break;
                case 4:
                    cout<<"B"<<endl;
                    break;
                case 5:
                    cout<<"U\'"<<endl;
                    break;
                case 6:
                    cout<<"D"<<endl;
                    break;
            }
            i+=2;
            j++;
        }
        else
        {
            cout<<"["<<j+1<<"] ";
            if(pasosResumidos[i]==pasosResumidos[i+1])
            {
                cout<<"x2 ";
                i++;
            }
            switch(pasosResumidos[i])
            {
                case 1:
                    cout<<"R\'"<<endl;
                    break;
                case 2:
                    cout<<"F"<<endl;
                    break;
                case 3:
                    cout<<"L"<<endl;
                    break;
                case 4:
                    cout<<"B\'"<<endl;
                    break;
                case 5:
                    cout<<"U"<<endl;
                    break;
                case 6:
                    cout<<"D\'"<<endl;
                    break;
            }
            j++;
        }
        if(j==aux)
        {
            system("pause");
            aux+=stoi(numPasos);
        }
    }
}
/**
 * Resumira los pasos registrados, si hay 4 instrucciones iguales seguidas las borra devido
 * a que hacer 4 movimientos iguales seguidos es equivalente a no mover nada.
 * @author  Equipo 1
 * @param   pasosResumidos  Un arreglo para guardar los pasos depsues de haberse resumido al maximo
 * @return  k               Que corresponde a la cantidad de pasos que tiene el nuevo arreglo
 */
int pasosRepetidos(int pasosResumidos[])
{
    int j=0, k=0, auxi[800];
    for(int i=0; i<counter; i++)
    {
        if(pasos[i]==pasos[i+1]&&pasos[i+1]==pasos[i+2]&&pasos[i+2]==pasos[i+3])
            i+=3;
        else
        {
            switch(pasos[i])
            {
                case 1:
                    auxi[j]=pasos[i];
                    break;
                case 2:
                    auxi[j]=pasos[i];
                    break;
                case 3:
                    auxi[j]=pasos[i];
                    break;
                case 4:
                    auxi[j]=pasos[i];
                    break;
                case 5:
                    auxi[j]=pasos[i];
                    break;
                case 6:
                    auxi[j]=pasos[i];
                    break;
            }
            j++;
        }
    }
    for(int i=0; i<j; i++)
    {
        if(auxi[i]==auxi[i+1]&&auxi[i+1]==auxi[i+2]&&auxi[i+2]==auxi[i+3])
            i+=3;
        else
        {
            switch(auxi[i])
            {
                case 1:
                    pasosResumidos[k]=auxi[i];
                    break;
                case 2:
                    pasosResumidos[k]=auxi[i];
                    break;
                case 3:
                    pasosResumidos[k]=auxi[i];
                    break;
                case 4:
                    pasosResumidos[k]=auxi[i];
                    break;
                case 5:
                    pasosResumidos[k]=auxi[i];
                    break;
                case 6:
                    pasosResumidos[k]=auxi[i];
                    break;
            }
            k++;
        }
    }
    return (k);
}
