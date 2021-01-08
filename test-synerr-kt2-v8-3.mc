//OPIS: Ternarni SynErr 3

int a;

int f(int b) {
	int c;
	c = 4;
	a = 1 + (1 <= 1) ? 1;
	return a;
}

int main() {
	int x;
	x = f(4);
	return x;
}