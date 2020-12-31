//int f(int c) {
// Return u sledecim zadacima postoji
// f++; // Ovo treba da kaze da nije deklarisano jer trazi samo VAR|PAR
//}

int main() {
	int a;
	int b, c;
	a = 2;
	a = a++;
	// b = f(a++); // Ne radi num_exp vise, samo id i literal
	a = b + c++ - 5;
	a++;
}