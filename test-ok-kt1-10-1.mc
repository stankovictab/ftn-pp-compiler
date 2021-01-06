//OPIS: 10-1 OK
//RETURN: 7

int f(int c) {
	int a;
	int g;
	a = 5;
	g = a + c;
	return g;
}

int main() {
	int a; // -4(%14)
	int b; // -8(%14)
	int m; // -12(%14)
	int l; // -16(%14)
	a = 2;
	b = 2;
	m = 3;
	a++;
	b = f(a++);
	a = b + m++ - 5;
	l = 1;
	m = b++ + l++ + 5;
	b = 1;
	a++;
	return a;
}