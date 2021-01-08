//OPIS: Ternarni OK 3
//RETURN: 9

int f(int b) {
	int a;
	int c;
	a = 1;
	c = 4;
	a = 1 + (3 != 3) ? 1 : 2; // 3
	a = a + (-1 != -1) ? c : 2; // 5
	a = a + (1 != 1) ? 10 : c; // 9
	return a;
}

int main() {
	int x;
	x = f(4);
	return x;
}