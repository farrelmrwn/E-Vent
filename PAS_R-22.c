/*
PEMROGRAMAN LANJUT + PRAKTIKUM 02
PROYEK UAS (E-Vent)
Program ini memiliki 2 mode yaitu mode
admin dan mode user. Mode admin memungkinkan
untuk menambahkan event baru dan menghapus 
event lama, sedangkan mode user bisa beli tiket
dan bisa cancel beli tiket. Program ini menggunakan
linked list dan file handling serta bersifat parallel
programming di beberapa bagian
KELOMPOK 22
Aliefya Fikri Ihsani-2106733843
Muhammad Farrel Mirawan-2106731554
*/
//Link Github : https://github.com/farrelmirawan/PAS-22
//Link Youtube:https://www.youtube.com/watch?v=lqlVs8bXi18

//library-library yang digunakan
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>


//Struct untuk melakukan linked list
//Struct untuk data login akun
struct login{
	char username[10];
	char password[10];
	struct login *next_login;
}*akun;

//Struct untuk data event
struct Event{
	char no[3];
	char event[32];
	char lokasi[32];
	int harga;
	int kuota;
	char tanggal[10];
	int jumlah;
	int total;
	char nama[50];
	struct Event *next_event;
};
struct Event *head;

//Fungsi-fungsi yang digunakan pada program
void mainscreen();
void login();
void regist();
void user();
void admin();
void menu_admin(char username[10]);
void menu_user(char username[10]);
int book_event(struct Event *head, int *counter, FILE *fp);
void lihat_event(int counter,char username[10]);
int cancel_event(int *counter);
int add_event(struct Event *head, int *loop);
void see_event(int loop);
int delete_event(int *loop);


int main(){
	system("color 5f");
	int opsi;
	mainscreen();
	printf("\t  ----HALOOO SOBAT E-VENT----\n");
	printf("\tSebelum mulai kita login dulu yuk\n");
	printf("  Apabila belum memiliki akun bisa register dulu yaa\n\n");
	printf("1. Login\n2. Register\n");
	printf("Pilihan : ");
	scanf("%d",&opsi);
	//login apabila sudah memiliki akun, register apabila belum
	if(opsi == 1){
		system("CLS");
		login();
	}
	else if(opsi == 2){
		system("CLS");
		regist();
	}
}

//function untuk menunjukkan layar awal
void mainscreen(){
	printf("		   ===============================\n");
	printf("		[||]        PROYEK AKHIR          [||]\n");
	printf("		 ||            E-VENT              ||\n");
	printf("		 ||          Kelompok 22           ||\n");
	printf("		 ||      Aliefya Fikri Ihsani      ||\n");
	printf("		[||]    Muhammad Farrel Mirawan   [||]\n");
	printf("		   ===============================\n");	
	printf("			Press Enter to Continue\n");
	getchar();
	system("CLS");
}

//function untuk menunjukkan menu untuk admin
void menu_admin(char username[10]){
	// untuk linked list
	struct Event *temp;
	head = NULL;
    temp = NULL;
    int loop = 0, opsi;
    //menggunakan do while, program akan loop sampai kondisi tercapai
    do{
		printf("		||============================||\n");
		printf("		||SELAMAT DATANG DI MENU ADMIN||\n");
		printf("		||	     %s           ||\n",username);
		printf("		||============================||\n");
		printf("		||1. Tambah Event             ||\n");
		printf("		||2. Hapus Event              ||\n");
		printf("		||3. Lihat Event              ||\n");
		printf("		||4. Exit to login            ||\n");
		printf("		||5. Exit program             ||\n");
		printf("		||============================||\n");
		printf("		Pilih : ");
		scanf("%d",&opsi);
		//switch case dengan variabel opsi
		switch(opsi){
			case 1:
				add_event(head,&loop);
				break;
			case 2:
				system("CLS");
				delete_event(&loop);
				break;
			case 3:
				see_event(loop);
				break;
			case 4:
				login();
		}
	}while(opsi>0&&opsi<5);//apabila opsi kurang dari 0 atau lebih dari 5 maka loop berhenti
	printf("Thankyou for using our program\n");
	printf("Have a nice day\n");
	printf("Sobat E-VENT !!!!");
	exit(1);
}

//function untuk menambahkan event baru
int add_event(struct Event *head, int *loop){
	//digunakan untuk melakukan linkedlist
	struct Event *newdata;
	struct Event *current;
	char ch;
	//dynamic memory allocation dengan malloc
	newdata = malloc(sizeof(struct Event));
	//untuk membuka file
	FILE *fp;
	fp = fopen("Event.txt","r");//"r" berarti hanya dibaca saja
	if(fp==NULL){//apabila file tidak ada maka akan diberikan peringatan
		printf("FILE DOES NOT FOUND!\n");
		exit(1);
	}
	else {
		system("CLS");//untuk membersihkan layar
		printf("===========================\n");
		printf("LIST EVENT YANG AKAN TAYANG\n");
		printf("===========================\n");
		printf("No\tNama\t\tLokasi\t\tHarga\t\tTanggal\n");
		printf("-----------------------------------------------------------------\n");
		//digunakan untuk mencetak satu isi file Event.txt
		while( ( ch = fgetc(fp) ) != EOF ){//EOF artinya end of file
			printf("%c",ch);
		}
		
	}
	//menutup file agar tidak boros
	fclose(fp);
	printf("\n\n");
	printf("==========================\n");
	printf("MASUKKAN DETAIL EVENT BARU\n");
	printf("==========================\n");
	if(newdata!=NULL){
		//meminta data event baru dan ditaruh di newdata
		printf("Event ke berapa(No) : ");
		scanf("%s",&newdata->no);
		printf("Nama Event : ");
		scanf("	%[^\n]s",&newdata->event);
		printf("Lokasi Event : ");
		scanf("	%[^\n]s",&newdata->lokasi);
		printf("Harga Tiket : ");
		scanf("%d",&newdata->harga);
		printf("Tanggal Event (dd/mm/yyyy) : ");
		scanf("%s",&newdata->tanggal);
		//membuka file Event.txt
		fp = fopen("Event.txt","a");//"a" artinya append, akan ditambahkan kata setelah kata yg sudah ada
		if(fp==NULL){
			printf("Error File not found\n");
			exit(1);
		}
		else{
			//Pencetakan data event yang baru diinput
			fprintf(fp,"\n%s%13s%15s%16d%21s",newdata->no,newdata->event,newdata->lokasi,
			newdata->harga,newdata->tanggal);
			printf("Event berhasil ditambahkan\n");
		}
		fclose(fp);//menutup file
		if(head == NULL){
            head = newdata;
            (*loop)++;
        }
		else{
            current = head;
            while(current->next_event != NULL){
            current = current->next_event;
        	}
        	current->next_event = newdata;
            (*loop)++;
        }
        //diatas adalah linkedlist agar menyimpan node lama dan membuka node baru
	}
	return *loop;
}

//function untuk melihat event-event
void see_event(int loop){
	int x,i;
	int total;
	char ch;
	//untuk membuka file Event.txt
	FILE *fp;
	fp = fopen("Event.txt","r");
	if(fp==NULL){
		printf("FILE DOES NOT FOUND!\n");
		exit(1);
	}
	else {
		//parallel programming 
		#pragma omp parallel
		{
			//agar thread master yang mengerjakan tugas dibawah
			#pragma omp master
			{
				system("CLS");
				printf("===========================\n");
				printf("LIST EVENT YANG AKAN TAYANG\n");
				printf("===========================\n");
				printf("No\tNama\t\tLokasi\t\tHarga\t\tTanggal\n");
				printf("-----------------------------------------------------------------\n");
				#pragma omp task firstprivate(ch)
				while( ( ch = fgetc(fp) ) != EOF ){
				printf("%c",ch);
				};	
			}
			//menunggu sampai task lain selesai
			#pragma omp barrier
			fclose(fp);
		}	
		
	}
	printf("\n");
	printf("Lanjut(1)/Exit program(0)\n");
	printf("Pilihan : ");
	scanf("%d",&x);
	if(x==1){
		return;	
	}
	else if(x==0){
		exit(1);
	}
}

//function untuk menghapus event
int delete_event(int *loop){
	//deklarasi variabel-variabel yang digunakan
	int i,row,temp_harga,temp_kuota;
	int cout=0;
	char temp_event[20];
	char temp_tanggal[20];
	char temp_no[3];
	char temp_lokasi[20];
	char ch;
	//untuk membuka file Event.txt dan tempevent.txt
	FILE *fp1;
	FILE *fp2;
	fp1 = fopen("Event.txt","r");
	if(!fp1){
		printf("\nFile tidak ditemukan\n\n");
        system("pause");
        return 0;
	}
	fp2 = fopen("tempevent.txt","w");//file sementara yang nanti akan dihapus
	if(!fp2){
		printf("Gagal membuat file temp\n\n");
		fclose(fp1);
		return 0;
	}
	do{
		//menclear input yang berlebih
        fflush(stdin);
        printf("\nMasukkan baris event yang ingin dihapus: ");
    }while(scanf("%d", &row) != 1);
    
    while (!feof(fp1)){//end of file
    	//akan mengscan isi file dan disimpan di variabel temp
        fscanf(fp1,"%s%13s%15s%16d%21s", temp_no,temp_event,temp_lokasi,
		&temp_harga,temp_tanggal);
        if(!feof(fp1)) {
            cout++;
            //Jika cout sama dengan row maka akan meng-skip fprintf
            if (cout != row){
            	//akan mencetak isi temp tadi di file baru
        		fprintf(fp2,"\n%s%13s%15s%16d%21s", temp_no,temp_event,temp_lokasi,
				temp_harga,temp_tanggal);
            }
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("Event.txt");//menghapus Event.txt
    rename("tempevent.txt","Event.txt");//mengganti tempevent.txt menjadi Event.txt
    printf("Event telah berhasil di hapus\n");
    (*loop)--;//decrement karena sudah ada yang dihapus
    return *loop;
}

//Function yang menunjukkan menu untuk user
void menu_user(char username[10]){
	//untuk linked list
	struct Event *temp;
	head = NULL;
    temp = NULL;
    int counter = 0, pilihan;
    //untuk file handling
    FILE *fp;
    do{//menggunakan do while, akan terus looping sampai kondisi terpenuhi
    	printf("\n");
		printf("		||============================||\n");
		printf("		||SELAMAT DATANG DI MENU USER ||\n");
		printf("		||	     %s           ||\n",username);
		printf("		||============================||\n");
		printf("		||1. Booking Event            ||\n");
		printf("		||2. Lihat List Bookingan     ||\n");
		printf("		||3. Cancel Tiket             ||\n");
		printf("		||4. Exit to login            ||\n");
		printf("		||5. Exit program             ||\n");
		printf("		||============================||\n");
		printf("		Pilih : ");
	    scanf("%d",&pilihan);
        switch(pilihan){
    		case 1:
    			book_event(head,&counter,fp);
    			break;
    		case 2:
    			system("CLS");
    			printf("\n***********************\n");
    			printf("List Event yang di book\n");
    			printf("***********************\n");
    			lihat_event(counter,username);
    			break;
    		case 3:
    			system("CLS");
    			cancel_event(&counter);
    			break;
    		case 4:
    			login();
    			break;
		}	
	}while(pilihan < 5 && pilihan > 0);
	printf("Thankyou for using our program\n");
	printf("Have a nice day\n");
	printf("Sobat E-VENT !!!!");
}

//function untuk booking tiket event
int book_event(struct Event *head, int *counter, FILE *fp){
	//untuk linked list
	struct Event *newdata;
	struct Event *current;
	char ch;
	int total;
	//dynamic memory allocation dengan malloc
	newdata = malloc(sizeof(struct Event));
	int i,confirm;
	FILE *op;
	//ada 2 file yang digunakan yaitu Event.txt dan Book.txt
	fp = fopen("Event.txt","r");
	op = fopen("Book.txt","a");
	if(fp==NULL){
		printf("FILE DOES NOT FOUND!\n");
		exit(1);
	}
	else{
		system("CLS");
		printf("===========================\n");
		printf("LIST EVENT YANG AKAN TAYANG\n");
		printf("===========================\n");
		printf("No	Nama		Lokasi		Harga		Tanggal\n");
		printf("-----------------------------------------------------------------\n");
		//untuk mencetak semua event
		while( ( ch = fgetc(fp) ) != EOF ){
			printf("%c",ch);
		}
	}
	//menutup file
	fclose(fp);
	printf("\n\n");
	printf("BOOKING TIKET EVENT\n");
	if(newdata!=NULL){
		//menginput data
		printf("Nama Pembooking : ");
		scanf("	%[^\n]s",&newdata->nama);
		printf("Nama Event : ");
		scanf("	%[^\n]s",&newdata->event);
		printf("Tanggal Event(dd/mm/yyyy): ");
		scanf("	%[^\n]s",&newdata->tanggal);
		printf("Harga :Rp.");
		scanf("%d",&newdata->harga);
		printf("Pesan berapa tiket : ");
		scanf("%d",&newdata->jumlah);
		//menghitung harga total 
		newdata->total = newdata->harga*newdata->jumlah;
		//sistem menunggu sebentar
		system("pause");
		//membersihkan layar sistem
		system("CLS");
		//mengkonfirmasi pesanan
		printf("Konfirmasi pemesanan tiket: \n");
		printf("\nNama Pemesan	: %s", newdata->nama);
		printf("\nNama Event 	: %s", newdata->event);
		printf("\nTanggal Event	: %s",newdata->tanggal);
		printf("\nJumlah Tiket 	: %d",newdata->jumlah);
		printf("\nHarga total	: %d", newdata->total);
		printf("\nTekan (1) untuk konfirmasi: ");
		scanf("%d",&confirm);
		if(confirm == 1){
			printf("Pesanan telah dikonfirmasi\n");
			//mencetak input tadi kedalam file Book.txt
			fprintf(op,"%s\t%s\t%d\t%s\n",newdata->nama,newdata->event,newdata->total,newdata->tanggal);
			fclose(op);
			newdata->next_event=NULL;
			if(head == NULL){
            	head = newdata;
            	(*counter)++;
        	}
			else{
            	current = head;
            	while(current->next_event != NULL){
            	current = current->next_event;
        		}
        		current->next_event = newdata;
            	(*counter)++;
        	}
        	//diatas adalah linked list untuk menyimpan data tadi dan membuka node baru
		}
		else{
			system("CLS");
			fclose(op);
			return;
		}
    }
}

//Function untuk melihat history bookingan
void lihat_event(int counter,char username[10]){
	char temp_nama[20],temp_event[20],temp_tanggal[20];
	int temp_harga,i;
	int total,sum=0;
	char carinama[20];
	FILE *op;
	FILE *fp;
	op = fopen("Book.txt","r");
	if(op==NULL){
		printf("FILE DOES NOT FOUND!\n");
		printf("BELUM MELAKUKAN BOOKING\n");
		system("pause");
		return;
	}
	printf("PESANAN USER : %s\n",username);
	//parallel programming
	#pragma omp parallel
	{
		//agar masing-masing thread bisa mengerjakan tugasnya dalam loop for
		#pragma omp for ordered private(temp_nama, temp_event,temp_harga,i)
		for(i=0;i<counter;i++){
			#pragma omp critical
			fscanf(op,"%s\t%s\t%d\t%s",temp_nama,temp_event,&temp_harga,temp_tanggal);
			printf("Event #%d\n",i+1);
			//Mencetak riwayat bookingan
			printf("=========================");
			printf("\nNama Pemesan	: %s", temp_nama);
			printf("\nNama Event 	: %s", temp_event);
			printf("\nHarga total	: %d", temp_harga);
			printf("\nTanggal Event	: %s", temp_tanggal);
			printf("\n=========================\n");
			total += temp_harga;
		}
		//digunakan untuk mereduksi variabel total agar langsung memberikan hasilnya
		#pragma omp for reduction(+:total)
		//untuk menghitung harga total
		for(i=0;i<counter;i++){
			total = total *1;
		}
		//agar hanya 1 thread saja yang menjalankan task
		#pragma omp single
		{
			printf("Harga total dari semua event = Rp.%d\n",total);
		}
	//hanya akan jalan apabila task lain selesai
	#pragma omp taskwait
	fclose(op);	
	}
}

//function untuk mengcancel bookingan tiket
int cancel_event(int *counter){
	//variabel-variabel yang digunakan
	int i, baris, temp_harga;
	int count = 0;
	char temp_nama[20];
	char temp_event[20];
	char temp_tanggal[20];
	//menggunakan 2 file yaitu Book.txt dan tempbook.txt
	FILE *file1;
	FILE *file2;
	file1 = fopen("Book.txt","r");
	if (!file1) {
        printf("\nFile tidak ditemukan\n\n");
        system("pause");
        return 0;
    }
    file2= fopen("tempbook.txt","w");
    if (!file2) {
        printf("Gagal membuat file temporary\n\n");
        fclose(file1);
        return 0;
    }
    do{
    	//menghapus input berlebihan
        fflush(stdin);
        printf("\nMasukkan baris tiket (no) yang ingin dihapus: ");
    }while(scanf("%d", &baris) != 1);
    
    while (!feof(file1)){//end of file
    	//mengscan isi file dan disimpan divariabel temp
        fscanf(file1, "%s\t%s\t%d\t%s", temp_nama,temp_event,&temp_harga,temp_tanggal);
        if(!feof(file1)) {
            count++;
            //Jika count sama dengan baris maka akan meng-skip fprintf
            if (count != baris){
            	//mencetak variabel temp tadi ke file tempbook.txt
        		fprintf(file2, "%s\t%s\t%d\t%s\n", temp_nama,temp_event,temp_harga,temp_tanggal);
            }
        }
    }
    //menutup file agar tidak boros
    fclose(file1);
    fclose(file2);
    //menghapus Book.txt
    remove("Book.txt");
    //menggantikan tempbook.txt dengan Book.txt
    rename("tempbook.txt","Book.txt");
    printf("Bookingan telah berhasil di cancel\n");
    (*counter)--;//decrement karena sudah ada yang dihapus
    return *counter;
}

//function untuk masuk kedalam akun
void login(){
	int pengguna;
	printf("\nLogin sebagai apa :\n");
	printf("1. User\n2. Admin\n");
	scanf("%d",&pengguna);
	//ada 2 mode yaitu user dan admin
	if(pengguna == 1){
		system("CLS");
		user();
	}
	else if(pengguna == 2){
		system("CLS");
		admin();
	}	
}

//function login untuk user
void user(){
	printf("HALO USER!!\n");
	char c,username[10],password[10];
	int i,z=0;
	FILE *fp;
	//dynamic memory allocation untuk menyimpan akun
	akun=(struct login*)malloc(sizeof(struct login));
	fp = fopen("login.txt","rb");
	if(fp == NULL){
		printf("Error, belum ada akun\n");
		printf("Silahkan register terlebih dahulu\n");
		system("pause");
		main();
	}
    printf("ENTER USERNAME: ");
    scanf("%9s",username);
    printf("\nENTER PASSWORD: ");
    //membuat password menjadi tersembunyi
    while((c=getch())!=13){
    	password[z++]=c;
        printf("%c",'*');
    }
    password[z]='\0';
    // looping untuk mengecek kebenaran input username dan password
    while(fread (akun, sizeof(struct login), 1, fp) == 1){
    	//apabila username dan password cocok dengan isi file login.txt
        if(strcmp(akun->username,username)==0 && strcmp(akun->password,password)==0){
            printf("\nYOU HAVE LOGGED IN SUCCESSFULLY!!");
            //membebaskan varaiabel akun
            free(akun);
   		 	getch();
   		 	//menutup file
		    fclose(fp);
		    //membersihkan layar
		    system("CLS");
		    menu_user(username);
        }
        //apabila username cocok namun password salah
        else if(strcmp(akun->username,username)==0 && strcmp(akun->password,password)!=0){
            printf("\nWRONG PASSWORD!! Not %s??",username);
            login();
        }
        //apabila username salah
        else if(strcmp(akun->username,username)!=0){
            printf("\nYou are not a Registered User\nPress enter to register yourself");
            regist();
        }
    }
}

//function untuk login admin 
void admin(){
	//variabel yang akan digunakan
	char c,username[50],password[50];
	int i,z=0;
	int checku,checkp,adm;
	char b;
	int y =0;
	//membuka file
	FILE *fp;
	fp = fopen("login.txt","rb");
	if(fp == NULL){
		printf("Error, belum ada akun\n");
		printf("Silahkan register terlebih dahulu\n");
		system("pause");
		main();
	}
	//dynamic memory allocation menggunakan malloc
	akun=(struct login*)malloc(sizeof(struct login));

	printf("HALO ADMIN!!\n");
    printf("ENTER USERNAME: ");
    scanf("%9s",username);
    printf("\nENTER PASSWORD: ");
    //agar password tersembunyikan
    while((c=getch())!=13){
    	password[z++]=c;
        printf("%c",'*');
    }
    printf("\nENTER ADMIN CODE: ");
    scanf("%d",&adm);
    
	printf("\n");
    password[z]='\0';
    //looping untuk mengecek username, input dan kode admin
    while(fread (akun, sizeof(struct login), 1, fp) == 1){
    	//apabila semua input benar
        if(strcmp(akun->username,username)==0 && strcmp(akun->password,password)==0 && adm == 123){
            printf("\nYOU HAVE LOGGED IN SUCCESSFULLY!!");
            fclose(fp);
    		free(akun);
    		getch();
    		system("CLS");
    		menu_admin(username);
        }
        //apabila username dan password benar namun kode admin salah
        else if(strcmp(akun->username,username)==0 && strcmp(akun->password,password)==0 && adm != 123){
        	printf("WRONG ADMIN CODE\n");
        	printf("Please login again\n");
        	login();
		}
		//apabila username benar namun password salah
        else if(strcmp(akun->username,username)==0 && strcmp(akun->password,password)!=0){
            printf("\nWRONG PASSWORD!! Not %s??",username);
            login();
        }
        //apabila username salah
        else if(strcmp(akun->username,username)!=0){
            printf("\nYou are not a Registered User\nPress enter to register yourself");
            regist();
        }
    }
}

//function untuk registrasi akun
void regist(){
	char check[10],c,b;
	int y = 0;
	FILE *fp;
	//dynamic memory allocation
	akun=(struct login*)malloc(sizeof(struct login));
	if ((fp=fopen("login.txt", "a+")) == NULL){
        if ((fp=fopen("login.txt", "w+")) == NULL){
            printf ("Could not open file\n");
            exit(1);
        }
    }
    printf("\n=============\n");
    printf("MENU REGISTER\n");
    printf("=============\n");
	printf("\nSelamat datang user baru\n");
	printf("\nTolong masukkan username dan password anda\n");
	printf("Username (Maks 9 karakter) : ");
	scanf("%9s", akun->username);
	printf("Password (Maks 9 karakter) : ");
	scanf("%9s",akun->password);
	fwrite(akun,sizeof(struct login),1,fp);
	fclose(fp);

	printf("\nRegistrasi berhasil");
	printf("\nAnda bisa login");
	printf("\n");
	free(akun);
	login();	
}
