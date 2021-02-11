#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	long int year;
	unsigned int month;
	unsigned day;
}DateOfBirth;

typedef struct {
	long long int id;
	char* name;
	char* family;
	DateOfBirth birthday;
	long long int partnerId;
	long long int motherId;
	long long int fatherId;
    int numOfChildren;
	char** childrenPtr;
}Person;

typedef struct {
	Person* residents;
	int numOfResidents;
}Db_mgr;

void print_person(Person* p);
void init_db(Db_mgr* p);
char menu();
void add_person(Db_mgr *p);
void copyStruct(Person *p1, Person *p2);
Db_mgr* increaseResidents(Db_mgr *p,int size);
void search_person(Db_mgr *p);
Person* search_id(Db_mgr *p, long long int id);
void search_parents(Db_mgr *p);
void printParents(Person* temp);
//void delete_person(Db_mgr* p);

//..........MAIN..........................//

void main() {
	
	int flag = 1;
	Db_mgr* mgr=malloc(sizeof(mgr));
	init_db(mgr);

	while (flag) {
		switch (menu()) {

		case '1': add_person(mgr);
			break;
		case '2': search_person(mgr);
			break;
		case '3': search_parents(mgr);
			break;
			//case '4': 
			//case '5':
			//case '6':
			//case '7':
		case '8': flag = 0;
			break;

		}
}
	



	for (int k = 0; k <mgr->numOfResidents; k++) {
		print_person(&mgr->residents[k]);
	}

}

//................FUNCTIONS.............//


void print_person(Person* p) {
	printf("\n");
	printf("Id: %lld\n", p->id);
	printf("First Name: %s\n", p->name);
	printf("Last Name: %s\n", p->family);
	printf("Partner Id: %lld\n", p->partnerId);
	printf("Mother Id: %lld\n", p->motherId);
	printf("Father Id: %lld\n", p->fatherId);
	printf("Number of children: %d\n", p->numOfChildren);
	if (p->numOfChildren != 0) {
		for (int j = 0; j < p->numOfChildren;j++) {
		
			printf("Children number [%d] id:", j+1);
			printf("%s\n",&(*p->childrenPtr[j]));
		}
	}
	printf("\n");
}


void init_db(Db_mgr* p) {
	int size = 0;
	do {
		printf("Enter the number of residents\n");
		scanf("%d", &size);
	} while (size <= 0);
	
	if (size > 0) {
		p->residents = (Person*)calloc(size,sizeof(Person));
		p->numOfResidents = size;
	}
	else {
		printf("The number of residents is out of the range\n");
	}
}



char menu() {
	char tav;
	int flag = 0;
	do {
		printf("Database System Menu:\n");
		printf("1. Add person\n2. Search a person\n3. Search parents\n4. Delete a person\n");
		printf("5. Get generation\n6.Print database\n7. Search by name\n8. Quit\n");
		scanf("%c", &tav);
		if (!(tav >= '1'&&tav <= '8')) {
			printf("Wrong character, Please try again\n");
			flag = 1;
		}

	} while (flag);

	return tav;
}


//..............options from the menu.......................//

//OPTION 1
void add_person(Db_mgr *p) {
	
	static int i;
	int flag = 0;
	Person *temp = (Person*)calloc(10, sizeof(Person));
	temp->name = (char*)calloc(10, sizeof(char));
	temp->family = (char*)calloc(10, sizeof(char));

	if (p->numOfResidents < i) {
		
		p = increaseResidents(p,i);
		
	}
	if (&p->residents[0].id==0) {
		i = 0;
	}

	do {
		printf("Enter Id:\n");
		scanf("%lld", &p->residents[i].id);
		if (p->residents[i].id < 0) {
			printf("This id is out of range(positive numbers only)\n");
			flag = 1;
		}
	} while (flag);

	p->residents[i].name = (char*)malloc(10*sizeof(char));
	p->residents[i].family = (char*)malloc(10*sizeof(char));

	if (p->residents[i].name == NULL || p->residents[i].family == NULL) {
		printf("ERROR..allocate memory went wrong\n");
	}

	printf("Enter first name:\n");
	fgets(p->residents[i].name,10*sizeof(p->residents[i].name),stdin);
	fgets(p->residents[i].name, 10 * sizeof(p->residents[i].name), stdin);

	printf("Enter last name:\n");
	fgets(p->residents[i].family, 10 * sizeof(p->residents[i].family), stdin);


	do {
		flag = 0;
		printf("Enter date of birth:\n");
		printf("Day:\n");
		scanf("%d", &p->residents[i].birthday.day);
		printf("Month:\n");
		scanf("%d", &p->residents[i].birthday.month);
		printf("Year:\n");
		scanf("%ld", &p->residents[i].birthday.year);

		if (p->residents[i].birthday.day > 31 || p->residents[i].birthday.day < 1) {
			printf("Day is out of the range(1-31)\n");
			flag = 1;
		}
		else if (p->residents[i].birthday.month > 12 || p->residents[i].birthday.month < 1) {
			printf("Month is out of the range(1-12)\n");

			flag = 1;
		}
		else if (p->residents[i].birthday.year < 1920||p->residents[i].birthday.year>2020) {
			printf("Year is out of the range(1920-2020)\n");
			flag = 1;
		}
	} while (flag);

	printf("Enter partner id:\n");
	scanf("%lld",&p->residents[i].partnerId);
	printf("Enter mother id:\n");
	scanf("%lld", &p->residents[i].motherId);
	printf("Enter father id:\n");
	scanf("%lld", &p->residents[i].fatherId);
	printf("Enter number of children:\n");
	scanf("%d", &p->residents[i].numOfChildren);

	if (p->residents[i].numOfChildren > 0) {
		temp->childrenPtr = (char**)calloc(p->residents[i].numOfChildren, sizeof(char));
		p->residents[i].childrenPtr = (char**)malloc((p->residents[i].numOfChildren)*sizeof(char));
		for (int j=0; j < p->residents[i].numOfChildren;j++) {
			p->residents[i].childrenPtr[j] = (char*)malloc(10*sizeof(char));

			printf("Enter id of child number [%d]\n", j + 1);
			scanf("%s",&(*p->residents[i].childrenPtr[j]));

		}
	}





	 ////////////// order persons///////////////////
	for (int index = 0; index <= i; index++) {
		for (int j = index + 1; j <= i; j++) {

			if (p->residents[index].id > p->residents[j].id) {
				copyStruct(temp, &p->residents[j]);
				copyStruct(&p->residents[j], &p->residents[index]);
				copyStruct(&p->residents[index], temp);


			}

		}

	}
	i++;

	free(temp);




}



//OPTION 2
void search_person(Db_mgr *p) {
	long long int temp;
	char choise;
	Person *temp2=malloc(sizeof(Person));
	printf("Enter the ID of the person you want to find\n");
	scanf("%lld",&temp);
	temp2=search_id(p, temp);
	if (temp2 == NULL) {
		printf("Coudn't find the given id\n");
	}

	else { 
		printf("1.print all data\n2.print the parent's details\n");
		choise=getchar();
		choise = getchar();

		switch (choise) {
		case '1': print_person(temp2);
			break;
		case '2': 
			printParents(temp2);
				break;
		}

	}

} 

//OPTION 3
void search_parents(Db_mgr *p) {
	
	search_person(p);

}

//OPTION 4

//void delete_person(Db_mgr* p) {
//	long long int temp;
//	printf("Enter the ID of the person you want to delete\n");
//	scanf("%lld", &temp);
//
//	if (search_Id(temp) == NULL) {
//		printf("Coudn't find the given id\n");
//	}
//	else {
//
//	}
//
//}



//..............EXTRA FUNCTIONS.......................//


void copyStruct(Person *src, Person *dest) {
	src->id = dest->id;
	strcpy(src->name, dest->name);
	strcpy(src->family, dest->family);
	src->partnerId = dest->partnerId;
	src->motherId = dest->motherId;
	src->fatherId = dest->fatherId;
	src->birthday.day = dest->birthday.day;
	src->birthday.month = dest->birthday.month;
	src->birthday.year = dest->birthday.year;
	src->numOfChildren = dest->numOfChildren;
	for (int j = 0; j < dest->numOfChildren; j++) {

		src->childrenPtr[j] = (char*)malloc(10 * sizeof(char));

		strcpy(src->childrenPtr[j], dest->childrenPtr[j]);

	}

}

Db_mgr* increaseResidents(Db_mgr *p, int size) {
	Db_mgr* temp = malloc(sizeof(temp));
	temp->residents = (Person*)calloc(size, sizeof(Person));

	for (int j = 0; j < size; j++) {
		copyStruct(&temp->residents[j], &p->residents[j]);
	}
	p->residents = (Person*)calloc(size, sizeof(Person));
	return temp;
}

Person* search_id(Db_mgr *p, long long int id) {
	
	for (int j = 0; j < p->numOfResidents; j++) {
		if (p->residents[j].id == id) {
			return &p->residents[j];
		}
	}
	return NULL;
}

void printParents(Person* temp) {
	if (temp->motherId != 0 && temp->fatherId != 0) {
		printf("Mother ID: %lld  Father ID: %lld\n", temp->motherId, temp->fatherId);
	}
	else if (temp->motherId != 0 && temp->fatherId == 0) {

		printf("Mother ID: %lld  \n", temp->motherId);


	}

	else if (temp->motherId == 0 && temp->fatherId != 0) {
		printf("Father ID: %lld  \n", temp->fatherId);

	}
	else {
		printf("There's no parents\n");
	}
}