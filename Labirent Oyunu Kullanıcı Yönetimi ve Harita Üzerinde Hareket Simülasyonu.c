#include <stdio.h>
#include <string.h>

#define MAX_USERS 100 


struct User {
    char name[50];
    char surname[50];
    char username[50];
    char password[50];
};

void writeUsersToFile(struct User users[], int userCount) {
    FILE *file = fopen("users.bin", "wb"); 
    fwrite(users, sizeof(struct User), userCount, file); 
    fclose(file);
}

int isUsernameExisting(struct User users[], int userCount, char *username) {
	int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1; 
        }
    }
    return 0;
}
void displayUsersFromFile() {
    struct User users[MAX_USERS];
    int userCount = 0;
    int i;

    FILE *file = fopen("users.bin", "rb");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        userCount = fileSize / sizeof(struct User);
        fread(users, sizeof(struct User), userCount, file);
        fclose(file);

        printf("Kullanici Bilgileri:\n");
        for (i = 0; i < userCount; i++) {
            printf("Kullanici %d:\n", i + 1);
            printf("Isim: %s\n", users[i].name);
            printf("Soyisim: %s\n", users[i].surname);
            printf("Kullanici Adi: %s\n", users[i].username);
            printf("Sifre: %s\n", users[i].password);
            printf("\n");
        }
    } else {
        printf("Dosya acilamadi!\n");
    }
}
void printMap(char **map, int rows, int cols) {
	int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%c\t", map[i][j]);
        }
        printf("\n\n");
    }
}
void readMap(const char *filename, char **matris,int ROWS,int COLS) {
    FILE *dosya = fopen(filename, "r");
    int i,j,rX,cX;
    ROWS = 0;
	COLS = 0;
    char c;
    // Sat�r ve s�tun say�s�n� belirleme
    while ((c = fgetc(dosya)) != EOF && c != '\n') {
        COLS++;
    }
    fseek(dosya, 0, SEEK_SET); 

    while ((c = fgetc(dosya)) != EOF) {
        if (c == '\n') {
            ROWS++;
        }
    }
    fseek(dosya, 0, SEEK_SET);  
    COLS++;
    
    matris = (char **)malloc(ROWS * sizeof(char *));
    for (i = 0; i < ROWS; i++) {
        matris[i] = (char *)malloc((COLS + 1) * sizeof(char)); 
        if (matris[i] == NULL) {
            printf("Bellek hatas�!\n");
            for (j = 0; j < i; j++) {
                free(matris[j]);
            }
            free(matris);
            fclose(dosya);
            return;
        }
    }
    
    i = 0;
    while (fgets(matris[i], COLS + 1, dosya) != NULL && i < ROWS) {
        matris[i][COLS] = '\0'; 
        i++;
    }

    fclose(dosya);
    
    for (i = 0; i < ROWS; ++i) {               
        for (j = 0; j < COLS; ++j) {
            if (matris[i][j] == 'X') {
                rX=i;
                cX=j;
            }
        }
    }

    for (i = 0; i < ROWS; i++) {
        free(matris[i]);
    }
    free(matris);
}


void printInventory(char inventory[], int NumParticles) {
	int i;
    for (i = 0; i < NumParticles; i++) {
        printf("%c ", inventory[i]);
    }
    printf("\n");
}


int main() {
    struct User users[MAX_USERS];
    int userCount = 0;
    char tempUsername[50];
    char tempPassword[50];
    int isExisting = 0;
    int addAnotherUser = 1; // Kontrol de�i�keni
    int choice, mapNum;
    int k=0,i,j;
    FILE *file = fopen("users.bin", "rb");
    if (file != NULL) {
        // Dosya varsa, daha �nce kaydedilmi� kullan�c� bilgilerini oku
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        userCount = fileSize / sizeof(struct User);
        fread(users, sizeof(struct User), userCount, file);
        fclose(file);
    }
    
    printf("                        LABIRENT OYUNUNA HOSGELDINIZ\n");
    printf("1.Kayit Ol\n");
    printf("2.Giris Yap\n");
    scanf("%d",&choice);
    
    switch(choice){
    	case 1:
    		

    while (addAnotherUser) { 
        printf("�sim: ");
        scanf("%s", users[userCount].name);

        printf("Soyisim: ");
        scanf("%s", users[userCount].surname);

        do {
            printf("Kullan�c� Ad�: ");
            scanf("%s", tempUsername);

            isExisting = isUsernameExisting(users, userCount, tempUsername);

            if (isExisting) {
                printf("Bu kullan�c� ad� zaten kullan�lm��. L�tfen farkl� bir kullan�c� ad� se�in.\n");
            } else {
                strcpy(users[userCount].username, tempUsername); 
                printf("�ifre: ");
                scanf("%s", users[userCount].password);

                userCount++; 
                break; 
            }
        } while (isExisting);

        printf("Ba�ka bir kullan�c� eklemek istiyor musunuz? (E/H): ");
        char choice;
        scanf(" %c", &choice);

        if (choice != 'E' && choice != 'e') {
            addAnotherUser = 0; 
        }
    }

    
    writeUsersToFile(users, userCount);
    break;
    
    	case 2:
    		
    		while(k==0){
    			printf("Kullan�c� Ad�: ");
    		scanf("%s", tempUsername);

    		printf("�ifre: ");
    		scanf("%s", tempPassword);

    		int isLoggedIn = 0; 

    		
    		int i = 0;
    		while (i < userCount && !isLoggedIn) {
       		if (strcmp(users[i].username, tempUsername) == 0 && strcmp(users[i].password, tempPassword) == 0) {
            	isLoggedIn = 1; 
        	}
        	i++;
    		}
			if (isLoggedIn) {
        		printf("Giri� ba�ar�l�! \n");	
       			k++;
        	} else {
        		printf("Kullan�c� ad� veya �ifre hatal�!\n");
        		
			}
			}
    		 
    
    break;
    		
	}
	


	
	fclose(file);
	
	printf("Oynamak istediginiz mapi secin:\n");
	printf("MAP-1\n");
	printf("MAP-2\n");
	printf("MAP-3\n");
	printf("MAP-4\n");
	scanf("%d",&mapNum);
	
	
	FILE *dosya;
    char **matris;
    int ROWS = 0;
    int COLS = 0;
    int gameOver = 0;
	int stepsize = 1;
	int flag = 0;
	char way;
	int rX,cX;
	char inventory[20];
	int NumParticles=0;
    switch(mapNum){
    	case 1:	
    		readMap("map1.txt",matris,ROWS,COLS); 
			
				printMap(matris, ROWS, COLS);
				scanf(" %c",&way);									
				if(way == 'w' || way == 'W'){
					printf("Yon: Up\n\n");
					if(matris[rX-1][cX]=='1'){
						printf("yanlis hamle!\n\n");
						flag=1;
					}
					if(matris[rX-1][cX]=='P'){
						if(stepsize==1){
							matris[rX][cX]='G';
						}
						else{
							matris[rX][cX]='0';
						}
						inventory[NumParticles]='P';
						matris[rX-1][cX]='X';
						printf("%d. Adim: \n\n",stepsize);
						printInventory(inventory,NumParticles);
						printf("\n\n");
						printMap(matris, ROWS, COLS);
						NumParticles++;
						stepsize++;
						flag=0;
					}
					if(matris[rX-1][cX]=='p'){
						if(stepsize==1){
							matris[rX][cX]='G';
						}
						else{
							matris[rX][cX]='0';
						}
						inventory[NumParticles]='p';
						matris[rX-1][cX]='X';
						printf("%d. Adim: \n\n",stepsize);
						printInventory(inventory,NumParticles);
						printf("\n\n");
						printMap(matris, ROWS, COLS);
						NumParticles++;
						stepsize++;
						flag=0;
					}
					if(matris[rX-1][cX]=='E'){
						if(stepsize==1){
							matris[rX][cX]='G';
						}
						else{
							matris[rX][cX]='0';
						}
						inventory[NumParticles]='E';
						matris[rX-1][cX]='X';
						printf("%d. Adim: \n\n",stepsize);
						printInventory(inventory,NumParticles);
						printf("\n\n");
						printMap(matris, ROWS, COLS);
						NumParticles++;
						stepsize++;
						flag=0;
					}
					if(matris[rX-1][cX]=='e'){
						if(stepsize==1){
							matris[rX][cX]='G';
						}
						else{
							matris[rX][cX]='0';
						}
						inventory[NumParticles]='e';
						matris[rX-1][cX]='X';
						printf("%d. Adim: \n\n",stepsize);
						printInventory(inventory,NumParticles);
						printf("\n\n");
						printMap(matris, ROWS, COLS);
						NumParticles++;
						stepsize++;
						flag=0;
					}
					
					
			
				}
				
		
		
			break;
		
		case 2:
			readMap("map1.txt",matris,ROWS,COLS); 
			//printMap(matris, ROWS, COLS);
			for (i = 0; i < ROWS; i++) {
        		for (j = 0; j < COLS; j++) {
            		printf("%c\t", matris[i][j]);
        		}
        		printf("\n\n");
			break;	
			}
	}
	

    

    return 0;
}

