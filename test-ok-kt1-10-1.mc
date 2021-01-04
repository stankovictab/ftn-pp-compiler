//OPIS: 10-1 OK
int f(int c) {
	int a;
	return a;
}

int main() {
	int a;
	int b, c;
	a = 2;
	a = a++;
	b = f(a++);
	a = b + c++ - 5;
	a++;
	return a;
}