package main

import "fmt"

func main() {
	var n, m int
	fmt.Scan(&n, &m)

	arr := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&arr[i])
	}

	// Префиксные суммы
	prefix := make([]int64, n+1)
	for i := 0; i < n; i++ {
		prefix[i+1] = prefix[i] + arr[i]
	}

	pos := 0
	lastOpponent := 0
	var scorePavel, scoreVika int64
	pavelTurn := true

	for pos < n {
		remaining := n - pos
		maxK := m
		if remaining < maxK {
			maxK = remaining
		}

		bestK := -1
		bestSum := int64(-1e18)

		for k := 1; k <= maxK; k++ {
			if k == lastOpponent {
				continue
			}
			sum := prefix[pos+k] - prefix[pos]
			if sum > bestSum || (sum == bestSum && k < bestK) {
				bestSum = sum
				bestK = k
			}
		}

		if bestK == -1 {
			bestK = 1
			bestSum = prefix[pos+1] - prefix[pos]
		}

		if pavelTurn {
			scorePavel += bestSum
		} else {
			scoreVika += bestSum
		}

		pos += bestK
		lastOpponent = bestK
		pavelTurn = !pavelTurn
	}

	if scorePavel > scoreVika {
		fmt.Println(1)
	} else {
		fmt.Println(0)
	}
}
