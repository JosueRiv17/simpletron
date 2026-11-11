#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
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
     	// Inicializacion de registros
		stw = 0;
		acumulador = 0;
		codigoOperacion = 0;
		operando = 0;
		registroInstruccion = 0;
		acumuladorFloat = 0.0f;
		
		// Inicializacion de memoria
		for(i = 0; i < 1000; i++){
		    memoria[i] = 0;
		    memoriaFloat[i] = 0.0f;
		}
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
					for(i = 0; i < 1000; i++){
			    char entrada[100];
			    char *fin;
			    long valor;
			
			    int resultado = fscanf(archivo, "%99s", entrada);
			
			    if(resultado == EOF){
			        if(i == 0){
			            printf("ERROR: el archivo esta vacio\n");
			            fclose(archivo);
			            return 0;
			        }
			
			        printf("Archivo leido correctamente\n");
			        break;
			    }
			
			    errno = 0;
			    valor = strtol(entrada, &fin, 10);
			
			    if(errno == ERANGE || fin == entrada || *fin != '\0'){
			        printf("ERROR: dato invalido en la posicion %d\n", i);
			        fclose(archivo);
			        return 0;
			    }
			
			    if(valor < -99999 || valor > 99998){
			        printf("ERROR: valor fuera de rango en la posicion %d\n", i);
			        fclose(archivo);
			        return 0;
			    }
			
			    memoria[i] = (int)valor;
			}
			
			if(i == 1000){
			    char extra[100];
			
			    if(fscanf(archivo, "%99s", extra) == 1){
			        printf("ERROR: el programa supera las 1000 posiciones\n");
			        fclose(archivo);
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
			
            printf("%02d ? + ", i);

			if(scanf("%d", &memoria[i]) != 1){
			
			    printf("ERROR: debes introducir un numero entero\n");
			
			    int caracter;
			    while((caracter = getchar()) != '\n' && caracter != EOF);
			
			    valorValido = false;
			    continue;
			}
             if(memoria[i]==99999){
             	memoria[i]=0;
            	menu=99999;
            break;
			}
            if(memoria[i]<-99999 || memoria[i]>99998){
            	 printf("valor invalido fuera de rango permitido");
        		valorValido=false;
			}else
			valorValido=true;
           }
           if(menu==99999)
           break;
        }
        }
    
	
//termino de cargar programa-----------------------------------------------

        
         	printf("**\nse termino de cargar el programa**\n");
       		 printf("**comienza la ejecucion del programma**\n");
       		 int instruccionContador=0;
		int menu2=0;
		while(menu2!=99){
			
			    if(instruccionContador < 0 || instruccionContador >= 1000){
        printf("ERROR FATAL: contador de instrucciones fuera de memoria\n");
        vaciadoMemoria(instruccionContador, acumulador,
                       registroInstruccion, codigoOperacion,
                       operando, memoria);
        return 0;
				    }
				
				    registroInstruccion = memoria[instruccionContador];
				    
				    if(registroInstruccion < -99999 || registroInstruccion > 99999){
					    printf("ERROR FATAL: instruccion fuera de rango\n");
					
					    vaciadoMemoria(instruccionContador, acumulador,
					                   registroInstruccion, codigoOperacion,
					                   operando, memoria);
					
					    return 0;
					}
				    
							
				        codigoOperacion =  registroInstruccion / 1000;
				        operando = registroInstruccion % 1000;
				        printf("DEBUG | PC: %d | Instruccion: %d | Opcode: %d | Operando: %d\n",
       instruccionContador, registroInstruccion,
       codigoOperacion, operando);
				        if(operando < 0 || operando >= 1000){
				    printf("ERROR FATAL: direccion de memoria invalida\n");
				    vaciadoMemoria(instruccionContador, acumulador,
				                   registroInstruccion, codigoOperacion,
				                   operando, memoria);
				    return 0;
				}
        switch(codigoOperacion)
        {
        	//read
				        case 10: {
				    char entrada[100];
				    char *fin;
				    long valor;
				
				    printf("Ingresa un valor entero: ");
				
				    if(scanf("%99s", entrada) != 1){
				        printf("ERROR FATAL: entrada invalida\n");
				        vaciadoMemoria(instruccionContador, acumulador,
				                       registroInstruccion, codigoOperacion,
				                       operando, memoria);
				        return 0;
				    }
				
				    valor = strtol(entrada, &fin, 10);
				
				    if(*fin != '\0' || fin == entrada ||
				       valor < -99999 || valor > 99998){
				
				        printf("ERROR FATAL: valor de entrada invalido\n");
				        vaciadoMemoria(instruccionContador, acumulador,
				                       registroInstruccion, codigoOperacion,
				                       operando, memoria);
				        return 0;
				    }
				
				    memoria[operando] = (int)valor;
				    instruccionContador++;
				    break;
				}
        		//write
        		case 11:
				    printf("%d\n", memoria[operando]);
				    instruccionContador++;
				    break;
        			//salto de linea
        			case 12:
        				printf("\n");
        				instruccionContador++;
        			break;
        			//entrada de cadena
        			case 13: {
					    printf("Ingrese una cadena: ");
					
					    if(scanf("%99s", cadena) != 1){
					        printf("ERROR FATAL: entrada de cadena invalida\n");
					        vaciadoMemoria(instruccionContador, acumulador,
					                       registroInstruccion, codigoOperacion,
					                       operando, memoria);
					        return 0;
					    }
					
					    int longitud = strlen(cadena);
					
					    if(operando + longitud >= 1000){
					        printf("ERROR FATAL: espacio insuficiente para la cadena\n");
					        vaciadoMemoria(instruccionContador, acumulador,
					                       registroInstruccion, codigoOperacion,
					                       operando, memoria);
					        return 0;
					    }
					
					    memoria[operando] = longitud * 1000;
					
					    for(i = 0; i < longitud; i++){
					        int ascii = (unsigned char)cadena[i];
					        memoria[operando + i + 1] = (i + 1) * 1000 + ascii;
					    }
					
					    instruccionContador++;
					    break;
					}
        				//salida de cadena
        				case 14: {
							    int longitud = memoria[operando] / 1000;
							
							    if(longitud < 0 || operando + longitud >= 1000){
							        printf("ERROR FATAL: longitud de cadena invalida\n");
							        vaciadoMemoria(instruccionContador, acumulador,
							                       registroInstruccion, codigoOperacion,
							                       operando, memoria);
							        return 0;
							    }
							
							    printf("Cadena: ");
							
							    for(i = 1; i <= longitud; i++){
							        int ascii = memoria[operando + i] % 1000;
							
							        if(ascii < 0 || ascii > 255){
							            printf("\nERROR FATAL: caracter invalido\n");
							            vaciadoMemoria(instruccionContador, acumulador,
							                           registroInstruccion, codigoOperacion,
							                           operando, memoria);
							            return 0;
							        }
							
							        printf("%c", ascii);
							    }
							
							    printf("\n");
							    instruccionContador++;
							    break;
							}
						
						////////////////FLOTANTES-------------------
						//agregar flotante
					case 15: {
						    char entrada[100];
						    char *fin;
						    float valor;
						
						    printf("Ingrese un numero decimal: ");
						
						    if(scanf("%99s", entrada) != 1){
						        printf("ERROR FATAL: entrada invalida\n");
						        vaciadoMemoria(instruccionContador, acumulador,
						                       registroInstruccion, codigoOperacion,
						                       operando, memoria);
						        return 0;
						    }
						
						    valor = strtof(entrada, &fin);
						
						    if(fin == entrada || *fin != '\0' || !isfinite(valor)){
						        printf("ERROR FATAL: numero decimal invalido\n");
						        vaciadoMemoria(instruccionContador, acumulador,
						                       registroInstruccion, codigoOperacion,
						                       operando, memoria);
						        return 0;
						    }
						
						    memoriaFloat[operando] = valor;
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
					
					    if(!isfinite(acumuladorFloat)){
					        printf("ERROR FATAL: valor flotante invalido\n");
					        vaciadoMemoria(instruccionContador, acumulador,
					                       registroInstruccion, codigoOperacion,
					                       operando, memoria);
					        return 0;
					    }
					
					    instruccionContador++;
					    break;
					}
						
						// sumar flotante
						case 18: {
						    acumuladorFloat += memoriaFloat[operando];
						
						    if(!isfinite(acumuladorFloat)){
						        printf("ERROR FATAL: desbordamiento flotante\n");
						        vaciadoMemoria(instruccionContador, acumulador,
						                       registroInstruccion, codigoOperacion,
						                       operando, memoria);
						        return 0;
						    }
						
						    instruccionContador++;
						    break;
						}
						
						// restar flotante
						case 19: {
						    acumuladorFloat -= memoriaFloat[operando];
						
						    if(!isfinite(acumuladorFloat)){
						        printf("ERROR FATAL: desbordamiento flotante\n");
						        vaciadoMemoria(instruccionContador, acumulador,
						                       registroInstruccion, codigoOperacion,
						                       operando, memoria);
						        return 0;
						    }
						
						    instruccionContador++;
						    break;
						}
						
						// multiplicar flotante
						case 22: {
							    acumuladorFloat *= memoriaFloat[operando];
							
							    if(!isfinite(acumuladorFloat)){
							        printf("ERROR FATAL: desbordamiento flotante\n");
							        vaciadoMemoria(instruccionContador, acumulador,
							                       registroInstruccion, codigoOperacion,
							                       operando, memoria);
							        return 0;
							    }
							
							    instruccionContador++;
							    break;
							}
						
						// dividir flotante
						case 23: {
						    if(memoriaFloat[operando] == 0.0f ||
								   !isfinite(memoriaFloat[operando]) ||
								   !isfinite(acumuladorFloat)){
						        printf("Error fatal: division entre cero\n");
						        vaciadoMemoria(instruccionContador, acumulador,
						                       registroInstruccion, codigoOperacion,
						                       operando, memoria);
						        return 0;
						    }
						
						    acumuladorFloat /= memoriaFloat[operando];
						    if(!isfinite(acumuladorFloat)){
							    printf("ERROR FATAL: resultado flotante invalido\n");
							
							    vaciadoMemoria(instruccionContador, acumulador,
							                   registroInstruccion, codigoOperacion,
							                   operando, memoria);
							
							    return 0;
							}
						    instruccionContador++;
						    break;
						}
						
						
        			//load
        			case 20:
        			acumulador = memoria[operando];
        			instruccionContador++;
        			break;
        			//STORE
        			case 21:
				    if(operando < 0 || operando >= 1000){
				        printf("ERROR FATAL: direccion de memoria invalida\n");
				        vaciadoMemoria(instruccionContador, acumulador,
				                       registroInstruccion, codigoOperacion,
				                       operando, memoria);
				        return 0;
				    }
				
				    memoria[operando] = acumulador;
				    instruccionContador++;
				    break;
        			//sumar
        			case 30:
        				{
					    long long resultado = (long long)acumulador + memoria[operando];
					
					    if(resultado > 99998 || resultado < -99999){
					        printf("ERROR FATAL: desbordamiento del acumulador\n");
					        vaciadoMemoria(instruccionContador, acumulador,
					                       registroInstruccion, codigoOperacion,
					                       operando, memoria);
					        return 0;
					    }
					
					    acumulador = (int)resultado;
					    instruccionContador++;
					    break;
					}
        				//subtract
        				case 31:
        					 {
						    long long resultado = (long long)acumulador - memoria[operando];
						
						    if(resultado > 99998 || resultado < -99999){
						        printf("ERROR FATAL: desbordamiento del acumulador\n");
						        vaciadoMemoria(instruccionContador, acumulador,
						                       registroInstruccion, codigoOperacion,
						                       operando, memoria);
						        return 0;
						    }
						
						    acumulador = (int)resultado;
						    instruccionContador++;
						    break;
						}
        					//divide
        					case 32: {
								    if(memoria[operando] == 0){
								        printf("ERROR FATAL: division entre cero\n");
								        vaciadoMemoria(instruccionContador, acumulador,
								                       registroInstruccion, codigoOperacion,
								                       operando, memoria);
								        return 0;
								    }
								
								    if(acumulador == -99999 && memoria[operando] == -1){
								        printf("ERROR FATAL: desbordamiento del acumulador\n");
								        vaciadoMemoria(instruccionContador, acumulador,
								                       registroInstruccion, codigoOperacion,
								                       operando, memoria);
								        return 0;
								    }
								
								    acumulador /= memoria[operando];
								    instruccionContador++;
								    break;
								}
        						//multiply
        						case 33:
        							{
								    long long resultado = (long long)acumulador * memoria[operando];
								
								    if(resultado > 99998 || resultado < -99999){
								        printf("ERROR FATAL: desbordamiento del acumulador\n");
								        vaciadoMemoria(instruccionContador, acumulador,
								                       registroInstruccion, codigoOperacion,
								                       operando, memoria);
								        return 0;
								    }
								
								    acumulador = (int)resultado;
								    instruccionContador++;
								    break;
								}
        						//modulo
        						case 34: {
									    if(memoria[operando] == 0){
									        printf("ERROR FATAL: modulo entre cero\n");
									        vaciadoMemoria(instruccionContador, acumulador,
									                       registroInstruccion, codigoOperacion,
									                       operando, memoria);
									        return 0;
									    }
									
									    acumulador %= memoria[operando];
									    instruccionContador++;
									    break;
									}
        							//potencia
        							case 35: {
								    double resultado;
								
								    if(memoria[operando] < 0){
								        printf("ERROR FATAL: exponente negativo no permitido\n");
								        vaciadoMemoria(instruccionContador, acumulador,
								                       registroInstruccion, codigoOperacion,
								                       operando, memoria);
								        return 0;
								    }
								
								    resultado = pow(acumulador, memoria[operando]);
								
								    if(!isfinite(resultado) || resultado > 99998 || resultado < -99999){
								        printf("ERROR FATAL: desbordamiento en exponenciacion\n");
								        vaciadoMemoria(instruccionContador, acumulador,
								                       registroInstruccion, codigoOperacion,
								                       operando, memoria);
								        return 0;
								    }
								
								    acumulador = (int)resultado;
								    instruccionContador++;
								    break;
								}
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

