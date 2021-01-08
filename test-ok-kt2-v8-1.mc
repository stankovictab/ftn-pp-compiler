//OPIS: test-temp
//RETURN: 5

int a;

int f(int b) {
	int c;
	c = 4;
	a = 1 + (b == c) ? b : c;
	return a;
}

int main() {
	int x;
	x = f(4);
	return x;
}