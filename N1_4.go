package main

import (
	"fmt"
	"math"
)

func main() {
	var xStart, xEnd, dx float64

	fmt.Print("X начальное: ")
	fmt.Scan(&xStart)
	fmt.Print("X конечное: ")
	fmt.Scan(&xEnd)
	fmt.Print("Шаг dx: ")
	fmt.Scan(&dx)

	// Заголовок таблицы
	fmt.Println("   X   |    Y")

	// Табулирование
	for x := xStart; x <= xEnd; x += dx {
		y := -math.Sin(math.Pi * x / 4.0)
		fmt.Printf("%6.1f | %8.4f\n", x, y)
	}

	fmt.Println("-------------------")
}
