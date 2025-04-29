package main

import (
	"fmt"
	"math"
)

// f(x) = 2ln(x) − 0.5x + 1
func f(x float64) float64 {
	return 2*math.Log(x) - 0.5*x + 1
}

// Производная функции для метода Ньютона
func df(x float64) float64 {
	return 2/x - 0.5
}

// Функция для метода простых итераций
func phi(x float64) float64 {
	return x - 0.5*(2*math.Log(x)-0.5*x+1)
}

// Метод половинного деления
func bisection(a, b, precision float64) {
	fmt.Println("Метод половинного деления:")
	fmt.Println("N\tan\t\tbn\t\tbn - an")
	fmt.Println("————————————————————————————————————")

	n := 0
	var c float64

	for math.Abs(b-a) > precision {
		n++
		c = (a + b) / 2
		fmt.Printf("%d\t%.6f\t%.6f\t%.6f\n", n, a, b, math.Abs(b-a))

		if f(c) == 0.0 {
			break
		} else if f(a)*f(c) < 0 {
			b = c
		} else {
			a = c
		}
	}

	root := (a + b) / 2
	fmt.Printf("Найденный корень: %.6f\n", root)
	fmt.Printf("Значение в корне: %.6f\n", f(root))
	fmt.Printf("Количество итераций: %d\n\n", n)
}

// Метод Ньютона
func newton(x0, precision float64) {
	fmt.Println("Метод Ньютона:")
	fmt.Println("N\tXn\t\tXn+1\t\tXn+1 - Xn")
	fmt.Println("————————————————————————————————————")

	n := 0
	x := x0
	var xPrev, delta float64

	for {
		n++
		xPrev = x
		x = xPrev - f(xPrev)/df(xPrev)
		delta = math.Abs(x - xPrev)
		fmt.Printf("%d\t%.6f\t%.6f\t%.6f\n", n, xPrev, x, delta)

		if math.Abs(f(x)) <= precision {
			break
		}
	}

	fmt.Printf("Найденный корень: %.6f\n", x)
	fmt.Printf("Значение в корне: %.6f\n", f(x))
	fmt.Printf("Количество итераций: %d\n\n", n)
}

// Метод простых итераций
func simpleIteration(x0, precision float64) {
	fmt.Println("Метод простых итераций:")
	fmt.Println("N\tXn\t\tXn+1\t\tXn+1 - Xn")
	fmt.Println("————————————————————————————————————")

	n := 0
	x := x0
	var xPrev, delta float64

	for {
		n++
		xPrev = x
		x = phi(xPrev)
		delta = math.Abs(x - xPrev)
		fmt.Printf("%d\t%.6f\t%.6f\t%.6f\n", n, xPrev, x, delta)

		if math.Abs(f(x)) <= precision {
			break
		}
	}

	fmt.Printf("Найденный корень: %.6f\n", x)
	fmt.Printf("Значение в корне: %.6f\n", f(x))
	fmt.Printf("Количество итераций: %d\n", n)
}

func main() {
	precision := 0.0001 // требуемая точность
	a, b := 0.0, 1.0    // графически определили интервал

	// Начальное приближение для Ньютона и простых итераций (середина интервала)
	x0 := (a + b) / 2

	fmt.Printf("Решение уравнения 2ln(x) − 0.5x + 1 = 0 с точностью %.4f\n\n", precision)

	bisection(a, b, precision)
	newton(x0, precision)
	simpleIteration(x0, precision)
}
