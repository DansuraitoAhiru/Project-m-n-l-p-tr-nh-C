#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
void checkTicketStatus(Trip *trips, int tripCount, Ticket *tickets, int ticketCount);
void listTrips(Trip *trips, int length);
void payTicket(Ticket *tickets, int ticketCount);
void manageTicketsStatus(Trip *cx, int tripCount, Ticket *tickets, int ticketCount);
void tripReport(Trip *cx, int tripCount, Ticket *tickets, int ticketCount);

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
				else checkTicketStatus(cx, length, tickets, ticketCount);
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

int isEmpty(const char *str) {   
    if (!str) return 1;                                                    // Neu con tro NULL (ko co gt de su dung), coi nhu rong, tra ve 1
    while (*str) {
        if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
            return 0;                                                     // Co ky tu khong phai khoang trang -> khong rong -> tra ve 0
        str++;                                                            // Di chuyen con tro sang ky tu tiep theo trong chuoi
    }
    return 1;                                                             // Neu vong lap ket thuc ko thay ky tu nao khac khoang trang->rong->tra ve 1
}

int isTripIdExists(Trip *trips, int length, char *id) {                   // ham ktra xem ma co ton tai hay co bi trung ko
	int i;
    for (i = 0; i < length; i++) {
        if (strcmp(trips[i].tripId, id) == 0)
            return 1;                                                     // 1 la id da ton tai
    }
    return 0;                                                             // 0 la id chua ton tai
}

double getValidNumber(const char *msg) {                                   //const char de co dinh chuoi, ko thay doi dc
	char buffer[50];
    double value;
    int i;

    while (1) {
        printf("%s", msg);  // msg la chuoi de hien thi nhu Nhap so:, Nhap gi do:...
        fgets(buffer, sizeof(buffer), stdin);  // buffer moi la chuoi de xet
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            printf("Ko duoc de rong!\n");
            continue;
        }
        if (buffer[0] == '\0') {
            printf("Ban chua nhap gi! Vui long nhap so!\n");
            continue;
        }
        int valid=1;
        for (i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] < '0' || buffer[i] > '9') { // không phai so -> sai, '0' (mã ASCII 48)  ->  '9' (mã ASCII 57)
                valid=0;                                   // ngoai khoang nay deu la ky tu dac biet, chu
                break;
            }
        }

        if (!valid) {  // <-- quay lai dau while thi valid quay lai = 1
            printf("Xin hay nhap lai so!\n");
            continue;
        }
        value = atof(buffer);   // doi chuoi sang double
        return value;
    }
}

void addInfoTrip(Trip *cx, int *length) {
	int i;
	int size = getValidNumber("Nhap so luong chuyen xe: ");
	for(i=0;i<size;i++){
	    Trip newTrip;    //tao struct moi de tránh làm hong du lieu neu nguoi dung nhap sai
	    do {
	        printf("Nhap ma chuyen xe: ");
	        fgets(newTrip.tripId, sizeof(newTrip.tripId), stdin);
	        newTrip.tripId[strcspn(newTrip.tripId, "\n")] = 0;
	        if (isEmpty(newTrip.tripId)) {
	            printf("Ma chuyen xe ko duoc rong!\n");
	        } else if (isTripIdExists(cx, *length, newTrip.tripId)) {     // ktra id ton tai hay chua?
	            printf("Ma chuyen xe da ton tai!\n");
	        } else {
	            break;
	        }
	    } while (1);
	
	    do {
	        printf("Nhap ten diem di: ");
	        fgets(newTrip.departure.name, sizeof(newTrip.departure.name), stdin);
	        newTrip.departure.name[strcspn(newTrip.departure.name, "\n")] = 0;
	
	        if (isEmpty(newTrip.departure.name))
	            printf("Ten diem di ko duoc rong!\n");
	        else break;
	    } while (1);
	
	    do {
			printf("Nhap dia chi diem di: ");
		    fgets(newTrip.departure.address, sizeof(newTrip.departure.address), stdin);
		    newTrip.departure.address[strcspn(newTrip.departure.address, "\n")] = 0;
		    
		    if (isEmpty(newTrip.departure.address))
	            printf("Dia chi diem di ko duoc rong!\n");
	        else break;
	    } while (1);
	
	    do {
	        printf("Nhap ten diem den: ");
	        fgets(newTrip.destination.name, sizeof(newTrip.destination.name), stdin);
	        newTrip.destination.name[strcspn(newTrip.destination.name, "\n")] = 0;
	
	        if (isEmpty(newTrip.destination.name))
	            printf("Ten diem den ko duoc rong!\n");
	        else break;
	    } while (1);
	    
	    do {
		    printf("Nhap dia chi diem den: ");
		    fgets(newTrip.destination.address, sizeof(newTrip.destination.address), stdin);
		    newTrip.destination.address[strcspn(newTrip.destination.address, "\n")] = 0;
		    
		    if(isEmpty(newTrip.destination.address))
		        printf("Dia chi diem den ko duoc rong!\n");
		    else break;
		} while (1);
	
	    do {
	        printf("Nhap ngay gio chuyen di: ");
	        fgets(newTrip.date, sizeof(newTrip.date), stdin);
	        newTrip.date[strcspn(newTrip.date, "\n")] = 0;
	
	        if (isEmpty(newTrip.date))
	            printf("Ngay gio ko duoc rong!\n");
	        else break;
	    } while (1);
	
	    do {
	        newTrip.totalSeats = getValidNumber("Nhap tong so ghe: ");
	        if (newTrip.totalSeats <= 0) {
	            printf("Tong so ghe phai > 0\n");
	        } else {
	            break;
	        }
	    } while (1);
	    newTrip.bookedSeats = 0;
	    cx[*length] = newTrip;    // them phan tu moi vao cuoi
	    (*length)++;
	    printf("Them chuyen xe thanh cong!\n");
	}
}

void updateTrip(Trip *cx, int length){
    char id[20];
    printf("Nhap ma chuyen xe can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    
    int i;
    for(i=0;i<length;i++){
		if(strcmp(cx[i].tripId, id)==0){
			printf("\n--- Cap nhat thong tin chuyen xe ID %s ---\n", cx[i].tripId);
		    Trip newTrip;
		    strcpy(newTrip.tripId, cx[i].tripId);    // copy tripId cua cx hien tai vao struct luu tru moi
		    do {
		        printf("Nhap ten diem di moi: ");
		        fgets(newTrip.departure.name, sizeof(newTrip.departure.name), stdin);
		        newTrip.departure.name[strcspn(newTrip.departure.name, "\n")] = 0;
		
		        if (isEmpty(newTrip.departure.name))
		            printf("Dia chi diem di khong duoc rong!\n");
		        else break;
		    } while (1);
		
		    do {
				printf("Nhap dia chi diem di: ");
			    fgets(newTrip.departure.address, sizeof(newTrip.departure.address), stdin);
			    newTrip.departure.address[strcspn(newTrip.departure.address, "\n")] = 0;
			    
			     if (isEmpty(newTrip.departure.address))
		            printf("Ten diem di khong duoc rong!\n");
		        else break;
		    } while (1);
		
		    do {
		        printf("Nhap ten diem den moi: ");
		        fgets(newTrip.destination.name, sizeof(newTrip.destination.name), stdin);
		        newTrip.destination.name[strcspn(newTrip.destination.name, "\n")] = 0;
		
		        if (isEmpty(newTrip.destination.name))
		            printf("Ten diem den ko duoc rong!\n");
		        else break;
		    } while (1);
		
		    do {
			    printf("Nhap dia chi diem den: ");
			    fgets(newTrip.destination.address, sizeof(newTrip.destination.address), stdin);
			    newTrip.destination.address[strcspn(newTrip.destination.address, "\n")] = 0;
			    
			    if(isEmpty(newTrip.destination.address))
			        printf("Dia chi diem den ko duoc rong!\n");
			    else break;
			} while (1);
		
		    do {
		        printf("Nhap ngay gio chuyen di moi: ");
		        fgets(newTrip.date, sizeof(newTrip.date), stdin);
		        newTrip.date[strcspn(newTrip.date, "\n")] = 0;
		
		        if (isEmpty(newTrip.date))
		            printf("Ngay gio ko duoc rong!\n");
		        else break;
		    } while (1);
		
		    do {
		        newTrip.totalSeats = getValidNumber("Nhap tong so ghe: ");
		        if (newTrip.totalSeats <= 0) {
		            printf("Tong so ghe phai > 0\n");
		        } else {
		            break;
		        }
		    } while (1);
		    cx[i] = newTrip;  // i la chuyen xe da ton tai trong mang, day la chinh sua phan tu cu chu ko phai them phan tu
            printf(">> Cap nhat chuyen xe thanh cong!\n");
            return;
        }
    }
	printf("Ko tim thay chuyen xe!\n");
}

int isPhone(char *s) {
	int len = strlen(s);
	int i;
    for (i = 0; i<len ; i++) {
        if (s[i] < '0' || s[i] > '9'){
        	printf("So dien thoai phai co nhung so trong khoang (0;9)!\n");
        	return 0;
        }
        if (len < 9 || len > 15){
        	printf("Ko du dung luong de nhap hoac qua it ky tu!\n");
        }
    }
    return strlen(s) >= 9 && strlen(s) <= 15;  //ktra do dai hop le, neu 9-15 thi tra ve 1, ko thi tra ve 0
}

void bookTicket(Trip *trips, int tripCount, Ticket *tickets, int *ticketCount) {
    if (tripCount == 0) {
        printf("Chua co chuyen xe nao. Ko the dat ve!\n");
        return;
    }
    char tripId[20];
    Ticket createdTickets[50];  // luu ve tam tao, co the luu dc nhieu ve cho 1 chuyen
    int createdCount = 0;       // so luong ve da tao

    while (1) {
        printf("Nhap ma chuyen xe: ");
        fgets(tripId, sizeof(tripId), stdin);
        tripId[strcspn(tripId, "\n")] = 0;

        if(strcmp(tripId, "0") == 0){
        	printf("Ma ko hop le!\n");
        } else if (isEmpty(tripId)) {
            printf("Ma chuyen xe ko duoc rong!\n");
        } else if (!isTripIdExists(trips, tripCount, tripId)) {
            printf("Ma chuyen xe ko ton tai!\n");
        } else break;
    }

    Trip *selectedTrip = NULL;   // con tro toi chuyen xe da chon, can dung vi ng dung chinh sua truc tiep va do phai viet cx[i] moi noi
    int i;
    for (i = 0; i < tripCount; i++) {
        if (strcmp(trips[i].tripId, tripId) == 0) {
            selectedTrip = &trips[i];
            break;
        }
    }

    int bookedCount = 0;
    for (i = 0; i < *ticketCount; i++) {
        if (strcmp(tickets[i].tripId, tripId) == 0)
            bookedCount++;
    }

    int availableSeats = selectedTrip->totalSeats - bookedCount;

    if (availableSeats == 0) {
        printf("Chuyen xe da het ghe!\n");
        return;   // giup thoat ham luon, ko chay phan code con lai
    }

    printf("Chuyen xe nay co tong %d ghe. Da dat %d ghe.\n", selectedTrip->totalSeats, bookedCount);
    printf("Con lai: %d ghe.\n\n", availableSeats);

    int numberToBook;
    while (1) {
        numberToBook = getValidNumber("Nhap so ve muon dat: ");
        if (numberToBook == 0) {   // neu nhap 0 thi thoát hàm
	        printf("Huy dat ve. Thoat!\n");
	        return;
	    }
        if (numberToBook <= 0 || numberToBook > availableSeats) {
            printf("So ve ko hop le! Chi con %d ghe.\n", availableSeats);
        } else break;
    }

    char passengerName[50], phone[15], bookingDate[20];

    while (1) {
        printf("Nhap ten hanh khach: ");
        fgets(passengerName, sizeof(passengerName), stdin);
        passengerName[strcspn(passengerName, "\n")] = 0;
        if (isEmpty(passengerName))
            printf("Ten hanh khach ko duoc rong!\n");
        else break;
    }

    while (1) {
        printf("Nhap so dien thoai: ");
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = 0;
        if (!isEmpty(phone) && isPhone(phone)) break;
        printf("So dien thoai ko hop le!\n");
    }

    double price = getValidNumber("Nhap gia ve: ");

    while (1) {
        printf("Nhap ngay dat ve: ");
        fgets(bookingDate, sizeof(bookingDate), stdin);
        bookingDate[strcspn(bookingDate, "\n")] = 0;
        if (!isEmpty(bookingDate)) break;
        printf("Ngay dat ko duoc rong!\n");
    }

    int k;
	for (k = 0; k < numberToBook; k++) {
        Ticket newTicket;
        strcpy(newTicket.tripId, tripId);
        strcpy(newTicket.passenger.name, passengerName);
        strcpy(newTicket.passenger.phone, phone);
        strcpy(newTicket.date, bookingDate);
        newTicket.price = price;
        newTicket.paymentStatus = 0;
        newTicket.status = 0;

        sprintf(newTicket.ticketId, "#%03d", *ticketCount + createdCount + 1);   //sprintf ghi du lieu vào 1 chuoi ký tu theo dinh dang, giong printf nhung không in ra màn hình
	
        createdTickets[createdCount++] = newTicket;                             //*ticketCount: so ve da có truoc dó, createdCount: so vé dã tao trong lan dat hien tai
    }                                                                           //+1 la de bat dau tu 1 va de nhay sang so tiep theo

    for (i = 0; i < createdCount; i++) {
        tickets[*ticketCount] = createdTickets[i];  //Chuyen ve tu mang tam createdTickets[] sang mang tong danh sach ve tickets[]
        (*ticketCount)++;
    }
    selectedTrip->bookedSeats += createdCount;

    printf(">> Dat ve thanh cong!\n");
    printf("Cac ma ve cua ban:\n");

    for (i = 0; i < createdCount; i++) {
        printf("%s\n", createdTickets[i].ticketId);
    }
}

void checkTicketStatus(Trip *trips, int tripCount, Ticket *tickets, int ticketCount) {
	while(getchar () != '\n');
    if (ticketCount == 0) {
        printf("Chua co ve nao duoc dat!\n");
        return;
    }
    
    char ticketId[20];
    while(1){
	    printf("Nhap ma ve can kiem tra: ");
	    fgets(ticketId, sizeof(ticketId), stdin);
	    ticketId[strcspn(ticketId, "\n")] = 0;
		if (!isEmpty(ticketId)) break;
		printf("Ma ve khong duoc de trong!\n");
	}

    int i,j;
	for (i = 0; i < ticketCount; i++) {
	    if (strcmp(tickets[i].ticketId, ticketId) == 0) {
            printf("\n--------------- Thong tin ve ---------------\n");
            printf("Ten hanh khach     : %s\n", tickets[i].passenger.name);
            printf("So dien thoai      : %s\n", tickets[i].passenger.phone);
            Trip *tripInfo = NULL;   // ve luu trong tripId nma chuyen xe lai luu o noi khac
            for (j = 0; j < tripCount; j++) {
                if (strcmp(trips[j].tripId, tickets[i].tripId) == 0) {
                    tripInfo = &trips[j];
                    break;
                }
            }

            if (tripInfo != NULL) {
                printf("Chuyen xe          : %s -> %s\n", tripInfo->departure.name, tripInfo->destination.name);
                printf("Ngay gio chuyen di : %s\n", tripInfo->date);
            }

            printf("So ghe             : %d\n", tickets[i].seatNumber);
            printf("Gia ve             : %.0f\n", tickets[i].price);
            printf("Trang thai thanh toan : %s\n", tickets[i].paymentStatus == 0 ? "Chua thanh toan" : "Da thanh toan");
            switch (tickets[i].status) {
			    case 1:
			        printf("Da khoa\n");
			        break;
			    case 2:
			        printf("Da huy\n");
			        break;
			    default:
			        printf("Waiting...\n");
			}
			return;
        }
    }
    printf("Ko tim thay ve!\n");
}

void listTrips(Trip *trips, int length) {
    if (length <= 0) {
        printf("Ko co chuyen xe nao de hien thi!\n");
        return;
    }

    int pageSize, pageNumber;
    char input[20];

    while (1) {
        printf("Nhap so luong chuyen xe tren 1 trang: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        pageSize = atoi(input);            //atoi de chuyen chuoi (char) thanh so (int)
        if (isEmpty(input)) {
            pageSize=10;
            break;
        }
        
        if (pageSize <= 0) {
            printf("So luong ko hop le!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Nhap trang muon xem: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        pageNumber = atoi(input);
        if (isEmpty(input)) {
            pageNumber=1;
            break;
        }

        if (pageNumber <= 0) {
            printf("So trang ko hop le!\n");
            continue;
        }
        break;
    }

    int totalPages = (length + pageSize - 1) / pageSize;

    if (pageNumber > totalPages) {
        printf("So trang ko hop le! Chi co %d trang.\n", totalPages);
        return;
    }

    int startIndex = (pageNumber - 1) * pageSize;
    int endIndex = startIndex + pageSize;
    if (endIndex > length) endIndex = length;

    printf("\n============================================ Danh sach chuyen xe (Trang %d/%d) ===========================================\n", pageNumber, totalPages);
    printf("| %-5s | %-20s | %-20s | %-16s | %-10s |\n", "ID", "Diem Di", "Diem Den", "Ngay Gio", "Ghe (da dat/tong so ghe)");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    int i;
	for (i = startIndex; i < endIndex; i++) {
        printf("| %-5s | %-20s | %-20s | %-15s |      %3d/%-6d   |\n",
               trips[i].tripId,
               trips[i].departure.name,
               trips[i].destination.name,
               trips[i].date,
               trips[i].bookedSeats,
               trips[i].totalSeats);
    }

    printf("------------------------------------------------------------------------------------------------------------------------\n");

    while (1) {
        printf("Nhap 'n' de xem trang tiep theo, 'p' de xem trang truoc, 'q' de thoat: ");
        fgets(input, sizeof(input), stdin);

        if (isEmpty(input)) {
            printf("Ko duoc de trong!\n");
            continue;
        }
		if (input[0] == 'q' || input[0] == 'Q') break;
        else if (input[0] == 'n' || input[0] == 'N') {
            if (pageNumber < totalPages) pageNumber++;
            else {
                printf("Da o trang cuoi cung.\n");
                continue;
            }
        }
        else if (input[0] == 'p' || input[0] == 'P') {
            if (pageNumber > 1) pageNumber--;
            else {
                printf("Da o trang dau tien.\n");
                continue;
            }
        } else {
        	printf("Ng dung chi co the nhap 3 ky tu p/q/n thoi!\n");
        }

        startIndex = (pageNumber - 1) * pageSize;
        endIndex = startIndex + pageSize;
        if (endIndex > length) endIndex = length;

        printf("\n============================================ Danh sach chuyen xe (Trang %d/%d) ===========================================\n", pageNumber, totalPages);
	    printf("| %-5s | %-20s | %-20s | %-16s | %-10s |\n", "ID", "Diem Di", "Diem Den", "Ngay Gio", "Ghe (da dat/tong so ghe)");
	    printf("------------------------------------------------------------------------------------------------------------------------\n");

        for (i = startIndex; i < endIndex; i++) {
            printf("| %-5s | %-20s | %-20s | %-15s |      %3d/%-6d   |\n",
                   trips[i].tripId,
                   trips[i].departure.name,
                   trips[i].destination.name,
                   trips[i].date,
                   trips[i].bookedSeats,
                   trips[i].totalSeats);
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n");
    }
}

void payTicket(Ticket *tickets, int ticketCount) {
    if (ticketCount == 0) {
        printf("Chua co ve nao trong he thong!\n");
        return;
    }

    char id[20];

    while (1) {  
        printf("Nhap ma ve can thanh toan: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;

        if (isEmpty(id)) {
            printf("Ma ve ko duoc de trong!\n");
        } else break;
    }

    int index = -1; //tai vi chuoi tinh tu 0 nen co the ton tai ve 0
    int i;
    for (i= 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].ticketId, id) == 0) {
            index = i;  //tim thay thi se luu lai vi tri cua i
            break;
        }
    }

    if (index == -1) {
        printf("Ko tim thay ve!\n");
        return;
    }

    Ticket *t = &tickets[index];

    if (t->status == 1 || t->status == 2) {   //1=Locked, 2=Cancelled
        printf("Ve ko the thanh toan vi da bi vo hieu hoa!\n");
        return;
    }

    if (t->paymentStatus == 1) {
        printf("Ve da thanh toan truoc do!\n");
        return;
    }

    t->paymentStatus = 1;
    printf("Thanh toan thanh cong!\n");
}

void manageTicketsStatus(Trip *cx, int tripCount, Ticket *tickets, int ticketCount){
	if (ticketCount == 0) {
        printf("Chua co ve nao duoc dat!\n");
        return;
    }
	char ticketId[20];
	while(1) {
		printf("Nhap ma ve: ");
		fgets(ticketId, sizeof(ticketId), stdin);
		ticketId[strcspn(ticketId, "\n")]=0;
		
		if(isEmpty(ticketId)){
			printf("Ma ve ko duoc de trong!\n");
			continue;
		}
		break;
	}
	
	Ticket *t = NULL;
	int i;
	for(i=0; i<ticketCount; i++){
		if(strcmp(tickets[i].ticketId, ticketId) == 0){
			t = &tickets[i];
			break;
		}
	}
	
	if(!t){
		printf("Ko tim thay ve!\n");
		return;
	}
	
	if(t->status == 1 || t->status == 2){     //1=locked, 2=cancelled
		printf("Ve da bi vo hieu hoa. Ko the thao tac!\n");
		return;
	}
	
	printf("Chon hanh dong: \n");
	printf("1. Khoa ve\n");
	printf("2. Huy ve\n");
	int action=getValidNumber("Nhap lua chon: ");
	
	if(action == 1){
		t->status = 1;
		printf("Khoa ve thanh cong!\n");
		return;
	}
	
	else if(action == 2){
	    if(t->paymentStatus == 1){
		   printf("Ko the huy ve vi ve da thanh toan!\n");
		   return;
		}	
		for (i=0; i < tripCount; i++){
			if(strcmp(cx[i].tripId, t->tripId) == 0){
				if(cx[i].bookedSeats > 0)
				   cx[i].bookedSeats--;
				break;
			}
		}
		
		t->status = 2;
		printf("Huy ve thanh cong!\n");
		return;
	}
	
	else{
		printf("Lua chon ko hop le!\n");
	}
}

void tripReport(Trip *cx, int tripCount, Ticket *tickets, int ticketCount){
	int i,j;
	if(ticketCount == 0){
		printf("Chua co du lieu de thong ke, bao cao!\n");
		return;
	}
	printf("1. Bao cao doanh thu\n");
	printf("2. Bao cao theo chuyen xe\n");
	printf("3. Bao cao theo thoi gian\n");
	int type = getValidNumber("Lua chon cua ban: ");
	
	if(type == 1){
		long long revenue = 0;
		int paidTickets = 0;
		for(i=0; i < ticketCount; i++){
			if(tickets[i].paymentStatus == 1){
				revenue += tickets[i].price;
				paidTickets++;
			}
		}
		printf("Tong doanh thu: %lld Vnd\n", revenue);
		printf("Tong ve da thanh toan: %d\n", paidTickets);
	} 
	
	else if(type == 2){
		printf("\n=================================== Bang bao cao theo chuyen xe =========================================\n");
		printf("| %-5s | %-10s | %-10s | %-10s | %-10s | %-10s |\n", 
		        "ID", "Tong ve", "Da thanh toan", "Huy", "Con hieu luc", "Doanh thu");
		printf("-----------------------------------------------------------------------------------------------------------\n");
		for(i=0; i < tripCount; i++){
			int total=0, paid=0, cancelled=0, valid=0;
			long long revenue=0;
			for(j=0; j<ticketCount; j++){
				if(strcmp(tickets[j].tripId, cx[i].tripId) == 0){
					total++;
					if(tickets[j].status == 2){
					    cancelled++;
					} else if(tickets[j].status == 0){
						valid++;
					}
					if(tickets[j].paymentStatus == 1){
						paid++;
						revenue += tickets[j].price;
					}
				}
			}
		    printf("| %-5s | %-10d | %-10d | %-10d | %-10d | %-10lld |\n",
		        cx[i].tripId, total, paid, cancelled, valid, revenue);
		    }
		    
	} else if(type == 3){
		char fromDate[20], toDate[20];
        printf("Nhap ngay bat dau (dd/mm/yy) hoac de trong: ");
        fgets(fromDate,sizeof(fromDate),stdin);
        fromDate[strcspn(fromDate,"\n")]=0;
        printf("Nhap ngay ket thuc (dd/mm/yy) hoac de trong: ");
        fgets(toDate,sizeof(toDate),stdin);
        toDate[strcspn(toDate,"\n")]=0;

        int total=0, paid=0, cancelled=0, valid=0;
        long long revenue=0;
        for(i=0;i<ticketCount;i++){
            int inRange=1;
            if(!isEmpty(fromDate) && strcmp(tickets[i].date,fromDate)<0) inRange=0;
            if(!isEmpty(toDate) && strcmp(tickets[i].date,toDate)>0) inRange=0;
            if(!inRange) continue;

            total++;
            if(tickets[i].paymentStatus==1) revenue += tickets[i].price;
            if(tickets[i].paymentStatus==1) paid++;
            if(tickets[i].status==2) cancelled++;
            if(tickets[i].status==0) valid++;
        }

        printf("\n--- Bao cao theo khoang thoi gian ---\n");
        printf("Tong ve trong khoang thoi gian : %d\n", total);
        printf("Tong doanh thu                 : %lld VND\n", revenue);
        printf("So ve huy                      : %d\n", cancelled);
        printf("So ve con hieu luc             : %d\n", valid);
    
	} else {
		printf("Ko phai lua chon hop le!\n");
    }
}	

