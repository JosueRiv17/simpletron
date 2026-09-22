#include <stdbool.h>
#include <stdio.h>
int memoria[100];
   
    int stw=0;
    int acumulador= 0;
    int codigoOperacion=0;
    int operando = 0;
    int registroInstruccion=0;
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

for(i=0;i<10;i++){
    printf("%2d    ", i);

    for(j=0;j<10;j++){
        printf("%+07d ", memoria[i * 10 + j]);
    }

    printf("\n");
}
			}
int main(){
		int menu=0;
     	int i;
     	int j;
    printf("** ¡Bienvenido a Simpletron!**\n");
    printf("**Introduzca su programa una instruccion**\n");
    printf("** (o palabra de datos) a la vez en linea *** \n");
    printf("**de texto de entrada. Yo indicaré el numero***\n");
    printf("** de posicion y una interrogacion (?). usted ***\n");
     printf("** tecleara entonces la palabra para esa**\n");
      printf("** posicion. haga clic en el boton LISTO PARA**\n");
       printf("** dejar de introducir su programa**\n");

      
	
        for( i = 0;i<100;i++){
        	bool valorValido=false;
        	
        	while(valorValido==false){
			
            printf("%02d ? + ",i);
            scanf("%d", &memoria[i] );
             if(memoria[i]==9999){
             	memoria[i]=0;
            	menu=9999;
            break;
			}
            if(memoria[i]<-9999 || memoria[i]>9998){
            	 printf("valor invalido");
        		valorValido=false;
			}else
			valorValido=true;
           }
           if(menu==9999)
           break;
        }
    

        
         	printf("**se termino de cargar el programa**\n");
       		 printf("**comienza la ejecucion del programma**\n");
       		 int instruccionContador=0;
		int menu2=0;
		while(menu2!=99){
			registroInstruccion = memoria[instruccionContador];
        codigoOperacion =  registroInstruccion / 100;
        operando = registroInstruccion % 100;
        
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
        			//load
        			case 20:
        			acumulador = memoria[operando];
        			instruccionContador++;
        			break;
        			//sumar
        			case 30:
        				acumulador+= memoria[operando];
        				if(acumulador > 9999 || acumulador < -9999){
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
        						if(acumulador > 9999 || acumulador < -9999){
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
        								if(acumulador > 9999 || acumulador < -9999){
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

