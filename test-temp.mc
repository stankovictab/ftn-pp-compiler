int f(int t, unsigned g) {
	int prvavar;
	unsigned drugavar;
	prvavar = 3;
	drugavar = 2u;
	g = 10u;
	return 2;
}

void y(int h) {
	int a;
	a = 3;
}

int main() {
	f(2, 3u);
	y(2);
	return 0;
}