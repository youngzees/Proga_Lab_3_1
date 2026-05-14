package main

import "fmt"

// Числа Эйлера 2-го рода
var E = [11][]int64{
	{1},
	{1},
	{1, 1},
	{1, 4, 1},
	{1, 11, 11, 1},
	{1, 26, 66, 26, 1},
	{1, 57, 302, 302, 57, 1},
	{1, 120, 1191, 2416, 1191, 120, 1},
	{1, 247, 4293, 15619, 15619, 4293, 247, 1},
	{1, 502, 14608, 88234, 156190, 88234, 14608, 502, 1},
	{1, 1013, 47840, 455192, 1310354, 1310354, 455192, 47840, 1013, 1},
}

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	var a, b int
	fmt.Scan(&a, &b)

	if b == 1 {
		fmt.Println("infinity")
		return
	}

	// Вычисляем A_a(b) = sum_{k=0}^{a-1} E[a][k] * b^(a-1-k)
	var A int64 = 0
	powB := int64(1)
	for k := a - 1; k >= 0; k-- {
		A += E[a][k] * powB
		powB *= int64(b)
	}

	num := A * int64(b)
	den := int64(1)
	for i := 0; i < a+1; i++ {
		den *= int64(b - 1)
	}

	g := gcd(num, den)
	fmt.Printf("%d/%d\n", num/g, den/g)
}
