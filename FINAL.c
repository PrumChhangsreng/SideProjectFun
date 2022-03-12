//prepare landAreaWithoutAutoarrayCleaner
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(){
	char countriesWithLand[][20] = {"cambodia:181035",
									"usa:9833520",
									"australia:7692024",
									"china:9596961",
									"japan:123123",
									"ireland:70273",
									"iceland:103000",
									"thailand:513120",
									"vietnam:331212",
									"laos:236800",
									"singapore:728",
									"russia:17098246",
									"canada:9984670",
									"uk:242495",
									"south Korea:100210",
									"north Korea:120540"};
	
	/*     Program to generate array of Country and Landarea       */						
	char countries[20][20] ={}; 
	char landAreas[20][20] ={};
	int landAreasDou[20];
	int indexOfColon;
	int j=0;
	int i,k;
	int nOfCountriesWithLand,nOfCountries;
	nOfCountriesWithLand = sizeof(countriesWithLand)/sizeof(countriesWithLand[0]);
	
	// sFormular
	char nameTemp[20];
	char nameTwoTemp[20];
	char probableR[30][20] ={""};
	int relatives = 0;
	int preRelatives =0;	
	int arrLen=0;
	int sizeofR =  nOfCountriesWithLand; //sizeof(countries)/sizeof(countries[0]);
	
	//math
	int mMargin =0;
	double percentageM=0;
	double mTotal=0;
	int nMTotal=0;
	double sEquation =0;
	double prePercentageM=0;
	
	//iterate each counries
	for(i=0;i<nOfCountriesWithLand;i++){
		//creating index of colon
		char *pOfColon = strchr(countriesWithLand[i],':');
		indexOfColon = pOfColon - countriesWithLand[i];
	
		//create list of country
		for(j=0;j<indexOfColon;j++){
			countries[i][j] = countriesWithLand[i][j]; 
		}
		int nOfLand = strlen(countriesWithLand[i]) - indexOfColon -1;

		//create list of landArea
		for(j=0;j<=nOfLand;j++){
			landAreas[i][j] = countriesWithLand[i][j+indexOfColon+1];
		}
		landAreasDou[i] = atoi(landAreas[i]); 
		nOfCountries++;
	}
	
	/*  debug
	
	//info
	printf("===arrary of country=====\n");
	for(i=0;i<nOfCountries;i++){
		printf("%s : %d\n", countries[i], landAreasDou[i]);	
	}	
	printf("===========================\n");
	
	*/
	
	/* Program to compare land area*/
	int nInput=1;
	char countryInput[2][20] = {}; 
	char countryInputDelete[2][20] = {}; 
	int correctIndex[2] ={999999,999999}; //fail safe.
	int correctIndexTemp;
	double multiplier;
	int w=0;
	int switcher=0;
	//restart progrma
	while(switcher==0){
		// switcher=1;
		w=0;
		while(w<2){
		// user input 
			printf("country[%d]: ", w+1);
			fgets(countryInput[w],20,stdin);
			countryInput[w][strcspn(countryInput[w], "\n")] = 0;
			//scanf("%s", &countryInput[w]);
			strlwr(countryInput[w]);
			//clean up
			strcpy(nameTwoTemp,countryInput[w]);
			//iterate each country
			for(k=0;k<sizeofR;k++){   
				//swap bigger to first    
				// printf("**current country: %s\n", countries[k]);
				if(strlen(countryInput[w])<strlen(countries[k])){
				strcpy(nameTemp, countries[k]);
				strcpy(countries[k], countryInput[w]);
				strcpy(countryInput[w],nameTemp);
				}
				else if(strlen(countryInput[w])>=strlen(countries[k])){
					strcpy(nameTemp,countryInput[w]);
				}
				// iterate each char of each country
				for(i=0;i<strlen(countries[k]); i++ ){
					// iterate through all countryInput[w] with char of country
					for(j=0;j<strlen(countryInput[w]);j++){
						if(countries[k][i] == countryInput[w][j]){
							//printf("%c = %c ", countries[k][i], countryInput[w][j]);
							countryInput[w][j] = '*';
							relatives++;
							// printf(" O %s ", countryInput[w]);
							mMargin = abs(i-j);
							//math
							sEquation = (1) / (1+ pow(M_E,-4.6+1.4*mMargin));
							if(sEquation>0.99){sEquation =1;}
							// printf(" => %lf", sEquation);
							mTotal = mTotal+ sEquation;
							nMTotal++;
							//printf("Margin : %d\n", mMargin);
							break;
						}	
					}
				}
				//calculation
				percentageM = mTotal/strlen(countryInput[w]) *100;
				
				/*
				printf("mTotal: %lf\n", mTotal);
				printf("nMtotal: %d\n", nMTotal);
				printf("percentageM: %lf\n", percentageM);
				*/
		
				//recalibrate (bullshit terminalogy)
				if(strlen(nameTwoTemp)<strlen(nameTemp)){
				strcpy(countries[k], nameTemp);
				}
				
				//set memories
				if(percentageM>prePercentageM){	
					for(i=0;arrLen>0;arrLen--){
						strcpy(probableR[arrLen], " ");
					}
					preRelatives = relatives;
					prePercentageM = percentageM;
					strcpy(probableR[arrLen], countries[k]);
					arrLen++;
				}
				else if(percentageM==prePercentageM){
					strcpy(probableR[arrLen],countries[k]);
					arrLen++;
					//printf("increment j: %d\n", arrLen);
				}
				
				/*
				//print the info
				for(i=0;i<arrLen;i++){
				printf("Most probable: %s\n", probableR[i]);
				}
				printf("Number of relative: %d\n", relatives);
				printf("=============================\n");
				*/
				
				//reset
				mTotal=0;
				relatives = 0;
				nMTotal=0;
				strcpy(countryInput[w],nameTwoTemp);
			}	
			
			/*
			//final result
			printf("============RESULT============\n");
			for(i=0;i<arrLen;i++){
			printf("Most probable: %s\n", probableR[i]);
			}
			printf("Number of relative: %d\n", preRelatives);
			printf("PercentageCloseness: %lf\n", prePercentageM);
			printf("=============================\n");
			*/
			
			//connector
			if(arrLen>1){
				printf("	Input too ambiguous.\n ");
				printf("	Please choose: ");
				for(i=0;i<arrLen;i++){
				printf("%s ,", probableR[i]);
				}
				printf("\n");
			}
			else if(arrLen==1){
				strcpy(countryInput[w],probableR[0]);
				w++;
			}
		   
			//loop reset
			arrLen=0;
			percentageM=0;
			prePercentageM=0;
		}	
	
		//compare and set the output (will always match tho)
		for(i=0;i<2;i++){
			for(j=0;j<nOfCountries;j++)
			if(strcmp(countryInput[i],countries[j])==0){ 
				correctIndex[i] = j;
				break;
			}		
		}
		
	 	//swap big country to first holder
	 	if(landAreasDou[correctIndex[0]] < landAreasDou[correctIndex[1]]){
	 		correctIndexTemp = correctIndex[0];
	 		correctIndex[0] = correctIndex[1];
			correctIndex[1] = correctIndexTemp;
		}
		
		//calculation
		multiplier = (double) landAreasDou[correctIndex[0]] / landAreasDou[correctIndex[1]];
	
		//Final Output	
		printf("%s is %.2lf bigger than %s. \n", countries[correctIndex[0]], multiplier, countries[correctIndex[1]]);
		printf("=======================================\n");
	}

	
	return 0;
}



