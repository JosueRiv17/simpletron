#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int memoria[1000];
   float memoriaFloat[1000];
    int stw=0;
    int acumulador= 0;
    int codigoOperacion=0;
    int operando = 0;
    int registroInstruccion=0;
    float acumuladorFloat;
//----------------------------------------------------------------
void vaciadoMemoria(int instruccionContador, int acumulador,  int registroInstruccion, int codigoOperacion, int operando, int memoria[]){
	int j, i;
	
		printf("Registros:\t+");
      	printf("acumulador:\t%+05d\n", acumulador);
		printf("instructionCounter:\t%02d\n", instruccionContador);
		printf("instructionRegister:\t%+05d\n", registroInstruccion);
		printf("operationCode:\t%02d\n", codigoOperacion);
		printf("operand:\t%02d\n", operando);
      	printf("\nMEMORIA\n");
printf("      ");

for(j=0;j<10;j++){
    printf("%8d", j);
}
printf("\n");

for(i=0;i<100;i++){
    printf("%3d    ", i*10);

    for(j=0;j<10;j++){
        printf("%+06d ", memoria[i * 10 + j]);
    }

    printf("\n");
}
			}
//-----------------------------------------------------------------------			
			
int main(){
		int menu=0;
     	int i;
     	int j;
     	int carga=0;
     	char cadena[100];
    printf("** ¡Bienvenido a Simpletron!**\n");
    printf("**Introduzca su programa una instruccion**\n");
    printf("** (o palabra de datos) a la vez en linea *** \n");
    printf("**de texto de entrada. Yo indicaré el numero***\n");
    printf("** de posicion y una interrogacion (?). usted ***\n");
     printf("** tecleara entonces la palabra para esa**\n");
      printf("** posicion. haga clic en el boton LISTO PARA**\n");
       printf("** dejar de introducir su programa**\n");
		
	
//cargado dessde archivo------------------------------------------------------
      FILE * archivo = fopen("programa.simp", "r");
		if(archivo != NULL){
			printf("leyendo archivo");
			for( i = 0;i<1000;i++){
				int resultado;
				resultado =fscanf(archivo," %d", &memoria[i]) ;
					if (resultado ==EOF){
						printf("archivo leido");
						break;
					}
					
					if(resultado == 0){
						printf("dato invalido en la linea %d", i);
						return 0;
					}
					if(memoria[i] < -99999 || memoria[i] > 99998){
            	 printf("dato invalido en la linea %d", i);
						return 0;
			}
					
			}
			fclose(archivo);
		}
//cargado manualmente--------------------------------------------------
		else{
		
		
		printf("no existe archivo, cargar manualmente\n");
        for( i = 0;i<1000;i++){
        	bool valorValido=false;
        	
        	while(valorValido==false){
			
            printf("%02d ? + ",i);
            scanf("%d", &memoria[i] );
             if(memoria[i]==99999){
             	memoria[i]=0;
            	menu=99999;
            break;
			}
            if(memoria[i]<-99999 || memoria[i]>99998){
            	 printf("valor invalido");
        		valorValido=false;
			}else
			valorValido=true;
           }
           if(menu==99999)
           break;
        }
        }
    
	
//termino de cargar programa-----------------------------------------------

        
         	printf("**se termino de cargar el programa**\n");
       		 printf("**comienza la ejecucion del programma**\n");
       		 int instruccionContador=0;
		int menu2=0;
		while(menu2!=99){
			registroInstruccion = memoria[instruccionContador];
        codigoOperacion =  registroInstruccion / 1000;
        operando = registroInstruccion % 1000;
        if(operando < 0 || operando > 999){
        	printf("error fatal: operando negativo");
        	vaciadoMemoria(instruccionContador,  acumulador,   registroInstruccion,  codigoOperacion,operando,memoria);
			return 0;
		}
        switch(codigoOperacion)
        {
        	//read
        	case 10:
        		printf("ingresa valor");
        		scanf("%d",&memoria[operando]);
        		instruccionContador++;
        		break;
        		//write
        		case 11:
        			printf("%02d", memoria[operando]);
        			instruccionContador++;
        			break;
        			//salto de linea
        			case 12:
        				printf("\n");
        				instruccionContador++;
        			break;
        			//entrada de cadena
        			case 13:
        				    printf("Ingrese una cadena: ");
   						 scanf("%99s", cadena);
    						memoria[operando] = strlen(cadena) * 1000;
    						for(i = 0; cadena[i] != '\0'; i++){
    						int ascii = cadena[i];
    						memoria[operando + i + 1] = (i + 1) * 1000 + ascii;
								}
   							 instruccionContador++;
        				break;
        				//salida de cadena
        				case 14:{
						
        					    printf("Cadena: ");
    							int longitud = memoria[operando] / 1000;
    							for(i = 1; i <= longitud; i++){
    							int ascii = memoria[operando + i] % 1000;
    							printf("%c", ascii);
									}			
    							printf("\n");
   								 instruccionContador++;
        					break;
						}
						
						////////////////FLOTANTES-------------------
						//agregar flotante
					case 15: {
						    printf("Ingrese un numero decimal: ");
						    scanf("%f", &memoriaFloat[operando]);
						    instruccionContador++;
						    break;
						}
						//salida de flotante
						case 16: {
						    printf("%.2f\n", acumuladorFloat);
						    instruccionContador++;
						    break;
						}
						// cargar flotante al acumulador flotante
						case 17: {
						    acumuladorFloat = memoriaFloat[operando];
						    instruccionContador++;
						    break;
						}
						
						// sumar flotante
						case 18: {
						    acumuladorFloat += memoriaFloat[operando];
						    instruccionContador++;
						    break;
						}
						
						// restar flotante
						case 19: {
						    acumuladorFloat -= memoriaFloat[operando];
						    instruccionContador++;
						    break;
						}
						
						// multiplicar flotante
						case 22: {
						    acumuladorFloat *= memoriaFloat[operando];
						    instruccionContador++;
						    break;
						}
						
						// dividir flotante
						case 23: {
						    if(memoriaFloat[operando] == 0){
						        printf("Error fatal: division entre cero\n");
						        vaciadoMemoria(instruccionContador, acumulador,
						                       registroInstruccion, codigoOperacion,
						                       operando, memoria);
						        return 0;
						    }
						
						    acumuladorFloat /= memoriaFloat[operando];
						    instruccionContador++;
						    break;
						}
						
						
        			//load
        			case 20:
        			acumulador = memoria[operando];
        			instruccionContador++;
        			break;
        			//sumar
        			case 30:
        				acumulador+= memoria[operando];
        				if(acumulador > 99999 || acumulador < -99999){
    					// error fatal
    					printf("error fatal desbordamiento del acumulador");
    					vaciadoMemoria(instruccionContador,  acumulador,   registroInstruccion,  codigoOperacion,operando,memoria);
    					return 0;
							}
        				instruccionContador++;
        				break;
        				//subtract
        				case 31:
        					acumulador -=memoria[operando];
        						if(acumulador > 99999 || acumulador < -99999){
    					// error fatal
    					printf("error fatal desbordamiento del acumulador");
    					vaciadoMemoria(instruccionContador,  acumulador,   registroInstruccion,  codigoOperacion, operando, memoria);
    					return 0;
							}
        					instruccionContador++;
        					break;
        					//divide
        					case 32:
        						if(memoria[operando]==0){
        							printf("no se puede dividir entre cero");
        							vaciadoMemoria(instruccionContador,  acumulador,    registroInstruccion,  codigoOperacion, operando, memoria);
        							return 0;
								}
        						acumulador /=memoria[operando];
        						instruccionContador++;
        						break;
        						//multiply
        						case 33:
        							acumulador*=memoria[operando];
        								if(acumulador > 99999 || acumulador < -99999){
    					// error fatal
    					printf("error fatal desbordamiento del acumulador");
    					vaciadoMemoria(instruccionContador,  acumulador,    registroInstruccion,  codigoOperacion,operando,  memoria);
    					return 0;
							}
        							instruccionContador++;
        						break;
        						//modulo
        						case 34:
        								if(memoria[operando]==0){
        							printf("no se puede dividir entre cero");
        							vaciadoMemoria(instruccionContador,  acumulador,    registroInstruccion,  codigoOperacion, operando, memoria);
        							return 0;
        						}
        						acumulador %=memoria[operando];
        						instruccionContador++;
        							break;
        							//potencia
        							case 35:
        								acumulador = (int)pow(acumulador, memoria[operando]);
        								if(acumulador > 99999 || acumulador < -99999){
			    					// error fatal
			    					printf("error fatal desbordamiento del acumulador");
			    					vaciadoMemoria(instruccionContador,  acumulador,    registroInstruccion,  codigoOperacion,operando,  memoria);
			    					return 0;
										}
        								instruccionContador++;
        								break;
        						//branch
        						case 40:
        							instruccionContador=operando;
        							
        						break;
        						//branchneg
        						case 41:
        							if(acumulador<0){
        								instruccionContador=operando;
									}else{
										instruccionContador++;
									}
        							
        						break;
        						//branchzero
        						case 42:
        							if(acumulador==0){
        								instruccionContador = operando;
									}else
        							instruccionContador++;

        						break;
        				//alto
        			case 99:
        				printf("***termino la ejecucion de simpletron***");
        				menu2 = 99;
        				break;
        				default:
					    printf("ERROR FATAL: codigo de operacion invalido\n");
					    vaciadoMemoria(instruccionContador, acumulador,
					                   registroInstruccion, codigoOperacion,
					                   operando, memoria);
    					return 0;
        	
		}
	}
	vaciadoMemoria(instruccionContador,  acumulador,    registroInstruccion,  codigoOperacion, operando, memoria);
	
	
	
        
      	
       
        
        
        return 0;
}

