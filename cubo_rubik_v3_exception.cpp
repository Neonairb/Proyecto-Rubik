#include <bits/stdc++.h>
using namespace std;

int pasos[1000];
int counter=0;

void displayMenu(int color);
void ptrPasosSinNotacion();
void ptrPasosConNotacion();
void wrtFace(int *arr);
void ptrFace(int *arr);
int pasosRepetidos(int p[1000], int s[500]);
void face(string p[9]);
bool isValidInt(string valid_numeroEnCadena);

struct Cube
{
    int *white, *yellow, *orange, *green, *red, *blue;
	Cube(){
		try{
			white= new (nothrow) int[9];
	    	yellow= new (nothrow) int[9];
	    	orange= new (nothrow) int[9];
	    	green= new (nothrow) int[9];
	    	red= new (nothrow) int[9];
	    	blue= new (nothrow) int[9];
		}catch(bad_alloc& error){
			cout<<"No se pudo reservar memoria";
			exit(-1);
		}
	    setlocale(LC_CTYPE, "Spanish");

		wrtFace(white);
		wrtFace(blue);
		wrtFace(orange);
		wrtFace(green);
		wrtFace(red);
		wrtFace(yellow);
	}
	void rotRightDown()
    {
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

        int auxi[9] = {orange[0], orange[1], orange[2], orange[3], orange[4], orange[5], orange[6], orange[7], orange[8]};
        orange[0]=auxi[2];
        orange[1]=auxi[5];
        orange[2]=auxi[8];
        orange[3]=auxi[1];
        orange[5]=auxi[7];
        orange[6]=auxi[0];
        orange[7]=auxi[3];
        orange[8]=auxi[6];

        pasos[counter]=1;
        counter+=1;
    }
    void rotRightUp()
    {
        rotRightDown();
        rotRightDown();
        rotRightDown();
    }
    void rotLeftDown()
    {
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

        int auxi[9] = {red[0], red[1], red[2], red[3], red[4], red[5], red[6], red[7], red[8]};
        red[0]=auxi[6];
        red[1]=auxi[3];
        red[2]=auxi[0];
        red[3]=auxi[7];
        red[5]=auxi[1];
        red[6]=auxi[8];
        red[7]=auxi[5];
        red[8]=auxi[2];
        pasos[counter]=3;
        counter+=1;
    }
    void rotLeftUp()
    {
        rotLeftDown();
        rotLeftDown();
        rotLeftDown();
    }
    void rotUpRight()
    {
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

        int auxi[9] = {green[0], green[1], green[2], green[3], green[4], green[5], green[6], green[7], green[8]};
        green[0]=auxi[2];
        green[1]=auxi[5];
        green[2]=auxi[8];
        green[3]=auxi[1];
        green[5]=auxi[7];
        green[6]=auxi[0];
        green[7]=auxi[3];
        green[8]=auxi[6];

        pasos[counter]=4;
        counter+=1;
    }
    void rotUpLeft()
    {
        rotUpRight();
        rotUpRight();
        rotUpRight();
    }
    void rotDownRight()
    {
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

        int auxi[9] = {blue[0], blue[1], blue[2], blue[3], blue[4], blue[5], blue[6], blue[7], blue[8]};
        blue[0]=auxi[6];
        blue[1]=auxi[3];
        blue[2]=auxi[0];
        blue[3]=auxi[7];
        blue[5]=auxi[1];
        blue[6]=auxi[8];
        blue[7]=auxi[5];
        blue[8]=auxi[2];

        pasos[counter]=2;
        counter+=1;
    }
    void rotDownLeft()
    {
        rotDownRight();
        rotDownRight();
        rotDownRight();
    }
    void rotFaceForwRight()
    {
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

        int auxi[9] = {white[0], white[1], white[2], white[3], white[4], white[5], white[6], white[7], white[8]};
        white[0]=auxi[6];
        white[1]=auxi[3];
        white[2]=auxi[0];
        white[3]=auxi[7];
        white[5]=auxi[1];
        white[6]=auxi[8];
        white[7]=auxi[5];
        white[8]=auxi[2];

        pasos[counter]=5;
        counter+=1;
    }
    void rotFaceForwLeft()
    {
        rotFaceForwRight();
        rotFaceForwRight();
        rotFaceForwRight();
    }
    void rotFaceBackRight()
    {
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

        int auxi[9] = {yellow[0], yellow[1], yellow[2], yellow[3], yellow[4], yellow[5], yellow[6], yellow[7], yellow[8]};
        yellow[0]=auxi[2];
        yellow[1]=auxi[5];
        yellow[2]=auxi[8];
        yellow[3]=auxi[1];
        yellow[5]=auxi[7];
        yellow[6]=auxi[0];
        yellow[7]=auxi[3];
        yellow[8]=auxi[6];

        pasos[counter]=6;
        counter+=1;
    }
    void rotFaceBackLeft()
    {
        rotFaceBackRight();
        rotFaceBackRight();
        rotFaceBackRight();
    }
    void permutateSupCross(int o[9], int g[9], int b[9], int r[9])
    {
        while(o[1]!=3 || g[1]!=4 || b[1]!=5 || r[1]!=6)
        {
            for(int i=0; i<4; i++)
            {
                if(b[1]==5 && o[1]==3)
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
                if(o[1]==3 && g[1]==4)
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
                if(g[1]==4 && r[1]==6)
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
                if(r[1]==6 && b[1]==5)
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
            if(o[1]!=3 || g[1]!=4 || b[1]!=5 || r[1]!=6)
            {
                for(int i=0; i<4; i++)
                {
                    if(o[1]==3 && r[1]==6)
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
                        if(b[1]==5 && g[1]==4)
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
    void permutateInfCross(int o[9], int g[9], int b[9], int r[9])
    {
        while(o[7]!=3 || g[7]!=4 || b[7]!=5 || r[7]!=6)
        {
            for(int i=0; i<4; i++)
            {
                if(b[7]==5 && o[7]==3)
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
                if(o[7]==3 && g[7]==4)
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
                if(g[7]==4 && r[7]==6)
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
                if(r[7]==6 && b[7]==5)
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
            if(o[7]!=3 || g[7]!=4 || b[7]!=5 || r[7]!=6)
            {
                for(int i=0; i<4; i++)
                {
                    if(o[7]==3 && r[7]==6)
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
                        if(b[7]==5 && g[7]==4)
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
    void makeSupCross()
    {
        int i=0, j=0;
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
        permutateSupCross(orange, green, blue, red);
    }
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
    void makeLatEdge()
    {
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
    void makeInfCross()
    {
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
        permutateInfCross(orange, green, blue, red);
    }
    void makeInfFace()
    {
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
    void solveCube()
    {
        makeSupCross();
        makeSupFace();
        makeLatEdge();
        makeInfCross();
        makeInfFace();
    }
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
    void prtCube()
    {
        setlocale(LC_CTYPE, "Spanish");
        cout<<endl<<"Resultado:"<<endl;
        cout<<"Blanca:"<<endl;
        ptrFace(white);
        cout<<"Az�l:"<<endl;
        ptrFace(blue);
        cout<<"Amarilla:"<<endl;
        ptrFace(yellow);
        cout<<"Verde:"<<endl;
        ptrFace(green);
        cout<<"Roja:"<<endl;
        ptrFace(red);
        cout<<"Naranja:"<<endl;
        ptrFace(orange);
    }
};
int main()
{
    setlocale(LC_CTYPE, "Spanish");
    int option=0;
    cout<<"Bienvenido a SYC un programa que te indica c�mo resolver tu cubo Rubik paso por paso\n"<<endl
        <<"Para resolver tu cubo necesitas indicarme la posici�n de los colores en las caras, recuerda que el color de la cara es indicado por el color del centro de la misma, a continuaci�n,veras una r�brica de como debes representar los colores:\n"<<endl
        <<"El orden de los colores se representa de arriba hacia abajo de izquierda a derecha como se indica a continuaci�n"<<endl;
    Cube micubo;
    micubo.solveCube();
    //micubo.prtCube();
    cout<<"Quieres ver las instrucci�n con notaci�n o texto (si elijes notaci�n se te dar� una rubrica para que la entiendas)"<<endl
        <<"1. Notaci�n"<<endl
        <<"2. Texto"<<endl;
    while(option>2 || option<1)
    {
        cin>>option;
        if(option>2 || option<1)    cout<<"Numero invalido, intentalo denuevo"<<endl;
    }
    switch(option)
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
void displayMenu(int color)
{
    setlocale(LC_CTYPE, "Spanish");
    switch(color)
    {
        case 0:
            cout<<"Cara Blanca (se mira poniendo la cara az�l debajo):"<<endl;
            break;
        case 1:
            cout<<"Cara Az�l (Teniendo la cara blanca arriba):"<<endl;
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
    cout<<" |1|2|3|"<<endl
        <<" |4|5|6|"<<endl
        <<" |7|8|9|"<<endl
        <<"R�brica de colores"<<endl
        <<"1 = Blanco   2 = Amarillo    3 = Naranja"<<endl
        <<"4 = Verde    5 = Azúl        6 = Rojo"<<endl
        <<"7 = Reintroducir una posicion\n"<<endl;
}
void wrtFace(int *arr)
{
    setlocale(LC_CTYPE, "Spanish");
    string n = "", pos = "", p[9];
    int static color = 0;
    for(int i=0; i<9; i++)
    {
        p[i] = " ";
    }
    switch(color)
    {
        case 0:
            p[4] ='1';
            break;
        case 1:
            p[4]='5';
            break;
        case 2:
            p[4]='3';
            break;
        case 3:
            p[4]='4';
            break;
        case 4:
            p[4]='6';
            break;
        case 5:
            p[4]='2';
            break;
    }
    p[0] = '*';
    for(int i=0; i<9; i++)
    {
        if(i==4)    continue;
        displayMenu(color);
        p[i] = '*';
        face(p);   
        try{
	        
            while(!isValidInt(n))
            {
                cin>>n;
                if(!isValidInt(n))    throw n;
                if(stoi(n)<1 || stoi(n)>7)  throw n;
            }
            p[i] = n;
            n = "";
            if(p[i]=="7")
            {
                cout<<"¿Que posición? ";
                while(!isValidInt(pos)){
                    try{
                        cin>>pos;
                        if(!isValidInt(pos))    throw pos;
                        if(stoi(pos)<1 || stoi(pos)>9 || pos=="5")  throw pos;
                        cout<<"Introduce el nuevo numero:"<<endl;
                        while(!isValidInt(n)){
                            try{
                                cin>>n;
                                if(!isValidInt(n))    throw n;
                                if(stoi(n)<1 || stoi(n)>6)  throw n;
                                p[stoi(pos)-1] = n;
                                i--;
                            }catch(string &e){
                                cout<<"El valor \""<<e<<"\" es invalido"<<endl;
                                n = "";
                            }
                        }
                        n = "";
                    }catch(string &e){
                        cout<<"El valor \""<<e<<"\" es invalido"<<endl;
                        pos = "";
                    }
                }
                pos = "";
            }
	        arr[i]=stoi(p[i]);
	    }catch(string &e){
	    	cout<<"El valor \""<<e<<"\" no es valido, reintroducelo"<<endl;
            n = "";
	    	i--;
            system("pause");
		}
        system("cls" );
    }
    color++;
}
void face(string p[9]){
	for(int i=0;i<9;i++){
        if(i!=0 && i%3==0)  cout<<" |"<<endl<<" -------------"<<endl;
        if(i==0)  cout<<" -------------"<<endl;
		cout<<" | "<<p[i];
	}
    cout<<" |"<<endl<<" -------------"<<endl;
}
void ptrFace(int *arr)
{
    for(int i=0; i<9; i++)
    {
        cout<<(arr[i])<<" ";
        if(i==2 || i==5 || i==8)
            cout<<endl;
    }
}
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
void ptrPasosSinNotacion()
{
    setlocale(LC_CTYPE, "Spanish");
    int j=0, pR[500], numPasos=0, aux=0;
    int k = pasosRepetidos(pasos, pR);

    cout<<"�Cuantos pasos quieres que se desplieguen a la vez? (Cuando termines de hacerlos presiona cualqueir bot�n)"<<endl;
    cin>>numPasos;
    while(numPasos<1)
    {
        cout<<"N�mero de pasos invalidos, introduce denuevo"<<endl;
        cin>>numPasos;
    }
    aux = numPasos;
    cout<<"\nTodos los pasos se hacen mirando la cara BLANCA teniendo la cara AZ�L debajo"<<endl;
    for(int i=0; i<k; i++)
    {
        if(pR[i]==pR[i+1]&&pR[i+1]==pR[i+2])
        {
            cout<<"["<<j+1<<"] ";
            switch(pR[i])
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
            if(pR[i]==pR[i+1])
            {
                cout<<"x2 ";
                i++;
            }
            switch(pR[i])
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
        if(j==numPasos)
        {
            system("pause");
            numPasos+=aux;
        }
    }
}
void ptrPasosConNotacion()
{
    setlocale(LC_CTYPE, "Spanish");
    int j=0, l=0, pR[500], numPasos, aux;
    int k = pasosRepetidos(pasos, pR);

    cout<<"Todos los pasos se hacen teniendo la cara BLANCA como superior, la AMARILLA como inferior y se mira de frente la cara AZ�L"<<endl
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
        <<"Cuando se dice en sentido horario se refiere a como si vieras la cara que estas girando de frente.\nSi la letra est� acompa�ada por el s�mbolo \' (prima) significa que va en direcci�n anti-horaria\n"<<endl;

    cout<<"�En cuantos pasos quieres ir avanzando? (Cuando termines de hacerlos presiona cualquier bot�n)"<<endl;

    cin>>numPasos;
    while(numPasos<1)
    {
        cout<<"N�mero de pasos invalidos, reintroducelo"<<endl;
        cin>>numPasos;
    }
    aux = numPasos;
    for(int i=0; i<k; i++)
    {
        if(pR[i]==pR[i+1]&&pR[i+1]==pR[i+2])
        {
            cout<<"["<<j+1<<"] ";
            switch(pR[i])
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
            if(pR[i]==pR[i+1])
            {
                cout<<"x2 ";
                i++;
            }
            switch(pR[i])
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
        if(j==numPasos)
        {
            system("pause");
            numPasos+=aux;
        }
    }
}
int pasosRepetidos(int p[1000], int s[800])
{
    int j=0, k=0, auxi[800];
    for(int i=0; i<counter; i++)
    {
        if(p[i]==p[i+1]&&p[i+1]==p[i+2]&&p[i+2]==p[i+3])
            i+=3;
        else
        {
            switch(p[i])
            {
                case 1:
                    auxi[j]=p[i];
                    break;
                case 2:
                    auxi[j]=p[i];
                    break;
                case 3:
                    auxi[j]=p[i];
                    break;
                case 4:
                    auxi[j]=p[i];
                    break;
                case 5:
                    auxi[j]=p[i];
                    break;
                case 6:
                    auxi[j]=p[i];
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
                    s[k]=auxi[i];
                    break;
                case 2:
                    s[k]=auxi[i];
                    break;
                case 3:
                    s[k]=auxi[i];
                    break;
                case 4:
                    s[k]=auxi[i];
                    break;
                case 5:
                    s[k]=auxi[i];
                    break;
                case 6:
                    s[k]=auxi[i];
                    break;
            }
            k++;
        }
    }
    return (k);
}
