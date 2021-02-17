#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARR_SIZE1 10
#define ARR_SIZE2 20

typedef struct {
	unsigned int year;
	unsigned int month;
	unsigned int day;
}DateOfBirth;

typedef struct {
	unsigned long int id;
	char* name;
	char* family;
	DateOfBirth birthday;
	unsigned long int partnerId;
	unsigned long int motherId;
	unsigned long int fatherId;
    int numOfChildren;
	char** childrenPtr;
}Person;

typedef struct {
	Person* residents;
	int numOfResidents;
	int countofresident;
}Db_mgr;

void print_person(const Person* p);
void init_db(Db_mgr* p);
char menu();
void add_person(Db_mgr *p);
void copyStruct(Person *p1, Person *p2);
void ChangeResidents(Db_mgr* p, int size);
void search_person(Db_mgr *p);
Person* search_id(Db_mgr *p, unsigned long int id);
void search_parents(Db_mgr *p);
void printParents(Person* temp);
unsigned long int HasMother(Db_mgr* p, Person* id);
unsigned long int HasFather(Db_mgr* p, Person* id);
void UpdateKids(Db_mgr* p, Person* id);
void UpdatePartnerID(Db_mgr* p, unsigned long int id);
void search_by_name(Db_mgr* p);
void print_db(Db_mgr* p);
void printBirthday(Person* p);
void EraseKidsID(Db_mgr* db, Person* p, unsigned long int id);
void EraseFatherID(Person* p);
void EraseMotherID(Person* p);
char* ConvertIDtoChar(unsigned long int id);
void OrderByAscID(Db_mgr* db);
void delete_person(Db_mgr* p);
int get_gen(Db_mgr* db);
int hasKids(Person* p);
void quit(Db_mgr* db);
//..........MAIN..........................//

void main() {

	int flag = 1;
	Db_mgr* mgr = malloc(sizeof(mgr));
	init_db(mgr);
	while (flag) {
		switch (menu()) {

		case '1': add_person(mgr);
			break;
		case '2': search_person(mgr);
			break;
		case '3': search_parents(mgr);
			break;
		case '4': delete_person(mgr);
			break;
		case '5': get_gen(mgr);
			break;
		case '6': print_db(mgr);
			break;
		case '7': search_by_name(mgr);
			break;
		case '8': quit(mgr);
			flag = 0;
		}
	}
}


//................FUNCTIONS.............//

//הפונקציה מקבלת מצביע למבנה מסוג בן אדם ומדפיסה את פרטיו
void print_person(const Person* p) {
	printf("\n");
	printf("Id: %lu\n", p->id);
	printf("First Name: %s\n", p->name);
	printf("Last Name: %s\n", p->family);
	printBirthday(p);
	printf("Partner Id: %lu\n", p->partnerId);
	printf("Mother Id: %lu\n", p->motherId);
	printf("Father Id: %lu\n", p->fatherId);
	printf("Number of children: %d\n", p->numOfChildren);
	if (p->numOfChildren != 0) {
		for (int j = 0; j < p->numOfChildren;j++) {
		
			printf("Children number [%d] id:", j+1);
			printf("%s\n",&(*p->childrenPtr[j]));
		}
	}
	printf("\n");
}

//הפונקציה מקבלת מצביע למבנה מנהל, מקבלת את מספר התושבים מהמשתמש ומקצה זיכרון למערך התושבים בהתאם
void init_db(Db_mgr* p) {
	p->countofresident = 0;
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


//פונקציה אשר מדפיסה תפריט, מקבלת מהמשתמש את התו שמסמל את מספר הפעולה שברצונו לממש, ומחזירה את אותו תו
char menu() {
	char tav;
	int flag = 0;
	do {
		printf("Database System Menu:\n");
		printf("1. Add person\n2. Search a person\n3. Search parents\n4. Delete a person\n");
		printf("5. Get generation\n6.Print database\n7. Search by name\n8. Quit\n");
		fseek(stdin, 0, SEEK_END);

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
//פונקציה אשר מקבלת מצביע למבנה מנהל, ומוסיפה תושב למערך, ומגדילה את המערך בהתאם
void add_person(Db_mgr* p) {
	int x = p->countofresident;
	int flag = 0;
	if (p->numOfResidents < x) {

	ChangeResidents(p, p->countofresident);
	}
	do {
		printf("Enter ID:\n");
		scanf("%lu", &p->residents[x].id);
		if (p->residents[x].id < 0) {
			printf("Please provide a valid ID (positive numbers only)\n");
			flag = 1;
		}
	} while (flag);

	p->residents[x].name = (char*)malloc(ARR_SIZE1 * sizeof(char));
	p->residents[x].family = (char*)malloc(ARR_SIZE1 * sizeof(char));

	if (p->residents[x].name == NULL || p->residents[x].family == NULL) {
		printf("ERROR... couldn't allocate memory\n");
	}

	printf("Enter first name: \n");
	fgets(p->residents[x].name, ARR_SIZE1 * sizeof(p->residents[x].name), stdin);
	fgets(p->residents[x].name, ARR_SIZE1 * sizeof(p->residents[x].name), stdin);

	printf("Enter last name: \n");
	fgets(p->residents[x].family, ARR_SIZE1 * sizeof(p->residents[x].family), stdin);


	do {
		flag = 0;
		printf("Enter date of birth: \n");
		printf("Day: \n");
		scanf("%d", &p->residents[x].birthday.day);
		printf("Month: \n");
		scanf("%d", &p->residents[x].birthday.month);
		printf("Year: \n");
		scanf("%u", &p->residents[x].birthday.year);

		if (p->residents[x].birthday.day > 31 || p->residents[x].birthday.day < 1) {
			printf("Day is out of the range(1-31)\n");
			flag = 1;
		}
		else if (p->residents[x].birthday.month > 12 || p->residents[x].birthday.month < 1) {
			printf("Month is out of the range(1-12)\n");

			flag = 1;
		}
		else if (p->residents[x].birthday.year < 1920 || p->residents[x].birthday.year>2020) {
			printf("Year is out of the range(1920-2020)\n");
			flag = 1;
		}
	} while (flag);

	printf("Enter partner id:\n");
	scanf("%lu", &p->residents[x].partnerId);
	printf("Enter mother id:\n");
	scanf("%lu", &p->residents[x].motherId);
	printf("Enter father id:\n");
	scanf("%lu", &p->residents[x].fatherId);
	printf("Enter number of children:\n");
	scanf("%d", &p->residents[x].numOfChildren);

	if (p->residents[x].numOfChildren > 0) {
		p->residents[x].childrenPtr = (char**)malloc((p->residents[x].numOfChildren) * sizeof(char));
		for (int j = 0; j < p->residents[x].numOfChildren; j++) {
			p->residents[x].childrenPtr[j] = (char*)malloc(ARR_SIZE1 * sizeof(char));

			printf("Enter id of child number [%d]\n", j + 1);
			scanf("%s", &(*p->residents[x].childrenPtr[j]));

		}
	}
	////////// Ascending ID arrangement of residents ///////////////////
	OrderByAscID(p);
	p->countofresident++;
}



//OPTION 2
//פונקציה אשר מקבלת מצביע למבנה מנהל, קולטת מהמשתמש ת.ז. ובודקת האם קיים תושב כזה (בעל אותו ת.ז.) 
void search_person(const Db_mgr* db) {

	unsigned long int id;
	Person* p = malloc(sizeof(Person));
	printf("Enter the ID of the person you want to find\n");
	scanf("%lu", &id);
	p = search_id(p, id);
	if (p == NULL) {
		printf("Couldn't find the given ID\n");
	}

	else {
		print_person(p);
	}
}

//OPTION 3
//פונקציה שמקבלת מצביע למבנה מנהל, ובודקת האם ההורים קיימים ומדפיסה במידה וכן
void search_parents(const Db_mgr* p)
{
	unsigned long id;
	printf("Enter ID\n");
	scanf("%lu", &id);
	Person* p = search_id(p, id);
	if (p==NULL)
	{
		printf("No resident has been found\n");
	}
	else
	{
		printParents(p);
	}
}

//OPTION 4
//מקבלת מצביע למבנה מנהל, ובתוך הפונקציה קולטת תעודת זהות, ומוחקת את הבן אדם המתאים ממערך התושבים, ומעדכנת את הקשרים בהתאם, ולבסוף מצמצמת את מערך התושבים
void delete_person(Db_mgr* p) 
{
	unsigned long int Idint; // משתנה לצורך המרה של ת"ז של הילדים
	char gender; // על מנת לבדוק האם האדם הוא אבא או אמא
	unsigned long int id, partnerID;
	printf("Enter the ID of the person you want to delete\n");
	scanf("%lu", &id);
	printf("What's his gender? f - female OR m - male\n");
	scanf(" %c", &gender);
	Person* p1 = malloc(sizeof(Person));
	Person* f = malloc(sizeof(Person));
	Person* m = malloc(sizeof(Person));
	p1 = search_id(p, id);
	f = search_id(p, p1->fatherId); //מחזיר את האבא כמצביע לתושב
	m = search_id(p, p1->motherId); //מחזיר את האמא כמצביע לתושבת
	partnerID = p1->partnerId;
	if (p1==NULL) //במידה והתושב לא קיים
	{
		printf("Couldn't find the given id\n");
	}
	else 
	{
		if (p1->partnerId) 
		{
			UpdatePartnerID(p, partnerID); //איפוס שדה אצל הפרטנר
		}
		if (HasFather(p,p1)) //במידה וקיים, מחיקה של הת"ז ממערך הילדים
		{
			UpdateKids(p, f);
			EraseKidsID(p, f, id);
		}
		if (HasMother(p,p1)) //במידה וקיימת, מחיקה של הת"ז ממערך הילדים
		{
			UpdateKids(p, m);
			EraseKidsID(p, m, id);
		}
		if (gender=='f') //אם תושבת, מחיקת הת"ז בשדה של ת"ז של אמא - אצל כל הילדים
		{
			for (int i = 0; i < p1->numOfChildren; i++)
			{
				Idint = atoll(p1->childrenPtr[i]);
				EraseMotherID(search_id(p, Idint));
			}
		}
		else if (gender=='m') //אם תושב, מחיקת הת"ז בשדה של ת"ז של אבא - אצל כל הילדים
		{
			for (int i = 0; i < p1->numOfChildren; i++)
			{
				Idint = atoll(p1->childrenPtr[i]);
				EraseFatherID(search_id(p, Idint));
			}
		}
	}
	for (int i = 0; i < p->numOfResidents; i++) //הזזה של התושבים בהתאם, דריסה של התושב שרוצים למחוק
	{
		if (p->residents[i].id==id)
		{
			for (int j = i; j < p->numOfResidents - 1; j++)
			{
				copyStruct(&p->residents[j], &p->residents[j + 1]);
			}
			break;
		}
	}
	p->countofresident--; //עדכון הגודל בפועל של התושבים
	ChangeResidents(p, p->countofresident); //הקטנה של מערך התושבים
	OrderByAscID(p); //סידור של התושבים לפי סדר ת"ז עולה
}

//OPTION 5
int get_gen(const Db_mgr* db) //הפונקציה מקבלת מצביע למבנה מנהל, ומחזירה את מספר הדורות
{
	unsigned long int ID;
	int size = 0;
	int j = 0;
	int gen = 0;
	int count = 0;
	int index = 1;
	int subindex = 0;
	int arrayofsize[10];
	Person* primary = (Person*)malloc(sizeof(Person));
	Person* kids = (Person*)malloc(sizeof(Person));
	Person* kidsarray = (Person*)malloc(sizeof(Person));
	printf("Enter the id of the resident\n");
	scanf("%lu", &ID);
	//הקצאת מערך חדש שיאותחל בתושב שקולטים מהמשתמש, ולאחר מכן הוספה של תאים במערך כאשר הילדים הם תושבים, וככה באופן חזרתי עד שמגיעים לילד שאינו תושב או לתושב שאין
	// לו ילדים, ומחזירים את מספר הדור
	if (search_id(db, ID) != NULL) {
		gen++;

	}
	for (int i = 0; i < index; i++) {

		primary = search_id(db, ID);
		if (primary != NULL) {
			gen++;

			size++;
			kidsarray = (Person*)realloc(kidsarray, (size) * sizeof(Person));
			count = hasKids(primary);
			if (count == 0) {
				continue;
			}
			j = 0;


			subindex = index;
			while (count) {

				ID = _atoi64(&(*primary->childrenPtr[j++]));
				kids = search_id(db, ID);
				if (kids != NULL) {

					kidsarray = (Person*)realloc(kidsarray, (++size) * sizeof(Person));
					kidsarray[subindex].id = kids->id;
					for (int k = 0; k < kids->numOfChildren; k++) {
						kidsarray[subindex].childrenPtr = (char**)malloc((kids->numOfChildren + 1) * sizeof(char));
						kidsarray[subindex].childrenPtr[k] = (char*)malloc(strlen(kids->childrenPtr[k]) * sizeof(char));
						kidsarray[subindex].childrenPtr[k] = kids->childrenPtr[k];
					}
					subindex++;
					index++;
				}
				count--;
			}
		}
	}	
	free(primary);
	free(kidsarray);
	return gen;
}

//OPTION 6
void print_db(const Db_mgr* p) //מקבלת מצביע למבנה מנהל, ומדפיסה את כל הרשומות
{
	for (int i = 0; i < p->numOfResidents; i++)
	{
		printf("Person No. [%d]", i + 1);
		print_person(&p->residents[i]);
	}
}

// Option 7

void search_by_name(const Db_mgr* p) //מקבלת מצביע למבנה מנהל, מקבלת קלט של שם פרטי ומשפחה מהמשתמש, ובודקת האם קיים תושב בעל השם הזה
{
	int count = 0;
	char first[ARR_SIZE2];
	char last[ARR_SIZE2];
	printf("Enter first name\n");
	scanf("%s", first);
	printf("Enter last name\n");
	fseek(stdin, 0, SEEK_END);
	scanf("%s", last);
	char* f = (char*)malloc((strlen(first) + 1) * sizeof(char));
	char* l = (char*)malloc((strlen(last) + 1) * sizeof(char));
	if (l==NULL||f==NULL)
	{
		printf("Allocation failed...\n");
	}
	else
	{
		strcpy(f, first);
		strcpy(l, last);
		for (int i = 0; i < p->numOfResidents; i++)
		{
			if (strcmp(p->residents[i].name, f) == 0 && strcmp(p->residents[i].family, l) == 0)
			{
				print_person(&p->residents[i]);
				count = 1;
			}
		}
		if (count==0)
		{
			printf("No residents have been found\n");
		}
	}
	free(f);
	free(l);
}

//OPTION 8
void quit(Db_mgr* db) //מקבלת מצביע למבנה מנהל, ומשחררת את כל הזיכרון הדינאמי שהוקצה, ולאחר מכן מדפיסה הודעה על סיום הריצה;
{
	for (int i = 0; i < db->countofresident; i++)
	{
		free(db->residents[i].name);
		free(db->residents[i].family);
		if (db->residents[i].numOfChildren > 0)
		{
			for (int j = 0; j < db->residents[i].numOfChildren; j++)
			{
				free(db->residents[i].childrenPtr[j]);
			}
		}
	}
	free(db->residents);
	free(db);
	printf("Memory has been freed - Program runtime has ended...\n");
}





//..............EXTRA FUNCTIONS.......................//


void copyStruct(Person *src, const Person *dest) { //העתקה של בן אדם לבן אדם אחר
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

		src->childrenPtr[j] = (char*)malloc(strlen(dest->numOfChildren) * sizeof(char));

		strcpy(src->childrenPtr[j], dest->childrenPtr[j]);

	}

}

void ChangeResidents(Db_mgr *p, int size) { //מקבלת מצביע למבנה מנהל ומשנה את כמות התושבים
	Db_mgr* temp = malloc(sizeof(temp));
	temp->residents = (Person*)calloc(size, sizeof(Person));
	for (int j = 0; j < size; j++) {
		copyStruct(&temp->residents[j], &p->residents[j]);
	}
	p->residents = (Person*)calloc(size, sizeof(Person));
}


Person* search_id(const Db_mgr *p, unsigned long int id) { //מקבלת מצביע למבנה מנהל ומחפשת במאגר תושב לפי ת"ז
	
	for (int j = 0; j < p->numOfResidents; j++) {
		if (p->residents[j].id == id) {
			return &p->residents[j];
		}
	}
	return NULL;
}

void printParents(const Person* p) { //מקבלת מצביע לבן אדם ומדפיס את פרטי ההורים
	if (p->motherId != 0 && p->fatherId != 0) {
		printf("Mother ID: %lu  Father ID: %lu\n", p->motherId, p->fatherId);
	}
	else if (p->motherId != 0 && p->fatherId == 0) {

		printf("Mother ID: %lu  \n", p->motherId);


	}

	else if (p->motherId == 0 && p->fatherId != 0) {
		printf("Father ID: %lu  \n", p->fatherId);

	}
	else {
		printf("There are no parents\n");
	}
}

unsigned long int HasMother(const Db_mgr* p, const Person* d)// מקבלת מצביע למבנה מנהל ולבן אדם, בודקת האם קיימת אמא, במידה וכן מחזירה את הת"ז שלה
{
	Person* p1 = search_id(p, d->id);
	if (p1==NULL)
	{
		printf("No person has been found\n");
		return 0;
	}
	else
	{
		return p1->motherId;
	}
}

unsigned long int HasFather(const Db_mgr* p, const Person* d)//מקבלת מצביע למבנה מנהל ולבן אדם, בודקת האם קיים אבא, במידה וכן מחזירה את הת"ז שלו
{
	Person* p1 = search_id(p, d->id);
	if (p1 == NULL)
	{
		printf("No person has been found\n");
		return 0;
	}
	else
	{
		return p1->fatherId;
	}
}

void UpdateKids(const Db_mgr* p, const Person* d) //מקבלת מצביע למבנה מנהל ולבן אדם, ומעדכנת את מספר הילדים
{
	for (int i = 0; i < p->numOfResidents; i++)
	{
		if (p->residents[i].id==d->id)
		{
			p->residents[i].numOfChildren--;
		}
	}
}

void UpdatePartnerID(const Db_mgr* p, unsigned long int id)//מקבלת מצביע למבנה מנהל ולתעודת זהות, ומעדכנת את הת"ז של הפרטנר
{
	for (int i = 0; i < p->numOfResidents; i++)
	{
		if (p->residents[i].id == id)
		{
			p->residents[i].partnerId = 0;
		}
	}
}

void printBirthday(const Person* p) //מקבלת מצביע לבן אדם ומדפיסה את היום הולדת שלו
{
	printf("Birth date:\n");
	printf("Day: %ld\n", p->birthday.day);
	printf("Month: %u\n", p->birthday.month);
	printf("Year: %u\n", p->birthday.year);
}

void EraseKidsID(const Db_mgr* db, Person* p, unsigned long int id)//מקבלת מצביע למבנה מנהל, לבן אדם ולתעודת זהות, ומוחקת את התושב ממערך הילדים של ההורים שלו
{
	int save;
	char ID[] = { ConvertIDtoChar(id) };
	if (!search_id(db,p->id))
	{
		printf("No such ID has been found\n");
	}
	else
	{
		for (int i = 0; i < p->numOfChildren; i++)

		{
			if (strcmp(p->childrenPtr[i],ID)==0)
			{
				p->childrenPtr[i] = 0;
				for (int j = i; j < p->numOfChildren-1; j++)
				{
					strcpy(p->childrenPtr[j], p->childrenPtr[j + 1]);
					save = j;
				}
				p->childrenPtr[save + 1] = 0;
				break;
			}
		}
	}
}

char* ConvertIDtoChar(unsigned long int id) //המרה של ת"ז למחרוזת
{
	char* ID = (char*)malloc(ARR_SIZE1 * sizeof(char));
	sprintf(ID, "%lu", id);
	return ID;
}


void EraseFatherID(Person* p)//מחיקת ת"ז של האבא
{
	p->fatherId = 0;
}

void EraseMotherID(Person* p)//מחיקת ת"ז של האמא
{
	p->motherId = 0;
}

void OrderByAscID(const Db_mgr* db)//מקבלת מצביע למבנה מנהל ומסדרת לפי ת"ז עולה
{
	Person* temp = (Person*)calloc(1, sizeof(Person));
	for (int index = 0; index <= db->numOfResidents; index++)
	{
		for (int j = index + 1; j <= db->numOfResidents; j++)
		{
			if (db->residents[index].id > db->residents[j].id)
			{
				copyStruct(temp, &db->residents[j]);
				copyStruct(&db->residents[j], &db->residents[index]);
				copyStruct(&db->residents[index], temp);
			}
		}
	}
	free(temp);
}

int hasKids(const Person* p)//מקבלת מצביע מסוג בן אדם, ובודקת האם יש לו ילדים - במידה וכן מחזירה את הכמות
{
	if (p->numOfChildren)
	{
		return p->numOfChildren;
	}
	else
	{
		return 0;
	}
}

