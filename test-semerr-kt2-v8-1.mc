//OPIS: Ternarni SemErr 1

int a;

int f(int b) {
	int c;
	c = 4;
	a = 1 + (b == c) ? 1u : 2;
	return a;
}

int main() {
	int x;
	x = f(4);
	return x;
}