//OPIS: test-temp
//RETURN: 20

int a;

int f(int b) {
	int c;
	c = 4;
	a = 1 + (3 == 3) ? 1 : 2;

	if(a == 2)
		a = 1 + (-1 == -1) ? c : 2;

	if(a == 5)
		a = 10 + (1 == 1) ? 10 : c;

	return a;
}

int main() {
	int x;
	x = f(4);
	return x;
}