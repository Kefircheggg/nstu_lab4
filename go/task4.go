package main

import (
	"fmt"
)

func findBorda(candidates []string, votes [][]string) string {
	scores := make(map[string]int)

	for _, vote := range votes {
		for i, candidate := range vote {
			scores[candidate] += len(candidates) - 1 - i
		}
	}

	maxScore := -1
	var winners []string
	for candidate, score := range scores {
		if score > maxScore {
			maxScore = score
			winners = []string{candidate}
		} else if score == maxScore {
			winners = append(winners, candidate)
		}
	}

	if len(winners) == 1 {
		return winners[0]
	}
	return "Ничья между несколькими кандидатами"
}

func findCondorcet(candidates []string, votes [][]string) string {
	pairwise := make(map[string]map[string]int)

	for _, c1 := range candidates {
		pairwise[c1] = make(map[string]int)
	}

	for _, vote := range votes {
		for i := 0; i < len(vote); i++ {
			for j := i + 1; j < len(vote); j++ {
				pairwise[vote[i]][vote[j]]++
			}
		}
	}

	for _, candidate := range candidates {
		isWinner := true
		for _, opponent := range candidates {
			if candidate == opponent {
				continue
			}
			if pairwise[candidate][opponent] <= pairwise[opponent][candidate] {
				isWinner = false
				break
			}
		}
		if isWinner {
			return candidate
		}
	}

	return "Победитель Кондорсе не найден"
}

func main() {
	candidates := []string{"a", "b", "c"}
	votes := [][]string{
		{"a", "c", "b"},
		{"a", "c", "b"},
		{"c", "b", "a"},
	}

	winBorda := findBorda(candidates, votes)
	winCondorcet := findCondorcet(candidates, votes)

	fmt.Println("Победитель по Борда:", winBorda)
	fmt.Println("Победитель по Кондорсе:", winCondorcet)

	if winBorda != winCondorcet {
		fmt.Println("Разные алгоритмы могут давать разные результаты в зависимости от специфики голосования")
	}
}
