#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void line(char style);
void header();
void header_receipt();
void header_paper();
void next();

int main(){
	//time
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
  	
  	//table
	char products[200][3][20];
	char receipt[400][6][20];
	char history[400][3][50];
	
	//var
	int k,n,m,op,i,j;
	int index=0;
	int navigation = 2 ;
	int b=0;
	double total;
	double sum_total;
	char no[20];
	int quantity;
	int isNew = 1;
	int limiter =0;
	int temp;
	char ctemp[40];
	int nhistory=0;
	double historyTotal;
	n=0;

	/* preset */
	strcpy(products[0][0],"100");
	strcpy(products[0][1],"apple");
	strcpy(products[0][2],"2");
	strcpy(products[1][0],"101");
	strcpy(products[1][1],"banana");
	strcpy(products[1][2],"2");
	strcpy(products[2][0],"102");
	strcpy(products[2][1],"orange");
	strcpy(products[2][2],"3");		
	strcpy(products[3][0],"103");
	strcpy(products[3][1],"watermelon");
	strcpy(products[3][2],"7");	
	n=4;
	index=4;
	/* preset */
	
	navigation=2;
	do{		
		if(navigation==1){		
			line('=');
			printf("[ADMIN MODE]\n");
			printf("1. Add Products \n");
			printf("2. Products list \n");
			printf("3. Search \n");
			printf("4. Insert product \n");
			printf("5. Delete product \n");
			printf("6. Clear all products \n");
			printf("7. history \n");
			printf("8. Generate Receipt \n");
			printf("9. Exit \n");
			line('=');
			printf("Please choose an option: ");
			scanf("%d", &op); fflush(stdin);
			line('=');
		}
		else{op=8;}
		switch(op){
			case 1:{
				n++;
				printf("Enter Product: \n");
				while(index<200){
					n++;
					printf("==========[Product(%d)]=========\n", index+1);
					itoa(index+100,products[index][0],10);
					printf("ID: %s \n", products[index][0]);
					printf("Name: "); fflush(stdin); gets(products[index][1]);
					// Exit
					if(strcmp(products[index][1],"done")==0){
						memset(products[index][1],0,strlen(products[index][1]));
						n--;
						next();
						printf("Input Complete! \n");
						break;
					}
					printf("Price: "); scanf("%s", products[index][2]);
					index++;
				}
				n--;
				printf("[Number of products: %d]\n", n);
			}break;
			
			case 2:{
				header();
				for(i=0;i<n;i++){
					for(j=0;j<3;j++){
						if(j==2){
							printf("%6s", products[i][j]);
						}
						else{
							printf("%14s", products[i][j]);
						}
					}
					printf(" $ \n");
				}
			}break;
		
			case 3:{ //search
				char sid[20];
				int b = 0;
				printf("Input ID to search: ");
				scanf("%s", &sid);
				next();
				for(i=0;i<n;i++){
					if(strcmp(sid,products[i][0])==0){
						//when found
						printf("Search Found!\n");
						header();
						for(j=0;j<3;j++){
							printf("%9s", products[i][j]);
						}
						printf("\n");
						b=1;
						break;
					}
				}
				if(b==0){
					printf("Product not found! \n");
				}
			}break;
			
			
			case 4:{ //insert product
				int j,k;
				char sid[20];
				b=0;
				printf("Input ID to insert: ");scanf("%s", &sid);
				for(i=0;i<n;i++){
					if(strcmp(sid,products[i][0])==0){
						for(j=n;j>i;j--){
							temp = atoi(products[j-1][0]);
							temp+=1;
							sprintf(products[j][0], "%d",temp);
							strcpy(products[j][1],products[j-1][1]);
							strcpy(products[j][2],products[j-1][2]);
						}
						printf("Name: "); fflush(stdin); gets(products[i][1]);
						printf("Price: "); scanf("%s", &products[i][2]);
						n++;
						index++;
						b=1;
						next();printf("Insert Succeed \n");
						break;
					}
				}
				if(b==0){
					next();
					printf("Index can't found\n");
				}
			}break;
			
			case 5:{ //delete
				int j;
				char sid[20];
				b=0;
				printf("Input ID to delete: "); scanf("%s", &sid);
				for(i=0;i<n;i++){
					if(strcmp(sid,products[i][0])==0){
						printf("product found\n");
						for(j=i;j<n;j++){
							temp = atoi(products[j+1][0]);
							temp -=1;
							sprintf(products[j][0],"%d",temp);
							strcpy(products[j][1],products[j+1][1]);
							strcpy(products[j][2],products[j+1][2]);
						}
						n--;
						index--;
						b=1;
						printf("Delete Complete\n");
						break;
					}
				}
				if(b==0){
					next();
					printf("There is no product at %s\n", sid);
				}
			}break;
			
			case 6: { //clear all products
				for(i=0;i<n;i++){
					strcpy(products[i][0], "");
					strcpy(products[i][1], "");
					strcpy(products[i][2], "");
				}
				n=0;
				index=0;
				printf("All products have been cleared\n");
			}break;
			
			case 7:{ //history
				historyTotal=0;
				printf("%6s%15s%27s\n","No." ,"Date","Income");
				for(i=0;i<nhistory;i++){
					printf("%6s", history[i][0]);
					printf("%30s",history[i][1]);
					printf("%10s $",history[i][2]);
					printf("\n");
					historyTotal = historyTotal + atof(history[i][2]);
				}
				printf("   ");
				line('_');
				printf("   %6s%37.2lf$\n","Total: ", historyTotal);
			}break;
			
			case 8:{ //generate receipt
				navigation=2;
				char sid[20];
				m=0;
				limiter =0;
				do{
					b=0;
					printf("Product ID: ");scanf("%s", &sid);
					//toggle admin mode
					if(strcmp(sid,"admin")==0){
						const char cpassword[20] = "ilovepich";
						char password[20];
						printf("Password: ");
						scanf("%s",&password);
						if(strcmp(password,cpassword)==0){
							navigation=1;
							break;
						}
						else{
							printf("incorrect password\n");
							line('=');
						}
						b=1;
					} 
					for(i=0;i<n;i++){
						if(strcmp(sid,products[i][0])==0){
							isNew=1;
							//if scanned same products twice
							for(k=0;k<m;k++){
								if(strcmp(sid,receipt[k][1])==0){
									//setting qty
/*Sound Here */						Beep(910, 200);			
									quantity = atoi(receipt[k][4]);
									quantity++;
									sprintf(receipt[k][4], "%d", quantity);	
									//setting total
									total = atof(receipt[k][3]) * atof(receipt[k][4]);
									sprintf(receipt[k][5], "%.2lf", total );
									//status update
									b=1;
									isNew = 0;
									limiter++;
								}
							}
							
							//first time
							if(isNew==1){
/*Sound here */					Beep(910, 200);
								itoa(m+1,no,10);
								strcpy(receipt[m][0],no);
								strcpy(receipt[m][1],products[i][0]);
								strcpy(receipt[m][2],products[i][1]);
								strcpy(receipt[m][3],products[i][2]);
							
		/* get lateer*/			quantity =0;
								quantity++;
								sprintf(receipt[m][4], "%d", quantity);
							
								//calculate and insert total
								total = atof(receipt[m][3]) * atof(receipt[m][4]);
								sprintf(receipt[m][5], "%.2lf", total );
								b=1;
								m++;
								limiter++;
							}
						}		
					}
				
					if(b==0 && strcmp(sid,"done")!=0){
						next();
						printf("product not found\n");
					}
					
				}while(strcmp(sid,"done")!=0 && limiter<400);
				
				//print receip
				if(strcmp(sid,"done")==0){						
					sum_total=0;
					printf("\n");
					printf("\t");
					header_paper();printf("   ");line('_');printf("\t");
					header_receipt();
					printf("   ");line('_');
					for(i=0;i<m;i++){
						printf("\t");
						for(j=0;j<6;j++){
							if(j==0){printf("%10s", receipt[i][j]);}//No
							else if(j==1){printf("%6s", receipt[i][j]);}//id
							else if(j==2){printf("%14s", receipt[i][j]);} //product
							else if(j==4){printf("%7s%s", "x",receipt[i][j]);} //qty
							else if(j==5){printf("%10s", receipt[i][j]);} //total
							else{printf("%8s", receipt[i][j]);}
						}
						sum_total = sum_total + atof(receipt[i][5]);
						printf("\n");
					}
					printf("   ");line('_');
					printf("   ");printf("%s %55.2lf \n", "Total", sum_total);
					printf("\n");
					line('=');
					//end of print
					
					/* create history */
					sprintf(history[nhistory][0],"%d", nhistory+1);
					strcpy(ctemp,asctime(timeinfo));
					ctemp[strlen(ctemp)-1] = '\0';
					strcpy(history[nhistory][1], ctemp);
					sprintf(history[nhistory][2],"%.2lf" ,sum_total);
					nhistory++;
					//end of create history 
				}
			}break;
			
			default:{
				printf("invalid input\n");
			} break;
		}
	}while(op!=9);
	return 0;
}

void line(char style){
	int i,max;
	if(style=='_'){max=65;}
	else{max=80;}
	for(i=0;i<max;i++){printf("%c", style);}
	printf("\n");
}
void header(){
	printf("%14s%14s%8s\n", "ID","Product","Price");
}
void header_receipt(){
	printf("%10s%6s%14s%8s%8s%10s\n","No.","ID","Product","Price","QTY","Total");
}
void header_paper(){
	printf("%43s", "Pich's Lovely Store\n");
	printf("%47s", "   Street NR2, Sangkat Chak Angrae Kroam, Khan Meanchey, PhnomPenh\n");
	printf("%48s", "Tel: 097 30 95 666\n");
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf("   %s", asctime (timeinfo));
}
void next(){
	printf(" > ");
}

