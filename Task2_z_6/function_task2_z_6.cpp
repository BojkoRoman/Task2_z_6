#include <iostream>
using namespace std;

// Студент
struct stud {
	int npp;
	char grupa[10];
	float reiting;
};

// Группа
struct grupa {
	char name[10];
	int count;
	float average;
	grupa* nextGrupa;
};

// Ф-я для створення структури група. 
grupa* createGrupa() {
	grupa * gr = new grupa;
	grupa* gr2;

	gr->average=0;
	gr->count=0;
	gr->nextGrupa = NULL;

	gr2 = gr;
	gr = NULL;
	return gr2;
}

// Створює массив вказівників на тип stud і дає його значенням NULL
stud** createArrey(int size) {
	stud** in=NULL, **in2=NULL;

	in = new stud*[size];
	for (int i=0; i<size; i++) {
		in[i] = NULL;
	}
	
	in2=in;
	in=NULL;

	return in2;
}

// Ф-я сортування списку студентів
void sort(stud** in, int size) {
	stud* temp;
	bool t = true;
	
	size--;
	while(t) {
		t=false;
		for (int i=size; i>0; i--) {
			if(in[i]->reiting > in[i-1]->reiting) {
				
				temp = in[i];
				in[i] = in[i-1];
				in[i-1] = temp;
				t = true;
			}
		}
	}
}

void sortGrups(grupa** in, int size) {
	grupa* temp;
	bool t = true;
	
	size--;
	while(t) {
		t=false;
		for (int i=size; i>0; i--) {
			if(in[i]->average > in[i-1]->average) {
				
				temp = in[i];
				in[i] = in[i-1];
				in[i-1] = temp;
				t = true;
			}
		}
	}
}

// Створює із однозвязного списку масив.
grupa** createArrayFromList(grupa* head, int& count, char* str) {
	
	grupa** out = NULL;
	grupa** out2 = NULL;
	grupa* gptr = NULL;
	gptr = head;

	count=0;

	// Підрахунок елементів списку
	while(gptr!= NULL) 
	{
		if(gptr!=NULL) 
		{
			if(strstr(gptr->name, str)!=NULL) {
				count++;
			}
		}
		gptr = gptr->nextGrupa;
	}

	out2 = new grupa*[count];
	out = out2;
	out2 = NULL;

	count=0;
	gptr = head;
	while(gptr!= NULL) 
	{
		if(gptr!=NULL) 
		{
			if(strstr(gptr->name, str)!=NULL) 
			{
				out[count] = gptr;
				count++;		
			}
		}
		gptr = gptr->nextGrupa;
	}
	
	return out;
}


// Формує список груп з введених студентів, вираховує середній бал для кожної групи
grupa* countGroupAverage(stud** in, int size) {

	grupa* head;			// Вказівник на початок списку
	grupa* gptr;			
	grupa* prev_gptr;		// Вказівник на попередній елемент

	head = createGrupa();
	gptr = head;
	strcpy(head->name, in[0]->grupa);

	for(int i=0; i<size; i++) {
		gptr = head;				// Вказівник на першу групу
		prev_gptr  = head;			
		
		while (true) {

			if( strstr(in[i]->grupa, gptr->name)!=NULL) {
				// Якщо група існує, прорахувати середній бал				
					gptr->average = (gptr->average*(float)gptr->count + in[i]->reiting) / (float)(gptr->count+1);
					gptr->count++;
			} else {
				prev_gptr = gptr;
				gptr = gptr->nextGrupa;
				
				// Якщо група не існує, створити нову групу 
				if(gptr==NULL) {					
					gptr = createGrupa();
					strcpy(gptr->name, in[i]->grupa); // Створення міні групи Прорахунок середнього балу
					gptr->average = (gptr->average*(float)gptr->count + in[i]->reiting) / (float)(gptr->count+1);
					gptr->count++;

					//і добавити в список
					prev_gptr->nextGrupa = gptr;
				} else continue;
			}
			break; // Вийти із циклу while
		}		
	}

	return head;
}


void find(stud** in, int size, char* str) {

	grupa* grupList = NULL, *gptr = NULL;

	// Формування списку груп
	grupList = countGroupAverage(in, size);
	
	// Вивід всіх груп
	cout << "\nВсі Групи:" << endl;

	gptr = grupList;
	while (gptr != NULL) {
		cout << "Група: \t" << gptr->name << "\tсередній бал :" << gptr->average << endl;
		gptr = gptr->nextGrupa;
	}

	grupa** gr_arr = NULL;
	int gr_arr_size;
	gr_arr = createArrayFromList(grupList, gr_arr_size, str);

	if(gr_arr_size == 0) {
		cout << "\nГрупа " << str << " не знайдено" << endl;
		return;
	} else {
		
		// Сортування масиву груп
		sortGrups(gr_arr, gr_arr_size);
		
		// Вивід відсортованих груп
		cout << "\nЗнайдені групи :" << endl;
		for (int i=0; i<gr_arr_size; i++) { 
			if(i>2) {
				break;
			}
			cout << "Група: " << gr_arr[i]->name << "\t" << "середній бал : " << gr_arr[i]->average << endl;
		}
	}
}

void enter() {
	int size=0;
	stud** students;
	stud* p;

	cout << "Введіть кількість студентів: ";
	cin >> size;
	
	if (size<2) {
		cout << "Значення має бути 2 і вище";
		return;
	}	
	// Створює масив для студентів
	students = createArrey(size);

	for (int i=0; i<size; i++) {
		p = new stud;
		cout << "Студент #" << i+1 << " (Середній бал Групи): "<<endl;
		cout << "Введіть назву групи : ";
		cin >> p->grupa; 
		cout << "Введіть Середній бал Групи : ";
		cin	>> p->reiting;
		p->npp = i+1;
		students[i] = p;
	}
	

	sort(students, size);
	cout << endl << "\nВідсортований список студентів : " << endl;

	for (int i=0; i<size; i++) {
		cout << "Студент " << students[i]->npp << "\t" << students[i]->grupa << "\t" << students[i]->reiting << endl;
	}

	find(students, size, "КН-");

}



