
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAL 1000 //Solo para validar opción
#define CODEMAX 80

//Menu de opciones
int menu(int agregado){
    int opc_menu=0;
    char prov[VAL];
    if (agregado==0)
    {
        printf("1 Ingresar tabla de la función de codificación en forma manual\n");
        printf("2 Ingresar tabla desde fichero\n");
        printf("0 Salir\n");
        printf("Elija su opción:");
        scanf("%s",prov);
        opc_menu=atoi(prov);
        while(opc_menu>2||opc_menu<0)
        {
            printf("Opción no válida\n");
            printf("Elija su opción (1,2,0):");
            scanf("%s",prov);
            opc_menu=atoi(prov);
            
        }
        fflush(stdin);
    }
    else
    {
        printf("1 Cambiar tabla de la función de codificación en forma manual\n");
        printf("2 Cambiar tabla desde fichero\n");
        printf("3 Decodificación de texto por teclado\n");
        printf("4 Decodificación de texto por fichero \n");
        printf("5 Codificación de texto por teclado\n");
        printf("6 Codificación de texto por fichero \n");
        printf("0 Salir\n");
        printf("Elija su opción:");
        scanf("%s",prov);
        opc_menu=atoi(prov);
        while(opc_menu>6||opc_menu<0)
        {
            printf("Opción no válida\n");
            printf("Elija su opción (1,2,3,4,5,6,0):");
            scanf("%s",prov);
            opc_menu=atoi(prov);
            
        }
        fflush(stdin);

    }
    
    return opc_menu;
}

//Introducción del número de caracteres en forma manual
int nummanual(){
    char caracteres='A';
    int total_car=0;
    int aux=0;
    char prov[VAL];
    int repetir=0;
    //Validación bien
    while (total_car<1)
    {
        printf("\nIntroduzca el número de caracteres a codificar (Ejemplo Alfabeto inglés 26):");
        scanf("%s",prov);
        total_car=atoi(prov);
    }
    fflush(stdin);
    return total_car;
}

// Recibimos las palabras reales
char dic_decodificar(int number){
    char prov[VAL];
    char taken;
    printf("\nIntroduzca el caracter %d por codificar:",number+1);
    scanf("%s",prov);
    taken=prov[0];
    fflush(stdin);
    return taken;
}

// Recibimos las palabras en código
char *dic_codificar(int number){
    char prov[VAL];
    char *type;
    int sz;
    printf("Introduzca el código del caracter %d:",number+1);
    scanf("%s",prov);
    sz=strlen(prov);
    fflush(stdin);
    type = malloc(sz);  // allocate memory from the heap
    strncpy(type, prov, sz);
    //printf("Numero introducido:%s\n",type);
    return(type);

}

//A) Decidir si el código es instantáneo
int verificaInstantaneo(char **diccodigo,int total)
{
    char *actual;
    int cmpcar=0;
    int instantaneo=1;
    int auxiliar=1;
    int palauxiliar=0;
    int carauxiliar=0;
    int desplazadic=0;
    //Reservamos memoria para el array de verificación
    actual=(char *)malloc(sizeof(long)*sizeof(char));
    while (auxiliar<total)
    {
        strcpy(actual,diccodigo[auxiliar]);
        while (palauxiliar<auxiliar)
        {
            //Comparación de caracteres para ver si alguno es prefijo del otro
            while(actual[carauxiliar]==diccodigo[palauxiliar][carauxiliar])
            {
                carauxiliar+=1;
            }
            if(actual[carauxiliar]=='\0'||diccodigo[palauxiliar][carauxiliar]=='\0')
            //Si alguno llega a nulo significa que recorrió comparando el actual con la palabra de código en el índice palauxiliar y al terminar la comparación con la finalización de alguno, entonces alguno de éstos es prefijo del otro y por lo tanto ya no es código instantáneo
            {
                instantaneo=0;
                return instantaneo;
            }
            carauxiliar=0;
            palauxiliar+=1;
        }
        palauxiliar=0;
        auxiliar+=1;
    }
    return instantaneo;
}

//B) Recibir palabras codificadas y las decodifique procediendo de forma voraz
void decodifica_manual(char *dicreal,char **diccodigo,int total)
{
    char texto[VAL];
    char textodecod[VAL];
    char decoder='A';
    int indicedecod=0;
    int cambio=0;
    int indice=0;
    int error=0;
    int indicetotal=0;
    int aux;
    char archivo[50];
    char opcion_guardar[VAL];
    FILE *f;
    char cadena[VAL];
    printf("Introduzca el texto a decodificar y al finalizar presione enter:");
    scanf("%s",&texto);
    while (decoder!='\0')
    {
        decoder=texto[indicetotal];
        if (decoder=='\0')
        {
            texto[indicetotal]='\0';
            break;
        }
        cadena[indice]=decoder;
        cadena[indice+1]='\0';
        //Verificar si la cadena actual se encuentra en el diccionario, si no hay que adjuntar otro caracter
        for (aux=0;aux<total;aux++)
        {
            if(strcmp(cadena,diccodigo[aux])==0)
            //Como se trata de código instantáneo, la palabra ya se encontró
            {
                textodecod[indicedecod]=dicreal[aux];
                indicedecod+=1;
                cambio=1;
                break;
            }
        }
        //Si hubo cambio, hay que decodificar la siguiente palabra
        if(cambio==1)
        {
            indice=0;
            cambio=0;
        }
        else
        {
            indice+=1;
        }
        indicetotal+=1;
    }
    //Hay palabras erróneas
    if(indice!=0)
    {
        textodecod[indicedecod]='\0';
        if(textodecod[0]=='\0')
        {
            printf("Error: El texto introducido no es parte del código introducido\n");
            error=1;
        }
        else
        {
            printf("El texto introducido contiene errores, la parte que se pudo traducir dice:\n%s\nFavor de verificarlo bien\n",textodecod);
        
        }
    }
    else
    {
        textodecod[indicedecod]='\0';
        printf("El texto decodificado es:\n%s\n",textodecod);
    }
    if(error!=1)
    {
        printf("¿Desea guardar el texto decodificado (S/N)?:");
        scanf("%s",opcion_guardar);
        while(opcion_guardar[0]!='s'&&opcion_guardar[0]!='S'&&opcion_guardar[0]!='n'&&opcion_guardar[0]!='N')
        {
            printf("Opción no válida\n");
            printf("Elija su opción (S/N):");
            scanf("%s",opcion_guardar);
        }
        if (opcion_guardar[0]=='S'||opcion_guardar[0]=='s')
        {
            printf("Introduzca el nombre de archivo con su extensión (ejemplo archivo1.txt):");
            scanf("%s",&archivo);
            f=fopen(archivo,"w+");
            fprintf(f,"%s",textodecod);
            fclose(f);
            printf("Archivo creado exitosamente: %s\n",archivo);
        }
    }
    
}

//Decodificación desde archivo
void decodifica_archivo(char *dicreal,char **diccodigo, int total, char *texto)
{
        char textodecod[VAL];
        char decoder='A';
        int indicedecod=0;
        int cambio=0;
        int indice=0;
        int indicetotal=0;
        int aux;
        int error=0;
        char cadena[VAL];
        char archivo[50];
        char opcion_guardar[VAL];
        FILE *f;
        while (decoder!='\0')
        {
            decoder=texto[indicetotal];
            if (decoder=='\0')
            {
                texto[indicetotal]='\0';
                break;
            }
            cadena[indice]=decoder;
            cadena[indice+1]='\0';
            //Verificar si la cadena actual se encuentra en el diccionario, si no hay que adjuntar otro caracter
            for (aux=0;aux<total;aux++)
            {
                if(strcmp(cadena,diccodigo[aux])==0)
                    //Como se trata de código instantáneo, la palabra ya se encontró
                {
                    textodecod[indicedecod]=dicreal[aux];
                    indicedecod+=1;
                    cambio=1;
                    break;
                }
            }
            //Si hubo cambio, hay que decodificar la siguiente palabra
            if(cambio==1)
            {
                indice=0;
                cambio=0;
            }
            else
            {
                indice+=1;
            }
            indicetotal+=1;
        }
        //Hay palabras erróneas
        if(indice!=0)
        {
            textodecod[indicedecod]='\0';
            if(textodecod[0]=='\0')
            {
                printf("Error: El texto introducido no es parte del código introducido\n");
                error=1;
            }
            else
            {
                printf("El texto introducido contiene errores, la parte que se pudo traducir dice:\n%s\nFavor de verificarlo bien\n",textodecod);

            }
        }
        else
        {
            textodecod[indicedecod]='\0';
            printf("El texto decodificado es:\n%s\n",textodecod);
        }
        if(error!=1){
        printf("¿Desea guardar el texto decodificado (S/N)?:");
        scanf("%s",opcion_guardar);
        while(opcion_guardar[0]!='s'&&opcion_guardar[0]!='S'&&opcion_guardar[0]!='n'&&opcion_guardar[0]!='N')
        {
            printf("Opción no válida\n");
            printf("Elija su opción (S/N):");
            scanf("%s",opcion_guardar);
        }
        if (opcion_guardar[0]=='S'||opcion_guardar[0]=='s')
        {
            printf("Introduzca el nombre de archivo con su extensión (ejemplo archivo1.txt):");
            scanf("%s",&archivo);
            f=fopen(archivo,"w+");
            fprintf(f,"%s",textodecod);
            fclose(f);
            printf("Archivo creado exitosamente: %s\n",archivo);
        }
        }
}

//Codificación manual
void codifica_manual(char *dicreal,char **diccodigo,int total)
{
    char texto[VAL];
    int indice=0;
    int error=0;
    int aux=0;
    char archivo[50];
    char opcion_guardar[VAL];
    FILE *f;
    char cadena[VAL][VAL];
    printf("Introduzca el texto a codificar y al finalizar presione enter:");
    scanf("%s",&texto);
    while(texto[aux]!='\0')
    {
        for (indice=0;indice<total;indice++)
        {
            //Si el caracter es igual, la palabra coincide
            if(dicreal[indice]==texto[aux])
            {
                strcpy(cadena[aux],diccodigo[indice]);
                aux+=1;
                break;
            }
        }
        if (indice==total)
            //Hay error en los caracteres por codificar
        {
            error=1;
            break;
        }
    }
    cadena[aux][0]='\0';
    aux=0;
    if(error==1)
    {
        if(cadena[0][0]=='\0')
        {
            printf("Error: El texto introducido no es parte del código introducido\n");
        }
        else
        {
            printf("El texto introducido contiene errores, la parte que se pudo codificar es:\n");
            aux=0;
            while(cadena[aux][0]!='\0')
            {
                printf("%s",cadena[aux]);
                aux+=1;
            }
            printf("\n");
            error=0;
        }
    }
    else
    {
        printf("El texto codificado es:");
        while(cadena[aux][0]!='\0')
        {
            printf("%s",cadena[aux]);
            aux+=1;
        }
        printf("\n");
    }
    if(error!=1){
        printf("¿Desea guardar el texto codificado (S/N)?:");
        scanf("%s",opcion_guardar);
        while(opcion_guardar[0]!='s'&&opcion_guardar[0]!='S'&&opcion_guardar[0]!='n'&&opcion_guardar[0]!='N')
        {
            printf("Opción no válida\n");
            printf("Elija su opción (S/N):");
            scanf("%s",opcion_guardar);
        }
        if (opcion_guardar[0]=='S'||opcion_guardar[0]=='s')
        {
            printf("Introduzca el nombre de archivo con su extensión (ejemplo archivo1.txt):");
            scanf("%s",&archivo);
            f=fopen(archivo,"w+");
            aux=0;
            while(cadena[aux][0]!='\0')
            {
                fprintf(f,"%s",cadena[aux]);
                aux+=1;
            }
            fclose(f);
            printf("Archivo creado exitosamente: %s\n",archivo);
        }
    }
}

//Codificación desde archivo
void codifica_archivo(char *dicreal,char **diccodigo,int total,char *texto)
{
    int indice=0;
    int error=0;
    int aux=0;
    char archivo[50];
    char opcion_guardar[VAL];
    FILE *f;
    char cadena[VAL][VAL];
    while(texto[aux]!='\0')
    {
        for (indice=0;indice<total;indice++)
        {
            //Si el caracter es igual, la palabra coincide
            if(dicreal[indice]==texto[aux])
            {
                strcpy(cadena[aux],diccodigo[indice]);
                aux+=1;
                break;
            }
        }
        if (indice==total)
            //Hay error en los caracteres por codificar
        {
            error=1;
            break;
        }
    }
    cadena[aux][0]='\0';
    aux=0;
    if(error==1)
    {
        if(cadena[0][0]=='\0')
        {
            printf("Error: El texto introducido no es parte del código introducido\n");
        }
        else
        {
            printf("El texto introducido contiene errores, la parte que se pudo codificar es:\n");
            aux=0;
            while(cadena[aux][0]!='\0')
            {
                printf("%s",cadena[aux]);
                aux+=1;
            }
            printf("\n");
            error=0;
        }
    }
    else
    {
        printf("El texto codificado es:");
        while(cadena[aux][0]!='\0')
        {
            printf("%s",cadena[aux]);
            aux+=1;
        }
        printf("\n");
    }
    if(error!=1){
        printf("¿Desea guardar el texto codificado (S/N)?:");
        scanf("%s",opcion_guardar);
        while(opcion_guardar[0]!='s'&&opcion_guardar[0]!='S'&&opcion_guardar[0]!='n'&&opcion_guardar[0]!='N')
        {
            printf("Opción no válida\n");
            printf("Elija su opción (S/N):");
            scanf("%s",opcion_guardar);
        }
        if (opcion_guardar[0]=='S'||opcion_guardar[0]=='s')
        {
            printf("Introduzca el nombre de archivo con su extensión (ejemplo archivo1.txt):");
            scanf("%s",&archivo);
            f=fopen(archivo,"w+");
            aux=0;
            while(cadena[aux][0]!='\0')
            {
                fprintf(f,"%s",cadena[aux]);
                aux+=1;
            }
            fclose(f);
            printf("Archivo creado exitosamente: %s\n",archivo);
        }
    }

}

//Programa principal
int main(int argc,char *argv[]){
    int opc;
    int total;
    int total2;
    int suitam=0;
    int aux=0,aux2=0;
    int ultsec=0;
    int sw=0;
    int yaexiste=0;
    int instantaneo=1;
    int codigo_agregado=0;
    //Variables de diccionario, dicreal es caracter real y diccodigo su código equivalente
    char *dicreal;
    char **diccodigo;
    char archivo[50];
    char cadena[VAL];
    char opcion_guardar[VAL];
    FILE *f,*p;
    
    printf("Bienvenido al programa de decodificación para códigos instantáneos\n\n");
    while (1){
            opc=menu(codigo_agregado);
            switch(opc)
            {
                //Agregar código en forma manual
                case 1:
                    aux=0;
                    aux2=0;
                    sw=0;
                    //Liberación de diccionario anterior
                    if(yaexiste==1)
                    {
                        if(ultsec==1)
                        {
                            for (aux=0;aux<total;aux++)
                            {
                                free(diccodigo[aux]);
                            }
                            free(diccodigo);
                            free(dicreal);
                        }
                        if(ultsec==2)
                        {
                            for (aux=0;aux<total2;aux++)
                            {
                                free(diccodigo[aux]);
                            }
                            free(diccodigo);
                            free(dicreal);
                        }
                    }
                    total=nummanual();
                    dicreal = (char *)malloc(total*sizeof(char));
                    diccodigo = (char **)malloc(total*sizeof(char*));
                    for (aux=0;aux<total;aux++)
                    {
                        diccodigo[aux]=(char *)malloc(CODEMAX*sizeof(char));
                        
                    }
                    aux=0;
                    while (aux<total)
                    {
                        //Se introduce la función de decodificación
                        dicreal[aux]=dic_decodificar(aux);
                        strcpy(diccodigo[aux],dic_codificar(aux));
                        //printf("Código %d: %s\n",aux,diccodigo[aux]);
                        aux+=1;
                    }
                    aux=0;
                    printf("El diccionario elaborado es:\n");
                    printf("(Nombre --> Clave)\n");
                    while (aux<total)
                    {
                        printf("%c --> %s\n",dicreal[aux],diccodigo[aux]);
                        aux+=1;
                    }
                    instantaneo=verificaInstantaneo(diccodigo,total);
                    
                    //Aquí muestra si el código ingresado es o no es instantáneo
                    if (instantaneo==0)
                    {
                        printf("Error, el código ingresado no es instantáneo\n\n");
                        codigo_agregado=0;
                        yaexiste=0;
                        ultsec=1;
                    }
                    else
                    {
                        printf("Enhorabuena, el código ingresado sí es instantáneo (prefijos diferentes)\n\n");
                        codigo_agregado=1;
                        yaexiste=1;
                        ultsec=1;
                        printf("¿Desea guardar el código (S/N)?:");
                        scanf("%s",opcion_guardar);
                        while(opcion_guardar[0]!='s'&&opcion_guardar[0]!='S'&&opcion_guardar[0]!='n'&&opcion_guardar[0]!='N')
                        {
                            printf("Opción no válida\n");
                            printf("Elija su opción (S/N):");
                            scanf("%s",opcion_guardar);
                        }
                        if (opcion_guardar[0]=='S'||opcion_guardar[0]=='s')
                        {
                            printf("Introduzca el nombre de archivo con su extensión (ejemplo archivo1.txt):");
                            scanf("%s",&archivo);
                            f=fopen(archivo,"w+");
                            aux=0;
                            fprintf(f,"%d\n",total);
                            while (aux<total)
                            {
                                fprintf(f,"%c\n",dicreal[aux]);
                                fprintf(f,"%s\n",diccodigo[aux]);
                                aux+=1;
                            }
                            fclose(f);
                            printf("Archivo creado exitosamente: %s\n",archivo);
                        }
                    }
                    break;
                    
                //Agregar código desde archivo
                case 2:
                    aux=0;
                    printf("Introduzca el nombre de archivo con su extensión (ejemplo archivo1.txt):");
                    scanf("%s",&archivo);
                    p = fopen(archivo,"r");
                    if (p == NULL){
                        printf("\nError de apertura del archivo. \n\n");
                    }
                    else
                    {
                        //Liberación de diccionario anterior
                        if(yaexiste==1)
                        {
                            if(ultsec==1)
                            {
                                for (aux=0;aux<total;aux++)
                                {
                                    free(diccodigo[aux]);
                                }
                                free(diccodigo);
                                free(dicreal);
                            }
                            if(ultsec==2)
                            {
                                for (aux=0;aux<total2;aux++)
                                {
                                    free(diccodigo[aux]);
                                }
                                free(diccodigo);
                                free(dicreal);
                            }
                        }
                        fgets(cadena,VAL,p);
                        total2=atoi(cadena);
                        dicreal = (char *)malloc(total2*sizeof(char));
                        diccodigo = (char **)malloc(total2*sizeof(char*));
                        for (aux=0;aux<total2;aux++)
                        {
                            diccodigo[aux]=(char *)malloc(CODEMAX*sizeof(char));
                            
                        }
                        aux=0;
                        aux2=0;
                        sw=0;
                        while (!feof(p))
                        {
                            if (sw==0)
                            {
                                fgets(cadena,VAL,p);
                                dicreal[aux]=cadena[0];
                                sw=1;

                            }
                            else
                            {
                                fgets(cadena,VAL,p);
                                while (cadena[aux2]!='\0')
                                {
                                    aux2+=1;
                                }
                                cadena[aux2-1]='\0';
                                aux2=0;
                                strcpy(diccodigo[aux],cadena);
                                sw=0;
                                aux+=1;
                            }
                        }
                        fclose(p);
                        aux=0;
                        printf("El diccionario leído es:\n");
                        printf("(Nombre --> Clave)\n");
                        while (aux<total2)
                        {
                            printf("%c --> %s\n",dicreal[aux],diccodigo[aux]);
                            aux+=1;
                        }
                        instantaneo=verificaInstantaneo(diccodigo,total2);
                        
                        //Aquí muestra si el código ingresado es o no es instantáneo
                        if (instantaneo==0)
                        {
                            printf("Error, el código leído no es instantáneo\n\n");
                            codigo_agregado=0;
                            yaexiste=0;
                            ultsec=2;
                        }
                        else
                        {
                            printf("Enhorabuena, el código leído sí es instantáneo (prefijos diferentes)\n\n");
                            codigo_agregado=1;
                            yaexiste=1;
                            ultsec=2;
                        }
                    }
                    break;
                    
                    
                //Decodificación de forma manual
                case 3:
                    if (ultsec==1)
                    {
                        suitam=total;
                    }
                    else
                    {
                        suitam=total2;
                    }
                    decodifica_manual(dicreal,diccodigo,suitam);
                    break;
                    
                //Decodificación desde archivo
                case 4:
                    if (ultsec==1)
                    {
                        suitam=total;
                    }
                    else
                    {
                        suitam=total2;
                    }
                    printf("Introduzca el nombre de archivo con su extensión (ejemplo archivo1.txt):");
                    scanf("%s",&archivo);
                    p = fopen(archivo,"r");
                    if (p == NULL){
                        printf("\nError de apertura del archivo. \n\n");
                    }
                    else
                    {
                        fscanf(p,"%s",cadena);
                        fclose(p);
                        decodifica_archivo(dicreal,diccodigo,suitam,cadena);
                    }
                    
                    break;
                    
                //Codificación en forma manual
                case 5:
                    if (ultsec==1)
                    {
                        suitam=total;
                    }
                    else
                    {
                        suitam=total2;
                    }
                    codifica_manual(dicreal,diccodigo,suitam);
                    break;
                    
                //Codificación desde archivo
                case 6:
                    if (ultsec==1)
                    {
                        suitam=total;
                    }
                    else
                    {
                        suitam=total2;
                    }
                    printf("Introduzca el nombre de archivo con su extensión (ejemplo archivo1.txt):");
                    scanf("%s",&archivo);
                    p = fopen(archivo,"r");
                    if (p == NULL){
                        printf("\nError de apertura del archivo. \n\n");
                    }
                    else
                    {
                        fscanf(p,"%s",cadena);
                        fclose(p);
                        codifica_archivo(dicreal,diccodigo,suitam,cadena);
                    }
                    
                    break;

                    
                //Salir del programa
                case 0:
                    return 0;
            
        }

    }
  
}

