#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Location{
	char name[50];
	char address[50];
};

typedef struct{
	char tripId[20];
	struct Location departure;
	struct Location destination;
	char date[20];
	int totalSeats;
	int bookedSeats;
}Trip;

struct Passenger{
	char name[50];
	char phone[15];
};

typedef struct{
	char ticketId[20];
	char tripId[20];
	struct Passenger passenger;
	int seatNumber;
	double price;
	int paymentStatus;
	char date[20];
	int status;
}Ticket;

// --- Cac ham ---
int isEmpty(const char *str);
int isTripIdExists(Trip *trips, int length, char *id);
double getValidNumber(const char *msg);
void addInfoTrip(Trip *cx, int *length);
void updateTrip(Trip *cx, int length);
int isPhone(char *s);
void bookTicket(Trip *trips, int tripCount, Ticket *tickets, int *ticketCount);
//void checkTicketStatus(Trip *trips, int tripCount, Ticket *tickets, int *ticketCount);
//void listTrips(Trip *trips, int length);
//void payTicket(Ticket *tickets, int ticketCount);
//void manageTicketsStatus(Trip *cx, int tripCount, Ticket *tickets, int ticketCount);
//void tripReport(Trip *cx, int tripCount, Ticket *tickets, int ticketCount);

int main(){
	int choice;
	int flag = 0;
	Trip cx[100];
	int length = 0;
	Ticket tickets[100];
	int ticketCount = 0;
	
	do{
		printf("\n-------------------------------------------\n");
		printf("|                  Menu                   |");
		printf("\n-------------------------------------------");
		printf("\n|1. Them chuyen xe moi                    |");
		printf("\n|2. Cap nhat thong tin chuyen xe          |");
		printf("\n|3. Dat ve                                |");
		printf("\n|4. Kiem tra tinh trang ve                |");
		printf("\n|5. Liet ke chuyen xe                     |");
		printf("\n|6. Thanh toan ve                         |");
		printf("\n|7. Quan ly trang thai ve                 |");
		printf("\n|8. Bao cao doanh thu & thong ke ve       |");
		printf("\n|9. Thoat                                 |");
		printf("\n-------------------------------------------");
		choice = getValidNumber("\nLua con cua ban: ");
		switch(choice){
			case 1:{
				addInfoTrip(cx,&length);
				flag=1;
				break;
			}
			
			case 2:{
				if(flag==0) printf("Chua co thong tin chuyen xe nao! Vui long chon 1 de nhap thong tin!\n");
				else updateTrip(cx,length);
				break;
			}	
			
			case 3:{
				bookTicket(cx, length, tickets, &ticketCount);
				break;
			}
			
			case 4:{
				if(flag==0) printf("Chua co chuyen xe nao! Vui long chon 1 de nhap thong tin chuyen xe!\n");
				else checkTicketStatus(cx, length, tickets, &ticketCount);
				break;
			}
			
			case 5:{
				listTrips(cx,length);
				break;
			}
			
			case 6:{
				if(flag==0) printf("Chua co chuyen xe nao! Vui long chon 1 de nhap thong tin chuyen xe!\n");
				else payTicket(tickets, ticketCount);
				break;
			}
			
			case 7:{
				if(flag==0) printf("Chua co chuyen xe nao! Vui long chon 1 de nhap thong tin chuyen xe!\n");
				else manageTicketsStatus(cx,length, tickets, ticketCount);
				break;
			}
			
			case 8:{
				if(flag==0) printf("Chua co chuyen xe nao! Vui long chon 1 de nhap thong tin chuyen xe!\n");
				else tripReport(cx,length, tickets, ticketCount);
				break;
			}
			
			case 9:{
				printf("Cam on quy khach vi da chon dich vu cua chung toi!");
				exit(0);
			}
		default:
			printf("Ko co lua chon %d\n", choice);
		}
	} while (choice !=9);
}

int isEmpty(const char *str){
	if(!str) return 1;
	while (*str) {
		if(*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r') return 0;
		str++;
	}
	return 1;
}

int isTripIdExists(Trip *cx, int length, char *id){
	int i;
	for (i=0; i<length; i++){
		if(strcmp(cx[i].tripId, id)==0) return 1;
	}
	return 0;
}

double getValidNumber(const char *msg){
	char buffer[50];
	double value;
	int i;
	
	while(1){
		printf("%s", msg);
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")]=0;
		if(strlen(buffer)==0){
			printf("Ko duoc de rong!\n");
			continue;
		}
		if(buffer[0] == '\0'){
			printf("Ban chua nhap gi! Vui long nhap so!\n");
			continue;
		}
		int valid=1;
		for(i=0;buffer[i] != '\0'; i++){
			if(buffer[i]<'0' || buffer[i]>'9'){
				valid=0;
				break;
			}
		}
		
		if(!valid){
			printf("Xin hay nhap lai so!\n");
			continue;
		}
		value=atof(buffer);
		return value;
	}
}

void addInfoTrip(Trip *cx, int *length){
	while(getchar() != '\n');
	int i;
	int size = getValidNumber("Nhap so luong chuyen xe: ");
	for(i=0;i<size;i++){
		Trip newTrip;
		do{
			printf("Nhap ma chuyen xe: ");
			fgets(newTrip.tripId, sizeof(newTrip.tripId), stdin);
			newTrip.tripId[strcspn(newTrip.tripId, "\n")]=0;
			if(isEmpty(newTrip.tripId)){
				printf("Ma chuyen xe ko dc rong!\n");
			} else if (isTripExists(cx, *length, newTrip.tripId)){
				printf("Ma chuyen xe da ton tai!\n");
			} else break;
	    } while(1);
	
		do{
			printf("Nhap ten diem di: ");
			fgets(newTrip.departure.name, sizeof(newTrip.departure.name), stdin);
			newTrip.departure.name[strcspn(newTrip.departure.name, "\n")]=0;
			
			if(isEmpty(newTrip.departure.name))
			    printf("Ten diem di ko dc rong!\n");
			else break;
		} while (1);
	
		do{
			printf("Nhap dia diem di: ");
			fgets(newTrip.departure.address, sizeof(newTrip.departure.address), stdin);
			newTrip.departure.address[strcspn(newTrip.departure.address, "\n")]=0;
			
			if(isEmpty(newTrip.departure.address))
			    printf("Dia chi diem di ko duoc rong!\n");
			else break;
		} while(1);
		
		do{
			printf("Nhap ten diem den: ");
			fgets(newTrip.destination.name, sizeof(newTrip.destination.name), stdin);
			newTrip.destination.name[strcspn(newTrip.destination.name, "\n")]=0;
			
			if(isEmpty(newTrip.destination.name))
			    printf("Ten diem den ko dc rong!\n");
			else break;
		} while(1);
		
		do{
			printf("Nhap dia diem den: ");
			fgets(newTrip.destination.address, sizeof(newTrip.destination.address), stdin);
			newTrip.destination.address[strcspn(newTrip.destination.address,"\n")]=0;
			
			if(isEmpty(newTrip.destination.address))
			    printf("Dia chi diem den ko dc rong!\n");
			else break;
		} while(1);
		
		do{
			printf("Nhap ngay gio chuyen di: ");
			fgets(newTrip.date, sizeof(newTrip.date), stdin);
			newTrip.date[strcspn(newTrip.date, "\n")]=0;
			
			if(isEmpty(newTrip.date))
			    printf("Ngay gio chuyen di ko dc rong!\n");
			else break;
		} while(1);
		
		do{
			newTrip.totalSeats=getValidNumber("Nhap tong so ghe: ");
			if(newTrip.totalSeats <= 0){
				printf("Tong so ghe phai>0\n");
			} else break;
		} while(1);
		newTrip.bookedSeats=0;
		cx[*length]=newTrip;
		(*length)++;
		printf("Them chuyen xe thanh cong!\n");
	}
}

void updateTrip(Trip *cx, int length){
	while(getchar() != '\n');
	char id[20];
	printf("Nhap ma chuyen xe can cap nhat: ");
	fgets(id, sizeof(id), stdin);
	id[strcspn(id,"\n")]=0;
	
	int i;
	for(i=0;i<length;i++){
		if(strcmp(cx[i].tripId, id)==0){
			printf("\n-------- Cap nhat thong tin chuyen xe ID %s --------\n", cx[i].tripId);
			Trip newTrip;
			strcpy(newTrip.tripId, cx[i].tripId);
			do{
				printf("Nhap ten diem di moi: ");
				fgets(newTrip.departure.name, sizeof(newTrip.departure.name), stdin);
				newTrip.departure.name[strcspn(newTrip.departure.name, "\n")]=0;
				
				if(isEmpty(newTrip.departure.name))
				    printf("Ten diem den ko duoc rong!\n");
				else break;
			} while (1);
			
			do{
				printf("Nhap dia chi diem di moi: ");
				fgets(newTrip.departure.address, sizeof(newTrip.departure.address), stdin);
				newTrip.departure.address[strcspn(newTrip.departure.address, "\n")]=0;
				
				if(isEmpty(newTrip.departure.address))
				    printf("Dia chi diem den ko duoc rong!\n");
				else break;
			} while(1);
			
			do{
				printf("Nhap ten diem den moi: ");
				fgets(newTrip.destination.name, sizeof(newTrip.destination.name), stdin);
				newTrip.destination.name[strcspn(newTrip.destination.name, "\n")]=0;
				
				if(isEmpty(newTrip.destination.name))
				    printf("Ten dia diem den ko duoc rong!\n");
				else break;
			} while (1);
			
			do{
				printf("Nhap dia chi den moi: ");
				fgets(newTrip.destination.address, sizeof(newTrip.destination.address), stdin);
				newTrip.destination.address[strcspn(newTrip.destination.address, "\n")]=0;
				
				if(isEmpty(newTrip.destination.address))
				    printf("Dia chi den ko duoc rong!\n");
				else break;
			} while(1);
			
			do{
				printf("Nhap ngay gio chuyen di moi: ");
				fgets(newTrip.date, sizeof(newTrip.date), stdin);
				newTrip.date[strcspn(newTrip.date, "\n")]=0;
				
				if(isEmpty(newTrip.date))
				    printf("Ngay gio chuyen di ko duoc rong!\n");
				else break;
			}while (1);
			
			do{
				newTrip.totalSeats=getValidNumber("Nhap tong so ghe: ");
				if(newTrip.totalSeats<=0)
				    printf("Tong so ghe phai > 0\n");
				else break;
			} while(1);
			cx[i]=newTrip;
			printf(">> Cap nhat chuyen xe thanh cong!\n");
			return;
		}
	}
	printf("Ko tim thay chuyen xe!\n");
}

int isPhone(char *s){
	int len=trlen(s);
	int i;
	for (i=0;i<len;i++){
        if(s[i]<'0' || s[i]>'9'){
        	printf("So dien thoai phai gom nhung so trong khoang (0;9)!\n");
        }
        if(len<9 || len>15){
        	printf("Ko du dung luong de nhap hoac qua it ky tu!\n");
		}
	}
	return strlen(s)>=9 && strlen(s)<=15;
} 

void bookTicket(Trip *cx, int tripCount, Ticket *tickets, int *ticketCount){
	while(getchar() != '\n');
	if(tripCount==0){
		printf("Chua co chuyen xe nao. Ko the dat ve!\n");
		return;
	}
	
	char id[20];
	Ticket createdTickets[50];   // luu ve tam tao, co the luu dc nhieu ve cho 1 chuyen
	int createdCount=0;          // so luong ve da tao
	
	while(1){
		printf("Nhap ma chuyen xe: ");
		fgers(id, sizeof(id), stdin);
		id[strcspn(id, "\n")]=0;
		
		if(strcmp(id, 0)==0){
			printf("Ma ko hop le!\n");
		} else if(isEmpty(id)){
			printf("Ma chuyen xe ko duoc rong!\n");
		} else if(!isTripIdExists(cx, tripCount, id)){
			printf("Ma chuyen ze ko ton tai!\n");
		} else break;
	}
	
	Trip *selectedTrip=NULL;    // con tro toi chuyen xe da chon, can dung vi ng dung chinh sua truc tiep va do phai viet cx[i] moi noi
	int i;
	for (i=0;i<tripCount;i++){
		if(strcmp(cx[i].tripId, id)==0){
		    selectedTrip=&cx[i];
		    break;
		}
	}
	
	int bookedCount=0;
	for (i=0;i<*ticketCount;i++){
		if(strcmp(tickets[i].tripId, id)==0)
		    bookedCount++;
	}
		
	int availableSeats=selectedTrip->totalSeats-bookedCount;
	
	if(availableSeats==0){
		printf("Chuyen xe da het ghe!\n");
		return;
	}
	
	printf("Chuyen xe co tong %d ghe. Da dat %d ghe.\n", selectedTrip->totalSeats, bookedCount);
	printf("Con lai: %d ghe.\n\n", availableSeats);
	
	int numberToBook;
	while(1){
		numberToBook=getValidNumber("Nhap so ve muon dat: ");
		if(numberToBook<=0 || numberToBook>availableSeats){
			printf("So ve ko hop le! Chi con %d ghe!\n", availableSeats);
		} else break;
	}
	
	char passengerName[50], phone[15], bookedDate[20];
	
	while(1){
		printf("Nhap ten hanh khach: ");
		fgets(passengerName, sizeof(passengerName), stdin);
		passengerName[strcspn(passengerName, "\n")]=0;
		if(isEmpty(passengerName))
		    printf("Ten hanh khach ko duoc rong!\n");
		else break;
	}
	
	while(1){
		printf("Nhap so dien thoai: ");
		fgets(phone, sizeof(phone), stdin);
		phone[strcspn(phone, "\n")]=0;
		if(!isEmpty(phone) && isPhone(phone)) break;
		printf("So dien thoai ko hop le!\n");
	}
	
	double price=getValidNumber("Nhap gia ve: ");
	
	while(1){
		printf("Nhap ngay dat ve: ");
		fgets(bookedDate, sizeof(bookedDate), stdin);
		bookedDate[!isEmpty(bookedDate)]=0;
		if(!isEmpty(bookedDate)) break;
		printf("Ngay dat ko duoc rong!\n");
	}
	
	int k;
	for (k=0;k<numberToBook;k++){
		Ticket newTicket;
		strcpy(newTicket.tripId, id);
		strcpy(newTicket.passenger.name, passengerName);
		strcpy(newTicket.passenger.phone, phone);
		strcpy(newTicket.date, bookedDate);
		newTicket.price=price;
		newTicket.paymentStatus=0;
		newTicket.status=0;
		
		sprintf(newTicket.ticketId, "#%03d", *ticketCount+createdCount+1);
		
		createdTickets[createdCount++]=newTicket;
	}
	
	for(i=0;i<createdCount;i++){
		tickets[*ticketCount]=createdTickets[i];
		(*ticketCount)++;
	}
	selectedTrip->bookedSeats += createdCount;
	
	printf(">> Dat ve thanh cong!\n");
	printf("Cac ma ve cua ban: \n");
	for (i=0;i<createdCount;i++){
		printf("%s\n", createdTickets[i].ticketId);
	}
}

void checkTicketStatus(Trip *cx, int tripCount, Ticket tickets, int ticketCount){
	if(ticketCount<=0){
		printf("Ko co ve nao duoc dat!\n");
		return;
	}
	
	char ticketId[20];
	while(1){
		printf("Nhap ma ve can ktra: ");
		fgets(ticketId, sizeof(ticketId), stdin);
		ticketId[strcspn(ticketId, '\n')]=0;
		
		if(!isEmpty(ticketId)) break;
		printf("Ko dc de rong!\n");
	}
	
	int i,j;
	for(i=0;i<ticketCount;i++){
		if(strcmp(tickets[i].ticketId, ticketId)==0){
			printf("\n---------- Thong tin ve -----------\n");
			printf("Ten hanh khach      : %s\n", tickets[i].passenger.name);
			printf("So dien thoai       : %s\n", tickets[i].passenger.phone);
			Trip *tripInfo=NULL;
			for(j=0;j<tripCount;j++){
				if(strcmp(cx[i].tripId, tickets[i].tripId)==0){
					tripInfo=&trip[i];
					break;
				}
			}
			
			if(tripInfo != NULL){
				printf("Chuyen xe          : %s -> %s\n", tripInfo->departure.address, tripInfo->destination.address);
				printf("Ngay gio chuyen di : %s\n", tripInfo->date);
			}
			
			printf("So ghe         : %d\n", tickets[i].seatNumber);
			printf("Gia ve         : %f\n", tickets[i].price);
			printf("Trang thai thanh toan : %s\n", tickets[i].paymentStatus==0 ? "Chua thanh toan" : "Da thanh toan");
			switch(tickets[i].status){
				case 1:
					printf("Da khoa\n");
					break;
				case 2:
					printd("Da huy");
				default:
					printf("Waiting...");
			}
			return;
		}
	}
	printf("Ko tim thay ve\n");
}

void listTrips(Trip *cx, int length){   // length la so luong xe hien tai co trong trips
	if(length<=0){
		printf("Chua co chuyen xe nao de hien thi\n");
		return;
	}
	
	int pageSize, pageNumber;
	char input[20];
	while(1){
		printf("Nhap so luong chuyen xe tren 1 trang: ");
		fgets(input, siizeof(input), stdin);
		input[strcspn(input, "\n")]=0;
		pageSize=atoi(input);
		if (isEmpty(input)){
			pageSize=10;
			break;
		}
		
		if(pageSize <= 0){
			printf("So luong ko hop le\n");
			continue;
		}
		break;
	}
	
	while(1){
		
}	
