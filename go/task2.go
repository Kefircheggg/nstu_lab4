package main

import (
	"fmt"
	"math/rand"
)

// генерация псевдослучайного числа в диапазоне min-max
func randomInt(min, max int) int {
	return rand.Intn(max-min+1) + min
}

func arrayPrint(n int, snake bool) {
	fmt.Println()
	minVal := 100

	arr := make([][]int, n)
	for i := range arr {
		arr[i] = make([]int, 6)
	}

	// Заполнение массива
	for i := 0; i < n; i++ {
		for j := 0; j < 6; j++ {
			arr[i][j] = minVal
			minVal++
		}
	}

	// Вывод массива
	for i := 0; i < n; i++ {
		if snake && i%2 == 0 {
			for j := 5; j >= 0; j-- {
				fmt.Printf("%4d", arr[i][j])
			}
		} else {
			for j := 0; j < 6; j++ {
				fmt.Printf("%4d", arr[i][j])
			}
		}
		fmt.Println()
	}
}

func main() {
	var n int
	fmt.Print("Введите количество чисел (≥10): ")
	fmt.Scan(&n)

	vec := make([]int, n)
	fmt.Print("Исходный массив: ")

	posNumAmount := 0
	for i := range vec {
		vec[i] = randomInt(-100, 100)
		fmt.Print(vec[i], " ")
		if vec[i] > 0 {
			posNumAmount++
		}
	}
	fmt.Printf("\nПоложительных элементов: %d\n", posNumAmount)

	// Поиск последнего нуля (с конца) и суммирование после него
	foundZero := false
	sumAftZero := 0
	for i := n - 1; i >= 0; i-- {
		if vec[i] == 0 {
			foundZero = true
			for j := i + 1; j < n; j++ {
				sumAftZero += vec[j]
			}
			break
		}
	}

	if foundZero {
		fmt.Printf("%d\n", sumAftZero)
	} else {
		fmt.Println("В массиве нет нуля!")
	}

	// Поиск самой длинной возрастающей подпоследовательности
	current := []int{}
	longest := []int{}
	prev := -101

	for _, val := range vec {
		if len(current) == 0 || val > prev {
			current = append(current, val)
		} else {
			if len(current) > len(longest) {
				longest = append([]int(nil), current...)
			}
			current = []int{val}
		}
		prev = val
	}
	if len(current) > len(longest) {
		longest = current
	}

	fmt.Print("Самая длинная возрастающая последовательность: ")
	for _, x := range longest {
		fmt.Print(x, " ")
	}
	fmt.Println()

	arrayPrint(n, false)
	arrayPrint(n, true)
}
