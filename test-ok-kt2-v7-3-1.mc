//OPIS: inkrement u numexp-u
//RETURN: 54
// Bio je return 53, ali posto meni y++ zapravo inkrementuje y, bice 54 (po gcc-u je 53, po njihovom je 54)

int y;

int main() {
	int x;
	x = 2;
	y = 6;
	y = x++ + y++ + 42;
	return x + y;
}
