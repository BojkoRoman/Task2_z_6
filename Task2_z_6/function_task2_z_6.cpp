#include <iostream>
using namespace std;

// �������
struct stud {
	int npp;
	char grupa[10];
	float reiting;
};

// ������
struct grupa {
	char name[10];
	int count;
	float average;
	grupa* nextGrupa;
};

// �-� ��� ��������� ��������� �����. 
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

// ������� ������ ��������� �� ��� stud � �� ���� ��������� NULL
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

// �-� ���������� ������ ��������
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

// ������� �� ������������ ������ �����.
grupa** createArrayFromList(grupa* head, int& count, char* str) {
	
	grupa** out = NULL;
	grupa** out2 = NULL;
	grupa* gptr = NULL;
	gptr = head;

	count=0;

	// ϳ�������� �������� ������
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


// ����� ������ ���� � �������� ��������, �������� ������� ��� ��� ����� �����
grupa* countGroupAverage(stud** in, int size) {

	grupa* head;			// �������� �� ������� ������
	grupa* gptr;			
	grupa* prev_gptr;		// �������� �� ��������� �������

	head = createGrupa();
	gptr = head;
	strcpy(head->name, in[0]->grupa);

	for(int i=0; i<size; i++) {
		gptr = head;				// �������� �� ����� �����
		prev_gptr  = head;			
		
		while (true) {

			if( strstr(in[i]->grupa, gptr->name)!=NULL) {
				// ���� ����� ����, ����������� ������� ���				
					gptr->average = (gptr->average*(float)gptr->count + in[i]->reiting) / (float)(gptr->count+1);
					gptr->count++;
			} else {
				prev_gptr = gptr;
				gptr = gptr->nextGrupa;
				
				// ���� ����� �� ����, �������� ���� ����� 
				if(gptr==NULL) {					
					gptr = createGrupa();
					strcpy(gptr->name, in[i]->grupa); // ��������� �� ����� ���������� ���������� ����
					gptr->average = (gptr->average*(float)gptr->count + in[i]->reiting) / (float)(gptr->count+1);
					gptr->count++;

					//� �������� � ������
					prev_gptr->nextGrupa = gptr;
				} else continue;
			}
			break; // ����� �� ����� while
		}		
	}

	return head;
}


void find(stud** in, int size, char* str) {

	grupa* grupList = NULL, *gptr = NULL;

	// ���������� ������ ����
	grupList = countGroupAverage(in, size);
	
	// ���� ��� ����
	cout << "\n�� �����:" << endl;

	gptr = grupList;
	while (gptr != NULL) {
		cout << "�����: \t" << gptr->name << "\t������� ��� :" << gptr->average << endl;
		gptr = gptr->nextGrupa;
	}

	grupa** gr_arr = NULL;
	int gr_arr_size;
	gr_arr = createArrayFromList(grupList, gr_arr_size, str);

	if(gr_arr_size == 0) {
		cout << "\n����� " << str << " �� ��������" << endl;
		return;
	} else {
		
		// ���������� ������ ����
		sortGrups(gr_arr, gr_arr_size);
		
		// ���� ������������ ����
		cout << "\n������� ����� :" << endl;
		for (int i=0; i<gr_arr_size; i++) { 
			if(i>2) {
				break;
			}
			cout << "�����: " << gr_arr[i]->name << "\t" << "������� ��� : " << gr_arr[i]->average << endl;
		}
	}
}

void enter() {
	int size=0;
	stud** students;
	stud* p;

	cout << "������ ������� ��������: ";
	cin >> size;
	
	if (size<2) {
		cout << "�������� �� ���� 2 � ����";
		return;
	}	
	// ������� ����� ��� ��������
	students = createArrey(size);

	for (int i=0; i<size; i++) {
		p = new stud;
		cout << "������� #" << i+1 << " (������� ��� �����): "<<endl;
		cout << "������ ����� ����� : ";
		cin >> p->grupa; 
		cout << "������ ������� ��� ����� : ";
		cin	>> p->reiting;
		p->npp = i+1;
		students[i] = p;
	}
	

	sort(students, size);
	cout << endl << "\n³����������� ������ �������� : " << endl;

	for (int i=0; i<size; i++) {
		cout << "������� " << students[i]->npp << "\t" << students[i]->grupa << "\t" << students[i]->reiting << endl;
	}

	find(students, size, "��-");

}



