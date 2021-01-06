//OPIS: 10-2 OK
//RETURN: 2
int f(int t, unsigned iu, int g, unsigned j) {
	g = 10;
	return 2;
}

unsigned y() {
	return 2u;
}

int main() {
	int a, b;
	unsigned h, k;
	h = 2u;
	k = h++ + 1u;
	k++;
	a = f(a, 812u, a + b++, 4u - 3u);
	return a;
}