//OPIS: 7 & 9 test
// f i main nemaju return, izbaca 2 upozorenja
int f(int c) {
	f++; // Ovo treba da kaze da nije deklarisano jer trazi samo VAR|PAR, izbaca gresku
}

int main() {
	int a;
	int b, c;
	a = 2;
	a = a++;
	b = f(a++);
	a = b + c++ - 5;
	a++;
}